#include "stdafx.h"
#include "LComponentPeer.h"

void LComponentPeer::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<ComponentPeer>("ComponentPeer")
			.enum_("StyleFlags")
			[
				value("windowAppearsOnTaskbar", (1 << 0)),
				value("windowIsTemporary", (1 << 1)),
				value("windowIgnoresMouseClicks", (1 << 2)),
				value("windowHasTitleBar", (1 << 3)),
				value("windowIsResizable", (1 << 4)),
				value("windowHasMinimiseButton", (1 << 5)),
				value("windowHasMaximiseButton", (1 << 6)),
				value("windowHasCloseButton", (1 << 7)),
				value("windowHasDropShadow", (1 << 8)),
				value("windowRepaintedExplictly", (1 << 9)),
				value("windowIgnoresKeyPresses", (1 << 10)),
				value("windowIsSemiTransparent", (1 << 31))
			]
	];
}