// Copyright Christian Neumüller 2016. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Test case by github.com/AndriyAstakhov

#include "test.hpp"
#include <luabind/luabind.hpp>
#include <vector>
#include <boost/static_assert.hpp>

#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>

using namespace luabind;

void test_main(lua_State* L)
{
    BOOST_STATIC_ASSERT((boost::is_base_and_derived<
        number_converter<double const>,
        default_converter<double const> >::value));

    BOOST_STATIC_ASSERT((boost::is_base_and_derived<
        number_converter<double const&>,
        default_converter<double const&> >::value));

    BOOST_STATIC_ASSERT((!boost::is_base_and_derived<
        number_converter<double&>,
        default_converter<double&> >::value));

    module(L) [
        class_<std::vector<double> >("vector_double")
            .def(constructor<>())
            .def(
                "push_back",
                static_cast<void(std::vector<double>::*)(const double&)>(
                    &std::vector<double>::push_back))
    ];

    DOSTRING(L,
        "local vecDouble = vector_double()\n"
        "vecDouble:push_back(1.5)\n");
}
