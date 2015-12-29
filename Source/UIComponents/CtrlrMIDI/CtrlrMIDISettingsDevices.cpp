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

//[Headers] You can add your own extra header files here...
#include "stdafx.h"
//[/Headers]

#include "CtrlrMIDISettingsDevices.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "MIDI/CtrlrMIDIDeviceManager.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrMacros.h"
//[/MiscUserDefs]

//==============================================================================
CtrlrMIDISettingsDevices::CtrlrMIDISettingsDevices (CtrlrPanel &_owner)
    : owner(_owner)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (inputDevices = new ComboBox (String()));
    inputDevices->setEditableText (false);
    inputDevices->setJustificationType (Justification::centredLeft);
    inputDevices->setTextWhenNothingSelected (TRANS("No device selected"));
    inputDevices->setTextWhenNoChoicesAvailable (TRANS("No devices available"));
    inputDevices->addListener (this);

    addAndMakeVisible (controllerDevices = new ComboBox (String()));
    controllerDevices->setEditableText (false);
    controllerDevices->setJustificationType (Justification::centredLeft);
    controllerDevices->setTextWhenNothingSelected (TRANS("No device selected"));
    controllerDevices->setTextWhenNoChoicesAvailable (TRANS("No devices available"));
    controllerDevices->addListener (this);

    addAndMakeVisible (outputDevices = new ComboBox (String()));
    outputDevices->setEditableText (false);
    outputDevices->setJustificationType (Justification::centredLeft);
    outputDevices->setTextWhenNothingSelected (TRANS("No device selected"));
    outputDevices->setTextWhenNoChoicesAvailable (TRANS("No devices available"));
    outputDevices->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Input device")));
    label->setFont (Font (16.00f, Font::bold));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Controller device")));
    label2->setFont (Font (16.00f, Font::bold));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Output device")));
    label3->setFont (Font (16.00f, Font::bold));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (oscProtocol = new ComboBox ("OSC Protocol"));
    oscProtocol->setEditableText (false);
    oscProtocol->setJustificationType (Justification::centredLeft);
    oscProtocol->setTextWhenNothingSelected (TRANS("TCP"));
    oscProtocol->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    oscProtocol->addItem (TRANS("Default"), 1);
    oscProtocol->addItem (TRANS("UDP"), 2);
    oscProtocol->addItem (TRANS("Local/UNIX"), 3);
    oscProtocol->addItem (TRANS("TCP"), 4);
    oscProtocol->addListener (this);

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("OSC Server settings")));
    label4->setFont (Font (16.00f, Font::bold));
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
    oscEnabled->setButtonText (String());
    oscEnabled->addListener (this);

    addAndMakeVisible (label7 = new Label ("new label",
                                           TRANS("Enable")));
    label7->setFont (Font (14.00f, Font::plain));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (inputChannel = new ComboBox (String()));
    inputChannel->setEditableText (false);
    inputChannel->setJustificationType (Justification::centredLeft);
    inputChannel->setTextWhenNothingSelected (TRANS("All"));
    inputChannel->setTextWhenNoChoicesAvailable (String());
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

    addAndMakeVisible (controllerChannel = new ComboBox (String()));
    controllerChannel->setEditableText (false);
    controllerChannel->setJustificationType (Justification::centredLeft);
    controllerChannel->setTextWhenNothingSelected (TRANS("All"));
    controllerChannel->setTextWhenNoChoicesAvailable (String());
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

    addAndMakeVisible (outputChannel = new ComboBox (String()));
    outputChannel->setEditableText (false);
    outputChannel->setJustificationType (Justification::centredLeft);
    outputChannel->setTextWhenNothingSelected (TRANS("All"));
    outputChannel->setTextWhenNoChoicesAvailable (String());
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

    addAndMakeVisible (label8 = new Label ("new label",
                                           TRANS("Plugin")));
    label8->setFont (Font (16.00f, Font::bold));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (pluginOutputChannel = new ComboBox (String()));
    pluginOutputChannel->setEditableText (false);
    pluginOutputChannel->setJustificationType (Justification::centredLeft);
    pluginOutputChannel->setTextWhenNothingSelected (TRANS("All"));
    pluginOutputChannel->setTextWhenNoChoicesAvailable (String());
    pluginOutputChannel->addItem (TRANS("All"), 1);
    pluginOutputChannel->addItem (TRANS("1"), 2);
    pluginOutputChannel->addItem (TRANS("2"), 3);
    pluginOutputChannel->addItem (TRANS("3"), 4);
    pluginOutputChannel->addItem (TRANS("4"), 5);
    pluginOutputChannel->addItem (TRANS("6"), 6);
    pluginOutputChannel->addItem (TRANS("7"), 7);
    pluginOutputChannel->addItem (TRANS("8"), 8);
    pluginOutputChannel->addItem (TRANS("9"), 9);
    pluginOutputChannel->addItem (TRANS("10"), 10);
    pluginOutputChannel->addItem (TRANS("11"), 11);
    pluginOutputChannel->addItem (TRANS("12"), 12);
    pluginOutputChannel->addItem (TRANS("13"), 13);
    pluginOutputChannel->addItem (TRANS("14"), 14);
    pluginOutputChannel->addItem (TRANS("15"), 15);
    pluginOutputChannel->addItem (TRANS("16"), 16);
    pluginOutputChannel->addListener (this);

    addAndMakeVisible (pluginOutput = new ToggleButton ("new toggle button"));
    pluginOutput->setButtonText (TRANS("Enable output to plugin host"));
    pluginOutput->addListener (this);

    addAndMakeVisible (label9 = new Label ("new label",
                                           TRANS("MIDI Channel")));
    label9->setFont (Font (16.00f, Font::bold));
    label9->setJustificationType (Justification::centredLeft);
    label9->setEditable (false, false, false);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (pluginInput = new ToggleButton ("new toggle button"));
    pluginInput->setButtonText (TRANS("Enable input from plugin host"));
    pluginInput->addListener (this);

    addAndMakeVisible (pluginInputChannel = new ComboBox (String()));
    pluginInputChannel->setEditableText (false);
    pluginInputChannel->setJustificationType (Justification::centredLeft);
    pluginInputChannel->setTextWhenNothingSelected (TRANS("All"));
    pluginInputChannel->setTextWhenNoChoicesAvailable (String());
    pluginInputChannel->addItem (TRANS("All"), 1);
    pluginInputChannel->addItem (TRANS("1"), 2);
    pluginInputChannel->addItem (TRANS("2"), 3);
    pluginInputChannel->addItem (TRANS("3"), 4);
    pluginInputChannel->addItem (TRANS("4"), 5);
    pluginInputChannel->addItem (TRANS("6"), 6);
    pluginInputChannel->addItem (TRANS("7"), 7);
    pluginInputChannel->addItem (TRANS("8"), 8);
    pluginInputChannel->addItem (TRANS("9"), 9);
    pluginInputChannel->addItem (TRANS("10"), 10);
    pluginInputChannel->addItem (TRANS("11"), 11);
    pluginInputChannel->addItem (TRANS("12"), 12);
    pluginInputChannel->addItem (TRANS("13"), 13);
    pluginInputChannel->addItem (TRANS("14"), 14);
    pluginInputChannel->addItem (TRANS("15"), 15);
    pluginInputChannel->addItem (TRANS("16"), 16);
    pluginInputChannel->addListener (this);


    //[UserPreSize]
    oscProtocol->clear();
    oscProtocol->addItem (TRANS("Default"), 1);
    oscProtocol->addItem (TRANS("UDP"), 2);
    oscProtocol->addItem (TRANS("Local/UNIX"), 3);
    oscProtocol->addItem (TRANS("TCP"), 5);
    //[/UserPreSize]

    setSize (400, 500);


    //[Constructor] You can add your own custom stuff here..
    owner.getCtrlrManagerOwner().getCtrlrMidiDeviceManager().reloadComboContents (*inputDevices, inputDevice, &owner);
    owner.getCtrlrManagerOwner().getCtrlrMidiDeviceManager().reloadComboContents (*controllerDevices, controllerDevice, &owner);
    owner.getCtrlrManagerOwner().getCtrlrMidiDeviceManager().reloadComboContents (*outputDevices, outputDevice, &owner);
    oscEnabled->setToggleState (owner.getProperty(Ids::panelOSCEnabled), dontSendNotification);
    oscPort->setText (owner.getProperty(Ids::panelOSCPort), dontSendNotification);
    oscProtocol->setSelectedItemIndex(owner.getProperty(Ids::panelOSCProtocol), dontSendNotification);
    inputChannel->setText (owner.getProperty(Ids::panelMidiInputChannelDevice), dontSendNotification);
    outputChannel->setText (owner.getProperty(Ids::panelMidiOutputChannelDevice), dontSendNotification);
    controllerChannel->setText (owner.getProperty(Ids::panelMidiControllerChannelDevice), dontSendNotification);
    pluginOutputChannel->setText (owner.getProperty(Ids::panelMidiOutputChannelHost), dontSendNotification);
    pluginInputChannel->setText (owner.getProperty(Ids::panelMidiInputChannelHost), dontSendNotification);
    pluginOutput->setToggleState (owner.getProperty(Ids::panelMidiOutputToHost), dontSendNotification);
    pluginInput->setToggleState (owner.getProperty(Ids::panelMidiInputFromHost), dontSendNotification);
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
    label8 = nullptr;
    pluginOutputChannel = nullptr;
    pluginOutput = nullptr;
    label9 = nullptr;
    pluginInput = nullptr;
    pluginInputChannel = nullptr;


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

    inputDevices->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.1109f), proportionOfWidth (0.6004f), proportionOfHeight (0.0597f));
    controllerDevices->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.2409f), proportionOfWidth (0.6004f), proportionOfHeight (0.0597f));
    outputDevices->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.3689f), proportionOfWidth (0.6004f), proportionOfHeight (0.0597f));
    label->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.0490f), proportionOfWidth (0.6004f), proportionOfHeight (0.0597f));
    label2->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.1770f), proportionOfWidth (0.7992f), proportionOfHeight (0.0597f));
    label3->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.3028f), proportionOfWidth (0.7992f), proportionOfHeight (0.0597f));
    oscProtocol->setBounds (proportionOfWidth (0.6305f), proportionOfHeight (0.8614f), proportionOfWidth (0.2008f), proportionOfHeight (0.0810f));
    label4->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.7313f), proportionOfWidth (0.7992f), proportionOfHeight (0.0810f));
    oscPort->setBounds (proportionOfWidth (0.2309f), proportionOfHeight (0.8614f), proportionOfWidth (0.2992f), proportionOfHeight (0.0810f));
    label5->setBounds (proportionOfWidth (0.6305f), proportionOfHeight (0.8124f), proportionOfWidth (0.2992f), proportionOfHeight (0.0490f));
    label6->setBounds (proportionOfWidth (0.2309f), proportionOfHeight (0.8124f), proportionOfWidth (0.2992f), proportionOfHeight (0.0490f));
    oscEnabled->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.8614f), proportionOfWidth (0.0502f), proportionOfHeight (0.0810f));
    label7->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.8124f), proportionOfWidth (0.1506f), proportionOfHeight (0.0490f));
    inputChannel->setBounds (proportionOfWidth (0.7410f), proportionOfHeight (0.1109f), proportionOfWidth (0.2008f), proportionOfHeight (0.0597f));
    controllerChannel->setBounds (proportionOfWidth (0.7410f), proportionOfHeight (0.2409f), proportionOfWidth (0.2008f), proportionOfHeight (0.0597f));
    outputChannel->setBounds (proportionOfWidth (0.7410f), proportionOfHeight (0.3689f), proportionOfWidth (0.2008f), proportionOfHeight (0.0597f));
    label8->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.4307f), proportionOfWidth (0.7992f), proportionOfHeight (0.0597f));
    pluginOutputChannel->setBounds (proportionOfWidth (0.7410f), proportionOfHeight (0.4968f), proportionOfWidth (0.2008f), proportionOfHeight (0.0597f));
    pluginOutput->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.4968f), proportionOfWidth (0.6004f), proportionOfHeight (0.0597f));
    label9->setBounds (proportionOfWidth (0.7209f), proportionOfHeight (0.0490f), proportionOfWidth (0.2410f), proportionOfHeight (0.0597f));
    pluginInput->setBounds (proportionOfWidth (0.0803f), proportionOfHeight (0.6226f), proportionOfWidth (0.6004f), proportionOfHeight (0.0597f));
    pluginInputChannel->setBounds (proportionOfWidth (0.7410f), proportionOfHeight (0.6226f), proportionOfWidth (0.2008f), proportionOfHeight (0.0597f));
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
        owner.setProperty(Ids::panelMidiInputChannelDevice, inputChannel->getText());
        //[/UserComboBoxCode_inputChannel]
    }
    else if (comboBoxThatHasChanged == controllerChannel)
    {
        //[UserComboBoxCode_controllerChannel] -- add your combo box handling code here..
        owner.setProperty(Ids::panelMidiControllerChannelDevice, controllerChannel->getText());
        //[/UserComboBoxCode_controllerChannel]
    }
    else if (comboBoxThatHasChanged == outputChannel)
    {
        //[UserComboBoxCode_outputChannel] -- add your combo box handling code here..
        owner.setProperty(Ids::panelMidiOutputChannelDevice, outputChannel->getText());
        //[/UserComboBoxCode_outputChannel]
    }
    else if (comboBoxThatHasChanged == pluginOutputChannel)
    {
        //[UserComboBoxCode_pluginOutputChannel] -- add your combo box handling code here..
        owner.setProperty(Ids::panelMidiOutputChannelHost, pluginOutputChannel->getText());
        //[/UserComboBoxCode_pluginOutputChannel]
    }
    else if (comboBoxThatHasChanged == pluginInputChannel)
    {
        //[UserComboBoxCode_pluginInputChannel] -- add your combo box handling code here..
        owner.setProperty(Ids::panelMidiInputChannelHost, pluginInputChannel->getText());
        //[/UserComboBoxCode_pluginInputChannel]
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
    else if (buttonThatWasClicked == pluginOutput)
    {
        //[UserButtonCode_pluginOutput] -- add your button handler code here..
        owner.setProperty(Ids::panelMidiOutputToHost, pluginOutput->getToggleState());
        //[/UserButtonCode_pluginOutput]
    }
    else if (buttonThatWasClicked == pluginInput)
    {
        //[UserButtonCode_pluginInput] -- add your button handler code here..
        owner.setProperty(Ids::panelMidiInputFromHost, pluginInput->getToggleState());
        //[/UserButtonCode_pluginInput]
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
                 initialHeight="500">
  <BACKGROUND backgroundColour="ffffff"/>
  <COMBOBOX name="" id="da3c6f7ecddc5352" memberName="inputDevices" virtualName=""
            explicitFocusOrder="0" pos="8% 11% 60% 6%" editable="0" layout="33"
            items="" textWhenNonSelected="No device selected" textWhenNoItems="No devices available"/>
  <COMBOBOX name="" id="a94f1d3032d8f227" memberName="controllerDevices"
            virtualName="" explicitFocusOrder="0" pos="8% 24% 60% 6%" editable="0"
            layout="33" items="" textWhenNonSelected="No device selected"
            textWhenNoItems="No devices available"/>
  <COMBOBOX name="" id="fe83d4dd0959ddb3" memberName="outputDevices" virtualName=""
            explicitFocusOrder="0" pos="8% 36.8% 60% 6%" editable="0" layout="33"
            items="" textWhenNonSelected="No device selected" textWhenNoItems="No devices available"/>
  <LABEL name="new label" id="cc6aee8fa905aeec" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="8% 5% 60% 6%" edTextCol="ff000000"
         edBkgCol="0" labelText="Input device" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16" bold="1" italic="0" justification="33"/>
  <LABEL name="new label" id="2bf98921779b015a" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="8% 17.6% 80% 6%" edTextCol="ff000000"
         edBkgCol="0" labelText="Controller device" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16" bold="1" italic="0" justification="33"/>
  <LABEL name="new label" id="40a9d900bf2cbcc1" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="8% 30.2% 80% 6%" edTextCol="ff000000"
         edBkgCol="0" labelText="Output device" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16" bold="1" italic="0" justification="33"/>
  <COMBOBOX name="OSC Protocol" id="fd4453150a503c5a" memberName="oscProtocol"
            virtualName="" explicitFocusOrder="0" pos="63% 86.2% 20% 8.2%"
            editable="0" layout="33" items="Default&#10;UDP&#10;Local/UNIX&#10;TCP"
            textWhenNonSelected="TCP" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="c30076b859684a74" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="8% 73.2% 80% 8.2%" edTextCol="ff000000"
         edBkgCol="0" labelText="OSC Server settings" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16" bold="1" italic="0" justification="33"/>
  <LABEL name="OSC Port" id="be4c7f1ba582d0c2" memberName="oscPort" virtualName=""
         explicitFocusOrder="0" pos="23% 86.2% 30% 8.2%" tooltip="OSC Port"
         bkgCol="ffffffff" outlineCol="84000000" edTextCol="ff000000"
         edBkgCol="0" labelText="7770" editableSingleClick="1" editableDoubleClick="1"
         focusDiscardsChanges="0" fontname="Default font" fontsize="24"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="8a64ca398a888a94" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="63% 81.2% 30% 5%" edTextCol="ff000000"
         edBkgCol="0" labelText="Protocol" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="14"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="1304c40e1573016e" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="23% 81.2% 30% 5%" edTextCol="ff000000"
         edBkgCol="0" labelText="Port/Socket path" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="14" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="OSC Enabled" id="b6fd89ac79c97787" memberName="oscEnabled"
                virtualName="" explicitFocusOrder="0" pos="8% 86.2% 5% 8.2%"
                buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <LABEL name="new label" id="e7f1c930b336318f" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="8% 81.2% 15% 5%" edTextCol="ff000000"
         edBkgCol="0" labelText="Enable" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="14"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="" id="2378ea7183adb5d1" memberName="inputChannel" virtualName=""
            explicitFocusOrder="0" pos="74% 11% 20% 6%" editable="0" layout="33"
            items="All&#10;1&#10;2&#10;3&#10;4&#10;6&#10;7&#10;8&#10;9&#10;10&#10;11&#10;12&#10;13&#10;14&#10;15&#10;16"
            textWhenNonSelected="All" textWhenNoItems=""/>
  <COMBOBOX name="" id="5001b5562798e961" memberName="controllerChannel"
            virtualName="" explicitFocusOrder="0" pos="74% 24% 20% 6%" editable="0"
            layout="33" items="All&#10;1&#10;2&#10;3&#10;4&#10;6&#10;7&#10;8&#10;9&#10;10&#10;11&#10;12&#10;13&#10;14&#10;15&#10;16"
            textWhenNonSelected="All" textWhenNoItems=""/>
  <COMBOBOX name="" id="2f1d4a52fe45eeaf" memberName="outputChannel" virtualName=""
            explicitFocusOrder="0" pos="74% 36.8% 20% 6%" editable="0" layout="33"
            items="All&#10;1&#10;2&#10;3&#10;4&#10;6&#10;7&#10;8&#10;9&#10;10&#10;11&#10;12&#10;13&#10;14&#10;15&#10;16"
            textWhenNonSelected="All" textWhenNoItems=""/>
  <LABEL name="new label" id="7ff152d672197d06" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="8% 43% 80% 6%" edTextCol="ff000000"
         edBkgCol="0" labelText="Plugin" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="16"
         bold="1" italic="0" justification="33"/>
  <COMBOBOX name="" id="d68abf2ee6c44107" memberName="pluginOutputChannel"
            virtualName="" explicitFocusOrder="0" pos="74% 49.6% 20% 6%"
            editable="0" layout="33" items="All&#10;1&#10;2&#10;3&#10;4&#10;6&#10;7&#10;8&#10;9&#10;10&#10;11&#10;12&#10;13&#10;14&#10;15&#10;16"
            textWhenNonSelected="All" textWhenNoItems=""/>
  <TOGGLEBUTTON name="new toggle button" id="713d217ca3a249f0" memberName="pluginOutput"
                virtualName="" explicitFocusOrder="0" pos="8% 49.6% 60% 6%" buttonText="Enable output to plugin host"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="7473888a1a01c9bd" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="72% 5% 24% 6%" edTextCol="ff000000"
         edBkgCol="0" labelText="MIDI Channel" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16" bold="1" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="6fba4b4ff826953e" memberName="pluginInput"
                virtualName="" explicitFocusOrder="0" pos="8% 62.2% 60% 6%" buttonText="Enable input from plugin host"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <COMBOBOX name="" id="67cc1acb3d5737ac" memberName="pluginInputChannel"
            virtualName="" explicitFocusOrder="0" pos="74% 62.2% 20% 6%"
            editable="0" layout="33" items="All&#10;1&#10;2&#10;3&#10;4&#10;6&#10;7&#10;8&#10;9&#10;10&#10;11&#10;12&#10;13&#10;14&#10;15&#10;16"
            textWhenNonSelected="All" textWhenNoItems=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
