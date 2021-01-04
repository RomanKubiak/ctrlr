#pragma once

#include "JuceHeader.h"
#include "CtrlrChildWindowContainer.h"
#include "CtrlrLog.h"

class CtrlrPanelWindowManager;
class CtrlrChildWindowContent;
class CtrlrLookAndFeel;
class CtrlrChildWindow;
class CtrlrManager;
class CtrlrWindowManager
{
	public:
        CtrlrWindowManager (CtrlrManager &_managerOwner) : managerOwner(_managerOwner) {}
		virtual ~CtrlrWindowManager() {}
		virtual void windowChanged(CtrlrChildWindow *windowThatChanged)=0;
		virtual void windowClosedButtonPressed(CtrlrChildWindow *windowThatChanged)=0;

		CtrlrManager &managerOwner;
};

class CtrlrChildWindow  : public DocumentWindow, public KeyListener
{
	public:
		CtrlrChildWindow (CtrlrWindowManager &_owner);
		~CtrlrChildWindow();
		CtrlrChildWindowContent *getContent();
		void setContent(CtrlrChildWindowContent *_contentComponent);
		uint8 getType();
		void closeButtonPressed();
		void moved();
		bool keyPressed (const KeyPress &key, Component *originatingComponent);
		void resized();
		void enablementChanged();

		JUCE_LEAK_DETECTOR(CtrlrChildWindow)

	private:
		CtrlrChildWindowContainer *containerComponent;
		CtrlrChildWindowContent *contentComponent;
		CtrlrWindowManager &owner;
		TooltipWindow window;
};
