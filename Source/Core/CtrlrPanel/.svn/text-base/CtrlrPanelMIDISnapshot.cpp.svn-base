#include "stdafx.h"
#include "CtrlrComponents/CtrlrComponent.h"
#include "CtrlrLog.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrPanelMIDISnapshot.h"

CtrlrPanelMIDISnapshot::CtrlrPanelMIDISnapshot(CtrlrPanel &_owner) 
	:	owner(_owner), 
		ThreadWithProgressWindow("MIDI Snapshot", true, true),
		snapshotDelay(50)
{
	buffer.ensureSize(8192);
}

CtrlrPanelMIDISnapshot::~CtrlrPanelMIDISnapshot()
{
}

void CtrlrPanelMIDISnapshot::sendSnapshot()
{
	triggerAsyncUpdate();
}

void CtrlrPanelMIDISnapshot::handleAsyncUpdate() 
{
	gatherSnapshotData();
	runThread();
}

void CtrlrPanelMIDISnapshot::gatherSnapshotData()
{
	buffer.clear();

	for (int i=0; i<owner.getModulators().size(); i++)
	{
		CtrlrModulator *m = owner.getModulators()[i];
		if (m->getMidiMessagePtr())
		{
			if (m->getComponent())
			{
				if ((int)m->getComponent()->getProperty(Ids::componentRadioGroupId) > 0)
				{
					if (m->getComponent()->getToggleState() == false)
						continue;
					else if (!(bool)m->getProperty(Ids::modulatorExcludeFromSnapshot))
						addCtrlrMidiMessageToBuffer (buffer, m->getMidiMessage());
				}
				else if (!(bool)m->getProperty(Ids::modulatorExcludeFromSnapshot))
				{
					addCtrlrMidiMessageToBuffer (buffer, m->getMidiMessage());
				}
			}
		}
	}
}

void CtrlrPanelMIDISnapshot::run()
{
	MidiBuffer::Iterator i(buffer);
	MidiMessage m; int t; int k=0;
	while (i.getNextEvent(m,t))
	{
		setProgress (k / (double) buffer.getNumEvents());
		owner.sendMidi(m);
		
		k++;

		wait(snapshotDelay);
	}
}

void CtrlrPanelMIDISnapshot::setDelay(const int _snapshotDelay)
{
	snapshotDelay = _snapshotDelay;
}