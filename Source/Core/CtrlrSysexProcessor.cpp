#include "stdafx.h"
#include "CtrlrMidiMessage.h"
#include "CtrlrSysexProcessor.h"
#include "CtrlrUtilities.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrLog.h"

CtrlrSysexProcessor::CtrlrSysexProcessor()
{
}

CtrlrSysexProcessor::~CtrlrSysexProcessor()
{
}

int CtrlrSysexProcessor::getGlobalIndex(const CtrlrSysexToken token)
{
	return (token.getAdditionalData());
}

void CtrlrSysexProcessor::sysExProcessToken (const CtrlrSysexToken token, uint8 *byte, const int value, const int channel)
{
	if (byte == NULL)
		return;

	BigInteger bi;

	switch (token.getType())
	{
		case ByteValue:
			*byte = (uint8)value;
			break;

		case ByteChannel:
			*byte = (uint8)jlimit (0,15, channel-1);
			break;

		case LSB7bitValue:
			*byte = (uint8)(value & 127);
			break;

		case MSB7bitValue:
			*byte = (uint8)(value >> 7);
			break;

		case ByteChannel4Bit:
			bi = BigInteger ((uint8)jlimit (0,15, channel-1));
			bi.setBitRangeAsInt (4, 3, token.getAdditionalData());
			*byte = (uint8)bi.getBitRangeAsInt(0,7);
			break;

		case GlobalVariable:
			if (getGlobalVariables() [token.getAdditionalData()] >= 0)
				*byte = (uint8)getGlobalVariables() [token.getAdditionalData()];
			break;

		case LSB4bitValue:
			*byte = (uint8)(value & 0xf);
			break;

		case MSB4bitValue:
			*byte = (uint8)((value >> 4) & 0xf);
			break;

		case RolandSplitByte1:
			*byte = getRolandSplit (value, 1);
			break;

		case RolandSplitByte2:
			*byte = getRolandSplit (value, 2);
			break;

		case RolandSplitByte3:
			*byte = getRolandSplit (value, 3);
			break;

		case RolandSplitByte4:
			*byte = getRolandSplit (value, 4);
			break;

        case CurrentProgram:
        case CurrentBank:
		case Ignore:
		case ChecksumRolandJP8080:
		case ChecksumWaldorfRackAttack:
		case FormulaToken:
		case LUAToken:
		case NoToken:
			break;
	}
}

void CtrlrSysexProcessor::sysExProcess (const Array<CtrlrSysexToken> &tokens, MidiMessage &m, const int value, const int channel)
{
	if (tokens.size() != m.getRawDataSize())
		return;

	uint8 *dataPtr = (uint8 *)m.getRawData();

	for (int i=0; i<m.getRawDataSize(); i++)
	{
		sysExProcessToken (tokens.getReference(i), dataPtr+i, value, channel);
	}

	sysexProcessPrograms(tokens, m);
	sysexProcessChecksums(tokens, m);
}

void CtrlrSysexProcessor::sysexProcessChecksums(const Array<CtrlrSysexToken> &tokens, MidiMessage &m)
{
	if (tokens.size() != m.getRawDataSize())
		return;

	for (int i=0; i<m.getRawDataSize(); i++)
	{
		if (tokens.getReference(i).getType() == ChecksumRolandJP8080)
		{
			checksumRolandJp8080 (tokens.getReference(i), m);
		}

		if (tokens.getReference(i).getType() == ChecksumWaldorfRackAttack)
		{
			checksumWaldorfRackAttack (tokens.getReference(i), m);
		}
	}
}

void CtrlrSysexProcessor::sysexProcessPrograms(const Array<CtrlrSysexToken> &tokens, MidiMessage &m)
{
	return;
}


const CtrlrMidiMessageEx CtrlrSysexProcessor::sysexMessageFromString (const String &formula, const int value, const int channel)
{
	MidiMessage m;
	MemoryBlock bl(0,true);
	StringArray tokens;
	tokens.addTokens (formula, " ;:", "\"");

	for (int i=0; i<tokens.size(); i++)
	{
		const int d = jmin<int> (tokens[i].getHexValue32(),255);
		bl.append (&d, 1);
	}

	Array <CtrlrSysexToken> tokenArray = sysExToTokenArray(formula);

	CtrlrMidiMessageEx mex;
	mex.m  = MidiMessage (bl.getData(), bl.getSize());
	mex.setTokenArray(tokenArray);
	return (mex);
}

const double CtrlrSysexProcessor::getValueFromSysExData (const Array<CtrlrSysexToken> &tokens, const CtrlrMidiMessageEx &message)
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

const uint8 CtrlrSysexProcessor::getRolandSplit (const int value, const int byteNum)
{
	const double result4   = value/16;
	const double reminder4 = fmod((double)value, 16.0);

	const double result3   = result4/16;
	const double reminder3 = fmod(result4, 16.0);

	const double result2   = result3/16;
	const double reminder2 = fmod(result3, 16.0);
	const double reminder1 = fmod(result2, 16.0);

	switch (byteNum)
	{
		case 1:
			return (jlimit<uint8>(0,127,(uint8)reminder1));
		case 2:
			return (jlimit<uint8>(0,127,(uint8)reminder2));
		case 3:
			return (jlimit<uint8>(0,127,(uint8)reminder3));
		case 4:
			return (jlimit<uint8>(0,127,(uint8)reminder4));
		default:
			return (0);
	}
}

const StringArray CtrlrSysexProcessor::templatesPrepare()
{
	StringArray templates;

	for (int i=0; i<kMidiMessageType; i++)
	{
		templates.add (midiMessageTypeToString((CtrlrMidiMessageType)i));
	}

	return (templates);
}

/** Static functions
*/

