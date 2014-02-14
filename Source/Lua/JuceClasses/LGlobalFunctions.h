#ifndef __L_GLOBAL_FUNCTIONS__
#define __L_GLOBAL_FUNCTIONS__

#include "CtrlrLuaManager.h"

class LGlobalFunctions
{
	public:
		LGlobalFunctions();
		static double double_Pi();
		static float float_Pi();
		static void wrapForLua (lua_State *L);
		
};

#endif