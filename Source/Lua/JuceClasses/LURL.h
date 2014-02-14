#ifndef __L_URL__
#define __L_URL__

#include "CtrlrLuaManager.h"

class LURL
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif