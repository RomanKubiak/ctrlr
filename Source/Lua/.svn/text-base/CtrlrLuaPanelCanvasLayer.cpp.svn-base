#include "stdafx.h"
#include "CtrlrLuaManager.h"
#include "CtrlrLog.h"
#include "CtrlrPanel/CtrlrPanelCanvas.h"

/** @brief Move the layer up one step

*/
void CtrlrPanelCanvasLayer::moveUp()
{
	owner.moveLayer (this, true);
}

/** @brief Move the layer down one step

*/
void CtrlrPanelCanvasLayer::moveDown()
{
	owner.moveLayer (this, false);
}

void CtrlrPanelCanvasLayer::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrPanelCanvasLayer, bases<Component, CtrlrLuaObject> >("CtrlrPanelCanvasLayer")
			.def("moveUp", &CtrlrPanelCanvasLayer::moveUp)
			.def("moveDown", &CtrlrPanelCanvasLayer::moveDown)
	];
}