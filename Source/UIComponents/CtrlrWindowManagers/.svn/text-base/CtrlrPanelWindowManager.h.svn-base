#ifndef __CTRLR_PANEL_WINDOW_MANAGER__
#define __CTRLR_PANEL_WINDOW_MANAGER__

#include "CtrlrChildWindow.h"

class CtrlrPanel;

class CtrlrPanelWindowManager : public CtrlrWindowManager
{
	public:
		enum WindowType
		{
			LuaConsole,
			LuaMethodEditor,
			ModulatorList,
			LayerEditor,
			MIDILibrary,
			BufferEditor
		};

		CtrlrPanelWindowManager(CtrlrPanel &_owner);
		virtual ~CtrlrPanelWindowManager();
		CtrlrPanel &getOwner();
		const String getWindowName(const CtrlrPanelWindowManager::WindowType window);
		const CtrlrPanelWindowManager::WindowType getWindowType(const String &windowName);
		void show (const CtrlrPanelWindowManager::WindowType window);
		void toggle(const CtrlrPanelWindowManager::WindowType window, const bool makeVisible=true);
		const bool isCreated(const CtrlrPanelWindowManager::WindowType window);
		Component *getContent(const CtrlrPanelWindowManager::WindowType window);
		void windowChanged(CtrlrChildWindow *windowThatChanged);
		void windowClosedButtonPressed(CtrlrChildWindow *windowThatChanged);
		void restoreState (const ValueTree &savedState);
		ValueTree &getManagerTree()															{ return (managerTree); }

		JUCE_LEAK_DETECTOR(CtrlrPanelWindowManager)

	private:
		CtrlrChildWindow *getWindow(const CtrlrPanelWindowManager::WindowType window, const bool createIfNeeded=true);
		void create(const CtrlrPanelWindowManager::WindowType window, const String &lastWindowState=String::empty);
		void create(const ValueTree &windowState);
		CtrlrChildWindow *createWindow(const CtrlrPanelWindowManager::WindowType window);
		CtrlrPanel &owner;
		OwnedArray <CtrlrChildWindow> windows;
		ValueTree managerTree;
};

#endif
