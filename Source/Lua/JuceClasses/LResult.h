#ifndef L_RESULT
#define L_RESULT

extern  "C"
{
	#include "lua.h"
}

class LResult
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
