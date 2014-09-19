#ifndef __L_RECTANGLE__
#define __L_RECTANGLE__

#include "CtrlrLuaManager.h"
#ifdef _WIN32
#pragma warning(disable:4244)
#endif
class LRectangle
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
