#ifndef L_FILE_TREE_COMPONENT
#define L_FILE_TREE_COMPONENT

extern  "C"
{
	#include "lua.h"
}

class LFileTreeComponent
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
