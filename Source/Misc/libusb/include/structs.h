/* this is a generated file, see gen.lua */
#include "lua.h"
#include "libusb.h"

struct libusb_device_descriptor* luausb_to_device_descriptor(lua_State* L, int index);
int luausb_is_device_descriptor(lua_State* L, int index);
struct libusb_device_descriptor* luausb_check_device_descriptor(lua_State* L, int index);
void luausb_push_device_descriptor(lua_State* L, const struct libusb_device_descriptor* value, int owner);
struct libusb_endpoint_descriptor* luausb_to_endpoint_descriptor(lua_State* L, int index);
int luausb_is_endpoint_descriptor(lua_State* L, int index);
struct libusb_endpoint_descriptor* luausb_check_endpoint_descriptor(lua_State* L, int index);
void luausb_push_endpoint_descriptor(lua_State* L, const struct libusb_endpoint_descriptor* value, int owner);
struct libusb_interface_descriptor* luausb_to_interface_descriptor(lua_State* L, int index);
int luausb_is_interface_descriptor(lua_State* L, int index);
struct libusb_interface_descriptor* luausb_check_interface_descriptor(lua_State* L, int index);
void luausb_push_interface_descriptor(lua_State* L, const struct libusb_interface_descriptor* value, int owner);
struct libusb_interface* luausb_to_interface(lua_State* L, int index);
int luausb_is_interface(lua_State* L, int index);
struct libusb_interface* luausb_check_interface(lua_State* L, int index);
void luausb_push_interface(lua_State* L, const struct libusb_interface* value, int owner);
struct libusb_config_descriptor* luausb_to_config_descriptor(lua_State* L, int index);
int luausb_is_config_descriptor(lua_State* L, int index);
struct libusb_config_descriptor* luausb_check_config_descriptor(lua_State* L, int index);
void luausb_push_config_descriptor(lua_State* L, const struct libusb_config_descriptor* value, int owner);
struct libusb_device* luausb_to_device(lua_State* L, int index);
int luausb_is_device(lua_State* L, int index);
struct libusb_device* luausb_check_device(lua_State* L, int index);
void luausb_push_device(lua_State* L, const struct libusb_device* value, int owner);
struct libusb_device_handle* luausb_to_device_handle(lua_State* L, int index);
int luausb_is_device_handle(lua_State* L, int index);
struct libusb_device_handle* luausb_check_device_handle(lua_State* L, int index);
void luausb_push_device_handle(lua_State* L, const struct libusb_device_handle* value, int owner);
struct libusb_transfer* luausb_to_transfer(lua_State* L, int index);
int luausb_is_transfer(lua_State* L, int index);
struct libusb_transfer* luausb_check_transfer(lua_State* L, int index);
void luausb_push_transfer(lua_State* L, const struct libusb_transfer* value, int owner);
void luausb_init_structs(lua_State* L);
