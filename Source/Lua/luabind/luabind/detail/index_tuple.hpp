// Copyright Daniel Wallin 2010. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef LUABIND_DETAIL_INDEX_TUPLE_100629_HPP
# define LUABIND_DETAIL_INDEX_TUPLE_100629_HPP

namespace luabind { namespace detail {

template <int... N>
struct index_tuple
{};

template <int N, int I, class Indices>
struct make_index_tuple_aux;

template <int N, int I, int... Indices>
struct make_index_tuple_aux<N, I, index_tuple<Indices...> >
  : make_index_tuple_aux<N - 1, I + 1, index_tuple<Indices..., I> >
{};

template <int I, int... Indices>
struct make_index_tuple_aux<0, I, index_tuple<Indices...> >
{
    typedef index_tuple<Indices...> type;
};

template <int N>
struct make_index_tuple
  : make_index_tuple_aux<N, 0, index_tuple<> >
{};

}} // namespace luabind::detail

#endif // LUABIND_DETAIL_INDEX_TUPLE_100629_HPP
