#include "stdafx.h"
#include "CtrlrPanelUndoManager.h"
#include "CtrlrPanel/CtrlrPanel.h"

CtrlrPanelUndoManager::CtrlrPanelUndoManager(CtrlrPanel &_owner) : owner(_owner)
{
}

CtrlrPanelUndoManager::~CtrlrPanelUndoManager()
{
}

void CtrlrPanelUndoManager::beginNewTransaction() noexcept
{
	UndoManager::beginNewTransaction();
	owner.actionPerformed();
}

void CtrlrPanelUndoManager::beginNewTransaction(const String& actionName) noexcept
{
	UndoManager::beginNewTransaction(actionName);
	owner.actionPerformed();
}

bool CtrlrPanelUndoManager::undo()
{
	bool result = UndoManager::undo();
	if (result)
	{
		owner.actionUndone();
	}
	return result;
}

bool CtrlrPanelUndoManager::redo()
{
	bool result = UndoManager::redo();
	if (result)
	{
		owner.actionPerformed();
	}
	return result;
}
