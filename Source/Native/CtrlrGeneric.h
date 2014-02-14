#ifndef __CTRLR_GENERIC__
#define __CTRLR_GENERIC__

#include "CtrlrNative.h"

class CtrlrGeneric : public CtrlrNative
{
	public:
		CtrlrGeneric() {}
		~CtrlrGeneric() {}
		const int getMemoryUsage(){}
		const short getCpuUsage(){}
		void timerCallback(){}
};
#endif