#include "stdafx.h"
#include "LAsyncUpdater.h"

void LAsyncUpdater::handleAsyncUpdate()
{
}

void LAsyncUpdater::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<LAsyncUpdater>("AsyncUpdater")
            .def("triggerAsyncUpdate", &AsyncUpdater::triggerAsyncUpdate)
            .def("cancelPendingUpdate", &AsyncUpdater::cancelPendingUpdate)
            .def("handleUpdateNowIfNeeded", &AsyncUpdater::handleUpdateNowIfNeeded)
            .def("isUpdatePending", &AsyncUpdater::isUpdatePending)
            .def("handleAsyncUpdate", &LAsyncUpdater::handleAsyncUpdate)
	];
}
