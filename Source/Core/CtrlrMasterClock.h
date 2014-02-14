#ifndef __CTRLR_MASTER_CLOCK__
#define __CTRLR_MASTER_CLOCK__

#include "CtrlrMacros.h"

class CtrlrMasterClock : public Thread
{
	public:
		CtrlrMasterClock();
		void run();
		int getElapsedMilliseconds (const int64 ticksStart, const int64 ticksEnd = 0);
        void adjustDrift();
		bool isRunning();
		void start();
		void stop();
		void pause();
		void reset();

	private:
		bool running;
		int64 ticksCurrent;
		int64 ticksPerSecond;
		int64 ticksNextClock;
		int64 ticksStart;
		int64 ticksElapsed;
		int64 ticksLast;
};

#endif
