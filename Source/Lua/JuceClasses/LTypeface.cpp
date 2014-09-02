#include "stdafx.h"
#include "LTypeface.h"

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
