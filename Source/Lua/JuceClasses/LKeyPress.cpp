#include "stdafx.h"
#include "LKeyPress.h"

void LKeyPress::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<KeyPress>("KeyPress")
			.def(constructor<>())
			.def(constructor<int>())
			.def(constructor<int, const ModifierKeys &, juce_wchar>())
			.def("isValid", &KeyPress::isValid)
			.def("getKeyCode", &KeyPress::getKeyCode)
			.def("getModifiers", &KeyPress::getModifiers)
			.def("getTextCharacter", &KeyPress::getTextCharacter)
			.def("isKeyCode", &KeyPress::isKeyCode)
			.def("getTextDescription", &KeyPress::getTextDescription)
			.def("getTextDescriptionWithIcons", &KeyPress::getTextDescriptionWithIcons)
			.def("isCurrentlyDown", &KeyPress::isCurrentlyDown)
			.scope
			[
                def("createFromDescription", &KeyPress::createFromDescription),
                def("isKeyCurrentlyDown", &KeyPress::isKeyCurrentlyDown)
			]
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
