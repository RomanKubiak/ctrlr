#include "stdafx.h"
#include "LookAndFeelBase.h"
#include "LLookAndFeel.h"

void LookAndFeelBase::drawRotarySlider (Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider)
{
	LookAndFeelParamWrapper wrappedParams (g, x, y, width, height, sliderPosProportional, rotaryStartAngle, rotaryEndAngle, slider);
	owner.drawRotarySlider (wrappedParams);
}

void LookAndFeelBase::getIdealPopupMenuItemSize (const String &text, bool isSeparator, int standardMenuItemHeight, int &idealWidth, int &idealHeight)
{
	LookAndFeelParamWrapper wrappedParams (text, isSeparator, standardMenuItemHeight, idealWidth, idealHeight);
	owner.getIdealPopupMenuItemSize (wrappedParams);
	idealWidth  = wrappedParams.idealWidth;
	idealHeight = wrappedParams.idealHeight;
}
