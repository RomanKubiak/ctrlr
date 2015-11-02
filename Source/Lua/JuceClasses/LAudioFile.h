#ifndef L_AUDIO_FILE
#define L_AUDIO_FILE

extern  "C"
{
	#include "lua.h"
}

class LAudioFile
{
	public:
		static void wrapForLua(lua_State *L);
};

#endif
