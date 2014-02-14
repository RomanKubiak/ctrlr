#include "stdafx.h"
#include "LMidiMessage.h"

void LMidiMessage::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<MidiMessage>("MidiMessage")
				.def(constructor<>())
				.def(constructor<const MidiMessage &>())
				.def(constructor<const MidiMessage &,double>())
				.def(constructor<int,int,int,double>())
				.def(constructor<int,int,double>())
				.def(constructor<int,double>())
				.def(constructor<const void *,int, double>())
				.def(constructor<const void *,int, int, uint8, double>())
				.def("getRawData", &MidiMessage::getRawData)
				.def("getRawDataSize", &MidiMessage::getRawDataSize)
				.def("getTimeStamp", &MidiMessage::getTimeStamp)
				.def("setTimeStamp", &MidiMessage::setTimeStamp)
				.def("addToTimeStamp", &MidiMessage::addToTimeStamp)
				.def("getChannel", &MidiMessage::getChannel)
				.def("isForChannel", &MidiMessage::isForChannel)
				.def("setChannel", &MidiMessage::setChannel)
				.def("isSysEx", &MidiMessage::isSysEx)
				.def("getSysExData", &MidiMessage::getSysExData)
				.def("getSysExDataSize", &MidiMessage::getSysExDataSize)
				.def("isNoteOn", &MidiMessage::isNoteOn)
				.def("isNoteOff", &MidiMessage::isNoteOff)
				.def("isNoteOnOrOff", &MidiMessage::isNoteOnOrOff)
				.def("getNoteNumber", &MidiMessage::getNoteNumber)
				.def("setNoteNumber", &MidiMessage::setNoteNumber)
				.def("getVelocity", &MidiMessage::getVelocity)
				.def("getFloatVelocity", &MidiMessage::getFloatVelocity)
				.def("setVelocity", &MidiMessage::setVelocity)
				.def("multiplyVelocity", &MidiMessage::multiplyVelocity)
				.def("isSustainPedalOn", &MidiMessage::isSustainPedalOn)
				.def("isSustainPedalOff", &MidiMessage::isSustainPedalOff)
				.def("isSostenutoPedalOn", &MidiMessage::isSostenutoPedalOn)
				.def("isSostenutoPedalOff", &MidiMessage::isSostenutoPedalOff)
				.def("isSoftPedalOn", &MidiMessage::isSoftPedalOn)
				.def("isSoftPedalOff", &MidiMessage::isSoftPedalOff)
				.def("isProgramChange", &MidiMessage::isProgramChange)
				.def("getProgramChangeNumber", &MidiMessage::getProgramChangeNumber)
				.def("isPitchWheel", &MidiMessage::isPitchWheel)
				.def("getPitchWheelValue", &MidiMessage::getPitchWheelValue)
				.def("isAftertouch", &MidiMessage::isAftertouch)
				.def("getAfterTouchValue", &MidiMessage::getAfterTouchValue)
				.def("isChannelPressure", &MidiMessage::isChannelPressure)
				.def("getChannelPressureValue", &MidiMessage::getChannelPressureValue)
				.def("isController", &MidiMessage::isController)
				.def("getControllerNumber", &MidiMessage::getControllerNumber)
				.def("getControllerValue", &MidiMessage::getControllerValue)
				.def("isControllerOfType", &MidiMessage::isControllerOfType)
				.def("isAllNotesOff", &MidiMessage::isAllNotesOff)
				.def("isAllSoundOff", &MidiMessage::isAllSoundOff)
				.def("isMetaEvent", &MidiMessage::isMetaEvent)
				.def("getMetaEventType", &MidiMessage::getMetaEventType)
				.def("getMetaEventData", &MidiMessage::getMetaEventData)
				.def("getMetaEventLength", &MidiMessage::getMetaEventLength)
				.def("isTrackMetaEvent", &MidiMessage::isTrackMetaEvent)
				.def("isEndOfTrackMetaEvent", &MidiMessage::isEndOfTrackMetaEvent)
				.def("isTrackNameEvent", &MidiMessage::isTrackNameEvent)
				.def("isTextMetaEvent", &MidiMessage::isTextMetaEvent)
				.def("getTextFromTextMetaEvent", &MidiMessage::getTextFromTextMetaEvent)
				.def("isTempoMetaEvent", &MidiMessage::isTempoMetaEvent)
				.def("getTempoMetaEventTickLength", &MidiMessage::getTempoMetaEventTickLength)
				.def("getTempoSecondsPerQuarterNote", &MidiMessage::getTempoSecondsPerQuarterNote)
				.def("isTimeSignatureMetaEvent", &MidiMessage::isTimeSignatureMetaEvent)
				.def("getTimeSignatureInfo", &MidiMessage::getTimeSignatureInfo)
				.def("isKeySignatureMetaEvent", &MidiMessage::isKeySignatureMetaEvent)
				.def("getKeySignatureNumberOfSharpsOrFlats", &MidiMessage::getKeySignatureNumberOfSharpsOrFlats)
				.def("isMidiChannelMetaEvent", &MidiMessage::isMidiChannelMetaEvent)
				.def("getMidiChannelMetaEventChannel", &MidiMessage::getMidiChannelMetaEventChannel)
				.def("isActiveSense", &MidiMessage::isActiveSense)
				.def("isMidiStart", &MidiMessage::isMidiStart)
				.def("isMidiContinue", &MidiMessage::isMidiContinue)
				.def("isMidiStop", &MidiMessage::isMidiStop)
				.def("isMidiClock", &MidiMessage::isMidiClock)
				.def("isSongPositionPointer", &MidiMessage::isSongPositionPointer)
				.def("getSongPositionPointerMidiBeat", &MidiMessage::getSongPositionPointerMidiBeat)
				.def("isQuarterFrame", &MidiMessage::isQuarterFrame)
				.def("getQuarterFrameSequenceNumber", &MidiMessage::getQuarterFrameSequenceNumber)
				.def("getQuarterFrameValue", &MidiMessage::getQuarterFrameValue)
				.def("isFullFrame", &MidiMessage::isFullFrame)
				.def("isMidiMachineControlMessage", &MidiMessage::isMidiMachineControlMessage)
				.def("getMidiMachineControlCommand", &MidiMessage::getMidiMachineControlCommand)
				.def("isMidiMachineControlGoto", &MidiMessage::isMidiMachineControlGoto)
				.enum_("SmtpeTimecodeType")
				[
					value("fps24", 0),
					value("fps25", 1),
					value("fps30drop", 2),
					value("fps30", 3)
				]
				// CAUSES COMPILATION ERROR .def("getFullFrameParameters", (void (MidiMessage::*)(int &, int &, int &, int &, MidiMessage::SmpteTimecodeType &) const noexcept)&MidiMessage::getFullFrameParameters)
				.enum_("MidiMachineControlCommand")
				[
					value("mmc_stop", 1),
					value("mmc_play", 2),
					value("mmc_deferredplay", 3),
					value("mmc_fastforward", 4),
					value("mmc_rewind", 5),
					value("mmc_recordStart", 6),
					value("mmc_recordStop", 7),
					value("mmc_pause", 9)
				]
				.scope
				[
					def("noteOn", (MidiMessage (*)(int, int, float) noexcept)&MidiMessage::noteOn),
					def("noteOn", (MidiMessage (*)(int, int, uint8) noexcept)&MidiMessage::noteOn),
					def("noteOff", &MidiMessage::noteOff),
					def("programChange", &MidiMessage::programChange),
					def("pitchWheel", &MidiMessage::pitchWheel),
					def("aftertouchChange", &MidiMessage::aftertouchChange),
					def("channelPressureChange", &MidiMessage::channelPressureChange),
					def("controllerEvent", &MidiMessage::controllerEvent),
					def("allNotesOff", &MidiMessage::allNotesOff),
					def("allSoundOff", &MidiMessage::allSoundOff),
					def("allControllersOff", &MidiMessage::allControllersOff),
					def("endOfTrack", &MidiMessage::endOfTrack),
					def("tempoMetaEvent", &MidiMessage::tempoMetaEvent),
					def("timeSignatureMetaEvent", &MidiMessage::timeSignatureMetaEvent),
					def("midiChannelMetaEvent", &MidiMessage::midiChannelMetaEvent),
					def("midiStart", &MidiMessage::midiStart),
					def("midiContinue", &MidiMessage::midiContinue),
					def("midiStop", &MidiMessage::midiStop),
					def("midiClock", &MidiMessage::midiClock),
					def("songPositionPointer", &MidiMessage::songPositionPointer),
					def("quarterFrame", &MidiMessage::quarterFrame),
					def("fullFrame", (MidiMessage (*)(int,int,int,int,MidiMessage::SmpteTimecodeType))&MidiMessage::fullFrame),
					def("midiMachineControlCommand", &MidiMessage::midiMachineControlCommand),
					def("midiMachineControlGoto", &MidiMessage::midiMachineControlGoto),
					def("masterVolume", &MidiMessage::masterVolume),
					def("createSysExMessage", &MidiMessage::createSysExMessage),
					def("readVariableLengthVal", &MidiMessage::readVariableLengthVal),
					def("getMessageLengthFromFirstByte", &MidiMessage::getMessageLengthFromFirstByte),
					def("getMidiNoteName", &MidiMessage::getMidiNoteName),
					def("getMidiNoteInHertz", &MidiMessage::getMidiNoteInHertz),
					def("getGMInstrumentName", &MidiMessage::getGMInstrumentName),
					def("getGMInstrumentBankName", &MidiMessage::getGMInstrumentBankName),
					def("getRhythmInstrumentName", &MidiMessage::getRhythmInstrumentName),
					def("getControllerName", &MidiMessage::getControllerName)
				]
			];
}