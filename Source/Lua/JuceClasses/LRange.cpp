#include "stdafx.h"
#include "LRange.h"

void LRange::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Range<int> >("Range")
		.def(constructor<>())
		.def(constructor<const Range<int> &>())
		.def(constructor<int,int>())
		.def("getStart", &Range<int>::getStart)
		.def("getLength", &Range<int>::getLength)
		.def("getEnd", &Range<int>::getEnd)
		.def("isEmpty", &Range<int>::isEmpty)
		.def("setStart", &Range<int>::setStart)
		.def("withStart", &Range<int>::withStart)
		.def("movedToStartAt", &Range<int>::movedToStartAt)
		.def("setEnd", &Range<int>::setEnd)
		.def("withEnd", &Range<int>::withEnd)
		.def("movedToEndAt", &Range<int>::movedToEndAt)
		.def("setLength", &Range<int>::setLength)
		.def("withLength", &Range<int>::withLength)
		.def("clipValue", &Range<int>::clipValue)
		.def("intersects", &Range<int>::intersects)
		.def("getIntersectionWith", &Range<int>::getIntersectionWith)
		.def("getUnionWith", (Range<int> (Range<int>::*)(Range<int>) const)&Range<int>::getUnionWith)

		.def("constrainRange", &Range<int>::constrainRange)
		.def("contains", (bool (Range<int>::*)(const int) const) &Range<int>::contains)
		.def("contains", (bool (Range<int>::*)(const Range<int>) const) &Range<int>::contains)
	];
}
