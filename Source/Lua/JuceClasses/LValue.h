#ifndef L_VALUE
#define L_VALUE

extern  "C"
{
	#include "lua.h"
}

class LValue
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
