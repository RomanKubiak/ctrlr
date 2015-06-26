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
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            TRANS("Controller mapping")));

    addAndMakeVisible (componentName = new Label (String::empty,
                                                  TRANS("This is a long modulator name")));
    componentName->setFont (Font (14.00f, Font::bold));
    componentName->setJustificationType (Justification::centred);
    componentName->setEditable (false, false, false);
    componentName->setColour (Label::outlineColourId, Colour (0x79000000));
    componentName->setColour (TextEditor::textColourId, Colours::black);
    componentName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (modulatorNumericValue = new Slider (String::empty));
    modulatorNumericValue->setRange (0, 127, 1);
    modulatorNumericValue->setSliderStyle (Slider::IncDecButtons);
    modulatorNumericValue->setTextBoxStyle (Slider::TextBoxLeft, false, 48, 20);
    modulatorNumericValue->setColour (Slider::textBoxOutlineColourId, Colours::black);
    modulatorNumericValue->addListener (this);

    addAndMakeVisible (viewRealtimeEvents = new TextButton (String::empty));
    viewRealtimeEvents->setTooltip (TRANS("This will show MIDI events comming from the selected Controller Midi Device"));
    viewRealtimeEvents->setButtonText (TRANS("View realtime"));
    viewRealtimeEvents->addListener (this);
    viewRealtimeEvents->setColour (TextButton::buttonColourId, Colour (0xff39ff99));

    addAndMakeVisible (realtimeEventsList = new ListBox());

    addAndMakeVisible (mapToSelected = new TextButton (String::empty));
    mapToSelected->setTooltip (TRANS("Map this modulator to the selected MIDI message type and controller number"));
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
    label2->setFont (Font (12.00f, Font::italic));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (currentMIDIType = new ComboBox ("new combo box"));
    currentMIDIType->setEditableText (false);
    currentMIDIType->setJustificationType (Justification::centredRight);
    currentMIDIType->setTextWhenNothingSelected (TRANS("CC"));
    currentMIDIType->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    currentMIDIType->addItem (TRANS("CC"), 1);
    currentMIDIType->addItem (TRANS("NRPN"), 2);
    currentMIDIType->addItem (TRANS("RPN"), 3);
    currentMIDIType->addItem (TRANS("Pitch Bend"), 4);
    currentMIDIType->addItem (TRANS("Mod Wheel"), 5);
    currentMIDIType->addItem (TRANS("Note On - Velocity"), 6);
    currentMIDIType->addItem (TRANS("Note On - Pitch"), 7);
    currentMIDIType->addSeparator();
    currentMIDIType->addListener (this);

    addAndMakeVisible (currentMIDINumber = new Label (String::empty,
                                                      TRANS("001")));
    currentMIDINumber->setFont (Font (Font::getDefaultMonospacedFontName(), 12.00f, Font::plain));
    currentMIDINumber->setJustificationType (Justification::centredRight);
    currentMIDINumber->setEditable (true, true, false);
    currentMIDINumber->setColour (Label::backgroundColourId, Colour (0x61ffffff));
    currentMIDINumber->setColour (Label::outlineColourId, Colour (0x80000000));
    currentMIDINumber->setColour (TextEditor::textColourId, Colours::black);
    currentMIDINumber->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    currentMIDINumber->addListener (this);

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Current mapping")));
    label3->setFont (Font (12.00f, Font::italic));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("Number")));
    label4->setFont (Font (12.00f, Font::bold | Font::italic));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (Label::outlineColourId, Colour (0x73000000));
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (currentMidiMessage = new Label (String::empty,
                                                       TRANS("This is the current Midi message")));
    currentMidiMessage->setFont (Font (Font::getDefaultMonospacedFontName(), 12.00f, Font::bold));
    currentMidiMessage->setJustificationType (Justification::centredLeft);
    currentMidiMessage->setEditable (false, false, false);
    currentMidiMessage->setColour (Label::outlineColourId, Colour (0x79000000));
    currentMidiMessage->setColour (TextEditor::textColourId, Colours::black);
    currentMidiMessage->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    componentToConfigure->getOwner().getOwnerPanel().addPanelListener(this);
    //[/UserPreSize]

    setSize (320, 200);


    //[Constructor] You can add your own custom stuff here..
    componentName->setText (componentToConfigure->getOwner().getName(), dontSendNotification);
    modulatorNumericValue->setRange (componentToConfigure->getOwner().getMinNonMapped(), componentToConfigure->getOwner().getMaxNonMapped(), 1);
    modulatorNumericValue->setValue (componentToConfigure->getOwner().getValueNonMapped(), dontSendNotification);
    mappingFormula->setText(componentToConfigure->getOwner().getProperty(Ids::modulatorControllerExpression, EXP_MODULATOR_CONTROLLER), dontSendNotification);
    //[/Constructor]
}

