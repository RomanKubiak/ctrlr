#ifndef L_BUTTON
#define L_BUTTON

extern  "C"
{
	#include "lua.h"
}

class LButton
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
