#include "stdafx.h"
#include "CtrlrUtilitiesGUI.h"
#include "CtrlrLog.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrComponents/CtrlrComponent.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "JuceClasses/LMemoryBlock.h"
DrawableImage *drawableFromImage (const Image &i)
{
	DrawableImage *di = new DrawableImage();
	di->setImage (i);
	return (di);
}

const String imageToBase64 (const Image &image)
{
	MemoryBlock memoryBlock;
	MemoryOutputStream memoryStream(memoryBlock,true);
	PNGImageFormat png;
	png.writeImageToStream (image, memoryStream);

	return (memoryBlock.toBase64Encoding());
}

const Justification justificationFromProperty(const var &justificationProperty)
{
	if (justificationProperty == "left")
	{
		return (Justification::left);
	}
	else if (justificationProperty == "right")
	{
		return (Justification::right);
	}
	else if (justificationProperty == "horizontallyCentred")
	{
		return (Justification::horizontallyCentred);
	}
	else if (justificationProperty == "top")
	{
		return (Justification::top);
	}
	else if (justificationProperty == "bottom")
	{
		return (Justification::bottom);
	}
	else if (justificationProperty == "verticallyCentred")
	{
		return (Justification::verticallyCentred);
	}
	else if (justificationProperty == "horizontallyJustified")
	{
		return (Justification::horizontallyJustified);
	}
	else if (justificationProperty == "centred")
	{
		return (Justification::centred);
	}
	else if (justificationProperty == "centredLeft")
	{
		return (Justification::centredLeft);
	}
	else if (justificationProperty == "centredRight")
	{
		return (Justification::centredRight);
	}
	else if (justificationProperty == "centredTop")
	{
		return (Justification::centredTop);
	}
	else if (justificationProperty == "centredBottom")
	{
		return (Justification::centredBottom);
	}
	else if (justificationProperty == "topLeft")
	{
		return (Justification::topLeft);
	}
	else if (justificationProperty == "topRight")
	{
		return (Justification::topRight);
	}
	else if (justificationProperty == "bottomLeft")
	{
		return (Justification::bottomLeft);
	}
	else if (justificationProperty == "bottomRight")
	{
		return (Justification::bottomRight);
	}

	return (Justification::centred);

}

void gradientFromProperty (Graphics &g, Rectangle<int> gradientBounds, const ValueTree &propertyHolder, const Identifier &gradientType, const Identifier &colour1, const Identifier &colour2)
{
	if ((int)propertyHolder.getProperty(gradientType) == 1)
	{
		g.setGradientFill (ColourGradient (VAR2COLOUR(propertyHolder.getProperty(colour1)),
										0.0f, 0.0f,
										VAR2COLOUR(propertyHolder.getProperty(colour2)),
										0.0f, (float) gradientBounds.getHeight(),
										false));
	}
	else if ((int)propertyHolder.getProperty(gradientType) == 2)
	{
		g.setGradientFill (ColourGradient (VAR2COLOUR(propertyHolder.getProperty(colour1)),
										0.0f, 0.0f,
										VAR2COLOUR(propertyHolder.getProperty(colour2)),
										(float) gradientBounds.getWidth(), 0.0f,
										false));
	}
	else if ((int)propertyHolder.getProperty(gradientType) == 3)
	{
		g.setGradientFill (ColourGradient (VAR2COLOUR(propertyHolder.getProperty(colour1)),
										gradientBounds.getWidth()/2.0f, gradientBounds.getHeight()/2.0f,
										VAR2COLOUR(propertyHolder.getProperty(colour2)),
										0.0f, 0.0f,
										true));
	}
	else
	{
		g.setColour (VAR2COLOUR(propertyHolder.getProperty(colour1)));
	}
}

const RectanglePlacement relativePostionFromProperty (const var &positionProperty)
{
	return ((RectanglePlacement)(int)positionProperty);
}

const MouseCursor::StandardCursorType mouseCursorFromproperty (const var &cursorProperty)
{
	return ((MouseCursor::StandardCursorType)(int)cursorProperty);
}

const Point<int> pointFromString(const String &pointState)
{
	Point<int> p;
	p.setX(pointState.upToFirstOccurrenceOf (",", false,false).trim().getIntValue());
	p.setY(pointState.fromFirstOccurrenceOf (",", false,false).trim().getIntValue());
	return (p);
}