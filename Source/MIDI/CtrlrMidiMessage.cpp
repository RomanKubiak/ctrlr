#include "stdafx.h"
#include "CtrlrMidiMessage.h"
#include "CtrlrUtilities.h"
#include "CtrlrIDs.h"
#include "CtrlrLog.h"
#include "CtrlrManager/CtrlrManager.h"
#include "JuceClasses/LMemoryBlock.h"

CtrlrMidiMessage::CtrlrMidiMessage()
	:	midiTree(Ids::midi), multiMasterValue(1),
		multiMasterNumber(1), messagePattern(0,true), restoring(false),
		initializationResult(Result::ok())
{
	initializeEmptyMessage();
}

CtrlrMidiMessage::CtrlrMidiMessage (const String& hexData)
	:	midiTree(Ids::midi), multiMasterValue(1),
		multiMasterNumber(1), messagePattern(0,true),
		initializationResult(Result::ok())
{
	initializeEmptyMessage();

	if (!stringIsHexadecimal (hexData))
	{
		_WRN("CtrlrMidiMessage::ctor initial string is not a valid HEX data string");
		initializationResult = Result::fail("Initial string is not a valid HEX data string");
	}
	else
	{
		/* create a data block from the hex string,
			initialize properties based on that data */

		MidiMessage m = createFromHexData(hexData);

		if (m.getRawDataSize() == 0)
		{
			_WRN("CtrlrMidiMessage::ctor string passed to constructor resulted in zero size memory string:"+hexData);
			initializationResult = Result::fail("String passed to constructor resulted in zero size memory");
		}
		else
		{
			initializationResult = fillMessagePropertiesFromData( MemoryBlock (m.getRawData(), m.getRawDataSize()) );

			if (!initializationResult.wasOk())
			{
				_WRN("CtrlrMidiMessage::ctor from string failed to init MIDI message string:"+hexData);
			}
			// Sysex is not added automagicly (since we need a valid formula), do it now
			else if (messageType == SysEx)
			{
				messageArray.add (m);
			}
		}
	}
}

CtrlrMidiMessage::CtrlrMidiMessage (const MidiMessage& other)
	:	midiTree(Ids::midi), messagePattern(0,true),
		initializationResult(Result::ok())
{
	initializeEmptyMessage();

	/* Copy the passed in midi message
		initialize properties based on that message*/

	initializationResult = fillMessagePropertiesFromJuceMidi (other);

	if (!initializationResult.wasOk())
	{
		_WRN("CtrlrMidiMessage::ctor other MidiMessage was invalid");
	}
	else if (messageType == SysEx)
	{
		messageArray.add (other);
	}
}

CtrlrMidiMessage::CtrlrMidiMessage (MemoryBlock& other)
	:	midiTree(Ids::midi), messagePattern(0,true), initializationResult(Result::ok())
{
	initializeEmptyMessage();

	/* Copy the passed in midi message
		initialize properties based on that message*/

	MidiMessage m = MidiMessage(other.getData(), other.getSize());

	initializationResult = fillMessagePropertiesFromJuceMidi (m);

	if (!initializationResult.wasOk())
	{
		_WRN("CtrlrMidiMessage::ctor other MemoryBlock was invalid");
	}
	else
	{
		// Sysex is not added automagicly (since we need a valid formula), do it now
		if (messageType == SysEx)
		{
			messageArray.add (m);
		}
	}
}

CtrlrMidiMessage::CtrlrMidiMessage (const luabind::object &luaArray)
	:	midiTree(Ids::midi), multiMasterValue(1),
		multiMasterNumber(1), messagePattern(0,true),
		initializationResult(Result::ok())
{
	initializeEmptyMessage();

	/* Convert the luaArray to a MemoryBlock treating it as an array of UINT8 numbers
		use the created MemoryBlock as initial data for a MidiMessage
		initialize properties based on that message*/

	MemoryBlock possibleMidiData = luaArrayTomemoryBlock(luaArray);

	if (possibleMidiData.getSize() > 0)
	{
		initializationResult = fillMessagePropertiesFromData(possibleMidiData);

		if (!initializationResult.wasOk())
		{
			_WRN("CtrlrMidiMessage::ctor LUA can't create midi message from input data: " + memoryBlockToString(possibleMidiData));
		}
		else
		{
			// Sysex is not added automagicly (since we need a valid formula), do it now
			if (messageType == SysEx)
			{
				messageArray.add (MidiMessage (possibleMidiData.getData(), possibleMidiData.getSize()));
			}
		}
	}
	else
	{
		_WRN("CtrlrMidiMessage::ctor LUA input data is zero size");
	}
}

