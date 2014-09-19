#ifndef CTRLR_MIDI_MESSAGE_EX
#define CTRLR_MIDI_MESSAGE_EX

#include "CtrlrMacros.h"
#include "CtrlrSysexProcessorOwned.h"

class CtrlrMidiMessageEx
{
	public:
		CtrlrMidiMessageEx();
		CtrlrMidiMessageEx(const MidiMessage &other);
		bool operator== (const CtrlrMidiMessageEx &other) const;

		void setValue (const int value);
		void setNumber (const int number);
		void setChannel (const int channel);

		int getValue() const;
		int getNumber() const;
		Array <CtrlrSysexToken> &getTokenArray()					{ return (sysExTokenArray); }
		void setTokenArray(Array <CtrlrSysexToken> tokens)			{ sysExTokenArray = tokens; }

		CtrlrSysExFormulaToken indirectValueFlag, indirectNumberFlag;
		int overrideValue, overrideNumber;
		const BigInteger getBitValue();
		MidiMessage m;

		JUCE_LEAK_DETECTOR(CtrlrMidiMessageEx)

	private:
		Array <CtrlrSysexToken> sysExTokenArray;
		MemoryBlock messageContainer;
		int getValueInternal(const int value) const;
		int getNumberInternal(const int number) const;
};

#endif
