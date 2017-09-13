/* this is a generated file, see gen.lua */
#include "Misc/libusb/include/structs.h"

#include "lauxlib.h"
#include <string.h>
#include "Misc/libusb/include/compat.h"

static int luausb_generic_index(lua_State* L)
{
	lua_getmetatable(L, 1);
	/* get a getter and call it */
	lua_getfield(L, -1, "getters");
	lua_pushvalue(L, 2);
	lua_gettable(L, -2);
	if (!lua_isnil(L, -1))
	{
		lua_pushvalue(L, 1);
		lua_call(L, 1, 1);
		return 1;
	}
	lua_pop(L, 2);
	/* get a method */
	lua_getfield(L, -1, "methods");
	lua_pushvalue(L, 2);
	lua_gettable(L, -2);
	return 1;
}

static int luausb_generic_newindex(lua_State* L)
{
	lua_getmetatable(L, 1);
	/* get a getter and call it */
	lua_getfield(L, -1, "setters");
	lua_pushvalue(L, 2);
	lua_gettable(L, -2);
	if (!lua_isnil(L, -1))
	{
		lua_pushvalue(L, 1);
		lua_pushvalue(L, 3);
		lua_call(L, 2, 1);
		return 1;
	}
	/* throw error */
	lua_pushliteral(L, "no setter for field ");
	lua_getglobal(L, "tostring");
	lua_pushvalue(L, 2);
	lua_call(L, 1, 1);
	lua_concat(L, 2);
	return lua_error(L);
}

static int luausb_generic_tostring(lua_State* L)
{
	lua_getmetatable(L, 1);
	lua_getfield(L, -1, "typename");
	lua_pushfstring(L, "%s: %p", lua_tostring(L, -1), lua_touserdata(L, 1));
	return 1;
}

struct libusb_device_descriptor* luausb_to_device_descriptor(lua_State* L, int index)
{
	struct libusb_device_descriptor* udata;
	udata = *(struct libusb_device_descriptor**)lua_touserdata(L, index);
	if (!udata)
	{
		luaL_argerror(L, index, "context has already been deinitialized");
		return NULL;
	}
	return udata;
}

int luausb_is_device_descriptor(lua_State* L, int index)
{
	int result = 0;
	void* p = lua_touserdata(L, index);
	/* value is a userdata? */
	if (p != NULL)
	{
		/* does it have a metatable? */
		if (lua_getmetatable(L, index))
		{
			/* get correct metatable */
			lua_getfield(L, LUA_REGISTRYINDEX, "struct libusb_device_descriptor");
			/* does it have the correct mt? */
			if (lua_rawequal(L, -1, -2))
			{
				result = 1;
			}
			lua_pop(L, 1); /* remove type metatable */
		}
		lua_pop(L, 1); /* remove udata metatable */
	}
	return result;
}

struct libusb_device_descriptor* luausb_check_device_descriptor(lua_State* L, int index)
{
	struct libusb_device_descriptor* udata;
	udata = *(struct libusb_device_descriptor**)luaL_checkudata(L, index, "struct libusb_device_descriptor");
	if (!udata)
	{
		luaL_argerror(L, index, "context has already been deinitialized");
		return NULL;
	}
	return udata;
}

void luausb_push_device_descriptor(lua_State* L, const struct libusb_device_descriptor* value, int owner)
{
	const struct libusb_device_descriptor** udata;
	if (owner < 0) owner = lua_gettop(L) + 1 + owner;
	udata = (const struct libusb_device_descriptor**)lua_newuserdata(L, sizeof(struct libusb_device_descriptor*));
	*udata = value;
	luaL_getmetatable(L, "struct libusb_device_descriptor");
	lua_setmetatable(L, -2);
	if (owner != 0)
	{
		lua_createtable(L, 1, 0);
		lua_pushvalue(L, owner);
		lua_rawseti(L, -2, 1);
		setuservalue(L, -2);
	}
}

static int luausb_get_device_descriptor_bLength(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	udata = luausb_to_device_descriptor(L, 1);
	lua_pushnumber(L, udata->bLength);
	return 1;
}

