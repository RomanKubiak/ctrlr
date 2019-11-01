.. _part-classes:

Binding classes to Lua
======================

To register classes you use a class called ``class_``. Its name is supposed to
resemble the C++ keyword, to make it look more intuitive. It has an overloaded
member function ``def()`` that is used to register member functions, operators,
constructors, enums and properties on the class. It will return its
this-pointer, to let you register more members directly.

Let's start with a simple example. Consider the following C++ class::

    class testclass
    {
    public:
        testclass(const std::string& s): m_string(s) {}
        void print_string() { std::cout << m_string << "\n"; }

    private:
        std::string m_string;
    };

To register it with a Lua environment, write as follows (assuming you are using
namespace luabind)::

    module(L)
    [
        class_<testclass>("testclass")
            .def(constructor<const std::string&>())
            .def("print_string", &testclass::print_string)
    ];

This will register the class with the name testclass and constructor that takes
a string as argument and one member function with the name ``print_string``.

.. code-block:: lua

    Lua 5.0  Copyright (C) 1994-2003 Tecgraf, PUC-Rio
    > a = testclass('a string')
    > a:print_string()
    a string

It is also possible to register free functions as member functions. The
requirement on the function is that it takes a pointer, const pointer,
reference or const reference to the class type as the first parameter. The rest
of the parameters are the ones that are visible in Lua, while the object
pointer is given as the first parameter. If we have the following C++ code::

    struct A
    {
        int a;
    };

    int plus(A* o, int v) { return o->a + v; }

You can register ``plus()`` as if it was a member function of A like this::

    class_<A>("A")
        .def("plus", &plus)

``plus()`` can now be called as a member function on A with one parameter, int.
If the object pointer parameter is const, the function will act as if it was a
const member function (it can be called on const objects).


Overloaded member functions
---------------------------

When binding more than one overloads of a member function, or just binding
one overload of an overloaded member function, you have to disambiguate
the member function pointer you pass to ``def``. To do this, you can use an
ordinary C-style cast, to cast it to the right overload. To do this, you have
to know how to express member function types in C++, here's a short tutorial
(for more info, refer to your favorite book on C++).

The syntax for member function pointer follows:

.. parsed-literal::

    *return-value* (*class-name*::\*)(*arg1-type*, *arg2-type*, *...*)

Here's an example illlustrating this::

    struct A
    {
        void f(int);
        void f(int, int);
    };

::

    class_<A>()
        .def("f", (void(A::*)(int))&A::f)

This selects the first overload of the function ``f`` to bind. The second
overload is not bound.


.. _sec-properties:

Properties
----------

To register a global data member with a class is easily done. Consider the
following class::

    struct A
    {
        int a;
    };

This class is registered like this::

    module(L)
    [
        class_<A>("A")
            .def_readwrite("a", &A::a)
    ];

This gives read and write access to the member variable ``A::a``. It is also
possible to register attributes with read-only access::

    module(L)
    [
        class_<A>("A")
            .def_readonly("a", &A::a)
    ];

When binding members that are a non-primitive type, the auto generated getter
function will return a reference to it. This is to allow chained .-operators.
For example, when having a struct containing another struct. Like this::

    struct A { int m; };
    struct B { A a; };

When binding ``B`` to lua, the following expression code should work:

.. code-block:: lua

    b = B()
    b.a.m = 1
    assert(b.a.m == 1)

This requires the first lookup (on ``a``) to return a reference to ``A``, and
not a copy. In that case, luabind will automatically use the dependency policy
to make the return value dependent on the object in which it is stored. So, if
the returned reference lives longer than all references to the object (b in
this case) it will keep the object alive, to avoid being a dangling pointer.

You can also register getter and setter functions and make them look as if they
were a public data member. Consider the following class::

    class A
    {
    public:
        void set_a(int x) { a = x; }
        int get_a() const { return a; }

    private:
        int a;
    };

It can be registered as if it had a public data member a like this::

    class_<A>("A")
        .property("a", &A::get_a, &A::set_a)

This way the ``get_a()`` and ``set_a()`` functions will be called instead of
just writing  to the data member. If you want to make it read only you can just
omit the last parameter. Please note that the get function **has to be
const**, otherwise it won't compile. This seems to be a common source of errors.


