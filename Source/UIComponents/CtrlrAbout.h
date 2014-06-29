/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_38C6DBC920B693D4__
#define __JUCE_HEADER_38C6DBC920B693D4__

//[Headers]     -- You can add your own extra header files here --
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrUpdateManager.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrAbout  : public Component,
                    public ButtonListener
{
public:
    //==============================================================================
    CtrlrAbout (CtrlrManager &_owner);
    ~CtrlrAbout();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void addVersionInfo (const String &componentName, const String &componentVersion);
	void updateVersionLabel();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	CtrlrManager &owner;
	StringPairArray versionInformationArray;
	DropShadowEffect shadow;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> ctrlrName;
    ScopedPointer<ImageButton> ctrlrLogo;
    ScopedPointer<TextEditor> versionInfoLabel;
    ScopedPointer<Label> label;
    ScopedPointer<Label> label2;
    ScopedPointer<Label> label3;
    ScopedPointer<Label> label4;
    ScopedPointer<HyperlinkButton> instanceUrl;
    ScopedPointer<Label> instanceVersion;
    ScopedPointer<Label> instanceAuthor;
    ScopedPointer<Label> instanceName;
    ScopedPointer<TextEditor> instanceDescription;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrAbout)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_38C6DBC920B693D4__
