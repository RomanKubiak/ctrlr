#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanelProcessor.h"
#include "CtrlrLuaManager.h"
#include "CtrlrPanel.h"
#include "Plugin/CtrlrProcessor.h"

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

void CtrlrPanelProcessor::processBlock(MidiBuffer &midiMessages, MidiBuffer &leftoverBuffer, const AudioPlayHead::CurrentPositionInfo &info)
{
	if (owner.getMidiOptionBool(panelMidiInputFromHostCompare))
	{
		owner.getMIDIInputThread().handleMIDIFromHost(midiMessages);
	}

	leftoverBuffer.clear();

    processLua(midiMessages, info);

	MidiBuffer::Iterator i(midiMessages);
	MidiMessage m;
	int time;

	while (i.getNextEvent(m,time))
	{
		_MIN("VST INPUT", m, time);
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

			leftoverBuffer.addEvent (m, time);
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
			owner.getCtrlrManagerOwner().getProcessorOwner()->addPanelProcessor (this);
		}

		if (owner.getMidiOptionBool(panelMidiInputFromHost) == false
			&& owner.getMidiOptionBool(panelMidiOutputToHost) == false
			&& owner.getMidiOptionBool(panelMidiThruH2H) == false
			&& owner.getMidiOptionBool(panelMidiThruH2D) == false)
		{
			owner.getCtrlrManagerOwner().getProcessorOwner()->removePanelProcessor (this);
		}
	}
}

CtrlrPanel &CtrlrPanelProcessor::getOwner()
{
	return (owner);
}

void CtrlrPanelProcessor::processLua(MidiBuffer &midiMessages, const AudioPlayHead::CurrentPositionInfo &info)
{
    if (luaAudioProcessBlockCbk && luaAudioProcessBlockCbk->isValid())
	{
		owner.getCtrlrLuaManager().getMethodManager().callAudio(luaAudioProcessBlockCbk, midiMessages, info);
	}
}
