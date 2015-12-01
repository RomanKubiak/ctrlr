#ifndef CTRLR_MIDI_DEVICE_MANAGER
#define CTRLR_MIDI_DEVICE_MANAGER

#include "CtrlrMacros.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrIDs.h"
#include "CtrlrMIDIDevice.h"

class CtrlrManager;

#define RUN		true
#define STP		false

class CtrlrMIDIDeviceManager
{
	public:
		CtrlrMIDIDeviceManager(CtrlrManager &_ctrlrManager);
		~CtrlrMIDIDeviceManager();
		void refreshDevices();

		enum DeviceState
		{
			closed,
			opened,
			error
		};

		const String getDeviceName(const int idx, const CtrlrMIDIDeviceType type = inputDevice);
		int getNumDevices(const CtrlrMIDIDeviceType type = inputDevice);
		bool isDeviceOpened(const int idx, const CtrlrMIDIDeviceType type = inputDevice);
		bool toggleDevice (const int idx, const CtrlrMIDIDeviceType type = inputDevice, const bool state=STP);
		CtrlrMIDIDevice *getDeviceByIndex(const int idx, const CtrlrMIDIDeviceType type = inputDevice);
		CtrlrMIDIDevice *getDeviceByName(const String name, const CtrlrMIDIDeviceType type = inputDevice, const bool openIfClosed=false);
		const StringArray getManagedDevices(const CtrlrMIDIDeviceType type = inputDevice);

		void restoreState (const ValueTree &savedState);
		void setProperty (const Identifier& name, const var &newValue)									{ managerTree.setProperty (name, newValue, 0); }
		const var &getProperty (const Identifier& name) const											{ return managerTree.getProperty (name); }
		const var getProperty (const Identifier& name, const var &defaultReturnValue) const				{ return managerTree.getProperty (name, defaultReturnValue); }
		UndoManager* getUndoManager() const																{ return (0); }
		ValueTree &getManagerTree()																		{ return (managerTree); }
		void removeListenerFromAllDevices (CtrlrMIDIDevice::Listener *l);
		void processBlock (MidiBuffer& midiMessages);
		void addProcessingListener(CtrlrMIDIDevice::Listener *l)										{ processingListeners.add(l); }
		void removeProcessingListener(CtrlrMIDIDevice::Listener *l)										{ processingListeners.remove(l); }

		void reloadComboContents (ComboBox &comboToUpdate, const CtrlrMIDIDeviceType type = inputDevice, CtrlrPanel *panel = nullptr);

		static void wrapForLua(lua_State *L);

		JUCE_LEAK_DETECTOR(CtrlrMIDIDeviceManager)

	private:
		ListenerList <CtrlrMIDIDevice::Listener,
							Array<CtrlrMIDIDevice::Listener*,CriticalSection>
						> processingListeners;


		OwnedArray <CtrlrMIDIDevice,CriticalSection> inDevs;
		OwnedArray <CtrlrMIDIDevice,CriticalSection> outDevs;
		ValueTree managerTree;
		CtrlrManager &owner;
};

#endif