CtrlrMidiMessage::CtrlrMidiMessage (const CtrlrMidiMessage &other)
	: midiTree(other.midiTree), initializationResult(Result::ok()),
		messageArray(other.messageArray)
{

	fillMessagePropertiesFromData();

}

CtrlrMidiMessage::~CtrlrMidiMessage()
{
	midiTree.removeListener (this);
}

void CtrlrMidiMessage::initializeEmptyMessage()
{
	setProperty (Ids::midiMessageType, 9);
	setProperty (Ids::midiMessageChannelOverride, false);
	setProperty (Ids::midiMessageChannel, 1);
	setProperty (Ids::midiMessageCtrlrNumber, 1);
	setProperty (Ids::midiMessageCtrlrValue, 0);
	setProperty (Ids::midiMessageMultiList, String::empty);
	setProperty (Ids::midiMessageSysExFormula, String::empty);

	midiTree.addListener (this);
}

Result CtrlrMidiMessage::fillMessagePropertiesFromJuceMidi(const MidiMessage &m)
{
	if (m.isController())
	{
		messageType = CC;
		setProperty (Ids::midiMessageType, CC);
		setProperty (Ids::midiMessageChannel, m.getChannel());
		setProperty (Ids::midiMessageCtrlrNumber, m.getControllerNumber());
		setProperty (Ids::midiMessageCtrlrValue, m.getControllerValue());

		return (Result::ok());
	}
	else if (m.isAftertouch())
	{
		messageType = Aftertouch;
		setProperty (Ids::midiMessageType, Aftertouch);
		setProperty (Ids::midiMessageChannel, m.getChannel());
		setProperty (Ids::midiMessageCtrlrNumber, m.getNoteNumber());
		setProperty (Ids::midiMessageCtrlrValue, m.getAfterTouchValue());

		return (Result::ok());
	}
	else if (m.isNoteOn())
	{
		messageType = NoteOn;
		setProperty (Ids::midiMessageType, NoteOn);
		setProperty (Ids::midiMessageChannel, m.getChannel());
		setProperty (Ids::midiMessageCtrlrNumber, m.getNoteNumber());
		setProperty (Ids::midiMessageCtrlrValue, m.getVelocity());

		return (Result::ok());
	}
	else if (m.isNoteOff())
	{
		messageType = NoteOff;
		setProperty (Ids::midiMessageType, NoteOff);
		setProperty (Ids::midiMessageChannel, m.getChannel());
		setProperty (Ids::midiMessageCtrlrNumber, m.getNoteNumber());
		setProperty (Ids::midiMessageCtrlrValue, m.getVelocity());

		return (Result::ok());
	}
	else if (m.isChannelPressure())
	{
		messageType = ChannelPressure;
		setProperty (Ids::midiMessageType, ChannelPressure);
		setProperty (Ids::midiMessageChannel, m.getChannel());
		setProperty (Ids::midiMessageCtrlrValue, m.getChannelPressureValue());

		return (Result::ok());
	}
	else if (m.isProgramChange())
	{
		messageType = ProgramChange;
		setProperty (Ids::midiMessageType, ProgramChange);
		setProperty (Ids::midiMessageChannel, m.getChannel());
		setProperty (Ids::midiMessageCtrlrValue, m.getProgramChangeNumber());

		return (Result::ok());
	}
	else if (m.isPitchWheel())
	{
		messageType = PitchWheel;
		setProperty (Ids::midiMessageType, PitchWheel);
		setProperty (Ids::midiMessageChannel, m.getChannel());
		setProperty (Ids::midiMessageCtrlrValue, m.getPitchWheelValue());

		return (Result::ok());
	}
	else if (m.isSysEx())
	{
		messageType = SysEx;
		setProperty (Ids::midiMessageType, SysEx);
		return (Result::ok());
	}
	else if (m.isMidiClock())
	{
		messageType = MidiClock;
		setProperty (Ids::midiMessageType, MidiClock);
		return (Result::ok());
	}
	else if (m.isMidiContinue())
	{
		messageType = MidiClockContinue;
		setProperty (Ids::midiMessageType, MidiClockContinue);
		return (Result::ok());
	}
	else if (m.isMidiStart())
	{
		messageType = MidiClockStart;
		setProperty (Ids::midiMessageType, MidiClockStart);
		return (Result::ok());
	}
	else if (m.isMidiStop())
	{
		messageType = MidiClockStop;
		setProperty (Ids::midiMessageType, MidiClockStop);
		return (Result::ok());
	}
	else if (m.isActiveSense())
	{
		messageType = ActiveSense;
		setProperty (Ids::midiMessageType, ActiveSense);
		return (Result::ok());
	}
	else
	{
		messageType = None;
		setProperty (Ids::midiMessageType, None);

		return (Result::ok());
	}
}

