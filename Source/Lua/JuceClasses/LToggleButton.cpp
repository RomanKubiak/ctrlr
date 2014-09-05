#include "stdafx.h"
#include "LToggleButton.h"

void LToggleButton::wrapForLua (lua_State *L)
{
    using namespace luabind;

	module(L)
    [
		class_<ToggleButton, Button>("ToggleButton")
            .def(constructor<>())
            .def(constructor<const String &>())
            .def("changeWidthToFitText", &ToggleButton::changeWidthToFitText)

    ];
}
