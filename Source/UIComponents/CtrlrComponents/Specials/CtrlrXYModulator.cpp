#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  27 Aug 2011 8:31:26pm

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
#include "CtrlrXYSurface.h"
#include "../CtrlrComponentTypeManager.h"
#include "CtrlrUtilities.h"
#include "CtrlrUtilitiesGUI.h"
//[/Headers]

#include "CtrlrXYModulator.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrXYModulator::CtrlrXYModulator (CtrlrXYSurface &_owner)
    : owner(_owner)
{

    //[UserPreSize]
    //[/UserPreSize]

    setSize (32, 32);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrXYModulator::~CtrlrXYModulator()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrXYModulator::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
	const float outline = (float)owner.getProperty(Ids::uiXYSurfaceModulatorOutlineThickness)/2.0f;

	gradientFromProperty (g, getBounds(), owner.getObjectTree(), Ids::uiXYSurfaceModulatorBgGradientType, Ids::uiXYSurfaceModulatorBgColour1, Ids::uiXYSurfaceModulatorBgColour2);
    g.fillEllipse (outline, outline, (float) (getWidth() - outline*2), (float) (getHeight() - outline*2));

	gradientFromProperty (g, getBounds(), owner.getObjectTree(), Ids::uiXYSurfaceModulatorOutlineGradientType, Ids::uiXYSurfaceModulatorOutlineColour1, Ids::uiXYSurfaceModulatorOutlineColour2);
    g.drawEllipse (outline, outline, (float) (getWidth() - outline*2), (float) (getHeight() - outline*2), owner.getProperty(Ids::uiXYSurfaceModulatorOutlineThickness));
    //[/UserPaint]
}

void CtrlrXYModulator::resized()
{
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CtrlrXYModulator::moved()
{
    //[UserCode_moved] -- Add your code here...
	owner.modulatorMoved();
    //[/UserCode_moved]
}

void CtrlrXYModulator::mouseEnter (const MouseEvent& e)
{
    //[UserCode_mouseEnter] -- Add your code here...
	setMouseCursor (MouseCursor::PointingHandCursor);
    //[/UserCode_mouseEnter]
}

void CtrlrXYModulator::mouseExit (const MouseEvent& e)
{
    //[UserCode_mouseExit] -- Add your code here...
    //[/UserCode_mouseExit]
}

void CtrlrXYModulator::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
	if (e.mods.isPopupMenu())
	{
		return;
	}
	dragger.startDraggingComponent (this, e);
    //[/UserCode_mouseDown]
}

void CtrlrXYModulator::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
	if (e.mods.isPopupMenu())
	{
		return;
	}

	MouseEvent er = e.getEventRelativeTo (&owner);

	if (er.x > 0 && er.x < owner.getWidth() && er.y > 0 && er.y < owner.getHeight())
	{
		dragger.dragComponent (this, e, 0);
		owner.modulatorMoved();
	}
    //[/UserCode_mouseDrag]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrXYModulator" componentName=""
                 parentClasses="public Component" constructorParams="CtrlrXYSurface &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="32"
                 initialHeight="32">
  <METHODS>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="moved()"/>
    <METHOD name="mouseEnter (const MouseEvent&amp; e)"/>
    <METHOD name="mouseExit (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="0">
    <ELLIPSE pos="1 1 2M 2M" fill="solid: ffff0000" hasStroke="1" stroke="2, mitered, butt"
             strokeColour="solid: fff1ff00"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
