#include "stdafx.h"
#include "CtrlrNative.h"

#ifdef JUCE_WINDOWS
#include "CtrlrWindows.h"

CtrlrNative *CtrlrNative::getNativeObject(CtrlrManager &owner)
{
	return (new CtrlrWindows(owner));
}

#elif __APPLE__
#include "CtrlrMac.h"
CtrlrNative *CtrlrNative::getNativeObject(CtrlrManager &owner)
{
	return (new CtrlrMac(owner));
}
#elif LINUX
#include "CtrlrLinux.h"
CtrlrNative *CtrlrNative::getNativeObject(CtrlrManager &owner)
{
	return (new CtrlrLinux(owner));
}
#else
#include "CtrlrGeneric.h"
CtrlrNative *CtrlrNative::getNativeObject(CtrlrManager &owner)
{
	return (new CtrlrGeneric(owner));
}
#endif