static int luausb_set_device_descriptor_bLength(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bLength (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_device_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bLength = (uint8_t)value;
	return 0;
}

static int luausb_get_device_descriptor_bDescriptorType(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	udata = luausb_to_device_descriptor(L, 1);
	lua_pushnumber(L, udata->bDescriptorType);
	return 1;
}

static int luausb_set_device_descriptor_bDescriptorType(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bDescriptorType (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_device_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bDescriptorType = (uint8_t)value;
	return 0;
}

static int luausb_get_device_descriptor_bcdUSB(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	udata = luausb_to_device_descriptor(L, 1);
	lua_pushnumber(L, udata->bcdUSB);
	return 1;
}

static int luausb_set_device_descriptor_bcdUSB(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bcdUSB (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_device_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bcdUSB = (uint16_t)value;
	return 0;
}

static int luausb_get_device_descriptor_bDeviceClass(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	udata = luausb_to_device_descriptor(L, 1);
	lua_pushnumber(L, udata->bDeviceClass);
	return 1;
}

static int luausb_set_device_descriptor_bDeviceClass(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bDeviceClass (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_device_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bDeviceClass = (uint8_t)value;
	return 0;
}

static int luausb_get_device_descriptor_bDeviceSubClass(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	udata = luausb_to_device_descriptor(L, 1);
	lua_pushnumber(L, udata->bDeviceSubClass);
	return 1;
}

static int luausb_set_device_descriptor_bDeviceSubClass(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bDeviceSubClass (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_device_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bDeviceSubClass = (uint8_t)value;
	return 0;
}

static int luausb_get_device_descriptor_bDeviceProtocol(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	udata = luausb_to_device_descriptor(L, 1);
	lua_pushnumber(L, udata->bDeviceProtocol);
	return 1;
}

static int luausb_set_device_descriptor_bDeviceProtocol(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bDeviceProtocol (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_device_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bDeviceProtocol = (uint8_t)value;
	return 0;
}

static int luausb_get_device_descriptor_bMaxPacketSize0(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	udata = luausb_to_device_descriptor(L, 1);
	lua_pushnumber(L, udata->bMaxPacketSize0);
	return 1;
}

static int luausb_set_device_descriptor_bMaxPacketSize0(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bMaxPacketSize0 (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_device_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bMaxPacketSize0 = (uint8_t)value;
	return 0;
}

static int luausb_get_device_descriptor_idVendor(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	udata = luausb_to_device_descriptor(L, 1);
	lua_pushnumber(L, udata->idVendor);
	return 1;
}

static int luausb_set_device_descriptor_idVendor(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field idVendor (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_device_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->idVendor = (uint16_t)value;
	return 0;
}

static int luausb_get_device_descriptor_idProduct(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	udata = luausb_to_device_descriptor(L, 1);
	lua_pushnumber(L, udata->idProduct);
	return 1;
}

static int luausb_set_device_descriptor_idProduct(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field idProduct (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_device_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->idProduct = (uint16_t)value;
	return 0;
}

static int luausb_get_device_descriptor_bcdDevice(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	udata = luausb_to_device_descriptor(L, 1);
	lua_pushnumber(L, udata->bcdDevice);
	return 1;
}

static int luausb_set_device_descriptor_bcdDevice(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bcdDevice (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_device_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bcdDevice = (uint16_t)value;
	return 0;
}

static int luausb_get_device_descriptor_iManufacturer(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	udata = luausb_to_device_descriptor(L, 1);
	lua_pushnumber(L, udata->iManufacturer);
	return 1;
}

static int luausb_set_device_descriptor_iManufacturer(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field iManufacturer (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_device_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->iManufacturer = (uint8_t)value;
	return 0;
}

static int luausb_get_device_descriptor_iProduct(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	udata = luausb_to_device_descriptor(L, 1);
	lua_pushnumber(L, udata->iProduct);
	return 1;
}

static int luausb_set_device_descriptor_iProduct(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field iProduct (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_device_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->iProduct = (uint8_t)value;
	return 0;
}

static int luausb_get_device_descriptor_iSerialNumber(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	udata = luausb_to_device_descriptor(L, 1);
	lua_pushnumber(L, udata->iSerialNumber);
	return 1;
}

static int luausb_set_device_descriptor_iSerialNumber(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field iSerialNumber (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_device_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->iSerialNumber = (uint8_t)value;
	return 0;
}

static int luausb_get_device_descriptor_bNumConfigurations(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	udata = luausb_to_device_descriptor(L, 1);
	lua_pushnumber(L, udata->bNumConfigurations);
	return 1;
}

static int luausb_set_device_descriptor_bNumConfigurations(lua_State* L)
{
	struct libusb_device_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bNumConfigurations (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_device_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bNumConfigurations = (uint8_t)value;
	return 0;
}

static struct luaL_Reg libusb_device_descriptor__getters[] = {
	{"bLength", luausb_get_device_descriptor_bLength},
	{"bDescriptorType", luausb_get_device_descriptor_bDescriptorType},
	{"bcdUSB", luausb_get_device_descriptor_bcdUSB},
	{"bDeviceClass", luausb_get_device_descriptor_bDeviceClass},
	{"bDeviceSubClass", luausb_get_device_descriptor_bDeviceSubClass},
	{"bDeviceProtocol", luausb_get_device_descriptor_bDeviceProtocol},
	{"bMaxPacketSize0", luausb_get_device_descriptor_bMaxPacketSize0},
	{"idVendor", luausb_get_device_descriptor_idVendor},
	{"idProduct", luausb_get_device_descriptor_idProduct},
	{"bcdDevice", luausb_get_device_descriptor_bcdDevice},
	{"iManufacturer", luausb_get_device_descriptor_iManufacturer},
	{"iProduct", luausb_get_device_descriptor_iProduct},
	{"iSerialNumber", luausb_get_device_descriptor_iSerialNumber},
	{"bNumConfigurations", luausb_get_device_descriptor_bNumConfigurations},
	{0, 0},
};

static struct luaL_Reg libusb_device_descriptor__setters[] = {
	{"bLength", luausb_set_device_descriptor_bLength},
	{"bDescriptorType", luausb_set_device_descriptor_bDescriptorType},
	{"bcdUSB", luausb_set_device_descriptor_bcdUSB},
	{"bDeviceClass", luausb_set_device_descriptor_bDeviceClass},
	{"bDeviceSubClass", luausb_set_device_descriptor_bDeviceSubClass},
	{"bDeviceProtocol", luausb_set_device_descriptor_bDeviceProtocol},
	{"bMaxPacketSize0", luausb_set_device_descriptor_bMaxPacketSize0},
	{"idVendor", luausb_set_device_descriptor_idVendor},
	{"idProduct", luausb_set_device_descriptor_idProduct},
	{"bcdDevice", luausb_set_device_descriptor_bcdDevice},
	{"iManufacturer", luausb_set_device_descriptor_iManufacturer},
	{"iProduct", luausb_set_device_descriptor_iProduct},
	{"iSerialNumber", luausb_set_device_descriptor_iSerialNumber},
	{"bNumConfigurations", luausb_set_device_descriptor_bNumConfigurations},
	{0, 0},
};
static struct luaL_Reg libusb_device_descriptor__metamethods[] = {
	{"__index", luausb_generic_index},
	{"__newindex", luausb_generic_newindex},
	{"__tostring", luausb_generic_tostring},
	{0, 0},
};
extern struct luaL_Reg libusb_device_descriptor__methods[];

struct libusb_endpoint_descriptor* luausb_to_endpoint_descriptor(lua_State* L, int index)
{
	struct libusb_endpoint_descriptor* udata;
	udata = *(struct libusb_endpoint_descriptor**)lua_touserdata(L, index);
	if (!udata)
	{
		luaL_argerror(L, index, "context has already been deinitialized");
		return NULL;
	}
	return udata;
}

int luausb_is_endpoint_descriptor(lua_State* L, int index)
{
	int result = 0;
	void* p = lua_touserdata(L, index);
	/* value is a userdata? */
	if (p != NULL)
	{
		/* does it have a metatable? */
		if (lua_getmetatable(L, index))
		{
			/* get correct metatable */
			lua_getfield(L, LUA_REGISTRYINDEX, "struct libusb_endpoint_descriptor");
			/* does it have the correct mt? */
			if (lua_rawequal(L, -1, -2))
			{
				result = 1;
			}
			lua_pop(L, 1); /* remove type metatable */
		}
		lua_pop(L, 1); /* remove udata metatable */
	}
	return result;
}

struct libusb_endpoint_descriptor* luausb_check_endpoint_descriptor(lua_State* L, int index)
{
	struct libusb_endpoint_descriptor* udata;
	udata = *(struct libusb_endpoint_descriptor**)luaL_checkudata(L, index, "struct libusb_endpoint_descriptor");
	if (!udata)
	{
		luaL_argerror(L, index, "context has already been deinitialized");
		return NULL;
	}
	return udata;
}

void luausb_push_endpoint_descriptor(lua_State* L, const struct libusb_endpoint_descriptor* value, int owner)
{
	const struct libusb_endpoint_descriptor** udata;
	if (owner < 0) owner = lua_gettop(L) + 1 + owner;
	udata = (const struct libusb_endpoint_descriptor**)lua_newuserdata(L, sizeof(struct libusb_endpoint_descriptor*));
	*udata = value;
	luaL_getmetatable(L, "struct libusb_endpoint_descriptor");
	lua_setmetatable(L, -2);
	lua_createtable(L, 1, 0);
	if (owner != 0)
	{
		lua_pushvalue(L, owner);
		lua_rawseti(L, -2, 1);
	}
	setuservalue(L, -2);
}

static int luausb_get_endpoint_descriptor_bLength(lua_State* L)
{
	struct libusb_endpoint_descriptor* udata;
	udata = luausb_to_endpoint_descriptor(L, 1);
	lua_pushnumber(L, udata->bLength);
	return 1;
}

static int luausb_set_endpoint_descriptor_bLength(lua_State* L)
{
	struct libusb_endpoint_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bLength (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_endpoint_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bLength = (uint8_t)value;
	return 0;
}

static int luausb_get_endpoint_descriptor_bDescriptorType(lua_State* L)
{
	struct libusb_endpoint_descriptor* udata;
	udata = luausb_to_endpoint_descriptor(L, 1);
	lua_pushnumber(L, udata->bDescriptorType);
	return 1;
}

static int luausb_set_endpoint_descriptor_bDescriptorType(lua_State* L)
{
	struct libusb_endpoint_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bDescriptorType (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_endpoint_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bDescriptorType = (uint8_t)value;
	return 0;
}

static int luausb_get_endpoint_descriptor_bEndpointAddress(lua_State* L)
{
	struct libusb_endpoint_descriptor* udata;
	udata = luausb_to_endpoint_descriptor(L, 1);
	lua_pushnumber(L, udata->bEndpointAddress);
	return 1;
}

static int luausb_set_endpoint_descriptor_bEndpointAddress(lua_State* L)
{
	struct libusb_endpoint_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bEndpointAddress (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_endpoint_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bEndpointAddress = (uint8_t)value;
	return 0;
}

static int luausb_get_endpoint_descriptor_bmAttributes(lua_State* L)
{
	struct libusb_endpoint_descriptor* udata;
	udata = luausb_to_endpoint_descriptor(L, 1);
	lua_pushnumber(L, udata->bmAttributes);
	return 1;
}

static int luausb_set_endpoint_descriptor_bmAttributes(lua_State* L)
{
	struct libusb_endpoint_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bmAttributes (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_endpoint_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bmAttributes = (uint8_t)value;
	return 0;
}

static int luausb_get_endpoint_descriptor_wMaxPacketSize(lua_State* L)
{
	struct libusb_endpoint_descriptor* udata;
	udata = luausb_to_endpoint_descriptor(L, 1);
	lua_pushnumber(L, udata->wMaxPacketSize);
	return 1;
}

static int luausb_set_endpoint_descriptor_wMaxPacketSize(lua_State* L)
{
	struct libusb_endpoint_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field wMaxPacketSize (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_endpoint_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->wMaxPacketSize = (uint16_t)value;
	return 0;
}

static int luausb_get_endpoint_descriptor_bInterval(lua_State* L)
{
	struct libusb_endpoint_descriptor* udata;
	udata = luausb_to_endpoint_descriptor(L, 1);
	lua_pushnumber(L, udata->bInterval);
	return 1;
}

static int luausb_set_endpoint_descriptor_bInterval(lua_State* L)
{
	struct libusb_endpoint_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bInterval (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_endpoint_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bInterval = (uint8_t)value;
	return 0;
}

static int luausb_get_endpoint_descriptor_bRefresh(lua_State* L)
{
	struct libusb_endpoint_descriptor* udata;
	udata = luausb_to_endpoint_descriptor(L, 1);
	lua_pushnumber(L, udata->bRefresh);
	return 1;
}

static int luausb_set_endpoint_descriptor_bRefresh(lua_State* L)
{
	struct libusb_endpoint_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bRefresh (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_endpoint_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bRefresh = (uint8_t)value;
	return 0;
}

static int luausb_get_endpoint_descriptor_bSynchAddress(lua_State* L)
{
	struct libusb_endpoint_descriptor* udata;
	udata = luausb_to_endpoint_descriptor(L, 1);
	lua_pushnumber(L, udata->bSynchAddress);
	return 1;
}

static int luausb_set_endpoint_descriptor_bSynchAddress(lua_State* L)
{
	struct libusb_endpoint_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bSynchAddress (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_endpoint_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bSynchAddress = (uint8_t)value;
	return 0;
}

static int luausb_get_endpoint_descriptor_extra(lua_State* L)
{
	struct libusb_endpoint_descriptor* udata;
	udata = luausb_to_endpoint_descriptor(L, 1);
	if (udata->extra)
	{
		lua_pushlstring(L, (const char*)udata->extra, udata->extra_length);
	}
	else
		lua_pushnil(L);
	return 1;
}

static int luausb_set_endpoint_descriptor_extra(lua_State* L)
{
	struct libusb_endpoint_descriptor* udata;
	if (!lua_isstring(L, 2))
	{
		lua_pushliteral(L, "invalid value for field extra (string expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_endpoint_descriptor(L, 1);
	getuservalue(L, 1);
	lua_pushvalue(L, 2);
	lua_setfield(L, -2, "extra");
	lua_pop(L, 1);
	{
		size_t size;
		udata->extra = (const unsigned char*)lua_tolstring(L, 2, &size);
		udata->extra_length = (int)size;
	}
	return 0;
}

static struct luaL_Reg libusb_endpoint_descriptor__getters[] = {
	{"bLength", luausb_get_endpoint_descriptor_bLength},
	{"bDescriptorType", luausb_get_endpoint_descriptor_bDescriptorType},
	{"bEndpointAddress", luausb_get_endpoint_descriptor_bEndpointAddress},
	{"bmAttributes", luausb_get_endpoint_descriptor_bmAttributes},
	{"wMaxPacketSize", luausb_get_endpoint_descriptor_wMaxPacketSize},
	{"bInterval", luausb_get_endpoint_descriptor_bInterval},
	{"bRefresh", luausb_get_endpoint_descriptor_bRefresh},
	{"bSynchAddress", luausb_get_endpoint_descriptor_bSynchAddress},
	{"extra", luausb_get_endpoint_descriptor_extra},
	{0, 0},
};

static struct luaL_Reg libusb_endpoint_descriptor__setters[] = {
	{"bLength", luausb_set_endpoint_descriptor_bLength},
	{"bDescriptorType", luausb_set_endpoint_descriptor_bDescriptorType},
	{"bEndpointAddress", luausb_set_endpoint_descriptor_bEndpointAddress},
	{"bmAttributes", luausb_set_endpoint_descriptor_bmAttributes},
	{"wMaxPacketSize", luausb_set_endpoint_descriptor_wMaxPacketSize},
	{"bInterval", luausb_set_endpoint_descriptor_bInterval},
	{"bRefresh", luausb_set_endpoint_descriptor_bRefresh},
	{"bSynchAddress", luausb_set_endpoint_descriptor_bSynchAddress},
	{"extra", luausb_set_endpoint_descriptor_extra},
	{0, 0},
};
static struct luaL_Reg libusb_endpoint_descriptor__metamethods[] = {
	{"__index", luausb_generic_index},
	{"__newindex", luausb_generic_newindex},
	{"__tostring", luausb_generic_tostring},
	{0, 0},
};
extern struct luaL_Reg libusb_endpoint_descriptor__methods[];

struct libusb_interface_descriptor* luausb_to_interface_descriptor(lua_State* L, int index)
{
	struct libusb_interface_descriptor* udata;
	udata = *(struct libusb_interface_descriptor**)lua_touserdata(L, index);
	if (!udata)
	{
		luaL_argerror(L, index, "context has already been deinitialized");
		return NULL;
	}
	return udata;
}

int luausb_is_interface_descriptor(lua_State* L, int index)
{
	int result = 0;
	void* p = lua_touserdata(L, index);
	/* value is a userdata? */
	if (p != NULL)
	{
		/* does it have a metatable? */
		if (lua_getmetatable(L, index))
		{
			/* get correct metatable */
			lua_getfield(L, LUA_REGISTRYINDEX, "struct libusb_interface_descriptor");
			/* does it have the correct mt? */
			if (lua_rawequal(L, -1, -2))
			{
				result = 1;
			}
			lua_pop(L, 1); /* remove type metatable */
		}
		lua_pop(L, 1); /* remove udata metatable */
	}
	return result;
}

struct libusb_interface_descriptor* luausb_check_interface_descriptor(lua_State* L, int index)
{
	struct libusb_interface_descriptor* udata;
	udata = *(struct libusb_interface_descriptor**)luaL_checkudata(L, index, "struct libusb_interface_descriptor");
	if (!udata)
	{
		luaL_argerror(L, index, "context has already been deinitialized");
		return NULL;
	}
	return udata;
}

void luausb_push_interface_descriptor(lua_State* L, const struct libusb_interface_descriptor* value, int owner)
{
	const struct libusb_interface_descriptor** udata;
	if (owner < 0) owner = lua_gettop(L) + 1 + owner;
	udata = (const struct libusb_interface_descriptor**)lua_newuserdata(L, sizeof(struct libusb_interface_descriptor*));
	*udata = value;
	luaL_getmetatable(L, "struct libusb_interface_descriptor");
	lua_setmetatable(L, -2);
	lua_createtable(L, 1, 0);
	if (owner != 0)
	{
		lua_pushvalue(L, owner);
		lua_rawseti(L, -2, 1);
	}
	setuservalue(L, -2);
}

static int luausb_get_interface_descriptor_bLength(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	udata = luausb_to_interface_descriptor(L, 1);
	lua_pushnumber(L, udata->bLength);
	return 1;
}

static int luausb_set_interface_descriptor_bLength(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bLength (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_interface_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bLength = (uint8_t)value;
	return 0;
}

static int luausb_get_interface_descriptor_bDescriptorType(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	udata = luausb_to_interface_descriptor(L, 1);
	lua_pushnumber(L, udata->bDescriptorType);
	return 1;
}

static int luausb_set_interface_descriptor_bDescriptorType(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bDescriptorType (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_interface_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bDescriptorType = (uint8_t)value;
	return 0;
}

static int luausb_get_interface_descriptor_bInterfaceNumber(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	udata = luausb_to_interface_descriptor(L, 1);
	lua_pushnumber(L, udata->bInterfaceNumber);
	return 1;
}

static int luausb_set_interface_descriptor_bInterfaceNumber(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bInterfaceNumber (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_interface_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bInterfaceNumber = (uint8_t)value;
	return 0;
}

static int luausb_get_interface_descriptor_bAlternateSetting(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	udata = luausb_to_interface_descriptor(L, 1);
	lua_pushnumber(L, udata->bAlternateSetting);
	return 1;
}

static int luausb_set_interface_descriptor_bAlternateSetting(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bAlternateSetting (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_interface_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bAlternateSetting = (uint8_t)value;
	return 0;
}

static int luausb_get_interface_descriptor_bNumEndpoints(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	udata = luausb_to_interface_descriptor(L, 1);
	lua_pushnumber(L, udata->bNumEndpoints);
	return 1;
}

static int luausb_set_interface_descriptor_bNumEndpoints(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bNumEndpoints (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_interface_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bNumEndpoints = (uint8_t)value;
	return 0;
}

static int luausb_get_interface_descriptor_bInterfaceClass(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	udata = luausb_to_interface_descriptor(L, 1);
	lua_pushnumber(L, udata->bInterfaceClass);
	return 1;
}

static int luausb_set_interface_descriptor_bInterfaceClass(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bInterfaceClass (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_interface_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bInterfaceClass = (uint8_t)value;
	return 0;
}

static int luausb_get_interface_descriptor_bInterfaceSubClass(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	udata = luausb_to_interface_descriptor(L, 1);
	lua_pushnumber(L, udata->bInterfaceSubClass);
	return 1;
}

static int luausb_set_interface_descriptor_bInterfaceSubClass(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bInterfaceSubClass (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_interface_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bInterfaceSubClass = (uint8_t)value;
	return 0;
}

static int luausb_get_interface_descriptor_bInterfaceProtocol(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	udata = luausb_to_interface_descriptor(L, 1);
	lua_pushnumber(L, udata->bInterfaceProtocol);
	return 1;
}

static int luausb_set_interface_descriptor_bInterfaceProtocol(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bInterfaceProtocol (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_interface_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bInterfaceProtocol = (uint8_t)value;
	return 0;
}

static int luausb_get_interface_descriptor_iInterface(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	udata = luausb_to_interface_descriptor(L, 1);
	lua_pushnumber(L, udata->iInterface);
	return 1;
}

static int luausb_set_interface_descriptor_iInterface(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field iInterface (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_interface_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->iInterface = (uint8_t)value;
	return 0;
}

int luausb_get_interface_descriptor_endpoint(lua_State* L);

static int luausb_get_interface_descriptor_extra(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	udata = luausb_to_interface_descriptor(L, 1);
	if (udata->extra)
	{
		lua_pushlstring(L, (const char*)udata->extra, udata->extra_length);
	}
	else
		lua_pushnil(L);
	return 1;
}

static int luausb_set_interface_descriptor_extra(lua_State* L)
{
	struct libusb_interface_descriptor* udata;
	if (!lua_isstring(L, 2))
	{
		lua_pushliteral(L, "invalid value for field extra (string expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_interface_descriptor(L, 1);
	getuservalue(L, 1);
	lua_pushvalue(L, 2);
	lua_setfield(L, -2, "extra");
	lua_pop(L, 1);
	{
		size_t size;
		udata->extra = (const unsigned char*)lua_tolstring(L, 2, &size);
		udata->extra_length = (int)size;
	}
	return 0;
}

static struct luaL_Reg libusb_interface_descriptor__getters[] = {
	{"bLength", luausb_get_interface_descriptor_bLength},
	{"bDescriptorType", luausb_get_interface_descriptor_bDescriptorType},
	{"bInterfaceNumber", luausb_get_interface_descriptor_bInterfaceNumber},
	{"bAlternateSetting", luausb_get_interface_descriptor_bAlternateSetting},
	{"bNumEndpoints", luausb_get_interface_descriptor_bNumEndpoints},
	{"bInterfaceClass", luausb_get_interface_descriptor_bInterfaceClass},
	{"bInterfaceSubClass", luausb_get_interface_descriptor_bInterfaceSubClass},
	{"bInterfaceProtocol", luausb_get_interface_descriptor_bInterfaceProtocol},
	{"iInterface", luausb_get_interface_descriptor_iInterface},
	{"endpoint", luausb_get_interface_descriptor_endpoint},
	{"extra", luausb_get_interface_descriptor_extra},
	{0, 0},
};

static struct luaL_Reg libusb_interface_descriptor__setters[] = {
	{"bLength", luausb_set_interface_descriptor_bLength},
	{"bDescriptorType", luausb_set_interface_descriptor_bDescriptorType},
	{"bInterfaceNumber", luausb_set_interface_descriptor_bInterfaceNumber},
	{"bAlternateSetting", luausb_set_interface_descriptor_bAlternateSetting},
	{"bNumEndpoints", luausb_set_interface_descriptor_bNumEndpoints},
	{"bInterfaceClass", luausb_set_interface_descriptor_bInterfaceClass},
	{"bInterfaceSubClass", luausb_set_interface_descriptor_bInterfaceSubClass},
	{"bInterfaceProtocol", luausb_set_interface_descriptor_bInterfaceProtocol},
	{"iInterface", luausb_set_interface_descriptor_iInterface},
	{"extra", luausb_set_interface_descriptor_extra},
	{0, 0},
};
static struct luaL_Reg libusb_interface_descriptor__metamethods[] = {
	{"__index", luausb_generic_index},
	{"__newindex", luausb_generic_newindex},
	{"__tostring", luausb_generic_tostring},
	{0, 0},
};
extern struct luaL_Reg libusb_interface_descriptor__methods[];

struct libusb_interface* luausb_to_interface(lua_State* L, int index)
{
	struct libusb_interface* udata;
	udata = *(struct libusb_interface**)lua_touserdata(L, index);
	if (!udata)
	{
		luaL_argerror(L, index, "context has already been deinitialized");
		return NULL;
	}
	return udata;
}

int luausb_is_interface(lua_State* L, int index)
{
	int result = 0;
	void* p = lua_touserdata(L, index);
	/* value is a userdata? */
	if (p != NULL)
	{
		/* does it have a metatable? */
		if (lua_getmetatable(L, index))
		{
			/* get correct metatable */
			lua_getfield(L, LUA_REGISTRYINDEX, "struct libusb_interface");
			/* does it have the correct mt? */
			if (lua_rawequal(L, -1, -2))
			{
				result = 1;
			}
			lua_pop(L, 1); /* remove type metatable */
		}
		lua_pop(L, 1); /* remove udata metatable */
	}
	return result;
}

struct libusb_interface* luausb_check_interface(lua_State* L, int index)
{
	struct libusb_interface* udata;
	udata = *(struct libusb_interface**)luaL_checkudata(L, index, "struct libusb_interface");
	if (!udata)
	{
		luaL_argerror(L, index, "context has already been deinitialized");
		return NULL;
	}
	return udata;
}

void luausb_push_interface(lua_State* L, const struct libusb_interface* value, int owner)
{
	const struct libusb_interface** udata;
	if (owner < 0) owner = lua_gettop(L) + 1 + owner;
	udata = (const struct libusb_interface**)lua_newuserdata(L, sizeof(struct libusb_interface*));
	*udata = value;
	luaL_getmetatable(L, "struct libusb_interface");
	lua_setmetatable(L, -2);
	if (owner != 0)
	{
		lua_createtable(L, 1, 0);
		lua_pushvalue(L, owner);
		lua_rawseti(L, -2, 1);
		setuservalue(L, -2);
	}
}

int luausb_get_interface_altsetting(lua_State* L);

static int luausb_get_interface_num_altsetting(lua_State* L)
{
	struct libusb_interface* udata;
	udata = luausb_to_interface(L, 1);
	lua_pushnumber(L, udata->num_altsetting);
	return 1;
}

static int luausb_set_interface_num_altsetting(lua_State* L)
{
	struct libusb_interface* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field num_altsetting (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_interface(L, 1);
	value = lua_tonumber(L, 2);
	udata->num_altsetting = (int)value;
	return 0;
}

static struct luaL_Reg libusb_interface__getters[] = {
	{"altsetting", luausb_get_interface_altsetting},
	{"num_altsetting", luausb_get_interface_num_altsetting},
	{0, 0},
};

static struct luaL_Reg libusb_interface__setters[] = {
	{"num_altsetting", luausb_set_interface_num_altsetting},
	{0, 0},
};
static struct luaL_Reg libusb_interface__metamethods[] = {
	{"__index", luausb_generic_index},
	{"__newindex", luausb_generic_newindex},
	{"__tostring", luausb_generic_tostring},
	{0, 0},
};
extern struct luaL_Reg libusb_interface__methods[];

struct libusb_config_descriptor* luausb_to_config_descriptor(lua_State* L, int index)
{
	struct libusb_config_descriptor* udata;
	udata = *(struct libusb_config_descriptor**)lua_touserdata(L, index);
	if (!udata)
	{
		luaL_argerror(L, index, "context has already been deinitialized");
		return NULL;
	}
	return udata;
}

int luausb_is_config_descriptor(lua_State* L, int index)
{
	int result = 0;
	void* p = lua_touserdata(L, index);
	/* value is a userdata? */
	if (p != NULL)
	{
		/* does it have a metatable? */
		if (lua_getmetatable(L, index))
		{
			/* get correct metatable */
			lua_getfield(L, LUA_REGISTRYINDEX, "struct libusb_config_descriptor");
			/* does it have the correct mt? */
			if (lua_rawequal(L, -1, -2))
			{
				result = 1;
			}
			lua_pop(L, 1); /* remove type metatable */
		}
		lua_pop(L, 1); /* remove udata metatable */
	}
	return result;
}

struct libusb_config_descriptor* luausb_check_config_descriptor(lua_State* L, int index)
{
	struct libusb_config_descriptor* udata;
	udata = *(struct libusb_config_descriptor**)luaL_checkudata(L, index, "struct libusb_config_descriptor");
	if (!udata)
	{
		luaL_argerror(L, index, "context has already been deinitialized");
		return NULL;
	}
	return udata;
}

void luausb_push_config_descriptor(lua_State* L, const struct libusb_config_descriptor* value, int owner)
{
	const struct libusb_config_descriptor** udata;
	if (owner < 0) owner = lua_gettop(L) + 1 + owner;
	udata = (const struct libusb_config_descriptor**)lua_newuserdata(L, sizeof(struct libusb_config_descriptor*));
	*udata = value;
	luaL_getmetatable(L, "struct libusb_config_descriptor");
	lua_setmetatable(L, -2);
	lua_createtable(L, 1, 0);
	if (owner != 0)
	{
		lua_pushvalue(L, owner);
		lua_rawseti(L, -2, 1);
	}
	setuservalue(L, -2);
}

static int luausb_get_config_descriptor_bLength(lua_State* L)
{
	struct libusb_config_descriptor* udata;
	udata = luausb_to_config_descriptor(L, 1);
	lua_pushnumber(L, udata->bLength);
	return 1;
}

static int luausb_set_config_descriptor_bLength(lua_State* L)
{
	struct libusb_config_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bLength (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_config_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bLength = (uint8_t)value;
	return 0;
}

static int luausb_get_config_descriptor_bDescriptorType(lua_State* L)
{
	struct libusb_config_descriptor* udata;
	udata = luausb_to_config_descriptor(L, 1);
	lua_pushnumber(L, udata->bDescriptorType);
	return 1;
}

static int luausb_set_config_descriptor_bDescriptorType(lua_State* L)
{
	struct libusb_config_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bDescriptorType (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_config_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bDescriptorType = (uint8_t)value;
	return 0;
}

static int luausb_get_config_descriptor_wTotalLength(lua_State* L)
{
	struct libusb_config_descriptor* udata;
	udata = luausb_to_config_descriptor(L, 1);
	lua_pushnumber(L, udata->wTotalLength);
	return 1;
}

static int luausb_set_config_descriptor_wTotalLength(lua_State* L)
{
	struct libusb_config_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field wTotalLength (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_config_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->wTotalLength = (uint16_t)value;
	return 0;
}

static int luausb_get_config_descriptor_bNumInterfaces(lua_State* L)
{
	struct libusb_config_descriptor* udata;
	udata = luausb_to_config_descriptor(L, 1);
	lua_pushnumber(L, udata->bNumInterfaces);
	return 1;
}

static int luausb_set_config_descriptor_bNumInterfaces(lua_State* L)
{
	struct libusb_config_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bNumInterfaces (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_config_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bNumInterfaces = (uint8_t)value;
	return 0;
}

static int luausb_get_config_descriptor_bConfigurationValue(lua_State* L)
{
	struct libusb_config_descriptor* udata;
	udata = luausb_to_config_descriptor(L, 1);
	lua_pushnumber(L, udata->bConfigurationValue);
	return 1;
}

static int luausb_set_config_descriptor_bConfigurationValue(lua_State* L)
{
	struct libusb_config_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bConfigurationValue (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_config_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bConfigurationValue = (uint8_t)value;
	return 0;
}

static int luausb_get_config_descriptor_iConfiguration(lua_State* L)
{
	struct libusb_config_descriptor* udata;
	udata = luausb_to_config_descriptor(L, 1);
	lua_pushnumber(L, udata->iConfiguration);
	return 1;
}

static int luausb_set_config_descriptor_iConfiguration(lua_State* L)
{
	struct libusb_config_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field iConfiguration (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_config_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->iConfiguration = (uint8_t)value;
	return 0;
}

static int luausb_get_config_descriptor_bmAttributes(lua_State* L)
{
	struct libusb_config_descriptor* udata;
	udata = luausb_to_config_descriptor(L, 1);
	lua_pushnumber(L, udata->bmAttributes);
	return 1;
}

static int luausb_set_config_descriptor_bmAttributes(lua_State* L)
{
	struct libusb_config_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field bmAttributes (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_config_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->bmAttributes = (uint8_t)value;
	return 0;
}

static int luausb_get_config_descriptor_MaxPower(lua_State* L)
{
	struct libusb_config_descriptor* udata;
	udata = luausb_to_config_descriptor(L, 1);
	lua_pushnumber(L, udata->MaxPower);
	return 1;
}

static int luausb_set_config_descriptor_MaxPower(lua_State* L)
{
	struct libusb_config_descriptor* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field MaxPower (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_config_descriptor(L, 1);
	value = lua_tonumber(L, 2);
	udata->MaxPower = (uint8_t)value;
	return 0;
}

int luausb_get_config_descriptor_interface(lua_State* L);

static int luausb_get_config_descriptor_extra(lua_State* L)
{
	struct libusb_config_descriptor* udata;
	udata = luausb_to_config_descriptor(L, 1);
	if (udata->extra)
	{
		lua_pushlstring(L, (const char*)udata->extra, udata->extra_length);
	}
	else
		lua_pushnil(L);
	return 1;
}

static int luausb_set_config_descriptor_extra(lua_State* L)
{
	struct libusb_config_descriptor* udata;
	if (!lua_isstring(L, 2))
	{
		lua_pushliteral(L, "invalid value for field extra (string expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_config_descriptor(L, 1);
	getuservalue(L, 1);
	lua_pushvalue(L, 2);
	lua_setfield(L, -2, "extra");
	lua_pop(L, 1);
	{
		size_t size;
		udata->extra = (const unsigned char*)lua_tolstring(L, 2, &size);
		udata->extra_length = (int)size;
	}
	return 0;
}

static struct luaL_Reg libusb_config_descriptor__getters[] = {
	{"bLength", luausb_get_config_descriptor_bLength},
	{"bDescriptorType", luausb_get_config_descriptor_bDescriptorType},
	{"wTotalLength", luausb_get_config_descriptor_wTotalLength},
	{"bNumInterfaces", luausb_get_config_descriptor_bNumInterfaces},
	{"bConfigurationValue", luausb_get_config_descriptor_bConfigurationValue},
	{"iConfiguration", luausb_get_config_descriptor_iConfiguration},
	{"bmAttributes", luausb_get_config_descriptor_bmAttributes},
	{"MaxPower", luausb_get_config_descriptor_MaxPower},
	{"interface", luausb_get_config_descriptor_interface},
	{"extra", luausb_get_config_descriptor_extra},
	{0, 0},
};

static struct luaL_Reg libusb_config_descriptor__setters[] = {
	{"bLength", luausb_set_config_descriptor_bLength},
	{"bDescriptorType", luausb_set_config_descriptor_bDescriptorType},
	{"wTotalLength", luausb_set_config_descriptor_wTotalLength},
	{"bNumInterfaces", luausb_set_config_descriptor_bNumInterfaces},
	{"bConfigurationValue", luausb_set_config_descriptor_bConfigurationValue},
	{"iConfiguration", luausb_set_config_descriptor_iConfiguration},
	{"bmAttributes", luausb_set_config_descriptor_bmAttributes},
	{"MaxPower", luausb_set_config_descriptor_MaxPower},
	{"extra", luausb_set_config_descriptor_extra},
	{0, 0},
};
int luausb_config_descriptor_gc(lua_State* L);
static struct luaL_Reg libusb_config_descriptor__metamethods[] = {
	{"__index", luausb_generic_index},
	{"__newindex", luausb_generic_newindex},
	{"__tostring", luausb_generic_tostring},
	{"__gc", luausb_config_descriptor_gc},
	{0, 0},
};
extern struct luaL_Reg libusb_config_descriptor__methods[];

struct libusb_device* luausb_to_device(lua_State* L, int index)
{
	struct libusb_device* udata;
	udata = *(struct libusb_device**)lua_touserdata(L, index);
	if (!udata)
	{
		luaL_argerror(L, index, "context has already been deinitialized");
		return NULL;
	}
	return udata;
}

int luausb_is_device(lua_State* L, int index)
{
	int result = 0;
	void* p = lua_touserdata(L, index);
	/* value is a userdata? */
	if (p != NULL)
	{
		/* does it have a metatable? */
		if (lua_getmetatable(L, index))
		{
			/* get correct metatable */
			lua_getfield(L, LUA_REGISTRYINDEX, "struct libusb_device");
			/* does it have the correct mt? */
			if (lua_rawequal(L, -1, -2))
			{
				result = 1;
			}
			lua_pop(L, 1); /* remove type metatable */
		}
		lua_pop(L, 1); /* remove udata metatable */
	}
	return result;
}

struct libusb_device* luausb_check_device(lua_State* L, int index)
{
	struct libusb_device* udata;
	udata = *(struct libusb_device**)luaL_checkudata(L, index, "struct libusb_device");
	if (!udata)
	{
		luaL_argerror(L, index, "context has already been deinitialized");
		return NULL;
	}
	return udata;
}

void luausb_push_device(lua_State* L, const struct libusb_device* value, int owner)
{
	const struct libusb_device** udata;
	if (owner < 0) owner = lua_gettop(L) + 1 + owner;
	udata = (const struct libusb_device**)lua_newuserdata(L, sizeof(struct libusb_device*));
	*udata = value;
	luaL_getmetatable(L, "struct libusb_device");
	lua_setmetatable(L, -2);
	if (owner != 0)
	{
		lua_createtable(L, 1, 0);
		lua_pushvalue(L, owner);
		lua_rawseti(L, -2, 1);
		setuservalue(L, -2);
	}
}

static struct luaL_Reg libusb_device__getters[] = {
	{0, 0},
};

static struct luaL_Reg libusb_device__setters[] = {
	{0, 0},
};
int luausb_device_gc(lua_State* L);
static struct luaL_Reg libusb_device__metamethods[] = {
	{"__index", luausb_generic_index},
	{"__newindex", luausb_generic_newindex},
	{"__tostring", luausb_generic_tostring},
	{"__gc", luausb_device_gc},
	{0, 0},
};
extern struct luaL_Reg libusb_device__methods[];

struct libusb_device_handle* luausb_to_device_handle(lua_State* L, int index)
{
	struct libusb_device_handle* udata;
	udata = *(struct libusb_device_handle**)lua_touserdata(L, index);
	if (!udata)
	{
		luaL_argerror(L, index, "context has already been deinitialized");
		return NULL;
	}
	return udata;
}

int luausb_is_device_handle(lua_State* L, int index)
{
	int result = 0;
	void* p = lua_touserdata(L, index);
	/* value is a userdata? */
	if (p != NULL)
	{
		/* does it have a metatable? */
		if (lua_getmetatable(L, index))
		{
			/* get correct metatable */
			lua_getfield(L, LUA_REGISTRYINDEX, "struct libusb_device_handle");
			/* does it have the correct mt? */
			if (lua_rawequal(L, -1, -2))
			{
				result = 1;
			}
			lua_pop(L, 1); /* remove type metatable */
		}
		lua_pop(L, 1); /* remove udata metatable */
	}
	return result;
}

struct libusb_device_handle* luausb_check_device_handle(lua_State* L, int index)
{
	struct libusb_device_handle* udata;
	udata = *(struct libusb_device_handle**)luaL_checkudata(L, index, "struct libusb_device_handle");
	if (!udata)
	{
		luaL_argerror(L, index, "context has already been deinitialized");
		return NULL;
	}
	return udata;
}

void luausb_push_device_handle(lua_State* L, const struct libusb_device_handle* value, int owner)
{
	const struct libusb_device_handle** udata;
	if (owner < 0) owner = lua_gettop(L) + 1 + owner;
	udata = (const struct libusb_device_handle**)lua_newuserdata(L, sizeof(struct libusb_device_handle*));
	*udata = value;
	luaL_getmetatable(L, "struct libusb_device_handle");
	lua_setmetatable(L, -2);
	if (owner != 0)
	{
		lua_createtable(L, 1, 0);
		lua_pushvalue(L, owner);
		lua_rawseti(L, -2, 1);
		setuservalue(L, -2);
	}
}

static struct luaL_Reg libusb_device_handle__getters[] = {
	{0, 0},
};

static struct luaL_Reg libusb_device_handle__setters[] = {
	{0, 0},
};
int luausb_device_handle_gc(lua_State* L);
static struct luaL_Reg libusb_device_handle__metamethods[] = {
	{"__index", luausb_generic_index},
	{"__newindex", luausb_generic_newindex},
	{"__tostring", luausb_generic_tostring},
	{"__gc", luausb_device_handle_gc},
	{0, 0},
};
extern struct luaL_Reg libusb_device_handle__methods[];

struct libusb_transfer* luausb_to_transfer(lua_State* L, int index)
{
	struct libusb_transfer* udata;
	udata = *(struct libusb_transfer**)lua_touserdata(L, index);
	if (!udata)
	{
		luaL_argerror(L, index, "context has already been deinitialized");
		return NULL;
	}
	return udata;
}

int luausb_is_transfer(lua_State* L, int index)
{
	int result = 0;
	void* p = lua_touserdata(L, index);
	/* value is a userdata? */
	if (p != NULL)
	{
		/* does it have a metatable? */
		if (lua_getmetatable(L, index))
		{
			/* get correct metatable */
			lua_getfield(L, LUA_REGISTRYINDEX, "struct libusb_transfer");
			/* does it have the correct mt? */
			if (lua_rawequal(L, -1, -2))
			{
				result = 1;
			}
			lua_pop(L, 1); /* remove type metatable */
		}
		lua_pop(L, 1); /* remove udata metatable */
	}
	return result;
}

struct libusb_transfer* luausb_check_transfer(lua_State* L, int index)
{
	struct libusb_transfer* udata;
	udata = *(struct libusb_transfer**)luaL_checkudata(L, index, "struct libusb_transfer");
	if (!udata)
	{
		luaL_argerror(L, index, "context has already been deinitialized");
		return NULL;
	}
	return udata;
}

void luausb_push_transfer(lua_State* L, const struct libusb_transfer* value, int owner)
{
	const struct libusb_transfer** udata;
	if (owner < 0) owner = lua_gettop(L) + 1 + owner;
	udata = (const struct libusb_transfer**)lua_newuserdata(L, sizeof(struct libusb_transfer*));
	*udata = value;
	luaL_getmetatable(L, "struct libusb_transfer");
	lua_setmetatable(L, -2);
	lua_createtable(L, 1, 0);
	if (owner != 0)
	{
		lua_pushvalue(L, owner);
		lua_rawseti(L, -2, 1);
	}
	setuservalue(L, -2);
}

int luausb_get_transfer_dev_handle(lua_State* L);
int luausb_set_transfer_dev_handle(lua_State* L);

static int luausb_get_transfer_flags(lua_State* L)
{
	struct libusb_transfer* udata;
	udata = luausb_to_transfer(L, 1);
	lua_pushnumber(L, udata->flags);
	return 1;
}

static int luausb_set_transfer_flags(lua_State* L)
{
	struct libusb_transfer* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field flags (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_transfer(L, 1);
	value = lua_tonumber(L, 2);
	udata->flags = (uint8_t)value;
	return 0;
}

static int luausb_get_transfer_endpoint(lua_State* L)
{
	struct libusb_transfer* udata;
	udata = luausb_to_transfer(L, 1);
	lua_pushnumber(L, udata->endpoint);
	return 1;
}

static int luausb_set_transfer_endpoint(lua_State* L)
{
	struct libusb_transfer* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field endpoint (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_transfer(L, 1);
	value = lua_tonumber(L, 2);
	udata->endpoint = (unsigned char)value;
	return 0;
}

static int luausb_get_transfer_type(lua_State* L)
{
	struct libusb_transfer* udata;
	udata = luausb_to_transfer(L, 1);
	lua_pushnumber(L, udata->type);
	return 1;
}

static int luausb_set_transfer_type(lua_State* L)
{
	struct libusb_transfer* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field type (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_transfer(L, 1);
	value = lua_tonumber(L, 2);
	udata->type = (unsigned char)value;
	return 0;
}

static int luausb_get_transfer_timeout(lua_State* L)
{
	struct libusb_transfer* udata;
	udata = luausb_to_transfer(L, 1);
	lua_pushnumber(L, udata->timeout);
	return 1;
}

static int luausb_set_transfer_timeout(lua_State* L)
{
	struct libusb_transfer* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field timeout (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_transfer(L, 1);
	value = lua_tonumber(L, 2);
	udata->timeout = (unsigned int)value;
	return 0;
}

static int luausb_get_transfer_status(lua_State* L)
{
	struct libusb_transfer* udata;
	udata = luausb_to_transfer(L, 1);
	lua_pushnumber(L, udata->status);
	return 1;
}

static int luausb_set_transfer_status(lua_State* L)
{
	struct libusb_transfer* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field status (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_transfer(L, 1);
	value = lua_tonumber(L, 2);
	udata->status = (enum libusb_transfer_status)value;
	return 0;
}

static int luausb_get_transfer_actual_length(lua_State* L)
{
	struct libusb_transfer* udata;
	udata = luausb_to_transfer(L, 1);
	lua_pushnumber(L, udata->actual_length);
	return 1;
}

static int luausb_set_transfer_actual_length(lua_State* L)
{
	struct libusb_transfer* udata;
	lua_Number value;
	if (!lua_isnumber(L, 2))
	{
		lua_pushliteral(L, "invalid value for field actual_length (number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	udata = luausb_to_transfer(L, 1);
	value = lua_tonumber(L, 2);
	udata->actual_length = (int)value;
	return 0;
}

int luausb_get_transfer_callback(lua_State* L);
int luausb_set_transfer_callback(lua_State* L);

static int luausb_get_transfer_buffer(lua_State* L)
{
	struct libusb_transfer* udata;
	udata = luausb_to_transfer(L, 1);
	if (udata->buffer)
	{
		lua_pushlstring(L, (const char*)udata->buffer, udata->length);
	}
	else
		lua_pushnil(L);
	return 1;
}

static int luausb_set_transfer_buffer(lua_State* L)
{
	struct libusb_transfer* udata;
	udata = luausb_to_transfer(L, 1);
	if (lua_type(L, 2)==LUA_TSTRING)
	{
		const char* value;
		size_t size;
		char* buffer;
		value = lua_tolstring(L, 2, &size);
		getuservalue(L, 1);
		buffer = lua_newuserdata(L, size);
		lua_setfield(L, -2, "buffer");
		lua_pop(L, 1);
		memcpy(buffer, value, size);
		udata->buffer = (unsigned char*)buffer;
		udata->length = (int)size;
	}
	else if (lua_type(L, 2)==LUA_TNUMBER)
	{
		size_t size;
		char* buffer;
		size = (size_t)lua_tonumber(L, 2); /* :FIXME: handle overflow */
		getuservalue(L, 1);
		buffer = lua_newuserdata(L, size);
		lua_setfield(L, -2, "buffer");
		lua_pop(L, 1);
		memset(buffer, 0, size);
		udata->buffer = (unsigned char*)buffer;
		udata->length = (int)size;
	}
	else
	{
		lua_pushliteral(L, "invalid value for field buffer (string or number expected, got ");
		lua_pushstring(L, luaL_typename(L, 2));
		lua_pushliteral(L, ")");
		lua_concat(L, 3);
		return lua_error(L);
	}
	return 0;
}

static struct luaL_Reg libusb_transfer__getters[] = {
	{"dev_handle", luausb_get_transfer_dev_handle},
	{"flags", luausb_get_transfer_flags},
	{"endpoint", luausb_get_transfer_endpoint},
	{"type", luausb_get_transfer_type},
	{"timeout", luausb_get_transfer_timeout},
	{"status", luausb_get_transfer_status},
	{"actual_length", luausb_get_transfer_actual_length},
	{"callback", luausb_get_transfer_callback},
	{"buffer", luausb_get_transfer_buffer},
	{0, 0},
};

static struct luaL_Reg libusb_transfer__setters[] = {
	{"dev_handle", luausb_set_transfer_dev_handle},
	{"flags", luausb_set_transfer_flags},
	{"endpoint", luausb_set_transfer_endpoint},
	{"type", luausb_set_transfer_type},
	{"timeout", luausb_set_transfer_timeout},
	{"status", luausb_set_transfer_status},
	{"actual_length", luausb_set_transfer_actual_length},
	{"callback", luausb_set_transfer_callback},
	{"buffer", luausb_set_transfer_buffer},
	{0, 0},
};
int luausb_transfer_gc(lua_State* L);
static struct luaL_Reg libusb_transfer__metamethods[] = {
	{"__index", luausb_generic_index},
	{"__newindex", luausb_generic_newindex},
	{"__tostring", luausb_generic_tostring},
	{"__gc", luausb_transfer_gc},
	{0, 0},
};
extern struct luaL_Reg libusb_transfer__methods[];

void luausb_init_structs(lua_State* L)
{
	/* device_descriptor */
	luaL_newmetatable(L, "struct libusb_device_descriptor");
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_device_descriptor__metamethods, 1);
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_device_descriptor__methods, 1);
	lua_setfield(L, -2, "methods");
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_device_descriptor__getters, 1);
	lua_setfield(L, -2, "getters");
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_device_descriptor__setters, 1);
	lua_setfield(L, -2, "setters");
	lua_pushliteral(L, "device_descriptor");
	lua_setfield(L, -2, "typename");
	lua_pop(L, 1);
	/* endpoint_descriptor */
	luaL_newmetatable(L, "struct libusb_endpoint_descriptor");
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_endpoint_descriptor__metamethods, 1);
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_endpoint_descriptor__methods, 1);
	lua_setfield(L, -2, "methods");
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_endpoint_descriptor__getters, 1);
	lua_setfield(L, -2, "getters");
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_endpoint_descriptor__setters, 1);
	lua_setfield(L, -2, "setters");
	lua_pushliteral(L, "endpoint_descriptor");
	lua_setfield(L, -2, "typename");
	lua_pop(L, 1);
	/* interface_descriptor */
	luaL_newmetatable(L, "struct libusb_interface_descriptor");
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_interface_descriptor__metamethods, 1);
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_interface_descriptor__methods, 1);
	lua_setfield(L, -2, "methods");
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_interface_descriptor__getters, 1);
	lua_setfield(L, -2, "getters");
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_interface_descriptor__setters, 1);
	lua_setfield(L, -2, "setters");
	lua_pushliteral(L, "interface_descriptor");
	lua_setfield(L, -2, "typename");
	lua_pop(L, 1);
	/* interface */
	luaL_newmetatable(L, "struct libusb_interface");
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_interface__metamethods, 1);
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_interface__methods, 1);
	lua_setfield(L, -2, "methods");
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_interface__getters, 1);
	lua_setfield(L, -2, "getters");
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_interface__setters, 1);
	lua_setfield(L, -2, "setters");
	lua_pushliteral(L, "interface");
	lua_setfield(L, -2, "typename");
	lua_pop(L, 1);
	/* config_descriptor */
	luaL_newmetatable(L, "struct libusb_config_descriptor");
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_config_descriptor__metamethods, 1);
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_config_descriptor__methods, 1);
	lua_setfield(L, -2, "methods");
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_config_descriptor__getters, 1);
	lua_setfield(L, -2, "getters");
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_config_descriptor__setters, 1);
	lua_setfield(L, -2, "setters");
	lua_pushliteral(L, "config_descriptor");
	lua_setfield(L, -2, "typename");
	lua_pop(L, 1);
	/* device */
	luaL_newmetatable(L, "struct libusb_device");
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_device__metamethods, 1);
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_device__methods, 1);
	lua_setfield(L, -2, "methods");
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_device__getters, 1);
	lua_setfield(L, -2, "getters");
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_device__setters, 1);
	lua_setfield(L, -2, "setters");
	lua_pushliteral(L, "device");
	lua_setfield(L, -2, "typename");
	lua_pop(L, 1);
	/* device_handle */
	luaL_newmetatable(L, "struct libusb_device_handle");
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_device_handle__metamethods, 1);
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_device_handle__methods, 1);
	lua_setfield(L, -2, "methods");
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_device_handle__getters, 1);
	lua_setfield(L, -2, "getters");
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_device_handle__setters, 1);
	lua_setfield(L, -2, "setters");
	lua_pushliteral(L, "device_handle");
	lua_setfield(L, -2, "typename");
	lua_pop(L, 1);
	/* transfer */
	luaL_newmetatable(L, "struct libusb_transfer");
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_transfer__metamethods, 1);
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_transfer__methods, 1);
	lua_setfield(L, -2, "methods");
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_transfer__getters, 1);
	lua_setfield(L, -2, "getters");
	lua_newtable(L);
	lua_pushvalue(L, 1);
	setfuncs(L, libusb_transfer__setters, 1);
	lua_setfield(L, -2, "setters");
	lua_pushliteral(L, "transfer");
	lua_setfield(L, -2, "typename");
	lua_pop(L, 1);
}
