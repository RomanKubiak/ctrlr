#include "stdafx.h"
#include "CtrlrLuaAudioConverter.h"
#include "CtrlrLog.h"
#include "CtrlrUtilities.h"
#include "JuceClasses/LMemoryBlock.h"

class CtrlrUInt16
{
public:
	inline CtrlrUInt16(void* d) noexcept : data(static_cast <uint16*> (d)) {}

	inline void advance() noexcept {
		++data;
	}
	inline void skip(int numSamples) noexcept {
		data += numSamples;
	}
	inline float getAsFloatLE() const noexcept {
		return (float)((1.0 / (1.0 + maxValue)) * (uint16)ByteOrder::swapIfBigEndian(*data));
	}
	inline float getAsFloatBE() const noexcept {
		return (float)((1.0 / (1.0 + maxValue)) * (uint16)ByteOrder::swapIfLittleEndian(*data));
	}
	inline void setAsFloatLE(float newValue) noexcept {
		*data = ByteOrder::swapIfBigEndian((uint16)jlimit<uint16>((uint16)-maxValue, (uint16)maxValue, roundToInt(newValue * (1.0 + maxValue))));
	}
	inline void setAsFloatBE(float newValue) noexcept {
		*data = ByteOrder::swapIfLittleEndian((uint16)jlimit<uint16>((uint16)-maxValue, (uint16)maxValue, roundToInt(newValue * (1.0 + maxValue))));
	}
	inline int32 getAsInt32LE() const noexcept {
		return (int32)(ByteOrder::swapIfBigEndian((uint16)*data) << 16);
	}
	inline int32 getAsInt32BE() const noexcept {
		return (int32)(ByteOrder::swapIfLittleEndian((uint16)*data) << 16);
	}
	inline void setAsInt32LE(int32 newValue) noexcept {
		*data = ByteOrder::swapIfBigEndian((uint16)(newValue >> 16));
	}
	inline void setAsInt32BE(int32 newValue) noexcept {
		*data = ByteOrder::swapIfLittleEndian((uint16)(newValue >> 16));
	}
	inline void clear() noexcept {
		*data = 0;
	}
	inline void clearMultiple(int num) noexcept {
		zeromem(data, (size_t)(num * bytesPerSample));
	}
	template <class SourceType> inline void copyFromLE(SourceType& source) noexcept {
		setAsInt32LE(source.getAsInt32());
	}
	template <class SourceType> inline void copyFromBE(SourceType& source) noexcept {
		setAsInt32BE(source.getAsInt32());
	}
	inline void copyFromSameType(CtrlrUInt16& source) noexcept {
		*data = *source.data;
	}

	uint16* data;
	enum {
		bytesPerSample = 2, maxValue = 0xffff, resolution = (1 << 16), isFloat = 0
	};
};

CtrlrLuaAudioConverter::CtrlrLuaAudioConverter()
{
}

CtrlrLuaAudioConverter::~CtrlrLuaAudioConverter()
{
}

void CtrlrLuaAudioConverter::convertInt8 (MemoryBlock &sourceData, AudioSampleBuffer &destination, const int numSamples, const int numChannels, const bool interleaved)
{
	if (interleaved)
	{
		AudioData::ConverterInstance <	AudioData::Pointer <AudioData::Int8,
																		AudioData::NativeEndian,
																		AudioData::Interleaved,
																		AudioData::Const>, 
													AudioData::Pointer <AudioData::Float32,
																		AudioData::NativeEndian,
																		AudioData::Interleaved,
																		AudioData::NonConst>
									> converter;
		for (int ch=0; ch<numChannels; ch++)
		{
			converter.convertSamples ((void *)destination.getReadPointer(ch), sourceData.getData(), numSamples);
		}
	}
	else
	{
		AudioData::ConverterInstance <	AudioData::Pointer <AudioData::Int8,
																		AudioData::NativeEndian,
																		AudioData::NonInterleaved,
																		AudioData::Const>, 
													AudioData::Pointer <AudioData::Float32,
																		AudioData::NativeEndian,
																		AudioData::Interleaved,
																		AudioData::NonConst>
									> converter;
		for (int ch=0; ch<numChannels; ch++)
		{
			converter.convertSamples ((void *)destination.getReadPointer(ch), ch, sourceData.getData(), ch, numSamples);
		}
	}
}

