#include "stdafx.h"
#include "LPoint.h"

void LPoint::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Point<float> >("Point")
			.def(constructor<>())
			.def(constructor<const Point<float> &>())
			.def(constructor<float,float>())
			.def("isOrigin", &Point<float>::isOrigin)
			.def("getX", &Point<float>::getX)
			.def("getY", &Point<float>::getY)
			.def("setX", &Point<float>::setX)
			.def("setY", &Point<float>::setY)
			.def("withX", &Point<float>::withX)
			.def("withY", &Point<float>::withY)
			.def("setXY", &Point<float>::setXY)
			.def("addXY", &Point<float>::addXY)
			.def("translated", &Point<float>::translated)
			.def("getDistanceFromOrigin", &Point<float>::getDistanceFromOrigin)
			.def("getDistanceFrom", &Point<float>::getDistanceFrom)
			.def("getAngleToPoint", &Point<float>::getAngleToPoint)
			.def("getPointOnCircumference", (Point<float> (Point<float>::*)(const float, const float) const noexcept)&Point<float>::getPointOnCircumference)
			.def("getPointOnCircumference", (Point<float> (Point<float>::*)(const float, const float, const float) const noexcept)&Point<float>::getPointOnCircumference)
			.def("applyTransform", &Point<float>::applyTransform)
			.def("transformedBy", &Point<float>::transformedBy)
			.def("toString", &Point<float>::toString)
			.def_readwrite("x",&Point<float>::x)
			.def_readwrite("y",&Point<float>::y)
	];
}