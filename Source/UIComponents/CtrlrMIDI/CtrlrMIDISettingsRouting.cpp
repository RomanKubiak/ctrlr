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
//[/MiscUserDefs]

//==============================================================================
CtrlrMIDISettingsRouting::CtrlrMIDISettingsRouting (CtrlrPanel &_owner)
    : owner(_owner)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            TRANS("THRU")));

    addAndMakeVisible (inDev2outDev = new ToggleButton (String::empty));
    inDev2outDev->setButtonText (TRANS("IN Device  -> OUT Device"));
    inDev2outDev->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrMIDISettingsRouting::~CtrlrMIDISettingsRouting()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    groupComponent = nullptr;
    inDev2outDev = nullptr;


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

    groupComponent->setBounds (proportionOfWidth (0.0500f), proportionOfHeight (0.0500f), proportionOfWidth (0.9000f), proportionOfHeight (0.5000f));
    inDev2outDev->setBounds (proportionOfWidth (0.1000f), proportionOfHeight (0.1000f), proportionOfWidth (0.8000f), proportionOfHeight (0.1000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CtrlrMIDISettingsRouting::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == inDev2outDev)
    {
        //[UserButtonCode_inDev2outDev] -- add your button handler code here..
        //[/UserButtonCode_inDev2outDev]
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
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffff"/>
  <GROUPCOMPONENT name="new group" id="f0c3f9ed7e0ffaef" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="5% 5% 90% 50%" title="THRU"/>
  <TOGGLEBUTTON name="" id="a01a31a53c31ca7" memberName="inDev2outDev" virtualName=""
                explicitFocusOrder="0" pos="10% 10% 80% 10%" buttonText="IN Device  -&gt; OUT Device"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
