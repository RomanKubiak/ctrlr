FAQ
===

What's up with __cdecl and __stdcall?
    If you're having problem with functions
    that cannot be converted from ``void (__stdcall *)(int,int)`` to
    ``void (__cdecl*)(int,int)``. You can change the project settings to make the
    compiler generate functions with __cdecl calling conventions. This is
    a problem in developer studio.

What's wrong with functions taking variable number of arguments?
    You cannot register a function with ellipses in its signature. Since
    ellipses don't preserve type safety, those should be avoided anyway.

Internal structure overflow in VC
    If you, in visual studio, get fatal error C1204: compiler limit :
    internal structure overflow. You should try to split that compilation
    unit up in smaller ones. See :ref:`part-split-registration` and
    :ref:`sec-split-cls-registration`.

What's wrong with precompiled headers in VC?
    Visual Studio doesn't like anonymous namespaces in its precompiled
    headers. If you encounter this problem you can disable precompiled
    headers for the compilation unit (cpp-file) that uses luabind.

error C1076: compiler limit - internal heap limit reached in VC
    In visual studio you will probably hit this error. To fix it you have to
    increase the internal heap with a command-line option. We managed to
    compile the test suit with /Zm300, but you may need a larger heap then
    that.

error C1055: compiler limit \: out of keys in VC
    It seems that this error occurs when too many assert() are used in a
    program, or more specifically, the __LINE__ macro. It seems to be fixed by
    changing /ZI (Program database for edit and continue) to /Zi
    (Program database).

How come my executable is huge?
    If you're compiling in debug mode, you will probably have a lot of
    debug-info and symbols (luabind consists of a lot of functions). Also,
    if built in debug mode, no optimizations were applied, luabind relies on
    that the compiler is able to inline functions. If you built in release
    mode, try running strip on your executable to remove export-symbols,
    this will trim down the size.

    Our tests suggests that cygwin's gcc produces much bigger executables
    compared to gcc on other platforms and other compilers.

.. HUH?! // check the magic number that identifies luabind's functions

Can I register class templates with luabind?
    Yes you can, but you can only register explicit instantiations of the
    class. Because there's no Lua counterpart to C++ templates. For example,
    you can register an explicit instantiation of std::vector<> like this::

        module(L)
        [
            class_<std::vector<int> >("vector")
                .def(constructor<int>)
                .def("push_back", &std::vector<int>::push_back)
        ];

.. Again, irrelevant to docs: Note that the space between the two > is required by C++.

Do I have to register destructors for my classes?
    No, the destructor of a class is always called by luabind when an
    object is collected. Note that Lua has to own the object to collect it.
    If you pass it to C++ and gives up ownership (with adopt policy) it will
    no longer be owned by Lua, and not collected.

    If you have a class hierarchy, you should make the destructor virtual if
    you want to be sure that the correct destructor is called (this apply to C++
    in general).

.. And again, the above is irrelevant to docs. This isn't a general C++ FAQ. But it saves us support questions.

Fatal Error C1063 compiler limit \: compiler stack overflow in VC
    VC6.5 chokes on warnings, if you are getting alot of warnings from your
    code try suppressing them with a pragma directive, this should solve the
    problem.

Crashes when linking against luabind as a dll in Windows
    When you build luabind, Lua and you project, make sure you link against
    the runtime dynamically (as a dll).

I cannot register a function with a non-const parameter
    This is because there is no way to get a reference to a Lua value. Have
    a look at :ref:`policy-out_value` and :ref:`policy-pure_out_value`
    policies.