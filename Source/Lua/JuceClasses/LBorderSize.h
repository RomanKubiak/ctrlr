#ifndef L_BORDERSIZE
#define L_BORDERSIZE

extern  "C"
{
	#include "lua.h"
}

class LBorderSize
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
