#ifndef __CTRLR_PANEL_MIDI_INPUT_THREAD__
#define __CTRLR_PANEL_MIDI_INPUT_THREAD__

#include "CtrlrMacros.h"
#include "CtrlrMidiDevice.h"
#include "CtrlrMidiInputComparator.h"

class CtrlrPanel;

class CtrlrPanelMIDIInputThread : public Thread, public CtrlrMidiDevice::Listener, public CtrlrPanelMidiProcessor
{
	public:
		CtrlrPanelMIDIInputThread(CtrlrPanel &_owner, CtrlrMIDIDeviceType _source);
		~CtrlrPanelMIDIInputThread();
		void run();
		int getListenerInputMidiChannel();
		void handleMIDIFromDevice(const MidiMessage &message);
		void handleMIDIFromHost(MidiBuffer &buffer);
		void processMessage(MidiMessage &/*midiMessage*/) {}
		void handlePartialMIDIFromDevice (const uint8* messageData, const int numBytesSoFar, const double timestamp);
		bool openInputDevice (const String &inputDeviceName);
		void panelEditModeChanged (const bool _panelEditMode);
		CtrlrMidiInputComparator &getInputComparator();
		void process();
		void midiOptionChanged(const CtrlrPanelMidiOption /*optionThatChanged*/){}
		void midiChannelChaned(const CtrlrPanelMidiChannel channelThatChanged);
		void closeInputDevice();
		JUCE_LEAK_DETECTOR(CtrlrPanelMIDIInputThread)

	private:
		MidiBuffer deviceInputBuffer, hostInputBuffer, thruToDeviceBuffer, junkBuffer;
		ReadWriteLock lock;
		CtrlrPanel &owner;
		CtrlrMidiDevice *inputDevice;
		CtrlrMIDIDeviceType source;
		ScopedPointer <CtrlrMidiInputComparator> inputComparator;
};

#endif
