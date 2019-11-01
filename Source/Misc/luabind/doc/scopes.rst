Scopes
======

Everything that gets registered in Lua is registered in a given Lua table, in
a namespace (Lua table at given name), or in the global scope (called module).
All registrations must be surrounded by its scope. To define a module, the
``luabind::module`` class is used. It is used like this::

    module(L)
    [
        // declarations
    ];

This will register all declared functions or classes in the global namespace
in Lua.

You can also register into a custom Lua table wrapped in a
:ref:`part-object`::

    object mod = newtable(L);
    module(L, mod)
    [
        // declarations
    ];

You can then directly use all object manipulation functions on ``mod``.

If you just want to have a namespace for your module (like the standard
libraries) you can give a name to the constructor, like this::

    module(L, "my_library")
    [
        // declarations
    ];

Here all declarations will be put in the my_library table.

If you want nested namespace's you can use the ``luabind::namespace_`` class. It
works exactly as ``luabind::module`` except that it doesn't take a lua_State*
in it's constructor. An example of its usage could look like this::

    module(L, "my_library")
    [
        // declarations

        namespace_("detail")
        [
            // library-private declarations
        ]
    ];

As you might have figured out, the following declarations are equivalent::

    module(L)
    [
        namespace_("my_library")
        [
            // declarations
        ]

    ];

::

    module(L, "my_library")
    [
        // declarations
    ];

Each declaration must be separated by a comma, like this::

    module(L)
    [
        def("f", &f),
        def("g", &g),
        class_<A>("A")
            .def(constructor<int, int>),
        def("h", &h)
    ];


More about the actual declarations in the :ref:`part-functions` and
:ref:`part-classes` sections.
