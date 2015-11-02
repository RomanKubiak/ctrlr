#ifndef L_COMPONENT_PEER
#define L_COMPONENT_PEER

extern  "C"
{
	#include "lua.h"
}

class LComponentPeer
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
