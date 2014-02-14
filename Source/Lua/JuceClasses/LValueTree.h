#ifndef __L_VALUE_TREE__
#define __L_VALUE_TREE__

#include "CtrlrLuaManager.h"

class LValueTree
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif