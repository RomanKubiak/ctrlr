#include "stdafx_luabind.h"
#include "LJuce.h"
#include "CtrlrUtilities.h"

void LAffineTransform::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<AffineTransform>("AffineTransform")
				.def(constructor<float, float, float, float, float, float>())
				.def(constructor<>())
				.def(constructor<const AffineTransform &>())
				.def("translated", (AffineTransform (AffineTransform::*)(float, float) const noexcept)&AffineTransform::translated)
				.def("rotated", (AffineTransform (AffineTransform::*)(float) const noexcept) &AffineTransform::rotated)
				.def("rotated", (AffineTransform (AffineTransform::*)(float, float, float) const noexcept) &AffineTransform::rotated)
				.def("scaled",  (AffineTransform (AffineTransform::*)(float, float) const noexcept) &AffineTransform::scaled)
				.def("scaled",  (AffineTransform (AffineTransform::*)(float, float, float, float) const noexcept) &AffineTransform::scaled)
				.def("sheared", &AffineTransform::sheared)
				.def("inverted", &AffineTransform::inverted)
				.def("followedBy", &AffineTransform::followedBy)
				.def("isIdentity", &AffineTransform::isIdentity)
				.def("isSingularity", &AffineTransform::isSingularity)
				.def("isOnlyTranslation", &AffineTransform::isOnlyTranslation)
				.def("getTranslationX", &AffineTransform::getTranslationX)
				.def("getTranslationY", &AffineTransform::getTranslationY)
				.def("getScaleFactor", &AffineTransform::getScaleFactor)
				//.def("translation", &AffineTransform::translation)
				.scope
				[
					def("translation", (AffineTransform (*)(float, float) noexcept)&AffineTransform::translation),
					def("rotation", (AffineTransform (*)(float) noexcept)&AffineTransform::rotation),
					def("rotation", (AffineTransform (*)(float, float, float) noexcept)&AffineTransform::rotation),
					def("scale", (AffineTransform (*)(float) noexcept)&AffineTransform::scale),
					def("scale", (AffineTransform (*)(float, float) noexcept)&AffineTransform::scale),
					def("scale", (AffineTransform (*)(float, float, float, float) noexcept)&AffineTransform::scale),
					def("shear", (AffineTransform (*)(float, float) noexcept)&AffineTransform::shear),
					def("verticalFlip", (AffineTransform (*)(float) noexcept)&AffineTransform::verticalFlip),
					def("fromTargetPoints", (AffineTransform (*)(float, float, float, float, float, float) noexcept)&AffineTransform::fromTargetPoints)
				]
	];
}

void LAttributedString::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<AttributedString>("AttributedString")
			.def(constructor<>())
			.def(constructor<const String &>())
			.def(constructor<const AttributedString &>())
			.def("getText", &AttributedString::getText)
			.def("setText", &AttributedString::setText)
			.def("append", (void (AttributedString::*) (const String &)) &AttributedString::append)
			.def("append", (void (AttributedString::*) (const String &, const Font &)) &AttributedString::append)
			.def("append", (void (AttributedString::*) (const String &, const Colour)) &AttributedString::append)
			.def("append", (void (AttributedString::*) (const String &, const Font &, const Colour)) &AttributedString::append)
			.def("append", (void (AttributedString::*) (const AttributedString &)) &AttributedString::append)
			.def("clear", &AttributedString::clear)
			.def("getJustification", &AttributedString::getJustification)
			.def("setJustification", &AttributedString::setJustification)
			.def("getWordWrap", &AttributedString::getWordWrap)
			.def("setWordWrap", &AttributedString::setWordWrap)
			.def("getReadingDirection", &AttributedString::getReadingDirection)
			.def("setReadingDirection", &AttributedString::setReadingDirection)
			.def("getLineSpacing", &AttributedString::getLineSpacing)
			.def("setLineSpacing", &AttributedString::setLineSpacing)
			.def("getNumAttributes", &AttributedString::getNumAttributes)
			.def("getAttribute", &AttributedString::getAttribute)
			.def("setColour", (void (AttributedString::*) (const Range<int>, const Colour)) &AttributedString::setColour)
			.def("setColour", (void (AttributedString::*) (const Colour)) &AttributedString::setColour)
			.def("setFont", (void (AttributedString::*) (const Range<int>, const Font &)) &AttributedString::setFont)
			.def("setFont", (void (AttributedString::*) (const Font &)) &AttributedString::setFont)
			.enum_("WordWrap")
			[
				value("none", 0),
				value("byWord", 1),
				value("byChar", 2)
			]
			.enum_("ReadingDirection")
			[
				value("natural", 0),
				value("leftToRight", 1),
				value("rightToLeft", 2)
			]
			.scope
			[
				class_<AttributedString::Attribute>("Attribute")
				.def(constructor<const AttributedString::Attribute &>())
				.def(constructor<const Range <int> &, const Font &, Colour>())
				.def_readwrite("font", &AttributedString::Attribute::font)
				.def_readwrite("colour", &AttributedString::Attribute::colour)
				.def_readwrite("range", &AttributedString::Attribute::range)
			]
	];
}

void LBorderSize::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<BorderSize<int> >("BorderSize")
	];
}

void LColour::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Colour>("Colour")
			.def(constructor<uint32>())
			.def(constructor<const Colour &>())
			.def(constructor<uint8, uint8, uint8, uint8>())
			.def("getRed", &Colour::getRed)
			.def("getGreen", &Colour::getGreen)
			.def("getBlue", &Colour::getBlue)
			.def("getFloatRed", &Colour::getFloatRed)
			.def("getFloatGreen", &Colour::getFloatGreen)
			.def("getFloatBlue", &Colour::getFloatBlue)
			.def("getARGB", &Colour::getARGB)
			.def("getAlpha", &Colour::getAlpha)
			.def("getFloatAlpha", &Colour::getFloatAlpha)
			.def("isOpaque", &Colour::isOpaque)
			.def("isTransparent", &Colour::isTransparent)
			.def("withAlpha", (Colour (Colour::*) (float) const noexcept)&Colour::withAlpha)
			.def("withMultipliedAlpha", &Colour::withMultipliedAlpha)
			.def("overlaidWith", &Colour::overlaidWith)
			.def("interpolatedWith", &Colour::interpolatedWith)
			.def("getHue", &Colour::getHue)
			.def("getSaturation", &Colour::getSaturation)
			.def("withHue", &Colour::withHue)
			.def("withSaturation", &Colour::withSaturation)
			.def("withBrightness", &Colour::withBrightness)
			.def("withRotatedHue", &Colour::withRotatedHue)
			.def("withMultipliedSaturation", &Colour::withMultipliedSaturation)
			.def("withMultipliedBrightness", &Colour::withMultipliedBrightness)
			.def("brighter", &Colour::brighter)
			.def("darker", &Colour::darker)
			.def("toString", &Colour::toString)
			.def("toDisplayString", &Colour::toDisplayString)
			.scope
			[
                def("fromRGB", &Colour::fromRGB),
                def("fromRGBA", &Colour::fromRGBA),
                def("fromFloatRGBA", &Colour::fromFloatRGBA),
                def("fromHSV", &Colour::fromHSV),
                def("contrasting", (Colour (*)(Colour, Colour) noexcept) &Colour::contrasting),
                def("greyLevel", (Colour (*)(float)) &Colour::greyLevel),
                def("fromString", &Colour::fromString)
			]
	];
}

