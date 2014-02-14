#ifndef __L_IMAGE__
#define __L_IMAGE__

#include "CtrlrLuaManager.h"

class LImage
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif