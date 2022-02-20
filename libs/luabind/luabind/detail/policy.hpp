// Copyright (c) 2003 Daniel Wallin and Arvid Norberg

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
// ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
// SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
// ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.


#ifndef LUABIND_POLICY_HPP_INCLUDED
#define LUABIND_POLICY_HPP_INCLUDED

#include <boost/bind/arg.hpp>
#include <boost/call_traits.hpp>
#include <boost/config.hpp>
#include <boost/integer_traits.hpp>
#include <boost/limits.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/or.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/version.hpp>

#include <luabind/back_reference_fwd.hpp>
#include <luabind/config.hpp>
#include <luabind/detail/class_registry.hpp>
#include <luabind/detail/debug.hpp>
#include <luabind/detail/decorate_type.hpp>
#include <luabind/detail/has_get_pointer.hpp>
#include <luabind/detail/make_instance.hpp>
#include <luabind/detail/object_rep.hpp>
#include <luabind/detail/primitives.hpp>
#include <luabind/detail/typetraits.hpp>
#include <luabind/from_stack.hpp>
#include <luabind/value_wrapper.hpp>
#include <luabind/weak_ref.hpp>

#include <memory>
#include <string>
#include <typeinfo>

#ifndef LUABIND_NO_SCOPED_ENUM
# if    !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS) \
     && !defined(BOOST_NO_0X_HDR_TYPE_TRAITS)
#  include <type_traits>
# elif BOOST_VERSION >= 105600
#  include <boost/core/underlying_type.hpp>
#  define LUABIND_USE_BOOST_UNDERLYING_TYPE
# endif
#endif

namespace luabind
{
    namespace detail
    {
        struct conversion_policy_base {};
    }

    template<int N, bool HasArg = true>
    struct conversion_policy : detail::conversion_policy_base
    {
        BOOST_STATIC_CONSTANT(int, index = N);
        BOOST_STATIC_CONSTANT(bool, has_arg = HasArg);
    };

    class index_map
    {
    public:
        index_map(const int* m): m_map(m) {}

        int operator[](int index) const
        {
            return m_map[index];
        }

    private:
        const int* m_map;
    };

//   template<class T> class functor;
     class weak_ref;
}

namespace luabind { namespace detail
{
    template<class H, class T>
    struct policy_cons
    {
        typedef H head;
        typedef T tail;

        template<class U>
        policy_cons<U, policy_cons<H,T> > operator,(policy_cons<U,detail::null_type>)
        {
            return policy_cons<U, policy_cons<H,T> >();
        }

        template<class U>
        policy_cons<U, policy_cons<H,T> > operator+(policy_cons<U,detail::null_type>)
        {
            return policy_cons<U, policy_cons<H,T> >();
        }

        template<class U>
        policy_cons<U, policy_cons<H,T> > operator|(policy_cons<U,detail::null_type>)
        {
            return policy_cons<U, policy_cons<H,T> >();
        }
    };

    struct indirection_layer
    {
        template<class T>
        indirection_layer(const T&);
    };

    yes_t is_policy_cons_test(const null_type&);
    template<class H, class T>
    yes_t is_policy_cons_test(const policy_cons<H,T>&);
    no_t is_policy_cons_test(...);

    template<class T>
    struct is_policy_cons
    {
        static const T& t;

        BOOST_STATIC_CONSTANT(bool, value =
            sizeof(is_policy_cons_test(t)) == sizeof(yes_t));

        typedef boost::mpl::bool_<value> type;
    };

    template<bool>
    struct is_string_literal
    {
        static no_t helper(indirection_layer);
        static yes_t helper(const char*);
    };

    template<>
    struct is_string_literal<false>
    {
        static no_t helper(indirection_layer);
    };


    namespace mpl = boost::mpl;

    template <class T, class Clone>
    void make_pointee_instance(lua_State* L, T& x, mpl::true_, Clone)
    {
        if (get_pointer(x))
        {
#ifdef LUABIND_USE_CXX11
            make_instance(L, std::move(x));
#else
            make_instance(L, x);
#endif
        }
        else
        {
            lua_pushnil(L);
        }
    }

