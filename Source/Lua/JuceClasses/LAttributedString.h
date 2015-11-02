#ifndef L_ATTRIBUTED_STRING
#define L_ATTRIBUTED_STRING

extern  "C"
{
	#include "lua.h"
}

class LAttributedString
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