Result CtrlrMidiMessage::fillMessagePropertiesFromData(const MemoryBlock &data)
{
	MidiMessageEx mex(MidiMessage(data.getData(), data.getSize()));

	if (mex.m.isController())
	{
		messageType = CC;
		setProperty (Ids::midiMessageType, CC);
		setProperty (Ids::midiMessageChannel, mex.m.getChannel());
		setProperty (Ids::midiMessageCtrlrNumber, mex.m.getControllerNumber());
		setProperty (Ids::midiMessageCtrlrValue, mex.m.getControllerValue());

		return (Result::ok());
	}
	else if (mex.m.isAftertouch())
	{
		messageType = Aftertouch;
		setProperty (Ids::midiMessageType, Aftertouch);
		setProperty (Ids::midiMessageChannel, mex.m.getChannel());
		setProperty (Ids::midiMessageCtrlrNumber, mex.m.getNoteNumber());
		setProperty (Ids::midiMessageCtrlrValue, mex.m.getAfterTouchValue());

		return (Result::ok());
	}
	else if (mex.m.isNoteOn())
	{
		messageType = NoteOn;
		setProperty (Ids::midiMessageType, NoteOn);
		setProperty (Ids::midiMessageChannel, mex.m.getChannel());
		setProperty (Ids::midiMessageCtrlrNumber, mex.m.getNoteNumber());
		setProperty (Ids::midiMessageCtrlrValue, mex.m.getVelocity());

		return (Result::ok());
	}
	else if (mex.m.isNoteOff())
	{
		messageType = NoteOff;
		setProperty (Ids::midiMessageType, NoteOff);
		setProperty (Ids::midiMessageChannel, mex.m.getChannel());
		setProperty (Ids::midiMessageCtrlrNumber, mex.m.getNoteNumber());
		setProperty (Ids::midiMessageCtrlrValue, mex.m.getVelocity());

		return (Result::ok());
	}
	else if (mex.m.isChannelPressure())
	{
		messageType = ChannelPressure;
		setProperty (Ids::midiMessageType, ChannelPressure);
		setProperty (Ids::midiMessageChannel, mex.m.getChannel());
		setProperty (Ids::midiMessageCtrlrValue, mex.m.getChannelPressureValue());

		return (Result::ok());
	}
	else if (mex.m.isProgramChange())
	{
		messageType = ProgramChange;
		setProperty (Ids::midiMessageType, ProgramChange);
		setProperty (Ids::midiMessageChannel, mex.m.getChannel());
		setProperty (Ids::midiMessageCtrlrValue, mex.m.getProgramChangeNumber());

		return (Result::ok());
	}
	else if (mex.m.isPitchWheel())
	{
		messageType = PitchWheel;
		setProperty (Ids::midiMessageType, PitchWheel);
		setProperty (Ids::midiMessageChannel, mex.m.getChannel());
		setProperty (Ids::midiMessageCtrlrValue, mex.m.getPitchWheelValue());

		return (Result::ok());
	}
	else if (mex.m.isSysEx())
	{
		messageType = SysEx;
		setProperty (Ids::midiMessageType, SysEx);
		return (Result::ok());
	}
	else if (mex.m.isMidiClock())
	{
		messageType = MidiClock;
		setProperty (Ids::midiMessageType, MidiClock);
		return (Result::ok());
	}
	else if (mex.m.isMidiContinue())
	{
		messageType = MidiClockContinue;
		setProperty (Ids::midiMessageType, MidiClockContinue);
		return (Result::ok());
	}
	else if (mex.m.isMidiStart())
	{
		messageType = MidiClockStart;
		setProperty (Ids::midiMessageType, MidiClockStart);
		return (Result::ok());
	}
	else if (mex.m.isMidiStop())
	{
		messageType = MidiClockStop;
		setProperty (Ids::midiMessageType, MidiClockStop);
		return (Result::ok());
	}
	else if (mex.m.isActiveSense())
	{
		messageType = ActiveSense;
		setProperty (Ids::midiMessageType, ActiveSense);
		return (Result::ok());
	}
	else
	{
		messageType = None;
		setProperty (Ids::midiMessageType, None);

		return (Result::ok());
	}
}