void LColourGradient::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<ColourGradient>("ColourGradient")
			.def(constructor<const Colour &, float, float, const Colour &, float, float, bool>())
			.def(constructor<>())
			.def("clearColours", &ColourGradient::clearColours)
			.def("addColour", &ColourGradient::addColour)
			.def("removeColour", &ColourGradient::removeColour)
			.def("multiplyOpacity", &ColourGradient::multiplyOpacity)
			.def("getNumColours", &ColourGradient::getNumColours)
			.def("getColourPosition", &ColourGradient::getColourPosition)
			.def("getColour", &ColourGradient::getColour)
			.def("setColour", &ColourGradient::setColour)
			.def("getColourAtPosition", &ColourGradient::getColourAtPosition)
			.def("isOpaque", &ColourGradient::isOpaque)
			.def("isInvisible", &ColourGradient::isInvisible)
		,
		class_<FillType>("FillType")
			.def(constructor<FillType &>())
			.def(constructor<const Colour &>())
			.def(constructor<const ColourGradient &>())
			.def(constructor<const Image &, const AffineTransform &>())
			.def("isColour", &FillType::isColour)
			.def("isGradient", &FillType::isGradient)
			.def("isTiledImage", &FillType::isTiledImage)
			.def("setColour", &FillType::setColour)
			.def("setGradient", &FillType::setGradient)
			.def("setTiledImage", &FillType::setTiledImage)
			.def("setOpacity", &FillType::setOpacity)
			.def("getOpacity", &FillType::getOpacity)
			.def("isInvisible", &FillType::isInvisible)
	];
}

void LDrawable::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Drawable>("Drawable")
			.def("createCopy", &Drawable::createCopy)
			.def("draw", &Drawable::draw)
			.def("drawAt", &Drawable::drawAt)
			.def("drawWithin", &Drawable::drawWithin)
			.def("setOriginWithOriginalSize", &Drawable::setOriginWithOriginalSize)
			.def("setTransformToFit", &Drawable::setTransformToFit)
			.def("getParent", &Drawable::getParent)
			.def("createFromImageFile", &Drawable::createFromValueTree)
			.def("getDrawableBounds", &Drawable::getDrawableBounds)
			.scope
			[
				def("createFromImageData", &Drawable::createFromImageData, adopt(result)),
				def("createFromImageDataStream", &Drawable::createFromImageDataStream, adopt(result)),
				def("createFromImageFile", &Drawable::createFromImageFile, adopt(result)),
				def("createFromSVG", &Drawable::createFromSVG, adopt(result)),
				def("createFromValueTree", &Drawable::createFromValueTree, adopt(result)),
				def("toDrawableComposite", &LDrawable::toDrawableComposite)
			]
		,
		class_<DrawableComposite, bases<Drawable> >("DrawableComposite")
			.def(constructor<>())
			.def(constructor<const DrawableComposite &>())
			.def("setBoundingBox", &DrawableComposite::setBoundingBox)
			.def("getBoundingBox", &DrawableComposite::getBoundingBox)
			.def("resetBoundingBoxToContentArea", &DrawableComposite::resetBoundingBoxToContentArea)
			.def("getContentArea", &DrawableComposite::getContentArea)
			.def("setContentArea", &DrawableComposite::setContentArea)
			.def("resetContentAreaAndBoundingBoxToFitChildren", &DrawableComposite::resetContentAreaAndBoundingBoxToFitChildren)
			.def("createCopy", &DrawableComposite::createCopy)
			.def("refreshFromValueTree", &DrawableComposite::refreshFromValueTree)
			.def("createValueTree", &DrawableComposite::createValueTree)
			.def("getDrawableBounds", &DrawableComposite::getDrawableBounds)
			.def("getMarkers", &DrawableComposite::getMarkers)
	];
}

void LFont::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<LFont>("LFont")
		,
		class_<Font,bases<LFont> >("Font")
			.def(constructor<float,int>())
			.def(constructor<const String &, float, int>())
			.def(constructor<const String &, const String &, float>())
			.def(constructor<const Typeface::Ptr &>())
			.def("setTypefaceName", &Font::setTypefaceName)
			.def("getTypefaceName", &Font::getTypefaceName)
			.def("getTypefaceStyle", &Font::getTypefaceStyle)
			.def("setTypefaceStyle", &Font::setTypefaceStyle)
			.def("withTypefaceStyle", &Font::withTypefaceStyle)
			.def("getAvailableStyles", &Font::getAvailableStyles)
			.def("withHeight", &Font::withHeight)
			.def("withPointHeight", &Font::withPointHeight)
			.def("setHeight", &Font::setHeight)
			.def("setHeightWithoutChangingWidth", &Font::setHeightWithoutChangingWidth)
			.def("getHeight", &Font::getHeight)
			.def("getHeightInPoints", &Font::getHeightInPoints)
			.def("getAscent", &Font::getAscent)
			.def("getAscentInPoints", &Font::getAscentInPoints)
			.def("getDescent", &Font::getDescent)
			.def("getDescentInPoints", &Font::getDescentInPoints)
			.def("getStyleFlags", &Font::getStyleFlags)
			.def("withStyle", &Font::withStyle)
			.def("setStyleFlags", &Font::setStyleFlags)
			.def("setBold", &Font::setBold)
			.def("boldened", &Font::boldened)
			.def("isBold", &Font::isBold)
			.def("setItalic", &Font::setItalic)
			.def("italicised", &Font::italicised)
			.def("setUnderline", &Font::setUnderline)
			.def("isUnderlined", &Font::isUnderlined)
			.def("getHorizontalScale", &Font::getHorizontalScale)
			.def("setHorizontalScale", &Font::setHorizontalScale)
			.def("getExtraKerningFactor", &Font::getExtraKerningFactor)
			.def("withExtraKerningFactor", &Font::withExtraKerningFactor)
			.def("setExtraKerningFactor", &Font::setExtraKerningFactor)
			.def("setSizeAndStyle", (void (Font::*)(float, int, float, float))&Font::setSizeAndStyle)
			.def("setSizeAndStyle", (void (Font::*)(float, const String &, float, float))&Font::setSizeAndStyle)
			.def("getStringWidth", &Font::getStringWidth)
			.def("getStringWidthFloat", &Font::getStringWidthFloat)
			.def("getGlyphPositions", &Font::getGlyphPositions)
			.def("getTypeface", &Font::getTypeface)
			.def("toString", &Font::toString)
			.scope
			[
				def("getDefaultSansSerifFontName", &Font::getDefaultSansSerifFontName),
				def("getDefaultSerifFontName", &Font::getDefaultSerifFontName),
				def("getDefaultMonospacedFontName ", &Font::getDefaultMonospacedFontName),
				def("getDefaultStyle", &Font::getDefaultStyle),
				def("getDefaultTypefaceForFont", &Font::getDefaultTypefaceForFont),
				def("findAllTypefaceNames", &Font::findAllTypefaceNames),
				def("findAllTypefaceStyles", &Font::findAllTypefaceStyles),
				def("getFallbackFontName", &Font::getFallbackFontName),
				def("setFallbackFontName", &Font::setFallbackFontName),
				def("getFallbackFontStyle", &Font::getFallbackFontStyle),
				def("setFallbackFontStyle", &Font::setFallbackFontStyle),
				def("fromString", &Font::fromString)
			]
			.enum_("FontStyleFlags")
			[
				value("plain", 0),
				value("bold", 1),
				value("italic", 2),
				value("underlined", 3)
			]
	];
}

void LGlyphArrangement::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<GlyphArrangement>("GlyphArrangement")
			.def(constructor<>())
			.def(constructor<const GlyphArrangement &>())
			.def("getNumGlyphs", &GlyphArrangement::getNumGlyphs)
			.def("getGlyph", &GlyphArrangement::getGlyph)
			.def("clear", &GlyphArrangement::clear)
			.def("addLineOfText", &GlyphArrangement::addLineOfText)
			.def("addCurtailedLineOfText", &GlyphArrangement::addCurtailedLineOfText)
			.def("addJustifiedText", &GlyphArrangement::addJustifiedText)
			.def("addFittedText", &GlyphArrangement::addFittedText)
			.def("addGlyphArrangement", &GlyphArrangement::addGlyphArrangement)
			.def("addGlyph", &GlyphArrangement::addGlyph)
			.def("draw", (void (GlyphArrangement::*) (const Graphics &) const) &GlyphArrangement::draw)
			.def("draw", (void (GlyphArrangement::*) (const Graphics &, const AffineTransform &) const) &GlyphArrangement::draw)
			.def("createPath", &GlyphArrangement::createPath)
			.def("findGlyphIndexAt", &GlyphArrangement::findGlyphIndexAt)
			.def("getBoundingBox", &GlyphArrangement::getBoundingBox)
			.def("moveRangeOfGlyphs", &GlyphArrangement::moveRangeOfGlyphs)
			.def("removeRangeOfGlyphs", &GlyphArrangement::removeRangeOfGlyphs)
			.def("stretchRangeOfGlyphs", &GlyphArrangement::stretchRangeOfGlyphs)
			.def("justifyGlyphs", &GlyphArrangement::justifyGlyphs)
	];
}

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

			.def("drawText", (void (Graphics::*)(const String &, int, int, int, int, Justification , bool) const)&Graphics::drawText)
			.def("drawText", (void (Graphics::*)(const String &, const Rectangle<int>, Justification , bool) const)&Graphics::drawText)
			.def("drawText", (void (Graphics::*)(const String &, const Rectangle<float>, Justification, bool) const)&Graphics::drawText)

			.def("drawFittedText", (void (Graphics::*)(const String &, int, int, int, int, Justification , int, float) const)&Graphics::drawFittedText)
			.def("drawFittedText", (void (Graphics::*)(const String &, Rectangle<int>, Justification , int, float) const)&Graphics::drawFittedText)

			.def("fillAll", (void (Graphics::*)() const)&Graphics::fillAll)
			.def("fillAll", (void (Graphics::*)(const Colour) const)&Graphics::fillAll)

			.def("fillRect", (void (Graphics::*)(int,int,int,int) const)&Graphics::fillRect)
			.def("fillRect", (void (Graphics::*)(const Rectangle<int>) const)&Graphics::fillRect)

			.def("fillRoundedRectangle", (void (Graphics::*)(float, float, float, float, float) const)&Graphics::fillRoundedRectangle)
			.def("fillRoundedRectangle", (void (Graphics::*)(const Rectangle<float>, float) const)&Graphics::fillRoundedRectangle)

			.def("fillCheckerBoard", &Graphics::fillCheckerBoard)

			.def("drawRect", (void (Graphics::*)(int, int, int, int, int) const)&Graphics::drawRect)
			.def("drawRect", (void (Graphics::*)(const Rectangle<int>, int) const)&Graphics::drawRect)

			.def("drawRoundedRectangle", (void (Graphics::*)(float, float, float, float, float, float) const)&Graphics::drawRoundedRectangle)
			.def("drawRoundedRectangle", (void (Graphics::*)(const Rectangle<float>, float, float) const)&Graphics::drawRoundedRectangle)

			//.def("setPixel", &Graphics::setPixel)

			.def("fillEllipse", (void (Graphics::*)(float, float, float, float) const)&Graphics::fillEllipse)
			.def("fillEllipse", (void (Graphics::*)(const Rectangle<float>) const)&Graphics::fillEllipse)

			.def("drawEllipse", (void (Graphics::*)(float, float, float, float, float) const)&Graphics::drawEllipse)
			.def("drawEllipse", (void (Graphics::*)(const Rectangle<float>, float) const)&Graphics::drawEllipse)

			.def("drawLine", (void (Graphics::*)(float, float, float, float) const)&Graphics::drawLine)
			.def("drawLine", (void (Graphics::*)(float, float, float, float, float) const)&Graphics::drawLine)
			//.def("drawLine", (void (Graphics::*)(const Line<float> &) const)&Graphics::drawLine)
			//.def("drawLine", (void (Graphics::*)(const Line<float> &, float) const)&Graphics::drawLine)
			.def("drawDashedLine", (void (Graphics::*)(const Line<float> &, const float *, int, float, int) const)&Graphics::drawDashedLine)
			.def("drawVerticalLine", (void (Graphics::*)(int, float, float) const)&Graphics::drawVerticalLine)
			.def("drawHorizontalLine", (void (Graphics::*)(int, float, float) const)&Graphics::drawHorizontalLine)

			.def("fillPath", (void (Graphics::*)(const Path &, const AffineTransform &) const)&Graphics::fillPath)
			.def("fillPath", (void (Graphics::*)(const Path &) const)&Graphics::fillPath)
			.def("strokePath", (void (Graphics::*)(const Path &, const PathStrokeType &, const AffineTransform &) const)&Graphics::strokePath)

			.def("drawArrow", &Graphics::drawArrow)

			.def("setImageResamplingQuality", &Graphics::setImageResamplingQuality)
			.def("drawImageAt", &Graphics::drawImageAt)
			.def("drawImage", (void (Graphics::*)(const Image &, int, int, int, int, int, int, int, int, bool) const)&Graphics::drawImage)
			.def("drawImage", (void (Graphics::*)(const Image &, Rectangle<float>, RectanglePlacement, bool) const)&Graphics::drawImage)
			.def("drawImageTransformed", &Graphics::drawImageTransformed)
			.def("drawImageWithin", &Graphics::drawImageWithin)

			.def("getClipBounds", &Graphics::getClipBounds)
			.def("clipRegionIntersects", &Graphics::clipRegionIntersects)
			.def("reduceClipRegion", (bool (Graphics::*)(int,int,int,int))&Graphics::reduceClipRegion)
			.def("reduceClipRegion", (bool (Graphics::*)(const Rectangle<int>))&Graphics::reduceClipRegion)
			.def("reduceClipRegion", (bool (Graphics::*)(const RectangleList<int> &))&Graphics::reduceClipRegion)
			.def("reduceClipRegion", (bool (Graphics::*)(const Path &path, const AffineTransform &))&Graphics::reduceClipRegion)
			.def("reduceClipRegion", (bool (Graphics::*)(const Image &, const AffineTransform &))&Graphics::reduceClipRegion)
			.def("excludeClipRegion", (bool (Graphics::*)(const Rectangle<int>))&Graphics::excludeClipRegion)
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