double CtrlrSysexProcessor::getValue(const Array<CtrlrSysexToken> &tokens, const CtrlrMidiMessageEx &message)
{
	double v = -1;

	for (int i=0; i<tokens.size(); i++)
	{
		if (tokens[i].isHoldingValue())
		{
			v += indirectReverseOperation (*(message.m.getRawData()+i), tokens[i].getType());
		}
	}

	return (v);
}

void CtrlrSysexProcessor::setSysExFormula(CtrlrMidiMessage &message, const String &formulaString)
{
	/* parse the formula to byte format */
	message.getMidiMessageArray().clear();
	message.getMidiMessageArray().add (sysexMessageFromString(formulaString, message.getValue(), message.getChannel()));
}

void CtrlrSysexProcessor::setMultiMessageFromString(CtrlrMidiMessage &message, const String &savedState)
{
	if (savedState.trim() == String::empty)
		return;

	StringArray messages;
	const int ch = message.getChannel();
	const int v  = message.getValue();
	const int n  = message.getNumber();

	message.getMidiMessageArray().clear();
	messages.addTokens (savedState.trim(), ":", "\"\'");

	for (int i=0; i<messages.size(); i++)
	{
		message.getMidiMessageArray().add (midiMessageExfromString (messages[i], ch, n, v));
	}
}

const Array<CtrlrSysexToken> CtrlrSysexProcessor::sysExToTokenArray (const String &formula)
{
	Array <CtrlrSysexToken> tokensToReturn;

	StringArray ar;
	ar.addTokens (formula, " :;", "\"\'");

	for (int i=0; i<ar.size(); i++)
	{
		CtrlrSysexToken tokenToAdd (i, *ar[i].substring(0,1).toUTF8(), sysExIdentifyToken (ar[i]));

		if (tokenToAdd.getType() == ByteChannel4Bit)
		{
			tokenToAdd.setAdditionalData (ar[i].substring(0,1).getHexValue32());
		}
		if (tokenToAdd.getType() == GlobalVariable
			|| tokenToAdd.getType() == ChecksumRolandJP8080
			|| tokenToAdd.getType() == ChecksumWaldorfRackAttack)
		{
			tokenToAdd.setAdditionalData (ar[i].substring(1,2).getHexValue32());
		}

		tokensToReturn.add (tokenToAdd);
	}

	return (tokensToReturn);
}

const CtrlrSysExFormulaToken CtrlrSysexProcessor::sysExIdentifyToken(const String &s)
{
	if (s == "xx")
	{
		return (ByteValue);
	}
	if (s.endsWith("y") && !s.startsWith("y"))
	{
		return (ByteChannel4Bit);
	}
	if (s.startsWith("k") || s.startsWith("p") || s.startsWith("n") || s.startsWith("o"))
	{
		return (GlobalVariable);
	}
	if (s.startsWith("z"))
	{
		return (ChecksumRolandJP8080);
	}
	if (s.startsWith("w"))
	{
		return (ChecksumWaldorfRackAttack);
	}
	if (s.startsWith("u"))
	{
		return (LUAToken);
	}
	if (s.startsWith ("v"))
	{
		return (FormulaToken);
	}
	if (s == "yy")
	{
		return (ByteChannel);
	}
	if (s == "LS")
	{
		return (LSB7bitValue);
	}
	if (s == "MS")
	{
		return (MSB7bitValue);
	}
	if (s == "ii")
	{
		return (Ignore);
	}
	if (s == "ls")
	{
		return (LSB4bitValue);
	}
	if (s == "ms")
	{
		return (MSB4bitValue);
	}

	if (s == "r1")
	{
		return (RolandSplitByte1);
	}
	if (s == "r2")
	{
		return (RolandSplitByte2);
	}
	if (s == "r3")
	{
		return (RolandSplitByte3);
	}
	if (s == "r4")
	{
		return (RolandSplitByte4);
	}
	if (s == "tp")
	{
		return (CurrentProgram);
	}
	if (s == "tb")
	{
		return (CurrentBank);
	}
	return (NoToken);
}

/** Checksum processors
*/
void CtrlrSysexProcessor::checksumRolandJp8080(const CtrlrSysexToken token, MidiMessage &m)
{
	/*
	Since +5 is parameter value 1DH,
	F0 41 10 00 06 (model id) 12 (command if) 01 00 10 03 (address) 1D (data) ?? (checksum) F7

	Next we calculate the checksum.
	01H + 00H + 10H + 03H + 1DH = 1 + 0 + 16 + 3 + 29 = 49 (sum)
	49 (total) 128 ÷ 0 (quotient) ... 49 (remainder)
	checksum = 128 - 49 (quotient) = 79 = 4FH

	This means that the message transmitted will be F0 41 10 00 06 12 01 00 10 03 1D 4F F7
	*/

	const int startByte = token.getPosition() - token.getAdditionalData();
	double chTotal		= 0.0;
	uint8 *ptr	= (uint8 *)m.getRawData();

	for (int i=startByte; i<token.getPosition(); i++)
	{
		chTotal = chTotal + *(ptr+i);
	}
	const double remainder	= fmod(chTotal, 128);
	const uint8 ch			= (uint8)(remainder ? (128 - remainder) : 0);
	*(ptr+token.getPosition())   = ch;
}

void CtrlrSysexProcessor::checksumWaldorfRackAttack(const CtrlrSysexToken token, MidiMessage &m)
{
	const int startByte = token.getPosition() - token.getAdditionalData();
	int chTotal			= 0;
	uint8 *ptr			= (uint8 *)m.getRawData();


	for (int i=startByte; i<token.getPosition(); i++)
	{
		chTotal = chTotal + *(ptr+i);
	}

	*(ptr+token.getPosition())   = chTotal & 0x7f;
}
