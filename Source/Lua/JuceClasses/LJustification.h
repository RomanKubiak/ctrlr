#ifndef L_JUSTIFICATION
#define L_JUSTIFICATION

extern  "C"
{
	#include "lua.h"
}

class LJustification
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