    template <class T>
    void make_pointee_instance(lua_State* L, T& x, mpl::false_, mpl::true_)
    {
#ifdef LUABIND_USE_CXX11
        std::unique_ptr<T> ptr(new T(x));
        make_instance(L, std::move(ptr));
#else
        std::auto_ptr<T> ptr(new T(x));
        make_instance(L, ptr);
#endif
    }

    template <class T>
    void make_pointee_instance(lua_State* L, T& x, mpl::false_, mpl::false_)
    {
        make_instance(L, &x);
    }

    template <class T, class Clone>
    void make_pointee_instance(lua_State* L, T& x, Clone)
    {
        make_pointee_instance(L, x, has_get_pointer<T>(), Clone());
    }

// ********** pointer converter ***********

    struct pointer_converter
    {
        typedef pointer_converter type;
        typedef mpl::false_ is_native;

        pointer_converter()
          : result(0)
        {}

        void* result;

        int consumed_args() const
        {
            return 1;
        }

        template<class T>
        void apply(lua_State* L, T* ptr)
        {
            if (ptr == 0)
            {
                lua_pushnil(L);
                return;
            }

            if (luabind::get_back_reference(L, ptr))
                return;

            make_instance(L, ptr);
        }

        template<class T>
        T* apply(lua_State*, by_pointer<T>, int)
        {
            return static_cast<T*>(result);
        }

        template<class T>
        int match(lua_State* L, by_pointer<T>, int index)
        {
            if (lua_isnil(L, index)) return 0;
            object_rep* obj = get_instance(L, index);
            if (obj == 0) return -1;

            if (obj->is_const())
                return -1;

            std::pair<void*, int> s = obj->get_instance(registered_class<T>::id);
            result = s.first;
            return s.second;
        }

        template<class T>
        void converter_postcall(lua_State*, by_pointer<T>, int)
        {}
    };

// ******* value converter *******

    struct value_converter
    {
        typedef value_converter type;
        typedef mpl::false_ is_native;

        int consumed_args() const
        {
            return 1;
        }

        value_converter()
          : result(0)
        {}

        void* result;

        template<class T>
        void apply(lua_State* L, T x)
        {
            if (luabind::get_back_reference(L, x))
                return;

            make_pointee_instance(L, x, mpl::true_());
        }

        template<class T>
        T apply(lua_State*, by_value<T>, int)
        {
            return *static_cast<T*>(result);
        }

        template<class T>
        int match(lua_State* L, by_value<T>, int index)
        {
            // special case if we get nil in, try to match the holder type
            if (lua_isnil(L, index))
                return -1;

            object_rep* obj = get_instance(L, index);
            if (obj == 0) return -1;

            std::pair<void*, int> s = obj->get_instance(registered_class<T>::id);
            result = s.first;
            return s.second;
        }

        template<class T>
        void converter_postcall(lua_State*, T, int) {}
    };

// ******* const pointer converter *******

    struct const_pointer_converter
    {
        typedef const_pointer_converter type;
        typedef mpl::false_ is_native;

        int consumed_args() const
        {
            return 1;
        }

        const_pointer_converter()
          : result(0)
        {}

        void* result;

        template<class T>
        void apply(lua_State* L, const T* ptr)
        {
            if (ptr == 0)
            {
                lua_pushnil(L);
                return;
            }

            if (luabind::get_back_reference(L, ptr))
                return;

            make_instance(L, ptr);
        }

        template<class T>
        T const* apply(lua_State*, by_const_pointer<T>, int)
        {
            return static_cast<T const*>(result);
        }

        template<class T>
        int match(lua_State* L, by_const_pointer<T>, int index)
        {
            if (lua_isnil(L, index)) return 0;
            object_rep* obj = get_instance(L, index);
            if (obj == 0) return -1; // if the type is not one of our own registered types, classify it as a non-match
            std::pair<void*, int> s = obj->get_instance(registered_class<T>::id);
            if (s.second >= 0 && !obj->is_const())
                s.second += 10;
            result = s.first;
            return s.second;
        }

        template<class T>
        void converter_postcall(lua_State*, T, int) {}
    };

// ******* reference converter *******

    struct ref_converter : pointer_converter
    {
        typedef ref_converter type;
        typedef mpl::false_ is_native;

        int consumed_args() const
        {
            return 1;
        }

