#ifndef L_THREADWITHPROGRESSWINDOW_H
#define L_THREADWITHPROGRESSWINDOW_H

#include "JuceHeader.h"
#include "luabind/object_fwd.hpp"
extern  "C"
{
	#include "lua.h"
}

class LThreadWithProgressWindow : public ThreadWithProgressWindow
{
	public:
		LThreadWithProgressWindow(const String &windowTitle, bool hasProgressBar, bool hasCancelButton, int timeOutMsWhenCancelling=10000, const String &cancelButtonText="Cancel");
		~LThreadWithProgressWindow();
		void run();
		void setThreadFunction(luabind::object const& functionToRunOnThread);
		void setProgress(double newProgress);
		void setStatusMessage(const String &newStatusMessage);
		static void wrapForLua (lua_State *L);

	private:
		luabind::object functionToRunOnThread;
};

#endif
