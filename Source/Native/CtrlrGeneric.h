#ifndef __CTRLR_GENERIC__
#define __CTRLR_GENERIC__

#include "CtrlrNative.h"

class CtrlrGeneric : public CtrlrNative
{
	public:
		CtrlrGeneric(CtrlrManager &owner) {}
		~CtrlrGeneric() {}
		const int getMemoryUsage(){}
		const short getCpuUsage(){}
		void timerCallback(){}
};
#endif
