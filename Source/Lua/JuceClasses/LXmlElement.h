#ifndef LXMLELEMENT_H_INCLUDED
#define LXMLELEMENT_H_INCLUDED

extern  "C"
{
	#include "lua.h"
}

class LXmlElement
{
	public:
		static void wrapForLua (lua_State *L);
};


#endif  // LXMLELEMENT_H_INCLUDED
