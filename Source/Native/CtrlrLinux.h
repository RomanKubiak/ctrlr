#ifndef CTRLR_LINUX_H
#define CTRLR_LINUX_H

#include "CtrlrNative.h"

class CtrlrLinux : public CtrlrNative
{
	public:
		CtrlrLinux(CtrlrManager &_owner);
		~CtrlrLinux();
		const Result exportWithDefaultPanel(CtrlrPanel*  panelToWrite, const bool isRestricted=false, const bool signPanel=false, RSAKey privateKey=RSAKey());
		const Result getDefaultPanel(MemoryBlock& dataToWrite);
		const Result getDefaultResources(MemoryBlock& dataToWrite);
		const Result getSignature(MemoryBlock &dataToWrite);

    private:
        CtrlrManager &owner;
};

#endif
