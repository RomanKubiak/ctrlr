#ifndef L_TYPEFACE
#define L_TYPEFACE

extern  "C"
{
	#include "lua.h"
}

class LTypeface
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
