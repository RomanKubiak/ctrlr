.. highlight:: lua

Defining classes in Lua
=======================

In addition to binding C++ functions and classes with Lua, luabind also provide
an OO-system in Lua. ::

    class 'lua_testclass'

    function lua_testclass:__init(name)
        self.name = name
    end

    function lua_testclass:print()
        print(self.name)
    end

    a = lua_testclass('example')
    a:print()


Inheritance can be used between lua-classes::

    class 'derived' (lua_testclass)

    function derived:__init()
        lua_testclass.__init(self, 'derived name')
    end

    function derived:print()
        print('Derived:print() -> ')
        lua_testclass.print(self)
    end

The base class is initialized explicitly by calling its ``__init()``
function.

As you can see in this example, you can call the base class member functions.
You can find all member functions in the base class, but you will have to give
the this-pointer (``self``) as first argument.


Deriving in lua
---------------

It is also possible to derive Lua classes from C++ classes, and override
virtual functions with Lua functions. To do this we have to create a wrapper
class for our C++ base class. This is the class that will hold the Lua object
when we instantiate a Lua class.

.. code-block:: c++

    class base
    {
    public:
        base(const char* s)
        { std::cout << s << "\n"; }

        virtual void f(int a)
        { std::cout << "f(" << a << ")\n"; }
    };

    struct base_wrapper : base, luabind::wrap_base
    {
        base_wrapper(const char* s)
            : base(s)
        {}

        virtual void f(int a)
        {
            call<void>("f", a);
        }

        static void default_f(base* ptr, int a)
        {
            return ptr->base::f(a);
        }
    };

    // ...

    module(L)
    [
        class_<base, base_wrapper>("base")
            .def(constructor<const char*>())
            .def("f", &base::f, &base_wrapper::default_f)
    ];

.. Important::
    Since MSVC6.5 doesn't support explicit template parameters
    to member functions, instead of using the member function ``call()``
    you call a free function ``call_member()`` and pass the this-pointer
    as first parameter.

Note that if you have both base classes and a base class wrapper, you must give
both bases and the base class wrapper type as template parameter to
``class_`` (as done in the example above). The order in which you specify
them is not important. You must also register both the static version and the
virtual version of the function from the wrapper, this is necessary in order
to allow luabind to use both dynamic and static dispatch when calling the function.

.. Important::
    It is extremely important that the signatures of the static (default) function
    is identical to the virtual function. The fact that one of them is a free
    function and the other a member function doesn't matter, but the parameters
    as seen from lua must match. It would not have worked if the static function
    took a ``base_wrapper*`` as its first argument, since the virtual function
    takes a ``base*`` as its first argument (its this pointer). There's currently
    no check in luabind to make sure the signatures match.

If we didn't have a class wrapper, it would not be possible to pass a Lua class
back to C++. Since the entry points of the virtual functions would still point
to the C++ base class, and not to the functions defined in Lua. That's why we
need one function that calls the base class' real function (used if the lua
class doesn't redefine it) and one virtual function that dispatches the call
into luabind, to allow it to select if a Lua function should be called, or if
the original function should be called. If you don't intend to derive from a
C++ class, or if it doesn't have any virtual member functions, you can register
it without a class wrapper.

You don't need to have a class wrapper in order to derive from a class, but if
it has virtual functions you may have silent errors.

.. Unnecessary? The rule of thumb is:
  If your class has virtual functions, create a wrapper type, if it doesn't
  don't create a wrapper type.

The wrappers must derive from ``luabind::wrap_base``, it contains a Lua reference
that will hold the Lua instance of the object to make it possible to dispatch
virtual function calls into Lua. This is done through an overloaded member function:

.. code-block:: c++

    template<class Ret>
    Ret call(char const* name, ...)

Its used in a similar way as ``call_function``, with the exception that it doesn't
take a ``lua_State`` pointer, and the name is a member function in the Lua class.

.. warning::

    The current implementation of ``call_member`` is not able to distinguish const
    member functions from non-const. If you have a situation where you have an overloaded
    virtual function where the only difference in their signatures is their constness, the
    wrong overload will be called by ``call_member``. This is rarely the case though.

.. note::
    You can also override virtual member functions per instance which often
    makes it unnecessary to derive a new class in Lua. Instead of e.g. ::

        class "D" (B)

        function D:__init() B.__init(self) end
        function D:virtual_function() ... end

    you may be able to get around with ::

        b = B()
        function b:virtual_function() ... end


