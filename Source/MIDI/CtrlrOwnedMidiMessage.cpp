#include "stdafx.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrOwnedMidiMessage.h"
#include "CtrlrManager/CtrlrManager.h"
#include "Core/CtrlrPanel/CtrlrPanel.h"
#include "CtrlrProcessor.h"

CtrlrOwnedMidiMessage::CtrlrOwnedMidiMessage(CtrlrMidiMessageOwner &_owner)
	: owner(_owner)
{
}

CtrlrOwnedMidiMessage::~CtrlrOwnedMidiMessage()
{
}

void CtrlrOwnedMidiMessage::setControllerNumber(const int controllerNumber)
{
	CtrlrMidiMessage::setNumber(controllerNumber);
}

void CtrlrOwnedMidiMessage::setMidiMessageType (const CtrlrMidiMessageType newType)
{
	CtrlrMidiMessage::setMidiMessageType (newType);
}

void CtrlrOwnedMidiMessage::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::midiMessageChannel)
	{
		if ((bool)getProperty(Ids::midiMessageChannelOverride) == true)
		{
			setChannel (getProperty(Ids::midiMessageChannel));
		}
		else
		{
			setChannel (jlimit(1,16,owner.getMidiChannelForOwnedMidiMessages()));
		}
	}

	if (property == Ids::midiMessageChannelOverride)
	{
		if ((bool)getProperty(Ids::midiMessageChannelOverride) == true)
		{
			setChannel (getProperty(Ids::midiMessageChannel));
		}
		else
		{
			setChannel (owner.getMidiChannelForOwnedMidiMessages());
		}
	}

	CtrlrMidiMessage::valueTreePropertyChanged (treeWhosePropertyHasChanged, property);
}

void CtrlrOwnedMidiMessage::patternChanged()
{
	CtrlrMidiMessage::patternChanged();
}

void CtrlrOwnedMidiMessage::compilePattern()
{
	CtrlrMidiMessage::patternChanged();
}

const Array<int,CriticalSection> &CtrlrOwnedMidiMessage::getGlobalVariables()
{
	return (owner.getGlobalVariables());
}

CtrlrSysexProcessor *CtrlrOwnedMidiMessage::getSysexProcessor()
{
	return (owner.getSysexProcessor());
}