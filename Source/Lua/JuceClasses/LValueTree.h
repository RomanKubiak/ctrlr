#ifndef L_VALUE_TREE
#define L_VALUE_TREE

extern  "C"
{
	#include "lua.h"
}

class LValueTree
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
