#ifndef __CTRLR_MIDI_INPUT_COMPARATOR__
#define __CTRLR_MIDI_INPUT_COMPARATOR__

#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrMidiMessage.h"
#include "CtrlrMidiInputComparatorMulti.h"
#include "CtrlrMidiInputComparatorSingle.h"

class CtrlrMidiInputComparator
{
	public:
		CtrlrMidiInputComparator(CtrlrPanel &_owner);
		~CtrlrMidiInputComparator();
		void addMatchTarget (CtrlrModulator *modulatorToAdd);
		void match (const MidiMessage &m);
		void match (const MidiBuffer &buffer);
		void clear();
		void panelEditModeChanged (const bool _panelEditMode);
		CtrlrMidiMessage &getSingleContainer() { return (singleContainer); }
		void rehashComparator();
        static void wrapForLua (lua_State *L);
		const String dumpTables();
		JUCE_LEAK_DETECTOR(CtrlrMidiInputComparator)

	private:
		CtrlrPanel &owner;
		CtrlrMidiInputComparatorSingle comparatorSingle;
		CtrlrMidiInputComparatorMulti comparatorMulti;
		CtrlrMidiMessage singleContainer, multiContainer;
		bool lastPanelMode;
};

#endif
