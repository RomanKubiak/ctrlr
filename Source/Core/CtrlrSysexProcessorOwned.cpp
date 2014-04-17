#include "stdafx.h"
#include "CtrlrSysexProcessorOwned.h"
#include "CtrlrPanel/CtrlrPanel.h"

CtrlrSysexProcessorOwned::CtrlrSysexProcessorOwned(CtrlrPanel &_owner) : owner(_owner)
{
}

CtrlrSysexProcessorOwned::~CtrlrSysexProcessorOwned()
{
}

Array <int,CriticalSection> &CtrlrSysexProcessorOwned::getGlobalVariables()
{
	return (owner.getGlobalVariables());
}

const double CtrlrSysexProcessorOwned::getValueFromSysExData (const Array<CtrlrSysexToken> &tokens, const CtrlrMidiMessageEx &message)
{
	double v = 0;

	for (int i=0; i<tokens.size(); i++)
	{
		if (tokens[i].isHoldingValue())
		{
			v += indirectReverseOperation (*(message.m.getRawData()+i), tokens[i].getType());
		}
	}

	return (v);
}

void CtrlrSysexProcessorOwned::sysexProcessPrograms(const Array<CtrlrSysexToken> &tokens, MidiMessage &m)
{
	if (tokens.size() != m.getRawDataSize())
		return;

	for (int i=0; i<m.getRawDataSize(); i++)
	{
		if (tokens.getReference(i).getType() == CurrentProgram)
		{
			uint8 *ptr	= (uint8 *)m.getRawData();
			*(ptr+tokens.getReference(i).getPosition()) = owner.getCurrentProgramNumber();
		}
		if (tokens.getReference(i).getType() == CurrentBank)
		{
			uint8 *ptr	= (uint8 *)m.getRawData();
			*(ptr+tokens.getReference(i).getPosition()) = owner.getCurrentBankNumber();
		}
	}
}
