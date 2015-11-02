#ifndef L_MODIFIER_KEYS
#define L_MODIFIER_KEYS

extern  "C"
{
	#include "lua.h"
}

class LModifierKeys
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