        template<class T>
        void apply(lua_State* L, T& ref)
        {
            if (luabind::get_back_reference(L, ref))
                return;

            make_pointee_instance(L, ref, mpl::false_());
        }

        template<class T>
        T& apply(lua_State* L, by_reference<T>, int index)
        {
            assert(!lua_isnil(L, index));
            return *pointer_converter::apply(L, by_pointer<T>(), index);
        }

        template<class T>
        int match(lua_State* L, by_reference<T>, int index)
        {
            object_rep* obj = get_instance(L, index);
            if (obj == 0) return -1;

            if (obj->is_const())
                return -1;

            std::pair<void*, int> s = obj->get_instance(registered_class<T>::id);
            result = s.first;
            return s.second;
        }

        template<class T>
        void converter_postcall(lua_State*, T, int) {}
    };

// ******** const reference converter *********

    struct const_ref_converter
    {
        typedef const_ref_converter type;
        typedef mpl::false_ is_native;

        int consumed_args() const
        {
            return 1;
        }

        const_ref_converter()
          : result(0)
        {}

        void* result;

        template<class T>
        void apply(lua_State* L, T const& ref)
        {
            if (luabind::get_back_reference(L, ref))
                return;

            make_pointee_instance(L, ref, mpl::false_());
        }

        template<class T>
        T const& apply(lua_State*, by_const_reference<T>, int)
        {
            return *static_cast<T*>(result);
        }

        template<class T>
        int match(lua_State* L, by_const_reference<T>, int index)
        {
            object_rep* obj = get_instance(L, index);
            if (obj == 0) return -1; // if the type is not one of our own registered types, classify it as a non-match

            std::pair<void*, int> s = obj->get_instance(registered_class<T>::id);
            if (s.second >= 0 && !obj->is_const())
                s.second += 10;
            result = s.first;
            return s.second;
        }

        template<class T>
        void converter_postcall(lua_State*, by_const_reference<T>, int)
        {
        }
    };

    // ****** enum converter ********

    struct enum_converter
    {
        typedef enum_converter type;
        typedef mpl::true_ is_native;

        int consumed_args() const
        {
            return 1;
        }

#ifdef LUABIND_NO_SCOPED_ENUM
        void apply(lua_State* L, int val)
        {
            lua_pushnumber(L, val);
        }
#else
        template<typename T>
        void apply(lua_State* L, T val)
        {
            typedef typename std::underlying_type<T>::type integral_t;
            lua_pushnumber(L, static_cast<integral_t>(val));
        }
#endif

        template<class T>
        T apply(lua_State* L, by_value<T>, int index)
        {
#ifdef LUABIND_NO_SCOPED_ENUM
            typedef int integral_t;
#elif defined(LUABIND_USE_BOOST_UNDERLYING_TYPE)
            typedef typename boost::underlying_type<T>::type integral_t;
#else
            typedef typename std::underlying_type<T>::type integral_t;
#endif
            return static_cast<T>(
                static_cast<integral_t>(lua_tonumber(L, index)));
        }

        template<class T>
        static int match(lua_State* L, by_value<T>, int index)
        {
            if (lua_isnumber(L, index)) return 0; else return -1;
        }

        template<class T>
        T apply(lua_State* L, by_const_reference<T>, int index)
        {
            return static_cast<T>(static_cast<int>(lua_tonumber(L, index)));
        }

        template<class T>
        static int match(lua_State* L, by_const_reference<T>, int index)
        {
            if (lua_isnumber(L, index)) return 0; else return -1;
        }

        template<class T>
        void converter_postcall(lua_State*, T, int) {}
    };

    template <class U>
    struct value_wrapper_converter
    {
        typedef value_wrapper_converter<U> type;
        typedef mpl::true_ is_native;

        int consumed_args() const
        {
            return 1;
        }

        template<class T>
        T apply(lua_State* L, by_const_reference<T>, int index)
        {
            return T(from_stack(L, index));
        }

        template<class T>
        T apply(lua_State* L, by_value<T>, int index)
        {
            return apply(L, by_const_reference<T>(), index);
        }

