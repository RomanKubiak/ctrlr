#ifndef __L_FILE_TREE_COMPONENT__
#define __L_FILE_TREE_COMPONENT__

#include "CtrlrLuaManager.h"

class LFileTreeComponent
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif