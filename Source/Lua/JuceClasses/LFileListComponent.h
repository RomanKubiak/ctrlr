#ifndef __L_FILE_LIST_COMPONENT__
#define __L_FILE_LIST_COMPONENT__

#include "CtrlrLuaManager.h"

class LFileListComponent
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif