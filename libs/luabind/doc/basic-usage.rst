Basic usage
===========

To use luabind, you must include ``lua.h`` and luabind's main header file::

    extern "C"
    {
        #include "lua.h"
    }

    #include <luabind/luabind.hpp>

This includes support for both registering classes and functions. If you just
want to have support for functions or classes you can include
``luabind/function.hpp`` and ``luabind/class.hpp`` separately::

    #include <luabind/function.hpp>
    #include <luabind/class.hpp>

The first thing you need to do is to call ``luabind::open(lua_State*)`` which
will register the functions to create classes from Lua, and initialize some
state-global structures used by luabind. If you don't call this function you
will hit asserts later in the library. There is no corresponding close function
because once a class has been registered in Lua, there really isn't any good
way to remove it. Partly because any remaining instances of that class relies
on the class being there. Everything will be cleaned up when the state is
closed though.

.. Isn't this wrong? Don't we include lua.h using lua_include.hpp ?

Luabind's headers will never include ``lua.h`` directly, but through
``<luabind/lua_include.hpp>``. If you for some reason need to include another
Lua header, you can modify this file.


Hello world
-----------

::

    #include <iostream>
    #include <luabind/luabind.hpp>

    void greet()
    {
        std::cout << "hello world!\n";
    }

    extern "C" int init(lua_State* L)
    {
        using namespace luabind;

        open(L);

        module(L)
        [
            def("greet", &greet)
        ];

        return 0;
    }

.. code-block:: lua

    Lua 5.0  Copyright (C) 1994-2003 Tecgraf, PUC-Rio
    > loadlib('hello_world.dll', 'init')()
    > greet()
    Hello world!
    >

