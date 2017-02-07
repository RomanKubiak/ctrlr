#include "stdafx.h"
#include "CtrlrUtilities.h"
#include "CtrlrLog.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrComponents/CtrlrComponent.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "JuceClasses/LMemoryBlock.h"

#ifdef _WIN32
#pragma warning(disable:4706)
#endif // _WIN32

static const char *asciiSpecials[]	= {"[NUL]", "[SOH]", "[STX]", "[ETX]", "[EOT]", "[ENQ]", "[ACK]", "[BEL]", "[BS]", "[HT]", "[LF]", "[VT]", "[FF]", "[CR]", "[SO]", "[SI]", "[DLE]", "[DC1]", "[DC2]", "[DC3]", "[DC4]", "[NAK]", "[SYN]", "[ETB]", "[CAN]", "[EM]", "[SUB]", "[ESC]", "[FS]", "[GS]", "[RS]", "[US]", 0};
static const uint8 vendors_id[] = { 1,2,3,4,5,6,7,8,9,0x0A,0x0B,0x0C,0x0D,0x0E,0x10,0x11,0x12,0x13,0x14,0x1B,0x15,0x16,0x17,0x18,0x20,0x21,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2F,0x36,0x3E,0x40,0x41,0x42,0x43,0x44,0x45 };
static const uint8 midiByteMask = 0xff;

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

CtrlrMidiMessageType midiMessageStringToType (const String &messageType)
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

CtrlrMidiMessageType midiMessageToType (const MidiMessage &midiMessage)
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

CtrlrSysExFormulaToken indirectFromString (const String &str)
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

int getMidiNumberFromModulator(CtrlrModulator *m, const CtrlrMIDIDeviceType source)
{
	if (m == 0 || m->getMidiMessagePtr(source) == 0)
		return (-1);

	if (m->getMidiMessage(source).getMidiMessageArray().size() == 1)
	{
		return (getMidiNumberFromMidiMessage (m->getMidiMessage(source).getReference(0).m));
	}
	return (-1);
}

CtrlrMidiMessageType getMidiTypeFromModulator(CtrlrModulator *m, const int index, const CtrlrMIDIDeviceType source)
{
	if (m == 0)
		return (None);

    if (m->getMidiMessagePtr(source) == 0)
        return (None);

	if (index <= 0)
		return (m->getMidiMessage(source).getMidiMessageType());
	else
    {
        if (m->getMidiMessagePtr(source))
            return (midiMessageToType(m->getMidiMessagePtr(source)->getReference(index).m));
        else
            return (None);
    }
}

int getMidiNumberFromMidiMessage (const MidiMessage &m)
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
	return (String::formatted (" Time(%.6f)", m.getTimeStamp()));
}