void CtrlrLuaAudioConverter::convertUInt8 (MemoryBlock &sourceData, AudioSampleBuffer &destination, const int numSamples, const int numChannels, const bool interleaved)
{
	if (interleaved)
	{
		AudioData::ConverterInstance <	AudioData::Pointer <AudioData::UInt8,
																		AudioData::NativeEndian,
																		AudioData::Interleaved,
																		AudioData::Const>, 
													AudioData::Pointer <AudioData::Float32,
																		AudioData::NativeEndian,
																		AudioData::Interleaved,
																		AudioData::NonConst>
									> converter;
		for (int ch=0; ch<numChannels; ch++)
		{
			converter.convertSamples ((void *)destination.getReadPointer(ch), sourceData.getData(), numSamples);
		}
	}
	else
	{
		AudioData::ConverterInstance <	AudioData::Pointer <AudioData::UInt8,
																		AudioData::NativeEndian,
																		AudioData::NonInterleaved,
																		AudioData::Const>, 
													AudioData::Pointer <AudioData::Float32,
																		AudioData::NativeEndian,
																		AudioData::Interleaved,
																		AudioData::NonConst>
									> converter;
		for (int ch=0; ch<numChannels; ch++)
		{
			converter.convertSamples ((void *)destination.getReadPointer(ch), ch, sourceData.getData(), ch, numSamples);
		}
	}
}

void CtrlrLuaAudioConverter::convertInt16 (MemoryBlock &sourceData, AudioSampleBuffer &destination, const int numSamples, const int numChannels, const bool interleaved)
{
	if (interleaved)
	{
		AudioData::ConverterInstance <	AudioData::Pointer <AudioData::Int16,
																		AudioData::NativeEndian,
																		AudioData::Interleaved,
																		AudioData::Const>, 
													AudioData::Pointer <AudioData::Float32,
																		AudioData::NativeEndian,
																		AudioData::Interleaved,
																		AudioData::NonConst>
									> converter;
		for (int ch=0; ch<numChannels; ch++)
		{
			converter.convertSamples ((void *)destination.getReadPointer(ch), sourceData.getData(), numSamples);
		}
	}
	else
	{
		AudioData::ConverterInstance <	AudioData::Pointer <AudioData::Int16,
																		AudioData::NativeEndian,
																		AudioData::NonInterleaved,
																		AudioData::Const>, 
													AudioData::Pointer <AudioData::Float32,
																		AudioData::NativeEndian,
																		AudioData::Interleaved,
																		AudioData::NonConst>
									> converter;
		for (int ch=0; ch<numChannels; ch++)
		{
			converter.convertSamples ((void *)destination.getReadPointer(ch), ch, sourceData.getData(), ch, numSamples);
		}
	}
}

void CtrlrLuaAudioConverter::convertUInt16 (MemoryBlock &sourceData, AudioSampleBuffer &destination, const int numSamples, const int numChannels, const bool interleaved)
{
	if (interleaved)
	{
		AudioData::ConverterInstance <	AudioData::Pointer <CtrlrUInt16,
																		AudioData::NativeEndian,
																		AudioData::Interleaved,
																		AudioData::Const>, 
													AudioData::Pointer <AudioData::Float32,
																		AudioData::NativeEndian,
																		AudioData::Interleaved,
																		AudioData::NonConst>
									> converter;
		for (int ch=0; ch<numChannels; ch++)
		{
			converter.convertSamples ((void *)destination.getReadPointer(ch), sourceData.getData(), numSamples);
		}
	}
	else
	{
		AudioData::ConverterInstance <	AudioData::Pointer <CtrlrUInt16,
																		AudioData::NativeEndian,
																		AudioData::NonInterleaved,
																		AudioData::Const>, 
													AudioData::Pointer <AudioData::Float32,
																		AudioData::NativeEndian,
																		AudioData::Interleaved,
																		AudioData::NonConst>
									> converter;
		for (int ch=0; ch<numChannels; ch++)
		{
			converter.convertSamples ((void *)destination.getReadPointer(ch), ch, sourceData.getData(), ch, numSamples);
		}
	}
}

