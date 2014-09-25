#ifndef CTRLR_LUA_SOCKET
#define CTRLR_LUA_SOCKET

#include "CtrlrMacros.h"

#ifndef LUAOPEN_API
#define LUAOPEN_API
#endif

LUAOPEN_API int luaopen_ltn12(lua_State *L);
LUAOPEN_API int luaopen_mime(lua_State *L);
LUAOPEN_API int luaopen_socket(lua_State *L);
LUAOPEN_API int luaopen_socket_ftp(lua_State *L);
LUAOPEN_API int luaopen_socket_http(lua_State *L);
LUAOPEN_API int luaopen_socket_smtp(lua_State *L);
LUAOPEN_API int luaopen_socket_tp(lua_State *L);
LUAOPEN_API int luaopen_socket_url(lua_State *L);

class CtrlrLuaSocket
{
    public:
        static void wrapForLua (lua_State *L);
};
#endif
