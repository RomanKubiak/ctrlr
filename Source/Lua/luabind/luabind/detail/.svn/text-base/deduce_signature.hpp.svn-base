// Copyright Daniel Wallin 2008. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !BOOST_PP_IS_ITERATING

# ifndef LUABIND_DEDUCE_SIGNATURE_080911_HPP
#  define LUABIND_DEDUCE_SIGNATURE_080911_HPP

#  include <luabind/detail/most_derived.hpp>
#  include <luabind/vector.hpp>

#  ifndef LUABIND_CPP0x
#   if LUABIND_MAX_ARITY <= 8
#    include <boost/mpl/vector/vector10.hpp>
#   else
#    include <boost/mpl/vector/vector50.hpp>
#   endif
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/iteration/iterate.hpp>
#   include <boost/preprocessor/repetition/enum_params.hpp>
#  endif

namespace luabind { namespace detail {

#  ifdef LUABIND_CPP0x

template <class R, class... Args>
vector<R, Args...> deduce_signature(R(*)(Args...), ...)
{
    return vector<R, Args...>();
}

template <class R, class T, class... Args>
vector<R, T&, Args...> deduce_signature(R(T::*)(Args...))
{
    return vector<R, T&, Args...>();
}

template <class R, class T, class Wrapped, class... Args>
vector<R, typename most_derived<T,Wrapped>::type&, Args...>
deduce_signature(R(T::*)(Args...), Wrapped*)
{
    return vector<R, typename most_derived<T,Wrapped>::type&, Args...>();
}

template <class R, class T, class... Args>
vector<R, T const&, Args...> deduce_signature(R(T::*)(Args...) const)
{
    return vector<R, T const&, Args...>();
}

template <class R, class T, class Wrapped, class... Args>
vector<R, typename most_derived<T,Wrapped>::type const&, Args...>
deduce_signature(R(T::*)(Args...) const, Wrapped*)
{
    return vector<R, typename most_derived<T,Wrapped>::type const&, Args...>();
}

// This is primarily intended to catch C++0x lambda closures. It figures out
// the signature of a function object, and strips the object type from the
// resulting signature:
//
//   vector<void, unspecified const&, ...>
//
//     into
//
//   vector<void, ...>
//
// This overload is all luabind needs to correctly handle monomorphic function
// objects with a fixed signature such as C++0x lambdas. The standard doesn't
// explicitly say that an implementation isn't allowed to add additional
// overloads of operator() to the closure type, in practice however, noone
// seems to.

template <class Signature>
struct strip_this_argument;

template <class R, class T, class... Args>
struct strip_this_argument<vector<R, T, Args...> >
{
    typedef vector<R, Args...> type;
};

template <class F>
typename strip_this_argument<
    decltype(deduce_signature(&F::operator()))
>::type deduce_signature(F const&)
{
    return typename strip_this_argument<
        decltype(deduce_signature(&F::operator()))>::type();
}

#  else // LUABIND_CPP0x

namespace mpl = boost::mpl;

template <class R>
mpl::vector1<R> deduce_signature(R(*)(), ...)
{
    return mpl::vector1<R>();
}

template <class R, class T>
mpl::vector2<R,T&> deduce_signature(R(T::*)())
{
    return mpl::vector2<R,T&>();
}

template <class R, class T, class Wrapped>
mpl::vector2<R,typename most_derived<T,Wrapped>::type&>
deduce_signature(R(T::*)(), Wrapped*)
{
    return mpl::vector2<R,typename most_derived<T,Wrapped>::type&>();
}

template <class R, class T>
mpl::vector2<R,T const&> deduce_signature(R(T::*)() const)
{
    return mpl::vector2<R,T const&>();
}

template <class R, class T, class Wrapped>
mpl::vector2<R,typename most_derived<T,Wrapped>::type const&>
deduce_signature(R(T::*)() const, Wrapped*)
{
    return mpl::vector2<R,typename most_derived<T,Wrapped>::type const&>();
}

#  define BOOST_PP_ITERATION_PARAMS_1 \
    (3, (1, LUABIND_MAX_ARITY, <luabind/detail/deduce_signature.hpp>))
#  include BOOST_PP_ITERATE()

#  endif // LUABIND_CPP0x

}} // namespace luabind::detail

# endif // LUABIND_DEDUCE_SIGNATURE_080911_HPP

#else // BOOST_PP_IS_ITERATING

# define N BOOST_PP_ITERATION()
# define NPLUS1 BOOST_PP_INC(N)

template <class R, BOOST_PP_ENUM_PARAMS(N,class A)>
BOOST_PP_CAT(mpl::vector,NPLUS1)<R, BOOST_PP_ENUM_PARAMS(N,A)>
deduce_signature(R(*)(BOOST_PP_ENUM_PARAMS(N,A)), ...)
{
    return BOOST_PP_CAT(mpl::vector,NPLUS1)<R,BOOST_PP_ENUM_PARAMS(N,A)>();
}

# define NPLUS2 BOOST_PP_INC(NPLUS1)

template <class R, class T, BOOST_PP_ENUM_PARAMS(N,class A)>
BOOST_PP_CAT(mpl::vector,NPLUS2)<R, T&, BOOST_PP_ENUM_PARAMS(N,A)>
deduce_signature(R(T::*)(BOOST_PP_ENUM_PARAMS(N,A)))
{
    return BOOST_PP_CAT(mpl::vector,NPLUS2)<R,T&,BOOST_PP_ENUM_PARAMS(N,A)>();
}

template <class R, class T, BOOST_PP_ENUM_PARAMS(N,class A), class Wrapped>
BOOST_PP_CAT(mpl::vector,NPLUS2)<
    R, typename most_derived<T,Wrapped>::type&, BOOST_PP_ENUM_PARAMS(N,A)
>
deduce_signature(R(T::*)(BOOST_PP_ENUM_PARAMS(N,A)), Wrapped*)
{
    return BOOST_PP_CAT(mpl::vector,NPLUS2)<
        R,typename most_derived<T,Wrapped>::type&,BOOST_PP_ENUM_PARAMS(N,A)>();
}

template <class R, class T, BOOST_PP_ENUM_PARAMS(N,class A)>
BOOST_PP_CAT(mpl::vector,NPLUS2)<R, T const&, BOOST_PP_ENUM_PARAMS(N,A)>
deduce_signature(R(T::*)(BOOST_PP_ENUM_PARAMS(N,A)) const)
{
    return BOOST_PP_CAT(mpl::vector,NPLUS2)<R,T const&,BOOST_PP_ENUM_PARAMS(N,A)>();
}

template <class R, class T, BOOST_PP_ENUM_PARAMS(N,class A), class Wrapped>
BOOST_PP_CAT(mpl::vector,NPLUS2)<
    R, typename most_derived<T,Wrapped>::type const&, BOOST_PP_ENUM_PARAMS(N,A)
>
deduce_signature(R(T::*)(BOOST_PP_ENUM_PARAMS(N,A)) const, Wrapped*)
{
    return BOOST_PP_CAT(mpl::vector,NPLUS2)<
        R,typename most_derived<T,Wrapped>::type const&,BOOST_PP_ENUM_PARAMS(N,A)>();
}

# undef NPLUS2
# undef NPLUS1
# undef N

#endif  // BOOST_PP_IS_ITERATING

