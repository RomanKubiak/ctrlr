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

void CtrlrOwnedMidiMessage::setChannel(const int midiChannel)
{
	if ((bool)getProperty(Ids::midiMessageChannelOverride) == true)
	{
		CtrlrMidiMessage::setChannel (getProperty(Ids::midiMessageChannel));
	}
	else
	{
		CtrlrMidiMessage::setChannel (jlimit(1,16,owner.getMidiChannelForOwnedMidiMessages()));
	}
}

void CtrlrOwnedMidiMessage::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
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