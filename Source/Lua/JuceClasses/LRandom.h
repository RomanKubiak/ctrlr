#ifndef L_RANDOM
#define L_RANDOM

extern  "C"
{
	#include "lua.h"
}

class LRandom
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
