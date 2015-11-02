#ifndef L_FONT
#define L_FONT

extern  "C"
{
	#include "lua.h"
}

class LFont : public Font
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
