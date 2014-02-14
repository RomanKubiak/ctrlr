#include "stdafx.h"
#include "CtrlrMIDIFilter.h"

CtrlrMIDIFilterSet::CtrlrMIDIFilterSet() : filterTree(Ids::midiFilter)
{
}

CtrlrMIDIFilterSet::~CtrlrMIDIFilterSet()
{
}

void CtrlrMIDIFilterSet::process (MidiBuffer &eventsToProcess)
{
}

bool CtrlrMIDIFilterSet::process (const MidiMessage &eventToProcess)
{
	return (false);
}