        template<class T>
        static int match(lua_State* L, by_const_reference<T>, int index)
        {
            return value_wrapper_traits<T>::check(L, index)
                ? (std::numeric_limits<int>::max)() / LUABIND_MAX_ARITY
                : -1;
        }

        template<class T>
        static int match(lua_State* L, by_value<T>, int index)
        {
            return match(L, by_const_reference<T>(), index);
        }

        void converter_postcall(...) {}

        template<class T>
        void apply(lua_State* interpreter, T const& value_wrapper)
        {
            value_wrapper_traits<T>::unwrap(interpreter, value_wrapper);
        }
    };

    template <class T>
    struct default_converter_generator
      : mpl::eval_if<
            is_value_wrapper_arg<T>
          , value_wrapper_converter<T>
          , mpl::eval_if<
                boost::is_enum<typename boost::remove_reference<T>::type>
              , enum_converter
              , mpl::eval_if<
                    is_nonconst_pointer<T>
                  , pointer_converter
                  , mpl::eval_if<
                        is_const_pointer<T>
                      , const_pointer_converter
                      , mpl::eval_if<
                            is_nonconst_reference<T>
                          , ref_converter
                          , mpl::eval_if<
                                is_const_reference<T>
                              , const_ref_converter
                              , value_converter
                            >
                        >
                    >
                >
            >
        >
    {};

} // namespace detail

// *********** default_policy *****************

template <class T, class Enable = void>
struct default_converter
  : detail::default_converter_generator<T>::type
{};

template <class T, class Derived = default_converter<T> >
struct native_converter_base
{
    typedef boost::mpl::true_ is_native;
    typedef typename boost::call_traits<T>::value_type value_type;
    typedef typename boost::call_traits<T>::param_type param_type;

    int consumed_args() const
    {
        return 1;
    }

    template <class U>
    void converter_postcall(lua_State*, U const&, int)
    {}

    int match(lua_State* L, detail::by_value<T>, int index)
    {
        return derived().compute_score(L, index);
    }

    int match(lua_State* L, detail::by_value<T const>, int index)
    {
        return derived().compute_score(L, index);
    }

    int match(lua_State* L, detail::by_const_reference<T>, int index)
    {
        return derived().compute_score(L, index);
    }

    value_type apply(lua_State* L, detail::by_value<T>, int index)
    {
        return derived().from(L, index);
    }

    value_type apply(lua_State* L, detail::by_value<T const>, int index)
    {
        return derived().from(L, index);
    }

    value_type apply(lua_State* L, detail::by_const_reference<T>, int index)
    {
        return derived().from(L, index);
    }

    void apply(lua_State* L, param_type value)
    {
        derived().to(L, value);
    }

