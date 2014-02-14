#ifndef __CTRLR_PANEL_MIDI_SNAPSHOT__
#define __CTRLR_PANEL_MIDI_SNAPSHOT__

#include "CtrlrMacros.h"
class CtrlrPanel;

class CtrlrPanelMIDISnapshot : public AsyncUpdater, public ThreadWithProgressWindow
{
	public:
		CtrlrPanelMIDISnapshot(CtrlrPanel &_owner);
		~CtrlrPanelMIDISnapshot();
		void sendSnapshot();
		void handleAsyncUpdate();
		void gatherSnapshotData();
		void run();
		void setDelay(const int _snapshotDelay);

		JUCE_LEAK_DETECTOR(CtrlrPanelMIDISnapshot)

	private:
		CtrlrPanel &owner;
		MidiBuffer buffer;
		int snapshotDelay;
};

#endif