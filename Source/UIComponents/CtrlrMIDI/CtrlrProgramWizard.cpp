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
//[/Headers]

#include "CtrlrProgramWizard.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrProgramWizard::CtrlrProgramWizard ()
{
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

    addAndMakeVisible (label = new Label ("step_1",
                                          TRANS("General information")));
    label->setFont (Font (16.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("step_2",
                                           TRANS("General information")));
    label2->setFont (Font (16.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label3 = new Label ("step_3",
                                           TRANS("General information")));
    label3->setFont (Font (16.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label4 = new Label ("step_4",
                                           TRANS("General information")));
    label4->setFont (Font (16.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label5 = new Label ("step_5",
                                           TRANS("General information")));
    label5->setFont (Font (16.00f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (content = new Viewport (String::empty));
    content->setScrollBarsShown (false, false);
    content->setScrollBarThickness (16);


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

    textButton = nullptr;
    textButton2 = nullptr;
    textButton3 = nullptr;
    label = nullptr;
    label2 = nullptr;
    label3 = nullptr;
    label4 = nullptr;
    label5 = nullptr;
    content = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrProgramWizard::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0xff81acc3));
    g.fillRect (0, 0, proportionOfWidth (0.2500f), getHeight() - 0);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrProgramWizard::resized()
{
    textButton->setBounds (proportionOfWidth (0.8600f), proportionOfHeight (0.9200f), proportionOfWidth (0.1200f), proportionOfHeight (0.0500f));
    textButton2->setBounds (proportionOfWidth (0.6000f), proportionOfHeight (0.9200f), proportionOfWidth (0.1200f), proportionOfHeight (0.0500f));
    textButton3->setBounds (proportionOfWidth (0.7300f), proportionOfHeight (0.9200f), proportionOfWidth (0.1200f), proportionOfHeight (0.0500f));
    label->setBounds (proportionOfWidth (0.0500f), 16, proportionOfWidth (0.2000f), 32);
    label2->setBounds (proportionOfWidth (0.0500f), 56, proportionOfWidth (0.2000f), 32);
    label3->setBounds (proportionOfWidth (0.0500f), 96, proportionOfWidth (0.2000f), 32);
    label4->setBounds (proportionOfWidth (0.0500f), 136, proportionOfWidth (0.2000f), 32);
    label5->setBounds (proportionOfWidth (0.0500f), 176, proportionOfWidth (0.2000f), 32);
    content->setBounds (proportionOfWidth (0.2500f), 0, proportionOfWidth (0.7500f), proportionOfHeight (0.9000f));
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
  <BACKGROUND backgroundColour="0">
    <RECT pos="0 0 25% 0M" fill="solid: ff81acc3" hasStroke="0"/>
  </BACKGROUND>
  <TEXTBUTTON name="new button" id="f94a26109cc16d12" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="86% 92% 12% 5%" bgColOff="ffbebebe"
              buttonText="Next" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="71f9c8dad3d1ac" memberName="textButton2"
              virtualName="" explicitFocusOrder="0" pos="60% 92% 12% 5%" bgColOff="ffbebebe"
              buttonText="Previous" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="e658577ed337b9cb" memberName="textButton3"
              virtualName="" explicitFocusOrder="0" pos="73% 92% 12% 5%" bgColOff="ffbebebe"
              buttonText="Execute" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="step_1" id="55f638b6ae64bf74" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="5% 16 20% 32" edTextCol="ff000000"
         edBkgCol="0" labelText="General information" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16" bold="0" italic="0" justification="33"/>
  <LABEL name="step_2" id="6cdd85436df42ec0" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="5% 56 20% 32" edTextCol="ff000000"
         edBkgCol="0" labelText="General information" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16" bold="0" italic="0" justification="33"/>
  <LABEL name="step_3" id="2ca013796ad158d3" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="5% 96 20% 32" edTextCol="ff000000"
         edBkgCol="0" labelText="General information" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16" bold="0" italic="0" justification="33"/>
  <LABEL name="step_4" id="ad881dca9522f695" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="5% 136 20% 32" edTextCol="ff000000"
         edBkgCol="0" labelText="General information" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16" bold="0" italic="0" justification="33"/>
  <LABEL name="step_5" id="ffde037166dfb368" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="5% 176 20% 32" edTextCol="ff000000"
         edBkgCol="0" labelText="General information" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16" bold="0" italic="0" justification="33"/>
  <VIEWPORT name="" id="7365944102f64de9" memberName="content" virtualName=""
            explicitFocusOrder="0" pos="25% 0 75% 90%" vscroll="0" hscroll="0"
            scrollbarThickness="16" contentType="0" jucerFile="" contentClass=""
            constructorParams=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
