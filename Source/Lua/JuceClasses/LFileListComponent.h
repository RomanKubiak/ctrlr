#ifndef L_FILE_LIST_COMPONENT
#define L_FILE_LIST_COMPONENT

extern  "C"
{
	#include "lua.h"
}

class LFileListComponent
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
