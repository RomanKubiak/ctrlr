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
			.def("getTypefaceStyle", &Font::getTypefaceStyle)
			.def("withTypefaceStyle", &Font::withTypefaceStyle)
			.def("getHeight", &Font::getHeight)
			.def("withPointHeight", &Font::withPointHeight)
			.def("setHeightWithoutChangingWidth", &Font::setHeightWithoutChangingWidth)
			.def("getDescent", &Font::getDescent)
			.def("withStyle", &Font::withStyle)
			.def("setBold", &Font::setBold)
			.def("isBold", &Font::isBold)
			.def("italicised", &Font::italicised)
			.def("setUnderline", &Font::setUnderline)
			.def("getHorizontalScale", &Font::getHorizontalScale)
			.def("setHorizontalScale", &Font::setHorizontalScale)
			.def("withExtraKerningFactor", &Font::withExtraKerningFactor)
			.def("setSizeAndStyle", (void (Font::*)(float, int, float, float))&Font::setSizeAndStyle)
			.def("setSizeAndStyle", (void (Font::*)(float, const String &, float, float))&Font::setSizeAndStyle)
			.def("getStringWidth", &Font::getStringWidth)
			.def("getGlyphPositions", &Font::getGlyphPositions)
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