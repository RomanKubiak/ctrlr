#ifndef __L_RANGE__
#define __L_RANGE__

#include "CtrlrLuaManager.h"

#pragma warning(disable:4244)

class LRange
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif