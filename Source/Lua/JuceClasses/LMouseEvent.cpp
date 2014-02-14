#include "stdafx.h"
#include "LMouseEvent.h"

void LMouseEvent::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<MouseEvent>("MouseEvent")
			.def("getMouseDownX", &MouseEvent::getMouseDownX)
			.def("getMouseDownY", &MouseEvent::getMouseDownY)
			.def("getDistanceFromDragStart", &MouseEvent::getDistanceFromDragStart)
			.def("getDistanceFromDragStartX", &MouseEvent::getDistanceFromDragStartX)
			.def("getDistanceFromDragStartY", &MouseEvent::getDistanceFromDragStartY)
			.def("mouseWasClicked", &MouseEvent::mouseWasClicked)
			.def("getNumberOfClicks", &MouseEvent::getNumberOfClicks)
			.def("getLengthOfMousePress", &MouseEvent::getLengthOfMousePress)
			.def("getScreenX", &MouseEvent::getScreenX)
			.def("getScreenY", &MouseEvent::getScreenY)
			.def("getMouseDownScreenX", &MouseEvent::getMouseDownScreenX)
			.def("getMouseDownScreenY", &MouseEvent::getMouseDownScreenY)
			.def_readonly("x", &MouseEvent::x)
			.def_readonly("y", &MouseEvent::y)
			.def_readonly("mods", &MouseEvent::mods)
			.def_readonly("eventTime", &MouseEvent::eventTime)
			.def_readonly("eventComponent", &MouseEvent::eventComponent)
			.def_readonly("originalComponent", &MouseEvent::originalComponent)
			.def_readonly("eventTime", &MouseEvent::eventTime)
			.def("getMouseDownPosition", &MouseEvent::getMouseDownPosition)
			.def("getOffsetFromDragStart", &MouseEvent::getOffsetFromDragStart)
			.def("getPosition", &MouseEvent::getPosition)
			.def("getScreenPosition", &MouseEvent::getScreenPosition)
			.def("getMouseDownScreenPosition", &MouseEvent::getMouseDownScreenPosition)
	];
}