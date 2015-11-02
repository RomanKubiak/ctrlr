#ifndef L_COLOUR
#define L_COLOUR

extern  "C"
{
	#include "lua.h"
}

class LColour
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
