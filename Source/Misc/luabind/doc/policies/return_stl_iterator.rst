return_stl_iterator
-------------------

Motivation
~~~~~~~~~~

This policy converts an STL container to a generator function that can be used
in lua to iterate over the container. It works on any container that defines
``begin()`` and ``end()`` member functions (they have to return iterators).

Defined in
~~~~~~~~~~

::

    #include <luabind/iterator_policy.hpp>

Synopsis
~~~~~~~~

::

    return_stl_iterator

Example
~~~~~~~

::

    struct X
    {
        std::vector<std::string> names;
    };

.. parsed-literal::

    module(L)
    [
        class_<A>("A")
            .def_readwrite("names", &X::names, **return_stl_iterator**)
    ];

.. code-block:: lua

    > a = A()
    > for name in a.names do
    >  print(name)
    > end

