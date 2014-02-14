#include "stdafx.h"
#include "LAttributedString.h"

void LAttributedString::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<AttributedString>("AttributedString")
			.def(constructor<const String &>())
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
				.def(constructor<const Range<int> &, const Colour &>())
				.def(constructor<const Range<int> &, const Font &>())
				.def("getFont", &AttributedString::Attribute::getFont)
				.def("getColour", &AttributedString::Attribute::getColour)
			]
	];
}