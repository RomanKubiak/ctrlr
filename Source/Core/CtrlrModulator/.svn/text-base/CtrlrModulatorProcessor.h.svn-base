#ifndef __CTRLR_MODULATOR_PROCESSOR__
#define __CTRLR_MODULATOR_PROCESSOR__

#include "CtrlrMacros.h"
#include "CtrlrMidiMessage.h"
#include "../MIDI/CtrlrOwnedMidiMessage.h"
#include "Methods/CtrlrLuaMethod.h"
#include "CtrlrValueMap.h"

class CtrlrProcessor;
class CtrlrModulator;

//==============================================================================
/** @brief Class that represents a Ctrlr Modulator processor, some explanation about expressions are found here
			This class always belongs to a CtrlrModulator and is responsible for handling value changes
			from the host, the GUI, and external midi devices

*/
class CtrlrModulatorProcessor : public AsyncUpdater, public Expression::Scope, public CtrlrMidiMessageOwner
{
	public:
		CtrlrModulatorProcessor(CtrlrModulator &_owner);
		~CtrlrModulatorProcessor();

		String getScopeUID() const;
		Expression getSymbolValue (const String& symbol) const;
		void visitRelativeScope (const String &scopeName, Visitor &visitor) const;
		void visit (const Scope &scope);
		void setForwardExpression (const String &forwardExpressionString);
		void setReverseExpression (const String &reverseExpressionString);
		void setModulatorMaxValue (const int newMaxValue);
		void setModulatorMinValue (const int newMinValue);
		void setValueChangedCallback (const String &methodName);
		void setGetValueFromMidiCallback (const String &methodName);
		void setGetValueForMidiCallback (const String &methodName);
		const int getValue() const;
		const int getValueMapped() const;
		const int getMax() const;
		const int getMin() const;

		/** Used for evaluating expressions when getting the midi value from the modulator (forward evaluation)

			A list of constants that can be used:
			- modulatorValue : the current linear value of the modulator
			- modulatorMappedValue : the current mapped value in case of components that have mappings
			- modulatorMax : the maximum value the modulator can have (non mapped)
			- modulatorMin : the minimum value the modulator can have (non mapped)
			- vstIndex : the VST/AU index of the paramter as seen by the host program
			- midiValue : the current value stored in the MIDI MESSAGE assosiated with the modulator
			- midiNumber : the number of the MIDI MESSAGE controller if applicable
		*/
		const int evaluateForward(const int inValue);

		/** Used for evaluating expressions when getting the modulator value from the incomming midi message

			A list of constants that can be used:
			- modulatorValue : the current linear value of the modulator
			- modulatorMappedValue : the current mapped value in case of components that have mappings
			- modulatorMax : the maximum value the modulator can have (non mapped)
			- modulatorMin : the minimum value the modulator can have (non mapped)
			- modulatorMappedMax : the maximum value the modulator can have (mapped)
			- modulatorMappedMin : the maximum value the modulator can have (mapped)
			- vstIndex : the VST/AU index of the paramter as seen by the host program
			- midiValue : the value of the incomming midi message
			- midiNumber : the number of the MIDI MESSAGE controller if applicable
		*/
		const int evaluateReverse(const int inValue);

		/** When evaluating expression in either direction a couple of utility functions can be used, the notation is the same as in C
			for example to get the absolute value of the modulator you'd type: "abs(modulatorValue)" as the expression

			A list of constants that can be used:
			- ceil : Returns the smallest integral value of the parameter
			- abs : Returns the absolute value of the parameter
			- floor : Returns the largest integral value that is not greater than the parameter
			- mod : divides two numbers and returns the result of the MODULO operation "%" in C 10 % 3 = 1, 0 % 5 = 0; 30 % 6 = 0; 32 % 5 = 2
			- fmod : Returns the floating-point remainder of the two parameters passed in
			- pow : Returns the first parameter raised to the power of the second (dunno what that could be used for but it's there)
			- gte : Return the larger or equal of the two passed parameters (a >= b), gte (modulatorValue, 0, modulatorValue, 128 - modulatorValue)
					will return modulatorValue if modulatorValue is greater then 0 and (128 - modulatorValue) if it is less then zero
			- gt : same as gte but greater then without the equal sign (a > b)
			- max : returns the bigger of two parameters
			- min : returns the smaller of two parameters
			- getBitRangeAsInt (value, startBit, numBits)
			- setBitRangeAsInt (value, startBit, numBits, valueToSet) 
			- clearBit (value, bitToClear) 
			- isBitSet (value, bitPosition) 
			- setBit (value, bitToSet) 
			- setGlobal (globalIndex, newValueToSet)
		*/
		double evaluateFunction (const String& functionName, const double* parameters, int numParameters) const;

		const int getValueForMidiMessage(const int value);
		const int getValueFromMidiMessage();
		void setValueFromGUI(const double inValue, const bool force=false, const bool mute=false);
		void setValueFromMIDI(CtrlrMidiMessage &m);
		void setValueFromHost(const float inValue);
		void handleAsyncUpdate();
		CtrlrProcessor *getProcessor();
		CtrlrOwnedMidiMessage *getMidiMessagePtr();
		CtrlrMidiMessage &getMidiMessage();
		CtrlrOwnedMidiMessage &getOwnedMidiMessage();
		void sendMidiMessage();
		void setMappedValue (const int mappedValue, const bool force, const bool mute=false);

		/** This is important for packed values, if we get a midi message that matches this modulator
			(is the same type and number), but it's value is out of defined range then we can't accept
			it otherwise a lot of modulators will react to the same message.

		*/
		const bool isInValidMappedRange(const int possibleValue) const;
		const float getValueForHost() const;
		const CtrlrValueMap &setValueMap (const String &mapAsString);
		void setValueMap (const CtrlrValueMap &map);
		CtrlrValueMap &getValueMap();
		void setLinkedToGlobal(const bool _linkedToGlobal, const int _globalIndex=-1);
		const bool getLinkedToGlobal();
		const int getLinkedToGlobalIndex();
		const void setParameterNotifyingHost();
		
		int getMidiChannelForOwnedMidiMessages();
		CtrlrSysexProcessor *getSysexProcessor();
		Array<int,CriticalSection> &getGlobalVariables();

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrModulatorProcessor)

	private:
		void setValue(const int value);
		bool usingForwardProcess, usingReverseProcess, usingValueMap, linkedToGlobal;
		ReadWriteLock processorLock;
		CtrlrModulator &owner;
		Expression forwardProcess;
		Expression reverseProcess;
		String forwardEvaluationErrors, reverseEvaluationErrors;
		ScopedPointer <CtrlrOwnedMidiMessage> ctrlrMidiMessage;
		int currentValue, currentMidiValue, maxValue, minValue, globalIndex;
		WeakReference <CtrlrLuaMethod> valueChangedCbk, getValueForMidiCbk, getValueFromMidiCbk;
		CtrlrValueMap valueMap;
};

#endif