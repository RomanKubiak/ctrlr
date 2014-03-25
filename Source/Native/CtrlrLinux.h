#ifndef CTRLR_LINUX_H
#define CTRLR_LINUX_H

#include "CtrlrNative.h"

class CtrlrLinux : public CtrlrNative
{
	public:
		CtrlrLinux();
		~CtrlrLinux();
		const Result exportWithDefaultPanel(CtrlrPanel*  panelToWrite, const bool isRestricted=false);
		const Result getDefaultPanel(MemoryBlock& dataToWrite);
		const Result getDefaultResources(MemoryBlock& dataToWrite);
	private:
		int myPid;
};

#endif
