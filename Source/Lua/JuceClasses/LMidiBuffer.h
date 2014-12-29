#ifndef L_MIDI_BUFFER
#define L_MIDI_BUFFER

#include "CtrlrLuaManager.h"

class LMidiBuffer
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
