#include <lua.h>
#include "compat.h"

/****************************************************************************/

#if LUA_VERSION_NUM>=502

int typeerror(lua_State* L, int narg, const char* tname)
{
	const char* msg = lua_pushfstring(L, "%s expected, got %s", tname, luaL_typename(L, narg));
	return luaL_argerror(L, narg, msg);
}

#endif

/****************************************************************************/

#if LUA_VERSION_NUM==501

void setfuncs(lua_State* L, const luaL_Reg* l, int nup)
{
	luaL_checkstack(L, nup, "too many upvalues");
	for (; l->name; ++l) /* fill the table with given functions */
	{
		int i;
		for (i = 0; i < nup; ++i) /* copy upvalues to the top */
			lua_pushvalue(L, -nup);
		lua_pushcclosure(L, l->func, nup); /* closure with those upvalues */
		lua_setfield(L, -(nup + 2), l->name);
	}
	lua_pop(L, nup); /* remove upvalues */
}

#endif

/****************************************************************************/

#if LUA_VERSION_NUM<=502

int lua_isinteger(lua_State* L, int idx)
{
	return ((lua_Number)lua_tointeger(L, idx)) == lua_tonumber(L, idx);
}

#endif

