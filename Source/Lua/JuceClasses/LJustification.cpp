#include "stdafx.h"
#include "LJustification.h"

void LJustification::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Justification>("Justification")
			.def(constructor<int>())
			.def("getFlags", &Justification::getFlags)
			.def("testFlags", &Justification::testFlags)
			.def("getOnlyVerticalFlags", &Justification::getOnlyVerticalFlags)
			.def("getOnlyHorizontalFlags", &Justification::getOnlyHorizontalFlags)
			.enum_("Flags")
			[
				value("left", 1),
				value("right", 2),
				value("horizontallyCentred", 4),
				value("top", 8),
				value("bottom", 16),
				value("verticallyCentred", 32),
				value("horizontallyJustified", 64),
				value("centred", 36),
				value("centredLeft", 33),
				value("centredRight", 34),
				value("centredTop", 12),
				value("centredBottom", 20),
				value("topLeft", 9),
				value("topRight", 10),
				value("bottomLeft", 17),
				value("bottomRight", 18)
			]
	];
}