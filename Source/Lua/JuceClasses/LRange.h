#ifndef __L_RANGE__
#define __L_RANGE__

#include "CtrlrLuaManager.h"
#ifdef _WIN32
#pragma warning(disable:4244)
#endif
class LRange
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