const String getTimestamp(const double t)
{
	return (String::formatted (" Time(%.6d)", t));
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

const String getMidiMessageAsLogString (const MidiMessage &m, const double customTimestamp, const bool name, const bool channel, const bool number, const bool value, const bool timestamp, const bool rawData, const bool rawInDecimal, const bool rawDataSize)
{
	return ((timestamp ? (customTimestamp >= 0 ? getTimestamp(customTimestamp) : getTimestamp(m)) : "") 
				+ (rawDataSize ? getRawDataSize(m) : "") 
				+ (name ? getName(m) : "") 
				+ (channel ? getMidiChannel(m) : "") 
				+ (number ? getMidiNumber(m) : "") 
				+ (value ? getMidiValue(m) : "") 
				+ (rawData ? getRawData(m,rawInDecimal) : ""));
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

bool getBitOption (const int &storage, const int &optionToGet)
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

const String dataPrefix (const CtrlrMidiMessage &data, const int prefixLength)
{
	return (dataPrefix (data.getData(), prefixLength));
}

const String dataPrefix (const MemoryBlock &data, const int prefixLength)
{
    return ("("+STR((int)data.getSize())+")"+String::toHexString (data.getData(), ( (prefixLength < (int)data.getSize()) ? prefixLength : data.getSize() ) ));
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

class CtrlrUInt16
{
public:
	inline CtrlrUInt16(void* d) noexcept : data(static_cast <uint16*> (d)) {}

	inline void advance() noexcept { ++data; }
	inline void skip(int numSamples) noexcept { data += numSamples; }
	inline float getAsFloatLE() const noexcept { return (float)((1.0 / (1.0 + maxValue)) * (uint16)ByteOrder::swapIfBigEndian(*data)); }
	inline float getAsFloatBE() const noexcept { return (float)((1.0 / (1.0 + maxValue)) * (uint16)ByteOrder::swapIfLittleEndian(*data)); }
	inline void setAsFloatLE(float newValue) noexcept { *data = ByteOrder::swapIfBigEndian((uint16)jlimit<uint16>((uint16)-maxValue, (uint16)maxValue, roundToInt(newValue * (1.0 + maxValue)))); }
	inline void setAsFloatBE(float newValue) noexcept { *data = ByteOrder::swapIfLittleEndian((uint16)jlimit<uint16>((uint16)-maxValue, (uint16)maxValue, roundToInt(newValue * (1.0 + maxValue)))); }
	inline int32 getAsInt32LE() const noexcept { return (int32)(ByteOrder::swapIfBigEndian((uint16)*data) << 16); }
	inline int32 getAsInt32BE() const noexcept { return (int32)(ByteOrder::swapIfLittleEndian((uint16)*data) << 16); }
	inline void setAsInt32LE(int32 newValue) noexcept { *data = ByteOrder::swapIfBigEndian((uint16)(newValue >> 16)); }
	inline void setAsInt32BE(int32 newValue) noexcept { *data = ByteOrder::swapIfLittleEndian((uint16)(newValue >> 16)); }
	inline void clear() noexcept { *data = 0; }
	inline void clearMultiple(int num) noexcept { zeromem(data, (size_t)(num * bytesPerSample)); }
	template <class SourceType> inline void copyFromLE(SourceType& source) noexcept { setAsInt32LE(source.getAsInt32()); }
	template <class SourceType> inline void copyFromBE(SourceType& source) noexcept { setAsInt32BE(source.getAsInt32()); }
	inline void copyFromSameType(CtrlrUInt16& source) noexcept { *data = *source.data; }

	uint16* data;
	enum { bytesPerSample = 2, maxValue = 0xffff, resolution = (1 << 16), isFloat = 0 };
};

static const inline void mergeMidiData(const CtrlrMidiMessage &source, CtrlrMidiMessage &destination)
{
	if (source.getNumMessages() != destination.getNumMessages())
	{
		_WRN("mergeMidiData two incompatible midi messages passed in (number of sub messages inside)");
		return;
	}

	for (int i = 0; i<source.getNumMessages(); i++)
	{
		const uint8 *sourcePtr = source.getReference(i).m.getRawData();
		uint8 *destPtr = (uint8 *)destination.getReference(i).m.getRawData();

		for (int j = 0; j<source.getReference(i).m.getRawDataSize(); j++)
		{
			if (destPtr + j != nullptr && sourcePtr + j != nullptr)
				*(destPtr + j) = *(sourcePtr + j);
		}
	}
}

static inline int getIntValue(const float newValue, const int maxValue)
{
	return (roundFloatToInt(newValue*(float)maxValue));
}

static inline float getFloatValue(const int intValueToUse, const int maxValue)
{
	return ((float)intValueToUse / (float)maxValue);
}

static inline int	indirectOperation(const int inValue, const CtrlrSysExFormulaToken op)
{
	if (op == LSB7bitValue)
	{
		return (inValue & 127);
	}
	else if (op == MSB7bitValue)
	{
		return (inValue >> 7);
	}
	else if (op == LSB4bitValue)
	{
		return (inValue & 0xf);
	}
	else if (op == MSB4bitValue)
	{
		return ((inValue >> 4) & 0xf);
	}
	else
	{
		return (inValue);
	}
}

static inline int indirectReverseOperation(const int inValue, const CtrlrSysExFormulaToken op)
{
	BigInteger i(0);
	if (op == LSB7bitValue)
	{
		i.setBitRangeAsInt(0, 7, inValue);
		return (i.getBitRangeAsInt(0, 7));
	}
	else if (op == MSB7bitValue)
	{
		i.setBitRangeAsInt(7, 7, inValue);
		return (i.getBitRangeAsInt(0, 14));
	}
	else if (op == LSB4bitValue)
	{
		i.setBitRangeAsInt(0, 4, inValue);
		return (i.getBitRangeAsInt(0, 8));
	}
	else if (op == MSB4bitValue)
	{
		i.setBitRangeAsInt(4, 4, inValue);
		return (i.getBitRangeAsInt(0, 8));
	}
	else
	{
		return (inValue);
	}
}

static const inline BigInteger getValueAsBigInteger(const int inValue, const CtrlrSysExFormulaToken op)
{
	BigInteger i(0);
	if (op == LSB7bitValue)
	{
		i.setBitRangeAsInt(0, 7, inValue);
		return (i.getBitRangeAsInt(0, 14));
	}
	else if (op == MSB7bitValue)
	{
		i.setBitRangeAsInt(7, 7, inValue);
		return (i.getBitRangeAsInt(0, 14));
	}
	else if (op == LSB4bitValue)
	{
		i.setBitRangeAsInt(0, 4, inValue);
		return (i.getBitRangeAsInt(0, 8));
	}
	else if (op == MSB4bitValue)
	{
		i.setBitRangeAsInt(4, 4, inValue);
		return (i.getBitRangeAsInt(0, 8));
	}
	else
	{
		return (BigInteger(inValue));
	}
}

static const inline MemoryBlock midiMessagePattern(const CtrlrMidiMessageEx &mEx, const Array<CtrlrSysexToken> tokens, const Array <int, CriticalSection> &globalVariables)
{
	if (mEx.m.isNoteOff() || mEx.m.isNoteOn())
	{
		MemoryBlock bl(mEx.m.getRawData(), mEx.m.getRawDataSize());
		bl[2] = midiByteMask;
		return (bl);
	}
	else if (mEx.m.isController())
	{
		MemoryBlock bl(mEx.m.getRawData(), mEx.m.getRawDataSize());
		bl[2] = midiByteMask;
		return (bl);
	}
	else if (mEx.m.isChannelPressure())
	{
		MemoryBlock bl(mEx.m.getRawData(), mEx.m.getRawDataSize());
		bl[1] = midiByteMask;
		return (bl);
	}
	else if (mEx.m.isAftertouch())
	{
		MemoryBlock bl(mEx.m.getRawData(), mEx.m.getRawDataSize());
		bl[2] = midiByteMask;
		return (bl);
	}
	else if (mEx.m.isProgramChange())
	{
		MemoryBlock bl(mEx.m.getRawData(), mEx.m.getRawDataSize());
		bl[1] = midiByteMask;
		return (bl);
	}
	else if (mEx.m.isSysEx())
	{
		MemoryBlock bl(mEx.m.getRawData(), mEx.m.getRawDataSize());

		for (int i = 0; i<tokens.size(); i++)
		{
			if (tokens[i].getType() == GlobalVariable)
			{
				if (globalVariables[tokens[i].getAdditionalData()] >= 0)
					bl[i] = (uint8)globalVariables[tokens[i].getAdditionalData()];
			}
			else if (tokens[i].getType() != NoToken
				|| tokens[i].getType() == Ignore
				|| tokens[i].getType() == ChecksumRolandJP8080
				|| tokens[i].getType() == ChecksumWaldorfRackAttack)
			{
				bl[i] = midiByteMask;
			}
		}

		return (bl);
	}
	return (MemoryBlock());
}

static inline bool compareMemory(const MemoryBlock &haystack, const MemoryBlock &needle)
{
	if (haystack.getSize() != needle.getSize())
		return (false);

	for (size_t i = 0; i<needle.getSize(); i++)
	{
		if ((uint8)haystack[i] == midiByteMask)
		{
			continue;
		}
		else if ((uint8)haystack[i] != (uint8)needle[i])
		{
			return (false);
		}
	}
	return (true);
}

inline const BigInteger memoryToBits(const MemoryBlock &mb)
{
	BigInteger bi;
	bi.loadFromMemoryBlock(mb);
	return (bi);
}

static inline void channelizeBuffer(MidiBuffer &inputBuffer, MidiBuffer &outputBuffer, const int channel, const bool channelizeAllowed)
{
	if (channelizeAllowed == false)
	{
		outputBuffer.swapWith(inputBuffer);
		return;
	}

	MidiBuffer::Iterator i(inputBuffer);
	int time;
	MidiMessage m;

	while (i.getNextEvent(m, time))
	{
		m.setChannel(channel);
		outputBuffer.addEvent(m, 1);
	}
}

static inline float normalizeValue(const double& value, const double& minValue, const double& maxValue)
{
	// jassert(maxValue > minValue);
	// jassert(normalized >= 0.0f && normalized <= 1.0f);
	return ((float)((value - minValue) / (maxValue - minValue)));
}

static inline double denormalizeValue(const float& normalized, const double& minValue, const double& maxValue)
{
	// jassert(normalized >= 0.0f && normalized <= 1.0f);
	// jassert(maxValue > minValue);

	return roundFloatToInt(minValue + normalized * (maxValue - minValue));
}

void restoreProperties(const ValueTree &sourceTree, ValueTree &destinationTree, UndoManager *undoManager = 0, const String &propertyPrefix = String::empty)
{
	if (propertyPrefix == String::empty)
	{
		for (int i = sourceTree.getNumProperties(); --i >= 0;)
		{
			destinationTree.setProperty(sourceTree.getPropertyName(i), sourceTree.getProperty(sourceTree.getPropertyName(i)), undoManager);
		}

		return;
	}


	for (int i = sourceTree.getNumProperties(); --i >= 0;)
	{
		if (sourceTree.getPropertyName(i).toString().startsWith(propertyPrefix))
			destinationTree.setProperty(sourceTree.getPropertyName(i), sourceTree.getProperty(sourceTree.getPropertyName(i)), undoManager);
	}
}

static inline int add_file_and_line(lua_State* L)
{
	lua_Debug d;
	if (lua_getstack(L, 1, &d) == 1)
	{
		lua_getinfo(L, "Sln", &d);
		String err = lua_tostring(L, -1);
		lua_pop(L, 1);

		String msg;
		msg << "\nAt line [" + String(d.currentline) + "]: ";
		msg << String(d.short_src);
		msg << "\n";

		if (d.name != 0)
		{
			msg << "What: ";
			msg << d.what;
			msg << "\nNamewhat: ";
			msg << d.namewhat;
			msg << "\nName: ";
			msg << d.name;
		}

		msg << "\nError message: " << err;
		lua_pushstring(L, msg.toUTF8());
		return 1;
	}
	else
	{
		_LERR("add_file_and_line() failed at lua_getstack, unknown error occured");
		return (0);
	}
}

static inline bool isInvalidMethodName(const String &name)
{
	if (name.isEmpty() || name == COMBO_NONE_ITEM)
		return (true);

	return (false);
}

static const inline MemoryBlock luaArrayTomemoryBlock(const luabind::object &luaArray)
{
	MemoryBlock bl;
	if (luaArray.is_valid() && luabind::type(luaArray) == LUA_TTABLE)
	{
		for (luabind::iterator i(luaArray), end; i != end; i++)
		{
			const uint8 v = luabind::object_cast<uint8>(*i);
			bl.append(&v, 1);
		}
	}

	return (bl);
}

static inline Array<float> luaArrayToFloat(const luabind::object &luaArray)
{
	Array<float> data;

	if (luaArray.is_valid() && luabind::type(luaArray) == LUA_TTABLE)
	{
		for (luabind::iterator i(luaArray), end; i != end; i++)
		{
			data.add(luabind::object_cast<float>(*i));
		}
	}

	return (data);
}

static const inline MemoryBlock stringToMemoryBlock(const String &stringToConvert)
{
	return (MemoryBlock(stringToConvert.toUTF8().getAddress(), strlen(stringToConvert.toUTF8())));
}

static const inline MemoryBlock hexStringToMemoryBlock(const String &hexData)
{
	MemoryBlock bl(hexData.length() / 2, true);
	bl.loadFromHexString(hexData);
	return (bl);
}

static const inline String memoryBlockToString(const MemoryBlock &data)
{
	return (String::toHexString(data.getData(), data.getSize(), 1));
}

static const inline String dumpMemoryBlock(const MemoryBlock &data)
{
	return (memoryBlockToString(data));
}

static inline bool stringIsHexadecimal(const String &hexData)
{
	return hexData.isNotEmpty() && hexData.containsOnly("abcdefABCDEF0123456789 ");
}

static const inline String versionNumberToString(const int versionNumber)
{
	int patch = versionNumber % 100;
	int minor = versionNumber / 100 % 1000;
	int major = versionNumber / 100000;

	return (STR(major) + "." + STR(minor) + "." + STR(patch));
}

static const inline String versionNumberToString2(const int versionNumber)
{
	int minor = versionNumber % 100 / 10;
	int major = versionNumber / 100;

	return (STR(major) + "." + STR(minor));
}

static const inline MemoryBlock signData(const MemoryBlock &dataToSign, const RSAKey keyToSign)
{
	BigInteger md5DataAsBigInteger;
	md5DataAsBigInteger.loadFromMemoryBlock(MD5(dataToSign).getRawChecksumData());
	keyToSign.applyToValue(md5DataAsBigInteger);

	return (md5DataAsBigInteger.toMemoryBlock());
}

static inline int getVersionAsHexInteger(const String version)
{
	const StringArray segments = StringArray::fromTokens(version, ".", "\"'");

	int value = (segments[0].getIntValue() << 16)
		+ (segments[1].getIntValue() << 8)
		+ segments[2].getIntValue();

	if (segments.size() >= 4)
		value = (value << 8) + segments[3].getIntValue();

	return value;
}
#endif
