#include "stdafx.h"
#include "LGraphics.h"

void LGraphics::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Graphics>("Graphics")
			.def(constructor<Image &>())
			.def("setColour", &Graphics::setColour)
			.def("setOpacity", &Graphics::setOpacity)

			.def("setGradientFill", &Graphics::setGradientFill)
			.def("setTiledImageFill", &Graphics::setTiledImageFill)
			.def("setFillType", &Graphics::setFillType)

			.def("setFont", (void (Graphics::*)(const Font &))&Graphics::setFont)
			.def("setFont", (void (Graphics::*)(float))&Graphics::setFont)
			.def("getCurrentFont", &Graphics::getCurrentFont)

			.def("drawSingleLineText", &Graphics::drawSingleLineText)
			.def("drawMultiLineText", &Graphics::drawMultiLineText)

			.def("drawText", (void (Graphics::*)(const String &, int, int, int, int, const Justification , bool) const)&Graphics::drawText)
			.def("drawText", (void (Graphics::*)(const String &, const Rectangle<int> &, const Justification , bool) const)&Graphics::drawText)

			.def("drawFittedText", (void (Graphics::*)(const String &, int, int, int, int, const Justification , int, float) const)&Graphics::drawFittedText)
			.def("drawFittedText", (void (Graphics::*)(const String &, const Rectangle<int> &, const Justification , int, float) const)&Graphics::drawFittedText)

			.def("fillAll", (void (Graphics::*)() const)&Graphics::fillAll)
			.def("fillAll", (void (Graphics::*)(const Colour) const)&Graphics::fillAll)

			.def("fillRect", (void (Graphics::*)(int,int,int,int) const)&Graphics::fillRect)
			.def("fillRect", (void (Graphics::*)(const Rectangle<int> &) const)&Graphics::fillRect)

			.def("fillRoundedRectangle", (void (Graphics::*)(float, float, float, float, float) const)&Graphics::fillRoundedRectangle)
			.def("fillRoundedRectangle", (void (Graphics::*)(const Rectangle<float> &, float) const)&Graphics::fillRoundedRectangle)

			.def("fillCheckerBoard", &Graphics::fillCheckerBoard)

			.def("drawRect", (void (Graphics::*)(int, int, int, int, int) const)&Graphics::drawRect)
			.def("drawRect", (void (Graphics::*)(const Rectangle<int> &, int) const)&Graphics::drawRect)

			.def("drawRoundedRectangle", (void (Graphics::*)(float, float, float, float, float, float) const)&Graphics::drawRoundedRectangle)
			.def("drawRoundedRectangle", (void (Graphics::*)(const Rectangle<float>&, float, float) const)&Graphics::drawRoundedRectangle)

			.def("setPixel", &Graphics::setPixel)

			.def("fillEllipse", (void (Graphics::*)(float, float, float, float) const)&Graphics::fillEllipse)
			.def("fillEllipse", (void (Graphics::*)(const Rectangle<float> &) const)&Graphics::fillEllipse)

			//.def("drawEllipse", &Graphics::drawEllipse)

			.def("drawLine", (void (Graphics::*)(float, float, float, float) const)&Graphics::drawLine)
			.def("drawLine", (void (Graphics::*)(float, float, float, float, float) const)&Graphics::drawLine)
			.def("drawLine", (void (Graphics::*)(const Line<float> &) const)&Graphics::drawLine)
			.def("drawLine", (void (Graphics::*)(const Line<float> &, float) const)&Graphics::drawLine)
			.def("drawDashedLine", (void (Graphics::*)(const Line<float> &, const float *, int, float, int) const)&Graphics::drawDashedLine)
			.def("drawVerticalLine", (void (Graphics::*)(int, float, float) const)&Graphics::drawVerticalLine)
			.def("drawHorizontalLine", (void (Graphics::*)(int, float, float) const)&Graphics::drawHorizontalLine)

			.def("fillPath", &Graphics::fillPath)
			.def("strokePath", (void (Graphics::*)(const Path &, const PathStrokeType &, const AffineTransform &) const)&Graphics::strokePath)

			.def("drawArrow", &Graphics::drawArrow)

			.def("setImageResamplingQuality", &Graphics::setImageResamplingQuality)
			.def("drawImageAt", &Graphics::drawImageAt)
			.def("drawImage", &Graphics::drawImage)
			.def("drawImageTransformed", &Graphics::drawImageTransformed)
			.def("drawImageWithin", &Graphics::drawImageWithin)

			.def("getClipBounds", &Graphics::getClipBounds)
			.def("clipRegionIntersects", &Graphics::clipRegionIntersects)
			.def("reduceClipRegion", (bool (Graphics::*)(int,int,int,int))&Graphics::reduceClipRegion)
			.def("reduceClipRegion", (bool (Graphics::*)(const Rectangle<int> &))&Graphics::reduceClipRegion)
			.def("reduceClipRegion", (bool (Graphics::*)(const RectangleList<int> &))&Graphics::reduceClipRegion)
			.def("reduceClipRegion", (bool (Graphics::*)(const Path &path, const AffineTransform &))&Graphics::reduceClipRegion)
			.def("reduceClipRegion", (bool (Graphics::*)(const Image &, const AffineTransform &))&Graphics::reduceClipRegion)
			.def("excludeClipRegion", (bool (Graphics::*)(const Rectangle<int> &))&Graphics::excludeClipRegion)
			.def("isClipEmpty", &Graphics::isClipEmpty)
			.def("saveState", &Graphics::saveState)
			.def("restoreState", &Graphics::restoreState)
			.def("beginTransparencyLayer", &Graphics::beginTransparencyLayer)
			.def("endTransparencyLayer", &Graphics::endTransparencyLayer)
			.def("setOrigin", (void (Graphics::*)(int, int))&Graphics::setOrigin)
			.def("setOrigin", (void (Graphics::*)(Point<int>))&Graphics::setOrigin)
			.def("addTransform", &Graphics::addTransform)
			.def("resetToDefaultState", &Graphics::resetToDefaultState)
			.def("isVectorDevice", &Graphics::isVectorDevice)

			.enum_("ResamplingQuality")
			[
				value("lowResamplingQuality", 0),
				value("mediumResamplingQuality", 1),
				value("highResamplingQuality", 2)
			]
	];
}
