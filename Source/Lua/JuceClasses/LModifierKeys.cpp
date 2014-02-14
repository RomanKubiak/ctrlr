#include "stdafx.h"
#include "LModifierKeys.h"

void LModifierKeys::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<ModifierKeys>("ModifierKeys")
			.def(constructor<int>())
			.def(constructor<const ModifierKeys &>())
			.def("isCommandDown", &ModifierKeys::isCommandDown)
			.def("isPopupMenu", &ModifierKeys::isPopupMenu)
			.def("isLeftButtonDown", &ModifierKeys::isLeftButtonDown)
			.def("isRightButtonDown", &ModifierKeys::isRightButtonDown)
			.def("isMiddleButtonDown", &ModifierKeys::isMiddleButtonDown)
			.def("isAnyModifierKeyDown", &ModifierKeys::isAnyModifierKeyDown)
			.def("isShiftDown", &ModifierKeys::isShiftDown)
			.def("isCtrlDown", &ModifierKeys::isCtrlDown)
			.def("isAltDown", &ModifierKeys::isAltDown)
			.def("getRawFlags", &ModifierKeys::getRawFlags)
			.def("testFlags", &ModifierKeys::testFlags)
			.def("getNumMouseButtonsDown", &ModifierKeys::getNumMouseButtonsDown)
			.enum_("Flags")
			[
				value ("shiftModifier", 1),
				value ("ctrlModifier", 2),
				value ("altModifier", 4),
				value ("leftButtonModifier", 16),
				value ("rightButtonModifier", 32),
				value ("middleButtonModifier", 64),
				value ("commandModifier", 8),
				value ("popupMenuClickModifier", 34),
				value ("allKeyboardModifiers", 15),
				value ("allMouseButtonModifiers ", 112)
			]
	];
}