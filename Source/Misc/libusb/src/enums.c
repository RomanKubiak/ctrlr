/* this is a generated file, see gen.lua */
#include "Misc/libusb/include/enums.h"

#include "lua.h"
#include "lauxlib.h"
#include "Misc/libusb/include/libusb.h"
#include "Misc/libusb/include/compat.h"

enum libusb_class_code luausb_to_class_code(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, index);
	case LUA_TSTRING:
		{
			enum libusb_class_code result;
			lua_getfield(L, lua_upvalueindex(1), "class_code");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

int luausb_is_class_code(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return 1;
	case LUA_TSTRING:
		{
			int result;
			lua_getfield(L, lua_upvalueindex(1), "class_code");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = 1;
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

enum libusb_class_code luausb_check_class_code(lua_State* L, int narg)
{
	switch (lua_type(L, narg))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, narg);
	case LUA_TSTRING:
		{
			enum libusb_class_code result;
			lua_getfield(L, lua_upvalueindex(1), "class_code");
			lua_pushvalue(L, narg);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
			{
				typeerror(L, narg, "enum libusb_class_code");
				return 0;
			}
			lua_pop(L, 2);
			return result;
		}
	default:
		typeerror(L, narg, "enum libusb_class_code");
		return 0;
	}
}

enum libusb_class_code luausb_opt_class_code(lua_State* L, int narg, enum libusb_class_code d)
{
	if (lua_isnoneornil(L, narg))
		return d;
	else
		return luausb_check_class_code(L, narg);
}

enum libusb_descriptor_type luausb_to_descriptor_type(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, index);
	case LUA_TSTRING:
		{
			enum libusb_descriptor_type result;
			lua_getfield(L, lua_upvalueindex(1), "descriptor_type");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

int luausb_is_descriptor_type(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return 1;
	case LUA_TSTRING:
		{
			int result;
			lua_getfield(L, lua_upvalueindex(1), "descriptor_type");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = 1;
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

enum libusb_descriptor_type luausb_check_descriptor_type(lua_State* L, int narg)
{
	switch (lua_type(L, narg))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, narg);
	case LUA_TSTRING:
		{
			enum libusb_descriptor_type result;
			lua_getfield(L, lua_upvalueindex(1), "descriptor_type");
			lua_pushvalue(L, narg);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
			{
				typeerror(L, narg, "enum libusb_descriptor_type");
				return 0;
			}
			lua_pop(L, 2);
			return result;
		}
	default:
		typeerror(L, narg, "enum libusb_descriptor_type");
		return 0;
	}
}

enum libusb_descriptor_type luausb_opt_descriptor_type(lua_State* L, int narg, enum libusb_descriptor_type d)
{
	if (lua_isnoneornil(L, narg))
		return d;
	else
		return luausb_check_descriptor_type(L, narg);
}

enum libusb_endpoint_direction luausb_to_endpoint_direction(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, index);
	case LUA_TSTRING:
		{
			enum libusb_endpoint_direction result;
			lua_getfield(L, lua_upvalueindex(1), "endpoint_direction");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

int luausb_is_endpoint_direction(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return 1;
	case LUA_TSTRING:
		{
			int result;
			lua_getfield(L, lua_upvalueindex(1), "endpoint_direction");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = 1;
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

enum libusb_endpoint_direction luausb_check_endpoint_direction(lua_State* L, int narg)
{
	switch (lua_type(L, narg))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, narg);
	case LUA_TSTRING:
		{
			enum libusb_endpoint_direction result;
			lua_getfield(L, lua_upvalueindex(1), "endpoint_direction");
			lua_pushvalue(L, narg);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
			{
				typeerror(L, narg, "enum libusb_endpoint_direction");
				return 0;
			}
			lua_pop(L, 2);
			return result;
		}
	default:
		typeerror(L, narg, "enum libusb_endpoint_direction");
		return 0;
	}
}

enum libusb_endpoint_direction luausb_opt_endpoint_direction(lua_State* L, int narg, enum libusb_endpoint_direction d)
{
	if (lua_isnoneornil(L, narg))
		return d;
	else
		return luausb_check_endpoint_direction(L, narg);
}

enum libusb_transfer_type luausb_to_transfer_type(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, index);
	case LUA_TSTRING:
		{
			enum libusb_transfer_type result;
			lua_getfield(L, lua_upvalueindex(1), "transfer_type");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

int luausb_is_transfer_type(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return 1;
	case LUA_TSTRING:
		{
			int result;
			lua_getfield(L, lua_upvalueindex(1), "transfer_type");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = 1;
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

enum libusb_transfer_type luausb_check_transfer_type(lua_State* L, int narg)
{
	switch (lua_type(L, narg))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, narg);
	case LUA_TSTRING:
		{
			enum libusb_transfer_type result;
			lua_getfield(L, lua_upvalueindex(1), "transfer_type");
			lua_pushvalue(L, narg);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
			{
				typeerror(L, narg, "enum libusb_transfer_type");
				return 0;
			}
			lua_pop(L, 2);
			return result;
		}
	default:
		typeerror(L, narg, "enum libusb_transfer_type");
		return 0;
	}
}

enum libusb_transfer_type luausb_opt_transfer_type(lua_State* L, int narg, enum libusb_transfer_type d)
{
	if (lua_isnoneornil(L, narg))
		return d;
	else
		return luausb_check_transfer_type(L, narg);
}

enum libusb_iso_sync_type luausb_to_iso_sync_type(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, index);
	case LUA_TSTRING:
		{
			enum libusb_iso_sync_type result;
			lua_getfield(L, lua_upvalueindex(1), "iso_sync_type");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

int luausb_is_iso_sync_type(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return 1;
	case LUA_TSTRING:
		{
			int result;
			lua_getfield(L, lua_upvalueindex(1), "iso_sync_type");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = 1;
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

enum libusb_iso_sync_type luausb_check_iso_sync_type(lua_State* L, int narg)
{
	switch (lua_type(L, narg))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, narg);
	case LUA_TSTRING:
		{
			enum libusb_iso_sync_type result;
			lua_getfield(L, lua_upvalueindex(1), "iso_sync_type");
			lua_pushvalue(L, narg);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
			{
				typeerror(L, narg, "enum libusb_iso_sync_type");
				return 0;
			}
			lua_pop(L, 2);
			return result;
		}
	default:
		typeerror(L, narg, "enum libusb_iso_sync_type");
		return 0;
	}
}

enum libusb_iso_sync_type luausb_opt_iso_sync_type(lua_State* L, int narg, enum libusb_iso_sync_type d)
{
	if (lua_isnoneornil(L, narg))
		return d;
	else
		return luausb_check_iso_sync_type(L, narg);
}

enum libusb_iso_usage_type luausb_to_iso_usage_type(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, index);
	case LUA_TSTRING:
		{
			enum libusb_iso_usage_type result;
			lua_getfield(L, lua_upvalueindex(1), "iso_usage_type");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

int luausb_is_iso_usage_type(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return 1;
	case LUA_TSTRING:
		{
			int result;
			lua_getfield(L, lua_upvalueindex(1), "iso_usage_type");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = 1;
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

enum libusb_iso_usage_type luausb_check_iso_usage_type(lua_State* L, int narg)
{
	switch (lua_type(L, narg))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, narg);
	case LUA_TSTRING:
		{
			enum libusb_iso_usage_type result;
			lua_getfield(L, lua_upvalueindex(1), "iso_usage_type");
			lua_pushvalue(L, narg);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
			{
				typeerror(L, narg, "enum libusb_iso_usage_type");
				return 0;
			}
			lua_pop(L, 2);
			return result;
		}
	default:
		typeerror(L, narg, "enum libusb_iso_usage_type");
		return 0;
	}
}

enum libusb_iso_usage_type luausb_opt_iso_usage_type(lua_State* L, int narg, enum libusb_iso_usage_type d)
{
	if (lua_isnoneornil(L, narg))
		return d;
	else
		return luausb_check_iso_usage_type(L, narg);
}

enum libusb_standard_request luausb_to_standard_request(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, index);
	case LUA_TSTRING:
		{
			enum libusb_standard_request result;
			lua_getfield(L, lua_upvalueindex(1), "standard_request");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

int luausb_is_standard_request(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return 1;
	case LUA_TSTRING:
		{
			int result;
			lua_getfield(L, lua_upvalueindex(1), "standard_request");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = 1;
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

enum libusb_standard_request luausb_check_standard_request(lua_State* L, int narg)
{
	switch (lua_type(L, narg))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, narg);
	case LUA_TSTRING:
		{
			enum libusb_standard_request result;
			lua_getfield(L, lua_upvalueindex(1), "standard_request");
			lua_pushvalue(L, narg);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
			{
				typeerror(L, narg, "enum libusb_standard_request");
				return 0;
			}
			lua_pop(L, 2);
			return result;
		}
	default:
		typeerror(L, narg, "enum libusb_standard_request");
		return 0;
	}
}

enum libusb_standard_request luausb_opt_standard_request(lua_State* L, int narg, enum libusb_standard_request d)
{
	if (lua_isnoneornil(L, narg))
		return d;
	else
		return luausb_check_standard_request(L, narg);
}

enum libusb_request_type luausb_to_request_type(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, index);
	case LUA_TSTRING:
		{
			enum libusb_request_type result;
			lua_getfield(L, lua_upvalueindex(1), "request_type");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

int luausb_is_request_type(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return 1;
	case LUA_TSTRING:
		{
			int result;
			lua_getfield(L, lua_upvalueindex(1), "request_type");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = 1;
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

enum libusb_request_type luausb_check_request_type(lua_State* L, int narg)
{
	switch (lua_type(L, narg))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, narg);
	case LUA_TSTRING:
		{
			enum libusb_request_type result;
			lua_getfield(L, lua_upvalueindex(1), "request_type");
			lua_pushvalue(L, narg);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
			{
				typeerror(L, narg, "enum libusb_request_type");
				return 0;
			}
			lua_pop(L, 2);
			return result;
		}
	default:
		typeerror(L, narg, "enum libusb_request_type");
		return 0;
	}
}

enum libusb_request_type luausb_opt_request_type(lua_State* L, int narg, enum libusb_request_type d)
{
	if (lua_isnoneornil(L, narg))
		return d;
	else
		return luausb_check_request_type(L, narg);
}

enum libusb_request_recipient luausb_to_request_recipient(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, index);
	case LUA_TSTRING:
		{
			enum libusb_request_recipient result;
			lua_getfield(L, lua_upvalueindex(1), "request_recipient");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

int luausb_is_request_recipient(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return 1;
	case LUA_TSTRING:
		{
			int result;
			lua_getfield(L, lua_upvalueindex(1), "request_recipient");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = 1;
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

enum libusb_request_recipient luausb_check_request_recipient(lua_State* L, int narg)
{
	switch (lua_type(L, narg))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, narg);
	case LUA_TSTRING:
		{
			enum libusb_request_recipient result;
			lua_getfield(L, lua_upvalueindex(1), "request_recipient");
			lua_pushvalue(L, narg);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
			{
				typeerror(L, narg, "enum libusb_request_recipient");
				return 0;
			}
			lua_pop(L, 2);
			return result;
		}
	default:
		typeerror(L, narg, "enum libusb_request_recipient");
		return 0;
	}
}

enum libusb_request_recipient luausb_opt_request_recipient(lua_State* L, int narg, enum libusb_request_recipient d)
{
	if (lua_isnoneornil(L, narg))
		return d;
	else
		return luausb_check_request_recipient(L, narg);
}

enum libusb_error luausb_to_error(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, index);
	case LUA_TSTRING:
		{
			enum libusb_error result;
			lua_getfield(L, lua_upvalueindex(1), "error");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

int luausb_is_error(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return 1;
	case LUA_TSTRING:
		{
			int result;
			lua_getfield(L, lua_upvalueindex(1), "error");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = 1;
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

enum libusb_error luausb_check_error(lua_State* L, int narg)
{
	switch (lua_type(L, narg))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, narg);
	case LUA_TSTRING:
		{
			enum libusb_error result;
			lua_getfield(L, lua_upvalueindex(1), "error");
			lua_pushvalue(L, narg);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
			{
				typeerror(L, narg, "enum libusb_error");
				return 0;
			}
			lua_pop(L, 2);
			return result;
		}
	default:
		typeerror(L, narg, "enum libusb_error");
		return 0;
	}
}

enum libusb_error luausb_opt_error(lua_State* L, int narg, enum libusb_error d)
{
	if (lua_isnoneornil(L, narg))
		return d;
	else
		return luausb_check_error(L, narg);
}

enum libusb_transfer_status luausb_to_transfer_status(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, index);
	case LUA_TSTRING:
		{
			enum libusb_transfer_status result;
			lua_getfield(L, lua_upvalueindex(1), "transfer_status");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

int luausb_is_transfer_status(lua_State* L, int index)
{
	switch (lua_type(L, index))
	{
	case LUA_TNUMBER:
		return 1;
	case LUA_TSTRING:
		{
			int result;
			lua_getfield(L, lua_upvalueindex(1), "transfer_status");
			lua_pushvalue(L, index);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = 1;
			else
				result = 0;
			lua_pop(L, 2);
			return result;
		}
	default:
		return 0;
	}
}

enum libusb_transfer_status luausb_check_transfer_status(lua_State* L, int narg)
{
	switch (lua_type(L, narg))
	{
	case LUA_TNUMBER:
		return lua_tonumber(L, narg);
	case LUA_TSTRING:
		{
			enum libusb_transfer_status result;
			lua_getfield(L, lua_upvalueindex(1), "transfer_status");
			lua_pushvalue(L, narg);
			lua_gettable(L, -2);
			if (lua_type(L, -1)==LUA_TNUMBER)
				result = lua_tonumber(L, -1);
			else
			{
				typeerror(L, narg, "enum libusb_transfer_status");
				return 0;
			}
			lua_pop(L, 2);
			return result;
		}
	default:
		typeerror(L, narg, "enum libusb_transfer_status");
		return 0;
	}
}

enum libusb_transfer_status luausb_opt_transfer_status(lua_State* L, int narg, enum libusb_transfer_status d)
{
	if (lua_isnoneornil(L, narg))
		return d;
	else
		return luausb_check_transfer_status(L, narg);
}

void luausb_init_enums(lua_State* L)
{
	/* ..., env */
	lua_pushnumber(L, LIBUSB_CLASS_WIRELESS); lua_setfield(L, -2, "CLASS_WIRELESS");
	lua_pushnumber(L, LIBUSB_CLASS_DATA); lua_setfield(L, -2, "CLASS_DATA");
	lua_pushnumber(L, LIBUSB_CLASS_PER_INTERFACE); lua_setfield(L, -2, "CLASS_PER_INTERFACE");
	lua_pushnumber(L, LIBUSB_CLASS_HUB); lua_setfield(L, -2, "CLASS_HUB");
	lua_pushnumber(L, LIBUSB_CLASS_VENDOR_SPEC); lua_setfield(L, -2, "CLASS_VENDOR_SPEC");
	lua_pushnumber(L, LIBUSB_CLASS_PRINTER); lua_setfield(L, -2, "CLASS_PRINTER");
	lua_pushnumber(L, LIBUSB_CLASS_PTP); lua_setfield(L, -2, "CLASS_PTP");
	lua_pushnumber(L, LIBUSB_CLASS_APPLICATION); lua_setfield(L, -2, "CLASS_APPLICATION");
	lua_pushnumber(L, LIBUSB_CLASS_MASS_STORAGE); lua_setfield(L, -2, "CLASS_MASS_STORAGE");
	lua_pushnumber(L, LIBUSB_CLASS_HID); lua_setfield(L, -2, "CLASS_HID");
	lua_pushnumber(L, LIBUSB_CLASS_COMM); lua_setfield(L, -2, "CLASS_COMM");
	lua_pushnumber(L, LIBUSB_CLASS_AUDIO); lua_setfield(L, -2, "CLASS_AUDIO");
	lua_pushnumber(L, LIBUSB_DT_DEVICE); lua_setfield(L, -2, "DT_DEVICE");
	lua_pushnumber(L, LIBUSB_DT_HUB); lua_setfield(L, -2, "DT_HUB");
	lua_pushnumber(L, LIBUSB_DT_REPORT); lua_setfield(L, -2, "DT_REPORT");
	lua_pushnumber(L, LIBUSB_DT_HID); lua_setfield(L, -2, "DT_HID");
	lua_pushnumber(L, LIBUSB_DT_STRING); lua_setfield(L, -2, "DT_STRING");
	lua_pushnumber(L, LIBUSB_DT_CONFIG); lua_setfield(L, -2, "DT_CONFIG");
	lua_pushnumber(L, LIBUSB_DT_INTERFACE); lua_setfield(L, -2, "DT_INTERFACE");
	lua_pushnumber(L, LIBUSB_DT_PHYSICAL); lua_setfield(L, -2, "DT_PHYSICAL");
	lua_pushnumber(L, LIBUSB_DT_ENDPOINT); lua_setfield(L, -2, "DT_ENDPOINT");
	lua_pushnumber(L, LIBUSB_ENDPOINT_OUT); lua_setfield(L, -2, "ENDPOINT_OUT");
	lua_pushnumber(L, LIBUSB_ENDPOINT_IN); lua_setfield(L, -2, "ENDPOINT_IN");
	lua_pushnumber(L, LIBUSB_TRANSFER_TYPE_INTERRUPT); lua_setfield(L, -2, "TRANSFER_TYPE_INTERRUPT");
	lua_pushnumber(L, LIBUSB_TRANSFER_TYPE_BULK); lua_setfield(L, -2, "TRANSFER_TYPE_BULK");
	lua_pushnumber(L, LIBUSB_TRANSFER_TYPE_CONTROL); lua_setfield(L, -2, "TRANSFER_TYPE_CONTROL");
	lua_pushnumber(L, LIBUSB_TRANSFER_TYPE_ISOCHRONOUS); lua_setfield(L, -2, "TRANSFER_TYPE_ISOCHRONOUS");
	lua_pushnumber(L, LIBUSB_ISO_SYNC_TYPE_ASYNC); lua_setfield(L, -2, "ISO_SYNC_TYPE_ASYNC");
	lua_pushnumber(L, LIBUSB_ISO_SYNC_TYPE_ADAPTIVE); lua_setfield(L, -2, "ISO_SYNC_TYPE_ADAPTIVE");
	lua_pushnumber(L, LIBUSB_ISO_SYNC_TYPE_NONE); lua_setfield(L, -2, "ISO_SYNC_TYPE_NONE");
	lua_pushnumber(L, LIBUSB_ISO_SYNC_TYPE_SYNC); lua_setfield(L, -2, "ISO_SYNC_TYPE_SYNC");
	lua_pushnumber(L, LIBUSB_ISO_USAGE_TYPE_IMPLICIT); lua_setfield(L, -2, "ISO_USAGE_TYPE_IMPLICIT");
	lua_pushnumber(L, LIBUSB_ISO_USAGE_TYPE_DATA); lua_setfield(L, -2, "ISO_USAGE_TYPE_DATA");
	lua_pushnumber(L, LIBUSB_ISO_USAGE_TYPE_FEEDBACK); lua_setfield(L, -2, "ISO_USAGE_TYPE_FEEDBACK");
	lua_pushnumber(L, LIBUSB_REQUEST_GET_CONFIGURATION); lua_setfield(L, -2, "REQUEST_GET_CONFIGURATION");
	lua_pushnumber(L, LIBUSB_REQUEST_SET_ADDRESS); lua_setfield(L, -2, "REQUEST_SET_ADDRESS");
	lua_pushnumber(L, LIBUSB_REQUEST_SET_FEATURE); lua_setfield(L, -2, "REQUEST_SET_FEATURE");
	lua_pushnumber(L, LIBUSB_REQUEST_SYNCH_FRAME); lua_setfield(L, -2, "REQUEST_SYNCH_FRAME");
	lua_pushnumber(L, LIBUSB_REQUEST_SET_CONFIGURATION); lua_setfield(L, -2, "REQUEST_SET_CONFIGURATION");
	lua_pushnumber(L, LIBUSB_REQUEST_GET_STATUS); lua_setfield(L, -2, "REQUEST_GET_STATUS");
	lua_pushnumber(L, LIBUSB_REQUEST_SET_INTERFACE); lua_setfield(L, -2, "REQUEST_SET_INTERFACE");
	lua_pushnumber(L, LIBUSB_REQUEST_CLEAR_FEATURE); lua_setfield(L, -2, "REQUEST_CLEAR_FEATURE");
	lua_pushnumber(L, LIBUSB_REQUEST_GET_INTERFACE); lua_setfield(L, -2, "REQUEST_GET_INTERFACE");
	lua_pushnumber(L, LIBUSB_REQUEST_SET_DESCRIPTOR); lua_setfield(L, -2, "REQUEST_SET_DESCRIPTOR");
	lua_pushnumber(L, LIBUSB_REQUEST_GET_DESCRIPTOR); lua_setfield(L, -2, "REQUEST_GET_DESCRIPTOR");
	lua_pushnumber(L, LIBUSB_REQUEST_TYPE_CLASS); lua_setfield(L, -2, "REQUEST_TYPE_CLASS");
	lua_pushnumber(L, LIBUSB_REQUEST_TYPE_RESERVED); lua_setfield(L, -2, "REQUEST_TYPE_RESERVED");
	lua_pushnumber(L, LIBUSB_REQUEST_TYPE_VENDOR); lua_setfield(L, -2, "REQUEST_TYPE_VENDOR");
	lua_pushnumber(L, LIBUSB_REQUEST_TYPE_STANDARD); lua_setfield(L, -2, "REQUEST_TYPE_STANDARD");
	lua_pushnumber(L, LIBUSB_RECIPIENT_DEVICE); lua_setfield(L, -2, "RECIPIENT_DEVICE");
	lua_pushnumber(L, LIBUSB_RECIPIENT_INTERFACE); lua_setfield(L, -2, "RECIPIENT_INTERFACE");
	lua_pushnumber(L, LIBUSB_RECIPIENT_OTHER); lua_setfield(L, -2, "RECIPIENT_OTHER");
	lua_pushnumber(L, LIBUSB_RECIPIENT_ENDPOINT); lua_setfield(L, -2, "RECIPIENT_ENDPOINT");
	lua_pushnumber(L, LIBUSB_ERROR_OVERFLOW); lua_setfield(L, -2, "ERROR_OVERFLOW");
	lua_pushnumber(L, LIBUSB_ERROR_TIMEOUT); lua_setfield(L, -2, "ERROR_TIMEOUT");
	lua_pushnumber(L, LIBUSB_ERROR_ACCESS); lua_setfield(L, -2, "ERROR_ACCESS");
	lua_pushnumber(L, LIBUSB_ERROR_OTHER); lua_setfield(L, -2, "ERROR_OTHER");
	lua_pushnumber(L, LIBUSB_ERROR_NOT_SUPPORTED); lua_setfield(L, -2, "ERROR_NOT_SUPPORTED");
	lua_pushnumber(L, LIBUSB_ERROR_BUSY); lua_setfield(L, -2, "ERROR_BUSY");
	lua_pushnumber(L, LIBUSB_ERROR_NO_MEM); lua_setfield(L, -2, "ERROR_NO_MEM");
	lua_pushnumber(L, LIBUSB_ERROR_NO_DEVICE); lua_setfield(L, -2, "ERROR_NO_DEVICE");
	lua_pushnumber(L, LIBUSB_ERROR_NOT_FOUND); lua_setfield(L, -2, "ERROR_NOT_FOUND");
	lua_pushnumber(L, LIBUSB_ERROR_PIPE); lua_setfield(L, -2, "ERROR_PIPE");
	lua_pushnumber(L, LIBUSB_ERROR_INVALID_PARAM); lua_setfield(L, -2, "ERROR_INVALID_PARAM");
	lua_pushnumber(L, LIBUSB_ERROR_IO); lua_setfield(L, -2, "ERROR_IO");
	lua_pushnumber(L, LIBUSB_ERROR_INTERRUPTED); lua_setfield(L, -2, "ERROR_INTERRUPTED");
	lua_pushnumber(L, LIBUSB_TRANSFER_ERROR); lua_setfield(L, -2, "TRANSFER_ERROR");
	lua_pushnumber(L, LIBUSB_TRANSFER_OVERFLOW); lua_setfield(L, -2, "TRANSFER_OVERFLOW");
	lua_pushnumber(L, LIBUSB_TRANSFER_TIMED_OUT); lua_setfield(L, -2, "TRANSFER_TIMED_OUT");
	lua_pushnumber(L, LIBUSB_TRANSFER_CANCELLED); lua_setfield(L, -2, "TRANSFER_CANCELLED");
	lua_pushnumber(L, LIBUSB_TRANSFER_NO_DEVICE); lua_setfield(L, -2, "TRANSFER_NO_DEVICE");
	lua_pushnumber(L, LIBUSB_TRANSFER_COMPLETED); lua_setfield(L, -2, "TRANSFER_COMPLETED");
	lua_pushnumber(L, LIBUSB_TRANSFER_STALL); lua_setfield(L, -2, "TRANSFER_STALL");
	lua_newtable(L); /* ..., env, t */
	lua_pushnumber(L, LIBUSB_CLASS_WIRELESS); lua_setfield(L, -2, "LIBUSB_CLASS_WIRELESS");
	lua_pushnumber(L, LIBUSB_CLASS_WIRELESS); lua_setfield(L, -2, "wireless");
	lua_pushnumber(L, LIBUSB_CLASS_DATA); lua_setfield(L, -2, "LIBUSB_CLASS_DATA");
	lua_pushnumber(L, LIBUSB_CLASS_DATA); lua_setfield(L, -2, "data");
	lua_pushnumber(L, LIBUSB_CLASS_PER_INTERFACE); lua_setfield(L, -2, "LIBUSB_CLASS_PER_INTERFACE");
	lua_pushnumber(L, LIBUSB_CLASS_PER_INTERFACE); lua_setfield(L, -2, "per_interface");
	lua_pushnumber(L, LIBUSB_CLASS_HUB); lua_setfield(L, -2, "LIBUSB_CLASS_HUB");
	lua_pushnumber(L, LIBUSB_CLASS_HUB); lua_setfield(L, -2, "hub");
	lua_pushnumber(L, LIBUSB_CLASS_VENDOR_SPEC); lua_setfield(L, -2, "LIBUSB_CLASS_VENDOR_SPEC");
	lua_pushnumber(L, LIBUSB_CLASS_VENDOR_SPEC); lua_setfield(L, -2, "vendor_spec");
	lua_pushnumber(L, LIBUSB_CLASS_PRINTER); lua_setfield(L, -2, "LIBUSB_CLASS_PRINTER");
	lua_pushnumber(L, LIBUSB_CLASS_PRINTER); lua_setfield(L, -2, "printer");
	lua_pushnumber(L, LIBUSB_CLASS_PTP); lua_setfield(L, -2, "LIBUSB_CLASS_PTP");
	lua_pushnumber(L, LIBUSB_CLASS_PTP); lua_setfield(L, -2, "ptp");
	lua_pushnumber(L, LIBUSB_CLASS_APPLICATION); lua_setfield(L, -2, "LIBUSB_CLASS_APPLICATION");
	lua_pushnumber(L, LIBUSB_CLASS_APPLICATION); lua_setfield(L, -2, "application");
	lua_pushnumber(L, LIBUSB_CLASS_MASS_STORAGE); lua_setfield(L, -2, "LIBUSB_CLASS_MASS_STORAGE");
	lua_pushnumber(L, LIBUSB_CLASS_MASS_STORAGE); lua_setfield(L, -2, "mass_storage");
	lua_pushnumber(L, LIBUSB_CLASS_HID); lua_setfield(L, -2, "LIBUSB_CLASS_HID");
	lua_pushnumber(L, LIBUSB_CLASS_HID); lua_setfield(L, -2, "hid");
	lua_pushnumber(L, LIBUSB_CLASS_COMM); lua_setfield(L, -2, "LIBUSB_CLASS_COMM");
	lua_pushnumber(L, LIBUSB_CLASS_COMM); lua_setfield(L, -2, "comm");
	lua_pushnumber(L, LIBUSB_CLASS_AUDIO); lua_setfield(L, -2, "LIBUSB_CLASS_AUDIO");
	lua_pushnumber(L, LIBUSB_CLASS_AUDIO); lua_setfield(L, -2, "audio");
	lua_setfield(L, -2, "class_code"); /* ..., env */
	
	lua_newtable(L); /* ..., env, t */
	lua_pushnumber(L, LIBUSB_DT_DEVICE); lua_setfield(L, -2, "LIBUSB_DT_DEVICE");
	lua_pushnumber(L, LIBUSB_DT_DEVICE); lua_setfield(L, -2, "device");
	lua_pushnumber(L, LIBUSB_DT_HUB); lua_setfield(L, -2, "LIBUSB_DT_HUB");
	lua_pushnumber(L, LIBUSB_DT_HUB); lua_setfield(L, -2, "hub");
	lua_pushnumber(L, LIBUSB_DT_REPORT); lua_setfield(L, -2, "LIBUSB_DT_REPORT");
	lua_pushnumber(L, LIBUSB_DT_REPORT); lua_setfield(L, -2, "report");
	lua_pushnumber(L, LIBUSB_DT_HID); lua_setfield(L, -2, "LIBUSB_DT_HID");
	lua_pushnumber(L, LIBUSB_DT_HID); lua_setfield(L, -2, "hid");
	lua_pushnumber(L, LIBUSB_DT_STRING); lua_setfield(L, -2, "LIBUSB_DT_STRING");
	lua_pushnumber(L, LIBUSB_DT_STRING); lua_setfield(L, -2, "string");
	lua_pushnumber(L, LIBUSB_DT_CONFIG); lua_setfield(L, -2, "LIBUSB_DT_CONFIG");
	lua_pushnumber(L, LIBUSB_DT_CONFIG); lua_setfield(L, -2, "config");
	lua_pushnumber(L, LIBUSB_DT_INTERFACE); lua_setfield(L, -2, "LIBUSB_DT_INTERFACE");
	lua_pushnumber(L, LIBUSB_DT_INTERFACE); lua_setfield(L, -2, "interface");
	lua_pushnumber(L, LIBUSB_DT_PHYSICAL); lua_setfield(L, -2, "LIBUSB_DT_PHYSICAL");
	lua_pushnumber(L, LIBUSB_DT_PHYSICAL); lua_setfield(L, -2, "physical");
	lua_pushnumber(L, LIBUSB_DT_ENDPOINT); lua_setfield(L, -2, "LIBUSB_DT_ENDPOINT");
	lua_pushnumber(L, LIBUSB_DT_ENDPOINT); lua_setfield(L, -2, "endpoint");
	lua_setfield(L, -2, "descriptor_type"); /* ..., env */
	
	lua_newtable(L); /* ..., env, t */
	lua_pushnumber(L, LIBUSB_ENDPOINT_OUT); lua_setfield(L, -2, "LIBUSB_ENDPOINT_OUT");
	lua_pushnumber(L, LIBUSB_ENDPOINT_OUT); lua_setfield(L, -2, "out");
	lua_pushnumber(L, LIBUSB_ENDPOINT_IN); lua_setfield(L, -2, "LIBUSB_ENDPOINT_IN");
	lua_pushnumber(L, LIBUSB_ENDPOINT_IN); lua_setfield(L, -2, "in");
	lua_setfield(L, -2, "endpoint_direction"); /* ..., env */
	
	lua_newtable(L); /* ..., env, t */
	lua_pushnumber(L, LIBUSB_TRANSFER_TYPE_INTERRUPT); lua_setfield(L, -2, "LIBUSB_TRANSFER_TYPE_INTERRUPT");
	lua_pushnumber(L, LIBUSB_TRANSFER_TYPE_INTERRUPT); lua_setfield(L, -2, "interrupt");
	lua_pushnumber(L, LIBUSB_TRANSFER_TYPE_BULK); lua_setfield(L, -2, "LIBUSB_TRANSFER_TYPE_BULK");
	lua_pushnumber(L, LIBUSB_TRANSFER_TYPE_BULK); lua_setfield(L, -2, "bulk");
	lua_pushnumber(L, LIBUSB_TRANSFER_TYPE_CONTROL); lua_setfield(L, -2, "LIBUSB_TRANSFER_TYPE_CONTROL");
	lua_pushnumber(L, LIBUSB_TRANSFER_TYPE_CONTROL); lua_setfield(L, -2, "control");
	lua_pushnumber(L, LIBUSB_TRANSFER_TYPE_ISOCHRONOUS); lua_setfield(L, -2, "LIBUSB_TRANSFER_TYPE_ISOCHRONOUS");
	lua_pushnumber(L, LIBUSB_TRANSFER_TYPE_ISOCHRONOUS); lua_setfield(L, -2, "isochronous");
	lua_setfield(L, -2, "transfer_type"); /* ..., env */
	
	lua_newtable(L); /* ..., env, t */
	lua_pushnumber(L, LIBUSB_ISO_SYNC_TYPE_ASYNC); lua_setfield(L, -2, "LIBUSB_ISO_SYNC_TYPE_ASYNC");
	lua_pushnumber(L, LIBUSB_ISO_SYNC_TYPE_ASYNC); lua_setfield(L, -2, "async");
	lua_pushnumber(L, LIBUSB_ISO_SYNC_TYPE_ADAPTIVE); lua_setfield(L, -2, "LIBUSB_ISO_SYNC_TYPE_ADAPTIVE");
	lua_pushnumber(L, LIBUSB_ISO_SYNC_TYPE_ADAPTIVE); lua_setfield(L, -2, "adaptive");
	lua_pushnumber(L, LIBUSB_ISO_SYNC_TYPE_NONE); lua_setfield(L, -2, "LIBUSB_ISO_SYNC_TYPE_NONE");
	lua_pushnumber(L, LIBUSB_ISO_SYNC_TYPE_NONE); lua_setfield(L, -2, "none");
	lua_pushnumber(L, LIBUSB_ISO_SYNC_TYPE_SYNC); lua_setfield(L, -2, "LIBUSB_ISO_SYNC_TYPE_SYNC");
	lua_pushnumber(L, LIBUSB_ISO_SYNC_TYPE_SYNC); lua_setfield(L, -2, "sync");
	lua_setfield(L, -2, "iso_sync_type"); /* ..., env */
	
	lua_newtable(L); /* ..., env, t */
	lua_pushnumber(L, LIBUSB_ISO_USAGE_TYPE_IMPLICIT); lua_setfield(L, -2, "LIBUSB_ISO_USAGE_TYPE_IMPLICIT");
	lua_pushnumber(L, LIBUSB_ISO_USAGE_TYPE_IMPLICIT); lua_setfield(L, -2, "implicit");
	lua_pushnumber(L, LIBUSB_ISO_USAGE_TYPE_DATA); lua_setfield(L, -2, "LIBUSB_ISO_USAGE_TYPE_DATA");
	lua_pushnumber(L, LIBUSB_ISO_USAGE_TYPE_DATA); lua_setfield(L, -2, "data");
	lua_pushnumber(L, LIBUSB_ISO_USAGE_TYPE_FEEDBACK); lua_setfield(L, -2, "LIBUSB_ISO_USAGE_TYPE_FEEDBACK");
	lua_pushnumber(L, LIBUSB_ISO_USAGE_TYPE_FEEDBACK); lua_setfield(L, -2, "feedback");
	lua_setfield(L, -2, "iso_usage_type"); /* ..., env */
	
	lua_newtable(L); /* ..., env, t */
	lua_pushnumber(L, LIBUSB_REQUEST_GET_CONFIGURATION); lua_setfield(L, -2, "LIBUSB_REQUEST_GET_CONFIGURATION");
	lua_pushnumber(L, LIBUSB_REQUEST_GET_CONFIGURATION); lua_setfield(L, -2, "get_configuration");
	lua_pushnumber(L, LIBUSB_REQUEST_SET_ADDRESS); lua_setfield(L, -2, "LIBUSB_REQUEST_SET_ADDRESS");
	lua_pushnumber(L, LIBUSB_REQUEST_SET_ADDRESS); lua_setfield(L, -2, "set_address");
	lua_pushnumber(L, LIBUSB_REQUEST_SET_FEATURE); lua_setfield(L, -2, "LIBUSB_REQUEST_SET_FEATURE");
	lua_pushnumber(L, LIBUSB_REQUEST_SET_FEATURE); lua_setfield(L, -2, "set_feature");
	lua_pushnumber(L, LIBUSB_REQUEST_SYNCH_FRAME); lua_setfield(L, -2, "LIBUSB_REQUEST_SYNCH_FRAME");
	lua_pushnumber(L, LIBUSB_REQUEST_SYNCH_FRAME); lua_setfield(L, -2, "synch_frame");
	lua_pushnumber(L, LIBUSB_REQUEST_SET_CONFIGURATION); lua_setfield(L, -2, "LIBUSB_REQUEST_SET_CONFIGURATION");
	lua_pushnumber(L, LIBUSB_REQUEST_SET_CONFIGURATION); lua_setfield(L, -2, "set_configuration");
	lua_pushnumber(L, LIBUSB_REQUEST_GET_STATUS); lua_setfield(L, -2, "LIBUSB_REQUEST_GET_STATUS");
	lua_pushnumber(L, LIBUSB_REQUEST_GET_STATUS); lua_setfield(L, -2, "get_status");
	lua_pushnumber(L, LIBUSB_REQUEST_SET_INTERFACE); lua_setfield(L, -2, "LIBUSB_REQUEST_SET_INTERFACE");
	lua_pushnumber(L, LIBUSB_REQUEST_SET_INTERFACE); lua_setfield(L, -2, "set_interface");
	lua_pushnumber(L, LIBUSB_REQUEST_CLEAR_FEATURE); lua_setfield(L, -2, "LIBUSB_REQUEST_CLEAR_FEATURE");
	lua_pushnumber(L, LIBUSB_REQUEST_CLEAR_FEATURE); lua_setfield(L, -2, "clear_feature");
	lua_pushnumber(L, LIBUSB_REQUEST_GET_INTERFACE); lua_setfield(L, -2, "LIBUSB_REQUEST_GET_INTERFACE");
	lua_pushnumber(L, LIBUSB_REQUEST_GET_INTERFACE); lua_setfield(L, -2, "get_interface");
	lua_pushnumber(L, LIBUSB_REQUEST_SET_DESCRIPTOR); lua_setfield(L, -2, "LIBUSB_REQUEST_SET_DESCRIPTOR");
	lua_pushnumber(L, LIBUSB_REQUEST_SET_DESCRIPTOR); lua_setfield(L, -2, "set_descriptor");
	lua_pushnumber(L, LIBUSB_REQUEST_GET_DESCRIPTOR); lua_setfield(L, -2, "LIBUSB_REQUEST_GET_DESCRIPTOR");
	lua_pushnumber(L, LIBUSB_REQUEST_GET_DESCRIPTOR); lua_setfield(L, -2, "get_descriptor");
	lua_setfield(L, -2, "standard_request"); /* ..., env */
	
	lua_newtable(L); /* ..., env, t */
	lua_pushnumber(L, LIBUSB_REQUEST_TYPE_CLASS); lua_setfield(L, -2, "LIBUSB_REQUEST_TYPE_CLASS");
	lua_pushnumber(L, LIBUSB_REQUEST_TYPE_CLASS); lua_setfield(L, -2, "class");
	lua_pushnumber(L, LIBUSB_REQUEST_TYPE_RESERVED); lua_setfield(L, -2, "LIBUSB_REQUEST_TYPE_RESERVED");
	lua_pushnumber(L, LIBUSB_REQUEST_TYPE_RESERVED); lua_setfield(L, -2, "reserved");
	lua_pushnumber(L, LIBUSB_REQUEST_TYPE_VENDOR); lua_setfield(L, -2, "LIBUSB_REQUEST_TYPE_VENDOR");
	lua_pushnumber(L, LIBUSB_REQUEST_TYPE_VENDOR); lua_setfield(L, -2, "vendor");
	lua_pushnumber(L, LIBUSB_REQUEST_TYPE_STANDARD); lua_setfield(L, -2, "LIBUSB_REQUEST_TYPE_STANDARD");
	lua_pushnumber(L, LIBUSB_REQUEST_TYPE_STANDARD); lua_setfield(L, -2, "standard");
	lua_setfield(L, -2, "request_type"); /* ..., env */
	
	lua_newtable(L); /* ..., env, t */
	lua_pushnumber(L, LIBUSB_RECIPIENT_DEVICE); lua_setfield(L, -2, "LIBUSB_RECIPIENT_DEVICE");
	lua_pushnumber(L, LIBUSB_RECIPIENT_DEVICE); lua_setfield(L, -2, "device");
	lua_pushnumber(L, LIBUSB_RECIPIENT_INTERFACE); lua_setfield(L, -2, "LIBUSB_RECIPIENT_INTERFACE");
	lua_pushnumber(L, LIBUSB_RECIPIENT_INTERFACE); lua_setfield(L, -2, "interface");
	lua_pushnumber(L, LIBUSB_RECIPIENT_OTHER); lua_setfield(L, -2, "LIBUSB_RECIPIENT_OTHER");
	lua_pushnumber(L, LIBUSB_RECIPIENT_OTHER); lua_setfield(L, -2, "other");
	lua_pushnumber(L, LIBUSB_RECIPIENT_ENDPOINT); lua_setfield(L, -2, "LIBUSB_RECIPIENT_ENDPOINT");
	lua_pushnumber(L, LIBUSB_RECIPIENT_ENDPOINT); lua_setfield(L, -2, "endpoint");
	lua_setfield(L, -2, "request_recipient"); /* ..., env */
	
	lua_newtable(L); /* ..., env, t */
	lua_pushnumber(L, LIBUSB_ERROR_OVERFLOW); lua_setfield(L, -2, "LIBUSB_ERROR_OVERFLOW");
	lua_pushnumber(L, LIBUSB_ERROR_OVERFLOW); lua_setfield(L, -2, "overflow");
	lua_pushnumber(L, LIBUSB_ERROR_TIMEOUT); lua_setfield(L, -2, "LIBUSB_ERROR_TIMEOUT");
	lua_pushnumber(L, LIBUSB_ERROR_TIMEOUT); lua_setfield(L, -2, "timeout");
	lua_pushnumber(L, LIBUSB_ERROR_ACCESS); lua_setfield(L, -2, "LIBUSB_ERROR_ACCESS");
	lua_pushnumber(L, LIBUSB_ERROR_ACCESS); lua_setfield(L, -2, "access");
	lua_pushnumber(L, LIBUSB_ERROR_OTHER); lua_setfield(L, -2, "LIBUSB_ERROR_OTHER");
	lua_pushnumber(L, LIBUSB_ERROR_OTHER); lua_setfield(L, -2, "other");
	lua_pushnumber(L, LIBUSB_ERROR_NOT_SUPPORTED); lua_setfield(L, -2, "LIBUSB_ERROR_NOT_SUPPORTED");
	lua_pushnumber(L, LIBUSB_ERROR_NOT_SUPPORTED); lua_setfield(L, -2, "not_supported");
	lua_pushnumber(L, LIBUSB_ERROR_BUSY); lua_setfield(L, -2, "LIBUSB_ERROR_BUSY");
	lua_pushnumber(L, LIBUSB_ERROR_BUSY); lua_setfield(L, -2, "busy");
	lua_pushnumber(L, LIBUSB_ERROR_NO_MEM); lua_setfield(L, -2, "LIBUSB_ERROR_NO_MEM");
	lua_pushnumber(L, LIBUSB_ERROR_NO_MEM); lua_setfield(L, -2, "no_mem");
	lua_pushnumber(L, LIBUSB_ERROR_NO_DEVICE); lua_setfield(L, -2, "LIBUSB_ERROR_NO_DEVICE");
	lua_pushnumber(L, LIBUSB_ERROR_NO_DEVICE); lua_setfield(L, -2, "no_device");
	lua_pushnumber(L, LIBUSB_ERROR_NOT_FOUND); lua_setfield(L, -2, "LIBUSB_ERROR_NOT_FOUND");
	lua_pushnumber(L, LIBUSB_ERROR_NOT_FOUND); lua_setfield(L, -2, "not_found");
	lua_pushnumber(L, LIBUSB_ERROR_PIPE); lua_setfield(L, -2, "LIBUSB_ERROR_PIPE");
	lua_pushnumber(L, LIBUSB_ERROR_PIPE); lua_setfield(L, -2, "pipe");
	lua_pushnumber(L, LIBUSB_ERROR_INVALID_PARAM); lua_setfield(L, -2, "LIBUSB_ERROR_INVALID_PARAM");
	lua_pushnumber(L, LIBUSB_ERROR_INVALID_PARAM); lua_setfield(L, -2, "invalid_param");
	lua_pushnumber(L, LIBUSB_ERROR_IO); lua_setfield(L, -2, "LIBUSB_ERROR_IO");
	lua_pushnumber(L, LIBUSB_ERROR_IO); lua_setfield(L, -2, "io");
	lua_pushnumber(L, LIBUSB_ERROR_INTERRUPTED); lua_setfield(L, -2, "LIBUSB_ERROR_INTERRUPTED");
	lua_pushnumber(L, LIBUSB_ERROR_INTERRUPTED); lua_setfield(L, -2, "interrupted");
	lua_setfield(L, -2, "error"); /* ..., env */
	
	lua_newtable(L); /* ..., env, t */
	lua_pushnumber(L, LIBUSB_TRANSFER_ERROR); lua_setfield(L, -2, "LIBUSB_TRANSFER_ERROR");
	lua_pushnumber(L, LIBUSB_TRANSFER_ERROR); lua_setfield(L, -2, "error");
	lua_pushnumber(L, LIBUSB_TRANSFER_OVERFLOW); lua_setfield(L, -2, "LIBUSB_TRANSFER_OVERFLOW");
	lua_pushnumber(L, LIBUSB_TRANSFER_OVERFLOW); lua_setfield(L, -2, "overflow");
	lua_pushnumber(L, LIBUSB_TRANSFER_TIMED_OUT); lua_setfield(L, -2, "LIBUSB_TRANSFER_TIMED_OUT");
	lua_pushnumber(L, LIBUSB_TRANSFER_TIMED_OUT); lua_setfield(L, -2, "out");
	lua_pushnumber(L, LIBUSB_TRANSFER_CANCELLED); lua_setfield(L, -2, "LIBUSB_TRANSFER_CANCELLED");
	lua_pushnumber(L, LIBUSB_TRANSFER_CANCELLED); lua_setfield(L, -2, "cancelled");
	lua_pushnumber(L, LIBUSB_TRANSFER_NO_DEVICE); lua_setfield(L, -2, "LIBUSB_TRANSFER_NO_DEVICE");
	lua_pushnumber(L, LIBUSB_TRANSFER_NO_DEVICE); lua_setfield(L, -2, "device");
	lua_pushnumber(L, LIBUSB_TRANSFER_COMPLETED); lua_setfield(L, -2, "LIBUSB_TRANSFER_COMPLETED");
	lua_pushnumber(L, LIBUSB_TRANSFER_COMPLETED); lua_setfield(L, -2, "completed");
	lua_pushnumber(L, LIBUSB_TRANSFER_STALL); lua_setfield(L, -2, "LIBUSB_TRANSFER_STALL");
	lua_pushnumber(L, LIBUSB_TRANSFER_STALL); lua_setfield(L, -2, "stall");
	lua_setfield(L, -2, "transfer_status"); /* ..., env */
	
}

