#ifndef __L_ATTRIBUTED_STRING__
#define __L_ATTRIBUTED_STRING__

#include "CtrlrLuaManager.h"

class LAttributedString
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif