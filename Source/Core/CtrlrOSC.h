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
	public:
		CtrlrOSCAddress(String _host, int _port, int _protocol=-1)
			: protocol(_protocol), port(_port), host(_host)
		{
			loAddress = lo_address_new_with_proto(protocol < 0 ? LO_UDP : protocol, host.getCharPointer(), _STR(port).getCharPointer());
		}

		CtrlrOSCAddress(const String &url)
		{
			loAddress = lo_address_new_from_url (url.getCharPointer());
		}

		lo_address getLoAddress() { return (loAddress); }
	private:
		lo_address loAddress;
		int protocol;
		int port;
		String host;
};

struct CtrlrOSCMessage
{
	public:
		void setPath(const String &_path) 			{ path = _path; }
		void setTypes(const String &_types) 		{ types = _types; }
		Array<lo_arg> &getArguments() 				{ return (arguments); }
		const String &getPath() 					{ return (path); }
		const String &getTypes() 					{ return (types); }
		void addArgument(const lo_arg argument) 	{ arguments.add(argument); }

		lo_message loMessage;

	private:
		String path;
		String types;
		Array<lo_arg> arguments;
};

class CtrlrOSC
{
	public:
		static bool sendMessage(const CtrlrOSCAddress &destinationAddress,
								const CtrlrOSCMessage &message);
		static void wrapForLua(lua_State *L);

		static void messageAddInt32(CtrlrOSCMessage &m, const int32_t i) 		{ lo_message_add_int32(m.loMessage, i); }
		static void messageAddFloat(CtrlrOSCMessage &m, const float f)			{ lo_message_add_float(m.loMessage, f); }
		static void messageAddString(CtrlrOSCMessage &m, const String &s)		{ lo_message_add_string(m.loMessage, s.getCharPointer()); }
		static void messageAddInt64(CtrlrOSCMessage &m, const int64_t i)		{ lo_message_add_string(m.loMessage, i); }
		static void messageAddTimetag(CtrlrOSCMessage &m, const lo_timetag t)	{ lo_message_add_timetag(m.loMessage, t); }
		static void messageAddDouble(CtrlrOSCMessage &m, const double d)		{ lo_message_add_double(m.loMessage, d); }
		static void messageAddTrue(CtrlrOSCMessage &m, const double d)			{ lo_message_add_true(m.loMessage); }
		static void messageAddFalse(CtrlrOSCMessage &m, const double d)			{ lo_message_add_false(m.loMessage); }
		static void messageAddNil(CtrlrOSCMessage &m, const double d)			{ lo_message_add_nil(m.loMessage); }
		static void messageAddMidi(CtrlrOSCMessage &m, const MidiMessage &blob);
		static void messageAddBlob(CtrlrOSCMessage &m, const LMemoryBlock &message);
};

#endif
