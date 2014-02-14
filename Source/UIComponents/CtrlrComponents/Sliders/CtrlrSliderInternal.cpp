#include "stdafx.h"
#include "../CtrlrComponent.h"
#include "CtrlrLog.h"
#include "CtrlrSliderInternal.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"

CtrlrSliderInternal::CtrlrSliderInternal(CtrlrComponent &_owner) : owner(_owner)
{
	Slider::setName (owner.getName());
}

CtrlrSliderInternal::~CtrlrSliderInternal()
{
}

String CtrlrSliderInternal::getTextFromValue(double value)
{
	// Causes crash on MAC
    // setColour (TooltipWindow::textColourId, VAR2COLOUR(owner.getOwner().getOwner().getEditor()->getProperty(Ids::uiPanelTooltipColour)));
	return (owner.getTextForValue(value));
}

void CtrlrSliderInternal::mouseWheelMove (const MouseEvent &e, const MouseWheelDetails& wheel)
{
	if (!isEnabled())
		return;

	if (wheel.deltaY < 0)
		setValue (snapValue (getValue() - (double)owner.getProperty(::Ids::uiSliderMouseWheelInterval), false));
	else
		setValue (snapValue (getValue() + (double)owner.getProperty(::Ids::uiSliderMouseWheelInterval), false));
}

/** */
void CtrlrSliderLookAndFeel::drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height, float /*sliderPos*/, float /*minSliderPos*/, float /*maxSliderPos*/, const Slider::SliderStyle /*style*/, Slider& slider)
{
    const float sliderRadius = (float) (getSliderThumbRadius (slider) - 2);

    const Colour trackColour (slider.findColour (Slider::trackColourId));
    const Colour gradCol1 (trackColour.overlaidWith (Colours::black.withAlpha (slider.isEnabled() ? 0.25f : 0.13f)));
    const Colour gradCol2 (trackColour.overlaidWith (Colour (0x14000000)));
    Path indent;

    if (slider.isHorizontal())
    {
        const float iy = y + height * 0.5f - sliderRadius * 0.5f;
        const float ih = sliderRadius;

        g.setGradientFill (ColourGradient (gradCol1, 0.0f, iy,
                                           gradCol2, 0.0f, iy + ih, false));

        indent.addRoundedRectangle (x - sliderRadius * 0.5f, iy,
                                    width + sliderRadius, ih,
                                    ownerTree.getProperty(Ids::uiSliderTrackCornerSize));
        g.fillPath (indent);
    }
    else
    {
        const float ix = x + width * 0.5f - sliderRadius * 0.5f;
        const float iw = sliderRadius;

        g.setGradientFill (ColourGradient (gradCol1, ix, 0.0f,
                                           gradCol2, ix + iw, 0.0f, false));

        indent.addRoundedRectangle (ix, y - sliderRadius * 0.5f,
                                    iw, height + sliderRadius,
                                    ownerTree.getProperty(Ids::uiSliderTrackCornerSize));
        g.fillPath (indent);
    }

    g.setColour (Colour (0x4c000000));
    g.strokePath (indent, PathStrokeType (0.5f));
}

