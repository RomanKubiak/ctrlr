#ifndef L_MOUSE_CURSOR
#define L_MOUSE_CURSOR

extern  "C"
{
	#include "lua.h"
}

class LMouseCursor
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
