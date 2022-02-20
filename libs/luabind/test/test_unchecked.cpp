// Copyright Christian Neumüller 2013. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include "test.hpp"
#include <luabind/luabind.hpp>

void test_main(lua_State* L)
{
    DOSTRING(L,
        "class 'Foo'\n"
        "function Foo:__init() end\n"
    );

    // Direct calls to metamethods used to cause access violations.

    DOSTRING_EXPECTED(L, "getmetatable(Foo).__index()",
        "[string \"getmetatable(Foo).__index()\"]:1: "
        "attempt to index a boolean value"
    );

    DOSTRING(L, "foo = Foo()");

    DOSTRING_EXPECTED(L, "getmetatable(foo).__index()",
        "[string \"getmetatable(foo).__index()\"]:1: "
        "attempt to index a boolean value"
    );
}
