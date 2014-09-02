#include "stdafx.h"
#include "LButton.h"

void LButton::wrapForLua (lua_State *L)
{
    using namespace luabind;

	module(L)
    [
		class_<Button>("Button")
    ];
}