CtrlrComponentRuntimeConfig::~CtrlrComponentRuntimeConfig()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    componentToConfigure->getOwner().getOwnerPanel().removePanelListener(this);
    //[/Destructor_pre]

    groupComponent = nullptr;
    componentName = nullptr;
    modulatorNumericValue = nullptr;
    viewRealtimeEvents = nullptr;
    realtimeEventsList = nullptr;
    mapToSelected = nullptr;
    mappingFormula = nullptr;
    label2 = nullptr;
    currentMIDIType = nullptr;
    currentMIDINumber = nullptr;
    label3 = nullptr;
    label4 = nullptr;
    currentMidiMessage = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrComponentRuntimeConfig::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setGradientFill (ColourGradient (Colour (0xffa9c6ff),
                                       0.0f, 0.0f,
                                       Colour (0xff69d7ff),
                                       320.0f, static_cast<float> (getHeight()),
                                       false));
    g.fillRect (0, 0, getWidth() - 0, getHeight() - 0);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrComponentRuntimeConfig::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    groupComponent->setBounds (0, 56, getWidth() - 0, 144);
    componentName->setBounds (4, 8, proportionOfWidth (0.5813f), 24);
    modulatorNumericValue->setBounds (proportionOfWidth (0.6000f), 8, proportionOfWidth (0.4000f), 24);
    viewRealtimeEvents->setBounds (176, 80, 64, 16);
    realtimeEventsList->setBounds (8, 80, proportionOfWidth (0.5000f), getHeight() - 88);
    mapToSelected->setBounds (248, 80, 63, 16);
    mappingFormula->setBounds (176, 176, 136, 16);
    label2->setBounds (176, 160, 136, 16);
    currentMIDIType->setBounds (176, 116, 136, 16);
    currentMIDINumber->setBounds (232, 136, 80, 16);
    label3->setBounds (176, 100, 136, 16);
    label4->setBounds (176, 136, 56, 16);
    currentMidiMessage->setBounds (4, 36, proportionOfWidth (0.9625f), 16);
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
        componentToConfigure->getOwner().setProperty(Ids::modulatorControllerExpression, mappingFormula->getText(), false);
        //[/UserLabelCode_mappingFormula]
    }
    else if (labelThatHasChanged == currentMIDINumber)
    {
        //[UserLabelCode_currentMIDINumber] -- add your label text handling code here..
        //[/UserLabelCode_currentMIDINumber]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}

void CtrlrComponentRuntimeConfig::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == currentMIDIType)
    {
        //[UserComboBoxCode_currentMIDIType] -- add your combo box handling code here..
        //[/UserComboBoxCode_currentMIDIType]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
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
    <RECT pos="0 0 0M 0M" fill="linear: 0 0, 320 0R, 0=ffa9c6ff, 1=ff69d7ff"
          hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="new group" id="1e62cac43e08f6c7" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="0 56 0M 144" title="Controller mapping"/>
  <LABEL name="" id="db93816ae811cf4d" memberName="componentName" virtualName=""
         explicitFocusOrder="0" pos="4 8 58.125% 24" outlineCol="79000000"
         edTextCol="ff000000" edBkgCol="0" labelText="This is a long modulator name"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="14" bold="1" italic="0" justification="36"/>
  <SLIDER name="" id="44437b95d8664f31" memberName="modulatorNumericValue"
          virtualName="" explicitFocusOrder="0" pos="60% 8 40% 24" textboxoutline="ff000000"
          min="0" max="127" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="48" textBoxHeight="20" skewFactor="1"/>
  <TEXTBUTTON name="" id="5a2402776f314e33" memberName="viewRealtimeEvents"
              virtualName="" explicitFocusOrder="0" pos="176 80 64 16" tooltip="This will show MIDI events comming from the selected Controller Midi Device"
              bgColOff="ff39ff99" buttonText="View realtime" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="" id="baa41514b5f7013f" memberName="realtimeEventsList"
                    virtualName="" explicitFocusOrder="0" pos="8 80 50% 88M" class="ListBox"
                    params=""/>
  <TEXTBUTTON name="" id="68e0657e7ef3a65a" memberName="mapToSelected" virtualName=""
              explicitFocusOrder="0" pos="248 80 63 16" tooltip="Map this modulator to the selected MIDI message type and controller number"
              bgColOff="ff39e8ff" buttonText="Map to selected" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="771520d7ac6dc5a3" memberName="mappingFormula" virtualName=""
         explicitFocusOrder="0" pos="176 176 136 16" outlineCol="80000000"
         edTextCol="ff000000" edBkgCol="0" labelText="value" editableSingleClick="1"
         editableDoubleClick="1" focusDiscardsChanges="0" fontname="Default monospaced font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="8949a0abd624d647" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="176 160 136 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Mapping formula" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="1" justification="33"/>
  <COMBOBOX name="new combo box" id="3150094d39df505" memberName="currentMIDIType"
            virtualName="" explicitFocusOrder="0" pos="176 116 136 16" editable="0"
            layout="34" items="CC&#10;NRPN&#10;RPN&#10;Pitch Bend&#10;Mod Wheel&#10;Note On - Velocity&#10;Note On - Pitch&#10;"
            textWhenNonSelected="CC" textWhenNoItems="(no choices)"/>
  <LABEL name="" id="9b3f92fe3ca96fc5" memberName="currentMIDINumber"
         virtualName="" explicitFocusOrder="0" pos="232 136 80 16" bkgCol="61ffffff"
         outlineCol="80000000" edTextCol="ff000000" edBkgCol="0" labelText="001"
         editableSingleClick="1" editableDoubleClick="1" focusDiscardsChanges="0"
         fontname="Default monospaced font" fontsize="12" bold="0" italic="0"
         justification="34"/>
  <LABEL name="new label" id="da93ee4c33971909" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="176 100 136 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Current mapping" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="1" justification="33"/>
  <LABEL name="new label" id="2c67825195c5a62c" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="176 136 56 16" outlineCol="73000000"
         edTextCol="ff000000" edBkgCol="0" labelText="Number" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="1" italic="1" justification="33"/>
  <LABEL name="" id="f3d83dd4300ccab" memberName="currentMidiMessage"
         virtualName="" explicitFocusOrder="0" pos="4 36 96.25% 16" outlineCol="79000000"
         edTextCol="ff000000" edBkgCol="0" labelText="This is the current Midi message"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default monospaced font" fontsize="12" bold="1" italic="0"
         justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
