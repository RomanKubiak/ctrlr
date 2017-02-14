// Copyright Christian Neumüller 2013. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include <luabind/luabind.hpp>
#include <boost/function.hpp>
#if BOOST_VERSION < 105000 && __cplusplus < 201103L
// Test missing before Boost 1.50, so before then guess based on what the compiler claims.
#  define BOOST_NO_CXX11_HDR_FUNCTIONAL
#endif

#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL
#  include <functional>
#endif

namespace {

int f(int x, int y)
{
    return x + y;
}

struct X
{
    int operator()(int x, int y)
    {
        return x + y;
    }
};

} // namespace unnamed

void test_main(lua_State* L)
{
    using namespace luabind;

    boost::function<int(int, int)> free_f(&f);
    X x;
    boost::function<int(int, int)> f_obj(x);

    module(L) [
        def("f", free_f),
        def("xf", f_obj)
    ];

    DOSTRING(L,
        "function test(f)\n"
        "   assert(f(0, 4) == 4)\n"
        "   assert(f(1, 8) == 9)\n"
        "   assert(f(5, 5) == 10)\n"
        "end\n"
    );

    DOSTRING(L, "test(f)");
    DOSTRING(L, "test(xf)");

#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL
    std::function<int(int, int)> free_f2(&f);
    std::function<int(int, int)> f_obj2(x);

    module(L) [
        def("f2", free_f2),
        def("xf2", f_obj2)
    ];

    DOSTRING(L, "test(f2)");
    DOSTRING(L, "test(xf2)");
#endif
}
