#ifndef __L_STRING__
#define __L_STRING__

#include "CtrlrLuaManager.h"

class LString
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif