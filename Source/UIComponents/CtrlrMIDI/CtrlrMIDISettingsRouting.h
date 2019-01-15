/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_C6A688908B7833AE__
#define __JUCE_HEADER_C6A688908B7833AE__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
class CtrlrPanel;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrMIDISettingsRouting  : public Component,
									public Button::Listener
{
public:
    //==============================================================================
    CtrlrMIDISettingsRouting (CtrlrPanel &_owner);
    ~CtrlrMIDISettingsRouting();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    CtrlrPanel &owner;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> groupComponent;
    ScopedPointer<ToggleButton> inDev2OutDev;
    ScopedPointer<ToggleButton> ctrlDev2OutDev;
    ScopedPointer<ToggleButton> host2OutDev;
    ScopedPointer<ToggleButton> host2Host;
    ScopedPointer<ToggleButton> inDev2OutDevCh;
    ScopedPointer<ToggleButton> ctrlDev2OutDevCh;
    ScopedPointer<ToggleButton> host2OutDevCh;
    ScopedPointer<ToggleButton> host2HostCh;
    ScopedPointer<Label> label;
    ScopedPointer<ToggleButton> inDev2Host;
    ScopedPointer<ToggleButton> inDev2HostCh;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrMIDISettingsRouting)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_C6A688908B7833AE__
