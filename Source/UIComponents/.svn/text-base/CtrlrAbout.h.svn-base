/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  7 Mar 2013 10:38:15pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRABOUT_CTRLRABOUT_41C9DE20__
#define __JUCER_HEADER_CTRLRABOUT_CTRLRABOUT_41C9DE20__

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
    //[/UserVariables]

    //==============================================================================
    Label* ctrlrName;
    ImageButton* ctrlrLogo;
    TextEditor* versionInfoLabel;
    Label* label;
    Label* label2;
    Label* label3;
    Label* label4;
    HyperlinkButton* instanceUrl;
    Label* instanceVersion;
    Label* instanceAuthor;
    Label* instanceName;
    TextEditor* instanceDescription;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrAbout)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCER_HEADER_CTRLRABOUT_CTRLRABOUT_41C9DE20__
