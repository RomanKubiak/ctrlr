#ifndef CTRLR_OSC
#define CTRLR_OSC

#include "CtrlrMacros.h"
#include "lo/lo.h"

struct CtrlrOSCTimetag
{
	uint32 sec;
	uint32 frac;
};

struct CtrlrOSCAddress
{
	CtrlrOSCAddress(String _host, int _port, int _protocol=-1)
		: protocol(_protocol), port(_port), host(_host)
	{
        loAddress = lo_address_new_with_proto(protocol < 0 ? LO_UDP : protocol, host.getCharPointer(), _STR(port).getCharPointer());
	}

	CtrlrOSCAddress(const String &url)
		loAddress = lo_address_new_from_url (url.getCharPointer());
	{
	}

	lo_address loAddress;

	private:
		int protocol;
		int port;
		String host;
};

struct CtrlrOSCMessage
{
	String path;
	String types;
    Array<lo_arg> arguments;
};

class CtrlrOSC
{
	public:
		static bool sendMessage(const CtrlrOSCAddress &destinationAddress,
								const CtrlrOSCMessage &message);

		static bool sendMessageFrom(const CtrlrOSCAddress &sourceAddress,
									const CtrlrOSCAddress &destinationAddress,
									const CtrlrOSCMessage &message);

		static bool sendMessageTimestamped(const CtrlrOSCAddress &destinationAddress,
											const CtrlrOSCTimetag &timetag,
											const CtrlrOSCMessage &message);

};

#endif
