/* this is a generated file, see gen.lua */
#include "lua.h"
#include "libusb.h"

enum libusb_class_code luausb_to_class_code(lua_State* L, int index);
int luausb_is_class_code(lua_State* L, int index);
enum libusb_class_code luausb_check_class_code(lua_State* L, int narg);
enum libusb_class_code luausb_opt_class_code(lua_State* L, int narg, enum libusb_class_code d);
enum libusb_descriptor_type luausb_to_descriptor_type(lua_State* L, int index);
int luausb_is_descriptor_type(lua_State* L, int index);
enum libusb_descriptor_type luausb_check_descriptor_type(lua_State* L, int narg);
enum libusb_descriptor_type luausb_opt_descriptor_type(lua_State* L, int narg, enum libusb_descriptor_type d);
enum libusb_endpoint_direction luausb_to_endpoint_direction(lua_State* L, int index);
int luausb_is_endpoint_direction(lua_State* L, int index);
enum libusb_endpoint_direction luausb_check_endpoint_direction(lua_State* L, int narg);
enum libusb_endpoint_direction luausb_opt_endpoint_direction(lua_State* L, int narg, enum libusb_endpoint_direction d);
enum libusb_transfer_type luausb_to_transfer_type(lua_State* L, int index);
int luausb_is_transfer_type(lua_State* L, int index);
enum libusb_transfer_type luausb_check_transfer_type(lua_State* L, int narg);
enum libusb_transfer_type luausb_opt_transfer_type(lua_State* L, int narg, enum libusb_transfer_type d);
enum libusb_iso_sync_type luausb_to_iso_sync_type(lua_State* L, int index);
int luausb_is_iso_sync_type(lua_State* L, int index);
enum libusb_iso_sync_type luausb_check_iso_sync_type(lua_State* L, int narg);
enum libusb_iso_sync_type luausb_opt_iso_sync_type(lua_State* L, int narg, enum libusb_iso_sync_type d);
enum libusb_iso_usage_type luausb_to_iso_usage_type(lua_State* L, int index);
int luausb_is_iso_usage_type(lua_State* L, int index);
enum libusb_iso_usage_type luausb_check_iso_usage_type(lua_State* L, int narg);
enum libusb_iso_usage_type luausb_opt_iso_usage_type(lua_State* L, int narg, enum libusb_iso_usage_type d);
enum libusb_standard_request luausb_to_standard_request(lua_State* L, int index);
int luausb_is_standard_request(lua_State* L, int index);
enum libusb_standard_request luausb_check_standard_request(lua_State* L, int narg);
enum libusb_standard_request luausb_opt_standard_request(lua_State* L, int narg, enum libusb_standard_request d);
enum libusb_request_type luausb_to_request_type(lua_State* L, int index);
int luausb_is_request_type(lua_State* L, int index);
enum libusb_request_type luausb_check_request_type(lua_State* L, int narg);
enum libusb_request_type luausb_opt_request_type(lua_State* L, int narg, enum libusb_request_type d);
enum libusb_request_recipient luausb_to_request_recipient(lua_State* L, int index);
int luausb_is_request_recipient(lua_State* L, int index);
enum libusb_request_recipient luausb_check_request_recipient(lua_State* L, int narg);
enum libusb_request_recipient luausb_opt_request_recipient(lua_State* L, int narg, enum libusb_request_recipient d);
enum libusb_error luausb_to_error(lua_State* L, int index);
int luausb_is_error(lua_State* L, int index);
enum libusb_error luausb_check_error(lua_State* L, int narg);
enum libusb_error luausb_opt_error(lua_State* L, int narg, enum libusb_error d);
enum libusb_transfer_status luausb_to_transfer_status(lua_State* L, int index);
int luausb_is_transfer_status(lua_State* L, int index);
enum libusb_transfer_status luausb_check_transfer_status(lua_State* L, int narg);
enum libusb_transfer_status luausb_opt_transfer_status(lua_State* L, int narg, enum libusb_transfer_status d);
void luausb_init_enums(lua_State* L);
