// Copyright Daniel Wallin 2010. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef LUABIND_DETAIL_CALL_0X_100630_HPP
# define LUABIND_DETAIL_CALL_0X_100630_HPP

# include <luabind/config.hpp>
# include <luabind/vector.hpp>
# include <luabind/yield_policy.hpp>
# include <luabind/detail/policy.hpp>
# include <luabind/detail/index_tuple.hpp>
# include <type_traits>

namespace luabind { namespace detail {

struct invoke_context;

struct LUABIND_API function_object
{
    function_object(lua_CFunction entry)
      : entry(entry)
      , next(0)
    {}

    virtual ~function_object()
    {}

    virtual int call(
        lua_State* L, invoke_context& ctx) const = 0;
    virtual void format_signature(lua_State* L, char const* function) const = 0;

    lua_CFunction entry;
    std::string name;
    function_object* next;
    object keepalive;
};

struct LUABIND_API invoke_context
{
    invoke_context()
      : best_score((std::numeric_limits<int>::max)())
      , candidate_index(0)
    {}

    operator bool() const
    {
        return candidate_index == 1;
    }

    void format_error(lua_State* L, function_object const* overloads) const;

    int best_score;
    function_object const* candidates[10];
    int candidate_index;
};

template <class F, class... Args, class Policies>
inline int invoke(
    lua_State* L, function_object const& self, invoke_context& ctx
  , F const& f, vector<Args...>, Policies const& policies)
{
    return invoke_aux(
        L, self, ctx, f, policies, vector<Args...>()
      , typename make_index_tuple<sizeof...(Args) - 1>::type()
    );
}

template <int N, class T, class Policies>
struct make_arg_converter
{
    typedef typename find_conversion_policy<N + 1, Policies>::type generator;
    typedef typename mpl::apply_wrap2<generator, T, lua_to_cpp>::type type;
};

template <class R, class Policies>
struct make_result_converter
{
    typedef typename find_conversion_policy<0, Policies>::type generator;
    typedef typename mpl::apply_wrap2<generator, R, cpp_to_lua>::type type;
};

struct void_result
{};

template <class Policies>
struct make_result_converter<void, Policies>
{
    typedef void_result type;
};

template <class F, class Policies, class R, class... Args, int... Indices>
inline int invoke_aux(
    lua_State* L, function_object const& self, invoke_context& ctx
  , F const& f, Policies const& policies
  , vector<R, Args...>, index_tuple<Indices...>)
{
    typename make_result_converter<R, Policies>::type result_converter;

    return invoke_actual(
        L, self, ctx, f, policies
      , vector<R, Args...>(), index_tuple<Indices...>(), result_converter
      , typename make_arg_converter<Indices, Args, Policies>::type()...
    );
}

inline int sum_scores(int const* first, int const* last)
{
    int result = 0;

    for (; first != last; ++first)
    {
        if (*first < 0)
            return *first;
        result += *first;
    }

    return result;
}

template <class T, class Converter>
int compute_score(lua_State* L, Converter& converter, int index)
{
    return converter.match(L, LUABIND_DECORATE_TYPE(T), index);
}

inline int compute_indices(int*, int base)
{
    return base;
}

template <class Converter, class... Rest>
int compute_indices(
    int* target, int base, Converter& converter, Rest&... rest)
{
    *target = base;
    return compute_indices(target + 1, base + converter.consumed_args(), rest...);
}

template <class F, class ResultConverter, class... Args>
void invoke_function(
    lua_State* L, F const& f, std::false_type, ResultConverter& result_converter
  , Args&&... args)
{
    result_converter.apply(L, f(std::forward<Args>(args)...));
}

template <class F, class... Args>
void invoke_function(
    lua_State* L, F const& f, std::false_type, void_result, Args&&... args)
{
    f(std::forward<Args>(args)...);
}

template <class F, class ResultConverter, class This, class... Args>
void invoke_function(
    lua_State* L, F const& f, std::true_type, ResultConverter& result_converter
  , This&& this_, Args&&... args)
{
    result_converter.apply(L, (this_.*f)(std::forward<Args>(args)...));
}

template <class F, class This, class... Args>
void invoke_function(
    lua_State* L, F const& f, std::true_type, void_result, This&& this_, Args&&... args)
{
    (this_.*f)(std::forward<Args>(args)...);
}

inline int maybe_yield_aux(lua_State*, int results, mpl::false_)
{
    return results;
}

inline int maybe_yield_aux(lua_State* L, int results, mpl::true_)
{
    return lua_yield(L, results);
}

template <class Policies>
int maybe_yield(lua_State* L, int results, Policies*)
{
    return maybe_yield_aux(
        L, results, has_policy<Policies, yield_policy>());
}

// Helper that ignores everything passed to it. Used so that we can invoke
// postcall on converters in a parameter pack expansion.
template <class... T>
void ignore(T&&...)
{}

template <
    class F, class Policies, class R, class... Args, int... Indices
  , class ResultConverter, class... Converters
>
inline int invoke_actual(
    lua_State* L, function_object const& self, invoke_context& ctx
  , F const& f, Policies const& policies
  , vector<R, Args...>, index_tuple<Indices...>
  , ResultConverter& result_converter, Converters&&... converters)
{
    int indices[sizeof...(Args) + 1];
    int const arity = compute_indices(indices + 1, 1, converters...) - 1;

    int const arguments = lua_gettop(L);
    int score = -1;

    if (arity == arguments)
    {
        int const scores[] = {
            compute_score<Args>(L, converters, indices[Indices + 1])...
        };

        score = sum_scores(scores, scores + sizeof...(Args));
    }

    if (score >= 0 && score < ctx.best_score)
    {
        ctx.best_score = score;
        ctx.candidates[0] = &self;
        ctx.candidate_index = 1;
    }
    else if (score == ctx.best_score)
    {
        ctx.candidates[ctx.candidate_index++] = &self;
    }

    int results = 0;

    if (self.next)
    {
        results = self.next->call(L, ctx);
    }

    if (score == ctx.best_score && ctx.candidate_index == 1)
    {
        invoke_function(
            L, f, std::is_member_function_pointer<F>(), result_converter
          , converters.apply(L, LUABIND_DECORATE_TYPE(Args), indices[Indices + 1])...
        );

        ignore(
            (converters.converter_postcall(
                L, LUABIND_DECORATE_TYPE(Args), indices[Indices + 1]), 0)...
        );

        results = maybe_yield(L, lua_gettop(L) - arguments, (Policies*)0);
        indices[0] = arguments + results;

        policy_list_postcall<Policies>::apply(L, indices);
    }

    return results;
}

}} // namespace luabind::detail

#endif // LUABIND_DETAIL_CALL_0X_100630_HPP
