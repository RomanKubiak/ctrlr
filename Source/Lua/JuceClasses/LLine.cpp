#include "stdafx.h"
#include "LLine.h"

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
