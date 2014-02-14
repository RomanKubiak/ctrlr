#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanelProcessor.h"
#include "CtrlrPanel.h"
#include "CtrlrProcessor.h"

CtrlrPanelProcessor::CtrlrPanelProcessor(CtrlrPanel &_owner) : owner(_owner)
{
	junkBuffer.ensureSize (8192);
}

CtrlrPanelProcessor::~CtrlrPanelProcessor()
{
	masterReference.clear();
}

void CtrlrPanelProcessor::handleAsyncUpdate()
{
}

void CtrlrPanelProcessor::processBlock(MidiBuffer &midiMessages, MidiBuffer &leftoverBuffer)
{	
	if (owner.getMidiOptionBool(panelMidiInputFromHostCompare))
	{
		owner.getMIDIInputThread().handleMIDIFromHost(midiMessages);
	}

	MidiBuffer::Iterator i(midiMessages);
	MidiMessage m;
	int time;

	while (i.getNextEvent(m,time))
	{		
		_MIN("VST INPUT", m);

		if (owner.getMidiOptionBool(panelMidiThruH2D) == true)
		{
			if (owner.getMidiOptionBool(panelMidiThruH2DChannelize))
			{
				m.setChannel (owner.getMidiChannel(panelMidiOutputChannelDevice));				
			}

			owner.sendMidi(m);
		}			

		if (owner.getMidiOptionBool(panelMidiThruH2H) == true)
		{
			if (owner.getMidiOptionBool(panelMidiThruH2HChannelize))
			{
				m.setChannel (owner.getMidiChannel(panelMidiOutputChannelHost));
			}

			leftoverBuffer.addEvent (m, m.getTimeStamp());
		}
	}
}

void CtrlrPanelProcessor::midiOptionChanged(const CtrlrPanelMidiOption optionThatChanged)
{
	if (optionThatChanged == panelMidiInputFromHost 
		|| optionThatChanged == panelMidiOutputToHost 
		|| optionThatChanged == panelMidiThruH2H
		|| optionThatChanged == panelMidiThruH2D)
	{
		if (owner.getMidiOptionBool(panelMidiInputFromHost) 
			|| owner.getMidiOptionBool(panelMidiOutputToHost)
			|| owner.getMidiOptionBool(panelMidiThruH2H)
			|| owner.getMidiOptionBool(panelMidiThruH2D))
		{
			owner.getOwner().getOwner()->addPanelProcessor (this);
		}

		if (owner.getMidiOptionBool(panelMidiInputFromHost) == false 
			&& owner.getMidiOptionBool(panelMidiOutputToHost) == false
			&& owner.getMidiOptionBool(panelMidiThruH2H) == false
			&& owner.getMidiOptionBool(panelMidiThruH2D) == false)
		{
			owner.getOwner().getOwner()->removePanelProcessor (this);
		}
	}
}

CtrlrPanel &CtrlrPanelProcessor::getOwner()
{
	return (owner);
}