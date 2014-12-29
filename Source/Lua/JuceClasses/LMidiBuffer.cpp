#include "stdafx.h"
#include "LMidiBuffer.h"

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
