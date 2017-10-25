#include "stdafx.h"
#include "CtrlrPanelUndoManager.h"
#include "CtrlrPanel/CtrlrPanel.h"

CtrlrPanelUndoManager::CtrlrPanelUndoManager(CtrlrPanel &_owner) : owner(_owner), transactionPending(false),isUndoing(false),isRedoing(false),isClearingHistory(false)
{
	UndoManager::addChangeListener(this);
}

CtrlrPanelUndoManager::~CtrlrPanelUndoManager()
{
	UndoManager::removeChangeListener(this);
}

void CtrlrPanelUndoManager::beginTransaction()
{
	transactionPending = true;
}

void CtrlrPanelUndoManager::endTransaction()
{
	if (transactionPending)
	{
		if (getNumActionsInCurrentTransaction() > 0)
		{
			owner.actionPerformed();
		}
	}
	transactionPending = false;
}

bool CtrlrPanelUndoManager::undo()
{
	isUndoing = true;
	bool result = UndoManager::undo();
	if (result)
	{
		owner.actionUndone();
	}
	else
	{
		isUndoing = false;
	}
	return result;
}

bool CtrlrPanelUndoManager::redo()
{
	isRedoing = true;
	bool result = UndoManager::redo();
	if (result)
	{
		owner.actionPerformed();
	}
	else
	{
		isRedoing = false;
	}
	return result;
}

void CtrlrPanelUndoManager::clearUndoHistory()
{
	isClearingHistory = true;
	UndoManager::clearUndoHistory();
	owner.setSavePoint();
}

void CtrlrPanelUndoManager::changeListenerCallback(ChangeBroadcaster* source)
{
	if (!transactionPending && !isUndoing && !isRedoing && !isClearingHistory)
	{
		owner.actionPerformed();
	}
	else
	{
		isUndoing = false;
		isRedoing = false;
		isClearingHistory = false;
	}
}
