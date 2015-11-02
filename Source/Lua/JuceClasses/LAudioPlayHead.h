#ifndef L_AUDIO_PLAYHEAD
#define L_AUDIO_PLAYHEAD

extern  "C"
{
	#include "lua.h"
}

class LAudioPlayHead
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
