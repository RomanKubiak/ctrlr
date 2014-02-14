#include "stdafx.h"
#include "LAudioFormat.h"

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
				.def("readMaxLevels", &AudioFormatReader::readMaxLevels)
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
