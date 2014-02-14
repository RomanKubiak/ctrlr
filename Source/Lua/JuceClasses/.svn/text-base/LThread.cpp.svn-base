#include "stdafx.h"
#include "LThread.h"

LThread::LThread(const String &threadName) : Thread(threadName)
{
}

void LThread::run()
{
	if (functionToRunOnThread.is_valid())
	{
		luabind::call_function<void>(functionToRunOnThread);
	}
}

void LThread::setThreadFunction(luabind::object const& _functionToRunOnThread)
{
	functionToRunOnThread = _functionToRunOnThread;
}

void LThread::startThread()
{
	Thread::startThread();
}

void LThread::startThread(int priority)
{
	Thread::startThread(priority);
}

bool LThread::isThreadRunning()
{
	return (Thread::isThreadRunning());
}

void LThread::signalThreadShouldExit()
{
	Thread::signalThreadShouldExit();
}

bool LThread::threadShoudExit() const
{
	return (Thread::threadShouldExit());
}

bool LThread::waitForThreadToExit(int timeOutMilliseconds) const
{
	return (Thread::waitForThreadToExit(timeOutMilliseconds));
}

bool LThread::setPriority(int priority)
{
	return (Thread::setPriority(priority));
}

void LThread::setAffinityMask(int affinityMask)
{
	Thread::setAffinityMask(affinityMask);
}

bool LThread::wait(int timeOutMilliseconds) const
{
	return (Thread::wait(timeOutMilliseconds));
}

void LThread::notify() const
{
	Thread::notify();
}

int LThread::getThreadId() const noexcept
{
	return ((int)Thread::getThreadId());
}

const String &LThread::getThreadName() const
{
	return (Thread::getThreadName());
}

void LThread::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<LThread>("Thread")
			.def(constructor<const String &>())
			.def("setThreadFunction", &LThread::setThreadFunction)
			.def("startThread", (void (LThread::*)(void))&LThread::setPriority)
			.def("startThread", (void (LThread::*)(int))&LThread::setPriority)
			.def("isThreadRunning", &LThread::isThreadRunning)
			.def("signalThreadShouldExit", &LThread::signalThreadShouldExit)
			.def("threadShoudExit", &LThread::threadShoudExit)
			.def("waitForThreadToExit", &LThread::waitForThreadToExit)
			.def("setPriority", (void (LThread::*)(int))&LThread::setPriority)
			.def("setAffinityMask", &LThread::setAffinityMask)
			.def("wait", &LThread::wait)
			.def("notify", &LThread::notify)
			.def("getThreadId", &LThread::getThreadId)
			.def("getThreadName", &LThread::getThreadName)
		,
		class_<CriticalSection>("CriticalSection")
			.def(constructor<>())
			.def("enter", &CriticalSection::enter)
			.def("tryEnter", &CriticalSection::tryEnter)
			.def("exit", &CriticalSection::exit)
		,
		class_<ScopedLock>("ScopedLock")
			.def(constructor<CriticalSection &>())
		,
		class_<ScopedUnlock>("ScopedUnlock")
			.def(constructor<CriticalSection &>())
		,
		class_<ScopedTryLock>("ScopedTryLock")
			.def(constructor<CriticalSection &>())
			.def("isLocked", &ScopedTryLock::isLocked)
	];
}
