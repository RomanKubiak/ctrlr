#ifndef __L_TEXT_EDITOR__
#define __L_TEXT_EDITOR__

#include "CtrlrLuaManager.h"

class LTextEditor
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif