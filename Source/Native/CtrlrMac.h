#ifndef __CTRLR_MAC__
#define __CTRLR_MAC__

#include "CtrlrNative.h"

typedef struct vmtotal vmtotal_t;

class CtrlrMac : public CtrlrNative
{
	public:
		CtrlrMac();
		~CtrlrMac();
		const Result exportWithDefaultPanel(CtrlrPanel *panelToWrite, const bool isRestricted=false);
		const Result getDefaultPanel(MemoryBlock &dataToWrite);
		const Result getDefaultResources(MemoryBlock& dataToWrite);
		const bool setBundleInfo (CtrlrPanel *sourceInfo, const File &bundle);
};
#endif
