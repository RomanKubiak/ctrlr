// Copyright Christian Neumüller 2013. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include <luabind/luabind.hpp>

struct CppClass {
    CppClass() { }
    void method() { }
};

using namespace luabind;

void test_main(lua_State* L)
{
    module(L) [
        class_<CppClass>("CppClass")
            .def(constructor<>())
            .def("method", &CppClass::method)
    ];

    DOSTRING_EXPECTED(L,
        "t = { }\n"
        "setmetatable(t, {__gc = function(t)\n"
        "    t.cppClass:method() end})\n"
        "t.cppClass = CppClass()\n"
        "t = nil\n"
        "collectgarbage()\n"
      , "error in __gc metamethod ([string \"t = { }...\"]:3: attempt to index field 'cppClass' (a userdata value))")
}