Enums
-----

If your class contains enumerated constants (enums), you can register them as
well to make them available in Lua. Note that they will not be type safe, all
enums are integers in Lua, and all functions that takes an enum, will accept
any integer. You register them like this::

    module(L)
    [
        class_<A>("A")
            .enum_("constants")
            [
                value("my_enum", 4),
                value("my_2nd_enum", 7),
                value("another_enum", 6)
            ]
    ];

In Lua they are accessed like any data member, except that they are read-only
and reached on the class itself rather than on an instance of the class.

.. code-block:: lua

    Lua 5.0  Copyright (C) 1994-2003 Tecgraf, PUC-Rio
    > print(A.my_enum)
    4
    > print(A.another_enum)
    6


Operators
---------

To bind operators you have to include ``<luabind/operator.hpp>``.

The mechanism for registering operators on your class is pretty simple. You use
a global name ``luabind::self`` to refer to the class itself and then you just
write the operator expression inside the ``def()`` call. This class::

    struct vec
    {
        vec operator+(int s);
    };

Is registered like this:

.. parsed-literal::

    module(L)
    [
        class_<vec>("vec")
            .def(**self + int()**)
    ];

This will work regardless if your plus operator is defined inside your class or
as a free function.

If your operator is const (or, when defined as a free function, takes a const
reference to the class itself) you have to use ``const_self`` instead of
``self``. Like this:

.. parsed-literal::

    module(L)
    [
        class_<vec>("vec")
            .def(**const_self** + int())
    ];

The operators supported are those available in Lua:

.. parsed-literal::

    +    -    \*    /    ==    <    <=    %

This means, no in-place operators.

Default implementations (described below) are provided for `==` and the
special `__tostring` pseudo-operator. If any other operator is called, Luabind
will trigger an error ("[const] class <type>: no <metamethod name> defined.",
e.g. "class vec: no __div operator defined.").

The equality operator (``==``) has a little hitch; it will not be called if
the references are equal. This means that the ``==`` operator has to do pretty
much what's it's expected to do.

For Luabind's default `==` operator, two objects are equal only if they are
both objects of Luabind-exported classes and have the same addresses, after
casting both to a common base if neccessary. If they do not have a common
base (and are not of the same type), they compare unequal.

Lua does not support operators such as ``!=``, ``>`` or ``>=``. That's why you
can only register the operators listed above. When you invoke one of the
mentioned operators, lua will define it in terms of one of the available
operators.

In the above example the other operand type is instantiated by writing
``int()``. If the operand type is a complex type that cannot easily be
instantiated you can wrap the type in a class called ``other<>``. For example:

To register this class, we don't want to instantiate a string just to register
the operator.

::

    struct vec
    {
        vec operator+(std::string);
    };

Instead we use the ``other<>`` wrapper like this:

.. parsed-literal::

    module(L)
    [
        class_<vec>("vec")
            .def(self + **other<std::string>()**)
    ];

To register an application (function call-) operator:

.. parsed-literal::

    module(L)
    [
        class_<vec>("vec")
            .def( **self(int())** )
    ];

There's one special operator. In Lua it's called ``__tostring``, it's not
really an operator. It is used for converting objects to strings in a standard
way in Lua. If you register this functionality, you will be able to use the lua
standard function ``tostring()`` for converting your object to a string.

To implement this operator in C++ you should supply an ``operator<<`` for
std::ostream. Like this example:

.. parsed-literal::

    class number {};
    std::ostream& operator<<(std::ostream&, number&);

    ...

    module(L)
    [
        class_<number>("number")
            .def(**tostring(self)**)
    ];

If you do not define a ``__tostring`` operator, Luabind supplies a default
which result in strings of the form ``[const] <type> object: <address>``, i.e.
``const`` is prepended if the object is const, ``<type>`` will be the string
you supplied to ``class_`` (or a string derived from `std::type_info::name`
for unnamed classes) and ``<address>`` will be the address of the C++ object.
(Note that in multiple inheritance scenarios where the same object is pushed
as multiple different base types, the addresses returned for the same
most-derived object will differ).


Nested scopes and static functions
----------------------------------

It is possible to add nested scopes to a class. This is useful when you need
to wrap a nested class, or a static function.

