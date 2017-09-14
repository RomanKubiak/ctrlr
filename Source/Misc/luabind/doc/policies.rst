.. _part-policies:

Policies
========

Sometimes it is necessary to control how luabind passes arguments and return
value, to do this we have policies. All policies use an index to associate
them with an argument in the function signature. These indices are ``result``
and ``_N`` (where ``N >= 1``). When dealing with member functions ``_1`` refers
to the ``this`` pointer.

.. contents:: Policies currently implemented
    :local:
    :depth: 1

.. include:: policies/adopt.rst
.. include:: policies/dependency.rst
.. include:: policies/out_value.rst
.. include:: policies/pure_out_value.rst
.. include:: policies/return_reference_to.rst
.. include:: policies/copy.rst
.. include:: policies/discard_result.rst
.. include:: policies/return_stl_iterator.rst
.. include:: policies/raw.rst
.. include:: policies/yield.rst

..  old policies section
    ===================================================

    Copy
    ----

    This will make a copy of the parameter. This is the default behavior when
    passing parameters by-value. Note that this can only be used when passing from
    C++ to Lua. This policy requires that the parameter type has a copy
    constructor.

    To use this policy you need to include ``luabind/copy_policy.hpp``.


    Adopt
    -----

    This will transfer ownership of the parameter.

    Consider making a factory function in C++ and exposing it to lua::

        base* create_base()
        {
            return new base();
        }

        ...

        module(L)
        [
            def("create_base", create_base)
        ];

    Here we need to make sure Lua understands that it should adopt the pointer
    returned by the factory-function. This can be done using the adopt-policy.

    ::

        module(L)
        [
            def(L, "create_base", adopt(return_value))
        ];

    To specify multiple policies we just separate them with '+'.

    ::

        base* set_and_get_new(base* ptr)
        {
            base_ptrs.push_back(ptr);
            return new base();
        }

        module(L)
        [
            def("set_and_get_new", &set_and_get_new,
                adopt(return_value) + adopt(_1))
        ];

    When Lua adopts a pointer, it will call delete on it. This means that it cannot
    adopt pointers allocated with another allocator than new (no malloc for
    example).

    To use this policy you need to include ``luabind/adopt_policy.hpp``.


    Dependency
    ----------

    The dependency policy is used to create life-time dependencies between values.
    Consider the following example::

        struct A
        {
            B member;

            const B& get_member()
            {
                return member;
            }
        };

    When wrapping this class, we would do something like::

        module(L)
        [
            class_<A>("A")
                .def(constructor<>())
                .def("get_member", &A::get_member)
        ];


    However, since the return value of get_member is a reference to a member of A,
    this will create some life-time issues. For example::

        Lua 5.0  Copyright (C) 1994-2003 Tecgraf, PUC-Rio
        a = A()
        b = a:get_member() -- b points to a member of a
        a = nil
        collectgarbage(0)  -- since there are no references left to a, it is
                           -- removed
                           -- at this point, b is pointing into a removed object

    When using the dependency-policy, it is possible to tell luabind to tie the
    lifetime of one object to another, like this::

        module(L)
        [
            class_<A>("A")
                .def(constructor<>())
                .def("get_member", &A::get_member, dependency(result, _1))
        ];

    This will create a dependency between the return-value of the function, and the
    self-object. This means that the self-object will be kept alive as long as the
    result is still alive. ::

        Lua 5.0  Copyright (C) 1994-2003 Tecgraf, PUC-Rio
        a = A()
        b = a:get_member() -- b points to a member of a
        a = nil
        collectgarbage(0)  -- a is dependent on b, so it isn't removed
        b = nil
        collectgarbage(0)  -- all dependencies to a gone, a is removed

    To use this policy you need to include ``luabind/dependency_policy.hpp``.


    Return reference to
    -------------------

    It is very common to return references to arguments or the this-pointer to
    allow for chaining in C++.

    ::

        struct A
        {
            float val;

            A& set(float v)
            {
                val = v;
                return *this;
            }
        };

    When luabind generates code for this, it will create a new object for the
    return-value, pointing to the self-object. This isn't a problem, but could be a
    bit inefficient. When using the return_reference_to-policy we have the ability
    to tell luabind that the return-value is already on the Lua stack.

    ::

        module(L)
        [
            class_<A>("A")
                .def(constructor<>())
                .def("set", &A::set, return_reference_to(_1))
        ];

    Instead of creating a new object, luabind will just copy the object that is
    already on the stack.

    .. warning::
       This policy ignores all type information and should be used only it
       situations where the parameter type is a perfect match to the
       return-type (such as in the example).

    To use this policy you need to include ``luabind/return_reference_to_policy.hpp``.


    Out value
    ---------

    This policy makes it possible to wrap functions that take non const references
    as its parameters with the intention to write return values to them.

    ::

        void f(float& val) { val = val + 10.f; }

    or

    ::

        void f(float* val) { *val = *val + 10.f; }

    Can be wrapped by doing::

        module(L)
        [
            def("f", &f, out_value(_1))
        ];

    When invoking this function from Lua it will return the value assigned to its
    parameter.

    ::

        Lua 5.0  Copyright (C) 1994-2003 Tecgraf, PUC-Rio
        > a = f(10)
        > print(a)
        20

    When this policy is used in conjunction with user define types we often need
    to do ownership transfers.

    ::

        struct A;

        void f1(A*& obj) { obj = new A(); }
        void f2(A** obj) { *obj = new A(); }

    Here we need to make sure luabind takes control over object returned, for
    this we use the adopt policy::

        module(L)
        [
            class_<A>("A"),
            def("f1", &f1, out_value(_1, adopt(_2)))
            def("f2", &f2, out_value(_1, adopt(_2)))
        ];

    Here we are using adopt as an internal policy to out_value. The index
    specified, _2, means adopt will be used to convert the value back to Lua.
    Using _1 means the policy will be used when converting from Lua to C++.

    To use this policy you need to include ``luabind/out_value_policy.hpp``.

    Pure out value
    --------------

    This policy works in exactly the same way as out_value, except that it
    replaces the parameters with default-constructed objects.

    ::

        void get(float& x, float& y)
        {
            x = 3.f;
            y = 4.f;
        }

        ...

        module(L)
        [
            def("get", &get,
                pure_out_value(_1) + pure_out_value(_2))
        ];

    ::

        Lua 5.0  Copyright (C) 1994-2003 Tecgraf, PUC-Rio
        > x, y = get()
        > print(x, y)
        3    5

    Like out_value, it is possible to specify an internal policy used then
    converting the values back to Lua.

    ::

        void get(test_class*& obj)
        {
            obj = new test_class();
        }

        ...

        module(L)
        [
            def("get", &get, pure_out_value(_1, adopt(_1)))
        ];


    Discard result
    --------------

    This is a very simple policy which makes it possible to throw away
    the value returned by a C++ function, instead of converting it to
    Lua. This example makes sure the this reference never gets converted
    to Lua.

    ::

        struct simple
        {
            simple& set_name(const std::string& n)
            {
                name = n;
                return *this;
            }

            std::string name;
        };

        ...

        module(L)
        [
            class_<simple>("simple")
                .def("set_name", &simple::set_name, discard_result)
        ];

    To use this policy you need to include ``luabind/discard_result_policy.hpp``.


    Return STL iterator
    -------------------

    This policy converts an STL container to a generator function that can be used
    in Lua to iterate over the container. It works on any container that defines
    ``begin()`` and ``end()`` member functions (they have to return iterators). It
    can be used like this::

        struct A
        {
            std::vector<std::string> names;
        };


        module(L)
        [
            class_<A>("A")
                .def_readwrite("names", &A::names, return_stl_iterator)
        ];

    The Lua code to iterate over the container::

        a = A()

        for name in a.names do
          print(name)
        end


    To use this policy you need to include ``luabind/iterator_policy.hpp``.


    Yield
    -----

    This policy will cause the function to always yield the current thread when
    returning. See the Lua manual for restrictions on yield.
