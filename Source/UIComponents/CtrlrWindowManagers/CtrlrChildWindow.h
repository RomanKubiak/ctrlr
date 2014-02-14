#ifndef CTRLR_CHILD_WINDOW_H
#define CTRLR_CHILD_WINDOW_H

#include "JuceHeader.h"
#include "CtrlrChildWindowContainer.h"
#include "CtrlrLog.h"

class CtrlrPanelWindowManager;
class CtrlrChildWindowContent;
class CtrlrLookAndFeel;
class CtrlrChildWindow;

class CtrlrWindowManager
{
	public:
		virtual ~CtrlrWindowManager() {}
		virtual void windowChanged(CtrlrChildWindow *windowThatChanged)=0;
		virtual void windowClosedButtonPressed(CtrlrChildWindow *windowThatChanged)=0;
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
		void paint (Graphics& g);
		void resized();
		void enablementChanged();

		JUCE_LEAK_DETECTOR(CtrlrChildWindow)

	private:
		CtrlrChildWindowContainer *containerComponent;
		CtrlrChildWindowContent *contentComponent;
		CtrlrWindowManager &owner;
};


#endif
