#ifndef __CTRLR_MIDI_DEVICE__
#define __CTRLR_MIDI_DEVICE__

#ifdef _WIN32
#pragma warning(disable:4201)
#endif // _WIN32

#include "CtrlrMacros.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrIDs.h"
#include "CtrlrMidiMessage.h"
#include "CtrlrMIDIDevice.h"

class CtrlrMIDIDeviceManager;
class CtrlrManager;

class CtrlrMIDIDevice : public ValueTree::Listener, public MidiInputCallback
{
	public:
		CtrlrMIDIDevice(CtrlrMIDIDeviceManager &_owner, const int idx, const String name, const String identifier, const bool type);
		virtual ~CtrlrMIDIDevice();

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
		bool openJuceDevice (const bool type);
		bool openRtDevice (const bool type);
		void restoreState(const ValueTree &savedState);
		void setProperty (const Identifier& name, const var &newValue)									{ deviceTree.setProperty (name, newValue, 0); }
		const var &getProperty (const Identifier& name) const											{ return deviceTree.getProperty (name); }
		const var getProperty (const Identifier& name, const var &defaultReturnValue) const				{ return deviceTree.getProperty (name, defaultReturnValue); }
		UndoManager* getUndoManager() const																{ return (0); }
		ValueTree &getDeviceTree()																		{ return (deviceTree); }
		void valueTreePropertyChanged (ValueTree &/*treeWhosePropertyHasChanged*/, const Identifier &/*property*/){}
		void valueTreeChildrenChanged (ValueTree &/*treeWhoseChildHasChanged*/){}
		void valueTreeParentChanged (ValueTree &/*treeWhoseParentHasChanged*/){}
		void valueTreeChildAdded (ValueTree& /*parentTree*/, ValueTree& /*childWhichHasBeenAdded*/){}
		void valueTreeChildRemoved (ValueTree& /*parentTree*/, ValueTree& /*childWhichHasBeenRemoved*/, int){}
		void valueTreeChildOrderChanged (ValueTree& /*parentTreeWhoseChildrenHaveMoved*/, int, int){}

		void addDeviceListener (CtrlrMIDIDevice::Listener *l)											{ deviceListeners.add(l); }
		void removeDeviceListener (CtrlrMIDIDevice::Listener *l)										{ deviceListeners.remove(l); }

		void handlePartialSysexMessage (MidiInput* source, const uint8* messageData, int numBytesSoFar, double timestamp);
		void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message);
		void sendMidiBuffer (const MidiBuffer &buffer, double millisecondCounterToStartAt=0);
		void sendMidiMessage (const MidiMessage &message, double millisecondCounterToStartAt=0);

		MidiInput *getInputDevicePtr();

		virtual bool getType();
		virtual bool getState();
		virtual const String getName();
		virtual bool openDevice();
		virtual void closeDevice();

		static void wrapForLua(lua_State *L);
		JUCE_LEAK_DETECTOR(CtrlrMIDIDevice)

	protected:
        MemoryBlock dataCollector;
		CtrlrMIDIDeviceManager &owner;
		CriticalSection deviceLock;
		ValueTree deviceTree;
		MidiOutput *outJucePtr;
		MidiInput *inJucePtr;
		int deviceIndex;
        bool lastMessageWasSysex;
		double lastMessageSentTime;
		MidiBuffer throwBuffer;
		ListenerList	<CtrlrMIDIDevice::Listener,
							Array<CtrlrMIDIDevice::Listener*,CriticalSection>
						> deviceListeners;
		CtrlrMidiMessage midiMessageCollector;
};

#endif
