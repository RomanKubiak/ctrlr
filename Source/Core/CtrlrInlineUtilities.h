#ifndef __CTRLR_INLINE_UTILITIES__
#define __CTRLR_INLINE_UTILITIES__

#include "stdafx.h"
#include "CtrlrLog.h"
#include "CtrlrMidiMessage.h"
#include "CtrlrOwnedMidiMessage.h"
#include "CtrlrSysexProcessor.h"
#include "CtrlrMidiInputComparatorTypes.h"
#include "CtrlrValueMap.h"

static const uint8 vendors_id[]		= { 1,2,3,4,5,6,7,8,9,0x0A,0x0B,0x0C,0x0D,0x0E,0x10,0x11,0x12,0x13,0x14,0x1B,0x15,0x16,0x17,0x18,0x20,0x21,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2F,0x36,0x3E,0x40,0x41,0x42,0x43,0x44,0x45 };
static const uint8 midiByteMask		= 0xff;

class CtrlrUInt16
    {
    public:
        inline CtrlrUInt16 (void* d) noexcept  : data (static_cast <uint16*> (d))  {}

        inline void advance() noexcept                          { ++data; }
        inline void skip (int numSamples) noexcept              { data += numSamples; }
        inline float getAsFloatLE() const noexcept              { return (float) ((1.0 / (1.0 + maxValue)) * (uint16) ByteOrder::swapIfBigEndian (*data)); }
        inline float getAsFloatBE() const noexcept              { return (float) ((1.0 / (1.0 + maxValue)) * (uint16) ByteOrder::swapIfLittleEndian (*data)); }
        inline void setAsFloatLE (float newValue) noexcept      { *data = ByteOrder::swapIfBigEndian ((uint16) jlimit<uint16> ((uint16) -maxValue, (uint16) maxValue, roundToInt (newValue * (1.0 + maxValue)))); }
        inline void setAsFloatBE (float newValue) noexcept      { *data = ByteOrder::swapIfLittleEndian ((uint16) jlimit<uint16> ((uint16) -maxValue, (uint16) maxValue, roundToInt (newValue * (1.0 + maxValue)))); }
        inline int32 getAsInt32LE() const noexcept              { return (int32) (ByteOrder::swapIfBigEndian ((uint16) *data) << 16); }
        inline int32 getAsInt32BE() const noexcept              { return (int32) (ByteOrder::swapIfLittleEndian ((uint16) *data) << 16); }
        inline void setAsInt32LE (int32 newValue) noexcept      { *data = ByteOrder::swapIfBigEndian ((uint16) (newValue >> 16)); }
        inline void setAsInt32BE (int32 newValue) noexcept      { *data = ByteOrder::swapIfLittleEndian ((uint16) (newValue >> 16)); }
        inline void clear() noexcept                            { *data = 0; }
        inline void clearMultiple (int num) noexcept            { zeromem (data, (size_t) (num * bytesPerSample)) ;}
        template <class SourceType> inline void copyFromLE (SourceType& source) noexcept    { setAsInt32LE (source.getAsInt32()); }
        template <class SourceType> inline void copyFromBE (SourceType& source) noexcept    { setAsInt32BE (source.getAsInt32()); }
        inline void copyFromSameType (CtrlrUInt16& source) noexcept   { *data = *source.data; }

        uint16* data;
        enum { bytesPerSample = 2, maxValue = 0xffff, resolution = (1 << 16), isFloat = 0 };
    };

static const inline void mergeMidiData (const CtrlrMidiMessage &source, CtrlrMidiMessage &destination)
{
	if (source.getNumMessages() != destination.getNumMessages())
	{
		_WRN("mergeMidiData two incompatible midi messages passed in (number of sub messages inside)");
		return;
	}

	for (int i=0; i<source.getNumMessages(); i++)
	{
		const uint8 *sourcePtr	= source.getReference(i).m.getRawData();
		uint8 *destPtr			= (uint8 *)destination.getReference(i).m.getRawData();

		for (int j=0; j<source.getReference(i).m.getRawDataSize(); j++)
		{
			if (destPtr+j != nullptr && sourcePtr+j != nullptr)
				*(destPtr+j) = *(sourcePtr+j);
		}
	}
}

