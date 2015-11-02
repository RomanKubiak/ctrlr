#ifndef L_COLOUR_GRADIENT
#define L_COLOUR_GRADIENT

extern  "C"
{
	#include "lua.h"
}

class LColourGradient
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