    Derived& derived()
    {
        return static_cast<Derived&>(*this);
    }
};

// *********** converter for arithmetic (number) types *****************
template <typename QualifiedT>
struct number_converter
  : native_converter_base<
        typename boost::remove_const<
            typename boost::remove_reference<QualifiedT>::type>::type>
{

    template <
        bool is_integral,
        typename Traits,
        typename TraitsLua = boost::integer_traits<lua_Integer> >
    struct use_integer: boost::mpl::false_ {};

    template <typename Traits, typename TraitsLua>
    struct use_integer<true, Traits, TraitsLua>: boost::mpl::bool_<
        Traits::const_min >= TraitsLua::const_min
        && Traits::const_max <= TraitsLua::const_max>
    {};

    typedef typename boost::remove_const<typename boost::remove_reference<QualifiedT>::type>::type T;
    typedef typename native_converter_base<T>::param_type param_type;
    typedef typename native_converter_base<T>::value_type value_type;

    typedef boost::integer_traits<T> traits;

    typedef use_integer<traits::is_integral, traits> use_integer_t;

    lua_Number do_from(lua_State* L, int index, boost::mpl::false_)
    {
        return lua_tonumber(L, index);
    }

    lua_Integer do_from(lua_State* L, int index, boost::mpl::true_)
    {
        return lua_tointeger(L, index);
    }

    void do_to(lua_State* L, param_type value, boost::mpl::false_)
    {
        lua_pushnumber(L, static_cast<lua_Number>(value));
    }

    void do_to(lua_State* L, param_type value, boost::mpl::true_)
    {
        lua_pushinteger(L, static_cast<lua_Integer>(value));
    }

    int compute_score(lua_State* L, int index)
    {
        return lua_type(L, index) == LUA_TNUMBER ? 0 : -1;
    }

    value_type from(lua_State* L, int index)
    {
        return static_cast<T>(do_from(L, index, use_integer_t()));
    }

    void to(lua_State* L, param_type value)
    {
        do_to(L, value, use_integer_t());
    }
};
// template partial specialization for those types that boost knows to be
// arithmetic and const references to them
template <typename T>
struct default_converter<T,
    typename boost::enable_if<boost::mpl::or_<
          boost::is_arithmetic<T>,
          boost::mpl::and_<
              boost::is_reference<T>,
              boost::is_const<
                  typename boost::remove_reference<T>::type
              >,
              boost::is_arithmetic<
                  typename boost::remove_const<
                      typename boost::remove_reference<T>::type>::type
              >
          >
    > >::type
>
    : number_converter<T> {};

// *********** converter for bool *****************
template <>
struct default_converter<bool>
  : native_converter_base<bool>
{
    static int compute_score(lua_State* L, int index)
    {
        return lua_type(L, index) == LUA_TBOOLEAN ? 0 : -1;
    }

    bool from(lua_State* L, int index)
    {
        return lua_toboolean(L, index) == 1;
    }

    void to(lua_State* L, bool value)
    {
        lua_pushboolean(L, value);
    }
};

template <>
struct default_converter<bool const>
  : default_converter<bool>
{};

template <>
struct default_converter<bool const&>
  : default_converter<bool>
{};

#ifndef LUABIND_NO_RVALUE_REFERENCES
template <>
struct default_converter<bool&&>
  : default_converter<bool>
{};
#endif

// *********** converter for string types *****************
template <>
struct default_converter<std::string>
  : native_converter_base<std::string>
{
    static int compute_score(lua_State* L, int index)
    {
        return lua_type(L, index) == LUA_TSTRING ? 0 : -1;
    }

    std::string from(lua_State* L, int index)
    {
        return std::string(lua_tostring(L, index), lua_rawlen(L, index));
    }

    void to(lua_State* L, std::string const& value)
    {
        lua_pushlstring(L, value.data(), value.size());
    }
};

template <>
struct default_converter<std::string const>
  : default_converter<std::string>
{};

template <>
struct default_converter<std::string const&>
  : default_converter<std::string>
{};

#ifndef LUABIND_NO_RVALUE_REFERENCES
template <>
struct default_converter<std::string&&>
  : default_converter<std::string>
{};
#endif

template <>
struct default_converter<char const*>
{
    typedef boost::mpl::true_ is_native;

    int consumed_args() const
    {
        return 1;
    }

    template <class U>
    static int match(lua_State* L, U, int index)
    {
        int type = lua_type(L, index);
        return (type == LUA_TSTRING || type == LUA_TNIL) ? 0 : -1;
    }

    template <class U>
    char const* apply(lua_State* L, U, int index)
    {
        return lua_tostring(L, index);
    }

    void apply(lua_State* L, char const* str)
    {
        lua_pushstring(L, str);
    }

    template <class U>
    void converter_postcall(lua_State*, U, int)
    {}
};

template <>
struct default_converter<const char* const>
  : default_converter<char const*>
{};

template <>
struct default_converter<char*>
  : default_converter<char const*>
{};

template <std::size_t N>
struct default_converter<char const[N]>
  : default_converter<char const*>
{};

template <std::size_t N>
struct default_converter<char[N]>
  : default_converter<char const*>
{};


// *********** converter for lua_State * arguments - consuming no explicit args *****************
template <>
struct default_converter<lua_State*>
{
    int consumed_args() const
    {
        return 0;
    }

    template <class U>
    lua_State* apply(lua_State* L, U, int)
    {
        return L;
    }

    template <class U>
    static int match(lua_State*, U, int)
    {
        return 0;
    }

    template <class U>
    void converter_postcall(lua_State*, U, int) {}
};

namespace detail
{

    struct default_policy
    {
        BOOST_STATIC_CONSTANT(bool, has_arg = true);

        template<class T>
        static void precall(lua_State*, T, int) {}

        template<class T, class Direction>
        struct apply
        {
            typedef default_converter<T> type;
        };
    };

