#include "stdafx.h"
#include "CtrlrNative.h"

#ifdef JUCE_WINDOWS
#include "CtrlrWindows.h"

CtrlrNative *CtrlrNative::getNativeObject()
{
	return (new CtrlrWindows());
}

#elif __APPLE__
#include "CtrlrMac.h"
CtrlrNative *CtrlrNative::getNativeObject()
{
	return (new CtrlrMac());
}
#elif LINUX
#include "CtrlrLinux.h"
CtrlrNative *CtrlrNative::getNativeObject()
{
	return (new CtrlrLinux());
}
#else
#include "CtrlrGeneric.h"
CtrlrNative *CtrlrNative::getNativeObject()
{
	return (new CtrlrGeneric());
}
#endif
