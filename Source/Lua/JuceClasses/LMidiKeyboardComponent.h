#ifndef L_MIDI_KEYBOARD_COMPONENT
#define L_MIDI_KEYBOARD_COMPONENT

extern  "C"
{
	#include "lua.h"
}

class LMidiKeyboardComponent
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
