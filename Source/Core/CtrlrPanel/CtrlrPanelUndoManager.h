#pragma once

#include "CtrlrMacros.h"

class CtrlrPanel;

class CtrlrPanelUndoManager : public UndoManager, ChangeListener
{
	public:
		CtrlrPanelUndoManager (CtrlrPanel &_owner);
		~CtrlrPanelUndoManager();
		void beginTransaction();
		void endTransaction();
		bool undo();
		bool redo();
		void clearUndoHistory();
		void changeListenerCallback(ChangeBroadcaster* source);

	private:
		CtrlrPanel &owner;
		bool transactionPending,isUndoing,isRedoing,isClearingHistory;
};
