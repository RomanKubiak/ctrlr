#include "stdafx.h"
#include "CtrlrLuaSocket.h"

extern "C"
{
	#include "LuaSocket/include/luasocket.h"
	#include "LuaSocket/include/mime.h"
}

#define LUA_LOAD_BUFFER(embed) luaL_loadbuffer (L, BinaryData::embed, BinaryData::embed ## Size, _STR(#embed).replace ("_", ".").toUTF8())

void CtrlrLuaSocket::wrapForLua (lua_State *L)
{
luaL_findtable(L, LUA_GLOBALSINDEX, "package.preload", 3);
lua_pushcfunction(L, luaopen_socket_core);
lua_setfield(L, -2, "socket.core");
lua_pushcfunction(L, luaopen_mime_core);
lua_setfield(L, -2, "mime.core");
lua_pushcfunction(L, luaopen_ltn12);
lua_setfield(L, -2, "ltn12");
lua_pushcfunction(L, luaopen_mime);
lua_setfield(L, -2, "mime");
lua_pushcfunction(L, luaopen_socket);
lua_setfield(L, -2, "socket");
lua_pushcfunction(L, luaopen_socket_ftp);
lua_setfield(L, -2, "socket.ftp");
lua_pushcfunction(L, luaopen_socket_http);
lua_setfield(L, -2, "socket.http");
lua_pushcfunction(L, luaopen_socket_smtp);
lua_setfield(L, -2, "socket.smtp");
lua_pushcfunction(L, luaopen_socket_tp);
lua_setfield(L, -2, "socket.tp");
lua_pushcfunction(L, luaopen_socket_url);
lua_setfield(L, -2, "socket.url");
lua_pop(L, 1);
}

LUAOPEN_API int luaopen_ltn12(lua_State *L) {
int arg = lua_gettop(L);
// luaL_loadbuffer(L,(const char*)B1,sizeof(B1),"ltn12.lua");
LUA_LOAD_BUFFER (ltn12_lua);
lua_insert(L,1);
lua_call(L,arg,1);
return 1;
}

LUAOPEN_API int luaopen_mime(lua_State *L) {
int arg = lua_gettop(L);
//luaL_loadbuffer(L,(const char*)B2,sizeof(B2),"mime.lua");
LUA_LOAD_BUFFER (mime_lua);
lua_insert(L,1);
lua_call(L,arg,1);
return 1;
}
LUAOPEN_API int luaopen_socket(lua_State *L) {
int arg = lua_gettop(L);
//luaL_loadbuffer(L,(const char*)B3,sizeof(B3),"socket.lua");
LUA_LOAD_BUFFER (socket_lua);
lua_insert(L,1);
lua_call(L,arg,1);
return 1;
}
LUAOPEN_API int luaopen_socket_ftp(lua_State *L) {
int arg = lua_gettop(L);
//luaL_loadbuffer(L,(const char*)B4,sizeof(B4),"socket/ftp.lua");
LUA_LOAD_BUFFER (ftp_lua);
lua_insert(L,1);
lua_call(L,arg,1);
return 1;
}
LUAOPEN_API int luaopen_socket_http(lua_State *L) {
int arg = lua_gettop(L);
//luaL_loadbuffer(L,(const char*)B5,sizeof(B5),"socket/http.lua");
LUA_LOAD_BUFFER (http_lua);
lua_insert(L,1);
lua_call(L,arg,1);
return 1;
}
LUAOPEN_API int luaopen_socket_smtp(lua_State *L) {
int arg = lua_gettop(L);
// luaL_loadbuffer(L,(const char*)B6,sizeof(B6),"socket/smtp.lua");
LUA_LOAD_BUFFER (smtp_lua);
lua_insert(L,1);
lua_call(L,arg,1);
return 1;
}
LUAOPEN_API int luaopen_socket_tp(lua_State *L) {
int arg = lua_gettop(L);
//luaL_loadbuffer(L,(const char*)B7,sizeof(B7),"socket/tp.lua");
LUA_LOAD_BUFFER (tp_lua);
lua_insert(L,1);
lua_call(L,arg,1);
return 1;
}
LUAOPEN_API int luaopen_socket_url(lua_State *L) {
int arg = lua_gettop(L);
//luaL_loadbuffer(L,(const char*)B8,sizeof(B8),"socket/url.lua");
LUA_LOAD_BUFFER (url_lua);
lua_insert(L,1);
lua_call(L,arg,1);
return 1;
}
