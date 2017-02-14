#ifndef CTRLR_OSC
#define CTRLR_OSC

#include "CtrlrMacros.h"
#include "CtrlrLog.h"
#include "luabind/object_fwd.hpp"
extern "C"
{
#include "lo/lo.h"
}

class LMemoryBlock;

struct CtrlrOSCTimetag
{
	uint32 sec;
	uint32 frac;
};

struct CtrlrOSCAddress
{
	private:
		void* loAddress;
		int protocol;
		int port;
		String host;

	public:
		CtrlrOSCAddress(String _host, int _port, int _protocol)
			: protocol(_protocol), port(_port), host(_host)
		{
			loAddress = lo_address_new_with_proto(protocol < 0 ? LO_UDP : protocol, host.getCharPointer(), _STR(port).getCharPointer());
		}

		CtrlrOSCAddress(String _host, int _port)
			: port(_port), host(_host)
		{
			loAddress = lo_address_new(host.getCharPointer(), _STR(port).getCharPointer());
		}

		CtrlrOSCAddress(const String &url)
		{
			loAddress = lo_address_new_from_url (url.getCharPointer());
		}

		const String &getHost()
		{
			return (host);
		}
		void* getLoAddress()
		{
			return (loAddress);
		}
};

struct CtrlrOSCMessage
{
	public:
		CtrlrOSCMessage()
		{
			loMessage = lo_message_new();
		}
		CtrlrOSCMessage(const String &_path, const String &_types)
		{
			loMessage = lo_message_new();
			path = _path;
			types = _types;
		}
		void setPath(const String &_path) 			{ path = _path; }
		void setTypes(const String &_types) 		{ types = _types; }
		const String &getPath() const 				{ return (path); }
		const String &getTypes() const 				{ return (types); }

		lo_message loMessage;

	private:
		String path;
		String types;
};

class CtrlrLoArg
{
	public:
		std::string asString()
		{
			_DBG("CtrlrLoArg::asString");
			return std::string();
		}
};

class CtrlrOSC
{
	public:
		static bool sendMessage(CtrlrOSCAddress destinationAddress,
								const CtrlrOSCMessage &message);
		static CtrlrOSCAddress createAddress(const String &host, const int port, const int proto);
		static CtrlrOSCAddress createAddress(const String &host, const int port);
		static CtrlrOSCMessage createMessage();
		static CtrlrOSCMessage createMessage(const String &path, const String &types);
		static void wrapForLua(lua_State *L);

		static void messageAddInt32(CtrlrOSCMessage &m, const int32_t i) 		{ lo_message_add_int32(m.loMessage, i); }
		static void messageAddFloat(CtrlrOSCMessage &m, const float f)			{ lo_message_add_float(m.loMessage, f); }
		static void messageAddString(CtrlrOSCMessage &m, const String &s); 
		static void messageAddInt64(CtrlrOSCMessage &m, const int64_t i)		{ lo_message_add_int64(m.loMessage, i); }
		static void messageAddTimetag(CtrlrOSCMessage &m, const lo_timetag t)	{ lo_message_add_timetag(m.loMessage, t); }
		static void messageAddDouble(CtrlrOSCMessage &m, const double d)		{ lo_message_add_double(m.loMessage, d); }
		static void messageAddTrue(CtrlrOSCMessage &m, const double d)			{ lo_message_add_true(m.loMessage); }
		static void messageAddFalse(CtrlrOSCMessage &m, const double d)			{ lo_message_add_false(m.loMessage); }
		static void messageAddNil(CtrlrOSCMessage &m, const double d)			{ lo_message_add_nil(m.loMessage); }
		static void messageAddMidi(CtrlrOSCMessage &m, const MidiMessage &blob);
		static void messageAddBlob(CtrlrOSCMessage &m, const LMemoryBlock &message);
};

#endif
