#include "stdafx.h"
#include "LAffineTransform.h"

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
