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

#include "CtrlrMIDISettingsRouting.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "CtrlrPanel/CtrlrPanel.h"
//[/MiscUserDefs]

//==============================================================================
CtrlrMIDISettingsRouting::CtrlrMIDISettingsRouting (CtrlrPanel &_owner)
    : owner(_owner)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            TRANS("THRU")));

    addAndMakeVisible (inDev2OutDev = new ToggleButton (String::empty));
    inDev2OutDev->setTooltip (TRANS("All messages that are received on the MIDI Input device will be copied to the selected output MIDI Device"));
    inDev2OutDev->setButtonText (TRANS("IN Device  -> OUT Device"));
    inDev2OutDev->addListener (this);

    addAndMakeVisible (ctrlDev2OutDev = new ToggleButton (String::empty));
    ctrlDev2OutDev->setTooltip (TRANS("All messages that are received on the MIDI Controller device will be copied to the selected output MIDI Device"));
    ctrlDev2OutDev->setButtonText (TRANS("CTRL Device -> OUT Device"));
    ctrlDev2OutDev->addListener (this);

    addAndMakeVisible (host2OutDev = new ToggleButton (String::empty));
    host2OutDev->setTooltip (TRANS("All messages received from the plugin HOST, will be copied to the MIDI Output device"));
    host2OutDev->setButtonText (TRANS("HOST -> OUT Device"));
    host2OutDev->addListener (this);

    addAndMakeVisible (host2Host = new ToggleButton (String::empty));
    host2Host->setTooltip (TRANS("All messages received from the plugin HOST, will be copied back to the plugin HOST"));
    host2Host->setButtonText (TRANS("HOST -> HOST"));
    host2Host->addListener (this);

    addAndMakeVisible (inDev2OutDevCh = new ToggleButton ("new toggle button"));
    inDev2OutDevCh->setButtonText (String::empty);
    inDev2OutDevCh->addListener (this);

    addAndMakeVisible (ctrlDev2OutDevCh = new ToggleButton ("new toggle button"));
    ctrlDev2OutDevCh->setButtonText (String::empty);
    ctrlDev2OutDevCh->addListener (this);

    addAndMakeVisible (host2OutDevCh = new ToggleButton ("new toggle button"));
    host2OutDevCh->setButtonText (String::empty);
    host2OutDevCh->addListener (this);

    addAndMakeVisible (host2HostCh = new ToggleButton ("new toggle button"));
    host2HostCh->setButtonText (String::empty);
    host2HostCh->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Change\n"
                                          "MIDI\n"
                                          "Channel")));
    label->setFont (Font (12.00f, Font::plain));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (inDev2Host = new ToggleButton (String::empty));
    inDev2Host->setTooltip (TRANS("All messages that are received on the MIDI Input device will be copied to the plugin HOST"));
    inDev2Host->setButtonText (TRANS("In Device -> Host"));
    inDev2Host->addListener (this);

    addAndMakeVisible (inDev2HostCh = new ToggleButton ("new toggle button"));
    inDev2HostCh->setButtonText (String::empty);
    inDev2HostCh->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 500);


    //[Constructor] You can add your own custom stuff here..
    inDev2OutDev->setToggleState(owner.getProperty(Ids::panelMidiThruD2D), dontSendNotification);
    ctrlDev2OutDev->setToggleState(owner.getProperty(Ids::panelMidiThruC2D), dontSendNotification);
    host2OutDev->setToggleState(owner.getProperty(Ids::panelMidiThruH2D), dontSendNotification);
    host2Host->setToggleState(owner.getProperty(Ids::panelMidiThruH2H), dontSendNotification);
    inDev2Host->setToggleState(owner.getProperty(Ids::panelMidiThruD2H), dontSendNotification);

    inDev2OutDevCh->setToggleState(owner.getProperty(Ids::panelMidiThruD2DChannelize), dontSendNotification);
    ctrlDev2OutDevCh->setToggleState(owner.getProperty(Ids::panelMidiThruC2DChannelize), dontSendNotification);
    host2OutDevCh->setToggleState(owner.getProperty(Ids::panelMidiThruH2DChannelize), dontSendNotification);
    host2HostCh->setToggleState(owner.getProperty(Ids::panelMidiThruH2HChannelize), dontSendNotification);
    inDev2HostCh->setToggleState(owner.getProperty(Ids::panelMidiThruD2HChannelize), dontSendNotification);
    //[/Constructor]
}

