#ifndef L_AUDIO_SAMPLE_BUFFER
#define L_AUDIO_SAMPLE_BUFFER

extern  "C"
{
	#include "lua.h"
}

class LAudioSampleBuffer
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