void LImage::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
        class_<ImageType>("ImageType")
            .def("create", &ImageType::create)
            .def("getTypeID", &ImageType::getTypeID)
            .def("convert", &ImageType::convert)
        ,
		class_<Image>("Image")
            .enum_("PixelFormat")
			[
				value("UnknownFormat", Image::UnknownFormat),
				value("RGB", Image::RGB),
				value("ARGB", Image::ARGB),
				value("SingleChannel", Image::SingleChannel)
			]
            .def(constructor<Image::PixelFormat, int, int, bool>())
            .def(constructor<Image::PixelFormat, int, int, bool, const ImageType &>())
			.def(constructor<const Image &>())
			.def(constructor<>())
			.def("isValid", &Image::isValid)
			.def("isNull", &Image::isNull)
			.def("getWidth", &Image::getWidth)
			.def("getHeight", &Image::getHeight)
			.def("isRGB", &Image::isRGB)
			.def("isARGB", &Image::isARGB)
			.def("isSingleChannel", &Image::isSingleChannel)
			.def("hasAlphaChannel", &Image::hasAlphaChannel)
			.def("rescaled", &Image::rescaled)
			.def("duplicateIfShared", &Image::duplicateIfShared)
			.def("getPixelAt", &Image::getPixelAt)
			.def("setPixelAt", &Image::setPixelAt)
			.def("multiplyAlphaAt", &Image::multiplyAlphaAt)
			.def("multiplyAllAlphas", &Image::multiplyAllAlphas)
			.def("desaturate", &Image::desaturate)
			.def("moveImageSection", &Image::moveImageSection)
			.def("getReferenceCount", &Image::getReferenceCount)
			.scope
			[
                def("null", &LImage::null)
			]
		,
		class_<ImageFileFormat>("ImageFileFormat")
			.def("getFormatName", &ImageFileFormat::getFormatName)
			.def("canUnderstand", &ImageFileFormat::canUnderstand)
			.def("loadFrom", (Image (*)(const File &)) &ImageFileFormat::loadFrom)
	];
}

void LJustification::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Justification>("Justification")
			.def(constructor<int>())
			.def("getFlags", &Justification::getFlags)
			.def("testFlags", &Justification::testFlags)
			.def("getOnlyVerticalFlags", &Justification::getOnlyVerticalFlags)
			.def("getOnlyHorizontalFlags", &Justification::getOnlyHorizontalFlags)
			.enum_("Flags")
			[
				value("left", 1),
				value("right", 2),
				value("horizontallyCentred", 4),
				value("top", 8),
				value("bottom", 16),
				value("verticallyCentred", 32),
				value("horizontallyJustified", 64),
				value("centred", 36),
				value("centredLeft", 33),
				value("centredRight", 34),
				value("centredTop", 12),
				value("centredBottom", 20),
				value("topLeft", 9),
				value("topRight", 10),
				value("bottomLeft", 17),
				value("bottomRight", 18)
			]
	];
}

