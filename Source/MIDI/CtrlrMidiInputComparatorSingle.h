#ifndef __CTRLR_MIDI_INPUT_COMPARATOR_SINGLE__
#define __CTRLR_MIDI_INPUT_COMPARATOR_SINGLE__

#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrUtilities.h"
#include "CtrlrMidiInputComparatorTypes.h"

class CtrlrPanel;

class CtrlrMidiInputComparatorSingle
{
	public:
		CtrlrMidiInputComparatorSingle(CtrlrPanel &_owner);
		~CtrlrMidiInputComparatorSingle();
		void clear();
		void match (const MidiMessage &m);
		void matchSysEx(const MidiMessage &m);
		const bool cacheMatch(CtrlrMidiMessageType type, const int number, const int channel);
		const bool cacheMatchSysEx ();
		void addMatchTarget (CtrlrModulator *m);
		void addMatchTargetSysEx (CtrlrModulator *m);
		CtrlrMidiMap &getMap(const CtrlrMidiMessageType t);

		Array<CtrlrCacheDataSingle> &getCache(const CtrlrMidiMessageType t);
		void updateCache (const CtrlrMidiMessageType t, CtrlrMidiMapIterator &it);
		void updateCacheSysEx (CtrlrMultiMidiMapIterator &it);
		const String dumpTableContents();
		
		JUCE_LEAK_DETECTOR(CtrlrMidiInputComparatorSingle)

	private:
		CtrlrPanel &owner;
		CtrlrMidiMessage messageContainer;
		CtrlrMultiMidiMap mapSysEx;
		Array<CtrlrCacheDataMulti> cacheSysEx;
		CtrlrMidiMap 
			mapCC, 
			mapAftertouch, 
			mapPitchWheel, 
			mapProgramChange, 
			mapNoteOn, 
			mapNoteOff, 
			mapChannelPressure,
			mapNull;

		Array<CtrlrCacheDataSingle>	
			cacheCC, 
			cacheAftertouch, 
			cachePitchWheel, 
			cacheProgramChange, 
			cacheNoteOn, 
			cacheNoteOff, 
			cacheChannelPressure,
			cacheNull;

		int cacheSize;
};

#endif