.. _sec-objid:

Object identity
~~~~~~~~~~~~~~~

When a pointer or reference to a registered class with a wrapper is passed
to Lua, luabind will query for it's dynamic type. If the dynamic type
inherits from ``wrap_base``, object identity is preserved.

.. code-block:: c++

    struct A { .. };
    struct A_wrap : A, wrap_base { .. };

    A* f(A* ptr) { return ptr; }

    module(L)
    [
        class_<A, A_wrap>("A"),
        def("f", &f)
    ];

::

    > class 'B' (A)
    > x = B()
    > assert(x == f(x)) -- object identity is preserved when object is
                        -- passed through C++

This functionality relies on RTTI being enabled (that ``LUABIND_NO_RTTI`` is
not defined).

Overloading operators
---------------------

You can overload most operators in Lua for your classes. You do this by simply
declaring a member function with the same name as an operator (the name of the
metamethods in Lua). The operators you can overload are:

 - ``__add``
 - ``__sub``
 - ``__mul``
 - ``__div``
 - ``__pow``
 - ``__lt``
 - ``__le``
 - ``__eq``
 - ``__call``
 - ``__unm``
 - ``__tostring``
 - ``__len``

``__tostring`` isn't really an operator, but it's the metamethod that is called
by the standard library's ``tostring()`` function. There's one strange behavior
regarding binary operators. You are not guaranteed that the self pointer you
get actually refers to an instance of your class. This is because Lua doesn't
distinguish the two cases where you get the other operand as left hand value or
right hand value. Consider the following examples::

    class 'my_class'

      function my_class:__init(v)
          self.val = v
      end

      function my_class:__sub(v)
          return my_class(self.val - v.val)
      end

      function my_class:__tostring()
          return self.val
      end

This will work well as long as you only subtracts instances of my_class with
each other. But If you want to be able to subtract ordinary numbers from your
class too, you have to manually check the type of both operands, including the
self object. ::

    function my_class:__sub(v)
        if (type(self) == 'number') then
            return my_class(self - v.val)

        elseif (type(v) == 'number') then
            return my_class(self.val - v)

        else
            -- assume both operands are instances of my_class
            return my_class(self.val - v.val)

        end
    end

The reason why ``__sub`` is used as an example is because subtraction is not
commutative (the order of the operands matters). That's why luabind cannot
change order of the operands to make the self reference always refer to the
actual class instance.

If you have two different Lua classes with an overloaded operator, the operator
of the right hand side type will be called. If the other operand is a C++ class
with the same operator overloaded, it will be prioritized over the Lua class'
operator. If none of the C++ overloads matches, the Lua class operator will be
called.


Finalizers
----------

If an object needs to perform actions when it's collected we provide a
``__finalize`` function that can be overridden in lua-classes. The
``__finalize`` functions will be called on all classes in the inheritance
chain, starting with the most derived type. ::

    ...

    function lua_testclass:__finalize()
        -- called when the an object is collected
    end


Slicing
-------

If your lua C++ classes don't have wrappers (see `Deriving in lua`_) and
you derive from them in lua, they may be sliced. Meaning, if an object
is passed into C++ as a pointer to its base class, the lua part will be
separated from the C++ base part. This means that if you call virtual
functions on that C++ object, they will not be dispatched to the lua
class. It also means that if you adopt the object, the lua part will be
garbage collected.

::

    +--------------------+
    | C++ object         |    <- ownership of this part is transferred
    |                    |       to c++ when adopted
    +--------------------+
    | lua class instance |    <- this part is garbage collected when
    | and lua members    |       instance is adopted, since it cannot
    +--------------------+       be held by c++.


The problem can be illustrated by this example:

.. code-block:: c++

    struct A {};

    A* filter_a(A* a) { return a; }
    void adopt_a(A* a) { delete a; }


.. code-block:: c++

    using namespace luabind;

    module(L)
    [
        class_<A>("A"),
        def("filter_a", &filter_a),
        def("adopt_a", &adopt_a, adopt(_1))
    ]


In lua::

    a = A()
    b = filter_a(a)
    adopt_a(b)

In this example, lua cannot know that ``b`` actually is the same object as
``a``, and it will therefore consider the object to be owned by the C++ side.
When the ``b`` pointer then is adopted, a runtime error will be raised because
an object not owned by lua is being adopted to C++.

If you have a wrapper for your class, none of this will happen, see
`Object identity`_.

