#include "stdafx.h"
#include "CtrlrUtilities.h"
#include "CtrlrLog.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrComponents/CtrlrComponent.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "JuceClasses/LMemoryBlock.h"
#pragma warning(disable:4706)

static const char *asciiSpecials[]	= {"[NUL]", "[SOH]", "[STX]", "[ETX]", "[EOT]", "[ENQ]", "[ACK]", "[BEL]", "[BS]", "[HT]", "[LF]", "[VT]", "[FF]", "[CR]", "[SO]", "[SI]", "[DLE]", "[DC1]", "[DC2]", "[DC3]", "[DC4]", "[NAK]", "[SYN]", "[ETB]", "[CAN]", "[EM]", "[SUB]", "[ESC]", "[FS]", "[GS]", "[RS]", "[US]", 0};

const String safeKey(const String &key)
{
	return (key.replace (" ", "_"));
}

const String midiMessageTypeToString (const CtrlrMidiMessageType messageType)
{
	switch (messageType)
	{
		case CC:
			return ("CC");
		case Aftertouch:
			return ("Aftertouch");
		case ChannelPressure:
			return ("ChannelPressure");
		case SysEx:
			return ("SysEx");
		case NoteOn:
			return ("NoteOn");
		case NoteOff:
			return ("NoteOff");
		case PitchWheel:
			return ("PitchWheel");
		case ProgramChange:
			return ("ProgramChange");
		case Multi:
			return ("Multi");
		case MidiClock:
			return ("MidiClock");
		case MidiClockContinue:
			return ("MidiContinue");
		case MidiClockStop:
			return ("MidiStop");
		case MidiClockStart:
			return ("MidiStart");
		case ActiveSense:
			return ("ActiveSense");
		case kMidiMessageType:
		case None:
			return ("None");
	}
	return ("None");
}

const CtrlrMidiMessageType midiMessageStringToType (const String &messageType)
{
	if (messageType == "CC")
	{
		return (CC);
	}
	else if (messageType == "Aftertouch")
	{
		return (Aftertouch);
	}
	else if (messageType == "ChannelPressure")
	{
		return (ChannelPressure);
	}
	else if (messageType == "SysEx")
	{
		return (SysEx);
	}
	else if (messageType == "NoteOn")
	{
		return (NoteOn);
	}
	else if (messageType == "NoteOff")
	{
		return (NoteOff);
	}
	else if (messageType == "PitchWheel")
	{
		return (PitchWheel);
	}
	else if (messageType == "ProgramChange")
	{
		return (ProgramChange);
	}
	else if (messageType == "Multi")
	{
		return (Multi);
	}
	else if (messageType == "MidiClock")
	{
		return (MidiClock);
	}
	else if (messageType == "MidiClockContinue")
	{
		return (MidiClockContinue);
	}
	else if (messageType == "MidiClockStop")
	{
		return (MidiClockStop);
	}
	else if (messageType == "MidiClockStart")
	{
		return (MidiClockStart);
	}
	else if (messageType == "ActiveSense")
	{
		return (ActiveSense);
	}
	else
	{
		return (None);
	}
}

const CtrlrMidiMessageType midiMessageToType (const MidiMessage &midiMessage)
{
	if (midiMessage.isController())
	{
		return (CC);
	}
	else if (midiMessage.isSysEx())
	{
		return (SysEx);
	}
	else if (midiMessage.isNoteOn())
	{
		return (NoteOn);
	}
	else if (midiMessage.isNoteOff())
	{
		return (NoteOff);
	}
	else if (midiMessage.isAftertouch())
	{
		return (Aftertouch);
	}
	else if (midiMessage.isChannelPressure())
	{
		return (ChannelPressure);
	}
	else if (midiMessage.isProgramChange())
	{
		return (ProgramChange);
	}
	else if (midiMessage.isPitchWheel())
	{
		return (PitchWheel);
	}
	else if (midiMessage.isMidiClock())
	{
		return (MidiClock);
	}
	else if (midiMessage.isMidiContinue())
	{
		return (MidiClockContinue);
	}
	else if (midiMessage.isMidiStart())
	{
		return (MidiClockStart);
	}
	else if (midiMessage.isMidiStop())
	{
		return (MidiClockStop);
	}
	else if (midiMessage.isActiveSense())
	{
		return (ActiveSense);
	}
	return (SysEx);
}