void LLine::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Line<float> >("Line")
			.def(constructor<>())
			.def(constructor<float,float,float,float>())
			.def(constructor<const Point<float> &, const Point<float>& >())
			.def(constructor<const Line<float> &>())
			.def("getStartX", &Line<float>::getStartX)
			.def("getStartY", &Line<float>::getStartY)
			.def("getEndX", &Line<float>::getEndX)
			.def("getEndY", &Line<float>::getEndY)
			.def("getStart", &Line<float>::getStart)
			.def("getEnd", &Line<float>::getEnd)
			.def("setStart", (void (Line<float>::*)(float,float) noexcept)&Line<float>::setStart)
			.def("setEnd", (void (Line<float>::*)(float,float) noexcept)&Line<float>::setEnd)
			.def("setStart", (void (Line<float>::*)(const Point<float> ) noexcept)&Line<float>::setStart)
			.def("setEnd", (void (Line<float>::*)(const Point<float> ) noexcept)&Line<float>::setEnd)
			.def("reversed", &Line<float>::reversed)
			.def("applyTransform", &Line<float>::applyTransform)
			.def("getLength", &Line<float>::getLength)
			.def("isVertical", &Line<float>::isVertical)
			.def("isHorizontal", &Line<float>::isHorizontal)
			.def("getAngle", &Line<float>::getAngle)
			//.def("intersects", &Line<float>::intersects)
			.def("getIntersection", &Line<float>::getIntersection )
			.def("getPointAlongLine", (Point<float> (Line<float>::*)(float) const noexcept)&Line<float>::getPointAlongLine)
			.def("getPointAlongLine", (Point<float> (Line<float>::*)(float,float) const noexcept)&Line<float>::getPointAlongLine)
			.def("getPointAlongLineProportionally", &Line<float>::getPointAlongLineProportionally)
			.def("getDistanceFromPoint", &Line<float>::getDistanceFromPoint)
			.def("findNearestProportionalPositionTo", &Line<float>::findNearestProportionalPositionTo)
			.def("findNearestPointTo", &Line<float>::findNearestPointTo)
			.def("isPointAbove", &Line<float>::isPointAbove)
			.def("withShortenedStart", &Line<float>::withShortenedStart)
			.def("withShortenedEnd", &Line<float>::withShortenedEnd)
	];
}

void LPath::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Path>("Path")
			.def(constructor<>())
			.def(constructor<const Path &>())
			.def("isEmpty", &Path::isEmpty)
			.def("getBounds", &Path::getBounds)
			.def("getBoundsTransformed", &Path::getBoundsTransformed)
			.def("contains", (bool (Path::*)(float, float, float) const) &Path::contains)
			.def("contains", (bool (Path::*)(const Point<float>, float) const) &Path::contains)
			.def("intersectsLine", &Path::intersectsLine)
			.def("getClippedLine", &Path::getClippedLine)
			.def("getLength", &Path::getLength)
			.def("getPointAlongPath", &Path::getPointAlongPath)
			.def("getNearestPoint", &Path::getNearestPoint)
			.def("clear", &Path::clear)
			.def("startNewSubPath", (void (Path::*)(float, float)) &Path::startNewSubPath)
			.def("startNewSubPath", (void (Path::*)(const Point<float>)) &Path::startNewSubPath)
			.def("closeSubPath", &Path::closeSubPath)
			.def("lineTo", (void (Path::*)(float, float)) &Path::lineTo)
			.def("lineTo", (void (Path::*)(const Point<float>)) &Path::lineTo)
			.def("quadraticTo", (void (Path::*)(float, float, float, float)) &Path::quadraticTo)
			.def("quadraticTo", (void (Path::*)(const Point<float>, const Point<float>)) &Path::quadraticTo)
			.def("cubicTo", (void (Path::*)(float, float, float, float, float, float)) &Path::cubicTo)
			.def("cubicTo", (void (Path::*)(const Point<float>, const Point<float>, const Point<float>)) &Path::cubicTo)
			.def("getCurrentPosition", &Path::getCurrentPosition)
			.def("addRectangle", (void (Path::*)(float, float, float, float)) &Path::addRectangle)
			.def("addRoundedRectangle", (void (Path::*)(float, float, float, float, float)) &Path::addRoundedRectangle)
			.def("addRoundedRectangle", (void (Path::*)(float, float, float, float, float, float)) &Path::addRoundedRectangle)
			.def("addRoundedRectangle", (void (Path::*)(float, float, float, float, float, float, bool, bool, bool, bool)) &Path::addRoundedRectangle)
			.def("addTriangle", (void (Path::*)(float, float, float, float, float, float)) &Path::addTriangle)
			.def("addQuadrilateral", &Path::addQuadrilateral)
			.def("addEllipse", (void(Path::*)(float, float, float, float))&Path::addEllipse)
			.def("addEllipse", (void(Path::*)(Rectangle<float>))&Path::addEllipse)
			.def("addArc", &Path::addArc)
			.def("addCentredArc", &Path::addCentredArc)
			.def("addPieSegment", (void(Path::*)(float, float, float, float, float, float, float)) &Path::addPieSegment)
			.def("addPieSegment", (void(Path::*)(Rectangle<float>, float, float, float)) &Path::addPieSegment)
			.def("addLineSegment", &Path::addLineSegment)
			.def("addArrow", &Path::addArrow)
			.def("addPolygon", &Path::addPolygon)
			.def("addStar", &Path::addStar)
			.def("addBubble", &Path::addBubble)
			.def("addPath", &Path::addQuadrilateral)
			.def("addPath", &Path::addQuadrilateral)
			.def("swapWithPath", &Path::swapWithPath)
			.def("applyTransform", &Path::applyTransform)
			.def("scaleToFit", &Path::scaleToFit)
			.def("getTransformToScaleToFit", (AffineTransform (Path::*)(float, float, float, float, bool, Justification) const)&Path::getTransformToScaleToFit)
			//.def("getTransformToScaleToFit", (AffineTransform (Path::*)(const Rectangle<float> &, bool, Justification) const)&Path::getTransformToScaleToFit)
			.def("createPathWithRoundedCorners", &Path::createPathWithRoundedCorners)
			.def("setUsingNonZeroWinding", &Path::setUsingNonZeroWinding)
			.def("isUsingNonZeroWinding", &Path::isUsingNonZeroWinding)
			.def("loadPathFromStream", &Path::loadPathFromStream)
			.def("loadPathFromData", &Path::loadPathFromData)
			.def("writePathToStream", &Path::writePathToStream)
			.def("toString", &Path::toString)
			.def("restoreFromString", &Path::restoreFromString)
		,
        class_<LPathStrokeType>("PathStrokeType")
		,
		class_<PathStrokeType, bases<LPathStrokeType> >("PathStrokeType")
			.def(constructor<float>())
			.def(constructor<float, PathStrokeType::JointStyle, PathStrokeType::EndCapStyle>())
			.def(constructor<const PathStrokeType &>())
			.def("createStrokedPath", &PathStrokeType::createStrokedPath)
			.def("createDashedStroke", &LPathStrokeType::createDashedStrokeWrap)
			.def("createStrokeWithArrowheads", &PathStrokeType::createStrokeWithArrowheads)
			.def("getStrokeThickness", &PathStrokeType::getStrokeThickness)
			.def("setStrokeThickness", &PathStrokeType::setStrokeThickness)
			.def("getJointStyle", &PathStrokeType::getJointStyle)
			.def("setJointStyle", &PathStrokeType::setJointStyle)
			.def("getEndStyle", &PathStrokeType::getEndStyle)
			.def("setEndStyle", &PathStrokeType::setEndStyle)
			.enum_("JoinStyle")
			[
				value("mitered", PathStrokeType::mitered),
				value("curved", PathStrokeType::curved),
				value("beveled", PathStrokeType::beveled)
			]
			.enum_("EndCapStyle")
			[
				value("butt", PathStrokeType::butt),
				value("square", PathStrokeType::square),
				value("rounded", PathStrokeType::rounded)
			]
	];
}

