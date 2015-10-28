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

#ifndef __JUCE_HEADER_76E483A2275D56C__
#define __JUCE_HEADER_76E483A2275D56C__

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
class CtrlrMIDISettingsDevices  : public Component,
                                  public ComboBoxListener,
                                  public LabelListener,
                                  public ButtonListener
{
public:
    //==============================================================================
    CtrlrMIDISettingsDevices (CtrlrPanel &_owner);
    ~CtrlrMIDISettingsDevices();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void labelTextChanged (Label* labelThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    CtrlrPanel &owner;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ComboBox> inputDevices;
    ScopedPointer<ComboBox> controllerDevices;
    ScopedPointer<ComboBox> outputDevices;
    ScopedPointer<Label> label;
    ScopedPointer<Label> label2;
    ScopedPointer<Label> label3;
    ScopedPointer<ComboBox> oscProtocol;
    ScopedPointer<Label> label4;
    ScopedPointer<Label> oscPort;
    ScopedPointer<Label> label5;
    ScopedPointer<Label> label6;
    ScopedPointer<ToggleButton> oscEnabled;
    ScopedPointer<Label> label7;
    ScopedPointer<ComboBox> inputChannel;
    ScopedPointer<ComboBox> controllerChannel;
    ScopedPointer<ComboBox> outputChannel;
    ScopedPointer<Label> label8;
    ScopedPointer<ComboBox> pluginOutputChannel;
    ScopedPointer<ToggleButton> pluginOutput;
    ScopedPointer<Label> label9;
    ScopedPointer<ToggleButton> pluginInput;
    ScopedPointer<ComboBox> pluginInputChannel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrMIDISettingsDevices)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_76E483A2275D56C__
