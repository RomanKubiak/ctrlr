#ifndef STDAFX_LUA_H
#define STDAFX_LUA_H

#ifdef __cplusplus
#ifndef __OBJC__
#define LUABIND_BUILDING
#undef LUABIND_CPP0x

extern "C"
{
	#include <luabind/lua.h>
	#include <luabind/lualib.h>
	#include <luabind/lauxlib.h>
}

#include <boost/foreach.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/version.hpp>

#ifdef check
#undef check
#endif

#ifdef nil
#undef nil
#endif

#include <luabind/config.hpp>
#include <luabind/class.hpp>
#include <luabind/function.hpp>
#include <luabind/open.hpp>

#define check
#define nil

#include <luabind/lua_include.hpp>
#include <luabind/nil.hpp>
#include <luabind/lua_include.hpp>
#include <luabind/luabind.hpp>
#include <luabind/class_info.hpp>
#include <luabind/detail/class_registry.hpp>
#include <luabind/detail/class_rep.hpp>
#include <luabind/detail/operator_id.hpp>
#include <luabind/detail/stack_utils.hpp>
#include <luabind/detail/conversion_storage.hpp>
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
#include <luabind/lua.hpp>

#endif // !__OBJC__
#endif // __cplusplus
#endif // guard
