#ifndef __CTRLR_LINUX__
#define __CTRLR_LINUX__

#include "CtrlrNative.h"

class CtrlrLinux : public CtrlrNative
{
	public:
		CtrlrLinux();
		~CtrlrLinux();
		
	private:
		int myPid;
};
#endif