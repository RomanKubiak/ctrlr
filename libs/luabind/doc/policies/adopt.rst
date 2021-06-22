adopt
-----

Motivation
~~~~~~~~~~

Used to transfer ownership across language boundaries.

Defined in
~~~~~~~~~~

::

    #include <luabind/adopt_policy.hpp>

Synopsis
~~~~~~~~

::

    adopt(index)

Parameters
~~~~~~~~~~

============= ===============================================================
Parameter     Purpose
============= ===============================================================
``index``     The index which should transfer ownership, ``_N`` or ``result``
============= ===============================================================

Example
~~~~~~~

::

    X* create()
    {
        return new X;
    }

.. parsed-literal::

    module(L)
    [
        def("create", &create, **adopt(result)**)
    ];