const CtrlrSysExFormulaToken indirectFromString (const String &str)
{
	if (str == "ByteValue")
		return (ByteValue);
	if (str == "LSB7bitValue")
		return (LSB7bitValue);
	if (str == "MSB7bitValue")
		return (MSB7bitValue);
	if (str == "LSB4bitValue")
		return (LSB4bitValue);
	if (str == "MSB4bitValue")
		return (MSB4bitValue);
	if (str == "GlobalVariable")
		return (GlobalVariable);
	if (str == "LUA")
		return (LUAToken);
	if (str == "Formula")
		return (FormulaToken);
	return (ByteValue);
}

const CtrlrMidiMessageEx midiMessageExfromString (const String &str, const int ch, const int number, const int value)
{
	CtrlrMidiMessageEx ret;
	StringArray tokens;

	tokens.addTokens (str, ",", "\"\'");

	if (tokens.size() >= 5)
	{
		ret.indirectNumberFlag	= indirectFromString (tokens[1]);
		ret.indirectValueFlag	= indirectFromString (tokens[2]);
		ret.overrideNumber		= tokens[3].getIntValue();
		ret.overrideValue		= tokens[4].getIntValue();

		if (tokens[0] == "CC")
			ret.m				= MidiMessage::controllerEvent (ch,number,value);
		if (tokens[0] == "Aftertouch")
			ret.m				= MidiMessage::aftertouchChange (ch,number,value);
		if (tokens[0] == "NoteOn")
			ret.m				= MidiMessage::noteOn (ch,number,(uint8)value);
		if (tokens[0] == "NoteOff")
			ret.m				= MidiMessage::noteOff (ch,number,(uint8)value);
		if (tokens[0] == "ChannelPressure")
			ret.m				= MidiMessage::channelPressureChange (ch,value);
		if (tokens[0] == "ProgramChange")
			ret.m				= MidiMessage::programChange(ch,value);

		if (tokens[0] == "SysEx")
		{
			return (CtrlrSysexProcessor::sysexMessageFromString(tokens[5], value, ch));
		}

		ret.setNumber(number);
		ret.setValue(value);
		return (ret);
	}
	else
	{
	    jassertfalse; // Looks like there is not enough tokens to create a CtrlrMidiMessageEx object
		return (CtrlrMidiMessageEx());
	}
}

const String extractVendorId (const CtrlrMidiMessage &message)
{
	MemoryBlock bl = message.getData();
	uint8 byte1 = 0xf7, byte2 = 0x00, byte3 = 0x00;
	if (bl.getSize() >= 5)
		byte1 = bl[5];

	if (byte1 == 0x0)
	{
		if (bl.getSize() >= 8)
		{
			byte2 = bl[6];
			byte3 = bl[7];
		}

		return (String::formatted ("%02x%02x%02x", byte1, byte2, byte3).toUpperCase());
	}

	return (String::formatted ("%02x", byte1).toUpperCase());
}

const String removeInvalidChars(const String &dataToValidate, const bool showSpecials, const char characterToReplace)
{
	String ret;
	StringArray specials(asciiSpecials);

	for (int i=0; i<dataToValidate.length(); i++)
	{
		juce_wchar c = dataToValidate[i];

		if (c < 0x20 && c != 0xd && c != 0x0b && c != 0x09 && c != 0x0a )
		{
			if (showSpecials)
			{
				ret << specials[(int)c];
			}
			else
			{
				ret << characterToReplace;
			}
		}
		else
		{
			ret << c;
		}
	}

	return (ret);
}

ValueTree valueTreeFromXml (const String &dumpedXmlAsString)
{
	XmlDocument doc(dumpedXmlAsString);
	ScopedPointer <XmlElement> xml(doc.getDocumentElement());

	if (xml)
	{
		return (ValueTree::fromXml (*xml));
	}
	else
	{
		return (ValueTree());
	}
}

