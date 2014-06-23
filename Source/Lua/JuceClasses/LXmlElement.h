#ifndef LXMLELEMENT_H_INCLUDED
#define LXMLELEMENT_H_INCLUDED

#include "CtrlrLuaManager.h"

class LXmlElement
{
	public:
		static void wrapForLua (lua_State *L);
};


#endif  // LXMLELEMENT_H_INCLUDED
