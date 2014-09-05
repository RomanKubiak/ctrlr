#include "stdafx.h"
#include "LMouseCursor.h"

void LMouseCursor::wrapForLua(lua_State *L)
{
    using namespace luabind;

	module(L)
    [
		class_<MouseCursor>("MouseCursor")
            .def(constructor<>())
            .def(constructor<MouseCursor::StandardCursorType>())
            .def(constructor<const Image &, int, int>())
            .def(constructor<const Image &, int, int, float>())
            .def(constructor<const MouseCursor &>())
            .enum_("StandardCursorType")
            [
                value("ParentCursor", MouseCursor::ParentCursor),
                value("NoCursor", MouseCursor::NoCursor),
                value("NormalCursor", MouseCursor::NormalCursor),
                value("WaitCursor", MouseCursor::WaitCursor)
            ]
            .scope
            [
                def("showWaitCursor", &MouseCursor::showWaitCursor),
                def("hideWaitCursor", &MouseCursor::hideWaitCursor)
            ]
    ];
}
