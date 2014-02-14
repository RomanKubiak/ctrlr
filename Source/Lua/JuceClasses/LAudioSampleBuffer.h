#ifndef __L_AUDIO_SAMPLE_BUFFER__
#define __L_AUDIO_SAMPLE_BUFFER__

#include "CtrlrLuaManager.h"

class LAudioSampleBuffer
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif