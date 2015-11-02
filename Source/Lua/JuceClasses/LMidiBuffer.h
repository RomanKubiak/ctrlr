#ifndef L_MIDI_BUFFER
#define L_MIDI_BUFFER

extern  "C"
{
	#include "lua.h"
}

class LMidiBuffer
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
