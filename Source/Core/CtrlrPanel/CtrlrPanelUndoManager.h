#ifndef __CTRLR_PANEL_UNDO_MANAGER__
#define __CTRLR_PANEL_UNDO_MANAGER__

#include "CtrlrMacros.h"

class CtrlrPanel;

class CtrlrPanelUndoManager : public UndoManager
{
	public:
		CtrlrPanelUndoManager (CtrlrPanel &_owner);
		~CtrlrPanelUndoManager();
		void beginNewTransaction() noexcept;
		void beginNewTransaction(const String& actionName) noexcept;
		bool undo();
		bool redo();

	private:
		CtrlrPanel &owner;
};

#endif
