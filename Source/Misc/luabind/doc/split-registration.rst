.. _part-split-registration:

Splitting up the registration
=============================

It is possible to split up a module registration into several
translation units without making each registration dependent
on the module it's being registered in.

``a.cpp``::

    luabind::scope register_a()
    {
        return
            class_<a>("a")
                .def("f", &a::f)
                ;
    }

``b.cpp``::

    luabind::scope register_b()
    {
        return
            class_<b>("b")
                .def("g", &b::g)
                ;
    }

``module_ab.cpp``::

    luabind::scope register_a();
    luabind::scope register_b();

    void register_module(lua_State* L)
    {
        module("b", L)
        [
            register_a(),
            register_b()
        ];
    }
