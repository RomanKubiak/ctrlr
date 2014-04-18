#ifndef CTRLR_MIDI_FILTER_H
#define CTRLR_MIDI_FILTER_H

class CtrlrMIDIFilter
{
	public:
		enum CtrlrMIDIFilterType
		{
			WhiteList,
			BlackList
		};

		CtrlrMIDIFilter(ValueTree &filterTree);
		void setTree (ValueTree &filterTree);
		ValueTree &getTree();
		void setType(const CtrlrMIDIFilterType type);
		const CtrlrMIDIFilterType getType();

        void setMIDIType(const CtrlrMidiMessageType type);
        const CtrlrMidiMessageType getMIDIType();
        void setMIDIValueRange (const Range<int> valueRange);
        const Range<int> getMIDIValueRange();
        void setMIDINumberRange (const Range<int> numberRange);
        const Range<int> getMIDINumberRange();
        void setMIDIRawDataMask(const String &rawDataMask);
        const String getMIDIRawDataMask();
};

class CtrlrMIDIFilterSet
{
	public:
		CtrlrMIDIFilterSet();
		~CtrlrMIDIFilterSet();
		void process (MidiBuffer &eventsToProcess);
		bool process (const MidiMessage &eventToProcess);

	private:
		ValueTree filterTree;
};

#endif
