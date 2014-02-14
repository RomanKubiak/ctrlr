#include "stdafx.h"
#include "LMidiKeyboardComponent.h"

void LMidiKeyboardComponent::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<MidiKeyboardComponent>("MidiKeyboardComponent")
	];
}