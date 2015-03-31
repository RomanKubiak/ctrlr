#ifndef __L_AUDIO_PLAYHEAD__
#define __L_AUDIO_PLAYHEAD__

#include "CtrlrLuaManager.h"

class LAudioPlayHead
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
