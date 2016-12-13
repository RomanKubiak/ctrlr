#include "lua.h"
#include "lauxlib.h"


int typeerror(lua_State* L, int narg, const char* tname);
#define setfuncs luaL_setfuncs
#define setuservalue lua_setuservalue
#define getuservalue lua_getuservalue