Result CtrlrMidiMessage::fillMessagePropertiesFromData()
{
	if (messageArray.size() == 0)
	{
		setProperty (Ids::midiMessageType, (uint8)None);
		setProperty (Ids::midiMessageChannelOverride, false);
		setProperty (Ids::midiMessageChannel, 1);
		setProperty (Ids::midiMessageCtrlrNumber, 1);
		setProperty (Ids::midiMessageCtrlrValue, 0);
		setProperty (Ids::midiMessageMultiList, String::empty);
		setProperty (Ids::midiMessageSysExFormula, String::empty);

		return (Result::fail("MessageArray is empty, initializing to empty NONE message"));
	}
	else
	{
		return (fillMessagePropertiesFromData( MemoryBlock (messageArray[0].m.getRawData(), messageArray[0].m.getRawDataSize()) ));
	}
}

void CtrlrMidiMessage::restoreState (const ValueTree &savedState)
{
	for (int i=0; i<savedState.getNumProperties(); i++)
	{
		midiTree.setProperty (savedState.getPropertyName(i), savedState.getProperty(savedState.getPropertyName(i), 0), 0);
	}

	for (int i=0; i<savedState.getNumChildren(); i++)
	{
		midiTree.addChild (savedState.getChild(i).createCopy(), -1, 0);
	}

	if (getProperty(Ids::midiMessageSysExFormula).toString().length() > 0 && (int)getProperty(Ids::midiMessageType) != SysEx)
	{
		setProperty (Ids::midiMessageSysExFormula, String::empty);
	}
	else if (getProperty(Ids::midiMessageSysExFormula).toString().length() > 0 && (int)getProperty(Ids::midiMessageType) == SysEx)
	{
		setProperty (Ids::midiMessageSysExFormula, getProperty(Ids::midiMessageSysExFormula));
		setProperty (Ids::midiMessageType, SysEx);
	}
}

void CtrlrMidiMessage::setValue (const int value)
{
	switch (messageType)
	{
		case CC:
		case Aftertouch:
		case ChannelPressure:
		case NoteOn:
		case NoteOff:
		case SysEx:
		case PitchWheel:
		case ProgramChange:
			setValueToSingle (0, value);
			break;
		case Multi:
			setValueToMulti (value);
			break;
		case MidiClock:
		case MidiClockContinue:
		case MidiClockStop:
		case kMidiMessageType:
		case ActiveSense:
		case MidiClockStart:
		case None:
			break;
	}
}

