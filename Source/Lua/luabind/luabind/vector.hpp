// Copyright Daniel Wallin 2010. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef LUABIND_VECTOR_100629_HPP
# define LUABIND_VECTOR_100629_HPP

# ifdef LUABIND_CPP0x

#  include <boost/mpl/fold.hpp>
#  include <boost/mpl/begin_end_fwd.hpp>
#  include <boost/mpl/front_fwd.hpp>
#  include <boost/mpl/size_fwd.hpp>

namespace luabind {

// This is used to specify function signatures, both in the user interface and
// in the implementation. In the C++03 version this used to be any MPL forward
// sequence. For backward compatibility reasons we provide a conversion layer
// from an MPL sequence.
template <class... Args>
struct vector
{};

namespace detail
{


  template <class... Args>
  struct vector_iterator;

  template <class Head, class... Tail>
  struct vector_iterator<Head, Tail...>
  {
      typedef Head type;
      typedef vector_iterator<Tail...> next;
  };

  template <>
  struct vector_iterator<>
  {};

} // namespace detail

} // namespace luabind

namespace boost { namespace mpl
{

  // MPL sequence adaption layer to ease the transition to C++0x.

  template <class... Args>
  struct begin<luabind::vector<Args...> >
  {
      typedef luabind::detail::vector_iterator<Args...> type;
  };

  template <class... Args>
  struct end<luabind::vector<Args...> >
  {
      typedef luabind::detail::vector_iterator<> type;
  };

  template <class... Args>
  struct size<luabind::vector<Args...> >
    : long_<sizeof...(Args)>
  {};

  template <class Head, class... Tail>
  struct front<luabind::vector<Head, Tail...> >
  {
      typedef Head type;
  };

  template <class Head, class... Tail>
  struct deref<luabind::detail::vector_iterator<Head, Tail...> >
  {
      typedef Head type;
  };

}} // namespace boost::mpl

# endif // LUABIND_CPP0x

namespace luabind { namespace detail
{

# ifdef LUABIND_CPP0x

  struct append_vector
  {
      template <class V, class T>
      struct apply;

      template <class... Args, class T>
      struct apply<vector<Args...>, T>
      {
          typedef vector<Args..., T> type;
      };
  };

  template <class Sequence>
  struct as_vector
    : boost::mpl::fold<Sequence, vector<>, append_vector>
  {};

  template <class... Args>
  struct as_vector<vector<Args...> >
  {
      typedef vector<Args...> type;
  };

# else // LUABIND_CPP0x

  template <class Sequence>
  struct as_vector
  {
      typedef Sequence type;
  };

# endif

}} // namespace luabind::detail

#endif // LUABIND_VECTOR_100629_HPP
