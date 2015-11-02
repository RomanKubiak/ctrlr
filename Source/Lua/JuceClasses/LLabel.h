#ifndef L_LABEL
#define L_LABEL

extern  "C"
{
	#include "lua.h"
}

class LLabel
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
