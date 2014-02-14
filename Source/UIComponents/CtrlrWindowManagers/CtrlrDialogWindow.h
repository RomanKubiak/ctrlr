#ifndef __CTRLR_DIALOG_WINDOW__
#define __CTRLR_DIALOG_WINDOW__

#include "CtrlrMacros.h"

class CtrlrDialogWindow
{
	public:
		
		static const int showModalDialog (const String &title, Component *content, const bool resizable, Component *parent);
};

#endif