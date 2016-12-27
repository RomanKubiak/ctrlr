// Copyright Christian Neumüller 2013. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include <luabind/function_converter.hpp>
#include <boost/function.hpp>

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

typedef int(*f_type)(int, int);

f_type function_test(boost::function<int(int)> g)
{
    TEST_CHECK(g(3) == 9);
    return &f;
}

} // namespace unnamed

void test_main(lua_State* L)
{
    using namespace luabind;

    globals(L)["f"] = &f;
    DOSTRING(L, "assert(f(1, 5) == 6)");

    X x;
    globals(L)["f2"] = boost::function<int(int, int)>(x);
    DOSTRING(L, "assert(f2(4, 3) == 7)");

    object free_f(L, &f);
    boost::function<int(int, int)> free_f_wrapped =
        object_cast<boost::function<int(int, int)> >(free_f);

    TEST_CHECK(free_f_wrapped(2, 6) == 8);

    globals(L)["function_test"] = &function_test;
    DOSTRING(L,
        "local function sqr(n) return n * n end\n"
        "assert(function_test(sqr)(11, 12) == 23)"
    );
}