.. parsed-literal::

    class_<foo>("foo")
        .def(constructor<>())
        **.scope
        [
            class_<inner>("nested"),
            def("f", &f)
        ]**;

In this example, ``f`` will behave like a static member function of the class
``foo``, and the class ``nested`` will behave like a nested class of ``foo``.

It's also possible to add namespaces to classes using the same syntax.


Derived classes
---------------

If you want to register classes that derives from other classes, you can
specify a template parameter ``bases<>`` to the ``class_`` instantiation. The
following hierarchy::

    struct A {};
    struct B : A {};

Would be registered like this::

    module(L)
    [
        class_<A>("A"),
        class_<B, A>("B")
    ];

If you have multiple inheritance you can specify more than one base. If B would
also derive from a class C, it would be registered like this::

    module(L)
    [
        class_<B, bases<A, C> >("B")
    ];

Note that you can omit ``bases<>`` when using single inheritance.

.. note::
   If you don't specify that classes derive from each other, luabind will not
   be able to implicitly cast pointers between the types.


Smart pointers
--------------

When registering a class you can tell luabind to hold all instances
explicitly created in Lua in a specific smart pointer type, rather than
the default raw pointer. This is done by passing an additional template
parameter to ``class_``:

.. parsed-literal::

    class_<X, **P**>(|...|)

Where the requirements of ``P`` are:

======================== =======================================
Expression               Returns
======================== =======================================
``P(raw)``
``get_pointer(p)``       Convertible to ``X*``
======================== =======================================

where:

* ``raw`` is of type ``X*``
* ``p`` is an instance of ``P``

``get_pointer()`` overloads are provided for the smart pointers in
Boost, and ``std::auto_ptr<>``. Should you need to provide your own
overload, note that it is called unqualified and is expected to be found
by *argument dependent lookup*. Thus it should be defined in the same
namespace as the pointer type it operates on.

For example:

.. parsed-literal::

    class_<X, **boost::scoped_ptr<X>** >("X")
      .def(constructor<>())

Will cause luabind to hold any instance created on the Lua side in a
``boost::scoped_ptr<X>``. Note that this doesn't mean **all** instances
will be held by a ``boost::scoped_ptr<X>``. If, for example, you
register a function::

    std::auto_ptr<X> make_X();

the instance returned by that will be held in ``std::auto_ptr<X>``. This
is handled automatically for all smart pointers that implement a
``get_pointer()`` overload.

.. important::

    ``get_const_holder()`` has been removed. Automatic conversions
    between ``smart_ptr<X>`` and ``smart_ptr<X const>`` no longer work.

.. important::

    ``__ok``  has been removed. Similar functionality can be implemented
    for specific pointer types by doing something along the lines of:

    .. parsed-literal::

      bool is_non_null(std::auto_ptr<X> const& p)
      {
          return p.get();
      }

      |...|

      def("is_non_null", &is_non_null)

When registering a hierarchy of classes, where all instances are to be held
by a smart pointer, all the classes should have the baseclass' holder type.
Like this:

.. parsed-literal::

        module(L)
        [
            class_<base, boost::shared_ptr<base> >("base")
                .def(constructor<>()),
            class_<derived, base, **boost::shared_ptr<base>** >("derived")
                .def(constructor<>())
        ];

Internally, luabind will do the necessary conversions on the raw pointers, which
are first extracted from the holder type.

This means that for Luabind a ``smart_ptr<derived>`` is not related to a
``smart_ptr<base>``, but ``derived*`` and ``base*`` are, as are
``smart_ptr<derived>`` and ``base*``. In other words, upcasting does not work
for smart pointers as target types, but as source types.


Additional support for shared_ptr and intrusive_ptr
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This limitation cannot be removed for all smart pointers in a generic way,
but luabind has special support for

    * ``boost::shared_ptr`` in ``shared_ptr_converter.hpp``
    * ``std::shared_ptr`` in ``std_shared_ptr_converter.hpp``
    * ``boost::intrusive_ptr`` in ``intrusive_ptr_converter.hpp``

You should include the header(s) you need in the cpp files which register
functions that accept the corresponding smart pointer types, to get automatic
conversions from ``smart_ptr<X>`` to ``smart_ptr<Y>``, whenever Luabind would
convert ``X*`` to ``Y*``, removing the limitation mentioned above.

