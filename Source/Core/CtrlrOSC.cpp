#include "stdafx.h"
#include "CtrlrOSC.h"
#include "JuceClasses/LMemoryBlock.h"

bool CtrlrOSC::sendMessage(const CtrlrOSCAddress &address, const CtrlrOSCMessage &message)
{
	return (lo_send_message (address.getLoAddress(), message.getPath().getCharPointer(), message.loMessage) < 0 ? false : true);
}

void CtrlrOSC::messageAddMidi(CtrlrOSCMessage &m, const MidiMessage &message)
{
	uint8_t data[4];
    memcpy (data, message.getRawData(), message.getRawDataSize());
	lo_message_add_midi (m.loMessage, data);
}

void CtrlrOSC::messageAddBlob(CtrlrOSCMessage &m, const LMemoryBlock &blob)
{
	lo_blob b = lo_blob_new(blob.getSize(), blob.getData());
	lo_message_add_blob (m.loMessage, b);
}

void CtrlrOSC::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrOSC>("osc")
		.scope
		[
			def("sendMessage", &CtrlrOSC::sendMessage),
			def("messageAddInt32", &CtrlrOSC::messageAddInt32),
			def("messageAddFloat", &CtrlrOSC::messageAddFloat),
			def("messageAddString", &CtrlrOSC::messageAddString),
			def("messageAddInt64", &CtrlrOSC::messageAddInt64),
			def("messageAddTimetag", &CtrlrOSC::messageAddTimetag),
			def("messageAddDouble", &CtrlrOSC::messageAddDouble),
			def("messageAddTrue", &CtrlrOSC::messageAddTrue),
			def("messageAddFalse", &CtrlrOSC::messageAddFalse),
			def("messageAddNil", &CtrlrOSC::messageAddNil),
			def("messageAddMidi", &CtrlrOSC::messageAddMidi),
			def("messageAddBlob", &CtrlrOSC::messageAddBlob)
		]
		,
		class_<lo_timetag>("lo_timetag")
			.def_readonly("sec", &lo_timetag::sec)
			.def_readonly("frac", &lo_timetag::frac)
		,
		class_<lo_arg>("lo_arg")
			.def_readonly("i", &lo_arg::i)
			.def_readonly("i32", &lo_arg::i32)
			.def_readonly("h", &lo_arg::h)
			.def_readonly("i64", &lo_arg::i64)
			.def_readonly("f", &lo_arg::f)
			.def_readonly("f32", &lo_arg::f32)
			.def_readonly("d", &lo_arg::d)
			.def_readonly("f64", &lo_arg::f64)
			.def_readonly("s", &lo_arg::s)
			.def_readonly("S", &lo_arg::S)
			.def_readonly("c", &lo_arg::c)
			.def_readonly("m", &lo_arg::m)
			.def_readonly("t", &lo_arg::t)
	];
}
