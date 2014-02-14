/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  23 Oct 2012 11:11:41pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRCHILDWINDOWCONTAINER_CTRLRCHILDWINDOWCONTAINER_BC6ED1A9__
#define __JUCER_HEADER_CTRLRCHILDWINDOWCONTAINER_CTRLRCHILDWINDOWCONTAINER_BC6ED1A9__

//[Headers]     -- You can add your own extra header files here --
#include "CtrlrMacros.h"
#include "CtrlrApplicationWindow/CtrlrLookAndFeel.h"
class CtrlrChildWindowContent;
class CtrlrPanelWindowManager;
class CtrlrChildWindowContainer;
class CtrlrWindowManager;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrChildWindowContainer  : public Component,
                                   public MenuBarModel
{
public:
    //==============================================================================
    CtrlrChildWindowContainer (CtrlrWindowManager &_owner);
    ~CtrlrChildWindowContainer();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setContent(CtrlrChildWindowContent *_content);
	CtrlrChildWindowContent *getContent();
	CtrlrWindowManager &getOwner();
	StringArray getMenuBarNames();
	PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName);
	void menuItemSelected(int menuItemID, int topLevelMenuIndex);
	void closeWindow();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	CtrlrChildWindowContent *content;
	CtrlrWindowManager &owner;
    //[/UserVariables]

    //==============================================================================
    MenuBarComponent* menuBar;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrChildWindowContainer);
};


#endif   // __JUCER_HEADER_CTRLRCHILDWINDOWCONTAINER_CTRLRCHILDWINDOWCONTAINER_BC6ED1A9__
