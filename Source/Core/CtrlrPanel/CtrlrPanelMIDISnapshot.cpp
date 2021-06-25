#include "stdafx.h"
#include "CtrlrComponents/CtrlrComponent.h"
#include "CtrlrLog.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrPanelMIDISnapshot.h"
#include "CtrlrLuaManager.h"

CtrlrPanelMIDISnapshot::CtrlrPanelMIDISnapshot(CtrlrPanel &_owner)
	:	owner(_owner),
		Thread("MIDI Snapshot"),
		snapshotDelay(50),
		showDialog(false),
		alertWindow(nullptr),
		wasCancelledByUser(false),
		luaPanelMidiSnapshotPreCbk(nullptr),
		luaPanelMidiSnapshotPostCbk(nullptr)
{
	buffer.ensureSize(8192);
}

CtrlrPanelMIDISnapshot::~CtrlrPanelMIDISnapshot()
{
    if (alertWindow)
        deleteAndZero (alertWindow);

    stopThread (500);
}

void CtrlrPanelMIDISnapshot::sendSnapshot()
{
	triggerAsyncUpdate();
}

void CtrlrPanelMIDISnapshot::handleAsyncUpdate()
{
	gatherSnapshotData();
	startThread();

	startTimer (100);
    if (alertWindow)
    {
        const ScopedLock sl (messageLock);
        alertWindow->setMessage (message);
        alertWindow->enterModalState();
    }
}

void CtrlrPanelMIDISnapshot::gatherSnapshotData()
{
	buffer.clear();

	for (int i=0; i<owner.getModulators().size(); i++)
	{
		CtrlrModulator *m = owner.getModulators()[i];
		if (m->getMidiMessagePtr())
		{
			if (m->getComponent())
			{
				if ((int)m->getComponent()->getProperty(Ids::componentRadioGroupId) > 0)
				{
					if (m->getComponent()->getToggleState() == false)
						continue;
					else if (!(bool)m->getProperty(Ids::modulatorExcludeFromSnapshot))
						addCtrlrMidiMessageToBuffer (buffer, m->getMidiMessage());
				}
				else if (!(bool)m->getProperty(Ids::modulatorExcludeFromSnapshot))
				{
					addCtrlrMidiMessageToBuffer (buffer, m->getMidiMessage());
				}
			}
		}
	}

	showDialog = owner.getProperty(Ids::panelMidiSnapshotShowProgress);

	if (showDialog)
    {
        if (alertWindow == nullptr)
        {
            alertWindow = LookAndFeel::getDefaultLookAndFeel().createAlertWindow ("MIDI Snapshot", String(), "Stop", String(), String(), AlertWindow::NoIcon, 1, nullptr);
            alertWindow->setEscapeKeyCancels (false);
            alertWindow->addProgressBarComponent (progress);
        }
    }
    else
    {
        alertWindow = nullptr;
    }

    if (luaPanelMidiSnapshotPreCbk && !luaPanelMidiSnapshotPreCbk.wasObjectDeleted())
	{
		if (luaPanelMidiSnapshotPreCbk->isCallable())
		{
			owner.getCtrlrLuaManager().getMethodManager().call (luaPanelMidiSnapshotPreCbk, &buffer);
		}
	}
}

void CtrlrPanelMIDISnapshot::setStatusMessage (const String& newStatusMessage)
{
    const ScopedLock sl (messageLock);
    message = newStatusMessage;
}

void CtrlrPanelMIDISnapshot::run()
{
	MidiBuffer::Iterator i(buffer);
	MidiMessage m; int t; int k=0;
	while (!threadShouldExit() && i.getNextEvent(m,t))
	{
	    progress = k / (double) buffer.getNumEvents();
		owner.sendMidi(m);
		k++;
		wait(snapshotDelay);
	}
	while (!threadShouldExit()) {
		wait(-1);
	}
}

void CtrlrPanelMIDISnapshot::setDelay(const int _snapshotDelay)
{
	snapshotDelay = _snapshotDelay;
}

void CtrlrPanelMIDISnapshot::timerCallback()
{
    bool threadStillRunning = isThreadRunning();

    if (! threadStillRunning)
    {
        stopTimer();

        if (alertWindow)
        {
            if (alertWindow->isCurrentlyModal())
                alertWindow->exitModalState (1);

            alertWindow->setVisible (false);
        }

        wasCancelledByUser = threadStillRunning;

        if (luaPanelMidiSnapshotPostCbk && !luaPanelMidiSnapshotPostCbk.wasObjectDeleted())
        {
            if (luaPanelMidiSnapshotPostCbk->isCallable())
            {
                owner.getCtrlrLuaManager().getMethodManager().call (luaPanelMidiSnapshotPostCbk, &buffer);
            }
        }

        return; // (this may be deleted now)
    }

    if (alertWindow)
    {
        const ScopedLock sl (messageLock);
        alertWindow->setMessage (message);
    }
}

void CtrlrPanelMIDISnapshot::setPreLuaCallback(CtrlrLuaMethod *method)
{
    luaPanelMidiSnapshotPreCbk = method;
}

void CtrlrPanelMIDISnapshot::setPostLuaCallback(CtrlrLuaMethod *method)
{
    luaPanelMidiSnapshotPostCbk = method;
}
