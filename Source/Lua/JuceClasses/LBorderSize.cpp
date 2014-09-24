#include "stdafx.h"
#include "LBorderSize.h"

void LBorderSize::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<BorderSize<int> >("BorderSize")
	];
}
