raw
---

.. note::

    ``raw()`` has been deprecated. ``lua_State*`` parameters are
    automatically handled by luabind.

Motivation
~~~~~~~~~~

This converter policy will pass through the ``lua_State*`` unmodified.
This can be useful for example when binding functions that need to
return a ``luabind::object``. The parameter will be removed from the
function signature, decreasing the function arity by one.

Defined in
~~~~~~~~~~

::

    #include <luabind/raw_policy.hpp>

Synopsis
~~~~~~~~

::

    raw(index)

Parameters
~~~~~~~~~~

============= ===============================================================
Parameter     Purpose
============= ===============================================================
``index``     The index of the lua_State* parameter.
============= ===============================================================

Example
~~~~~~~

::

    void greet(lua_State* L)
    {
        lua_pushstring(L, "hello");
    }

.. parsed-literal::

    module(L)
    [
        def("greet", &greet, **raw(_1)**)
    ];

.. code-block:: lua

    > print(greet())
    hello

