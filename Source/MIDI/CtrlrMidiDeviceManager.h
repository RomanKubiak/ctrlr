#ifndef __CTRLR_MIDI_DEVICE_MANAGER__
#define __CTRLR_MIDI_DEVICE_MANAGER__

#include "CtrlrMacros.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrIDs.h"
#include "CtrlrMidiDevice.h"

class CtrlrManager;

#define RUN		true
#define STP		false

class CtrlrMidiDeviceManager
{
	public:
		CtrlrMidiDeviceManager(CtrlrManager &_ctrlrManager);
		~CtrlrMidiDeviceManager();
		void refreshDevices();

		enum DeviceType
		{
			outputDevice,
			inputDevice,
			controllerDevice,
            hostInputDevice,
            hostOutputDevice
		};

		enum DeviceState
		{
			closed,
			opened,
			error
		};

		const String getDeviceName(const int idx, const DeviceType type=inputDevice);
		const int getNumDevices(const DeviceType type=inputDevice);
		const bool isDeviceOpened(const int idx, const DeviceType type=inputDevice);
		const bool toggleDevice (const int idx, const DeviceType type=inputDevice, const bool state=STP);
		CtrlrMidiDevice *getDeviceByIndex(const int idx, const DeviceType type=inputDevice);
		CtrlrMidiDevice *getDeviceByName(const String name, const DeviceType type=inputDevice, const bool openIfClosed=false);
		const StringArray getManagedDevices(const DeviceType type=inputDevice);

		void restoreState (const ValueTree &savedState);
		void setProperty (const Identifier& name, const var &newValue)									{ managerTree.setProperty (name, newValue, 0); }
		const var &getProperty (const Identifier& name) const											{ return managerTree.getProperty (name); }
		const var getProperty (const Identifier& name, const var &defaultReturnValue) const				{ return managerTree.getProperty (name, defaultReturnValue); }
		UndoManager* getUndoManager() const																{ return (0); }
		ValueTree &getManagerTree()																		{ return (managerTree); }
		void removeListenerFromAllDevices (CtrlrMidiDevice::Listener *l);
		void processBlock (MidiBuffer& midiMessages);
		void addProcessingListener(CtrlrMidiDevice::Listener *l)										{ processingListeners.add(l); }
		void removeProcessingListener(CtrlrMidiDevice::Listener *l)										{ processingListeners.remove(l); }

		void reloadComboContents (ComboBox &comboToUpdate, const DeviceType type=inputDevice);


		JUCE_LEAK_DETECTOR(CtrlrMidiDeviceManager)

	private:
		ListenerList <CtrlrMidiDevice::Listener,
							Array<CtrlrMidiDevice::Listener*,CriticalSection>
						> processingListeners;


		OwnedArray <CtrlrMidiDevice,CriticalSection> inDevs;
		OwnedArray <CtrlrMidiDevice,CriticalSection> outDevs;
		ValueTree managerTree;
		CtrlrManager &owner;
};

#endif