const MidiMessage createFromHexData (const String &hexData)
{
	MemoryBlock bl;
	bl.loadFromHexString(hexData);

	return (MidiMessage ((uint8*)bl.getData(), (int)bl.getSize()));
}

void setComboContentFromString (ComboBox *box, const String &content)
{
	StringArray top;
	top.addTokens (content, ":", "\'\"");

	for (int i=0; i<top.size(); i++)
	{
		StringArray item;
		item.addTokens (top[i], "=", "\'\"");

		if (item.size() == 2)
		{
			box->addItem (item[0], item[1].getIntValue());
		}
		if (item.size() == 1)
		{
			box->addItem (item[0], i+1);
		}
	}
}

const String generateRandomUnique(const String &additionalRandomData)
{
	Time t = Time::getCurrentTime();
	Random r(t.getHighResolutionTicks());
	String randData = additionalRandomData
		+ SystemStats::getComputerName()
		+ SystemStats::getCpuVendor()
		+ SystemStats::getFullUserName()
		+ SystemStats::getJUCEVersion()
		+ SystemStats::getLogonName()
		+ SystemStats::getOperatingSystemName();

	BigInteger bi;
	r.fillBitsRandomly(bi, 0, 64);

	return (bi.toMemoryBlock().toBase64Encoding());
}

const String generateRandomUniquePluginId()
{
    String ret;

    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < 4; ++i)
    {
        ret << alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return (ret);
}

void uniqueIntArray (Array <int> &arrayToModify)
{
	Array<int> temp;
	for (int i=0; i<arrayToModify.size(); i++)
	{
		temp.addIfNotAlreadyThere(arrayToModify[i]);
	}

	arrayToModify.swapWith (temp);
}

const String fileToBase64 (const File &file)
{
	MemoryBlock memoryBlock;
	file.loadFileAsData (memoryBlock);
	return (memoryBlock.toBase64Encoding());
}

int getMidiNumberFromModulator(CtrlrModulator *m)
{
	if (m == 0 || m->getMidiMessagePtr() == 0)
		return (-1);

	if (m->getMidiMessage().getMidiMessageArray().size() == 1)
	{
		return (getMidiNumberFromMidiMessage (m->getMidiMessage().getReference(0).m));
	}
	return (-1);
}

const CtrlrMidiMessageType getMidiTypeFromModulator(CtrlrModulator *m, const int index)
{
	if (m == 0 || m->getMidiMessagePtr() == 0)
		return (None);

	if (index < 0)
		return (m->getMidiMessage().getMidiMessageType());
	else
		return (midiMessageToType(m->getMidiMessage().getReference(index).m));
}

const int getMidiNumberFromMidiMessage (const MidiMessage &m)
{
	switch (midiMessageToType(m))
	{
		case CC:
			return (m.getControllerNumber());
			break;

		case NoteOn:
		case NoteOff:
		case Aftertouch:
			return (m.getNoteNumber());
			break;

		case PitchWheel:
		case ProgramChange:
		case ChannelPressure:
		case SysEx:
		default:
			break;
	}
	return (-1);
}

void addCtrlrMidiMessageToBuffer (MidiBuffer &bufferToAddTo, CtrlrMidiMessage &m)
{
	for (int i=0; i<m.getNumMessages(); i++)
	{
		bufferToAddTo.addEvent (m.getReference(i).m, 1);
	}
}

const String getMidiChannel(const MidiMessage &m)
{
	if (m.getChannel() > 0)
	{
		return (String::formatted (" Ch:[%2d]", m.getChannel()));
	}

	return (" Ch:[--]");
}

