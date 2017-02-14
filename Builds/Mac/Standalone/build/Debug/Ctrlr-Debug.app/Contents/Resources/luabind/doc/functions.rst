.. _part-functions:

Binding functions to Lua
========================

To bind functions to Lua you use the function ``luabind::def()``. It has the
following synopsis::

    template<class F, class policies>
    void def(const char* name, F f, const Policies&);

- name is the name the function will have within Lua.
- F is the function pointer you want to register.
- The Policies parameter is used to describe how parameters and return values
  are treated by the function, this is an optional parameter. More on this in
  the :ref:`part-policies` section.

An example usage could be if you want to register the function ``float
std::sin(float)``::

    module(L)
    [
        def("sin", &std::sin)
    ];

Overloaded functions
--------------------

If you have more than one function with the same name, and want to register
them in Lua, you have to explicitly give the signature. This is to let C++ know
which function you refer to. For example, if you have two functions, ``int
f(const char*)`` and ``void f(int)``. ::

    module(L)
    [
        def("f", (int(*)(const char*)) &f),
        def("f", (void(*)(int)) &f)
    ];

Signature matching
------------------

luabind will generate code that checks the Lua stack to see if the values there
can match your functions' signatures. It will handle implicit typecasts between
derived classes, and it will prefer matches with the least number of implicit
casts. In a function call, if the function is overloaded and there's no
overload that match the parameters better than the other, you have an
ambiguity. This will spawn a run-time error, stating that the function call is
ambiguous. A simple example of this is to register one function that takes an
int and one that takes a float. Since Lua doesn't distinguish between floats and
integers, both will always match.

Since all overloads are tested, it will always find the best match (not the
first match). This also means that it can handle situations where the only
difference in the signature is that one member function is const and the other
isn't.

.. sidebar:: Ownership transfer

   To correctly handle ownership transfer, create_a() would need an adopt
   return value policy. More on this in the :ref:`part-policies` section.

For example, if the following function and class is registered:

::

    struct A
    {
        void f();
        void f() const;
    };

    const A* create_a();

    struct B: A {};
    struct C: B {};

    void g(A*);
    void g(B*);

And the following Lua code is executed:

.. code-block:: lua

    a1 = create_a()
    a1:f() -- the const version is called

    a2 = A()
    a2:f() -- the non-const version is called

    a = A()
    b = B()
    c = C()

    g(a) -- calls g(A*)
    g(b) -- calls g(B*)
    g(c) -- calls g(B*)


Calling Lua functions
---------------------

To call a Lua function, you can either use ``call_function()`` or
an ``object``.

::

    template<class Ret>
    Ret call_function(lua_State* L, const char* name, ...)
    template<class Ret>
    Ret call_function(object const& obj, ...)

There are two overloads of the ``call_function`` function, one that calls
a function given its name, and one that takes an object that should be a Lua
value that can be called as a function.

The overload that takes a name can only call global Lua functions. The ...
represents a variable number of parameters that are sent to the Lua
function. This function call may throw ``luabind::error`` if the function
call fails.

The return value isn't actually Ret (the template parameter), but a proxy
object that will do the function call. This enables you to give policies to the
call. You do this with the operator[]. You give the policies within the
brackets, like this::

    int ret = call_function<int>(
        L
      , "a_lua_function"
      , new complex_class()
    )[ adopt(_1) ];

If you want to pass a parameter as a reference, you have to wrap it with the
`Boost.Ref`__.

__ http://www.boost.org/doc/html/ref.html

Like this::

    int ret = call_function(L, "fun", boost::ref(val));


If you want to use a custom error handler for the function call, see
``set_pcall_callback`` under :ref:`sec-pcall-errorfunc`.

Using Lua threads
-----------------

To start a Lua thread, you have to call ``lua_resume()``, this means that you
cannot use the previous function ``call_function()`` to start a thread. You have
to use

::

    template<class Ret>
    Ret resume_function(lua_State* L, const char* name, ...)
    template<class Ret>
    Ret resume_function(object const& obj, ...)

and

::

    template<class Ret>
    Ret resume(lua_State* L, ...)

The first time you start the thread, you have to give it a function to execute. i.e. you
have to use ``resume_function``, when the Lua function yields, it will return the first
value passed in to ``lua_yield()``. When you want to continue the execution, you just call
``resume()`` on your ``lua_State``, since it's already executing a function, you don't pass
it one. The parameters to ``resume()`` will be returned by ``yield()`` on the Lua side.

For yielding C++-functions (without the support of passing data back and forth between the
Lua side and the c++ side), you can use the :ref:`policy-yield` policy.

With the overload of ``resume_function`` that takes an :ref:`part-object`,
it is important that the object was constructed with the thread as its
``lua_State*``. Like this:

.. parsed-literal::

    lua_State* thread = lua_newthread(L);
    object fun = get_global(**thread**)["my_thread_fun"];
    resume_function(fun);


Binding function objects with explicit signatures
-------------------------------------------------

Using ``luabind::tag_function<>`` it is possible to export function objects
from which luabind can't automatically deduce a signature. This can be used to
slightly alter the signature of a bound function, or even to bind stateful
function objects.

Synopsis:

.. parsed-literal::

  template <class Signature, class F>
  *implementation-defined* tag_function(F f);

Where ``Signature`` is a function type describing the signature of ``F``.
It can be used like this::

  int f(int x);

  // alter the signature so that the return value is ignored
  def("f", tag_function<void(int)>(f));

  struct plus
  {
      plus(int x)
        : x(x)
      {}

      int operator()(int y) const
      {
          return x + y;
      }
  };

  // bind a stateful function object
  def("plus3", tag_function<int(int)>(plus(3)));
