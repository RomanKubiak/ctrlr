#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  11 Aug 2011 9:18:09pm

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
#include "../../CtrlrPanel/CtrlrPanelEditor.h"
#include "../CtrlrComponentTypeManager.h"
//[/Headers]

#include "CtrlrHyperlink.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrHyperlink::CtrlrHyperlink (CtrlrModulator &owner)
    : CtrlrComponent(owner),
      hyperlinkButton (0)
{
    addAndMakeVisible (hyperlinkButton = new HyperlinkButton ("http://ctrlr.org",
                                                              URL ("http://ctrlr.org")));
    hyperlinkButton->setTooltip ("http://ctrlr.org");
    hyperlinkButton->setButtonText ("http://ctrlr.org");
    hyperlinkButton->addListener (this);


    //[UserPreSize]
	setProperty (Ids::uiHyperlinkText, "Ctrlr");
	setProperty (Ids::uiHyperlinkUrl, "http://ctrlr.org");
	setProperty (Ids::uiHyperlinkColour, "0xff0000ff");
	setProperty (Ids::uiHyperlinkFont, Font (14, Font::underlined).toString());
	setProperty (Ids::uiHyperlinkFitTextToSize, true);
	setProperty (Ids::uiHyperlinkTextJustification, "centred");
    //[/UserPreSize]

    setSize (128, 48);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrHyperlink::~CtrlrHyperlink()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (hyperlinkButton);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrHyperlink::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrHyperlink::resized()
{
    hyperlinkButton->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
	hyperlinkButton->setBounds (getUsableRect());
    //[/UserResized]
}

void CtrlrHyperlink::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == hyperlinkButton)
    {
        //[UserButtonCode_hyperlinkButton] -- add your button handler code here..
        //[/UserButtonCode_hyperlinkButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrHyperlink::setComponentValue (const double newValue, const bool sendChangeMessage)
{
}

const double CtrlrHyperlink::getComponentValue()
{
	return (0);
}

const int CtrlrHyperlink::getComponentMidiValue()
{
	return (getComponentValue());
}

const double CtrlrHyperlink::getComponentMaxValue()
{
	return (1);
}

const String CtrlrHyperlink::getComponentText()
{
	return (hyperlinkButton->getButtonText());
}

void CtrlrHyperlink::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiHyperlinkText)
	{
		hyperlinkButton->setButtonText (getProperty(property));
		hyperlinkButton->setTooltip (getProperty(property));
	}

	else if (property == Ids::uiHyperlinkUrl)
	{
		hyperlinkButton->setURL (getProperty(property).toString());
	}

	else if (property == Ids::uiHyperlinkColour)
	{
		hyperlinkButton->setColour (HyperlinkButton::textColourId, VAR2COLOUR(getProperty(property)));
	}

	else if (property == Ids::uiHyperlinkFont
		|| property == Ids::uiHyperlinkFitTextToSize
		|| property == Ids::uiHyperlinkTextJustification)
	{
		hyperlinkButton->setFont (STR2FONT(getProperty(Ids::uiHyperlinkFont)), getProperty(Ids::uiHyperlinkFitTextToSize), justificationFromProperty(getProperty(Ids::uiHyperlinkTextJustification)));
	}
	else
	{
		CtrlrComponent::valueTreePropertyChanged(treeWhosePropertyHasChanged, property);
	}

	if (restoreStateInProgress == false)
	{
		resized();
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrHyperlink" componentName=""
                 parentClasses="public CtrlrComponent" constructorParams="CtrlrModulator &amp;owner"
                 variableInitialisers="CtrlrComponent(owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="128"
                 initialHeight="48">
  <BACKGROUND backgroundColour="ffffff"/>
  <HYPERLINKBUTTON name="" id="d5ee7524d0abc04e" memberName="hyperlinkButton" virtualName=""
                   explicitFocusOrder="0" pos="0 0 0M 0M" tooltip="http://ctrlr.org"
                   buttonText="http://ctrlr.org" connectedEdges="0" needsCallback="1"
                   radioGroupId="0" url="http://ctrlr.org"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
