#ifndef L_SLIDER
#define L_SLIDER

extern  "C"
{
	#include "lua.h"
}

class LSlider
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
