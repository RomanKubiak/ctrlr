dependency
----------

Motivation
~~~~~~~~~~

The dependency policy is used to create life-time dependencies between values.
This is needed for example when returning internal references to some class.

Defined in
~~~~~~~~~~

::

    #include <luabind/dependency_policy.hpp>

Synopsis
~~~~~~~~

::

    dependency(nurse_index, patient_index)

Parameters
~~~~~~~~~~

================= ==========================================================
Parameter         Purpose
================= ==========================================================
``nurse_index``   The index which will keep the patient alive.
``patient_index`` The index which will be kept alive.
================= ==========================================================

Example
~~~~~~~

::

    struct X
    {
        B member;
        B& get() { return member; }
    };

.. parsed-literal::

    module(L)
    [
        class_<X>("X")
            .def("get", &X::get, **dependency(result, _1)**)
    ];

