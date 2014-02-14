#include "stdafx.h"
#include "LAudioFile.h"

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
			.def("createWriterFor", &WavAudioFormat::createWriterFor)
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