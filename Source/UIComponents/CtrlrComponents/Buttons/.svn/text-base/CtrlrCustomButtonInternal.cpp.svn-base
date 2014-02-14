#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  16 Apr 2011 6:28:52pm

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
#include "CtrlrImageButton.h"
#include "../CtrlrComponentTypeManager.h"
#include "CtrlrIDs.h"
#include "CtrlrUtilities.h"
#include "CtrlrFontManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
//[/Headers]

#include "CtrlrCustomButtonInternal.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrCustomButtonInternal::CtrlrCustomButtonInternal (CtrlrImageButton &_owner)
    : Button (String::empty),
      owner(_owner),
	  paintMode(RectanglePlacement::stretchToFit)
{
    //[UserPreSize]
    //[/UserPreSize]

    setSize (128, 32);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrCustomButtonInternal::~CtrlrCustomButtonInternal()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrCustomButtonInternal::resized()
{
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}
//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrCustomButtonInternal::paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
	drawFrame (g, getFrameDestinationRect(), isMouseOverButton, isButtonDown);
	drawTextBoxText (g, getFrameDestinationRect(), getBounds());
}

void CtrlrCustomButtonInternal::setPaintMode(const RectanglePlacement _paintMode)
{
	paintMode = _paintMode;
}

void CtrlrCustomButtonInternal::setImage (const Image imageToSet, const int _frameWidth, const int _frameHeight)
{
	possibleValues.clear();

	if (imageToSet == Image::null)
	{
		frameWidth	= 0;
		frameHeight = 0;
		return;
	}

	int totalSpace  = 0;
	frameWidth		= _frameWidth;
	frameHeight		= _frameHeight;
	filmStripImage	= imageToSet;

	if (isVertical)
	{
		totalSpace		= filmStripImage.getHeight()/frameHeight;
		for (int y=0; y<totalSpace; y++)
		{
			Rectangle<int> rect(0, y*frameHeight, frameWidth, frameHeight);
			possibleValues.add (rect);
		}
	}
	else
	{
		totalSpace		= filmStripImage.getWidth()/frameWidth;
		for (int x=0; x<totalSpace; x++)		
		{
			Rectangle<int> rect(x*frameWidth, 0, frameWidth, frameHeight);
			possibleValues.add (rect);
		}
	}
}

const Rectangle<int> CtrlrCustomButtonInternal::getFrameDestinationRect()
{
	Rectangle <int> frameDestinationRectangle;
	const String textBoxPosition						= owner.getProperty(::Ids::uiImageButtonTextPosition);
	const int textBoxHeight								= (int)owner.getProperty(::Ids::uiImageButtonTextHeight);
	const int textBoxWidth								= (int)owner.getProperty(::Ids::uiImageButtonTextWidth);

	if (textBoxPosition == "top")
	{
		frameDestinationRectangle = Rectangle<int>(0, textBoxHeight, getWidth(), getHeight() - textBoxHeight);
	}
	else if (textBoxPosition == "bottom")
	{
		frameDestinationRectangle = Rectangle<int>(0, 0, getWidth(), getHeight() - textBoxHeight);
	}	
	else if (textBoxPosition == "left")
	{
		frameDestinationRectangle = Rectangle<int>(textBoxWidth, 0, getWidth() - textBoxWidth, getHeight());
	}
	else if (textBoxPosition == "right")
	{
		frameDestinationRectangle = Rectangle<int>(0, 0, getWidth() - textBoxWidth, getHeight());
	}
	else
	{
		frameDestinationRectangle = Rectangle<int>(0,0,getWidth(),getHeight());
	}
	
	return (frameDestinationRectangle);
}

