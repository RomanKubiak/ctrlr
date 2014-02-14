#ifndef __CTRLR_MIDI_INPUT_COMPARATOR_MULTI__
#define __CTRLR_MIDI_INPUT_COMPARATOR_MULTI__

#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrUtilities.h"
#include "CtrlrMidiInputComparatorTypes.h"

class CtrlrPanel;

class CtrlrMidiInputComparatorMulti : public Timer
{
	public:
		CtrlrMidiInputComparatorMulti(CtrlrPanel &_owner);
		~CtrlrMidiInputComparatorMulti();

		void clear();
		void addMatchTarget (CtrlrModulator *m);
		void match (const MidiMessage &m);
		const bool cacheMatch ();
		const bool basicMatch(const MidiMessage &m);
		void panelEditModeChanged (const bool _panelEditMode);
		void updateCache (CtrlrMultiMidiMapIterator &it);
		void updateState (const bool match);
		void timerCallback();
		const String dumpTableContents();
		JUCE_LEAK_DETECTOR(CtrlrMidiInputComparatorMulti)

	private:
		CtrlrPanel &owner;
		CtrlrMultiMidiMap map;
		CtrlrMidiMessage messageContainer;
		Array<int> messageTypesContainer;
		Array<unsigned int> messageSizeContainer;
		DefaultElementComparator<unsigned int> messageSizeContainerSorter;
		Array<CtrlrCacheDataMulti> cache;
		int cacheSize;
};

#endif