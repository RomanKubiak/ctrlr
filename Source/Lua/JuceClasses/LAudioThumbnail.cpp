#include "stdafx.h"
#include "LAudioThumbnail.h"

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