static const inline int getIntValue(const float newValue, const int maxValue)
{
	return (roundFloatToInt(newValue*(float)maxValue));
}

static const inline float getFloatValue(const int intValueToUse, const int maxValue)
{
	return ((float)intValueToUse/(float)maxValue);
}

static const inline int	indirectOperation (const int inValue, const CtrlrSysExFormulaToken op)
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

static const inline int indirectReverseOperation (const int inValue, const CtrlrSysExFormulaToken op)
{
	BigInteger i(0);
	if (op == LSB7bitValue)
	{
		i.setBitRangeAsInt (0,7,inValue);
		return (i.getBitRangeAsInt(0,7));
	}
	else if (op == MSB7bitValue)
	{
		i.setBitRangeAsInt (7,7,inValue);
		return (i.getBitRangeAsInt(0,14));
	}
	else if (op == LSB4bitValue)
	{
		i.setBitRangeAsInt (0,4,inValue);
		return (i.getBitRangeAsInt (0,8));
	}
	else if (op == MSB4bitValue)
	{
		i.setBitRangeAsInt (4,4,inValue);
		return (i.getBitRangeAsInt (0,8));
	}
	else
	{
		return (inValue);
	}
}

static const inline BigInteger getValueAsBigInteger (const int inValue, const CtrlrSysExFormulaToken op)
{
	BigInteger i(0);
	if (op == LSB7bitValue)
	{
		i.setBitRangeAsInt (0,7,inValue);
		return (i.getBitRangeAsInt(0,14));
	}
	else if (op == MSB7bitValue)
	{
		i.setBitRangeAsInt (7,7,inValue);
		return (i.getBitRangeAsInt(0,14));
	}
	else if (op == LSB4bitValue)
	{
		i.setBitRangeAsInt (0,4,inValue);
		return (i.getBitRangeAsInt (0,8));
	}
	else if (op == MSB4bitValue)
	{
		i.setBitRangeAsInt (4,4,inValue);
		return (i.getBitRangeAsInt (0,8));
	}
	else
	{
		return (BigInteger(inValue));
	}
}

