Adding converters for user defined types
========================================

It is possible to get luabind to handle user defined types like it does
the built in types by specializing ``luabind::default_converter<>``:

::

  struct int_wrapper
  {
      int_wrapper(int value)
        : value(value)
      {}

      int value;
  };

  namespace luabind
  {
      template <>
      struct default_converter<X>
        : native_converter_base<X>
      {
          static int compute_score(lua_State* L, int index)
          {
              return lua_type(L, index) == LUA_TNUMBER ? 0 : -1;
          }

          X from(lua_State* L, int index)
          {
              return X(lua_tonumber(L, index));
          }

          void to(lua_State* L, X const& x)
          {
              lua_pushnumber(L, x.value);
          }
      };

      template <>
      struct default_converter<X const&>
        : default_converter<X>
      {};
  }

Note that ``default_converter<>`` is instantiated for the actual argument and
return types of the bound functions. In the above example, we add a
specialization for ``X const&`` that simply forwards to the ``X`` converter.
This lets us export functions which accept ``X`` by const reference.

``native_converter_base<>`` should be used as the base class for the
specialized converters. It simplifies the converter interface, and
provides a mean for backward compatibility since the underlying
interface is in flux.