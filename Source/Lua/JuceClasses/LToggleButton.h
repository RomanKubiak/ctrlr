#ifndef L_TOGGLE_BUTTON
#define L_TOGGLE_BUTTON

extern  "C"
{
	#include "lua.h"
}

class LToggleButton
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
