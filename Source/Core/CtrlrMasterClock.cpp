#include "stdafx.h"
#include "CtrlrMasterClock.h"

CtrlrMasterClock::CtrlrMasterClock()
	: 	Thread("CTRLR MASTER CLOCK"),
		ticksCurrent(Time::getHighResolutionTicks()),
		ticksPerSecond(Time::getHighResolutionTicksPerSecond()),
		ticksNextClock(0),
		ticksStart(0),
		ticksLast(0),
		running(false)
{
}

void CtrlrMasterClock::run()
{
	while (1)
	{
		const bool result = wait (2);

		ticksElapsed += (Time::getHighResolutionTicks() - ticksLast);

		if (result)
		{
			/* singal */
		}
		else
		{
			/* timeout */
		}
	}
}

void CtrlrMasterClock::adjustDrift()
{
}

void CtrlrMasterClock::start()
{
	running 	= true;
	ticksLast	= Time::getHighResolutionTicks();

	startThread();
}

void CtrlrMasterClock::stop()
{
	running 	= false;

	stopThread (40);
	reset();
}

void CtrlrMasterClock::pause()
{
	running 	= false;
	stopThread(40);
}

void CtrlrMasterClock::reset()
{
	ticksStart		= Time::getHighResolutionTicks();
	ticksElapsed	= 0;
}

bool CtrlrMasterClock::isRunning()
{
	return (running);
}

int CtrlrMasterClock::getElapsedMilliseconds (const int64 ticksStart, const int64 ticksEnd)
{
	return ( (( (ticksEnd ? ticksEnd : Time::getHighResolutionTicks()) - ticksStart) * ticksPerSecond) / 1000);
}
