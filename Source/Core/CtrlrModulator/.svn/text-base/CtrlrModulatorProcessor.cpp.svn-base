#include "stdafx.h"
#include "CtrlrLuaManager.h"
#include "CtrlrModulatorProcessor.h"
#include "CtrlrModulator.h"
#include "CtrlrIDs.h"
#include "CtrlrUtilities.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrProcessor.h"
#include "CtrlrLog.h"
#include "CtrlrComponents/CtrlrComponent.h"

CtrlrModulatorProcessor::CtrlrModulatorProcessor(CtrlrModulator &_owner)
	: owner(_owner),
		currentValue(-1),
		valueChangedCbk(0),
		usingForwardProcess(false),
		usingReverseProcess(false),
		minValue(0),
		maxValue(127),
		usingValueMap(false)
{
	ctrlrMidiMessage	= new CtrlrOwnedMidiMessage(*this);
}

CtrlrModulatorProcessor::~CtrlrModulatorProcessor()
{
}

void CtrlrModulatorProcessor::handleAsyncUpdate()
{
	{
	/* update the GUI and the ValueTree from the value provided by the HOST or
		the MIDI subsystem */
		const ScopedReadLock sl (processorLock);

		/* If we already have the same value, calling setProperty on the ValueTree won't cause a
			propertyChanged callback, we need to remove the property and re-set it */
		if ((double)owner.getProperty(Ids::modulatorValue) == currentValue)
		{
			owner.removeProperty(Ids::modulatorValue);
		}
		owner.setProperty (Ids::modulatorValue, currentValue);
	}

	if (valueChangedCbk && !valueChangedCbk.wasObjectDeleted() && !owner.getOwner().getRestoreState())
	{
		if (valueChangedCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (valueChangedCbk, &owner, (int)owner.getProperty(Ids::modulatorValue));
		}
	}

	if (linkedToGlobal)
	{
		owner.getOwner().setGlobalVariable (getLinkedToGlobalIndex(), currentValue);
	}
}

void CtrlrModulatorProcessor::setValue(const int value)
{
}

void CtrlrModulatorProcessor::setModulatorMaxValue (const int newMaxValue)
{
	const ScopedWriteLock sl (processorLock);
	maxValue = newMaxValue;
}

void CtrlrModulatorProcessor::setModulatorMinValue (const int newMinValue)
{
	const ScopedWriteLock sl (processorLock);
	minValue = newMinValue;
}

void CtrlrModulatorProcessor::setForwardExpression (const String &forwardExpressionString)
{
	if (forwardExpressionString == String::empty || forwardExpressionString == EXP_MODULATOR_FORWARD)
	{
		const ScopedWriteLock sl (processorLock);

		usingForwardProcess = false;
		return;
	}

	{
		const ScopedWriteLock sl (processorLock);

		try
		{
			forwardProcess = Expression(forwardExpressionString);
		}
		catch (Expression::ParseError err)
		{
			_ERR("CtrlrModulatorProcessor::setForwardExpression parse error: " + err.description);
			usingForwardProcess = false;

			return;
		}

		usingForwardProcess = true;
	}
}

void CtrlrModulatorProcessor::setReverseExpression (const String &reverseExpressionString)
{
	if (reverseExpressionString == String::empty || reverseExpressionString == EXP_MODULATOR_REVERSE)
	{
		const ScopedWriteLock sl (processorLock);

		usingReverseProcess = false;
		return;
	}

	{
		const ScopedWriteLock sl (processorLock);

		try
		{
			reverseProcess = Expression(reverseExpressionString);
		}
		catch (Expression::ParseError err)
		{
			_ERR("CtrlrModulatorProcessor::setReverseExpression parse error: " + err.description);
			usingReverseProcess = false;

			return;
		}

		usingReverseProcess = true;
	}
}

void CtrlrModulatorProcessor::setValueChangedCallback (const String &methodName)
{
	if (methodName.isEmpty())
		return;

	valueChangedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(methodName);
}

void CtrlrModulatorProcessor::setGetValueForMidiCallback (const String &methodName)
{
	if (methodName.isEmpty())
		return;

	getValueForMidiCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(methodName);
}

void CtrlrModulatorProcessor::setGetValueFromMidiCallback (const String &methodName)
{
	if (methodName.isEmpty())
		return;

	getValueFromMidiCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(methodName);
}

