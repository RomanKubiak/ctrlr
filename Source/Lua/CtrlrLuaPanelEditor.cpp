#include "stdafx.h"
#include "CtrlrLuaManager.h"
#include "CtrlrLog.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"

void CtrlrPanelEditor::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrPanelEditor, CtrlrLuaObject>("CtrlrPanelEditor")
			.def("getWidth", &CtrlrPanelEditor::getWidth)
			.def("getHeight", &CtrlrPanelEditor::getHeight)
			.def("getCanvas",&CtrlrPanelEditor::getCanvas)
	];
}