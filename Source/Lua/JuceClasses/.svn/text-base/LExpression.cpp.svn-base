#include "stdafx.h"
#include "LExpression.h"

void LExpression::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Expression::Scope>("Scope")
		,
		class_<Expression::Symbol>("Symbol")
		,
		class_<Expression>("Expression")
			.def(constructor<>())
			.def(constructor<double>())
			.def(constructor<const String &>())
			.def(constructor<const Expression &>())
			.def("toString", &Expression::toString)
			.def("evaluate", (double (Expression::*) () const) &Expression::evaluate)
			.def("evaluate", (double (Expression::*) (const Expression::Scope &) const) &Expression::evaluate)
			.def("evaluate", (double (Expression::*) (const Expression::Scope &, String &) const) &Expression::evaluate)
			.def("adjustedToGiveNewResult", &Expression::adjustedToGiveNewResult)
			.def("withRenamedSymbol", &Expression::withRenamedSymbol)
			.def("referencesSymbol", &Expression::referencesSymbol)
			.def("usesAnySymbols", &Expression::usesAnySymbols)
			.def("findReferencedSymbols", &Expression::findReferencedSymbols)
			.def("getType", &Expression::getType)
			.def("getSymbolOrFunction", &Expression::getSymbolOrFunction)
			.def("getNumInputs", &Expression::getNumInputs)
			.def("getInput", &Expression::getInput)
	];
}