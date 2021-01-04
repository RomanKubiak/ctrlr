#pragma once

#include "CtrlrMacros.h"

class CtrlrPanel;

class CtrlrPanelSchemeMigration
{
	public:
		CtrlrPanelSchemeMigration(CtrlrPanel &_owner);

	private:
		CtrlrPanel &owner;
};
