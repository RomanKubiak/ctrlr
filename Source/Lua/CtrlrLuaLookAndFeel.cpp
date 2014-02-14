#include "stdafx.h"
#include "CtrlrLuaLookAndFeel.h"

CtrlrLuaLookAndFeel::CtrlrLuaLookAndFeel(luabind::object _o) : o(_o)
{
}

void CtrlrLuaLookAndFeel::drawLabel(Graphics &g, Label &label)
{
	if (o)
	{
		luabind::object call = o["drawLabel"];
 
		if(call && luabind::type(call) == LUA_TFUNCTION)
		{
			try
			{
				luabind::call_function<void>(call, o, boost::ref(g), boost::ref(label));
			}
			catch (luabind::error e)
			{
				_LERR("CtrlrLuaLookAndFeel::drawLabel error "+String(e.what()));
			}
		}
	}
}

void CtrlrLuaLookAndFeel::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrLuaLookAndFeel,LookAndFeel_V2>("CtrlrLuaLookAndFeel")
			.def(constructor<luabind::object>())
	];
}