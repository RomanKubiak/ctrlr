#ifndef L_GRAPHICS
#define L_GRAPHICS

extern  "C"
{
	#include "lua.h"
}

class LGraphics
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
