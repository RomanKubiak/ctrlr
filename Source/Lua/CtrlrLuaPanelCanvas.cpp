#include "stdafx.h"
#include "CtrlrLuaManager.h"
#include "CtrlrLog.h"
#include "CtrlrPanel/CtrlrPanelCanvas.h"

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
	];
}
