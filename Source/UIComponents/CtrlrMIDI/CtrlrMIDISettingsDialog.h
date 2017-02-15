/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 4.0.2

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_522F0365577AE4E2__
#define __JUCE_HEADER_522F0365577AE4E2__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "CtrlrWindowManagers/CtrlrChildWindowContent.h"
class CtrlrPanel;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrMIDISettingsDialog  : public CtrlrChildWindowContent
{
public:
    //==============================================================================
    CtrlrMIDISettingsDialog (CtrlrPanel &_owner);
    ~CtrlrMIDISettingsDialog();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    static void showDialog(CtrlrPanel &_owner);
    uint8 getType() { return (CtrlrPanelWindowManager::MIDISettings); }
    //[/UserMethods]
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    CtrlrPanel &owner;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TabbedComponent> midiTabs;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrMIDISettingsDialog)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_522F0365577AE4E2__
