#ifndef L_ASYNC_UPDATER_H
#define L_ASYNC_UPDATER_H

#include "JuceHeader.h"
extern  "C"
{
	#include "lua.h"
}

class LAsyncUpdater : public AsyncUpdater
{
	public:
		static void wrapForLua (lua_State *L);
		void handleAsyncUpdate();

	private:
		luabind::object asyncCallbackMethod;
};

#endif