void LPathStrokeType::createDashedStrokeWrap (Path &destPath, const Path &sourcePath, const luabind::object dashLengths, const AffineTransform &transform, float extraAccuracy)
{
    Array<float> dashLengthsFloat = luaArrayToFloat (dashLengths);
    PathStrokeType::createDashedStroke (destPath, sourcePath, dashLengthsFloat.getRawDataPointer(), dashLengthsFloat.size(), transform, extraAccuracy);
}

void LPoint::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Point<float> >("Point")
			.def(constructor<>())
			.def(constructor<const Point<float> &>())
			.def(constructor<float,float>())
			.def("isOrigin", &Point<float>::isOrigin)
			.def("getX", &Point<float>::getX)
			.def("getY", &Point<float>::getY)
			.def("setX", &Point<float>::setX)
			.def("setY", &Point<float>::setY)
			.def("withX", &Point<float>::withX)
			.def("withY", &Point<float>::withY)
			.def("setXY", &Point<float>::setXY)
			.def("addXY", &Point<float>::addXY)
			.def("translated", &Point<float>::translated)
			.def("getDistanceFromOrigin", &Point<float>::getDistanceFromOrigin)
			.def("getDistanceFrom", &Point<float>::getDistanceFrom)
			.def("getAngleToPoint", &Point<float>::getAngleToPoint)
			.def("getPointOnCircumference", (Point<float> (Point<float>::*)(const float, const float) const noexcept)&Point<float>::getPointOnCircumference)
			.def("getPointOnCircumference", (Point<float> (Point<float>::*)(const float, const float, const float) const noexcept)&Point<float>::getPointOnCircumference)
			.def("applyTransform", &Point<float>::applyTransform)
			.def("transformedBy", &Point<float>::transformedBy)
			.def("toString", &Point<float>::toString)
			.def_readwrite("x",&Point<float>::x)
			.def_readwrite("y",&Point<float>::y)
	];
}

