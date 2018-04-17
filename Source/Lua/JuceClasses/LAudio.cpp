#include "stdafx.h"
#include "LJuce.h"
/*
void LAudioFile::wrapForLua(lua_State *L)
{
	using namespace luabind;
	module(L)
    [
		class_<AiffAudioFormat>("AiffAudioFormat")
			.def(constructor<>())
			.def("canDoStereo", &AiffAudioFormat::canDoStereo)
			.def("canDoMono", &AiffAudioFormat::canDoMono)
			.def("canHandleFile", &AiffAudioFormat::canHandleFile)
			.def("createReaderFor", &AiffAudioFormat::createReaderFor)
			.def("createWriterFor", &AiffAudioFormat::createWriterFor)
		,
		class_<WavAudioFormat>("WavAudioFormat")
			.def(constructor<>())
			.def("canDoStereo", &WavAudioFormat::canDoStereo)
			.def("canDoMono", &WavAudioFormat::canDoMono)
			.def("canHandleFile", &WavAudioFormat::canHandleFile)
			.def("createReaderFor", &WavAudioFormat::createReaderFor)
			//.def("createWriterFor", &WavAudioFormat::createWriterFor)
			.def("replaceMetadataInFile", &WavAudioFormat::replaceMetadataInFile)
			.def("createBWAVMetadata", &WavAudioFormat::createBWAVMetadata)
		,
		class_<OggVorbisAudioFormat>("OggVorbisAudioFormat")
			.def(constructor<>())
			.def("canDoStereo", &OggVorbisAudioFormat::canDoStereo)
			.def("canDoMono", &OggVorbisAudioFormat::canDoMono)
			.def("canHandleFile", &OggVorbisAudioFormat::canHandleFile)
			.def("createReaderFor", &OggVorbisAudioFormat::createReaderFor)
			.def("createWriterFor", &OggVorbisAudioFormat::createWriterFor)
			.def("isCompressed", &OggVorbisAudioFormat::isCompressed)
			.def("getQualityOptions", &OggVorbisAudioFormat::getQualityOptions)
			.def("estimateOggFileQuality", &OggVorbisAudioFormat::estimateOggFileQuality)
		,
		class_<FlacAudioFormat>("FlacAudioFormat")
			.def(constructor<>())
			.def("canDoStereo", &FlacAudioFormat::canDoStereo)
			.def("canDoMono", &FlacAudioFormat::canDoMono)
			.def("canHandleFile", &FlacAudioFormat::canHandleFile)
			.def("createReaderFor", &FlacAudioFormat::createReaderFor)
			.def("createWriterFor", &FlacAudioFormat::createWriterFor)
			.def("isCompressed", &FlacAudioFormat::isCompressed)
			.def("getQualityOptions", &FlacAudioFormat::getQualityOptions)
	];
}

void LAudioFormat::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<int64>("int64")
		,
		class_<AudioFormatReader>("AudioFormatReader")
				.def("getFormatName", &AudioFormatReader::getFormatName)
				.def("read", (bool (AudioFormatReader::*)(int *const *, int, int64, int, bool))&AudioFormatReader::read)
				.def("read", (void (AudioFormatReader::*)(AudioSampleBuffer *, int, int, int64, bool, bool))&AudioFormatReader::read)
				.def("readMaxLevels", (void (AudioFormatReader::*)(int64, int64, float&, float&, float&, float&))&AudioFormatReader::readMaxLevels)
				.def("searchForLevel", &AudioFormatReader::searchForLevel)
				.def_readonly("sampleRate", &AudioFormatReader::sampleRate)
				.def_readonly("bitsPerSample", &AudioFormatReader::bitsPerSample)
				.def_readonly("lengthInSamples", &AudioFormatReader::lengthInSamples)
				.def_readonly("numChannels", &AudioFormatReader::numChannels)
				.def_readonly("usesFloatingPointData", &AudioFormatReader::usesFloatingPointData)
				.def_readonly("metadataValues", &AudioFormatReader::metadataValues)
				.def_readonly("input", &AudioFormatReader::input)
		,
			class_<AudioFormatWriter>("AudioFormatWriter")
				.def("getFormatName", &AudioFormatWriter::getFormatName)
				.def("writeFromAudioReader", &AudioFormatWriter::writeFromAudioReader)
				.def("writeFromAudioSource", &AudioFormatWriter::writeFromAudioSource)
				.def("writeFromAudioSampleBuffer", &AudioFormatWriter::writeFromAudioSampleBuffer)
				.def("getSampleRate", &AudioFormatWriter::getSampleRate)
				.def("getNumChannels", &AudioFormatWriter::getNumChannels)
				.def("getBitsPerSample", &AudioFormatWriter::getBitsPerSample)
				.def("isFloatingPoint", &AudioFormatWriter::isFloatingPoint)
		,
			class_<AudioFormat>("AudioFormat")
				.def("getFormatName", &AudioFormat::getFormatName)
				.def("getFileExtensions", &AudioFormat::getFileExtensions)
				.def("canHandleFile", &AudioFormat::canHandleFile)
				.def("canDoStereo", &AudioFormat::canDoStereo)
				.def("canDoMono", &AudioFormat::canDoMono)
				.def("isCompressed", &AudioFormat::isCompressed)
				.def("getQualityOptions", &AudioFormat::getQualityOptions)
				.def("canDoMono", &AudioFormat::canDoMono)
		,
			class_<AudioFormatManager>("JAudioFormatManager")
			,
			class_<LAudioFormatManager, bases<AudioFormatManager> >("AudioFormatManager")
				.def(constructor<>())
				.def("registerBasicFormats", &AudioFormatManager::registerBasicFormats)
				.def("getNumKnownFormats", &AudioFormatManager::getNumKnownFormats)
				.def("getKnownFormat", &AudioFormatManager::getKnownFormat)
				.def("findFormatForFileExtension", &AudioFormatManager::findFormatForFileExtension)
				.def("getDefaultFormat", &AudioFormatManager::getDefaultFormat)
				.def("getWildcardForAllFormats", &AudioFormatManager::getWildcardForAllFormats)
				.def("createReaderFor", &LAudioFormatManager::createReaderFor)
		,
			class_<AudioThumbnailCache>("AudtioThumbnailCache")
				.def(constructor<int>())
				.def("clear", &AudioThumbnailCache::clear)
				.def("loadThumb", &AudioThumbnailCache::loadThumb)
				.def("storeThumb", &AudioThumbnailCache::storeThumb)
				.def("removeThumb", &AudioThumbnailCache::removeThumb)
				.def("readFromStream", &AudioThumbnailCache::readFromStream)
				.def("writeToStream", &AudioThumbnailCache::writeToStream)
				.def("getTimeSliceThread", &AudioThumbnailCache::getTimeSliceThread)
	];
}

void LAudioPlayHead::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<AudioPlayHead>("AudioPlayHead")
			.def("getCurrentPosition", &AudioPlayHead::getCurrentPosition)
			.enum_("FrameRateType")
			[
                value("fps24", AudioPlayHead::fps24),
                value("fps25", AudioPlayHead::fps25),
                value("fps2997", AudioPlayHead::fps2997),
                value("fps30", AudioPlayHead::fps30),
                value("fps2997drop", AudioPlayHead::fps2997drop),
                value("fps30drop", AudioPlayHead::fps30drop),
                value("fpsUnknown", AudioPlayHead::fpsUnknown)
			]
        ,
        class_<AudioPlayHead::CurrentPositionInfo>("CurrentPositionInfo")
            .def_readonly ("bpm", &AudioPlayHead::CurrentPositionInfo::bpm)
            .def_readonly ("timeSignNumerator", &AudioPlayHead::CurrentPositionInfo::timeSigNumerator)
            .def_readonly ("timeSigDenominator", &AudioPlayHead::CurrentPositionInfo::timeSigDenominator)
            .def_readonly ("timeInSamples", &AudioPlayHead::CurrentPositionInfo::timeInSamples)
            .def_readonly ("timeInSeconds", &AudioPlayHead::CurrentPositionInfo::timeInSeconds)
            .def_readonly ("editOriginTime", &AudioPlayHead::CurrentPositionInfo::editOriginTime)
            .def_readonly ("ppqPosition", &AudioPlayHead::CurrentPositionInfo::ppqPosition)
            .def_readonly ("ppqPositionOfLastBarStart", &AudioPlayHead::CurrentPositionInfo::ppqPositionOfLastBarStart)
            .def_readonly ("frameRate", &AudioPlayHead::CurrentPositionInfo::frameRate)
            .def_readonly ("isPlaying", &AudioPlayHead::CurrentPositionInfo::isPlaying)
            .def_readonly ("isRecording", &AudioPlayHead::CurrentPositionInfo::isRecording)
            .def_readonly ("ppqLoopStart", &AudioPlayHead::CurrentPositionInfo::ppqLoopStart)
            .def_readonly ("ppqLoopEnd", &AudioPlayHead::CurrentPositionInfo::ppqLoopEnd)
            .def_readonly ("isLooping", &AudioPlayHead::CurrentPositionInfo::isLooping)
	];
}

void LAudioSampleBuffer::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<AudioSampleBuffer>("AudioSampleBuffer")
				.def(constructor<int, int>())
				.def(constructor<float *const *, int, int>())
				.def(constructor<float *const *, int, int, int>())
				.def("getNumChannels", &AudioSampleBuffer::getNumChannels)
				.def("getNumSamples", &AudioSampleBuffer::getNumSamples)
				//.def("getSampleData", (float *(AudioSampleBuffer::*)(int) noexcept)&AudioSampleBuffer::getSampleData)
				//.def("getSampleData", (float *(AudioSampleBuffer::*)(int, int) noexcept)&AudioSampleBuffer::getSampleData)
				.def("getArrayOfChannels", &AudioSampleBuffer::getArrayOfWritePointers)
				.def("getArrayOfWritePointers", &AudioSampleBuffer::getArrayOfWritePointers)
				.def("setSize", &AudioSampleBuffer::setSize)
				//.def("setDataToReferTo", &AudioSampleBuffer::setDataToReferTo)
				.def("clear", (void (AudioSampleBuffer::*)(void))&AudioSampleBuffer::clear)
				.def("clear", (void (AudioSampleBuffer::*)(int,int))&AudioSampleBuffer::clear)
				.def("clear", (void (AudioSampleBuffer::*)(int,int,int))&AudioSampleBuffer::clear)
				.def("applyGain", (void (AudioSampleBuffer::*)(int,int,int,float))&AudioSampleBuffer::applyGain)
				.def("applyGain", (void (AudioSampleBuffer::*)(int,int,float))&AudioSampleBuffer::applyGain)
				// .def("applyGainRamp", &AudioSampleBuffer::applyGainRamp)
				.def("addFrom", (void (AudioSampleBuffer::*)(int,int,const AudioSampleBuffer&, int, int, int, float))&AudioSampleBuffer::addFrom)
				.def("addFrom", (void (AudioSampleBuffer::*)(int,int,const float *, int, float))&AudioSampleBuffer::addFrom)
				.def("addFromWithRamp", (void (AudioSampleBuffer::*)(int,int,const float *,int,float,float))&AudioSampleBuffer::addFromWithRamp)
				.def("copyFrom", (void (AudioSampleBuffer::*)(int,int,const AudioSampleBuffer&, int, int, int))&AudioSampleBuffer::copyFrom)
				.def("copyFrom", (void (AudioSampleBuffer::*)(int,int,const float *, int))&AudioSampleBuffer::copyFrom)
				.def("copyFrom", (void (AudioSampleBuffer::*)(int,int,const float *, int, float))&AudioSampleBuffer::copyFrom)
				.def("copyFromWithRamp", (void (AudioSampleBuffer::*)(int,int,const float *,int,float,float) const noexcept)&AudioSampleBuffer::copyFromWithRamp)
				.def("findMinMax", &AudioSampleBuffer::findMinMax)
				.def("getMagnitude", (float (AudioSampleBuffer::*)(int,int,int) const noexcept)&AudioSampleBuffer::getMagnitude)
				.def("getMagnitude", (float (AudioSampleBuffer::*)(int,int) const noexcept)&AudioSampleBuffer::getMagnitude)
				.def("getRMSLevel", &AudioSampleBuffer::getRMSLevel)
	];
}

void LAudioThumbnail::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<AudioThumbnail>("AudioThumbnail")
			.def(constructor<int, AudioFormatManager &, AudioThumbnailCache &>())
			.def("clear", &AudioThumbnail::clear)
			.def("setSource", &AudioThumbnail::setSource)
			.def("setReader", &AudioThumbnail::setReader)
			.def("reset", &AudioThumbnail::reset)
			.def("addBlock", &AudioThumbnail::addBlock)
			.def("loadFrom", &AudioThumbnail::loadFrom)
			.def("saveTo", &AudioThumbnail::saveTo)
			.def("getNumChannels", &AudioThumbnail::getNumChannels)
			.def("getTotalLength", &AudioThumbnail::getNumChannels)
			.def("drawChannel", &AudioThumbnail::drawChannel)
			.def("drawChannels", &AudioThumbnail::drawChannels)
			.def("isFullyLoaded", &AudioThumbnail::isFullyLoaded)
			.def("getProportionComplete", &AudioThumbnail::getProportionComplete)
			.def("getNumSamplesFinished", &AudioThumbnail::getNumSamplesFinished)
			.def("getApproximatePeak", &AudioThumbnail::getApproximatePeak)
			.def("getApproximateMinMax", &AudioThumbnail::getApproximateMinMax)
			.def("getHashCode", &AudioThumbnail::getHashCode)
	];
}

void LMidiBuffer::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<MidiBuffer>("MidiBuffer")
            .def(constructor<>())
            .def(constructor<const MidiMessage &>())
            .def(constructor<const MidiBuffer &>())
            .def("clear", (void (MidiBuffer::*)(void))&MidiBuffer::clear)
            .def("clear", (void (MidiBuffer::*)(int, int)) &MidiBuffer::clear)
            .def("isEmpty", &MidiBuffer::isEmpty)
            .def("getNumEvents", &MidiBuffer::getNumEvents)
            .def("addEvent", (void (MidiBuffer::*)(const MidiMessage &, int)) &MidiBuffer::addEvent)
            .def("addEvents", (void (MidiBuffer::*)(const MidiBuffer &, int, int, int)) &MidiBuffer::addEvents)
            .def("getFirstEventTime", &MidiBuffer::getFirstEventTime)
            .def("getLastEventTime", &MidiBuffer::getLastEventTime)
            .def("swapWith", &MidiBuffer::swapWith)
            .def("ensureSize", &MidiBuffer::ensureSize)
        ,
        class_<MidiBuffer::Iterator>("MidiBufferIterator")
            .def(constructor<const MidiBuffer &>())
            .def("setNextSamplePosition", &MidiBuffer::Iterator::setNextSamplePosition)
            .def("getNextEvent", (bool (MidiBuffer::Iterator::*)(MidiMessage &, int &)) &MidiBuffer::Iterator::getNextEvent)
    ];
}

void LMidiKeyboardComponent::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<MidiKeyboardComponent>("MidiKeyboardComponent")
	];
}

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
					def("noteOff", (MidiMessage (*)(int, int, float) noexcept)&MidiMessage::noteOff),
					def("noteOff", (MidiMessage (*)(int, int, uint8) noexcept)&MidiMessage::noteOff),
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
*/