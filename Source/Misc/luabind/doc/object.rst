.. _part-object:

Object
======

Since functions have to be able to take Lua values (of variable type) we need a
wrapper around them. This wrapper is called ``luabind::object``. If the
function you register takes an object, it will match any Lua value. To use it,
you need to include ``<luabind/object.hpp>``.

.. topic:: Synopsis

    .. parsed-literal::

        class object
        {
        public:
            template<class T>
            object(lua_State\*, T const& value);
            object(from_stack const&);
            object(object const&);
            object();

            ~object();

            lua_State\* interpreter() const;
            void push() const;
            bool is_valid() const;
            operator *safe_bool_type* () const;

            template<class Key>
            *implementation-defined* operator[](Key const&);

            template<class T>
            object& operator=(T const&);
            object& operator=(object const&);

            bool operator==(object const&) const;
            bool operator<(object const&) const;
            bool operator<=(object const&) const;
            bool operator>(object const&) const;
            bool operator>=(object const&) const;
            bool operator!=(object const&) const;

            template <class T>
            *implementation-defined* operator[](T const& key) const

            void swap(object&);

            *implementation-defined* operator()();

            template<class A0>
            *implementation-defined* operator()(A0 const& a0);

            template<class A0, class A1>
            *implementation-defined* operator()(A0 const& a0, A1 const& a1);

            /\* ... \*/
        };

When you have a Lua object, you can assign it a new value with the assignment
operator (=). When you do this, the ``default_policy`` will be used to make the
conversion from C++ value to Lua. If your ``luabind::object`` is a table you
can access its members through the operator[] or the Iterators_. The value
returned from the operator[] is a proxy object that can be used both for
reading and writing values into the table (using operator=).