void CtrlrMidiMessage::setValueToSingle(const int index, const int value)
{
	if (messageArray.size() > index && messageArray.getReference(index).overrideValue == -2)
	{
		return;
	}
	else if ( (messageArray.size() > index && messageArray.getReference(index).m.isSysEx())
			|| (messageArray.size() > index && messageType == SysEx))
	{
		if (getSysexProcessor())
		{
			getSysexProcessor()->sysExProcess (messageArray.getReference(index).getTokenArray(), messageArray.getReference(index).m, value, getChannel());
		}
	}
	else
	{
		if (messageArray.size() > index)
			messageArray.getReference(index).setValue (value);
	}
}

void CtrlrMidiMessage::setValueToMulti (const int value)
{
	for (int i=0; i<messageArray.size(); i++)
	{
		setValueToSingle (i, value);
	}
}

int CtrlrMidiMessage::getValue()
{
	if (messageType != Multi && messageType != SysEx)
	{
		if (messageArray.size() == 1)
			return (messageArray.getReference(0).getValue());
		else
			return (0);
	}
	else if (messageType == Multi)
	{
		BigInteger value(0);

		for (int i=0; i<messageArray.size(); i++)
		{
			if (messageArray.getReference(i).overrideValue == -2)
				continue;

			value |= messageArray.getReference(i).getBitValue();
		}
		return (value.getBitRangeAsInt(0,14));
	}
	else if (messageType == SysEx)
	{
		if (messageArray.size() == 1)
		{
			if (getSysexProcessor())
			{
				return (getSysexProcessor()->getValueFromSysExData (messageArray.getReference(0).getTokenArray(), messageArray.getReference(0)));
			}
			else
			{
				return (CtrlrSysexProcessor::getValue (messageArray.getReference(0).getTokenArray(), messageArray.getReference(0)));
			}
		}
	}

	return (1);
}

void CtrlrMidiMessage::setNumber(const int number)
{
	multiMasterNumber = number;

	switch (messageType)
	{
		case CC:
		case Aftertouch:
		case ChannelPressure:
		case NoteOn:
		case NoteOff:
		case PitchWheel:
		case ProgramChange:
			setNumberToSingle (0, number);
			break;

		case Multi:
			setNumberToMulti (number);
			break;

		case SysEx:
		case None:
		case MidiClock:
		case MidiClockContinue:
		case MidiClockStop:
		case kMidiMessageType:
		case ActiveSense:
		case MidiClockStart:
			break;
	}
}

void CtrlrMidiMessage::setNumberToSingle (const int index, const int number)
{
	if (index >= messageArray.size())
		return;

	if (messageArray.getReference(index).overrideValue == -2)
	{
		messageArray.getReference(index).setValue (number);
	}
	else
	{
		messageArray.getReference(index).setNumber (number);
	}
}

void CtrlrMidiMessage::setNumberToMulti (const int number)
{
	for (int i=0; i<messageArray.size(); i++)
	{
		setNumberToSingle (i, number);
	}
}

int CtrlrMidiMessage::getNumber() const
{
	if (messageType != Multi && messageType != SysEx)
	{
		if (messageArray.size() == 1)
			return (messageArray.getReference(0).getNumber());
		else
			return (1);
	}
	else if (messageType == Multi)
	{
		return (multiMasterNumber);
	}
	else
	{
		return (1);
	}
}

const CtrlrMidiMessageType CtrlrMidiMessage::getMidiMessageType() const
{
	return (messageType);
}

int CtrlrMidiMessage::getChannel() const
{
	if (messageArray.size() >= 1)
	{
		if (!messageArray.getReference(0).m.isSysEx())
		{
			return (jmax <int>(messageArray.getReference(0).m.getChannel(),1));
		}
		else
		{
			return (jmax <int>(getProperty(Ids::midiMessageChannel),1));
		}
	}

	return (jmax <int>(getProperty(Ids::midiMessageChannel),1));
}

void CtrlrMidiMessage::setChannel(const int midiChannel)
{
	for (int i=0; i<messageArray.size(); i++)
	{
		messageArray.getReference(i).setChannel (jmax<int>(midiChannel,1));
	}
}

