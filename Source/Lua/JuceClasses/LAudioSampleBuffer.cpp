#include "stdafx.h"
#include "LAudioSampleBuffer.h"

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
				.def("setDataToReferTo", &AudioSampleBuffer::setDataToReferTo)
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