CtrlrMIDISettingsRouting::~CtrlrMIDISettingsRouting()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    groupComponent = nullptr;
    inDev2OutDev = nullptr;
    ctrlDev2OutDev = nullptr;
    host2OutDev = nullptr;
    host2Host = nullptr;
    inDev2OutDevCh = nullptr;
    ctrlDev2OutDevCh = nullptr;
    host2OutDevCh = nullptr;
    host2HostCh = nullptr;
    label = nullptr;
    inDev2Host = nullptr;
    inDev2HostCh = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrMIDISettingsRouting::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrMIDISettingsRouting::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    groupComponent->setBounds (proportionOfWidth (0.0500f), proportionOfHeight (0.0200f), proportionOfWidth (0.9000f), proportionOfHeight (0.9560f));
    inDev2OutDev->setBounds (proportionOfWidth (0.1000f), proportionOfHeight (0.2200f), proportionOfWidth (0.6000f), proportionOfHeight (0.1000f));
    ctrlDev2OutDev->setBounds (proportionOfWidth (0.1000f), proportionOfHeight (0.3680f), proportionOfWidth (0.6000f), proportionOfHeight (0.1000f));
    host2OutDev->setBounds (proportionOfWidth (0.1000f), proportionOfHeight (0.5120f), proportionOfWidth (0.6000f), proportionOfHeight (0.1000f));
    host2Host->setBounds (proportionOfWidth (0.1000f), proportionOfHeight (0.6560f), proportionOfWidth (0.6000f), proportionOfHeight (0.1000f));
    inDev2OutDevCh->setBounds (proportionOfWidth (0.8000f), proportionOfHeight (0.2200f), 24, proportionOfHeight (0.1000f));
    ctrlDev2OutDevCh->setBounds (proportionOfWidth (0.8000f), proportionOfHeight (0.3680f), 24, proportionOfHeight (0.1000f));
    host2OutDevCh->setBounds (proportionOfWidth (0.8000f), proportionOfHeight (0.5120f), 24, proportionOfHeight (0.1000f));
    host2HostCh->setBounds (proportionOfWidth (0.8000f), proportionOfHeight (0.6560f), 24, proportionOfHeight (0.1000f));
    label->setBounds (proportionOfWidth (0.7400f), proportionOfHeight (0.0800f), proportionOfWidth (0.1600f), proportionOfHeight (0.1200f));
    inDev2Host->setBounds (proportionOfWidth (0.1000f), proportionOfHeight (0.8000f), proportionOfWidth (0.6000f), proportionOfHeight (0.1000f));
    inDev2HostCh->setBounds (proportionOfWidth (0.8000f), proportionOfHeight (0.8000f), 24, proportionOfHeight (0.1000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CtrlrMIDISettingsRouting::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == inDev2OutDev)
    {
        //[UserButtonCode_inDev2OutDev] -- add your button handler code here..
        owner.setProperty(Ids::panelMidiThruD2D, inDev2OutDev->getToggleState());
        //[/UserButtonCode_inDev2OutDev]
    }
    else if (buttonThatWasClicked == ctrlDev2OutDev)
    {
        //[UserButtonCode_ctrlDev2OutDev] -- add your button handler code here..
        owner.setProperty(Ids::panelMidiThruC2D, ctrlDev2OutDev->getToggleState());
        //[/UserButtonCode_ctrlDev2OutDev]
    }
    else if (buttonThatWasClicked == host2OutDev)
    {
        //[UserButtonCode_host2OutDev] -- add your button handler code here..
        owner.setProperty(Ids::panelMidiThruH2D, host2OutDev->getToggleState());
        //[/UserButtonCode_host2OutDev]
    }
    else if (buttonThatWasClicked == host2Host)
    {
        //[UserButtonCode_host2Host] -- add your button handler code here..
        owner.setProperty(Ids::panelMidiThruH2H, host2Host->getToggleState());
        //[/UserButtonCode_host2Host]
    }
    else if (buttonThatWasClicked == inDev2OutDevCh)
    {
        //[UserButtonCode_inDev2OutDevCh] -- add your button handler code here..
        owner.setProperty(Ids::panelMidiThruD2DChannelize, inDev2OutDevCh->getToggleState());
        //[/UserButtonCode_inDev2OutDevCh]
    }
    else if (buttonThatWasClicked == ctrlDev2OutDevCh)
    {
        //[UserButtonCode_ctrlDev2OutDevCh] -- add your button handler code here..
        owner.setProperty(Ids::panelMidiThruC2DChannelize, ctrlDev2OutDevCh->getToggleState());
        //[/UserButtonCode_ctrlDev2OutDevCh]
    }
    else if (buttonThatWasClicked == host2OutDevCh)
    {
        //[UserButtonCode_host2OutDevCh] -- add your button handler code here..
        owner.setProperty(Ids::panelMidiThruH2DChannelize, host2OutDevCh->getToggleState());
        //[/UserButtonCode_host2OutDevCh]
    }
    else if (buttonThatWasClicked == host2HostCh)
    {
        //[UserButtonCode_host2HostCh] -- add your button handler code here..
        owner.setProperty(Ids::panelMidiThruH2HChannelize, host2HostCh->getToggleState());
        //[/UserButtonCode_host2HostCh]
    }
    else if (buttonThatWasClicked == inDev2Host)
    {
        //[UserButtonCode_inDev2Host] -- add your button handler code here..
        owner.setProperty(Ids::panelMidiThruD2H, inDev2Host->getToggleState());
        //[/UserButtonCode_inDev2Host]
    }
    else if (buttonThatWasClicked == inDev2HostCh)
    {
        //[UserButtonCode_inDev2HostCh] -- add your button handler code here..
        owner.setProperty(Ids::panelMidiThruD2HChannelize, inDev2HostCh->getToggleState());
        //[/UserButtonCode_inDev2HostCh]
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

<JUCER_COMPONENT documentType="Component" className="CtrlrMIDISettingsRouting"
                 componentName="" parentClasses="public Component" constructorParams="CtrlrPanel &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="400"
                 initialHeight="500">
  <BACKGROUND backgroundColour="ffffff"/>
  <GROUPCOMPONENT name="new group" id="f0c3f9ed7e0ffaef" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="5% 2% 90% 95.6%" title="THRU"/>
  <TOGGLEBUTTON name="" id="a01a31a53c31ca7" memberName="inDev2OutDev" virtualName=""
                explicitFocusOrder="0" pos="10% 22% 60% 10%" tooltip="All messages that are received on the MIDI Input device will be copied to the selected output MIDI Device"
                buttonText="IN Device  -&gt; OUT Device" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="" id="bde4fc098e4774c3" memberName="ctrlDev2OutDev" virtualName=""
                explicitFocusOrder="0" pos="10% 36.8% 60% 10%" tooltip="All messages that are received on the MIDI Controller device will be copied to the selected output MIDI Device"
                buttonText="CTRL Device -&gt; OUT Device" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="" id="50a426d1fc912132" memberName="host2OutDev" virtualName=""
                explicitFocusOrder="0" pos="10% 51.2% 60% 10%" tooltip="All messages received from the plugin HOST, will be copied to the MIDI Output device"
                buttonText="HOST -&gt; OUT Device" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="" id="4c954443df1971f4" memberName="host2Host" virtualName=""
                explicitFocusOrder="0" pos="10% 65.6% 60% 10%" tooltip="All messages received from the plugin HOST, will be copied back to the plugin HOST"
                buttonText="HOST -&gt; HOST" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="65314e3c0175f720" memberName="inDev2OutDevCh"
                virtualName="" explicitFocusOrder="0" pos="80% 22% 24 10%" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="e6304756fc4b81d6" memberName="ctrlDev2OutDevCh"
                virtualName="" explicitFocusOrder="0" pos="80% 36.8% 24 10%"
                buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="a120edeacb410007" memberName="host2OutDevCh"
                virtualName="" explicitFocusOrder="0" pos="80% 51.2% 24 10%"
                buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="ef5aa97fd1f39959" memberName="host2HostCh"
                virtualName="" explicitFocusOrder="0" pos="80% 65.6% 24 10%"
                buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <LABEL name="new label" id="8fab92602bf7e160" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="74% 8% 16% 12%" edTextCol="ff000000"
         edBkgCol="0" labelText="Change&#10;MIDI&#10;Channel" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <TOGGLEBUTTON name="" id="56715e270a44bdda" memberName="inDev2Host" virtualName=""
                explicitFocusOrder="0" pos="10% 80% 60% 10%" tooltip="All messages that are received on the MIDI Input device will be copied to the plugin HOST"
                buttonText="In Device -&gt; Host" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="fdf600615f88ffbb" memberName="inDev2HostCh"
                virtualName="" explicitFocusOrder="0" pos="80% 80% 24 10%" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
