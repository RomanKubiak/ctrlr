#ifndef __CTRLR_MANAGER_WINDOW_MANAGER__
#define __CTRLR_MANAGER_WINDOW_MANAGER__

#include "CtrlrMacros.h"
#include "CtrlrChildWindow.h"
class CtrlrManager;
class CtrlrChildWindow;

class CtrlrFloatingWindow : public DocumentWindow
{
	public:
		CtrlrFloatingWindow(const String &title, Component *content) : DocumentWindow (title, Colours::white, DocumentWindow::allButtons, true)
		{
			setUsingNativeTitleBar (true);
			setContentNonOwned (content, true);
			setVisible (true);
			centreWithSize (getWidth(), getHeight());
		}

		virtual ~CtrlrFloatingWindow()
		{
		}

		void closeButtonPressed()
		{
			delete this;
		}
};

class CtrlrManagerWindowManager : public CtrlrWindowManager
{
	public:
		enum WindowType
		{
			Repository,
			MidiMonWindow,
			LogViewer,
			MIDICalculator
		};

		CtrlrManagerWindowManager(CtrlrManager &_owner);
		virtual ~CtrlrManagerWindowManager();
		CtrlrManager &getOwner();

		const String getWindowName(const CtrlrManagerWindowManager::WindowType window);
		const CtrlrManagerWindowManager::WindowType getWindowType(const String &windowName);
		void show (const CtrlrManagerWindowManager::WindowType window);
		void hide (const CtrlrManagerWindowManager::WindowType window);
		void toggle(const CtrlrManagerWindowManager::WindowType window, const bool makeVisible=true);
		const bool isCreated(const CtrlrManagerWindowManager::WindowType window);
		Component *getContent(const CtrlrManagerWindowManager::WindowType window);

		void windowChanged(CtrlrChildWindow *windowThatChanged);
		void windowClosedButtonPressed(CtrlrChildWindow *windowThatChanged);

		void restoreState (const ValueTree &savedState);
		static void showModalDialog(const String &title, Component *content, const bool resizable=false, Component *parent=0);
		ValueTree &getManagerTree();

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrManagerWindowManager)

	private:
		CtrlrChildWindow *getWindow(const CtrlrManagerWindowManager::WindowType window, const bool createIfNeeded=true);
		CtrlrChildWindow *createWindow(const CtrlrManagerWindowManager::WindowType window);
		void create(const CtrlrManagerWindowManager::WindowType window, const String &lastWindowState=String::empty);
		void create(const ValueTree &windowState);
		CtrlrManager &owner;
		OwnedArray <CtrlrChildWindow> windows;
		ValueTree managerTree;
};

#endif
