#ifndef __CTRLR_LUA_LOOK_AND_FEEL__
#define __CTRLR_LUA_LOOK_AND_FEEL__

#include "CtrlrLuaManager.h"
#include "CtrlrLog.h"

class CtrlrLuaLookAndFeel : public LookAndFeel_V2
{
	public:
		CtrlrLuaLookAndFeel (luabind::object _o);
		void drawLabel(Graphics &g, Label &label);

		static void wrapForLua (lua_State *L);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLuaLookAndFeel);

	private:
		luabind::object o;
};

#endif