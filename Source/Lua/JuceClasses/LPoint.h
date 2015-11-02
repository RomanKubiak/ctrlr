#ifndef L_POINT
#define L_POINT

extern  "C"
{
	#include "lua.h"
}

class LPoint
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
