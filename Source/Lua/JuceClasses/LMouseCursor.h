#ifndef L_MOUSE_CURSOR
#define L_MOUSE_CURSOR

#include "CtrlrLuaManager.h"

class LMouseCursor
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
