#include "stdafx.h"
#include "LFont.h"

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
