#include "stdafx.h"
#include "CtrlrFilmStripPainter.h"
#include "CtrlrComponentTypeManager.h"
#include "CtrlrUtilities.h"
#include "CtrlrFontManager.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"

CtrlrImageSliderLF::CtrlrImageSliderLF(CtrlrComponent &_owner)
	: owner(_owner)
{
}

void CtrlrImageSliderLF::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
	CtrlrFilmStripPainter::paint (g, x, y, width, height, sliderPosProportional, rotaryStartAngle, rotaryEndAngle, slider);
}

void CtrlrImageSliderLF::drawLinearSlider (Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &slider)
{
	CtrlrFilmStripPainter::paint (g, x, y, width, height, false, 0, 0, slider);
}

void CtrlrImageSliderLF::drawLinearSliderBackground (Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &slider)
{
}

void CtrlrImageSliderLF::drawLinearSliderThumb (Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &slider)
{
}

Label *CtrlrImageSliderLF::createSliderTextBox (Slider &slider)
{
	Label* const l = new Label();
	l->setFont(owner.getOwner().getOwner().getOwner().getFontManager().getFontFromString(owner.getProperty(Ids::uiSliderValueFont)));
	l->setJustificationType (justificationFromProperty(owner.getProperty(Ids::uiSliderValueTextJustification)));
	l->setColour (Label::textColourId, slider.findColour (Slider::textBoxTextColourId));
	l->setColour (Label::backgroundColourId, (slider.getSliderStyle() == Slider::LinearBar) ? Colours::transparentBlack : slider.findColour (Slider::textBoxBackgroundColourId));
	l->setColour (Label::outlineColourId, slider.findColour (Slider::textBoxOutlineColourId));
	l->setColour (TextEditor::textColourId, slider.findColour (Slider::textBoxTextColourId));
	l->setColour (TextEditor::backgroundColourId, slider.findColour (Slider::textBoxBackgroundColourId).withAlpha (slider.getSliderStyle() == Slider::LinearBar ? 0.7f : 1.0f));
	l->setColour (TextEditor::outlineColourId, slider.findColour (Slider::textBoxOutlineColourId));

	return (l);
}

/**
 
 */

CtrlrImageToggleButton::CtrlrImageToggleButton(CtrlrComponent &_owner) : owner(_owner)
{
}

void CtrlrImageToggleButton::drawToggleButton (Graphics &g, ToggleButton &button, bool isMouseOverButton, bool isButtonDown)
{
	CtrlrFilmStripPainter::paint (g, button, isMouseOverButton, isButtonDown);
}

void CtrlrImageToggleButton::setImage (const Image image, const int frameWidth, const int frameHeight)
{
	CtrlrFilmStripPainter::setImage (image, frameWidth, frameHeight);
}

/**

 */

CtrlrFilmStripPainter::CtrlrFilmStripPainter(const Image imageToSet, const int frameWidth, const int frameHeight)
	: paintMode(RectanglePlacement::stretchToFit), isVertical(true)
{
	if (imageToSet.isValid())
	{
		setImage (imageToSet, frameWidth, frameHeight);
	}
}

CtrlrFilmStripPainter::~CtrlrFilmStripPainter()
{
}

void CtrlrFilmStripPainter::setPaintMode(const RectanglePlacement _paintMode)
{
	paintMode = _paintMode;
}

void CtrlrFilmStripPainter::setImage (const Image imageToSet, const int _frameWidth, const int _frameHeight)
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

	maxValue = possibleValues.size()-1;
}

Rectangle<int> CtrlrFilmStripPainter::getCoordsForValue(const bool value)
{
	if (value)
	{
		return(possibleValues[1]);
	}
	else
	{
		return(possibleValues[0]);
	}
}

Rectangle<int> CtrlrFilmStripPainter::getCoordsForValue(Slider& slider)
{
	Rectangle<int> r;

	const double range		= abs(slider.getMaximum()) + abs(slider.getMinimum());
	const double divider	= range / getMaxValue();
	const double value		= slider.getValue();
	double position			= 0;

	if (slider.getMinimum() < 0 && slider.getMaximum() > 0)
	{
		if (value < 0)
		{
			position			= roundFloatToInt( (((float)range/2.0f) - (float)abs(value)) / (float)divider );
		}
		else
		{
			position			= roundFloatToInt( (((float)range/2.0f) + (float)value) / (float)divider );
		}
	}
	else if (slider.getMinimum() <= 0 && slider.getMaximum() > 0)
	{
		position			= abs(roundFloatToInt((float)value / (float)divider));
	}
	else if (slider.getMinimum() < 0 && slider.getMaximum() == 0)
	{
		position			= roundFloatToInt( ((float)range + (float)value) / (float)divider);
	}
	else if (slider.getMinimum() >= 0 && slider.getMaximum() > 0)
	{
		position			= roundFloatToInt((float)value / (float)divider);
	}
	else if (slider.getMinimum() > 0 && slider.getMaximum() == 0)
	{
		position			= roundFloatToInt( abs((float)value - (float)range) / (float)divider);
	}

	//Logger::writeToLog("range="+String(range)+" divider="+String(divider)+" pos="+String(position)+" maxValue="+String(getMaxValue()));

	return (possibleValues[(int)position]);
}

void CtrlrFilmStripPainter::paint(Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
	Rectangle<int> r = getCoordsForValue (slider);

	g.drawImageWithin (filmStripImage.getClippedImage(r), 
						x, 
						y, 
						width, 
						height, 
						paintMode, 
						false);
}

void CtrlrFilmStripPainter::paint(Graphics &g, ToggleButton &button, bool isMouseOverButton, bool isButtonDown)
{
	Rectangle<int> r = getCoordsForValue ((int)button.getToggleState());

	g.drawImageWithin (filmStripImage.getClippedImage(r), 
						0, 
						0, 
						button.getWidth(), 
						button.getHeight(), 
						paintMode, 
						false);
}

void CtrlrFilmStripPainter::paint(Graphics &g, Button &button, bool isMouseOverButton, bool isButtonDown)
{
	Rectangle<int> r = getCoordsForValue ((int)button.getToggleState());

	g.drawImageWithin (filmStripImage.getClippedImage(r), 
						0, 
						0, 
						button.getWidth(), 
						button.getHeight(), 
						paintMode, 
						false);
}
