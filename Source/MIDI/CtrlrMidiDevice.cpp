#include "stdafx.h"
#include "CtrlrUtilities.h"
#include "CtrlrMidiDeviceManager.h"
#include "CtrlrMidiDevice.h"
#include "CtrlrProcessor.h"
#include "CtrlrLog.h"

CtrlrMidiDevice::CtrlrMidiDevice(CtrlrMidiDeviceManager &_owner, const int idx, const String name, const bool type)
	:	deviceTree(Ids::midiDev),
		owner(_owner),
		outJucePtr(nullptr),
		inJucePtr(nullptr)
{
	throwBuffer.ensureSize (8192);

	deviceTree.addListener (this);

	setProperty (Ids::midiDevState, STP);
	setProperty (Ids::name,  name);
	setProperty (Ids::midiDevIndex, idx);
	setProperty (Ids::midiDevType,  type);

	owner.getManagerTree().addChild (deviceTree, -1, 0);
}

CtrlrMidiDevice::~CtrlrMidiDevice()
{
	deviceListeners.clear();
	owner.getManagerTree().removeChild (deviceTree, 0);
	closeDevice();
}

void CtrlrMidiDevice::restoreState(const ValueTree &savedState)
{
	for (int i=0; i<savedState.getNumProperties(); i++)
	{
		deviceTree.setProperty (savedState.getPropertyName(i), savedState.getProperty(savedState.getPropertyName(i)), 0);
	}
}

const bool CtrlrMidiDevice::openDevice()
{
	if (getType() == CtrlrMidiDeviceManager::outputDevice)
	{
		if (outJucePtr != nullptr)
		{
			return (true);
		}

		const ScopedLock sl(deviceLock);

		outJucePtr = MidiOutput::openDevice (getProperty(Ids::midiDevIndex));
		if (outJucePtr == NULL)
		{
			_ERR("CtrlrMidiDevice::openDevice failed to open device \""+getName()+"\"");
			setProperty (Ids::midiDevState, false);
			return (false);
		}
		else
		{
			outJucePtr->startBackgroundThread();
			setProperty (Ids::midiDevState, true);
			return (true);
		}
	}
	else
	{
		if (inJucePtr != nullptr)
		{
			return (true);
		}

		inJucePtr = MidiInput::openDevice (getProperty(Ids::midiDevIndex), this);

		if (inJucePtr == NULL)
		{
			_ERR("CtrlrMidiDevice::openDevice failed to open device \""+getName()+"\"");
			setProperty (Ids::midiDevState, false);
			return (false);
		}
		else
		{
			inJucePtr->start();
			setProperty (Ids::midiDevState, true);
			return (true);
		}
	}
}

void CtrlrMidiDevice::closeDevice()
{
	if (getType() == CtrlrMidiDeviceManager::outputDevice)
	{

		if (outJucePtr != nullptr)
		{
			const ScopedLock sl(deviceLock);
			outJucePtr->stopBackgroundThread();
			deleteAndZero (outJucePtr);
		}
	}
	else
	{
		if (inJucePtr != nullptr)
		{
			const ScopedLock sl(deviceLock);
			inJucePtr->stop();
			deleteAndZero (inJucePtr);
		}
	}

	deviceListeners.clear();
	setProperty (Ids::midiDevState, false);
}

void CtrlrMidiDevice::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
}

void CtrlrMidiDevice::handlePartialSysexMessage (MidiInput* source, const uint8* messageData, int numBytesSoFar, double timestamp)
{
	deviceListeners.call (&CtrlrMidiDevice::Listener::handlePartialMIDIFromDevice, messageData, numBytesSoFar, timestamp);
}

void CtrlrMidiDevice::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message)
{
	_MIN(getProperty(Ids::name), message);

#ifdef JUCE_LINUX
    uint8 *ptr = message.getRawData();

    if (!message.isSysEx() && *(ptr + (message.getRawDataSize() - 1)) == 0xf7)
    {
        dataCollector.append (ptr, message.getRawDataSize());

        deviceListeners.call (&CtrlrMidiDevice::Listener::handleMIDIFromDevice, MidiMessage (dataCollector.getData(), dataCollector.getSize()));

        return;
    }
#endif

	if (message.isSysEx())
	{
#ifdef JUCE_LINUX


        if (*(ptr + (message.getRawDataSize() - 1)) == 0xf7)
        {
            deviceListeners.call (&CtrlrMidiDevice::Listener::handleMIDIFromDevice, message);
        }
        else
        {
            dataCollector = MemoryBlock (ptr, message.getRawDataSize());
        }
#else
		deviceListeners.call (&CtrlrMidiDevice::Listener::handleMIDIFromDevice, message);
#endif
	}
	else
	{
        lastMessageWasSysex = false;

		for (int i=0; i<deviceListeners.size(); i++)
		{
			const int ch = deviceListeners.getListeners() [i]->getListenerInputMidiChannel();

			if (ch == message.getChannel() || ch == 0 || message.getChannel() == 0)
			{
				deviceListeners.getListeners() [i]->handleMIDIFromDevice (message);
			}
		}
	}
}

const bool CtrlrMidiDevice::getType()
{
	return ((bool)getProperty(Ids::midiDevType));
}

const bool CtrlrMidiDevice::getState()
{
	return (getProperty(Ids::midiDevState));
}

const String CtrlrMidiDevice::getName()
{
	return (getProperty(Ids::name));
}

void CtrlrMidiDevice::sendMidiBuffer (const MidiBuffer &buffer, double millisecondCounterToStartAt)
{
	if (outJucePtr != nullptr)
	{
		{
			const ScopedLock sl(deviceLock);
			outJucePtr->sendBlockOfMessages (buffer, Time::getMillisecondCounter() + millisecondCounterToStartAt + 1, SAMPLERATE);
		}
		_MOUT(getProperty(Ids::name).toString() + "[JUCE]", buffer);
	}
}

void CtrlrMidiDevice::sendMidiMessage (const MidiMessage &message, double millisecondCounterToStartAt)
{
	if (outJucePtr != nullptr)
	{
		{
			const ScopedLock sl(deviceLock);
			throwBuffer.clear();
			throwBuffer.addEvent (message, 1);
			outJucePtr->sendBlockOfMessages (throwBuffer, Time::getMillisecondCounter() + millisecondCounterToStartAt + 1, SAMPLERATE);
		}

		_MOUT(getProperty(Ids::name).toString() + "[JUCE]", message);
	}
}

MidiInput *CtrlrMidiDevice::getInputDevicePtr()
{
	return (inJucePtr);
}
