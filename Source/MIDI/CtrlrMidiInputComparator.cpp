#include "stdafx.h"
#include <algorithm>
#include <limits>
#include "CtrlrMidiInputComparator.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrProcessor.h"
#include "CtrlrLog.h"

CtrlrMidiInputComparator::CtrlrMidiInputComparator(CtrlrPanel &_owner)
	: owner(_owner), comparatorSingle(_owner), comparatorMulti(_owner), lastPanelMode(false)
{
}

CtrlrMidiInputComparator::~CtrlrMidiInputComparator()
{
}

void CtrlrMidiInputComparator::clear()
{
	comparatorSingle.clear();
	comparatorMulti.clear();
}

void CtrlrMidiInputComparator::match (const MidiMessage &m)
{
	comparatorSingle.match(m);
	comparatorMulti.match(m);
}

void CtrlrMidiInputComparator::match (const MidiBuffer &buffer)
{
	if (buffer.getNumEvents() == 0)
		return;

	MidiBuffer::Iterator i(buffer);
	MidiMessage m;
	int time;

	while (i.getNextEvent(m,time))
	{
		comparatorSingle.match(m);
		comparatorMulti.match(m);
	}

	owner.panelReceivedMidi (buffer);
}

void CtrlrMidiInputComparator::addMatchTarget (CtrlrModulator *modulatorToAdd)
{
	const CtrlrMidiMessageType type = modulatorToAdd->getMidiMessage().getMidiMessageType();

	switch (type)
	{
		case CC:
		case Aftertouch:
		case NoteOn:
		case NoteOff:
		case ChannelPressure:
		case ProgramChange:
		case PitchWheel:
		case SysEx:
			comparatorSingle.addMatchTarget (modulatorToAdd);
			break;

		case Multi:
			comparatorMulti.addMatchTarget (modulatorToAdd);
			break;

		case None:
			break;

		default:
			//_WRN("CtrlrMidiInputComparator::addMatchTarget an unknown midi type found="+String((int)type));
			break;
	}
}

void CtrlrMidiInputComparator::panelEditModeChanged (const bool _panelEditMode)
{
	clear();

	if (_panelEditMode == false)
	{
		rehashComparator();
	}
}

void CtrlrMidiInputComparator::rehashComparator()
{
	OwnedArray <CtrlrModulator,CriticalSection> &targets = owner.getModulators();

	for (int i=0; i<targets.size(); i++)
	{
		if (targets[i]->getMidiMessagePtr())
		{
			addMatchTarget (targets[i]);
		}
	}
}

const String CtrlrMidiInputComparator::dumpTables()
{
	return (comparatorSingle.dumpTableContents() + comparatorMulti.dumpTableContents());
}

void CtrlrMidiInputComparator::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrMidiInputComparator>("CtrlrMidiInputComparator")
            .def("rehashComparator", &CtrlrMidiInputComparator::rehashComparator)
            .def("dumpTables", &CtrlrMidiInputComparator::dumpTables)
            .def("clear", &CtrlrMidiInputComparator::clear)
            .def("addMatchTarget", &CtrlrMidiInputComparator::addMatchTarget)
            .def("match", (void(CtrlrMidiInputComparator::*)(const MidiMessage &)) &CtrlrMidiInputComparator::match )
            .def("match", (void(CtrlrMidiInputComparator::*)(const MidiBuffer &)) &CtrlrMidiInputComparator::match )
    ];
}
