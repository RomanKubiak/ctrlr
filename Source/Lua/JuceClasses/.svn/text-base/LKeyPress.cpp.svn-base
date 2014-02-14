#include "stdafx.h"
#include "LKeyPress.h"

void LKeyPress::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<KeyPress>("JKeyPress")
		,
		class_<LKeyPress, bases<KeyPress> >("KeyPress")
			.def(constructor<>())
			.def(constructor<int>())
			.def(constructor<int, const ModifierKeys &, juce_wchar>())
			.enum_("KeyCode")
			[
				value("spaceKey", KeyPress::spaceKey),
				value("escapeKey", KeyPress::escapeKey),
				value("returnKey", KeyPress::returnKey),
				value("tabKey", KeyPress::tabKey),
				value("deleteKey", KeyPress::deleteKey),
				value("backspaceKey", KeyPress::backspaceKey),
				value("insertKey", KeyPress::insertKey),
				value("upKey", KeyPress::upKey),
				value("downKey", KeyPress::downKey),
				value("leftKey", KeyPress::leftKey),
				value("rightKey", KeyPress::rightKey)
			]
	];
}