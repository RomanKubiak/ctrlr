#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  2 May 2012 3:20:53pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "CtrlrSysExFormulaEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrSysExFormulaEditor::CtrlrSysExFormulaEditor ()
    : forwardFormula (0),
      reverseFormula (0),
      forwardLabel (0),
      reverseLabel (0),
      label (0)
{
    addAndMakeVisible (forwardFormula = new CodeEditorComponent (forwardFormulaDocument, 0));

    addAndMakeVisible (reverseFormula = new CodeEditorComponent (reverseFormulaDocument, 0));

    addAndMakeVisible (forwardLabel = new Label (L"forwardLabel",
                                                 L"Forward"));
    forwardLabel->setFont (Font (16.0000f, Font::plain));
    forwardLabel->setJustificationType (Justification::centredLeft);
    forwardLabel->setEditable (false, false, false);
    forwardLabel->setColour (TextEditor::textColourId, Colours::black);
    forwardLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (reverseLabel = new Label (L"reverseLabel",
                                                 L"Reverse"));
    reverseLabel->setFont (Font (16.0000f, Font::plain));
    reverseLabel->setJustificationType (Justification::centredLeft);
    reverseLabel->setEditable (false, false, false);
    reverseLabel->setColour (TextEditor::textColourId, Colours::black);
    reverseLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label = new Label (L"new label",
                                          L"SysEx Formula ()"));
    label->setFont (Font (24.0000f, Font::plain));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x0));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrSysExFormulaEditor::~CtrlrSysExFormulaEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (forwardFormula);
    deleteAndZero (reverseFormula);
    deleteAndZero (forwardLabel);
    deleteAndZero (reverseLabel);
    deleteAndZero (label);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrSysExFormulaEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrSysExFormulaEditor::resized()
{
    forwardFormula->setBounds (0, (32) + (16), getWidth() - 0, proportionOfHeight (0.4200f));
    reverseFormula->setBounds (0, (((32) + (16)) + (proportionOfHeight (0.4200f))) + (16), getWidth() - 0, proportionOfHeight (0.4200f));
    forwardLabel->setBounds (0, 32, getWidth() - 0, 16);
    reverseLabel->setBounds (0, ((32) + (16)) + (proportionOfHeight (0.4200f)), getWidth() - 0, 16);
    label->setBounds (0, 0, getWidth() - 0, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrSysExFormulaEditor"
                 componentName="" parentClasses="public Component" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330000013" fixedSize="1" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffff"/>
  <GENERICCOMPONENT name="" id="38d02d38be9fbd84" memberName="forwardFormula" virtualName=""
                    explicitFocusOrder="0" pos="0 0R 0M 42%" posRelativeY="773714c115d14957"
                    class="CodeEditorComponent" params="forwardFormulaDocument, 0"/>
  <GENERICCOMPONENT name="" id="d04b58999ff1dc0f" memberName="reverseFormula" virtualName=""
                    explicitFocusOrder="0" pos="0 0R 0M 42%" posRelativeY="6bf7e0e89437db37"
                    class="CodeEditorComponent" params="reverseFormulaDocument, 0"/>
  <LABEL name="forwardLabel" id="773714c115d14957" memberName="forwardLabel"
         virtualName="" explicitFocusOrder="0" pos="0 32 0M 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Forward" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="16"
         bold="0" italic="0" justification="33"/>
  <LABEL name="reverseLabel" id="6bf7e0e89437db37" memberName="reverseLabel"
         virtualName="" explicitFocusOrder="0" pos="0 0R 0M 16" posRelativeY="38d02d38be9fbd84"
         edTextCol="ff000000" edBkgCol="0" labelText="Reverse" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c210b6b0228cca2f" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 0 0M 24" edTextCol="ff000000" edBkgCol="0"
         labelText="SysEx Formula ()" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="24"
         bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
