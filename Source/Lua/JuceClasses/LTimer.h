#ifndef L_TIMER
#define L_TIMER

#include "JuceHeader.h"

extern  "C"
{
	#include "lua.h"
}

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
