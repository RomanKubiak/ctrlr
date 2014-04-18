#ifndef __CTRLR_PANEL_SCHEME_MIGRATION__
#define __CTRLR_PANEL_SCHEME_MIGRATION__

#include "CtrlrMacros.h"

class CtrlrPanel;

class CtrlrPanelSchemeMigration
{
	public:
		CtrlrPanelSchemeMigration(CtrlrPanel &_owner);

	private:
		CtrlrPanel &owner;
};

#endif
