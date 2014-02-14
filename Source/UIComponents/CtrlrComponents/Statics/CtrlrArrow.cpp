#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  11 Jul 2011 12:41:00pm

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

#include "CtrlrArrow.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrArrow::CtrlrArrow (CtrlrModulator &owner)
    : CtrlrComponent(owner)
{

    //[UserPreSize]
	owner.setProperty (Ids::modulatorIsStatic, true);
	owner.setProperty (Ids::modulatorVstExported, false);

	setProperty (Ids::uiArrowColour, "0xff000000");
	setProperty (Ids::uiArrowLineThickness, 2);
	setProperty (Ids::uiArrowHeadWidth, 8);
	setProperty (Ids::uiArrowHeadHeight, 16);
	setProperty (Ids::uiArrowOrientation, 0);
	setProperty (Ids::uiArrowRotation, 0);
	setProperty (Ids::uiArrowStokeThickness, 1);

	componentTree.addListener (this);
    //[/UserPreSize]

    setSize (32, 96);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrArrow::~CtrlrArrow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	componentTree.removeListener (this);
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrArrow::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
	const int orientation	= getProperty(Ids::uiArrowOrientation);
	const int thick			= getProperty(Ids::uiArrowStokeThickness);

	g.setColour (VAR2COLOUR(getProperty (Ids::uiArrowColour)));
	Path arrowPath;

	switch (orientation)
	{
		case 0: /* points top */
			arrowPath.addArrow (Line<float>(getWidth()/2.0f, (float)getHeight()-thick, getWidth()/2.0f, (float)thick), getProperty(Ids::uiArrowLineThickness), getProperty(Ids::uiArrowHeadWidth), getProperty(Ids::uiArrowHeadHeight));
			break;
		
		case 1: /* points down */
			arrowPath.addArrow (Line<float>(getWidth()/2.0f, (float)thick, getWidth()/2.0f, (float)getHeight()-thick), getProperty(Ids::uiArrowLineThickness), getProperty(Ids::uiArrowHeadWidth), getProperty(Ids::uiArrowHeadHeight));
			break;
		
		case 2: /* points left */
			arrowPath.addArrow (Line<float>((float)getWidth()-thick, (float)getHeight()/2.0f, (float)thick, (float)getHeight()/2.0f), getProperty(Ids::uiArrowLineThickness), getProperty(Ids::uiArrowHeadWidth), getProperty(Ids::uiArrowHeadHeight));
			break;
		
		case 3: /* points right */
			arrowPath.addArrow (Line<float>((float)thick, (float)getHeight()/2.0f, (float)getWidth()-thick, (float)getHeight()/2.0f), getProperty(Ids::uiArrowLineThickness), getProperty(Ids::uiArrowHeadWidth), getProperty(Ids::uiArrowHeadHeight));
			break;

		default:
			break;
	}

	g.strokePath (arrowPath, PathStrokeType(getProperty(Ids::uiArrowStokeThickness)), AffineTransform::rotation ((float)getProperty(Ids::uiArrowRotation)*(float_Pi/180), getWidth()/2.0f, getHeight()/2.0f));
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrArrow::resized()
{
    //[UserResized] Add your own custom resize handling here..
	CtrlrComponent::resized();
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrArrow::setComponentValue (const double newValue, const bool sendChangeMessage)
{
}

const double CtrlrArrow::getComponentValue()
{
	return (1);
}

const int CtrlrArrow::getComponentMidiValue()
{
	return (1);
}

const double CtrlrArrow::getComponentMaxValue()
{
	return (1);
}

void CtrlrArrow::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	CtrlrComponent::valueTreePropertyChanged(treeWhosePropertyHasChanged, property);
	resized();
	repaint();
}

void CtrlrArrow::restoreState (const ValueTree &savedState)
{
	CtrlrComponent::restoreState(savedState);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrArrow" componentName=""
                 parentClasses="public CtrlrComponent" constructorParams="CtrlrModulator &amp;owner"
                 variableInitialisers="CtrlrComponent(owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="32"
                 initialHeight="96">
  <BACKGROUND backgroundColour="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
