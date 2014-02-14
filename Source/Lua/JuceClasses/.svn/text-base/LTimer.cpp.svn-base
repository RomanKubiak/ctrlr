#include "stdafx.h"
#include "LTimer.h"

void LTimer::setCallback (luabind::object _callback)
{
	callback = _callback;
}

void LTimer::timerCallback()
{
	if (callback)
	{
		luabind::call_function<void>(callback);
	}
}

void LTimer::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Timer, LTimer>("Timer")
			.def("setCallback", &LTimer::setCallback)
			.def("startTimer", &Timer::startTimer)
			.def("stopTimer", &Timer::stopTimer)
			.def("isTimerRunning", &Timer::isTimerRunning)
			.def("getTimerInterval", &Timer::getTimerInterval)
	];
}