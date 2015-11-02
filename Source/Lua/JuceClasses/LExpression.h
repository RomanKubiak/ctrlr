#ifndef L_EXPRESSION
#define L_EXPRESSION

extern  "C"
{
	#include "lua.h"
}

class LExpression
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
