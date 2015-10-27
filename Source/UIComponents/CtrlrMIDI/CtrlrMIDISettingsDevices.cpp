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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "CtrlrMIDISettingsDevices.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "MIDI/CtrlrMidiDeviceManager.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
//[/MiscUserDefs]

//==============================================================================
CtrlrMIDISettingsDevices::CtrlrMIDISettingsDevices (CtrlrPanel &_owner)
    : owner(_owner)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (inputDevices = new ComboBox (String::empty));
    inputDevices->setEditableText (false);
    inputDevices->setJustificationType (Justification::centredLeft);
    inputDevices->setTextWhenNothingSelected (TRANS("No device selected"));
    inputDevices->setTextWhenNoChoicesAvailable (TRANS("No devices available"));
    inputDevices->addListener (this);

    addAndMakeVisible (controllerDevices = new ComboBox (String::empty));
    controllerDevices->setEditableText (false);
    controllerDevices->setJustificationType (Justification::centredLeft);
    controllerDevices->setTextWhenNothingSelected (TRANS("No device selected"));
    controllerDevices->setTextWhenNoChoicesAvailable (TRANS("No devices available"));
    controllerDevices->addListener (this);

    addAndMakeVisible (outputDevices = new ComboBox (String::empty));
    outputDevices->setEditableText (false);
    outputDevices->setJustificationType (Justification::centredLeft);
    outputDevices->setTextWhenNothingSelected (TRANS("No device selected"));
    outputDevices->setTextWhenNoChoicesAvailable (TRANS("No devices available"));
    outputDevices->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Input device")));
    label->setFont (Font (16.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Controller device")));
    label2->setFont (Font (16.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Output device")));
    label3->setFont (Font (16.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (oscProtocol = new ComboBox ("OSC Protocol"));
    oscProtocol->setEditableText (false);
    oscProtocol->setJustificationType (Justification::centredLeft);
    oscProtocol->setTextWhenNothingSelected (TRANS("TCP"));
    oscProtocol->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    oscProtocol->addItem (TRANS("UDP"), 1);
    oscProtocol->addItem (TRANS("TCP"), 2);
    oscProtocol->addItem (TRANS("SOCKET"), 3);
    oscProtocol->addListener (this);

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("OSC Server settings")));
    label4->setFont (Font (16.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (oscPort = new Label ("OSC Port",
                                            TRANS("7770")));
    oscPort->setTooltip (TRANS("OSC Port"));
    oscPort->setFont (Font (24.00f, Font::plain));
    oscPort->setJustificationType (Justification::centred);
    oscPort->setEditable (true, true, false);
    oscPort->setColour (Label::backgroundColourId, Colours::white);
    oscPort->setColour (Label::outlineColourId, Colour (0x84000000));
    oscPort->setColour (TextEditor::textColourId, Colours::black);
    oscPort->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    oscPort->addListener (this);

    addAndMakeVisible (label5 = new Label ("new label",
                                           TRANS("Protocol")));
    label5->setFont (Font (14.00f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label6 = new Label ("new label",
                                           TRANS("Port/Socket path")));
    label6->setFont (Font (14.00f, Font::plain));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (oscEnabled = new ToggleButton ("OSC Enabled"));
    oscEnabled->setButtonText (String::empty);
    oscEnabled->addListener (this);

    addAndMakeVisible (label7 = new Label ("new label",
                                           TRANS("Enable")));
    label7->setFont (Font (14.00f, Font::plain));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (inputChannel = new ComboBox (String::empty));
    inputChannel->setEditableText (false);
    inputChannel->setJustificationType (Justification::centredLeft);
    inputChannel->setTextWhenNothingSelected (TRANS("All"));
    inputChannel->setTextWhenNoChoicesAvailable (String::empty);
    inputChannel->addItem (TRANS("All"), 1);
    inputChannel->addItem (TRANS("1"), 2);
    inputChannel->addItem (TRANS("2"), 3);
    inputChannel->addItem (TRANS("3"), 4);
    inputChannel->addItem (TRANS("4"), 5);
    inputChannel->addItem (TRANS("6"), 6);
    inputChannel->addItem (TRANS("7"), 7);
    inputChannel->addItem (TRANS("8"), 8);
    inputChannel->addItem (TRANS("9"), 9);
    inputChannel->addItem (TRANS("10"), 10);
    inputChannel->addItem (TRANS("11"), 11);
    inputChannel->addItem (TRANS("12"), 12);
    inputChannel->addItem (TRANS("13"), 13);
    inputChannel->addItem (TRANS("14"), 14);
    inputChannel->addItem (TRANS("15"), 15);
    inputChannel->addItem (TRANS("16"), 16);
    inputChannel->addListener (this);

    addAndMakeVisible (controllerChannel = new ComboBox (String::empty));
    controllerChannel->setEditableText (false);
    controllerChannel->setJustificationType (Justification::centredLeft);
    controllerChannel->setTextWhenNothingSelected (TRANS("All"));
    controllerChannel->setTextWhenNoChoicesAvailable (String::empty);
    controllerChannel->addItem (TRANS("All"), 1);
    controllerChannel->addItem (TRANS("1"), 2);
    controllerChannel->addItem (TRANS("2"), 3);
    controllerChannel->addItem (TRANS("3"), 4);
    controllerChannel->addItem (TRANS("4"), 5);
    controllerChannel->addItem (TRANS("6"), 6);
    controllerChannel->addItem (TRANS("7"), 7);
    controllerChannel->addItem (TRANS("8"), 8);
    controllerChannel->addItem (TRANS("9"), 9);
    controllerChannel->addItem (TRANS("10"), 10);
    controllerChannel->addItem (TRANS("11"), 11);
    controllerChannel->addItem (TRANS("12"), 12);
    controllerChannel->addItem (TRANS("13"), 13);
    controllerChannel->addItem (TRANS("14"), 14);
    controllerChannel->addItem (TRANS("15"), 15);
    controllerChannel->addItem (TRANS("16"), 16);
    controllerChannel->addListener (this);

    addAndMakeVisible (outputChannel = new ComboBox (String::empty));
    outputChannel->setEditableText (false);
    outputChannel->setJustificationType (Justification::centredLeft);
    outputChannel->setTextWhenNothingSelected (TRANS("All"));
    outputChannel->setTextWhenNoChoicesAvailable (String::empty);
    outputChannel->addItem (TRANS("All"), 1);
    outputChannel->addItem (TRANS("1"), 2);
    outputChannel->addItem (TRANS("2"), 3);
    outputChannel->addItem (TRANS("3"), 4);
    outputChannel->addItem (TRANS("4"), 5);
    outputChannel->addItem (TRANS("6"), 6);
    outputChannel->addItem (TRANS("7"), 7);
    outputChannel->addItem (TRANS("8"), 8);
    outputChannel->addItem (TRANS("9"), 9);
    outputChannel->addItem (TRANS("10"), 10);
    outputChannel->addItem (TRANS("11"), 11);
    outputChannel->addItem (TRANS("12"), 12);
    outputChannel->addItem (TRANS("13"), 13);
    outputChannel->addItem (TRANS("14"), 14);
    outputChannel->addItem (TRANS("15"), 15);
    outputChannel->addItem (TRANS("16"), 16);
    outputChannel->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 400);


    //[Constructor] You can add your own custom stuff here..
    owner.getCtrlrManagerOwner().getCtrlrMidiDeviceManager().reloadComboContents (*inputDevices, CtrlrMIDIDeviceType::inputDevice, &owner);
    owner.getCtrlrManagerOwner().getCtrlrMidiDeviceManager().reloadComboContents (*controllerDevices, CtrlrMIDIDeviceType::controllerDevice, &owner);
    owner.getCtrlrManagerOwner().getCtrlrMidiDeviceManager().reloadComboContents (*outputDevices, CtrlrMIDIDeviceType::outputDevice, &owner);
    oscEnabled->setToggleState (owner.getProperty(Ids::panelOSCEnabled), dontSendNotification);
    oscPort->setText (owner.getProperty(Ids::panelOSCPort), dontSendNotification);
    oscProtocol->setSelectedItemIndex(owner.getProperty(Ids::panelOSCProtocol), dontSendNotification);
    //[/Constructor]
}

CtrlrMIDISettingsDevices::~CtrlrMIDISettingsDevices()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    inputDevices = nullptr;
    controllerDevices = nullptr;
    outputDevices = nullptr;
    label = nullptr;
    label2 = nullptr;
    label3 = nullptr;
    oscProtocol = nullptr;
    label4 = nullptr;
    oscPort = nullptr;
    label5 = nullptr;
    label6 = nullptr;
    oscEnabled = nullptr;
    label7 = nullptr;
    inputChannel = nullptr;
    controllerChannel = nullptr;
    outputChannel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrMIDISettingsDevices::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrMIDISettingsDevices::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    inputDevices->setBounds (proportionOfWidth (0.1000f), proportionOfHeight (0.1500f), proportionOfWidth (0.6000f), proportionOfHeight (0.1000f));
    controllerDevices->setBounds (proportionOfWidth (0.1000f), proportionOfHeight (0.3500f), proportionOfWidth (0.6000f), proportionOfHeight (0.1000f));
    outputDevices->setBounds (proportionOfWidth (0.1000f), proportionOfHeight (0.5500f), proportionOfWidth (0.6000f), proportionOfHeight (0.1000f));
    label->setBounds (proportionOfWidth (0.1000f), proportionOfHeight (0.0500f), proportionOfWidth (0.8000f), proportionOfHeight (0.1000f));
    label2->setBounds (proportionOfWidth (0.1000f), proportionOfHeight (0.2500f), proportionOfWidth (0.8000f), proportionOfHeight (0.1000f));
    label3->setBounds (proportionOfWidth (0.1000f), proportionOfHeight (0.4500f), proportionOfWidth (0.8000f), proportionOfHeight (0.1000f));
    oscProtocol->setBounds (proportionOfWidth (0.6500f), proportionOfHeight (0.8000f), proportionOfWidth (0.2000f), proportionOfHeight (0.1000f));
    label4->setBounds (proportionOfWidth (0.1000f), proportionOfHeight (0.6500f), proportionOfWidth (0.8000f), proportionOfHeight (0.1000f));
    oscPort->setBounds (proportionOfWidth (0.2500f), proportionOfHeight (0.8000f), proportionOfWidth (0.3000f), proportionOfHeight (0.1000f));
    label5->setBounds (proportionOfWidth (0.6500f), proportionOfHeight (0.7500f), proportionOfWidth (0.3000f), proportionOfHeight (0.0500f));
    label6->setBounds (proportionOfWidth (0.2500f), proportionOfHeight (0.7500f), proportionOfWidth (0.3000f), proportionOfHeight (0.0500f));
    oscEnabled->setBounds (proportionOfWidth (0.1000f), proportionOfHeight (0.8000f), proportionOfWidth (0.0500f), proportionOfHeight (0.1000f));
    label7->setBounds (proportionOfWidth (0.1000f), proportionOfHeight (0.7500f), proportionOfWidth (0.1500f), proportionOfHeight (0.0500f));
    inputChannel->setBounds (proportionOfWidth (0.7500f), proportionOfHeight (0.1500f), proportionOfWidth (0.2000f), proportionOfHeight (0.1000f));
    controllerChannel->setBounds (proportionOfWidth (0.7500f), proportionOfHeight (0.3500f), proportionOfWidth (0.2000f), proportionOfHeight (0.1000f));
    outputChannel->setBounds (proportionOfWidth (0.7500f), proportionOfHeight (0.5500f), proportionOfWidth (0.2000f), proportionOfHeight (0.1000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CtrlrMIDISettingsDevices::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == inputDevices)
    {
        //[UserComboBoxCode_inputDevices] -- add your combo box handling code here..
        owner.setProperty(Ids::panelMidiInputDevice, inputDevices->getText());
        //[/UserComboBoxCode_inputDevices]
    }
    else if (comboBoxThatHasChanged == controllerDevices)
    {
        //[UserComboBoxCode_controllerDevices] -- add your combo box handling code here..
        owner.setProperty(Ids::panelMidiControllerDevice, controllerDevices->getText());
        //[/UserComboBoxCode_controllerDevices]
    }
    else if (comboBoxThatHasChanged == outputDevices)
    {
        //[UserComboBoxCode_outputDevices] -- add your combo box handling code here..
        owner.setProperty(Ids::panelMidiOutputDevice, outputDevices->getText());
        //[/UserComboBoxCode_outputDevices]
    }
    else if (comboBoxThatHasChanged == oscProtocol)
    {
        //[UserComboBoxCode_oscProtocol] -- add your combo box handling code here..
        owner.setProperty(Ids::panelOSCProtocol, oscProtocol->getSelectedItemIndex());
        //[/UserComboBoxCode_oscProtocol]
    }
    else if (comboBoxThatHasChanged == inputChannel)
    {
        //[UserComboBoxCode_inputChannel] -- add your combo box handling code here..
        //[/UserComboBoxCode_inputChannel]
    }
    else if (comboBoxThatHasChanged == controllerChannel)
    {
        //[UserComboBoxCode_controllerChannel] -- add your combo box handling code here..
        //[/UserComboBoxCode_controllerChannel]
    }
    else if (comboBoxThatHasChanged == outputChannel)
    {
        //[UserComboBoxCode_outputChannel] -- add your combo box handling code here..
        //[/UserComboBoxCode_outputChannel]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void CtrlrMIDISettingsDevices::labelTextChanged (Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == oscPort)
    {
        //[UserLabelCode_oscPort] -- add your label text handling code here..
        owner.setProperty(Ids::panelOSCPort, oscPort->getText().getIntValue());
        //[/UserLabelCode_oscPort]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}

void CtrlrMIDISettingsDevices::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == oscEnabled)
    {
        //[UserButtonCode_oscEnabled] -- add your button handler code here..
        owner.setProperty(Ids::panelOSCEnabled, oscEnabled->getToggleState());
        //[/UserButtonCode_oscEnabled]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrMIDISettingsDevices"
                 componentName="" parentClasses="public Component" constructorParams="CtrlrPanel &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="400"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffff"/>
  <COMBOBOX name="" id="da3c6f7ecddc5352" memberName="inputDevices" virtualName=""
            explicitFocusOrder="0" pos="10% 15% 60% 10%" editable="0" layout="33"
            items="" textWhenNonSelected="No device selected" textWhenNoItems="No devices available"/>
  <COMBOBOX name="" id="a94f1d3032d8f227" memberName="controllerDevices"
            virtualName="" explicitFocusOrder="0" pos="10% 35% 60% 10%" editable="0"
            layout="33" items="" textWhenNonSelected="No device selected"
            textWhenNoItems="No devices available"/>
  <COMBOBOX name="" id="fe83d4dd0959ddb3" memberName="outputDevices" virtualName=""
            explicitFocusOrder="0" pos="10% 55% 60% 10%" editable="0" layout="33"
            items="" textWhenNonSelected="No device selected" textWhenNoItems="No devices available"/>
  <LABEL name="new label" id="cc6aee8fa905aeec" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="10% 5% 80% 10%" edTextCol="ff000000"
         edBkgCol="0" labelText="Input device" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="2bf98921779b015a" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="10% 25% 80% 10%" edTextCol="ff000000"
         edBkgCol="0" labelText="Controller device" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="40a9d900bf2cbcc1" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="10% 45% 80% 10%" edTextCol="ff000000"
         edBkgCol="0" labelText="Output device" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="OSC Protocol" id="fd4453150a503c5a" memberName="oscProtocol"
            virtualName="" explicitFocusOrder="0" pos="65% 80% 20% 10%" editable="0"
            layout="33" items="UDP&#10;TCP&#10;SOCKET" textWhenNonSelected="TCP"
            textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="c30076b859684a74" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="10% 65% 80% 10%" edTextCol="ff000000"
         edBkgCol="0" labelText="OSC Server settings" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16" bold="0" italic="0" justification="33"/>
  <LABEL name="OSC Port" id="be4c7f1ba582d0c2" memberName="oscPort" virtualName=""
         explicitFocusOrder="0" pos="25% 80% 30% 10%" tooltip="OSC Port"
         bkgCol="ffffffff" outlineCol="84000000" edTextCol="ff000000"
         edBkgCol="0" labelText="7770" editableSingleClick="1" editableDoubleClick="1"
         focusDiscardsChanges="0" fontname="Default font" fontsize="24"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="8a64ca398a888a94" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="65% 75% 30% 5%" edTextCol="ff000000"
         edBkgCol="0" labelText="Protocol" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="14"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="1304c40e1573016e" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="25% 75% 30% 5%" edTextCol="ff000000"
         edBkgCol="0" labelText="Port/Socket path" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="14" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="OSC Enabled" id="b6fd89ac79c97787" memberName="oscEnabled"
                virtualName="" explicitFocusOrder="0" pos="10% 80% 5% 10%" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="e7f1c930b336318f" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="10% 75% 15% 5%" edTextCol="ff000000"
         edBkgCol="0" labelText="Enable" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="14"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="" id="2378ea7183adb5d1" memberName="inputChannel" virtualName=""
            explicitFocusOrder="0" pos="75% 15% 20% 10%" editable="0" layout="33"
            items="All&#10;1&#10;2&#10;3&#10;4&#10;6&#10;7&#10;8&#10;9&#10;10&#10;11&#10;12&#10;13&#10;14&#10;15&#10;16"
            textWhenNonSelected="All" textWhenNoItems=""/>
  <COMBOBOX name="" id="5001b5562798e961" memberName="controllerChannel"
            virtualName="" explicitFocusOrder="0" pos="75% 35% 20% 10%" editable="0"
            layout="33" items="All&#10;1&#10;2&#10;3&#10;4&#10;6&#10;7&#10;8&#10;9&#10;10&#10;11&#10;12&#10;13&#10;14&#10;15&#10;16"
            textWhenNonSelected="All" textWhenNoItems=""/>
  <COMBOBOX name="" id="2f1d4a52fe45eeaf" memberName="outputChannel" virtualName=""
            explicitFocusOrder="0" pos="75% 55% 20% 10%" editable="0" layout="33"
            items="All&#10;1&#10;2&#10;3&#10;4&#10;6&#10;7&#10;8&#10;9&#10;10&#10;11&#10;12&#10;13&#10;14&#10;15&#10;16"
            textWhenNonSelected="All" textWhenNoItems=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