void CtrlrLuaAudioConverter::convertInt24 (MemoryBlock &sourceData, AudioSampleBuffer &destination, const int numSamples, const int numChannels, const bool interleaved)
{
	if (interleaved)
	{
		AudioData::ConverterInstance <	AudioData::Pointer <AudioData::Int24,
																		AudioData::NativeEndian,
																		AudioData::Interleaved,
																		AudioData::Const>, 
													AudioData::Pointer <AudioData::Float32,
																		AudioData::NativeEndian,
																		AudioData::Interleaved,
																		AudioData::NonConst>
									> converter;
		for (int ch=0; ch<numChannels; ch++)
		{
			converter.convertSamples ((void *)destination.getReadPointer(ch), sourceData.getData(), numSamples);
		}
	}
	else
	{
		AudioData::ConverterInstance <	AudioData::Pointer <AudioData::Int24,
																		AudioData::NativeEndian,
																		AudioData::NonInterleaved,
																		AudioData::Const>, 
													AudioData::Pointer <AudioData::Float32,
																		AudioData::NativeEndian,
																		AudioData::Interleaved,
																		AudioData::NonConst>
									> converter;
		for (int ch=0; ch<numChannels; ch++)
		{
			converter.convertSamples ((void *)destination.getReadPointer(ch), ch, sourceData.getData(), ch, numSamples);
		}
	}
}

void CtrlrLuaAudioConverter::convertInt32 (MemoryBlock &sourceData, AudioSampleBuffer &destination, const int numSamples, const int numChannels, const bool interleaved)
{
	if (interleaved)
	{
		AudioData::ConverterInstance <	AudioData::Pointer <AudioData::Int32,
																		AudioData::NativeEndian,
																		AudioData::Interleaved,
																		AudioData::Const>, 
													AudioData::Pointer <AudioData::Float32,
																		AudioData::NativeEndian,
																		AudioData::Interleaved,
																		AudioData::NonConst>
									> converter;
		for (int ch=0; ch<numChannels; ch++)
		{
			converter.convertSamples ((void *)destination.getReadPointer(ch), sourceData.getData(), numSamples);
		}
	}
	else
	{
		AudioData::ConverterInstance <	AudioData::Pointer <AudioData::Int32,
																		AudioData::NativeEndian,
																		AudioData::NonInterleaved,
																		AudioData::Const>, 
													AudioData::Pointer <AudioData::Float32,
																		AudioData::NativeEndian,
																		AudioData::Interleaved,
																		AudioData::NonConst>
									> converter;
		for (int ch=0; ch<numChannels; ch++)
		{
			converter.convertSamples ((void *)destination.getReadPointer(ch), ch, sourceData.getData(), ch, numSamples);
		}
	}
}

LMemoryBlock CtrlrLuaAudioConverter::convertToUInt8 (AudioFormatReader *sourceFormatReader, const int numSamples, const int sampleOffset, const int sourceChannel, const bool sourceIsInterleaved)
{
	AudioSampleBuffer tempBuffer (1, numSamples);
	MemoryBlock mb(numSamples, true);

	if (sourceFormatReader)
	{
		sourceFormatReader->read (&tempBuffer, 0, numSamples, sampleOffset, true, true);

		if (sourceIsInterleaved)
		{
			AudioData::ConverterInstance <	AudioData::Pointer <AudioData::Float32,
											AudioData::NativeEndian,
											AudioData::Interleaved,
											AudioData::Const>, 
										AudioData::Pointer <AudioData::UInt8,
											AudioData::NativeEndian,
											AudioData::Interleaved,
											AudioData::NonConst>
									> converter;

			converter.convertSamples (mb.getData(), tempBuffer.getReadPointer (sourceChannel, 0), numSamples);
		}
		else
		{
			AudioData::ConverterInstance <	AudioData::Pointer <AudioData::Float32,
											AudioData::NativeEndian,
											AudioData::NonInterleaved,
											AudioData::Const>, 
										AudioData::Pointer <AudioData::UInt8,
											AudioData::NativeEndian,
											AudioData::Interleaved,
											AudioData::NonConst>
									> converter;

			converter.convertSamples (mb.getData(), tempBuffer.getReadPointer (sourceChannel, 0), numSamples);
		}
	}

	return (mb);
}

void CtrlrLuaAudioConverter::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrLuaAudioConverter>("CtrlrLuaAudioConverter")
			.def(constructor<>())
			.def("convertInt8", &CtrlrLuaAudioConverter::convertInt8)
			.def("convertUInt8", &CtrlrLuaAudioConverter::convertUInt8)
			.def("convertInt16", &CtrlrLuaAudioConverter::convertInt16)
			.def("convertUInt16", &CtrlrLuaAudioConverter::convertUInt16)
			.def("convertInt24", &CtrlrLuaAudioConverter::convertInt24)
			.def("convertInt32", &CtrlrLuaAudioConverter::convertInt32)
			.def("convertToUInt8", &CtrlrLuaAudioConverter::convertToUInt8)
	];
}