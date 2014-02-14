#include "stdafx.h"
#include "LValue.h"
#include <luabind/operator.hpp>

void LValue::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Value>("Value")
			.def(constructor<>())
			.def(constructor<const Value &>())
			.def(constructor<const var &>())
			.def("getValue", &Value::getValue)
			.def("toString", &Value::toString)
			.def("setValue", &Value::setValue)
			.def("referTo", &Value::referTo)
			.def("refersToSameSourceAs", &Value::refersToSameSourceAs)
			.def("addListener", &Value::addListener)
			.def("removeListener", &Value::removeListener)
			.def("getValueSource", &Value::getValueSource)
	];
}