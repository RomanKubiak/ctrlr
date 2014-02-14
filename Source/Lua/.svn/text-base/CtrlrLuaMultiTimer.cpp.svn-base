#include "stdafx.h"
#include "CtrlrLuaMultiTimer.h"
#include "CtrlrWindowManagers/CtrlrManagerWindowManager.h"

CtrlrLuaMultiTimer::CtrlrLuaMultiTimer()
{
}

CtrlrLuaMultiTimer::~CtrlrLuaMultiTimer()
{
}

void CtrlrLuaMultiTimer::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrLuaMultiTimer>("CtrlrLuaMultiTimer")
			.def("setCallback", &CtrlrLuaMultiTimer::setCallback)
			.def("startTimer", &CtrlrLuaMultiTimer::startTimer)
			.def("isRegistered", &CtrlrLuaMultiTimer::isRegistered)
			.def("stopTimer", &CtrlrLuaMultiTimer::stopTimer)
			.def("isTimerRunning", &CtrlrLuaMultiTimer::isTimerRunning)
			.def("getTimerInterval", &CtrlrLuaMultiTimer::getTimerInterval)
	];
}

void CtrlrLuaMultiTimer::setCallback (const int timerId, luabind::object callback)
{
	LuaTimerCallback c;
	c.o = callback;
	c.isValid = true;
	callbacks.set (timerId, c);
}

void CtrlrLuaMultiTimer::startTimer (const int timerId, const int interval)
{
	MultiTimer::startTimer (timerId, interval);
}

void CtrlrLuaMultiTimer::timerCallback(int timerId)
{
	if (callbacks.contains (timerId))
	{
		if (callbacks[timerId].isValid)
		{
			try
			{
				luabind::call_function <void>(callbacks[timerId].o, timerId);
			}
			catch (const luabind::error &e)
			{
				LuaTimerCallback cb = callbacks[timerId];
				cb.isValid = false;

				callbacks.set (timerId, cb);
				const char* a = lua_tostring(e.state(), -1);
				AlertWindow::showMessageBox (AlertWindow::WarningIcon, "Timer callback error, timer id that failed was: "+String(timerId),  String(e.what())+"\n"+String(a)+"\n\nCallback disabled");
			}
		}
	}
}

const bool CtrlrLuaMultiTimer::isRegistered(const int timerId)
{
	return (callbacks.contains (timerId));
}

void CtrlrLuaMultiTimer::stopTimer (const int timerId)
{
	MultiTimer::stopTimer (timerId);
}

const bool CtrlrLuaMultiTimer::isTimerRunning (const int timerId)
{
	return (MultiTimer::isTimerRunning(timerId));
}

const int CtrlrLuaMultiTimer::getTimerInterval(const int timerId)
{
	return (MultiTimer::getTimerInterval(timerId));
}