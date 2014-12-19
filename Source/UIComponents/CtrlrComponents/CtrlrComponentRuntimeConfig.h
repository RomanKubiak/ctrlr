/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_67FEE93AC802F808__
#define __JUCE_HEADER_67FEE93AC802F808__

//[Headers]     -- You can add your own extra header files here --
#include "CtrlrPanel/CtrlrPanel.h"
class CtrlrComponent;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrComponentRuntimeConfig  : public Component,
                                     public ListBoxModel,
                                     public CtrlrPanel::Listener,
                                     public SliderListener,
                                     public ButtonListener,
                                     public LabelListener,
                                     public ComboBoxListener
{
public:
    //==============================================================================
    CtrlrComponentRuntimeConfig (CtrlrComponent *_componentToConfigure);
    ~CtrlrComponentRuntimeConfig();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    int getNumRows();
    void paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);
    void labelTextChanged (Label* labelThatHasChanged);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    CtrlrComponent *componentToConfigure;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> componentName;
    ScopedPointer<Slider> modulatorNumericValue;
    ScopedPointer<TextButton> viewRealtimeEvents;
    ScopedPointer<ListBox> realtimeEventsList;
    ScopedPointer<TextButton> mapToSelected;
    ScopedPointer<Label> mappingFormula;
    ScopedPointer<Label> label2;
    ScopedPointer<ComboBox> currentMIDIType;
    ScopedPointer<Label> currentMIDINumber;
    ScopedPointer<Label> label3;
    ScopedPointer<Label> label4;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrComponentRuntimeConfig)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_67FEE93AC802F808__
