#ifndef __CTRLR_WINDOWS__
#define __CTRLR_WINDOWS__

#include "CtrlrNative.h"
#include <Windows.h>
class CtrlrPanel;

class CtrlrWindows : public CtrlrNative
{
	public:
		CtrlrWindows();
		~CtrlrWindows();

		/* resource handling */
		const Result writeResource (void *handle, const LPSTR resourceId, const LPSTR resourceType, const MemoryBlock &resourceData);
		const Result readResource (void *handle, const LPSTR resourceId, const LPSTR resourceType, MemoryBlock &resourceData);
		const Result exportWithDefaultPanel(CtrlrPanel*  panelToWrite, const bool isRestricted=false, const bool signPanel=false, RSAKey privateKey=RSAKey());
		const Result getDefaultPanel(MemoryBlock &dataToWrite);
		const Result getDefaultResources(MemoryBlock& dataToWrite);
		const Result getSignature(MemoryBlock &dataToWrite);
		const Result registerFileHandler();
};
#endif
