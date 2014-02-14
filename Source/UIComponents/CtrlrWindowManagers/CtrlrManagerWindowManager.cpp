#include "stdafx.h"
#include "CtrlrUtilities.h"
#include "CtrlrManagerWindowManager.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrChildWindow.h"
#include "CtrlrDialogWindow.h"
#include "CtrlrMIDI/CtrlrMIDIMon.h"
#include "CtrlrLogViewer.h"
#include "CtrlrMIDI/CtrlrMIDICalculator.h"

CtrlrManagerWindowManager::CtrlrManagerWindowManager(CtrlrManager &_owner) : owner(_owner), managerTree(Ids::uiWindowManager)
{
}

CtrlrManagerWindowManager::~CtrlrManagerWindowManager()
{
}

CtrlrManager &CtrlrManagerWindowManager::getOwner()
{
	return (owner);
}

ValueTree &CtrlrManagerWindowManager::getManagerTree()
{
	return (managerTree);
}

void CtrlrManagerWindowManager::showModalDialog(const String &title, Component *content, const bool resizable, Component *parent)
{
	content->setSize (content->getWidth() ? content->getWidth() : 400, content->getHeight() ? content->getHeight() : 500);
	CtrlrDialogWindow::showModalDialog (title, content, resizable, parent);
}

void CtrlrManagerWindowManager::restoreState (const ValueTree &savedState)
{
	restoreProperties (savedState, managerTree, nullptr);
	for (int i=0; i<savedState.getNumChildren(); i++)
	{
		managerTree.addChild (savedState.getChild(i).createCopy(), -1, nullptr);
	}
}

void CtrlrManagerWindowManager::show (const CtrlrManagerWindowManager::WindowType window)
{
	CtrlrChildWindow *w = getWindow(window);
	if (w)
	{
		w->setVisible (true);
	}
}

void CtrlrManagerWindowManager::hide (const CtrlrManagerWindowManager::WindowType window)
{
	CtrlrChildWindow *w = getWindow(window);
	if (w)
	{
		windows.removeObject (w);
	}
}

void CtrlrManagerWindowManager::toggle(const CtrlrManagerWindowManager::WindowType window, const bool makeVisible)
{
	CtrlrChildWindow *w = getWindow(window);
	if (w)
	{
		if (makeVisible)
		{
			w->setVisible (true);
			w->toFront(true);
		}
	}
}

Component *CtrlrManagerWindowManager::getContent(const CtrlrManagerWindowManager::WindowType window)
{
	CtrlrChildWindow *w = getWindow(window);
	if (w)
	{
		return (w->getContent());
	}
	return (0);
}

const bool CtrlrManagerWindowManager::isCreated(const CtrlrManagerWindowManager::WindowType window)
{
	for (int i=0; i<windows.size(); i++)
	{
		if (windows[i]->getType() == window)
			return (true);
	}
	return (false);
}

CtrlrChildWindow *CtrlrManagerWindowManager::getWindow(const CtrlrManagerWindowManager::WindowType window, const bool createIfNeeded)
{
	if (!isCreated(window))
	{
		if (createIfNeeded)
			create (window);
	}

	for (int i=0; i<windows.size(); i++)
	{
		if (windows[i]->getType() == window)
			return (windows[i]);
	}

	return (0);
}

const String CtrlrManagerWindowManager::getWindowName(const CtrlrManagerWindowManager::WindowType window)
{
	switch (window)
	{
		case Repository:
			return ("Repository");
		case MidiMonWindow:
			return ("MidiMonWindow");
		case LogViewer:
			return ("LogViewer");
		case MIDICalculator:
			return ("MIDICalculator");
		default:
			return ("Unknown");
	}
}

const CtrlrManagerWindowManager::WindowType CtrlrManagerWindowManager::getWindowType(const String &windowName)
{
	if (windowName == "Repository")
		return (Repository);
	if (windowName == "MidiMonWindow")
		return (MidiMonWindow);
	if (windowName == "LogViewer")
		return (LogViewer);
	if (windowName == "MIDICalculator")
		return (MIDICalculator);
	return (MidiMonWindow);
}

void CtrlrManagerWindowManager::windowClosedButtonPressed(CtrlrChildWindow *windowThatChanged)
{
	windows.removeObject (windowThatChanged);
}

void CtrlrManagerWindowManager::windowChanged(CtrlrChildWindow *windowThatChanged)
{
	CtrlrChildWindowContent		*c	= windowThatChanged->getContent();

	if (c == 0)
		return;

	CtrlrManagerWindowManager::WindowType window = (CtrlrManagerWindowManager::WindowType) c->getType();

	if (managerTree.getChildWithProperty (Ids::uiChildWindowName, getWindowName(window)).isValid())
	{
		managerTree.getChildWithProperty (Ids::uiChildWindowName, getWindowName(window)).setProperty (Ids::uiChildWindowState, getWindow(window)->getWindowStateAsString(), 0);
	}
	else
	{
		ValueTree windowTree(Ids::uiChildWindow);

		windowTree.setProperty (Ids::uiChildWindowName, getWindowName(window), 0);
		windowTree.setProperty (Ids::uiChildWindowState, getWindow(window)->getWindowStateAsString(), 0);
		managerTree.addChild(windowTree,-1,0);
		windowTree.addChild (c->saveState(), -1, 0);
	}
}

CtrlrChildWindow *CtrlrManagerWindowManager::createWindow(const CtrlrManagerWindowManager::WindowType window)
{
	if (isCreated(window))
	{
		return (nullptr);
	}

	CtrlrChildWindow *w = new CtrlrChildWindow (*this);

	switch (window)
	{
		case CtrlrManagerWindowManager::MidiMonWindow:
			w->setContent (new CtrlrMIDIMon (owner));
			break;

		case CtrlrManagerWindowManager::LogViewer:
			w->setContent (new CtrlrLogViewer (owner));
			break;

		case CtrlrManagerWindowManager::MIDICalculator:
			w->setContent (new CtrlrMIDICalculator (owner));
			break;

        case CtrlrManagerWindowManager::Repository:
            break;
	}

	w->setName("Ctrlr/" + w->getContent()->getContentName());
	windows.add (w);

	return (w);
}

void CtrlrManagerWindowManager::create(const CtrlrManagerWindowManager::WindowType window, const String &lastWindowState)
{
	CtrlrChildWindow *w			= createWindow(window);
	String windowState;

	if (w == nullptr)
	{
		return;
	}

	if (lastWindowState.isEmpty())
	{
		if (managerTree.getChildWithProperty (Ids::uiChildWindowName, getWindowName(window)).isValid())
		{
			windowState = managerTree.getChildWithProperty (Ids::uiChildWindowName, getWindowName(window)).getProperty (Ids::uiChildWindowState);
		}
	}
	else
	{
		windowState = lastWindowState;
	}

	if (windowState != String::empty)
	{
		w->restoreWindowStateFromString(windowState);
	}
	else
	{
		w->centreWithSize(w->getWidth(), w->getHeight());
	}

	if (managerTree.getChildWithProperty (Ids::uiChildWindowName, getWindowName(window)).isValid())
	{
		if (w->getContent())
		{
			w->getContent()->restoreState (managerTree.getChildWithProperty (Ids::uiChildWindowName, getWindowName(window)).getChildWithName(Ids::uiChildWindowContentState));
		}
	}
}
