// Currently fails to compile (See
// https://github.com/Oberon00/luabind/issues/30)

#include "test.hpp"

#include <luabind/luabind.hpp>
#include <luabind/out_value_policy.hpp>

void f(float& val) { val = val + 10.f; }

void test_main(lua_State* L)
{
    using namespace luabind;

    module(L)
    [
         def("f", &f, out_value(_1)) // compiles with "pure_out_value"
    ];

    // out_value
    DOSTRING(L,
        "a = f(5)\n"
        "assert(a == 15)");

}
