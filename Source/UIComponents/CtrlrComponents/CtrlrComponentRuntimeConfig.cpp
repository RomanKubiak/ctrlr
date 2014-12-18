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

//[Headers] You can add your own extra header files here...
#include "stdafx.h"
#include "CtrlrComponent.h"
//[/Headers]

#include "CtrlrComponentRuntimeConfig.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrComponentRuntimeConfig::CtrlrComponentRuntimeConfig (CtrlrComponent *_componentToConfigure)
    : componentToConfigure(_componentToConfigure)
{
    addAndMakeVisible (componentName = new Label (String::empty,
                                                  TRANS("Component Name")));
    componentName->setFont (Font (16.00f, Font::bold));
    componentName->setJustificationType (Justification::centred);
    componentName->setEditable (false, false, false);
    componentName->setColour (TextEditor::textColourId, Colours::black);
    componentName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (modulatorNumericValue = new Slider (String::empty));
    modulatorNumericValue->setRange (0, 127, 0);
    modulatorNumericValue->setSliderStyle (Slider::IncDecButtons);
    modulatorNumericValue->setTextBoxStyle (Slider::TextBoxLeft, false, 48, 20);
    modulatorNumericValue->setColour (Slider::textBoxOutlineColourId, Colours::black);
    modulatorNumericValue->addListener (this);

    addAndMakeVisible (viewRealtimeEvents = new TextButton (String::empty));
    viewRealtimeEvents->setButtonText (TRANS("View realtime"));
    viewRealtimeEvents->addListener (this);
    viewRealtimeEvents->setColour (TextButton::buttonColourId, Colour (0xff39ff99));

    addAndMakeVisible (realtimeEventsList = new ListBox());

    addAndMakeVisible (mapToSelected = new TextButton (String::empty));
    mapToSelected->setButtonText (TRANS("Map to selected"));
    mapToSelected->addListener (this);
    mapToSelected->setColour (TextButton::buttonColourId, Colour (0xff39e8ff));

    addAndMakeVisible (mappingFormula = new Label (String::empty,
                                                   TRANS("value")));
    mappingFormula->setFont (Font (Font::getDefaultMonospacedFontName(), 12.00f, Font::plain));
    mappingFormula->setJustificationType (Justification::centredLeft);
    mappingFormula->setEditable (true, true, false);
    mappingFormula->setColour (Label::outlineColourId, Colour (0x80000000));
    mappingFormula->setColour (TextEditor::textColourId, Colours::black);
    mappingFormula->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    mappingFormula->addListener (this);

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Mapping formula")));
    label2->setFont (Font (12.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    componentToConfigure->getOwner().getOwner().addPanelListener(this);
    //[/UserPreSize]

    setSize (320, 200);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrComponentRuntimeConfig::~CtrlrComponentRuntimeConfig()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    componentToConfigure->getOwner().getOwner().removePanelListener(this);
    //[/Destructor_pre]

    componentName = nullptr;
    modulatorNumericValue = nullptr;
    viewRealtimeEvents = nullptr;
    realtimeEventsList = nullptr;
    mapToSelected = nullptr;
    mappingFormula = nullptr;
    label2 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrComponentRuntimeConfig::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setGradientFill (ColourGradient (Colours::white,
                                       0.0f, 0.0f,
                                       Colour (0xff608fd4),
                                       0.0f, static_cast<float> (getHeight()),
                                       false));
    g.fillRect (0, 0, getWidth() - 0, getHeight() - 0);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrComponentRuntimeConfig::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    componentName->setBounds (0, 8, proportionOfWidth (0.6000f), 24);
    modulatorNumericValue->setBounds (proportionOfWidth (0.6000f), 8, proportionOfWidth (0.4000f), 24);
    viewRealtimeEvents->setBounds (176, 40, 103, 24);
    realtimeEventsList->setBounds (8, 40, proportionOfWidth (0.5000f), getHeight() - 48);
    mapToSelected->setBounds (176, 72, 103, 24);
    mappingFormula->setBounds (176, 120, 136, 24);
    label2->setBounds (176, 104, 136, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CtrlrComponentRuntimeConfig::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == modulatorNumericValue)
    {
        //[UserSliderCode_modulatorNumericValue] -- add your slider handling code here..
        //[/UserSliderCode_modulatorNumericValue]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void CtrlrComponentRuntimeConfig::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == viewRealtimeEvents)
    {
        //[UserButtonCode_viewRealtimeEvents] -- add your button handler code here..
        //[/UserButtonCode_viewRealtimeEvents]
    }
    else if (buttonThatWasClicked == mapToSelected)
    {
        //[UserButtonCode_mapToSelected] -- add your button handler code here..
        //[/UserButtonCode_mapToSelected]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void CtrlrComponentRuntimeConfig::labelTextChanged (Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == mappingFormula)
    {
        //[UserLabelCode_mappingFormula] -- add your label text handling code here..
        //[/UserLabelCode_mappingFormula]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
int CtrlrComponentRuntimeConfig::getNumRows()
{
    return (0);
}

void CtrlrComponentRuntimeConfig::paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrComponentRuntimeConfig"
                 componentName="" parentClasses="public Component, public ListBoxModel, public CtrlrPanel::Listener"
                 constructorParams="CtrlrComponent *_componentToConfigure" variableInitialisers="componentToConfigure(_componentToConfigure)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="320" initialHeight="200">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 0 0M 0M" fill="linear: 0 0, 0 0R, 0=ffffffff, 1=ff608fd4"
          hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="" id="db93816ae811cf4d" memberName="componentName" virtualName=""
         explicitFocusOrder="0" pos="0 8 60% 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Component Name" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16" bold="1" italic="0" justification="36"/>
  <SLIDER name="" id="44437b95d8664f31" memberName="modulatorNumericValue"
          virtualName="" explicitFocusOrder="0" pos="60% 8 40% 24" textboxoutline="ff000000"
          min="0" max="127" int="0" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="48" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="" id="5a2402776f314e33" memberName="viewRealtimeEvents"
              virtualName="" explicitFocusOrder="0" pos="176 40 103 24" bgColOff="ff39ff99"
              buttonText="View realtime" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <GENERICCOMPONENT name="" id="baa41514b5f7013f" memberName="realtimeEventsList"
                    virtualName="" explicitFocusOrder="0" pos="8 40 50% 48M" class="ListBox"
                    params=""/>
  <TEXTBUTTON name="" id="68e0657e7ef3a65a" memberName="mapToSelected" virtualName=""
              explicitFocusOrder="0" pos="176 72 103 24" bgColOff="ff39e8ff"
              buttonText="Map to selected" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <LABEL name="" id="771520d7ac6dc5a3" memberName="mappingFormula" virtualName=""
         explicitFocusOrder="0" pos="176 120 136 24" outlineCol="80000000"
         edTextCol="ff000000" edBkgCol="0" labelText="value" editableSingleClick="1"
         editableDoubleClick="1" focusDiscardsChanges="0" fontname="Default monospaced font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="8949a0abd624d647" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="176 104 136 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Mapping formula" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
