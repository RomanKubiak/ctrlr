#ifndef __CTRLR_MIDI_DEVICE__
#define __CTRLR_MIDI_DEVICE__

#pragma warning(disable:4201)

#include "CtrlrMacros.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrIDs.h"
#include "CtrlrMidiMessage.h"
#include "CtrlrMidiDevice.h"

class CtrlrMidiDeviceManager;
class CtrlrManager;

class CtrlrMidiDevice : public ValueTree::Listener, public MidiInputCallback
{
	public:
		CtrlrMidiDevice(CtrlrMidiDeviceManager &_owner, const int idx, const String name, const bool type);
		virtual ~CtrlrMidiDevice();

		class Listener
		{
			public:
				virtual ~Listener(){}
				virtual int getListenerInputMidiChannel()=0;
				virtual void handleMIDIFromDevice(const MidiMessage &message)=0;
				virtual void handleMIDIFromHost(MidiBuffer &buffer)=0;
				virtual void handlePartialMIDIFromDevice (const uint8* messageData, const int numBytesSoFar, const double timestamp)=0;
		};

		void closeJuceDevice (const bool type);
		void closeRtDevice (const bool type);
		const bool openJuceDevice (const bool type);
		const bool openRtDevice (const bool type);
		void restoreState(const ValueTree &savedState);
		void setProperty (const Identifier& name, const var &newValue)									{ deviceTree.setProperty (name, newValue, 0); }
		const var &getProperty (const Identifier& name) const											{ return deviceTree.getProperty (name); }
		const var getProperty (const Identifier& name, const var &defaultReturnValue) const				{ return deviceTree.getProperty (name, defaultReturnValue); }
		UndoManager* getUndoManager() const																{ return (0); }
		ValueTree &getDeviceTree()																		{ return (deviceTree); }
		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
		void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
		void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
		void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
		void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}

		void addDeviceListener (CtrlrMidiDevice::Listener *l)											{ deviceListeners.add(l); }
		void removeDeviceListener (CtrlrMidiDevice::Listener *l)										{ deviceListeners.remove(l); }

		void handlePartialSysexMessage (MidiInput* source, const uint8* messageData, int numBytesSoFar, double timestamp);
		void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message);
		void sendMidiBuffer (const MidiBuffer &buffer, double millisecondCounterToStartAt=0);
		void sendMidiMessage (const MidiMessage &message, double millisecondCounterToStartAt=0);

		MidiInput *getInputDevicePtr();

		virtual const bool getType();
		virtual const bool getState();
		virtual const String getName();
		virtual const bool openDevice();
		virtual void closeDevice();

		JUCE_LEAK_DETECTOR(CtrlrMidiDevice)

	protected:
        MemoryBlock dataCollector;
		CtrlrMidiDeviceManager &owner;
		CriticalSection deviceLock;
		ValueTree deviceTree;
		MidiOutput *outJucePtr;
		MidiInput *inJucePtr;
		int deviceIndex;
        bool lastMessageWasSysex;
		MidiBuffer throwBuffer;
		ListenerList	<CtrlrMidiDevice::Listener,
							Array<CtrlrMidiDevice::Listener*,CriticalSection>
						> deviceListeners;
		CtrlrMidiMessage midiMessageCollector;
};

#endif
