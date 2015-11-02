#ifndef L_TEXT_BUTTON
#define L_TEXT_BUTTON

extern  "C"
{
	#include "lua.h"
}

class LTextButton
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
