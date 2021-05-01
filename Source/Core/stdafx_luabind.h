#ifndef __STDAFX_LUABIND_H__
#define __STDAFX_LUABIND_H__

#ifdef __cplusplus
#ifndef __OBJC__

#undef nil
#include <string>

extern "C"
{
#include "lua.h"
};

#pragma warning(disable:4913)
#pragma warning(disable:4459)
#pragma warning(disable:4297)

#define  LUABIND_USE_CXX11

#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>
#include <luabind/adopt_policy.hpp>
#include <luabind/version.hpp>

#if 0
#include <luabind/config.hpp>
#include <luabind/class.hpp>
#include <luabind/function.hpp>
#include <luabind/open.hpp>
#include <luabind/lua_include.hpp>
#include <luabind/nil.hpp>
#include <luabind/lua_include.hpp>
#include <luabind/luabind.hpp>
#include <luabind/class_info.hpp>
#include <luabind/detail/class_registry.hpp>
#include <luabind/detail/class_rep.hpp>
#include <luabind/detail/operator_id.hpp>
#include <luabind/detail/stack_utils.hpp>
#include <luabind/exception_handler.hpp>
#include <luabind/get_main_thread.hpp>
#include <luabind/error.hpp>
#include <luabind/config.hpp>
#include <luabind/make_function.hpp>
#include <luabind/typeid.hpp>
#include <luabind/detail/inheritance.hpp>
#include <luabind/detail/link_compatibility.hpp>
#include <luabind/detail/object_rep.hpp>
#include <luabind/detail/pcall.hpp>
#include <luabind/scope.hpp>
#include <luabind/detail/debug.hpp>
#include <luabind/weak_ref.hpp>
#include <luabind/operator.hpp>
#include <luabind/copy_policy.hpp>
#include <luabind/return_reference_to_policy.hpp>
#include <luabind/adopt_policy.hpp>
#include <luabind/out_value_policy.hpp>
#include <luabind/discard_result_policy.hpp>
#include <luabind/version.hpp>
#include <luabind/shared_ptr_converter.hpp>
#endif
#include "JuceHeader.h"
static const std::string obj_name(const luabind::object& o)
{
	lua_State* L = o.interpreter();
	std::string name;

	o.push(L);
	luabind::detail::object_rep* obj = luabind::detail::get_instance(L, -1);
	if (!obj)
	{
		name = lua_typename(L, lua_type(L, -1));
		lua_pop(L, 1);
		return name;
	}

	lua_pop(L, 1);
	name = obj->crep()->name();
	return name;
}

static const var toVar(lua_State* L, int index)
{
	var v;
	luabind::object obj(luabind::from_stack(L, index));

	switch (luabind::type(obj))
	{
	case LUA_TSTRING:
		v = luabind::object_cast<String>(obj);
		return v;

	case LUA_TNUMBER:
		v = luabind::object_cast<double>(obj);
		return v;
	}

	return v;
}

static void fromVar (lua_State* L, var const& v)
{
	if (v.isString())
	{
		lua_pushstring(L, v.toString().toUTF8());
		return;
	}
	else if (v.isInt())
	{
		lua_pushnumber(L, (int)v);
		return;
	}
	else if (v.isDouble())
	{
		lua_pushnumber(L, (double)v);
		return;
	}
	lua_pushnil(L);
}

namespace luabind
{
	/* var converter */
	template <> struct default_converter<var> : native_converter_base<var>
	{
		static int compute_score(lua_State* L, int index)
		{
			lua_type(L, index);
			return 0;
		}

		var from(lua_State* L, int index)
		{
			return toVar(L, index);
		}

		void to(lua_State* L, var const& v)
		{
			fromVar (L, v);
		}
	};

	template <> struct default_converter<var const&> : default_converter<var>
	{};

	/* String converter */
	template <> struct default_converter<String> : native_converter_base<String>
	{
		static int compute_score(lua_State* L, int index)
		{
			object obj(luabind::from_stack(L, index));
			std::string name = obj_name(obj);

			if (name == "String")
			{
				return (0);
			}
			return (lua_type(L, index) == LUA_TSTRING) ? 0 : -1;
		}

		String from(lua_State* L, int index)
		{
			object obj(luabind::from_stack(L, index));
			std::string name = obj_name(obj);

			if (name == "String")
			{
				String* wp = object_cast<String*>(obj);
				return String(*wp);
			}
			return String(CharPointer_UTF8 (lua_tostring(L, index)));
		}

		void to(lua_State* L, String const &value)
		{
			lua_pushlstring(L, value.toUTF8(), value.length());
		}
	};

	template <> struct default_converter<String const&> : default_converter<String>
	{
	};

	/* StringRef converter */
	template <> struct default_converter<StringRef> : native_converter_base<StringRef>
	{
		static int compute_score(lua_State* L, int index)
		{
			object obj(luabind::from_stack(L, index));
			std::string name = obj_name(obj);

			if (name == "StringRef")
			{
				return (0);
			}
			return (lua_type(L, index) == LUA_TSTRING) ? 0 : -1;
		}

		StringRef from(lua_State* L, int index)
		{
			object obj(luabind::from_stack(L, index));
			std::string name = obj_name(obj);

			if (name == "StringRef")
			{
				StringRef* wp = object_cast<StringRef*>(obj);
				return StringRef(*wp);
			}
			return StringRef(lua_tostring(L, index));
		}

		void to(lua_State* L, StringRef const &value)
		{
			lua_pushlstring(L, value, value.length());
		}
	};

	template <> struct default_converter<StringRef const&> : default_converter<StringRef>
	{
	};

	/* Identifier converter */
	template <> struct default_converter<Identifier> : native_converter_base<Identifier>
	{
		static int compute_score(lua_State* L, int index)
		{
			object obj(luabind::from_stack(L, index));
			std::string name = obj_name(obj);

			if (name == "Identifier")
			{
				return (0);
			}
			return (lua_type(L, index) == LUA_TSTRING) ? 0 : -1;
		}

		Identifier from(lua_State* L, int index)
		{
			object obj(luabind::from_stack(L, index));
			std::string name = obj_name(obj);

			if (name == "Identifier")
			{
				Identifier* wp = object_cast<Identifier*>(obj);
				return Identifier(*wp);
			}
			return Identifier(lua_tostring(L, index));
		}

		void to(lua_State* L, Identifier const &value)
		{
			lua_pushlstring(L, value.toString().toUTF8(), strlen(value.toString().toUTF8()));
		}
	};

	template <> struct default_converter<Identifier const&> : default_converter<Identifier>
	{
	};
}

#endif
#endif
#endif
