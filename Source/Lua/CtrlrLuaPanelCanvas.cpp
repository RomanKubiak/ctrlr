#include "stdafx.h"
#include "CtrlrLuaManager.h"
#include "CtrlrLog.h"
#include "CtrlrPanel/CtrlrPanelCanvas.h"
#include "CtrlrPanel/CtrlrPanelCanvasLayer.h"

void CtrlrPanelCanvas::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrPanelCanvas,bases<Component> >("CtrlrPanelCanvas")
			.def("getLayerByName", &CtrlrPanelCanvas::getLayerByName)
			.def("getLayer", &CtrlrPanelCanvas::getLayer)
			.def("getLayerFromArray",&CtrlrPanelCanvas::getLayerFromArray)
			.def("getNumLayers",&CtrlrPanelCanvas::getNumLayers)
			.def("getLayerName",&CtrlrPanelCanvas::getLayerName)
			.def("setCustomLookAndFeel", (void (CtrlrPanelCanvas::*)(const luabind::object &)) &CtrlrPanelCanvas::setCustomLookAndFeel)
	];
}
