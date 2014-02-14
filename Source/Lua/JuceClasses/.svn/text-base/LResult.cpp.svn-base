#include "stdafx.h"
#include "LResult.h"

void LResult::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Result>("Result")
				.def("wasOk", &Result::wasOk)
				.def("failed", &Result::failed)
				.def("getErrorMessage", &Result::getErrorMessage)
				.def("fail", &Result::fail)
				.def("ok", &Result::ok)
	];
}