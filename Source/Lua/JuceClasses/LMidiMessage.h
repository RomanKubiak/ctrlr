#ifndef L_MIDI_MESSAGE
#define L_MIDI_MESSAGE

extern  "C"
{
	#include "lua.h"
}

class LMidiMessage
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
