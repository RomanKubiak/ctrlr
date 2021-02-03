#include "stdafx.h"
#include "stdafx_luabind.h"
#include "CtrlrUtilities.h"
#include "CtrlrMIDIDeviceManager.h"
#include "CtrlrMIDIDevice.h"
#include "CtrlrProcessor.h"
#include "CtrlrLog.h"

CtrlrMIDIDevice::CtrlrMIDIDevice(CtrlrMIDIDeviceManager &_owner, const int idx, const String name, const String identifier, const bool type)
	:	deviceTree(Ids::midiDev),
		owner(_owner),
		outJucePtr(nullptr),
		inJucePtr(nullptr),
		lastMessageSentTime(0)
{
	throwBuffer.ensureSize (8192);

	deviceTree.addListener (this);

	setProperty (Ids::midiDevState, STP);
	setProperty (Ids::name,  name);
	setProperty (Ids::midiDevId, identifier );
	setProperty (Ids::midiDevIndex, idx);
	setProperty (Ids::midiDevType,  type);

	owner.getManagerTree().addChild (deviceTree, -1, 0);
}

CtrlrMIDIDevice::~CtrlrMIDIDevice()
{
	deviceListeners.clear();
	owner.getManagerTree().removeChild (deviceTree, 0);
	closeDevice();
}

void CtrlrMIDIDevice::restoreState(const ValueTree &savedState)
{
	for (int i=0; i<savedState.getNumProperties(); i++)
	{
		deviceTree.setProperty (savedState.getPropertyName(i), savedState.getProperty(savedState.getPropertyName(i)), 0);
	}
}

bool CtrlrMIDIDevice::openDevice()
{
	if (getType() == outputDevice)
	{
		if (outJucePtr != nullptr)
		{
			return (true);
		}

		const ScopedLock sl(deviceLock);

		outJucePtr = MidiOutput::openDevice (getProperty(Ids::midiDevId).toString()).release();
		if (outJucePtr == NULL)
		{
			_ERR("CtrlrMIDIDevice::openDevice failed to open device \""+getName()+"\"");
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

		inJucePtr = MidiInput::openDevice (getProperty(Ids::midiDevId).toString(), this).release();

		if (inJucePtr == NULL)
		{
			_ERR("CtrlrMIDIDevice::openDevice failed to open device \""+getName()+"\"");
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

void CtrlrMIDIDevice::closeDevice()
{
	if (getType() == outputDevice)
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

void CtrlrMIDIDevice::handlePartialSysexMessage (MidiInput* /*source*/, const uint8* messageData, int numBytesSoFar, double timestamp)
{
	deviceListeners.call (&CtrlrMIDIDevice::Listener::handlePartialMIDIFromDevice, messageData, numBytesSoFar, timestamp);
}

void CtrlrMIDIDevice::handleIncomingMidiMessage (MidiInput* /*source*/, const MidiMessage& message)
{
	_MIN(getProperty(Ids::name), message, -1);

#ifdef JUCE_LINUX
    uint8 *ptr = (uint8 *)message.getRawData();

    if (!message.isSysEx() && *(ptr + (message.getRawDataSize() - 1)) == 0xf7)
    {
        dataCollector.append (ptr, message.getRawDataSize());

        deviceListeners.call (&CtrlrMIDIDevice::Listener::handleMIDIFromDevice, MidiMessage (dataCollector.getData(), dataCollector.getSize()));

        return;
    }
#endif

	if (message.isSysEx())
	{
#ifdef JUCE_LINUX


        if (*(ptr + (message.getRawDataSize() - 1)) == 0xf7)
        {
            deviceListeners.call (&CtrlrMIDIDevice::Listener::handleMIDIFromDevice, message);
        }
        else
        {
            dataCollector = MemoryBlock (ptr, message.getRawDataSize());
        }
#else
		deviceListeners.call (&CtrlrMIDIDevice::Listener::handleMIDIFromDevice, message);
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

bool CtrlrMIDIDevice::getType()
{
	return ((bool)getProperty(Ids::midiDevType));
}

bool CtrlrMIDIDevice::getState()
{
	return (getProperty(Ids::midiDevState));
}

const String CtrlrMIDIDevice::getName()
{
	return (getProperty(Ids::name));
}

void CtrlrMIDIDevice::sendMidiBuffer (const MidiBuffer &buffer, double millisecondCounterToStartAt)
{
	if (outJucePtr != nullptr)
	{
		{
			const ScopedLock sl(deviceLock);
			if (lastMessageSentTime == 0 || (lastMessageSentTime + millisecondCounterToStartAt) < Time::getMillisecondCounter())
			{
				lastMessageSentTime = Time::getMillisecondCounter();
			}

			outJucePtr->sendBlockOfMessages (buffer, lastMessageSentTime + millisecondCounterToStartAt, SAMPLERATE);

			lastMessageSentTime = lastMessageSentTime + millisecondCounterToStartAt;
		}
		_MOUT(getProperty(Ids::name).toString() + "[JUCE]", buffer, -1);
	}
}

void CtrlrMIDIDevice::sendMidiMessage (const MidiMessage &message, double millisecondCounterToStartAt)
{
	if (outJucePtr != nullptr)
	{
		{
			const ScopedLock sl(deviceLock);

			if (lastMessageSentTime == 0 || (lastMessageSentTime + millisecondCounterToStartAt) < Time::getMillisecondCounter())
			{
				lastMessageSentTime = Time::getMillisecondCounter();
			}

			throwBuffer.clear();
			throwBuffer.addEvent (message, 1);
			outJucePtr->sendBlockOfMessages (throwBuffer, lastMessageSentTime + millisecondCounterToStartAt, SAMPLERATE);

			lastMessageSentTime = lastMessageSentTime + millisecondCounterToStartAt;
		}

		_MOUT(getProperty(Ids::name).toString() + "[JUCE]", message, -1);
	}
}

MidiInput *CtrlrMIDIDevice::getInputDevicePtr()
{
	return (inJucePtr);
}

void CtrlrMIDIDevice::wrapForLua(lua_State *L)
{
		using namespace luabind;

	module(L)
    [
		class_<CtrlrMIDIDevice>("CtrlrMIDIDevice")
			.def("openDevice", &CtrlrMIDIDevice::openDevice)
			.def("closeDevice", &CtrlrMIDIDevice::closeDevice)
			.def("sendMidiMessage", &CtrlrMIDIDevice::sendMidiMessage)
			.def("sendMidiBuffer", &CtrlrMIDIDevice::sendMidiBuffer)
			.def("getName", &CtrlrMIDIDevice::getName)
			.def("getState", &CtrlrMIDIDevice::getState)
			.def("getType", &CtrlrMIDIDevice::getType)
	];
}
