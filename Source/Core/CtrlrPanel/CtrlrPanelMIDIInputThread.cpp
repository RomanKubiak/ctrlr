#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrLog.h"
#include "CtrlrProcessor.h"
#include "CtrlrPanelMIDIInputThread.h"
#include "MIDI/CtrlrMIDILibrary/CtrlrMIDILibrary.h"

CtrlrPanelMIDIInputThread::CtrlrPanelMIDIInputThread(CtrlrPanel &_owner, const bool _inputFromController)
	:	owner(_owner),
		Thread("PANEL MIDI INPUT THREAD"),
		inputDevice(nullptr),
		inputComparator(nullptr),
		inputFromController(_inputFromController)
{
	inputComparator = new CtrlrMidiInputComparator (owner);
	junkBuffer.ensureSize(8192);
	hostInputBuffer.ensureSize(8192);
	deviceInputBuffer.ensureSize(8192);
}

CtrlrPanelMIDIInputThread::~CtrlrPanelMIDIInputThread()
{
	if (inputDevice)
	{
		inputDevice->removeDeviceListener(this);
	}

	inputDevice  = nullptr;
}

void CtrlrPanelMIDIInputThread::run()
{
	while (! threadShouldExit())
    {
		uint32 timeToWait = 500;

		{
			process();
		}

		wait ((int) timeToWait);
	}
	_WRN("CtrlrPanelMIDIInputThread::run stopping");
}

void CtrlrPanelMIDIInputThread::process()
{
	const ScopedWriteLock sl (lock);

	if (owner.getMidiOptionBool(panelMidiThruD2D))
	{
		owner.sendMidi (deviceInputBuffer);
	}

	if (inputComparator)
	{
		inputComparator->match(deviceInputBuffer);
	}

	if (owner.getMidiOptionBool(panelMidiInputFromHostCompare) && hostInputBuffer.getNumEvents() > 0)
	{
		if (inputComparator)
			inputComparator->match(hostInputBuffer);
	}

	if (owner.getMidiOptionBool(panelMidiThruD2H))
	{
		channelizeBuffer (deviceInputBuffer, junkBuffer, owner.getMidiChannel(panelMidiOutputChannelHost), owner.getMidiOptionBool(panelMidiThruD2HChannelize));
		owner.getOwner().getOwner()->addMidiToOutputQueue (deviceInputBuffer);
	}

	owner.getCtrlrMIDILibrary().processMidi (deviceInputBuffer);
	owner.getCtrlrMIDILibrary().processMidi (hostInputBuffer);

	hostInputBuffer.clear();
	deviceInputBuffer.clear();
}

int CtrlrPanelMIDIInputThread::getListenerInputMidiChannel()
{
	return (owner.getMidiChannel(panelMidiInputChannelDevice));
}

void CtrlrPanelMIDIInputThread::handlePartialMIDIFromDevice (const uint8* messageData, const int numBytesSoFar, const double timestamp)
{
	const ScopedWriteLock sl (lock);
}

void CtrlrPanelMIDIInputThread::handleMIDIFromDevice (const MidiMessage &message)
{
	const ScopedWriteLock sl (lock);

	if (owner.getMidiOptionBool(panelMidiRealtimeIgnore) && message.getRawDataSize() <= 1)
		return;

	if (isController())
	{
		owner.sendMidi( message );
	}
	else if (message.isNoteOnOrOff() || message.isMidiClock())
	{
		deviceInputBuffer.addEvent (message, deviceInputBuffer.getNumEvents()+1);
	}
	else
	{
		deviceInputBuffer.addEvent (message, deviceInputBuffer.getNumEvents()+2);
	}

	notify();
}

void CtrlrPanelMIDIInputThread::handleMIDIFromHost(MidiBuffer &buffer)
{
	{
		const ScopedWriteLock sl(lock);
		hostInputBuffer.addEvents (buffer, 0, buffer.getNumEvents(), 1);
	}

	notify();
}

void CtrlrPanelMIDIInputThread::closeInputDevice()
{
	if (inputDevice)
	{
		inputDevice->closeDevice();
	}
}

bool CtrlrPanelMIDIInputThread::openInputDevice (const String &inputDeviceName)
{
	const ScopedWriteLock sl(lock);

	inputDevice = owner.getOwner().getCtrlrMidiDeviceManager().getDeviceByName (inputDeviceName, CtrlrMidiDeviceManager::inputDevice, true);

	if (inputDevice != nullptr)
	{
		inputDevice->addDeviceListener (this);

		return (true);
	}

	return (false);
}

CtrlrMidiInputComparator &CtrlrPanelMIDIInputThread::getInputComparator()
{
	if (inputComparator == nullptr)
	{
		inputComparator = new CtrlrMidiInputComparator (owner);
	}

	return (*inputComparator);
}

void CtrlrPanelMIDIInputThread::panelEditModeChanged (const bool _panelEditMode)
{
	if (inputComparator)
	{
		inputComparator->panelEditModeChanged(_panelEditMode);
	}
}

void CtrlrPanelMIDIInputThread::midiChannelChaned(const CtrlrPanelMidiChannel channelThatChanged)
{
	if (channelThatChanged == panelMidiOutputChannelDevice)
	{
		if (inputComparator)
		{
			const ScopedWriteLock sl(lock);
			inputComparator->rehashComparator();
		}
	}
}

bool CtrlrPanelMIDIInputThread::isController()
{
	const ScopedReadLock sl(lock);

	return (inputFromController);
}
