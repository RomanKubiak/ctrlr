#ifndef CTRLR_PANEL_MIDI_SNAPSHOT
#define CTRLR_PANEL_MIDI_SNAPSHOT

#include "CtrlrMacros.h"
class CtrlrPanel;

class CtrlrPanelMIDISnapshot : public AsyncUpdater, public Thread, public Timer
{
	public:
		CtrlrPanelMIDISnapshot(CtrlrPanel &_owner);
		~CtrlrPanelMIDISnapshot();
		void sendSnapshot();
		void handleAsyncUpdate();
		void gatherSnapshotData();
		void run();
		void setDelay(const int _snapshotDelay);
		void setStatusMessage (const String& newStatusMessage);
		void setPreLuaCallback(CtrlrLuaMethod *method);
		void setPostLuaCallback(CtrlrLuaMethod *method);

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrPanelMIDISnapshot)

	private:
	    void timerCallback() override;
        double progress;
        AlertWindow *alertWindow;
        bool wasCancelledByUser;
        String message;
        CriticalSection messageLock;
        bool showDialog;
		CtrlrPanel &owner;
		MidiBuffer buffer;
		int snapshotDelay;
		WeakReference <CtrlrLuaMethod> luaPanelMidiSnapshotPostCbk, luaPanelMidiSnapshotPreCbk;
};

#endif
