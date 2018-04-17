#include "stdafx.h"
#include "CtrlrLuaManager.h"
#include "CtrlrLog.h"
#include "CtrlrComponents/CtrlrCustomComponent.h"

void CtrlrCustomComponent::wrapForLua(lua_State *L)
{
	using namespace luabind;
	module(L)
	[
		class_<CtrlrCustomComponent,CtrlrComponent>("CtrlrCustomComponent")
		,
		class_<DragAndDropSourceDetails>("DragAndDropSourceDetails")
			.def(constructor<const String &, Component *, int, int>())
			.def(constructor<const String &, Image, int, int>())
			.def(constructor<>())
			.def("getDescription", &DragAndDropSourceDetails::getDescription)
			.def("getSourceComponent", &DragAndDropSourceDetails::getSourceComponent)
			.def("getLocalPositionX", &DragAndDropSourceDetails::getLocalPositionX)
			.def("getLocalPositionY", &DragAndDropSourceDetails::getLocalPositionY)
	];
}