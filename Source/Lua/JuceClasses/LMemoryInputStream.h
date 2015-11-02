#ifndef L_MEMORY_INPUT_STREAM
#define L_MEMORY_INPUT_STREAM

extern  "C"
{
	#include "lua.h"
}

class LMemoryInputStream
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