void LRectangle::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Rectangle<int> >("Rectangle")
			.def(constructor<>())
			.def(constructor<const Rectangle<int> &>())
			.def(constructor<int,int,int,int>())
			.def(constructor<int,int>())
			.def(constructor<const Point<int> &, const Point <int> &>())
			.def("isEmpty", &Rectangle<int>::isEmpty)
			.def("getX", &Rectangle<int>::getX)
			.def("getY", &Rectangle<int>::getY)
			.def("getWidth", &Rectangle<int>::getWidth)
			.def("getHeight", &Rectangle<int>::getHeight)
			.def("getRight", &Rectangle<int>::getRight)
			.def("getBottom", &Rectangle<int>::getBottom)
			.def("getCentreX", &Rectangle<int>::getCentreX)
			.def("getCentreY", &Rectangle<int>::getCentreY)
			.def("getCentre", &Rectangle<int>::getCentre)
			.def("getAspectRatio", &Rectangle<int>::getAspectRatio)
			.def("getPosition", &Rectangle<int>::getPosition)
			.def("setPosition", (void (Rectangle<int>::*)(const Point<int> ) noexcept)&Rectangle<int>::setPosition)
			.def("setPosition", (void (Rectangle<int>::*)(const int, const int) noexcept)&Rectangle<int>::setPosition)
			.def("getTopLeft", &Rectangle<int>::getTopLeft)
			.def("getTopRight", &Rectangle<int>::getTopRight)
			.def("getBottomLeft", &Rectangle<int>::getBottomLeft)
			.def("getBottomRight", &Rectangle<int>::getBottomRight)
			.def("setSize", &Rectangle<int>::setSize)
			.def("setBounds", &Rectangle<int>::setBounds)
			.def("setX", &Rectangle<int>::setX)
			.def("setY", &Rectangle<int>::setY)
			.def("setWidth", &Rectangle<int>::setWidth)
			.def("setHeight", &Rectangle<int>::setHeight)
			.def("withX", &Rectangle<int>::withX)
			.def("withY", &Rectangle<int>::withY)
			.def("withPosition", (Rectangle<int> (Rectangle<int>::*)(const Point<int> ) const noexcept)&Rectangle<int>::withPosition)
			.def("withPosition", (Rectangle<int> (Rectangle<int>::*)(const int, const int) const noexcept)&Rectangle<int>::withPosition)
			.def("withZeroOrigin", &Rectangle<int>::withZeroOrigin)
			.def("withWidth", &Rectangle<int>::withWidth)
			.def("withHeight", &Rectangle<int>::withHeight)
			.def("withSize", &Rectangle<int>::withSize)
			.def("setLeft", &Rectangle<int>::setLeft)
			.def("withLeft", &Rectangle<int>::withLeft)
			.def("setTop", &Rectangle<int>::setTop)
			.def("withTop", &Rectangle<int>::withTop)
			.def("setRight", &Rectangle<int>::setRight)
			.def("withRight", &Rectangle<int>::withRight)
			.def("setBottom", &Rectangle<int>::setBottom)
			.def("withBottom", &Rectangle<int>::withBottom)
			.def("translate", &Rectangle<int>::translate)
			.def("translated", &Rectangle<int>::translated)
			.def("expand", &Rectangle<int>::expand)
			.def("expanded", (Rectangle<int> (Rectangle<int>::*)(const int, const int) const noexcept)&Rectangle<int>::expanded)
			.def("expanded", (Rectangle<int> (Rectangle<int>::*)(const int) const noexcept)&Rectangle<int>::expanded)
			.def("reduce", &Rectangle<int>::reduce)
			.def("reduced", (Rectangle<int> (Rectangle<int>::*)(const int, const int) const noexcept)&Rectangle<int>::reduced)
			.def("reduced", (Rectangle<int> (Rectangle<int>::*)(const int) const noexcept)&Rectangle<int>::reduced)
			.def("removeFromTop", &Rectangle<int>::removeFromTop)
			.def("removeFromLeft", &Rectangle<int>::removeFromLeft)
			.def("removeFromRight", &Rectangle<int>::removeFromRight)
			.def("removeFromBottom", &Rectangle<int>::removeFromBottom)
			.def("contains", (bool (Rectangle<int>::*)(const int, const int) const noexcept)&Rectangle<int>::contains)
			.def("contains", (bool (Rectangle<int>::*)(const Point<int> ) const noexcept)&Rectangle<int>::contains)
			//.def("contains", (bool (Rectangle<int>::*)(const Rectangle<int> &) const noexcept)&Rectangle<int>::contains)
			.def("getConstrainedPoint", &Rectangle<int>::getConstrainedPoint)
			// .def("intersects", (bool (Rectangle<int>::*)(Rectangle<int> &) const noexcept) &Rectangle<int>::intersects)
			.def("getIntersection", &Rectangle<int>::getIntersection)
			.def("getUnion", &Rectangle<int>::getUnion)
			.def("enlargeIfAdjacent", &Rectangle<int>::enlargeIfAdjacent)
			.def("reduceIfPartlyContainedIn", &Rectangle<int>::reduceIfPartlyContainedIn)
			.def("transformedBy", &Rectangle<int>::transformedBy)
			.def("getSmallestIntegerContainer", &Rectangle<int>::getSmallestIntegerContainer)
			.def("toFloat", &Rectangle<int>::toFloat)
			.def("toString", &Rectangle<int>::toString)
			.def("leftTopRightBottom", &Rectangle<int>::leftTopRightBottom)
			.def("findAreaContainingPoints", &Rectangle<int>::findAreaContainingPoints)
			.def("intersectRectangles", &Rectangle<int>::intersectRectangles)
			.def("fromString", &Rectangle<int>::fromString)
		,
		class_<RectanglePlacement>("RectanglePlacement")
			.def(constructor<int>())
			.def("getFlags", &RectanglePlacement::getFlags)
			.def("testFlags", &RectanglePlacement::testFlags)
			.def("applyTo", &RectanglePlacement::applyTo)
			.enum_("flags")
			[
				value("xLeft", 1),
				value("xRight", 2),
				value("xMid", 4),
				value("yTop", 8),
				value("yBottom", 16),
				value("yMid", 32),
				value("stretchToFit", 64),
				value("fillDestination", 128),
				value("onlyReduceInSize", 256),
				value("onlyIncreaseInSize", 512),
				value("doNotResize", 768),
				value("centred", 36)
			]
    ,
        class_<LRectangle>("LRectangle")
    ,
        class_<Rectangle<float>, bases<LRectangle> >("RectangleFloat")
            .def(constructor<>())
            .def(constructor<const Rectangle<float> &>())
			.def(constructor<float,float,float,float>())
			.def(constructor<float,float>())
			.def(constructor<const Point<float> &, const Point <float> &>())
			.def("isEmpty", &Rectangle<float>::isEmpty)
			.def("getX", &Rectangle<float>::getX)
			.def("getY", &Rectangle<float>::getY)
			.def("getWidth", &Rectangle<float>::getWidth)
			.def("getHeight", &Rectangle<float>::getHeight)
			.def("getRight", &Rectangle<float>::getRight)
			.def("getBottom", &Rectangle<float>::getBottom)
			.def("getCentreX", &Rectangle<float>::getCentreX)
			.def("getCentreY", &Rectangle<float>::getCentreY)
			.def("getCentre", &Rectangle<float>::getCentre)
			.def("getAspectRatio", &Rectangle<float>::getAspectRatio)
			.def("getPosition", &Rectangle<float>::getPosition)
			.def("setPosition", (void (Rectangle<float>::*)(const Point<float> ) noexcept)&Rectangle<float>::setPosition)
			.def("setPosition", (void (Rectangle<float>::*)(const float, const float) noexcept)&Rectangle<float>::setPosition)
			.def("getTopLeft", &Rectangle<float>::getTopLeft)
			.def("getTopRight", &Rectangle<float>::getTopRight)
			.def("getBottomLeft", &Rectangle<float>::getBottomLeft)
			.def("getBottomRight", &Rectangle<float>::getBottomRight)
			.def("setSize", &Rectangle<float>::setSize)
			.def("setBounds", &Rectangle<float>::setBounds)
			.def("setX", &Rectangle<float>::setX)
			.def("setY", &Rectangle<float>::setY)
			.def("setWidth", &Rectangle<float>::setWidth)
			.def("setHeight", &Rectangle<float>::setHeight)
			.def("withX", &Rectangle<float>::withX)
			.def("withY", &Rectangle<float>::withY)
			.def("withPosition", (Rectangle<float> (Rectangle<float>::*)(const Point<float> ) const noexcept)&Rectangle<float>::withPosition)
			.def("withPosition", (Rectangle<float> (Rectangle<float>::*)(const float, const float) const noexcept)&Rectangle<float>::withPosition)
			.def("withZeroOrigin", &Rectangle<float>::withZeroOrigin)
			.def("withWidth", &Rectangle<float>::withWidth)
			.def("withHeight", &Rectangle<float>::withHeight)
			.def("withSize", &Rectangle<float>::withSize)
			.def("setLeft", &Rectangle<float>::setLeft)
			.def("withLeft", &Rectangle<float>::withLeft)
			.def("setTop", &Rectangle<float>::setTop)
			.def("withTop", &Rectangle<float>::withTop)
			.def("setRight", &Rectangle<float>::setRight)
			.def("withRight", &Rectangle<float>::withRight)
			.def("setBottom", &Rectangle<float>::setBottom)
			.def("withBottom", &Rectangle<float>::withBottom)
			.def("translate", &Rectangle<float>::translate)
			.def("translated", &Rectangle<float>::translated)
			.def("expand", &Rectangle<float>::expand)
			.def("expanded", (Rectangle<float> (Rectangle<float>::*)(const float, const float) const noexcept)&Rectangle<float>::expanded)
			.def("expanded", (Rectangle<float> (Rectangle<float>::*)(const float) const noexcept)&Rectangle<float>::expanded)
			.def("reduce", &Rectangle<float>::reduce)
			.def("reduced", (Rectangle<float> (Rectangle<float>::*)(const float, const float) const noexcept)&Rectangle<float>::reduced)
			.def("reduced", (Rectangle<float> (Rectangle<float>::*)(const float) const noexcept)&Rectangle<float>::reduced)
			.def("removeFromTop", &Rectangle<float>::removeFromTop)
			.def("removeFromLeft", &Rectangle<float>::removeFromLeft)
			.def("removeFromRight", &Rectangle<float>::removeFromRight)
			.def("removeFromBottom", &Rectangle<float>::removeFromBottom)
			.def("contains", (bool (Rectangle<float>::*)(const float, const float) const noexcept)&Rectangle<float>::contains)
			.def("contains", (bool (Rectangle<float>::*)(const Point<float> ) const noexcept)&Rectangle<float>::contains)
			//.def("contains", (bool (Rectangle<float>::*)(const Rectangle<float> &) const noexcept)&Rectangle<float>::contains)
			.def("getConstrainedPoint", &Rectangle<float>::getConstrainedPoint)
			.def("getIntersection", &Rectangle<float>::getIntersection)
			.def("getUnion", &Rectangle<float>::getUnion)
			.def("enlargeIfAdjacent", &Rectangle<float>::enlargeIfAdjacent)
			.def("reduceIfPartlyContainedIn", &Rectangle<float>::reduceIfPartlyContainedIn)
			.def("transformedBy", &Rectangle<float>::transformedBy)
			.def("toString", &Rectangle<float>::toString)
			.def("leftTopRightBottom", &Rectangle<float>::leftTopRightBottom)
			.def("findAreaContainingPoints", &Rectangle<float>::findAreaContainingPoints)
			.def("intersectRectangles", &Rectangle<float>::intersectRectangles)
			.def("fromString", &Rectangle<float>::fromString)
			.def("toInt", &LRectangle::toInt)
	];
}

