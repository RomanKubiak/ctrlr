#include "stdafx.h"
#include "LRectangle.h"

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
			.def("contains", (bool (Rectangle<int>::*)(const Rectangle<int> &) const noexcept)&Rectangle<int>::contains)
			.def("getConstrainedPoint", &Rectangle<int>::getConstrainedPoint)
			//.def("intersects", &Rectangle<int>::intersects)
			.def("getIntersection", &Rectangle<int>::getIntersection)
			.def("getUnion", &Rectangle<int>::getUnion)
			.def("enlargeIfAdjacent", &Rectangle<int>::enlargeIfAdjacent)
			.def("reduceIfPartlyContainedIn", &Rectangle<int>::reduceIfPartlyContainedIn)
			.def("transformed", &Rectangle<int>::transformed)
			// .def("getSmallestIntegerContainer", &Rectangle<int>::getSmallestIntegerContainer)
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
	];
}
