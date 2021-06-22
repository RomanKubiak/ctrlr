// Copyright Christian Neumüller 2015. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include <luabind/function.hpp>

namespace {

void f() { }

} // namespace unnamed

void test_main(lua_State* L)
{
    using namespace luabind;

    module(L)
    [ // 11 functions
        def("f", &f), //  1
        def("f", &f), //  2
        def("f", &f), //  3
        def("f", &f), //  4
        def("f", &f), //  5
        def("f", &f), //  6
        def("f", &f), //  7
        def("f", &f), //  8
        def("f", &f), //  9
        def("f", &f), // 10
        def("f", &f)  // 11
    ];

    DOSTRING_EXPECTED(L, "f()",
        "Ambiguous, candidates:\n" // 11 candidates
        "void f()\n" //  1
        "void f()\n" //  2
        "void f()\n" //  3
        "void f()\n" //  4
        "void f()\n" //  5
        "void f()\n" //  6
        "void f()\n" //  7
        "void f()\n" //  8
        "void f()\n" //  9
        "void f()\n" // 10
        "and 1 additional overload(s) not shown"); // 11
}
