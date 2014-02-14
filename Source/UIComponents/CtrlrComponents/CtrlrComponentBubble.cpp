#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  8 Jun 2011 12:39:27am

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
#include "CtrlrComponent.h"
//[/Headers]

#include "CtrlrComponentBubble.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrComponentBubble::CtrlrComponentBubble (CtrlrComponent &_owner)
    : owner(_owner),
      value (0),
      name (0)
{
    addAndMakeVisible (value = new Label ("value"));
    value->setFont (Font (12.0000f, Font::bold));
    value->setJustificationType (Justification::centred);
    value->setEditable (true, false, false);
    value->setColour (TextEditor::textColourId, Colours::black);
    value->setColour (TextEditor::backgroundColourId, Colour (0x0));
    value->addListener (this);

    addAndMakeVisible (name = new Label ("name"));
    name->setFont (Font (12.0000f, Font::bold));
    name->setJustificationType (Justification::centredLeft);
    name->setEditable (false, false, false);
    name->setColour (TextEditor::textColourId, Colours::black);
    name->setColour (TextEditor::backgroundColourId, Colour (0x0));


    //[UserPreSize]
	name->addMouseListener (this,false);
	value->addMouseListener (this,false);
	addKeyListener (this);
	value->addKeyListener (this);
	name->addKeyListener (this);
    //[/UserPreSize]

    setSize (64, 64);

    //[Constructor] You can add your own custom stuff here..
	owner.getObjectTree().addListener(this);
    //[/Constructor]
}

CtrlrComponentBubble::~CtrlrComponentBubble()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	owner.getObjectTree().removeListener(this);
    //[/Destructor_pre]

    deleteAndZero (value);
    deleteAndZero (name);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrComponentBubble::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
	g.setGradientFill (ColourGradient (VAR2COLOUR(owner.getProperty(Ids::componentBubbleBackgroundColour1)),
                                       0.0f, 0.0f,
                                       VAR2COLOUR(owner.getProperty(Ids::componentBubbleBackgroundColour2)),
                                       0.0f, (float) (getHeight()),
                                       false));
	g.fillRoundedRectangle (1.0f, 1.0f, (float) (getWidth() - 2), (float) (getHeight() - 2), owner.getProperty(Ids::componentBubbleRoundAngle));

	g.setGradientFill (ColourGradient (VAR2COLOUR(owner.getProperty(Ids::componentBubbleBackgroundColour1)).darker(),
                                       0.0f, 0.0f,
                                       VAR2COLOUR(owner.getProperty(Ids::componentBubbleBackgroundColour2)).darker(),
                                       0.0f, (float) (getHeight()),
                                       false));

    g.drawRoundedRectangle (1.0f, 1.0f, (float) (getWidth() - 2), (float) (getHeight() - 2), owner.getProperty(Ids::componentBubbleRoundAngle), 2.0f);
    //[/UserPrePaint]
    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrComponentBubble::resized()
{
    //[UserResized] Add your own custom resize handling here..
	name->setBounds (0, 0, getWidth(), getHeight()/2);
	value->setBounds (0, getHeight()/2, getWidth(), getHeight()/2);
    //[/UserResized]
}

void CtrlrComponentBubble::labelTextChanged (Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == value)
    {
        //[UserLabelCode_value] -- add your label text handling code here..
		owner.setComponentValue (value->getText().getIntValue(), true);
        //[/UserLabelCode_value]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}

void CtrlrComponentBubble::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    //[/UserCode_mouseDown]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrComponentBubble::mouseDoubleClick(const MouseEvent& e)
{
	setVisible(false);
	owner.removeChildComponent (this);
}

void CtrlrComponentBubble::show()
{
	value->setText (String(owner.getComponentValue()), dontSendNotification);
	name->setText (owner.getOwner().getName(), dontSendNotification);
	owner.addAndMakeVisible(this);
	setBounds(0, 0, owner.getWidth(), owner.getHeight());
	setVisible(true);
}

Label &CtrlrComponentBubble::getValueLabel()
{
	return (*value);
}

Label &CtrlrComponentBubble::getNameLabel()
{
	return (*name);
}

void CtrlrComponentBubble::valueTreePropertyChanged (ValueTree &t, const Identifier &property)
{
	if (property == Ids::componentBubbleNameColour
		|| property == Ids::componentBubbleNameJustification
		|| property == Ids::componentBubbleNameFont)
	{
		name->setColour (Label::textColourId, VAR2COLOUR(t.getProperty(Ids::componentBubbleNameColour)));
		name->setJustificationType (justificationFromProperty (t.getProperty(Ids::componentBubbleNameJustification)));
		name->setFont (STR2FONTM(owner.getFontManager(), t.getProperty(Ids::componentBubbleNameFont)));
	}
	else if (property == Ids::componentBubbleValueColour
		|| property == Ids::componentBubbleValueJustification
		|| property == Ids::componentBubbleValueFont)
	{
		value->setColour (Label::textColourId, VAR2COLOUR(t.getProperty(Ids::componentBubbleValueColour)));
		value->setJustificationType (justificationFromProperty (t.getProperty(Ids::componentBubbleValueJustification)));
		value->setFont (STR2FONTM(owner.getFontManager(), t.getProperty(Ids::componentBubbleValueFont)));
	}
}

bool CtrlrComponentBubble::keyPressed (const KeyPress& key, Component* originatingComponent)
{
	if (key == KeyPress::escapeKey)
	{
		setVisible(false);
		owner.removeChildComponent (this);
	}
	return (false);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrComponentBubble" componentName=""
                 parentClasses="public Component" constructorParams="CtrlrComponent &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="64"
                 initialHeight="64">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffff">
    <ROUNDRECT pos="1 1 2M 2M" cornerSize="10" fill="linear: 0 0, 0 0R, 0=9cffffff, 1=bab9b9b9"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: a68f8f8f"/>
  </BACKGROUND>
  <LABEL name="value" id="991f9fc9ffd6bee6" memberName="value" virtualName=""
         explicitFocusOrder="0" pos="0 16R 0M 16" edTextCol="ff000000"
         edBkgCol="0" labelText="276" editableSingleClick="1" editableDoubleClick="1"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12"
         bold="1" italic="0" justification="36"/>
  <LABEL name="new label" id="d6669f8089558007" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="0 24R 0M 10" edTextCol="ff000000"
         edBkgCol="0" labelText="Value" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="8"
         bold="1" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
