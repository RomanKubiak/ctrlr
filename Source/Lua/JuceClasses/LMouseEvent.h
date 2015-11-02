#ifndef L_MOUSE_EVENT
#define L_MOUSE_EVENT

extern  "C"
{
	#include "lua.h"
}

class LMouseEvent
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
