#include "stdafx.h"
#include "CtrlrOSC.h"

bool CtrlrOSC::sendMessage(const CtrlrOSCAddress &address, const CtrlrOSCMessage &message)
{
}

bool CtrlrOSC::sendMessageFrom(const CtrlrOSCAddress &sourceAddress,
								const CtrlrOSCAddress &destinationAddress,
								const CtrlrOSCMessage &message)
{
}

bool CtrlrOSC::sendMessageTimestamped(const CtrlrOSCAddress &destinationAddress,
										const CtrlrOSCTimetag &timetag,
										const CtrlrOSCMessage &message)
{
}
