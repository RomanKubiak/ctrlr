#include "stdafx.h"
#include "LLookAndFeel.h"

void LLookAndFeel::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
	[
		class_<LookAndFeelBase, LLookAndFeel>("LookAndFeel")
			.def(constructor<>())
	];
}
