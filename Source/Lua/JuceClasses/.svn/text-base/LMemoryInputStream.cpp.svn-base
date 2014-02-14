#include "stdafx.h"
#include "LMemoryInputStream.h"

void LMemoryInputStream::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<MemoryInputStream>("MemoryInputStream")
	];
}