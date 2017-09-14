#ifndef CTRLR_INLINE_UTILITIES_GUI
#define CTRLR_INLINE_UTILITIES_GUI

#include "stdafx.h"
#include "CtrlrMacros.h"

static const inline void drawSelectionRectangle (Graphics &g, int width, int height, Colour base=Colour(HIGHLIGHT_COLOUR), const float baseSaturation=0.9f, const float baseAlpha=0.9f, const float gradientMin=0.2f, const float gradientMax=0.25f)
{
	Colour baseColour (base.withMultipliedSaturation (baseSaturation).withMultipliedAlpha (baseAlpha));
	const float mainBrightness = baseColour.getBrightness();
	const float mainAlpha = baseColour.getFloatAlpha();
	Path outline;
	outline.addRoundedRectangle (0, 0, width, height, 4.0f, 4.0f,false, false, false, false);
	g.setGradientFill (ColourGradient (baseColour.brighter (gradientMin), 0.0f, 0.0f,
                                       baseColour.darker (gradientMax), 0.0f, height, false));
	g.fillPath (outline);

	g.setColour (Colours::white.withAlpha (0.4f * mainAlpha * mainBrightness * mainBrightness));
	g.strokePath (outline, PathStrokeType (1.0f), AffineTransform::translation (0.0f, 1.0f).scaled (1.0f, (height - 1.6f) / height));
	g.setColour (Colours::black.withAlpha (0.4f * mainAlpha));
	g.strokePath (outline, PathStrokeType (1.0f));
}

static const inline void drawSelectionRectangle (Graphics &g, int x, int y, int width, int height, Colour base=Colour(HIGHLIGHT_COLOUR), const float baseSaturation=0.9f, const float baseAlpha=0.9f)
{
	Colour baseColour (base.withMultipliedSaturation (baseSaturation).withMultipliedAlpha (baseAlpha));
	const float mainBrightness = baseColour.getBrightness();
	const float mainAlpha = baseColour.getFloatAlpha();
	Path outline;

	outline.addRoundedRectangle (x, y, width, height, 4.0f, 4.0f,false, false, false, false);

	g.setGradientFill (ColourGradient (baseColour.brighter (0.2f), x, y, baseColour.darker (0.25f), x, height, false));
	g.fillPath (outline);

	g.setColour (Colours::white.withAlpha (0.4f * mainAlpha * mainBrightness * mainBrightness));
	g.strokePath (outline, PathStrokeType (1.0f), AffineTransform::translation (0.0f, 1.0f).scaled (1.0f, (height - 1.6f) / height));
	g.setColour (Colours::black.withAlpha (0.4f * mainAlpha));
	g.strokePath (outline, PathStrokeType (1.0f));
}

#endif
