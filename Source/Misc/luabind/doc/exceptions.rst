.. _part-exceptions:

Exceptions
==========

If any of the functions you register throws an exception when called, that
exception will be caught by luabind and converted to an error string and
``lua_error()`` will be invoked. If the exception is a ``std::exception`` or a
``const char*`` the string that is pushed on the Lua stack, as error message,
will be the string returned by ``std::exception::what()`` or the string itself
respectively. If the exception is unknown, a generic string saying that the
function threw an exception will be pushed.

If you have an exception type that isn't derived from
``std::exception``, or you wish to change the error message from the
default result of ``what()``, it is possible to register custom
exception handlers::

  struct my_exception
  {};

  void translate_my_exception(lua_State* L, my_exception const&)
  {
      lua_pushstring(L, "my_exception");
  }

  …

  luabind::register_exception_handler<my_exception>(&translate_my_exception);

``translate_my_exception()`` will be called by luabind whenever a
``my_exception`` is caught. ``lua_error()`` will be called after the
handler function returns, so it is expected that the function will push
an error string on the stack.

Any function that invokes Lua code may throw ``luabind::error``. This exception
means that a Lua run-time error occurred. The error message is found on top of
the Lua stack. The reason why the exception doesn't contain the error string
itself is because it would then require heap allocation which may fail. If an
exception class throws an exception while it is being thrown itself, the
application will be terminated.

Error's synopsis is::

    class error : public std::exception
    {
    public:
        error(lua_State*);
        lua_State* state() const throw();
        virtual const char* what() const throw();
    };

The state function returns a pointer to the Lua state in which the error was
thrown. This pointer may be invalid if you catch this exception after the lua
state is destructed. If the Lua state is valid you can use it to retrieve the
error message from the top of the Lua stack.

An example of where the Lua state pointer may point to an invalid state
follows::

    struct lua_state
    {
        lua_state(lua_State* L): m_L(L) {}
        ~lua_state() { lua_close(m_L); }
        operator lua_State*() { return m_L; }
        lua_State* m_L;
    };

    int main()
    {
        try
        {
            lua_state L = luaL_newstate();
            /* ... */
        }
        catch(luabind::error& e)
        {
            lua_State* L = e.state();
            // L will now point to the destructed
            // Lua state and be invalid
            /* ... */
        }
    }

There's another exception that luabind may throw: ``luabind::cast_failed``,
this exception is thrown from ``call_function<>`` or ``call_member<>``. It
means that the return value from the Lua function couldn't be converted to
a C++ value. It is also thrown from ``object_cast<>`` if the cast cannot
be made.

The synopsis for ``luabind::cast_failed`` is::

    class cast_failed : public std::exception
    {
    public:
        cast_failed(lua_State*);
        lua_State* state() const throw();
        LUABIND_TYPE_INFO info() const throw();
        virtual const char* what() const throw();
    };

Again, the state member function returns a pointer to the Lua state where the
error occurred. See the example above to see where this pointer may be invalid.

The info member function returns the user defined ``LUABIND_TYPE_INFO``, which
defaults to a ``const std::type_info*``. This type info describes the type that
we tried to cast a Lua value to.

If you have defined ``LUABIND_NO_EXCEPTIONS`` none of these exceptions will be
thrown, instead you can set two callback functions that are called instead.
These two functions are only defined if ``LUABIND_NO_EXCEPTIONS`` are defined.

::

    luabind::set_error_callback(void(*)(lua_State*))

The function you set will be called when a runtime-error occur in Lua code. You
can find an error message on top of the Lua stack. This function is not
expected to return, if it does luabind will call ``std::terminate()``.

::

    luabind::set_cast_failed_callback(void(*)(lua_State*, LUABIND_TYPE_INFO))

The function you set is called instead of throwing ``cast_failed``. This function
is not expected to return, if it does luabind will call ``std::terminate()``.