    template<class T>
    struct is_primitive
      : default_converter<T>::is_native
    {};

// ============== new policy system =================

    template<int, class> struct find_conversion_policy;

    template<bool IsConverter = false>
    struct find_conversion_impl
    {
        template<int N, class Policies>
        struct apply
        {
            typedef typename find_conversion_policy<N, typename Policies::tail>::type type;
        };
    };

    template<>
    struct find_conversion_impl<true>
    {
        template<int N, class Policies>
        struct apply
        {
            typedef typename Policies::head head;
            typedef typename Policies::tail tail;

            BOOST_STATIC_CONSTANT(bool, found = (N == head::index));

            typedef typename
                boost::mpl::if_c<found
                    , head
                    , typename find_conversion_policy<N, tail>::type
                >::type type;
        };
    };

    template<class Policies>
    struct find_conversion_impl2
    {
        template<int N>
        struct apply
            : find_conversion_impl<
                boost::is_base_and_derived<conversion_policy_base, typename Policies::head>::value
            >::template apply<N, Policies>
        {
        };
    };

    template<>
    struct find_conversion_impl2<detail::null_type>
    {
        template<int N>
        struct apply
        {
            typedef default_policy type;
        };
    };

    template<int N, class Policies>
    struct find_conversion_policy : find_conversion_impl2<Policies>::template apply<N>
    {
    };

    template<class List>
    struct policy_list_postcall
    {
        typedef typename List::head head;
        typedef typename List::tail tail;

        static void apply(lua_State* L, const index_map& i)
        {
            head::postcall(L, i);
            policy_list_postcall<tail>::apply(L, i);
        }
    };

    template<>
    struct policy_list_postcall<detail::null_type>
    {
        static void apply(lua_State*, const index_map&) {}
    };

// ==================================================

// ************** precall and postcall on policy_cons *********************


    template<class List>
    struct policy_precall
    {
        typedef typename List::head head;
        typedef typename List::tail tail;

        static void apply(lua_State* L, int index)
        {
            head::precall(L, index);
            policy_precall<tail>::apply(L, index);
        }
    };

    template<>
    struct policy_precall<detail::null_type>
    {
        static void apply(lua_State*, int) {}
    };

    template<class List>
    struct policy_postcall
    {
        typedef typename List::head head;
        typedef typename List::tail tail;

        static void apply(lua_State* L, int index)
        {
            head::postcall(L, index);
            policy_postcall<tail>::apply(L, index);
        }
    };

    template<>
    struct policy_postcall<detail::null_type>
    {
        static void apply(lua_State*, int) {}
    };

    template <class Policies, class Sought>
    struct has_policy
      : mpl::if_<
            boost::is_same<typename Policies::head, Sought>
          , mpl::true_
          , has_policy<typename Policies::tail, Sought>
        >::type
    {};

    template <class Sought>
    struct has_policy<null_type, Sought>
      : mpl::false_
    {};

}} // namespace luabind::detail


namespace luabind { namespace
{
#if defined(__GNUC__) && ( \
    (BOOST_VERSION < 103500) \
 || (BOOST_VERSION < 103900 && (__GNUC__ * 100 + __GNUC_MINOR__ <= 400)) \
 || (__GNUC__ * 100 + __GNUC_MINOR__ < 400))
  static inline boost::arg<0> return_value()
  {
      return boost::arg<0>();
  }

  static inline boost::arg<0> result()
  {
      return boost::arg<0>();
  }
# define LUABIND_PLACEHOLDER_ARG(N) boost::arg<N>(*)()
#elif defined(BOOST_MSVC) || defined(__MWERKS__) \
  || (BOOST_VERSION >= 103900 && defined(__GNUC__) \
        && (__GNUC__ * 100 + __GNUC_MINOR__ == 400))
  static boost::arg<0> return_value;
  static boost::arg<0> result;
# define LUABIND_PLACEHOLDER_ARG(N) boost::arg<N>
#else
  boost::arg<0> return_value;
  boost::arg<0> result;
# define LUABIND_PLACEHOLDER_ARG(N) boost::arg<N>
#endif
}}

#endif // LUABIND_POLICY_HPP_INCLUDED