const String getMidiValue(const MidiMessage &m)
{
	if (m.isAftertouch())
	{
		return (String::formatted (" Val:[%4d]", m.getAfterTouchValue()));
	}

	if (m.isController())
	{
		return (String::formatted (" Val:[%4d]", m.getControllerValue()));
	}

	if (m.isNoteOnOrOff())
	{
		return (String::formatted (" Val:[%4d]", m.getVelocity()));
	}

	if (m.isPitchWheel())
	{
		return (String::formatted (" Val:[%4d]", m.getPitchWheelValue()));
	}

	if (m.isChannelPressure())
	{
		return (String::formatted (" Val:[%4d]", m.getChannelPressureValue()));
	}

	return (" Val:[----]");
}

const String getRawDataSize(const MidiMessage &m)
{
	return (String::formatted (" Size:[%6d]", m.getRawDataSize()));
}

const String getMidiNumber(const MidiMessage &m)
{
	if (m.isAftertouch())
	{
		return (String::formatted (" No:[%4d]", m.getNoteNumber()));
	}

	if (m.isController())
	{
		return (String::formatted (" No:[%4d]", m.getControllerNumber()));
	}

	if (m.isNoteOnOrOff())
	{
		return (String::formatted (" No:[%4d]", m.getNoteNumber()));
	}

	if (m.isProgramChange())
	{
		return (String::formatted (" No:[%4d]", m.getProgramChangeNumber()));
	}
	return (" No:[----]");
}

const String getRawData(const MidiMessage &m, const bool rawInDecimal)
{
	if (rawInDecimal)
	{
		String ret;
		uint8 *ptr = (uint8 *)m.getRawData();
		for (int i=0; i<m.getRawDataSize(); i++)
		{
			ret << String::formatted ("%.3d", (int)*(ptr+i));
			ret << " ";
		}
		return (" RAW:["+ret.trim()+"]");
	}
	else
	{
		return (" RAW:["+String::toHexString (m.getRawData(), m.getRawDataSize())+"]");
	}
}

const String getTimestamp(const MidiMessage &m)
{
	return (String::formatted (" Time(%.6d)", m.getTimeStamp()));
}

const String getName(const MidiMessage &m)
{
	if (m.isActiveSense())
	{
		return (" [Active Sense]");
	}

	if (m.isAftertouch())
	{
		return (" [Aftertouch]");
	}

	if (m.isAllNotesOff())
	{
		return (" [All notes off]");
	}

	if (m.isAllSoundOff())
	{
		return (" [All sound off]");
	}

	if (m.isChannelPressure())
	{
		return (" [Channel pressure]");
	}

	if (m.isController())
	{
		return (" [Controller]");
	}

	if (m.isFullFrame())
	{
		return (" [Full frame]");
	}

	if (m.isMetaEvent())
	{
		return (" [Meta event]");
	}

	if (m.isMidiClock())
	{
		return (" [MIDI Clock]");
	}

	if (m.isMidiContinue())
	{
		return (" [MIDI Continue]");
	}

	if (m.isMidiStart())
	{
		return (" [MIDI Start]");
	}

	if (m.isMidiStop())
	{
		return (" [MIDI Stop]");
	}

	if (m.isNoteOff())
	{
		return (" [Note off]");
	}

	if (m.isNoteOn())
	{
		return (" [Note on]");
	}

	if (m.isPitchWheel())
	{
		return (" [Pitch wheel]");
	}

	if (m.isProgramChange())
	{
		return (" [Program change]");
	}

	if (m.isQuarterFrame())
	{
		return (" Quarter frame]");
	}

	if (m.isSysEx())
	{
		return (" [System exclusive]");
	}

	return (" [Yet unknown]");
}

const String getMidiMessageAsLogString (const MidiMessage &m, const bool name, const bool channel, const bool number, const bool value, const bool timestamp, const bool rawData, const bool rawInDecimal, const bool rawDataSize)
{
	return ((timestamp ? getTimestamp(m) : "") + (rawDataSize ? getRawDataSize(m) : "") + (name ? getName(m) : "") + (channel ? getMidiChannel(m) : "") + (number ? getMidiNumber(m) : "") + (value ? getMidiValue(m) : "") + (rawData ? getRawData(m,rawInDecimal) : ""));
}