void CtrlrModulatorProcessor::setMappedValue (const int mappedValue, const bool force, const bool mute)
{
	setValueFromGUI (valueMap.getIndexForValue (mappedValue), force, mute);
}

void CtrlrModulatorProcessor::setValueFromGUI(const double inValue, const bool force, const bool mute)
{
	/* there are 3 sources of value changes

		- gui
		- midi
		- host

		- gui should affect the MIDI first and then send the value to host, when it comes back from host
			and is the same as the value set before sending it to host, nothing should happen, if theyre
			different it should be set to the MIDI and a async update should be triggered

		- midi should affect the host first

		- host update has to check what's different from the value received, if it is different an update
			should be triggered (midi sent and/or async update done)


		** problem, when a value comes back from host it needs to be re-mapped to a midi value that lives
			in the UI component, this will be the audio thread so asking the component will require locking
			it might be better to keep a copy of value mapping (just the numeric part, we don't need the text, or do we?)
			internaly in the processor so we can avoid locking at runtime
	*/
	{
		/* if the values are already the same, and the force flag is set to false
			don't do anything the modulator is already in the state it should be */

		const ScopedReadLock sl(processorLock);

		if (currentValue == inValue && force == false)
		{
			return;
		}
	}

	{
		/* set the current value and the midi messages value,
			send the MIDI out and notify the host about the parameter change */
		const ScopedWriteLock sl(processorLock);

		/* it's the same value, but it's forced, send out MIDI and triggerAsyncUpdate
			don't inform the host, it already knows about it

			if mute is true, no midi goes out */
		if (currentValue == inValue && force == true)
		{
			if (!mute)
				sendMidiMessage();

			triggerAsyncUpdate();

			return;
		}

		/* first we se the currentValue to the new value comming from the gui, it's needed for the
			expressions evaluations to work */

		currentValue = inValue;

		/* send the midi message, this is done using a special thread so it won't wait until it's actualy sent */
		if (!mute)
			sendMidiMessage();

		triggerAsyncUpdate();
	}

	/* notify the pluginHost about the change */
	setParameterNotifyingHost();
}

void CtrlrModulatorProcessor::setValueFromHost(const float inValue)
{
	/* called from the audio thread */
	{
		/* first quickly check if we need to change anything at all */
		const ScopedReadLock sl (processorLock);
		
		const int possibleNewValue	= denormalizeValue (inValue, minValue, maxValue);

		if (possibleNewValue == currentValue)
		{
			/* the host told us the same exact value we already have, we won't do anything about it */
			triggerAsyncUpdate();
			return;
		}
	}

	{
		/* if we got here the value from the host is new and we need to update things */
		const ScopedWriteLock sl(processorLock);
		
		/* set the new value for the modulator */
		currentValue = denormalizeValue (inValue, minValue, maxValue);

		/* send a midi message */
		sendMidiMessage();
	}

	/* update the modulator ValueTree and tell the GUI about the changes */
	triggerAsyncUpdate();
} 


void CtrlrModulatorProcessor::setValueFromMIDI(CtrlrMidiMessage &m)
{
	/* called from the Panel's MIDI thread */
	{
		const ScopedWriteLock sl (processorLock);
		
		/* merge the icomming midi data with our message */
		mergeMidiData (m, *ctrlrMidiMessage);

		/* fetch the value from the midi message and pass it to the host */
		const int possibleValue = getValueFromMidiMessage();
		
		if (currentValue != possibleValue)
		{
			if (isInValidMappedRange (possibleValue))
			{
				currentValue = possibleValue;

				/* notify the pluginHost about the change */
				setParameterNotifyingHost();
			}
		}
	}
} 

const void CtrlrModulatorProcessor::setParameterNotifyingHost()
{
	if (owner.getVstIndex() >= 0 && owner.isExportedToVst())
	{
		getProcessor()->setParameterNotifyingHost (owner.getVstIndex(), normalizeValue (currentValue, minValue, maxValue));
	}
}

