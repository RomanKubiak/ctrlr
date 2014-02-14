#include "stdafx.h"
#include "LColour.h"

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
			.def("greyLevel", &Colour::greyLevel)
			.def("toString", &Colour::toString)
			.def("fromString", &Colour::fromString)
			.def("toDisplayString", &Colour::toDisplayString)
	];
}