void CtrlrSliderLookAndFeel::drawLinearSliderThumb (Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider)
{
    const float sliderRadius = (float) (getSliderThumbRadius (slider) - 2);

    Colour knobColour (createBaseColour (slider.findColour (Slider::thumbColourId),
                                                             slider.hasKeyboardFocus (false) && slider.isEnabled(),
                                                             slider.isMouseOverOrDragging() && slider.isEnabled(),
                                                             slider.isMouseButtonDown() && slider.isEnabled()));

    const float outlineThickness = slider.isEnabled() ? 0.8f : 0.3f;

    if (style == Slider::LinearHorizontal || style == Slider::LinearVertical)
    {
        float kx, ky;

        if (style == Slider::LinearVertical)
        {
            kx = x + width * 0.5f;
            ky = sliderPos;
        }
        else
        {
            kx = sliderPos;
            ky = y + height * 0.5f;
        }

		drawGlassLozenge (g,
                         kx - ((bool)ownerTree.getProperty(Ids::uiSliderThumbWidth) ? (int)ownerTree.getProperty(Ids::uiSliderThumbWidth) : sliderRadius),
                         ky - ((bool)ownerTree.getProperty(Ids::uiSliderThumbHeight) ? (int)ownerTree.getProperty(Ids::uiSliderThumbHeight) : sliderRadius),
                         ((bool)ownerTree.getProperty(Ids::uiSliderThumbWidth) ? (int)ownerTree.getProperty(Ids::uiSliderThumbWidth) : sliderRadius) * 2.0f,
						 ((bool)ownerTree.getProperty(Ids::uiSliderThumbHeight) ? (int)ownerTree.getProperty(Ids::uiSliderThumbHeight) : sliderRadius) * 2.0f,
                         knobColour, outlineThickness,
						 ownerTree.getProperty(Ids::uiSliderThumbCornerSize),
						 ownerTree.getProperty(Ids::uiSliderThumbFlatOnLeft),
						 ownerTree.getProperty(Ids::uiSliderThumbFlatOnRight),
						 ownerTree.getProperty(Ids::uiSliderThumbFlatOnTop),
						 ownerTree.getProperty(Ids::uiSliderThumbFlatOnBottom));
        /*drawGlassSphere (g,
                         kx - sliderRadius,
                         ky - sliderRadius,
                         sliderRadius * 2.0f,
                         knobColour, outlineThickness);*/
    }
    else
    {
        if (style == Slider::ThreeValueVertical)
        {
            drawGlassSphere (g, x + width * 0.5f - sliderRadius,
                             sliderPos - sliderRadius,
                             sliderRadius * 2.0f,
                             knobColour, outlineThickness);
        }
        else if (style == Slider::ThreeValueHorizontal)
        {
            drawGlassSphere (g,sliderPos - sliderRadius,
                             y + height * 0.5f - sliderRadius,
                             sliderRadius * 2.0f,
                             knobColour, outlineThickness);
        }

        if (style == Slider::TwoValueVertical || style == Slider::ThreeValueVertical)
        {
            const float sr = jmin (sliderRadius, width * 0.4f);

            drawGlassPointer (g, jmax (0.0f, x + width * 0.5f - sliderRadius * 2.0f),
                              minSliderPos - sliderRadius,
                              sliderRadius * 2.0f, knobColour, outlineThickness, 1);

            drawGlassPointer (g, jmin (x + width - sliderRadius * 2.0f, x + width * 0.5f), maxSliderPos - sr,
                              sliderRadius * 2.0f, knobColour, outlineThickness, 3);
        }
        else if (style == Slider::TwoValueHorizontal || style == Slider::ThreeValueHorizontal)
        {
            const float sr = jmin (sliderRadius, height * 0.4f);

            drawGlassPointer (g, minSliderPos - sr,
                              jmax (0.0f, y + height * 0.5f - sliderRadius * 2.0f),
                              sliderRadius * 2.0f, knobColour, outlineThickness, 2);

            drawGlassPointer (g, maxSliderPos - sliderRadius,
                              jmin (y + height - sliderRadius * 2.0f, y + height * 0.5f),
                              sliderRadius * 2.0f, knobColour, outlineThickness, 4);
        }
    }
}

int CtrlrSliderLookAndFeel::getSliderPopupPlacement(Slider &slider)
{
	CtrlrLookAndFeel *lf = owner.getOwner().getOwner().getOwner().getCtrlrLookAndFeel();
	if (lf)
	{
        return (lf->getSliderPopupPlacement(slider));
	}

	return (0);
}

Font CtrlrSliderLookAndFeel::getSliderPopupFont(Slider &slider)
{
	CtrlrLookAndFeel *lf = owner.getOwner().getOwner().getOwner().getCtrlrLookAndFeel();
	if (lf)
	{
        return (lf->getSliderPopupFont(slider));
	}
	return (Font());
}

Colour CtrlrSliderLookAndFeel::findColour (int colourId) const noexcept
{
	return (LookAndFeel::findColour (colourId));
}
