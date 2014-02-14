#include "stdafx.h"
#include "LGlyphArrangement.h"

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