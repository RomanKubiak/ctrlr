#ifndef __L_TIMER__
#define __L_TIMER__

#include "CtrlrLuaManager.h"

class LTimer : public Timer
{
	public:
		LTimer()
		{}
		void timerCallback();
		void setCallback (luabind::object _callback);
		static void wrapForLua (lua_State *L);
	private:
		luabind::object callback;
};

#endif