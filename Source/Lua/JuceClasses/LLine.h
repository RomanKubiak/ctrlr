#ifndef L_LINE
#define L_LINE

extern  "C"
{
	#include "lua.h"
}

class LLine
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
