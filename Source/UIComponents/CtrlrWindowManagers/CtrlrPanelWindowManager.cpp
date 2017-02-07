#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrPanelWindowManager.h"
#include "CtrlrIDs.h"
#include "CtrlrLog.h"
#include "CtrlrPanel/CtrlrPanelModulatorList.h"
#include "CtrlrPanel/CtrlrPanelLayerList.h"
#include "CtrlrLua/CtrlrLuaConsole.h"
#include "CtrlrLua/MethodEditor/CtrlrLuaMethodEditor.h"
#include "CtrlrMIDI/CtrlrMIDILibraryEditor.h"
#include "CtrlrMIDI/CtrlrMIDIBufferEditor.h"
#include "CtrlrMIDI/CtrlrMIDISettingsDialog.h"
#include "CtrlrUtilities.h"

CtrlrPanelWindowManager::CtrlrPanelWindowManager(CtrlrPanel &_owner)
	: owner(_owner), managerTree(Ids::uiWindowManager)
{
	owner.getObjectTree().addChild (managerTree, -1, nullptr);
}

CtrlrPanelWindowManager::~CtrlrPanelWindowManager()
{
	windows.clear(true);
}

CtrlrPanel &CtrlrPanelWindowManager::getOwner()
{
	return (owner);
}

void CtrlrPanelWindowManager::restoreState (const ValueTree &savedState)
{
	restoreProperties (savedState, managerTree, nullptr);
	for (int i=0; i<savedState.getNumChildren(); i++)
	{
		managerTree.addChild (savedState.getChild(i).createCopy(), -1, nullptr);
	}
}

void CtrlrPanelWindowManager::windowClosedButtonPressed(CtrlrChildWindow *windowThatChanged)
{
	_DBG("CtrlrPanelWindowManager::windowClosedButtonPressed");
	windowChanged(windowThatChanged);
	windows.removeObject (windowThatChanged);
}

void CtrlrPanelWindowManager::show (const CtrlrPanelWindowManager::WindowType window)
{
	CtrlrChildWindow *w = getWindow(window);
	if (w)
	{
		w->setVisible (true);
	}
}

void CtrlrPanelWindowManager::toggle(const CtrlrPanelWindowManager::WindowType window, const bool makeVisible)
{
	CtrlrChildWindow *w = getWindow(window);
	if (w)
	{
		if (w->isVisible () && !makeVisible)
		{
			windows.removeObject (w);
		}
		else
		{
			w->setVisible (true);
			w->toFront(true);
		}
	}
}

Component *CtrlrPanelWindowManager::getContent(const CtrlrPanelWindowManager::WindowType window)
{
	CtrlrChildWindow *w = getWindow(window);
	if (w)
	{
		return (w->getContent());
	}
	return (0);
}

bool CtrlrPanelWindowManager::isCreated(const CtrlrPanelWindowManager::WindowType window)
{
	for (int i=0; i<windows.size(); i++)
	{
		if (windows[i]->getType() == window)
			return (true);
	}
	return (false);
}

CtrlrChildWindow *CtrlrPanelWindowManager::getWindow(const CtrlrPanelWindowManager::WindowType window, const bool createIfNeeded)
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

const String CtrlrPanelWindowManager::getWindowName(const CtrlrPanelWindowManager::WindowType window)
{
	switch (window)
	{
		case LuaConsole:
			return ("LuaConsole");
		case LuaMethodEditor:
			return ("LuaMethodEditor");
		case ModulatorList:
			return ("ModulatorList");
		case LayerEditor:
			return ("LayerEditor");
		case MIDILibrary:
			return ("MIDILibrary");
		case BufferEditor:
			return ("BufferEditor");
		case MIDISettings:
			return ("MIDISettings");
		default:
			return ("LuaConsole");
	}
}

CtrlrPanelWindowManager::WindowType CtrlrPanelWindowManager::getWindowType(const String &windowName)
{
	if (windowName == "LuaConsole")
		return (LuaConsole);
	if (windowName == "LuaMethodEditor")
		return (LuaMethodEditor);
	if (windowName == "ModulatorList")
		return (ModulatorList);
	if (windowName == "LayerEditor")
		return (LayerEditor);
	if (windowName == "MIDILibrary")
		return (MIDILibrary);
	if (windowName == "BufferEditor")
		return (BufferEditor);
	if (windowName == "MIDISettings")
		return (MIDISettings);
	return (LuaConsole);
}

CtrlrChildWindow *CtrlrPanelWindowManager::createWindow(const CtrlrPanelWindowManager::WindowType window)
{
	if (isCreated(window))
	{
		return (nullptr);
	}

	CtrlrChildWindow *w = new CtrlrChildWindow (*this);

	switch (window)
	{
		case CtrlrPanelWindowManager::LuaConsole:
			w->setContent (new CtrlrLuaConsole (owner));
			break;

		case CtrlrPanelWindowManager::LuaMethodEditor:
			w->setContent (new CtrlrLuaMethodEditor (owner));
			break;

		case CtrlrPanelWindowManager::ModulatorList:
			w->setContent (new CtrlrPanelModulatorList(owner));
			break;

		case CtrlrPanelWindowManager::LayerEditor:
			w->setContent (new CtrlrPanelLayerList(owner));
			break;

		case CtrlrPanelWindowManager::MIDILibrary:
			w->setContent (new CtrlrMIDILibraryEditor(owner));
			break;

		case CtrlrPanelWindowManager::BufferEditor:
			w->setContent (new CtrlrMIDIBufferEditor(owner));
			break;

		case CtrlrPanelWindowManager::MIDISettings:
			w->setContent (new CtrlrMIDISettingsDialog(owner));
	}

	w->setName(owner.getProperty (Ids::name).toString() + "/" + w->getContent()->getContentName());
	windows.add (w);

	return (w);
}

void CtrlrPanelWindowManager::create(const CtrlrPanelWindowManager::WindowType window, const String &lastWindowState)
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
			/* restore the stored state in our global tree */
			w->getContent()->restoreState (managerTree.getChildWithProperty (Ids::uiChildWindowName, getWindowName(window)).getChildWithName(Ids::uiChildWindowContentState));

			/* remove the CONTENT state */
			managerTree.getChildWithProperty (Ids::uiChildWindowName, getWindowName(window)).removeAllChildren (nullptr);

			/* reattach the CONTENT state but with the valid data reference */
			managerTree.getChildWithProperty (Ids::uiChildWindowName, getWindowName(window)).addChild (w->getContent()->saveState(), -1, nullptr);
		}
	}
}

void CtrlrPanelWindowManager::windowChanged(CtrlrChildWindow *windowThatChanged)
{
	CtrlrChildWindowContent		*c	= windowThatChanged->getContent();

	if (c == 0)
		return;

	CtrlrPanelWindowManager::WindowType window = (CtrlrPanelWindowManager::WindowType) c->getType();

	if (managerTree.getChildWithProperty (Ids::uiChildWindowName, getWindowName(window)).isValid())
	{
		managerTree.getChildWithProperty (Ids::uiChildWindowName, getWindowName(window)).setProperty (Ids::uiChildWindowState, getWindow(window)->getWindowStateAsString(), 0);
	}
	else
	{
		ValueTree windowTree(Ids::uiChildWindow);

		windowTree.setProperty (Ids::uiChildWindowName, getWindowName(window), 0);
		windowTree.setProperty (Ids::uiChildWindowState, getWindow(window)->getWindowStateAsString(), 0);
		windowTree.addChild (c->saveState(), -1, nullptr);

		managerTree.addChild(windowTree,-1,0);
	}
}