void LRelativeCoordinate::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<RelativePoint>("RelativePoint")
			.def(constructor<>())
			.def(constructor<const Point<float> &>())
			.def(constructor<float, float>())
			.def(constructor<const RelativeCoordinate &, const RelativeCoordinate &>())
			.def(constructor<const String &>())
			.def("resolve", &RelativePoint::resolve)
			.def("moveToAbsolute", &RelativePoint::moveToAbsolute)
			.def("toString", &RelativePoint::toString)
			.def("isDynamic", &RelativePoint::isDynamic)
		,
		class_<RelativeCoordinate>("JRelativeCoordinate")
		,
		class_<LRelativeCoordinate, bases<RelativeCoordinate> >("RelativeCoordinate")
			.def(constructor<const Expression &>())
			.def(constructor<const RelativeCoordinate &>())
			.def(constructor<double>())
			.def(constructor<const String &>())
			.def("resolve", &RelativeCoordinate::resolve)
			// .def("references", &LRelativeCoordinate::references) LINKER ERROR when using that
			.def("isRecursive", &RelativeCoordinate::isRecursive)
			.def("isDynamic", &RelativeCoordinate::isDynamic)
			.def("moveToAbsolute", &RelativeCoordinate::moveToAbsolute)
			.def("getExpression", &RelativeCoordinate::getExpression)
			.def("toString", &RelativeCoordinate::toString)
		,
		class_<RelativeParallelogram>("RelativeParallelogram")
			.def(constructor<>())
			.def(constructor<const Rectangle<float> &>())
			.def(constructor<const RelativePoint &, const RelativePoint &, const RelativePoint &>())
			.def(constructor<const String &, const String &, const String &>())
			.def("resolveThreePoints", &RelativeParallelogram::resolveThreePoints)
			.def("resolveFourCorners", &RelativeParallelogram::resolveFourCorners)
			.def("getBounds", &RelativeParallelogram::getBounds)
			.def("getPath", &RelativeParallelogram::getPath)
			.def("resetToPerpendicular", &RelativeParallelogram::resetToPerpendicular)
			.scope
			[
				def("getInternalCoordForPoint", &RelativeParallelogram::getInternalCoordForPoint),
				def("getPointForInternalCoord", &RelativeParallelogram::getPointForInternalCoord),
				def("getBoundingBox", &RelativeParallelogram::getBoundingBox)
			]
	];
}

void LTypeface::wrapForLua (lua_State *L)
{
    using namespace luabind;

	module(L)
    [
        class_<Typeface::Ptr>("TypefacePtr")
        ,
		class_<Typeface>("Typeface")
            .def("getName", &Typeface::getName)
            .def("getStyle", &Typeface::getStyle)
            .def("isSuitableForFont", &Typeface::isSuitableForFont)
            .def("getAscent", &Typeface::getAscent)
            .def("getDescent", &Typeface::getDescent)
            .def("getHeightToPointsFactor", &Typeface::getHeightToPointsFactor)
            .def("getStringWidth", &Typeface::getStringWidth)
            .def("getGlyphPositions", &Typeface::getGlyphPositions)
            .def("getOutlineForGlyph", &Typeface::getOutlineForGlyph)
            .def("getEdgeTableForGlyph", &Typeface::getEdgeTableForGlyph)
            .def("isHinted", &Typeface::isHinted)
            .def("applyVerticalHintingTransform",  &Typeface::applyVerticalHintingTransform)
            .scope
            [
                def("createSystemTypefaceFor", (Typeface::Ptr (*) (const Font &))&Typeface::createSystemTypefaceFor),
                def("createSystemTypefaceFor", (Typeface::Ptr (*) (const void *, size_t))&Typeface::createSystemTypefaceFor),
                def("setTypefaceCacheSize", &Typeface::setTypefaceCacheSize),
                def("clearTypefaceCache", &Typeface::clearTypefaceCache),
                def("scanFolderForFonts", &Typeface::scanFolderForFonts)
            ]
    ];
}