const int CtrlrModulatorProcessor::getValueFromMidiMessage()
{
	int evaluationResult = 0;
	if (usingValueMap)
	{
		const int possibleValue = valueMap.getIndexForValue(evaluateReverse (ctrlrMidiMessage->getValue()));

		if (possibleValue >= 0)
		{
			evaluationResult = possibleValue;
		}
		else
		{
			evaluationResult = currentValue;
		}
	}
	else
	{
		evaluationResult = evaluateReverse (ctrlrMidiMessage->getValue());
	}

	if (getValueFromMidiCbk)
	{
		if (!getValueFromMidiCbk.wasObjectDeleted() && getValueForMidiCbk->isValid())
		{
			evaluationResult = owner.getOwner().getCtrlrLuaManager().getMethodManager().callWithRet (getValueFromMidiCbk, &owner, *ctrlrMidiMessage, evaluationResult);
		}
	}

	return (evaluationResult);
}

const float CtrlrModulatorProcessor::getValueForHost() const
{
	const ScopedReadLock sl (processorLock);

	return (normalizeValue (currentValue, minValue, maxValue));
}

CtrlrOwnedMidiMessage *CtrlrModulatorProcessor::getMidiMessagePtr()
{
	return (ctrlrMidiMessage);
}

CtrlrMidiMessage &CtrlrModulatorProcessor::getMidiMessage()
{
	const ScopedReadLock sl (processorLock);

	return (*ctrlrMidiMessage);
}

CtrlrOwnedMidiMessage &CtrlrModulatorProcessor::getOwnedMidiMessage()
{
	const ScopedReadLock sl (processorLock);

	return (*ctrlrMidiMessage);
}

CtrlrProcessor *CtrlrModulatorProcessor::getProcessor()
{
	return (owner.getOwner().getOwner().getOwner());
}

const int CtrlrModulatorProcessor::getValue() const
{
	const ScopedReadLock sl (processorLock);

	return (currentValue);
}

const int CtrlrModulatorProcessor::getValueMapped() const
{
	const ScopedReadLock sl (processorLock);

	return (valueMap.getMappedValue(currentValue));
}

const int CtrlrModulatorProcessor::getMax() const
{
	const ScopedReadLock sl (processorLock);

	return (maxValue);
}

const int CtrlrModulatorProcessor::getMin() const
{
	const ScopedReadLock sl (processorLock);

	return (minValue);
}

void CtrlrModulatorProcessor::sendMidiMessage()
{
	if (!owner.getRestoreState())
	{
		ctrlrMidiMessage->setValue (getValueForMidiMessage(currentValue));

		owner.getOwner().sendMidi (getMidiMessage(), -1);

		if (owner.getOwner().getMidiOptionBool(panelMidiOutputToHost))
		{
			owner.getOwner().queueMessageForHostOutput (getMidiMessage());
		}
	}
	else
	{
		ctrlrMidiMessage->setValue (getValueForMidiMessage(currentValue));
	}
}

const CtrlrValueMap &CtrlrModulatorProcessor::setValueMap (const String &mapAsString)
{
	{
		const ScopedWriteLock sl (processorLock);
		valueMap.parseString (mapAsString);
		usingValueMap	= true;
	}

	{
		const ScopedReadLock sl (processorLock);

		owner.setProperty (Ids::modulatorMax, valueMap.getNonMappedMax());
		owner.setProperty (Ids::modulatorMin, valueMap.getNonMappedMin());
		return (valueMap);
	}
}

void CtrlrModulatorProcessor::setValueMap (const CtrlrValueMap &map)
{
	{
		const ScopedWriteLock sl (processorLock);
		valueMap.copyFrom (map);
		usingValueMap	= true;
	}

	{
		const ScopedReadLock sl (processorLock);

		owner.setProperty (Ids::modulatorMax, valueMap.getNonMappedMax());
		owner.setProperty (Ids::modulatorMin, valueMap.getNonMappedMin());
	}
}

const int CtrlrModulatorProcessor::getValueForMidiMessage(const int value)
{
	int evaluationResult = value;

	if (usingValueMap)
	{
		if (usingForwardProcess)
		{
			evaluationResult = evaluateForward (valueMap.getMappedValue(value));
		}
		else
		{
			evaluationResult = valueMap.getMappedValue(value);
		}
	}
	else
	{
		evaluationResult = evaluateForward(value);
	}

	if (getValueForMidiCbk)
	{
		if (!getValueForMidiCbk.wasObjectDeleted() && getValueForMidiCbk->isValid())
		{
			evaluationResult = owner.getOwner().getCtrlrLuaManager().getMethodManager().callWithRet (getValueForMidiCbk, &owner, evaluationResult);
		}
	}

	return (evaluationResult);
}

