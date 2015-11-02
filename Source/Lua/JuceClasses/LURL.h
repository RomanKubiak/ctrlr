#ifndef L_URL
#define L_URL

extern  "C"
{
	#include "lua.h"
}

class LURL
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