Rectangle<int> CtrlrCustomButtonInternal::getFrameCoordsFromStrip(const bool isMouseOver, const bool isMouseDown)
{
	Rectangle<int> stripRectangle;

	if (owner.getButtonMode() == CtrlrImageButton::Momentary)
	{
		if (isMouseDown)
		{
			stripRectangle = possibleValues[1];
		}
		else
		{
			stripRectangle = possibleValues[0];
		}
	}
	else if (owner.getButtonMode() == CtrlrImageButton::MomentaryMouseOver)
	{
		if (isMouseOver && !isMouseDown)
		{
			stripRectangle = possibleValues[0];
		}
		else if (isMouseDown && isMouseOver)
		{
			stripRectangle = possibleValues[2];
		}
		else
		{
			stripRectangle = possibleValues[1];
		}
	}
	else if (isMouseOver && !isMouseDown && getMouseOverMode())
	{
		/* need to draw the mouseOver[1] frame */
		stripRectangle = possibleValues[0];
	}
	else if (isMouseDown && getMouseOverMode())
	{
		/* mouse is not over, draw a normal frame for the current value, but move the index by one to include the mouseOver frame */
		stripRectangle = possibleValues[(int)owner.getComponentValue()+1];
	}
	else if (getMouseOverMode())
	{
		stripRectangle = possibleValues[(int)owner.getComponentValue()+1];
	}
	else if (!getMouseOverMode())
	{
		/* normal event, draw a frame that corresponds to the value */
		stripRectangle = possibleValues[(int)owner.getComponentValue()];
	}

	return (stripRectangle);
}

const bool CtrlrCustomButtonInternal::getMouseOverMode()
{
	switch (owner.getButtonMode())
	{
		case CtrlrImageButton::NormalMouseOver:
		case CtrlrImageButton::MomentaryMouseOver:
			return (true);
		default:
			break;
	}

	return (false);
}

void CtrlrCustomButtonInternal::drawTextBoxText(Graphics &g, const Rectangle<int> &frameRect, const Rectangle<int> &totalAreaToDraw)
{
	RectangleList<int> list;
	list.add (totalAreaToDraw);
	list.subtract (frameRect);
	Rectangle<int> destination = list.getBounds();

	const int destinationWidth = (int)owner.getProperty(::Ids::uiImageButtonTextWidth)  ? (int)owner.getProperty(::Ids::uiImageButtonTextWidth)  : destination.getWidth();
	const int destinatioHeight = (int)owner.getProperty(::Ids::uiImageButtonTextHeight) ? (int)owner.getProperty(::Ids::uiImageButtonTextHeight) : destination.getHeight();

	destination.setSize (destinationWidth, destinatioHeight);

	g.setColour (VAR2COLOUR(owner.getProperty(::Ids::uiImageButtonTextColour)));
	g.setFont (owner.getOwner().getOwner().getOwner().getFontManager().getFontFromString(owner.getProperty(::Ids::uiButtonTextFont)));

	g.drawFittedText (getButtonText(), 
							destination.getX(), 
							destination.getY(), 
							destination.getWidth(), 
							destination.getHeight(), 
							justificationFromProperty (owner.getProperty(::Ids::uiButtonTextJustification)),
							2);
}

void CtrlrCustomButtonInternal::drawFrame(Graphics &g, const Rectangle<int> &destinationRect, const bool isMouseOver, const bool isMouseDown)
{
	g.drawImageWithin (filmStripImage.getClippedImage(getFrameCoordsFromStrip(isMouseOver, isMouseDown)), 
						destinationRect.getX(), 
						destinationRect.getY(), 
						destinationRect.getWidth(), 
						destinationRect.getHeight(), 
						relativePostionFromProperty (owner.getProperty(::Ids::resourceImagePaintMode)), 
						false);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Button" className="CtrlrCustomButtonInternal" componentName=""
                 parentClasses="public Button" constructorParams="CtrlrImageButton &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="128"
                 initialHeight="32">
  <BACKGROUND backgroundColour="0" buttonState="normal" enabled="1">
    <IMAGE pos="0 0 32 64" resource="button_filmstrip_png" opacity="1" mode="1"/>
  </BACKGROUND>
  <BACKGROUND backgroundColour="0" buttonState="over" enabled="0"/>
  <BACKGROUND backgroundColour="0" buttonState="down" enabled="1">
    <IMAGE pos="0 -32 32 64" resource="button_filmstrip_png" opacity="1"
           mode="1"/>
  </BACKGROUND>
  <BACKGROUND backgroundColour="0" buttonState="normal on" enabled="0"/>
  <BACKGROUND backgroundColour="0" buttonState="over on" enabled="0"/>
  <BACKGROUND backgroundColour="0" buttonState="down on" enabled="0"/>
  <BACKGROUND backgroundColour="0" buttonState="common background" enabled="1">
    <TEXT pos="32 0 32M 0M" fill="solid: ff000000" hasStroke="0" text="Button"
          fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
