#ifndef L_TEXT_EDITOR
#define L_TEXT_EDITOR

extern  "C"
{
	#include "lua.h"
}

class LTextEditor
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
