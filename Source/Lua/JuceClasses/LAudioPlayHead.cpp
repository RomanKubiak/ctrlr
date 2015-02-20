#include "stdafx.h"
#include "LAudioPlayHead.h"

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
