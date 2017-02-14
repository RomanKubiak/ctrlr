#ifndef L_THREAD_H
#define L_THREAD_H

#include "JuceHeader.h"
#include "luabind/object_fwd.hpp"
extern  "C"
{
	#include "lua.h"
}

class LThread : public Thread
{
	public:
		LThread(const String &threadName);
		void run();
		void setThreadFunction(luabind::object const& functionToRunOnThread);
		void startThread();
		void startThread(int priority);
		bool isThreadRunning();
		void signalThreadShouldExit();
		bool threadShoudExit() const;
		bool waitForThreadToExit(int timeOutMilliseconds) const;
		bool setPriority(int priority);
		void setAffinityMask(int affinityMask);
		bool wait(int timeOutMilliseconds) const;
		void notify() const;
		int getThreadId() const noexcept;
		const String &getThreadName() const;
		static void wrapForLua (lua_State *L);

	private:
		luabind::object functionToRunOnThread;
};

#endif