void CtrlrMidiMessage::setMidiMessageType (const CtrlrMidiMessageType newType)
{
	const int ch = getChannel();

	switch (newType)
	{
		case CC:
			messageArray.clear();
			messageArray.add (MidiMessage::controllerEvent(ch, jmin<int>(getNumber(),127), jmin<int>(getValue(),127)));
			break;

		case Aftertouch:
			messageArray.clear();
			messageArray.add (MidiMessage::aftertouchChange(ch, jmin<int>(getNumber(),127), jmin<int>(getValue(),127)));
			break;

		case ChannelPressure:
			messageArray.clear();
			messageArray.add (MidiMessage::channelPressureChange (ch, jmin<int>(getValue(),127)));
			break;

		case NoteOn:
			messageArray.clear();
			messageArray.add (MidiMessage::noteOn (ch, jmin<int>(getNumber(),127), (uint8)jmin<int>(getValue(),127)));
			break;

		case NoteOff:
			messageArray.clear();
			messageArray.add (MidiMessage::noteOff (ch, jmin<int>(getNumber(),127), (uint8)jmin<int>(getValue(),127)));
			break;

		case SysEx:
			messageArray.clear();

			if (getProperty(Ids::midiMessageSysExFormula).toString().length() > 0)
			{
				messageArray.add (CtrlrSysexProcessor::sysexMessageFromString(getProperty(Ids::midiMessageSysExFormula),getValue(),getChannel()));
				patternChanged();
			}

			break;

		case Multi:
			CtrlrSysexProcessor::setMultiMessageFromString (*this, getProperty(Ids::midiMessageMultiList));
			break;

		case PitchWheel:
			messageArray.clear();
			messageArray.add (MidiMessage::pitchWheel (ch, (uint8)jmin<int>(getValue(),16383)));
			break;

		case ProgramChange:
			messageArray.clear();
			messageArray.add (MidiMessage::programChange (ch, (uint8)jmin<int>(getValue(),127)));
			break;

		case MidiClock:
			messageArray.clear();
			messageArray.add (MidiMessage::midiClock());
			break;

		case MidiClockContinue:
			messageArray.clear();
			messageArray.add (MidiMessage::midiContinue());
			break;

		case MidiClockStop:
			messageArray.clear();
			messageArray.add (MidiMessage::midiStop());
			break;

		case MidiClockStart:
			messageArray.clear();
			messageArray.add (MidiMessage::midiStart());
			break;

		case ActiveSense:
			messageArray.clear();
			messageArray.add (MidiMessage());
			break;

		case None:
			messageArray.clear();
			break;

		case kMidiMessageType:
			break;
	}

	messageType = newType;
}

void CtrlrMidiMessage::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::midiMessageType)
	{
		setMidiMessageType ((CtrlrMidiMessageType)(int)getProperty(Ids::midiMessageType));
		setNumber ((int)getProperty(Ids::midiMessageCtrlrNumber));
		patternChanged();
	}
	else if(property == Ids::midiMessageSysExFormula)
	{
		if (restoring == false && (int)getProperty(Ids::midiMessageType) == SysEx)
		{
			if (getProperty(property).toString().length() >= 1)
			{
				if (getSysexProcessor())
				{
					CtrlrSysexProcessor::setSysExFormula (*this, getProperty(Ids::midiMessageSysExFormula));
				}
				setValue ((int)getProperty(Ids::midiMessageCtrlrValue));
				patternChanged();
			}
		}
	}
	else if (property == Ids::midiMessageChannel)
	{
		setChannel (getProperty(Ids::midiMessageChannel));
	}
	else if (property == Ids::midiMessageCtrlrValue)
	{
		setValue ((int)getProperty(Ids::midiMessageCtrlrValue));
		return;
	}
	else if (property == Ids::midiMessageCtrlrNumber)
	{
		setNumber ((int)getProperty(Ids::midiMessageCtrlrNumber));
	}
	else if (property == Ids::midiMessageMultiList)
	{
		CtrlrSysexProcessor::setMultiMessageFromString (*this, getProperty(Ids::midiMessageMultiList));

		setNumber ((int)getProperty(Ids::midiMessageCtrlrNumber));
	}

	patternChanged();
}

