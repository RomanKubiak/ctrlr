#ifndef L_RANGE
#define L_RANGE

extern  "C"
{
	#include "lua.h"
}

#ifdef _WIN32
#pragma warning(disable:4244)
#endif

class LRange
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
