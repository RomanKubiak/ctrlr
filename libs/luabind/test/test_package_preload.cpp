// Copyright (c) 2004 Daniel Wallin and Arvid Norberg
// Copyright (c) 2012 Iowa State University

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

#include "test.hpp"
#include <luabind/luabind.hpp>
#include <luabind/set_package_preload.hpp>
#include <cstring>

static int f(int x)
{
    return x + 1;
}

static void loader(lua_State* L, char const* modname)
{
    TEST_CHECK(modname);
    TEST_CHECK(modname && std::strcmp(modname, "testmod") == 0);
    using namespace luabind;
    module(L)
    [
        def("f", &f)
    ];
}

static luabind::object local_loader(lua_State* L, char const* modname)
{
    TEST_CHECK(modname);
    TEST_CHECK(modname && std::strcmp(modname, "testmod_l") == 0);
    using namespace luabind;
    object modtable = newtable(L);
    module(modtable)
    [
        def("f", &f)
    ];
    return modtable;
}

void test_main(lua_State* L)
{
    using namespace luabind;

    set_package_preload(L, "testmod", &loader);
    DOSTRING(L, "assert(require('testmod') == true)");

    DOSTRING(L, "assert(f(7) == 8)");

    set_package_preload(L, "testmod_l", &local_loader);
    DOSTRING(L, "mod = require('testmod_l')");
    DOSTRING(L,
        "assert(not testmod_l)\n" // No global should be created.
        "assert(mod.f(41) == 42)\n"); // Module should be returned.

    DOSTRING(L, "package.preload = nil");
    try {
        set_package_preload(L, "failmod", &loader);
    } catch (luabind::error const&) {
        TEST_CHECK(std::strcmp("attempt to index a nil value", lua_tostring(L, -1)) == 0);
        lua_pop(L, 1);
        return;
    }
    TEST_ERROR("set_package_preload() should have thrown.");
}
