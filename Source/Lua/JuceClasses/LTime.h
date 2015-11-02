#ifndef L_TIME
#define L_TIME

#include "JuceHeader.h"
extern  "C"
{
	#include "lua.h"
}

class LTime : public Time
{
	public:
		LTime() : Time()
		{
		}

		LTime(int year, int month, int day, int hours, int minutes, int seconds, int milliseconds, bool useLocalTime)
			: Time(year, month, day, hours, minutes, seconds, milliseconds, useLocalTime)
		{}

		LTime(double millisecondsSinceEpoch) : Time((int64)millisecondsSinceEpoch)
		{}

		LTime(const LTime &other) : Time(other)
		{}

		LTime(const Time &other) : Time(other)
		{}

		double toMilliseconds()
		{
			return ( (double) Time::toMilliseconds());
		}

		static LTime getCurrentTime()
		{
			return (Time::getCurrentTime());
		}

		static double currentTimeMillis()
		{
			return ( (double) Time::currentTimeMillis());
		}

		static double getHighResolutionTicks()
		{
			return ( (double) Time::getHighResolutionTicks());
		}

		static double getHighResolutionTicksPerSecond()
		{
			return ( (double) Time::getHighResolutionTicksPerSecond());
		}

		static double highResolutionTicksToSeconds(double ticks)
		{
			return (Time::highResolutionTicksToSeconds(ticks));
		}

		static double secondsToHighResolutionTicks(double seconds)
		{
			return ( (double) Time::secondsToHighResolutionTicks(seconds));
		}

		static void wrapForLua (lua_State *L);
};

#endif