Note that it is impossible to know if a Lua value is indexable or not
(``lua_gettable`` doesn't fail, it succeeds or crashes). This means that if
you're trying to index something that cannot be indexed, you're on your own.
Lua will call its ``panic()`` function. See :ref:`sec-lua-panic`.

There are also free functions that can be used for indexing the table, see
`Related functions`_.

The constructor that takes a ``from_stack`` object is used when you want to
initialize the object with a value from the lua stack. The ``from_stack``
type has the following constructor::

     from_stack(lua_State* L, int index);

The index is an ordinary lua stack index, negative values are indexed from the
top of the stack. You use it like this::

     object o(from_stack(L, -1));

This will create the object ``o`` and copy the value from the top of the lua stack.

The ``interpreter()`` function returns the Lua state where this object is stored.
If you want to manipulate the object with Lua functions directly you can push
it onto the Lua stack by calling ``push()``.

The operator== will call lua_compare() on the operands and return its result.

The ``is_valid()`` function tells you whether the object has been initialized
or not. When created with its default constructor, objects are invalid. To make
an object valid, you can assign it a value. If you want to invalidate an object
you can simply assign it an invalid object.

The ``operator safe_bool_type()`` is equivalent to ``is_valid()``. This means
that these snippets are equivalent::

    object o;
    // ...
    if (o)
    {
        // ...
    }

    ...

    object o;
    // ...
    if (o.is_valid())
    {
        // ...
    }

The application operator will call the value as if it was a function. You can
give it any number of parameters (currently the ``default_policy`` will be used
for the conversion). The returned object refers to the return value (currently
only one return value is supported). This operator may throw ``luabind::error``
if the function call fails. If you want to specify policies to your function
call, you can use index-operator (operator[]) on the function call, and give
the policies within the [ and ]. Like this::

    my_function_object(
        2
      , 8
      , new my_complex_structure(6)
    ) [ adopt(_3) ];

This tells luabind to make Lua adopt the ownership and responsibility for the
pointer passed in to the lua-function.

It's important that all instances of object have been destructed by the time
the Lua state is closed. The object will keep a pointer to the lua state and
release its Lua object in its destructor.

Here's an example of how a function can use a table::

    void my_function(object const& table)
    {
        if (type(table) == LUA_TTABLE)
        {
            table["time"] = std::clock();
            table["name"] = std::rand() < 500 ? "unusual" : "usual";

            std::cout << object_cast<std::string>(table[5]) << "\n";
        }
    }

If you take a ``luabind::object`` as a parameter to a function, any Lua value
will match that parameter. That's why we have to make sure it's a table before
we index into it.

::

    std::ostream& operator<<(std::ostream&, object const&);

There's a stream operator that makes it possible to print objects or use
``boost::lexical_cast`` to convert it to a string. This will use lua's string
conversion function. So if you convert a C++ object with a ``tostring``
operator, the stream operator for that type will be used.

Iterators
---------

There are two kinds of iterators. The normal iterator that will use the metamethod
of the object (if there is any) when the value is retrieved. This iterator is simply
called ``luabind::iterator``. The other iterator is called ``luabind::raw_iterator``
and will bypass the metamethod and give the true contents of the table. They have
identical interfaces, which implements the ForwardIterator_ concept. Apart from
the members of standard iterators, they have the following members and constructors:

.. _ForwardIterator: http://www.sgi.com/tech/stl/ForwardIterator.html

.. parsed-literal::

    class iterator
    {
        iterator();
        iterator(object const&);

        object key() const;

        *standard iterator members*
    };

The constructor that takes a ``luabind::object`` is actually a template that can be
used with object. Passing an object as the parameter to the iterator will
construct the iterator to refer to the first element in the object.

The default constructor will initialize the iterator to the one-past-end
iterator. This is used to test for the end of the sequence.

The value type of the iterator is an implementation defined proxy type which
supports the same operations as ``luabind::object``. Which means that in most
cases you can just treat it as an ordinary object. The difference is that any
assignments to this proxy will result in the value being inserted at the
iterators position, in the table.

The ``key()`` member returns the key used by the iterator when indexing the
associated Lua table.

An example using iterators::

    for (iterator i(globals(L)["a"]), end; i != end; ++i)
    {
      *i = 1;
    }

The iterator named ``end`` will be constructed using the default constructor
and hence refer to the end of the sequence. This example will simply iterate
over the entries in the global table ``a`` and set all its values to 1.

Related functions
-----------------

There are a couple of functions related to objects and tables.

::

    int type(object const&);

This function will return the lua type index of the given object.
i.e. ``LUA_TNIL``, ``LUA_TNUMBER`` etc.

::

    template<class T, class K>
    void settable(object const& o, K const& key, T const& value);
    template<class K>
    object gettable(object const& o, K const& key);
    template<class T, class K>
    void rawset(object const& o, K const& key, T const& value);
    template<class K>
    object rawget(object const& o, K const& key);

These functions are used for indexing into tables. ``settable`` and ``gettable``
translates into calls to ``lua_settable`` and ``lua_gettable`` respectively. Which
means that you could just as well use the index operator of the object.

``rawset`` and ``rawget`` will translate into calls to ``lua_rawset`` and
``lua_rawget`` respectively. So they will bypass any metamethod and give you the
true value of the table entry.

::

    template<class T>
    T object_cast<T>(object const&);
    template<class T, class Policies>
    T object_cast<T>(object const&, Policies);

    template<class T>
    boost::optional<T> object_cast_nothrow<T>(object const&);
    template<class T, class Policies>
    boost::optional<T> object_cast_nothrow<T>(object const&, Policies);

The ``object_cast`` function casts the value of an object to a C++ value.
You can supply a policy to handle the conversion from lua to C++. If the cast
cannot be made a ``cast_failed`` exception will be thrown. If you have
defined LUABIND_NO_ERROR_CHECKING (see :ref:`part-build-options`) no checking
will occur, and if the cast is invalid the application may very well crash.
The nothrow versions will return an uninitialized ``boost::optional<T>``
object, to indicate that the cast could not be performed.

The function signatures of all of the above functions are really templates
for the object parameter, but the intention is that you should only pass
objects in there, that's why it's left out of the documentation.

::

    object globals(lua_State*);
    object registry(lua_State*);

These functions return the global environment table and the registry table respectively.

::

  object newtable(lua_State*);

This function creates a new table and returns it as an object.

::

  object getmetatable(object const& obj);
  void setmetatable(object const& obj, object const& metatable);

These functions get and set the metatable of a Lua object.

::

  lua_CFunction tocfunction(object const& value);
  template <class T> T* touserdata(object const& value)

These extract values from the object at a lower level than ``object_cast()``.

::

  object getupvalue(object const& function, int index);
  void setupvalue(object const& function, int index, object const& value);

These get and set the upvalues of ``function``.

Assigning nil
-------------

To set a table entry to ``nil``, you can use ``luabind::nil``. It will avoid
having to take the detour by first assigning ``nil`` to an object and then
assign that to the table entry. It will simply result in a ``lua_pushnil()``
call, instead of copying an object.

Example::

  using luabind;
  object table = newtable(L);
  table["foo"] = "bar";

  // now, clear the "foo"-field
  table["foo"] = nil;
