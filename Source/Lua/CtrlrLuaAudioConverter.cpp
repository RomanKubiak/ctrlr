#include "stdafx.h"
#include "CtrlrLuaAudioConverter.h"
#include "CtrlrLog.h"
#include "CtrlrUtilities.h"
#include "JuceClasses/LMemoryBlock.h"

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