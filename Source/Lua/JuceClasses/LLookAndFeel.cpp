#include "stdafx.h"
#include "LLookAndFeel.h"

void LLookAndFeel::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
	[
        class_<LookAndFeel_V3>("LookAndFeel_V3")
        ,
        class_<LookAndFeelBase, LookAndFeel_V3>("LookAndFeelBase")
            .def(constructor<>())
            .def("setMethod", &LookAndFeelBase::setMethod)
    ];
}
