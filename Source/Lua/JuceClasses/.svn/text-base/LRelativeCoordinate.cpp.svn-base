#include "stdafx.h"
#include "LRelativeCoordinate.h"

void LRelativeCoordinate::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<RelativePoint>("RelativePoint")
			.def(constructor<>())
			.def(constructor<const Point<float> &>())
			.def(constructor<float, float>())
			.def(constructor<const RelativeCoordinate &, const RelativeCoordinate &>())
			.def(constructor<const String &>())
			.def("resolve", &RelativePoint::resolve)
			.def("moveToAbsolute", &RelativePoint::moveToAbsolute)
			.def("toString", &RelativePoint::toString)
			.def("isDynamic", &RelativePoint::isDynamic)
		,
		class_<RelativeCoordinate>("JRelativeCoordinate")
		,
		class_<LRelativeCoordinate, bases<RelativeCoordinate> >("RelativeCoordinate")
			.def(constructor<const Expression &>())
			.def(constructor<const RelativeCoordinate &>())
			.def(constructor<double>())
			.def(constructor<const String &>())
			.def("resolve", &RelativeCoordinate::resolve)
			// .def("references", &LRelativeCoordinate::references) LINKER ERROR when using that
			.def("isRecursive", &RelativeCoordinate::isRecursive)
			.def("isDynamic", &RelativeCoordinate::isDynamic)
			.def("moveToAbsolute", &RelativeCoordinate::moveToAbsolute)
			.def("getExpression", &RelativeCoordinate::getExpression)
			.def("toString", &RelativeCoordinate::toString)
		,
		class_<RelativeParallelogram>("RelativeParallelogram")
			.def(constructor<>())
			.def(constructor<const Rectangle<float> &>())
			.def(constructor<const RelativePoint &, const RelativePoint &, const RelativePoint &>())
			.def(constructor<const String &, const String &, const String &>())
			.def("resolveThreePoints", &RelativeParallelogram::resolveThreePoints)
			.def("resolveFourCorners", &RelativeParallelogram::resolveFourCorners)
			.def("getBounds", &RelativeParallelogram::getBounds)
			.def("getPath", &RelativeParallelogram::getPath)
			.def("resetToPerpendicular", &RelativeParallelogram::resetToPerpendicular)
			.scope
			[
				def("getInternalCoordForPoint", &RelativeParallelogram::getInternalCoordForPoint),
				def("getPointForInternalCoord", &RelativeParallelogram::getPointForInternalCoord),
				def("getBoundingBox", &RelativeParallelogram::getBoundingBox)
			]
	];
}