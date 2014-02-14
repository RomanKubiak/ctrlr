#include "stdafx.h"
#include "LTime.h"

void LTime::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Time>("JTime")
		,
		class_<LTime, bases<Time> >("Time")
				.def(constructor<>())
				.def(constructor<int,int,int,int,int,int,int,bool>())
				.def(constructor<double>())
				.def(constructor<const LTime &>())
				.def(constructor<const Time &>())
				.def("toMilliseconds", &LTime::toMilliseconds)
				.def("getYear", &Time::getYear)
				.def("getMonth", &Time::getMonth)
				.def("getMonthName", (String (Time::*)(bool) const)&Time::getMonthName)
				.def("getDayOfMonth", &Time::getDayOfMonth)
				.def("getDayOfWeek", &Time::getDayOfWeek)
				.def("getDayOfYear", &Time::getDayOfYear)
				.def("getWeekdayName", (String (Time::*)(bool) const)&Time::getWeekdayName)
				.def("getHours", &Time::getHours)
				.def("isAfternoon", &Time::isAfternoon)
				.def("getHoursInAmPmFormat", &Time::getHoursInAmPmFormat)
				.def("getMinutes", &Time::getMinutes)
				.def("getSeconds", &Time::getSeconds)
				.def("getMilliseconds", &Time::getMilliseconds)
				.def("isDaylightSavingTime", &Time::isDaylightSavingTime)
				.def("getTimeZone", &Time::getTimeZone)
				.def("toString", &Time::toString)
				.def("formatted", &Time::formatted)
				.def("setSystemTimeToThisTime", &Time::setSystemTimeToThisTime)
				.scope
				[
					def("getCurrentTime", &LTime::getCurrentTime),
					def("currentTimeMillis", &LTime::currentTimeMillis),
					def("getMillisecondCounter", &Time::getMillisecondCounter),
					def("getMillisecondCounterHiRes", &Time::getMillisecondCounterHiRes),
					def("waitForMillisecondCounter", &Time::waitForMillisecondCounter),
					def("getApproximateMillisecondCounter", &Time::getApproximateMillisecondCounter),
					def("getHighResolutionTicks", &LTime::getHighResolutionTicks),
					def("getHighResolutionTicksPerSecond", &LTime::getHighResolutionTicksPerSecond),
					def("highResolutionTicksToSeconds", &LTime::highResolutionTicksToSeconds),
					def("secondsToHighResolutionTicks", &LTime::secondsToHighResolutionTicks)
				]
	];
}