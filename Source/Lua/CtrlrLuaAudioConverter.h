#ifndef CTRLR_LUA_AUDIO_CONVERTER
#define CTRLR_LUA_AUDIO_CONVERTER

#ifdef _WIN32
#pragma warning(disable:4100)
#endif // _WIN32

#include "CtrlrMacros.h"
#include "JuceClasses/LMemoryBlock.h"

//==============================================================================
/** @brief A class for holding audio samples
 *
 */
class CtrlrLuaAudioConverter
{
	public:
		CtrlrLuaAudioConverter();
		~CtrlrLuaAudioConverter();

		/** @brief Convert a block of data in the format of 8bit (1 byte) signed data, to a floating point AudioSampleBuffer

			@param	sourceData	a MemoryBlock of data that holds the raw samples
			@param	destination	the destination AudioSampleBuffer to write samples to
			@param	numSamples	how many samples to convert
			@param	numChannels	how many audio channels to convert
			@param	interleaved	if there is more then 1 audio channel, this tells the converter if the samples are interleaved or not
		*/
		void convertInt8 (MemoryBlock &sourceData, AudioSampleBuffer &destination, const int numSamples, const int numChannels=1, const bool interleaved=false);

		/** @brief Convert a block of data in the format of 8bit (1 byte) unsigned data, to a floating point AudioSampleBuffer

			@param	sourceData	a MemoryBlock of data that holds the raw samples
			@param	destination	the destination AudioSampleBuffer to write samples to
			@param	numSamples	how many samples to convert
			@param	numChannels	how many audio channels to convert
			@param	interleaved	if there is more then 1 audio channel, this tells the converter if the samples are interleaved or not
		*/
		void convertUInt8 (MemoryBlock &sourceData, AudioSampleBuffer &destination, const int numSamples, const int numChannels=1, const bool interleaved=false);

		/** @brief Convert a block of data in the format of 16bit (2 bytes) signed data, to a floating point AudioSampleBuffer

			@param	sourceData	a MemoryBlock of data that holds the raw samples
			@param	destination	the destination AudioSampleBuffer to write samples to
			@param	numSamples	how many samples to convert
			@param	numChannels	how many audio channels to convert
			@param	interleaved	if there is more then 1 audio channel, this tells the converter if the samples are interleaved or not
		*/
		void convertInt16 (MemoryBlock &sourceData, AudioSampleBuffer &destination, const int numSamples, const int numChannels=1, const bool interleaved=false);

		/** @brief Convert a block of data in the format of 16bit (2 bytes) unsigned data, to a floating point AudioSampleBuffer

			@param	sourceData	a MemoryBlock of data that holds the raw samples
			@param	destination	the destination AudioSampleBuffer to write samples to
			@param	numSamples	how many samples to convert
			@param	numChannels	how many audio channels to convert
			@param	interleaved	if there is more then 1 audio channel, this tells the converter if the samples are interleaved or not
		*/
		void convertUInt16 (MemoryBlock &sourceData, AudioSampleBuffer &destination, const int numSamples, const int numChannels=1, const bool interleaved=false);

		/** @brief Convert a block of data in the format of 24bit (3 bytes) signed data, to a floating point AudioSampleBuffer

			@param	sourceData	a MemoryBlock of data that holds the raw samples
			@param	destination	the destination AudioSampleBuffer to write samples to
			@param	numSamples	how many samples to convert
			@param	numChannels	how many audio channels to convert
			@param	interleaved	if there is more then 1 audio channel, this tells the converter if the samples are interleaved or not
		*/
		void convertInt24 (MemoryBlock &sourceData, AudioSampleBuffer &destination, const int numSamples, const int numChannels=1, const bool interleaved=false);

		/** @brief Convert a block of data in the format of 32bit (4 bytes) signed data, to a floating point AudioSampleBuffer

			@param	sourceData	a MemoryBlock of data that holds the raw samples
			@param	destination	the destination AudioSampleBuffer to write samples to
			@param	numSamples	how many samples to convert
			@param	numChannels	how many audio channels to convert
			@param	interleaved	if there is more then 1 audio channel, this tells the converter if the samples are interleaved or not
		*/
		void convertInt32 (MemoryBlock &sourceData, AudioSampleBuffer &destination, const int numSamples, const int numChannels=1, const bool interleaved=false);

		LMemoryBlock convertToUInt8 (AudioFormatReader *sourceFormatReader, const int numSamples, const int sampleOffset, const int channel, const bool sourceIsInterleaved);

		static void wrapForLua(lua_State *L);
};

#endif