static const inline MemoryBlock midiMessagePattern (const CtrlrMidiMessageEx &mEx, const Array<CtrlrSysexToken> tokens, const Array <int,CriticalSection> &globalVariables)
{
	if (mEx.m.isNoteOff() || mEx.m.isNoteOn())
	{
		MemoryBlock bl (mEx.m.getRawData(), mEx.m.getRawDataSize());
		bl[2] = midiByteMask;
		return (bl);
	}
	else if (mEx.m.isController())
	{
		MemoryBlock bl (mEx.m.getRawData(), mEx.m.getRawDataSize());
		bl[2] = midiByteMask;
		return (bl);
	}
	else if (mEx.m.isChannelPressure())
	{
		MemoryBlock bl (mEx.m.getRawData(), mEx.m.getRawDataSize());
		bl[1] = midiByteMask;
		return (bl);
	}
	else if (mEx.m.isAftertouch())
	{
		MemoryBlock bl (mEx.m.getRawData(), mEx.m.getRawDataSize());
		bl[2] = midiByteMask;
		return (bl);
	}
	else if (mEx.m.isProgramChange())
	{
		MemoryBlock bl (mEx.m.getRawData(), mEx.m.getRawDataSize());
		bl[1] = midiByteMask;
		return (bl);
	}
	else if (mEx.m.isSysEx())
	{
		MemoryBlock bl (mEx.m.getRawData(), mEx.m.getRawDataSize());

		for (int i=0; i<tokens.size(); i++)
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

static const inline bool compareMemory (const MemoryBlock &haystack, const MemoryBlock &needle)
{
	if (haystack.getSize() != needle.getSize())
		return (false);

	for (size_t i=0; i<needle.getSize(); i++)
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
	bi.loadFromMemoryBlock (mb);
	return (bi);
}

static inline void channelizeBuffer (MidiBuffer &inputBuffer, MidiBuffer &outputBuffer, const int channel, const bool channelizeAllowed)
{
	if (channelizeAllowed == false)
	{
		outputBuffer.swapWith (inputBuffer);
		return;
	}

	MidiBuffer::Iterator i(inputBuffer);
	int time;
	MidiMessage m;

	while (i.getNextEvent(m,time))
	{
		m.setChannel (channel);
		outputBuffer.addEvent (m, 1);
	}
}

static const inline float normalizeValue (const double& value, const double& minValue, const double& maxValue)
{
	// jassert(maxValue > minValue);
    // jassert(normalized >= 0.0f && normalized <= 1.0f);
    return ((float)((value - minValue) / (maxValue - minValue)));
}

static const inline double denormalizeValue (const float& normalized, const double& minValue, const double& maxValue)
{
	// jassert(normalized >= 0.0f && normalized <= 1.0f);
	// jassert(maxValue > minValue);

    return roundFloatToInt (minValue + normalized * (maxValue - minValue));
}

static const inline void restoreProperties (const ValueTree &sourceTree, ValueTree &destinationTree, UndoManager *undoManager=0, const String &propertyPrefix=String::empty)
{
	if (propertyPrefix == String::empty)
	{
		for (int i=sourceTree.getNumProperties(); --i >= 0;)
		{
			destinationTree.setProperty (sourceTree.getPropertyName(i), sourceTree.getProperty(sourceTree.getPropertyName(i)), undoManager);
		}

		return;
	}


	for (int i=sourceTree.getNumProperties(); --i >= 0;)
	{
		if (sourceTree.getPropertyName(i).toString().startsWith (propertyPrefix))
			destinationTree.setProperty (sourceTree.getPropertyName(i), sourceTree.getProperty(sourceTree.getPropertyName(i)), undoManager);
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
		msg << "\nAt line ["+String(d.currentline)+"]: ";
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

static const inline bool isInvalidMethodName(const String &name)
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
		for(luabind::iterator i(luaArray), end; i != end; i++)
		{
			const uint8 v = luabind::object_cast<uint8>(*i);
			bl.append (&v, 1);
		}
	}

	return (bl);
}

static const inline MemoryBlock stringToMemoryBlock (const String &stringToConvert)
{
	return (MemoryBlock (stringToConvert.toUTF8().getAddress(), strlen(stringToConvert.toUTF8())));
}

static const inline MemoryBlock hexStringToMemoryBlock (const String &hexData)
{
	MemoryBlock bl(hexData.length()/2, true);
	bl.loadFromHexString (hexData);
	return (bl);
}

static const inline String memoryBlockToString(const MemoryBlock &data)
{
	return (String::toHexString (data.getData(), data.getSize(), 1));
}

static const inline String dumpMemoryBlock(const MemoryBlock &data)
{
	return (memoryBlockToString(data));
}

static const inline bool stringIsHexadecimal (const String &hexData)
{
	return hexData.isNotEmpty() && hexData.containsOnly ("abcdefABCDEF0123456789 ");
}

static const inline String versionNumberToString (const int versionNumber)
{
	int patch		= versionNumber % 100;
	int minor		= versionNumber / 100 % 1000;
	int major		= versionNumber / 100000;

	return (STR(major)+"."+STR(minor)+"."+STR(patch));
}

static const inline String versionNumberToString2 (const int versionNumber)
{
	int minor		= versionNumber % 100 / 10;
	int major		= versionNumber / 100;

	return (STR(major)+"."+STR(minor));
}

static const inline MemoryBlock signData (const MemoryBlock &dataToSign, const RSAKey keyToSign)
{
    BigInteger md5DataAsBigInteger;
    md5DataAsBigInteger.loadFromMemoryBlock (MD5 (dataToSign).getRawChecksumData());
    keyToSign.applyToValue (md5DataAsBigInteger);

    return (md5DataAsBigInteger.toMemoryBlock());
}

static const inline getVersionAsHexInteger(const String version)
{
    const StringArray segments = StringArray::fromTokens (version, ".", "\"'");

    int value = (segments[0].getIntValue() << 16)
    + (segments[1].getIntValue() << 8)
    + segments[2].getIntValue();

    if (segments.size() >= 4)
        value = (value << 8) + segments[3].getIntValue();

    return value;
}
#endif