MidiBuffer CtrlrMidiMessage::getMidiBuffer(const int startSample)
{
	midiBuffer.clear();

	for (int i=0; i<messageArray.size(); i++)
	{
		midiBuffer.addEvent (messageArray.getReference(i).m,startSample+i);
	}

	return (midiBuffer);
}

const LMemoryBlock CtrlrMidiMessage::getData() const
{
	MemoryBlock bl(0);
	for (int i=0; i<messageArray.size(); i++)
	{
		bl.append (messageArray.getReference(i).m.getRawData(), messageArray.getReference(i).m.getRawDataSize());
	}
	return (bl);
}

void CtrlrMidiMessage::patternChanged()
{
	messagePattern.setSize(0);

	for (int i=0; i<messageArray.size(); i++)
	{
		MemoryBlock bl(0);
		if (messageArray.getReference(i).overrideValue == -2)
		{
			bl = MemoryBlock(messageArray.getReference(i).m.getRawData(), messageArray.getReference(i).m.getRawDataSize());
		}
		else
		{
			bl = midiMessagePattern(messageArray.getReference(i), messageArray.getReference(i).getTokenArray(), getGlobalVariables());
		}

		messagePattern.append (bl.getData(), bl.getSize());
	}
}

void CtrlrMidiMessage::addMidiMessage (const MidiMessage &message)
{
	messageArray.add (message);
	patternChanged();
}

void CtrlrMidiMessage::clear()
{
	messageArray.clear();
	patternChanged();
}

MidiMessageEx &CtrlrMidiMessage::getReference(const int messageIndex) const
{
	return (messageArray.getReference(messageIndex));
}

void CtrlrMidiMessage::memoryMerge (const CtrlrMidiMessage &otherMessage)
{
	if (otherMessage.getNumMessages() == getNumMessages())
	{
		for (int i=0; i<messageArray.size(); i++)
		{
			messageArray.getReference(i).m = otherMessage.getMidiMessageEx(i).m;
		}
	}
}

const MemoryBlock &CtrlrMidiMessage::getMidiPattern() const
{
	return (messagePattern);
}

Array <MidiMessageEx> &CtrlrMidiMessage::getMidiMessageArray()
{
	return (messageArray);
}

const String CtrlrMidiMessage::toString() const
{
	return (String::toHexString (getData().getData(), getData().getSize()));
}

const int CtrlrMidiMessage::getSize() const
{
	return (getData().getSize());
}

void CtrlrMidiMessage::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrMidiMessage, CtrlrLuaObject>("CtrlrMidiMessage")
			.def(constructor<const String&>())
			.def(constructor<const luabind::object&>())
			.def(constructor<const MidiMessage&>())
			.def(constructor<MemoryBlock&>())
			.enum_("CtrlrMidiMessageType")
			[
	            value("CC",				0),
				value("Aftertouch",		1),
				value("ChannelPressure",2),
				value("NoteOn",			3),
				value("NoteOff",		4),
				value("SysEx",			5),
				value("Multi",			6),
				value("ProgramChange",	7),
				value("PitchWheel",		8),
				value("None",			9),
				value("MidiClock",		10),
				value("MidiClockContinue", 11),
				value("MidiClockStop", 12),
				value("MidiClockStart", 13)
			]
			.def("setChannel", &CtrlrMidiMessage::setChannel)
			.def("getChannel", &CtrlrMidiMessage::getChannel)
			.def("setNumber", &CtrlrMidiMessage::setNumber)
			.def("getNumber", &CtrlrMidiMessage::getNumber)
			.def("setValue", &CtrlrMidiMessage::setValue)
			.def("getValue", &CtrlrMidiMessage::getValue)
			.def("getSize", &CtrlrMidiMessage::getSize)
			.def("getData", &CtrlrMidiMessage::getData)
			.def("getLuaData", &CtrlrMidiMessage::getData)
			.def("getType", &CtrlrMidiMessage::getMidiMessageType)
			.def("getMidiMessageType", &CtrlrMidiMessage::getMidiMessageType)
			.def("toString", &CtrlrMidiMessage::toString)
			.def("getInitializationResult", &CtrlrMidiMessage::getInitializationResult)
	];
}
