#ifndef __CTRLR_MAC__
#define __CTRLR_MAC__

#include "CtrlrNative.h"

typedef struct vmtotal vmtotal_t;

class CtrlrMac : public CtrlrNative
{
	public:
		CtrlrMac(CtrlrManager &_owner);
		~CtrlrMac();
		const Result exportWithDefaultPanel(CtrlrPanel*  panelToWrite, const bool isRestricted=false, const bool signPanel=false, RSAKey privateKey=RSAKey());
		const Result getDefaultPanel(MemoryBlock &dataToWrite);
		const Result getDefaultResources(MemoryBlock& dataToWrite);
		const bool setBundleInfo (CtrlrPanel *sourceInfo, const File &bundle);
        int getVersionAsHexInteger(const String version) const;
    private:
        CtrlrManager &owner;
};
#endif