void setBitOption (int &storage, const int optionToSet, const bool isSet)
{
	if (isSet)
	{
		storage |= optionToSet;
	}
	else
	{
		storage &= ~optionToSet;
	}
}

const bool getBitOption (const int &storage, const int &optionToGet)
{
	return ((storage & optionToGet) != 0);
}

const String dumpTree (const ValueTree &tree)
{
	ScopedPointer <XmlElement> xml(tree.createXml());
	if (xml)
	{
		return (xml->createDocument(""));
	}

	return ("dumpTree: INVALID TREE");
}

const String getAudioFormatDetails(AudioFormat *format)
{
	String ret;

	Array<int> bitDepths		= format->getPossibleBitDepths();
	Array<int> sampleRates		= format->getPossibleSampleRates();
	StringArray qualityOptions	= format->getQualityOptions();
	bool isCompressed			= format->isCompressed();
	bool canDoMono				= format->canDoMono();
	bool canDoStereo			= format->canDoStereo();
	String name					= format->getFormatName();

	ret << "Name: " + name + "\n";
	ret << "SampleRates: ";
	for (int i=0; i<sampleRates.size(); i++)
	{
		ret << String(sampleRates[i]) + " ";
	}
	ret << "\n";
	ret << "BitDepths: ";
	for (int i=0; i<bitDepths.size(); i++)
	{
		ret << String(bitDepths[i]) + " ";
	}
	ret << "\n";
	ret << "QualityOptions: ";
	for (int i=0; i<qualityOptions.size(); i++)
	{
		ret << qualityOptions[i] + " ";
	}
	ret << "\n";
	ret << "CanDoMono: " + String(canDoMono ? "Yes" : "No") + "\n";
	ret << "CanDoStereo: " + String(canDoStereo ? "Yes" : "No") + "\n";
	ret << "IsCompressed: " + String(isCompressed ? "Yes" : "No") + "\n";

	return (ret);
}

const String getAudioFormatReaderDetails(AudioFormatReader *reader)
{
	String ret;

	ret << "SampleRate: " + String(reader->sampleRate) + "\n";
	ret << "BitsPerSample: " + String(reader->bitsPerSample) + "\n";
	ret << "LengthInSamples: " + String(reader->lengthInSamples) + "\n";
	ret << "NumChannels: " + String(reader->numChannels) + "\n";
	ret << "UsesFloatingPointData: " + String(reader->usesFloatingPointData);

	return (ret);
}

const int customInfoDialog (const String &title, Component *customComponent)
{
	AlertWindow wnd(title, String::empty, AlertWindow::InfoIcon);
	customComponent->setSize (400,400);
	wnd.addCustomComponent (customComponent);
	wnd.addButton ("OK", 1, KeyPress (KeyPress::returnKey));
	return (wnd.runModalLoop());
}

const String dataPrefix (const CtrlrMidiMessage &data, const int prefixLength)
{
	return (dataPrefix (data.getData(), prefixLength));
}

const String dataPrefix (const MemoryBlock &data, const int prefixLength)
{
    return ("("+STR((int)data.getSize())+")"+String::toHexString (data.getData(), ( (prefixLength < data.getSize()) ? prefixLength : data.getSize() ) ));
}

const bool isMonospaced(const Font &font)
{
	return (false);
}

const String labelFromProperty (CtrlrModulator *modulator, const String &formatText)
{
	if (modulator == nullptr)
		return (String::empty);

	String ret = formatText.replace ("%n", modulator->getName());
	if (modulator->getComponent())
	{
		ret = ret.replace ("%N", modulator->getComponent()->getProperty(Ids::componentVisibleName).toString());
		ret = ret.replace ("%s", modulator->getComponent()->getComponentText());
	}
	ret = ret.replace ("%v", String(modulator->getModulatorValue()));
	ret = ret.replace ("%h", String::formatted ("%x", modulator->getModulatorValue()));
	ret = ret.replace ("%x", modulator->getMidiMessage().toString());
	ret = ret.replace ("%g", modulator->getGroupName());

	return (ret);
}