However, the ``shared_ptr`` converters might not behave exactly as you would
expect:

    1. If the shared_ptr requested (from C++) has the exact same type as the
       one which is present in Lua (if any), then a copy will be made.

    2. If the pointee type of the requested shared_ptr has a
       ``shared_from_this`` member (checked automatically at compile time),
       this will be used to obtain a ``shared_ptr``. Caveats:

        * If the object is not already held in a shared_ptr, behavior is
          undefined (probably a ``bad_weak_ptr`` exception will be thrown).

        * If the ``shared_from_this`` member is not a function with the right
          prototype (``ptr_t shared_from_this()`` with the expression ::

            shared_ptr<RequestedT>(raw->shared_from_this(), raw)

          being valid, where ``raw`` is of type ``RequestedT*`` and points to
          the C++ object in Lua.

    3. Otherwise, a new ``shared_ptr`` will be created from the raw pointer
       associated with the Lua object (even if it is not held in a
       ``shared_ptr``). It will have a deleter set that holds a strong
       reference to the Lua object, thus preventing it’s collection until the
       reference is released by invoking the deleter (i.e. by resetting or
       destroying the ``shared_ptr``) or until the assocciated ``lua_State``
       is closed: then the ``shared_ptr`` becomes dangling.

       If such a ``shared_ptr`` is passed back to Lua, the original Lua object
       (userdata) will be passed instead, preventing the creation of more
       ``shared_ptr``\ s with this deleter.

1. is as you should have expected and 2. is special behavior introduced to
avoid 3. when possible. If you cannot derive your (root) classes from
``enable_shared_from_this`` (which is the recommended way of providing a
``shared_from_this`` method) you must be careful not to close the
``lua_State`` when you still have a ``shared_ptr`` obtained by 3.

There are three functions provided to support this (in namespace luabind)::

    bool is_state_unreferenced(lua_State* L);

    typedef void(*state_unreferenced_fun)(lua_State* L);
    void set_state_unreferenced_callback(lua_State* L, state_unreferenced_fun cb);
    state_unreferenced_fun get_state_unreferenced_callback(lua_State* L);

``is_state_unreferenced`` will return ``false`` if closing ``L`` would make
existing ``shared_ptrs`` dangling and ``true`` if it safe (in this respect) to
call ``lua_close(L)``.

The ``cb`` argument passed to ``set_state_unreferenced_callback`` will be
called whenever the return value of ``is_state_unreferenced(L)`` would change
from ``false`` to ``true``.

``get_state_unreferenced_callback`` returns the current
``state_unreferenced_fun`` for ``L``.

A typical use of this functions would be to replace ::

    lua_close(L);

with ::

    if (luabind::is_state_unreferenced(L))
        lua_close(L);
    else
        luabind::set_state_unreferenced_callback(L, &lua_close);

(``lua_close`` happens to be a valid ``state_unreferenced_fun``.)


Unnamed classes
---------------

You can register unnamed classes by not passing a name to ``class_``::

    class_<X>()

This does not export the class object itself to Lua, meaning that
constructors cannot be called and enums are only accessible via objects of
this class' type.

This is useful e.g. for registering multiple instantiations of a class
template, and construct a matching instance using a factory function,
like boost::make_shared of for hiding intermediate classes in inheritance
hierarchies.


.. _sec-split-cls-registration:

Splitting class registrations
-----------------------------

In some situations it may be desirable to split a registration of a class
across different compilation units. Partly to save rebuild time when changing
in one part of the binding, and in some cases compiler limits may force you
to split it. To do this is very simple. Consider the following sample code::

    void register_part1(class_<X>& x)
    {
        x.def(/*...*/);
    }

    void register_part2(class_<X>& x)
    {
        x.def(/*...*/);
    }

    void register_(lua_State* L)
    {
        class_<X> x("x");

        register_part1(x);
        register_part2(x);

        module(L) [ x ];
    }

Here, the class ``X`` is registered in two steps. The two functions
``register_part1`` and ``register_part2`` may be put in separate compilation
units.

To separate the module registration and the classes to be registered, see
:ref:`part-split-registration`.