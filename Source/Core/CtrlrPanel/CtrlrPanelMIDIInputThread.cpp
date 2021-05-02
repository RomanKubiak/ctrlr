#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrLog.h"
#include "CtrlrProcessor.h"
#include "CtrlrPanelMIDIInputThread.h"

CtrlrPanelMIDIInputThread::CtrlrPanelMIDIInputThread(CtrlrPanel &_owner, const CtrlrMIDIDeviceType _source)
	:	owner(_owner),
		Thread("PANEL MIDI INPUT THREAD"),
		inputDevicePtr(nullptr),
		inputComparator(nullptr),
		source(_source)
{
	inputComparator             = new CtrlrMidiInputComparator (owner, source);
	junkBuffer.ensureSize(8192);
	hostInputBuffer.ensureSize(8192);
	deviceInputBuffer.ensureSize(8192);
}

CtrlrPanelMIDIInputThread::~CtrlrPanelMIDIInputThread()
{
	if (inputDevicePtr)
	{
		inputDevicePtr->removeDeviceListener(this);
	}

	inputDevicePtr  = nullptr;
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
	_TXT("CtrlrPanelMIDIInputThread::run stopping");
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
		owner.getCtrlrManagerOwner().getProcessorOwner()->addMidiToOutputQueue (deviceInputBuffer);
	}

	hostInputBuffer.clear();
	deviceInputBuffer.clear();
	devicePartialBuffer.clear();
}

int CtrlrPanelMIDIInputThread::getListenerInputMidiChannel()
{
	return (owner.getMidiChannel(panelMidiInputChannelDevice));
}

void CtrlrPanelMIDIInputThread::handlePartialMIDIFromDevice (const uint8* messageData, const int numBytesSoFar, const double timestamp)
{
	const ScopedWriteLock sl (lock);

	devicePartialBuffer.add (MemoryBlock (messageData, numBytesSoFar));
}

void CtrlrPanelMIDIInputThread::handleMIDIFromDevice (const MidiMessage &message)
{
	const ScopedWriteLock sl (lock);

	if (owner.getMidiOptionBool(panelMidiRealtimeIgnore) && message.getRawDataSize() <= 1)
		return;

	if (message.isNoteOnOrOff() || message.isMidiClock())
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
		/* last event time is in samples, not event numbers you dumbass */
		hostInputBuffer.addEvents (buffer, 0, buffer.getLastEventTime() + 1, 1);
	}

	notify();
}

void CtrlrPanelMIDIInputThread::closeInputDevice()
{
	if (inputDevicePtr)
	{
		inputDevicePtr->closeDevice();
	}
}

bool CtrlrPanelMIDIInputThread::openInputDevice (const String &inputDeviceName)
{
	const ScopedWriteLock sl(lock);

	inputDevicePtr = owner.getCtrlrManagerOwner().getCtrlrMidiDeviceManager().getDeviceByName (inputDeviceName, inputDevice, true);

	if (inputDevicePtr != nullptr)
	{
		inputDevicePtr->addDeviceListener (this);

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
