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
//[/Headers]

#include "CtrlrProgramWizard.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrProgramWizard::CtrlrProgramWizard ()
{
    addAndMakeVisible (progressStep1 = new HyperlinkButton (TRANS("General information"),
                                                            URL (String::empty)));
    progressStep1->setButtonText (TRANS("General information"));
    progressStep1->setColour (HyperlinkButton::textColourId, Colour (0xcc000000));

    addAndMakeVisible (progressStep2 = new HyperlinkButton (TRANS("Request data"),
                                                            URL (String::empty)));
    progressStep2->setButtonText (TRANS("Request data"));
    progressStep2->setColour (HyperlinkButton::textColourId, Colour (0xcc000000));

    addAndMakeVisible (progressStep3 = new HyperlinkButton (TRANS("Response data"),
                                                            URL (String::empty)));
    progressStep3->setButtonText (TRANS("Response data"));
    progressStep3->setColour (HyperlinkButton::textColourId, Colour (0xcc000000));

    addAndMakeVisible (progressStep4 = new HyperlinkButton (TRANS("Storage format"),
                                                            URL (String::empty)));
    progressStep4->setButtonText (TRANS("Storage format"));
    progressStep4->setColour (HyperlinkButton::textColourId, Colour (0xcc000000));

    addAndMakeVisible (textButton = new TextButton ("new button"));
    textButton->setButtonText (TRANS("Next"));
    textButton->addListener (this);
    textButton->setColour (TextButton::buttonColourId, Colour (0xffbebebe));

    addAndMakeVisible (textButton2 = new TextButton ("new button"));
    textButton2->setButtonText (TRANS("Previous"));
    textButton2->addListener (this);
    textButton2->setColour (TextButton::buttonColourId, Colour (0xffbebebe));

    addAndMakeVisible (textButton3 = new TextButton ("new button"));
    textButton3->setButtonText (TRANS("Execute"));
    textButton3->addListener (this);
    textButton3->setColour (TextButton::buttonColourId, Colour (0xffbebebe));


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

    progressStep1 = nullptr;
    progressStep2 = nullptr;
    progressStep3 = nullptr;
    progressStep4 = nullptr;
    textButton = nullptr;
    textButton2 = nullptr;
    textButton3 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrProgramWizard::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colour (0xff81acc3));
    g.fillRect (0, 0, proportionOfWidth (0.2500f), getHeight() - 0);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrProgramWizard::resized()
{
    progressStep1->setBounds (16, 16, proportionOfWidth (0.2000f), 24);
    progressStep2->setBounds (16, 56, proportionOfWidth (0.2000f), 24);
    progressStep3->setBounds (16, 96, proportionOfWidth (0.2000f), 24);
    progressStep4->setBounds (16, 136, proportionOfWidth (0.2000f), 24);
    textButton->setBounds (688, 552, 95, 32);
    textButton2->setBounds (480, 552, 95, 32);
    textButton3->setBounds (584, 552, 95, 32);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CtrlrProgramWizard::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == textButton)
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
        //[/UserButtonCode_textButton]
    }
    else if (buttonThatWasClicked == textButton2)
    {
        //[UserButtonCode_textButton2] -- add your button handler code here..
        //[/UserButtonCode_textButton2]
    }
    else if (buttonThatWasClicked == textButton3)
    {
        //[UserButtonCode_textButton3] -- add your button handler code here..
        //[/UserButtonCode_textButton3]
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
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="800" initialHeight="600">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 0 25% 0M" fill="solid: ff81acc3" hasStroke="0"/>
  </BACKGROUND>
  <HYPERLINKBUTTON name="" id="23e6c13cc7c72353" memberName="progressStep1" virtualName=""
                   explicitFocusOrder="0" pos="16 16 20% 24" textCol="cc000000"
                   buttonText="General information" connectedEdges="0" needsCallback="0"
                   radioGroupId="0" url=""/>
  <HYPERLINKBUTTON name="" id="ff5fc3bd9eb903f1" memberName="progressStep2" virtualName=""
                   explicitFocusOrder="0" pos="16 56 20% 24" textCol="cc000000"
                   buttonText="Request data" connectedEdges="0" needsCallback="0"
                   radioGroupId="0" url=""/>
  <HYPERLINKBUTTON name="" id="b9e86467d1ef2d14" memberName="progressStep3" virtualName=""
                   explicitFocusOrder="0" pos="16 96 20% 24" textCol="cc000000"
                   buttonText="Response data" connectedEdges="0" needsCallback="0"
                   radioGroupId="0" url=""/>
  <HYPERLINKBUTTON name="" id="e5756d456645b4fb" memberName="progressStep4" virtualName=""
                   explicitFocusOrder="0" pos="16 136 20% 24" textCol="cc000000"
                   buttonText="Storage format" connectedEdges="0" needsCallback="0"
                   radioGroupId="0" url=""/>
  <TEXTBUTTON name="new button" id="f94a26109cc16d12" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="688 552 95 32" bgColOff="ffbebebe"
              buttonText="Next" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="71f9c8dad3d1ac" memberName="textButton2"
              virtualName="" explicitFocusOrder="0" pos="480 552 95 32" bgColOff="ffbebebe"
              buttonText="Previous" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="e658577ed337b9cb" memberName="textButton3"
              virtualName="" explicitFocusOrder="0" pos="584 552 95 32" bgColOff="ffbebebe"
              buttonText="Execute" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
