#include "lua.h"
#include "lauxlib.h"

/****************************************************************************/

#if LUA_VERSION_NUM>=502

int typeerror(lua_State* L, int narg, const char* tname);
#define setfuncs luaL_setfuncs
#define setuservalue lua_setuservalue
#define getuservalue lua_getuservalue

#elif LUA_VERSION_NUM==501

#define typeerror luaL_typerror
void setfuncs(lua_State* L, const luaL_Reg* l, int nup);
#define setuservalue lua_setfenv
#define getuservalue lua_getfenv

#endif
