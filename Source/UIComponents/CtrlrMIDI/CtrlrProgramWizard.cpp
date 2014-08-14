/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "stdafx.h"
#include "CtrlrApplicationWindow/CtrlrEditor.h"
//[/Headers]

#include "CtrlrProgramWizard.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrProgramWizard::CtrlrProgramWizard (CtrlrEditor &_owner)
    : owner(_owner)
{
    addAndMakeVisible (executeButton = new TextButton (String::empty));
    executeButton->setButtonText (TRANS("Execute"));
    executeButton->addListener (this);
    executeButton->setColour (TextButton::buttonColourId, Colours::lightgrey);

    addAndMakeVisible (inputMonitor = new CtrlrProgramWizardMonitor (*this));
    addAndMakeVisible (outputMonitor = new CtrlrProgramWizardMonitor (*this));

    //[UserPreSize]
    //[/UserPreSize]

    setSize (800, 600);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrProgramWizard::~CtrlrProgramWizard()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    executeButton = nullptr;
    inputMonitor = nullptr;
    outputMonitor = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrProgramWizard::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    g.fillCheckerBoard (getBounds(), 24, 24, Colours::lightgrey, Colours::grey);
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrProgramWizard::resized()
{
    executeButton->setBounds (proportionOfWidth (0.8500f), proportionOfHeight (0.9333f), proportionOfWidth (0.1200f), proportionOfHeight (0.0500f));
    inputMonitor->setBounds (proportionOfWidth (0.0100f), proportionOfHeight (0.7733f), proportionOfWidth (0.9700f), proportionOfHeight (0.1500f));
    outputMonitor->setBounds (proportionOfWidth (0.0100f), proportionOfHeight (0.6133f), proportionOfWidth (0.9700f), proportionOfHeight (0.1500f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CtrlrProgramWizard::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == executeButton)
    {
        //[UserButtonCode_executeButton] -- add your button handler code here..
        //[/UserButtonCode_executeButton]
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

<JUCER_COMPONENT documentType="Component" className="CtrlrProgramWizard" componentName=""
                 parentClasses="public Component" constructorParams="CtrlrEditor &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="800"
                 initialHeight="600">
  <BACKGROUND backgroundColour="0"/>
  <TEXTBUTTON name="" id="e658577ed337b9cb" memberName="executeButton" virtualName=""
              explicitFocusOrder="0" pos="85% 93.333% 12% 5%" bgColOff="ffd3d3d3"
              buttonText="Execute" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <JUCERCOMP name="" id="726b33ebe78c8c44" memberName="inputMonitor" virtualName=""
             explicitFocusOrder="0" pos="1% 77.333% 97% 15%" sourceFile="CtrlrProgramWizardMonitor.cpp"
             constructorParams="*this"/>
  <JUCERCOMP name="" id="e43d943270cd3a2" memberName="outputMonitor" virtualName=""
             explicitFocusOrder="0" pos="1% 61.333% 97% 15%" sourceFile="CtrlrProgramWizardMonitor.cpp"
             constructorParams="*this"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
