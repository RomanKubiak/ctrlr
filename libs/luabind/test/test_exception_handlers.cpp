// Copyright Daniel Wallin 2008. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include <luabind/exception_handler.hpp>
#include <luabind/luabind.hpp>

namespace {

struct my_exception {};

void translate_my_exception(lua_State* L, my_exception const&)
{
    lua_pushliteral(L, "my_exception");
}

struct derived_std_exception : std::exception
{
    char const* what() const LUABIND_NOEXCEPT
    {
        return "derived_std_exception";
    }
};

void translate_derived_exception(lua_State* L, derived_std_exception const&)
{
    lua_pushliteral(L, "derived_std_exception");
}

void LUABIND_ATTRIBUTE_NORETURN raise_my_exception()
{
    throw my_exception();
}

void LUABIND_ATTRIBUTE_NORETURN raise_derived()
{
    throw derived_std_exception();
}

} // namespace unnamed

void test_main(lua_State* L)
{
    using namespace luabind;

    register_exception_handler<my_exception>(&translate_my_exception);

    module(L) [
        def("raise", &raise_my_exception),
        def("raise_derived", &raise_derived)
    ];

    DOSTRING(L,
        "status, msg = pcall(raise)\n"
        "assert(status == false)\n"
        "assert(msg == 'my_exception')\n");

    DOSTRING(L,
        "status, msg = pcall(raise_derived)\n"
        "assert(status == false)\n"
        "assert(msg == 'std::exception: \\'derived_std_exception\\'')\n");

    register_exception_handler<derived_std_exception>(&translate_derived_exception);

    DOSTRING(L,
        "status, msg = pcall(raise_derived)\n"
        "assert(status == false)\n"
        "assert(msg == 'derived_std_exception')\n");
}
