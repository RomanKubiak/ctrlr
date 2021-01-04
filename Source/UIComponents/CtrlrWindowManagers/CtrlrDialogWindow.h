#pragma once

#include "CtrlrMacros.h"

class CtrlrDialogWindow
{
	public:
		
		static const int showModalDialog (const String &title, Component *content, const bool resizable, Component *parent);
};
