#include "stdafx.h"
#include "LColourGradient.h"

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