const bool CtrlrModulatorProcessor::isInValidMappedRange(const int possibleValue) const
{
	if (usingValueMap)
	{
		if (possibleValue >= valueMap.getMappedMin() && possibleValue <= valueMap.getMappedMax())
		{
			return (true);
		}
	}
	else
	{
		if (possibleValue >= minValue && possibleValue <= maxValue)
		{
			return (true);
		}
	}

	return (false);
}

void CtrlrModulatorProcessor::setLinkedToGlobal(const bool _linkedToGlobal, const int _globalIndex)
{
	{
		const ScopedWriteLock sl (processorLock);
		linkedToGlobal	= _linkedToGlobal;
		globalIndex		= _globalIndex;
	}
}

const bool CtrlrModulatorProcessor::getLinkedToGlobal()
{
	const ScopedReadLock sl (processorLock);

	return (linkedToGlobal);
}

const int CtrlrModulatorProcessor::getLinkedToGlobalIndex()
{
	const ScopedReadLock sl (processorLock);

	return (globalIndex);
}

CtrlrValueMap &CtrlrModulatorProcessor::getValueMap()
{
	return (valueMap);
}

const int CtrlrModulatorProcessor::evaluateForward(const int inValue)
{
	if (usingForwardProcess)
	{
		String errors;
		double ret;

		ret = forwardProcess.evaluate (*this, errors);

		if (!errors.isEmpty())
		{
			_ERR("CtrlrModulatorProcessor::evaluateForward " + errors);
		}

		return (ret);
	}

	return (inValue);
}

const int CtrlrModulatorProcessor::evaluateReverse(const int inValue)
{
	if (usingReverseProcess)
	{
		String errors;
		double ret;
		ret = reverseProcess.evaluate (*this, errors);
		if (!errors.isEmpty())
		{
			_ERR("CtrlrModulatorProcessor::evaluateReverse " + errors);
		}

		return (ret);
	}

	return (inValue);
}

String CtrlrModulatorProcessor::getScopeUID() const
{
	return ("mProcessor");
}

double CtrlrModulatorProcessor::evaluateFunction (const String& functionName, const double* parameters, int numParameters) const
{
	return (evaluateFormulaFunction (owner.getOwner(), functionName, parameters, numParameters));
}

void CtrlrModulatorProcessor::visitRelativeScope (const String &scopeName, Visitor &visitor) const
{
	if (scopeName == "panel")
	{
		visitor.visit (owner.getOwner().getPanelEvaluationScope());
	}
	else if (scopeName == "global")
	{
		visitor.visit (owner.getOwner().getGlobalEvaluationScope());
	}
}

Expression CtrlrModulatorProcessor::getSymbolValue (const String& symbol) const
{
	if (symbol == "modulatorValue")
	{
		return (Expression((double)currentValue));
	}
	else if (symbol == "modulatorMappedValue")
	{
		return (Expression((double)valueMap.getMappedValue(currentValue)));
	}
	else if (symbol == "modulatorMax")
	{
		return (Expression((double)maxValue));
	}
	else if (symbol == "modulatorMin")
	{
		return (Expression((double)minValue));
	}
	else if (symbol == "modulatorMappedMax")
	{
		return (Expression((double)valueMap.getMappedMax()));
	}
	else if (symbol == "modulatorMappedMin")
	{
		return (Expression((double)valueMap.getMappedMin()));
	}
	else if (symbol == "vstIndex")
	{
		return (Expression((double)owner.getVstIndex()));
	}
	else if (symbol == "midiValue")
	{
		return (Expression((double)ctrlrMidiMessage->getValue()));
	}
	else if (symbol == "midiNumber")
	{
		return (Expression((double)ctrlrMidiMessage->getNumber()));
	}

	return (Expression(1.0));
}

int CtrlrModulatorProcessor::getMidiChannelForOwnedMidiMessages()
{
	return (owner.getOwner().getProperty(Ids::panelMidiOutputChannelDevice));
}

CtrlrSysexProcessor *CtrlrModulatorProcessor::getSysexProcessor()
{
	return (&owner.getOwner().getSysExProcessor());
}

Array<int,CriticalSection> &CtrlrModulatorProcessor::getGlobalVariables()
{
	return (owner.getOwner().getGlobalVariables());
}