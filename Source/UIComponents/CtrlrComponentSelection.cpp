#include "stdafx.h"
#include "CtrlrComponentSelection.h"
#include "CtrlrMacros.h"
#include "CtrlrProcessor.h"

CtrlrComponentSelection::CtrlrComponentSelection(CtrlrPanelEditor &_owner) : owner(_owner)
{
}

CtrlrComponentSelection::~CtrlrComponentSelection()
{
}

void CtrlrComponentSelection::itemSelected (CtrlrComponent *selectedComponent)
{
	if (!selectedComponent->getTransform().isIdentity())
	{
		selectedComponent->setTransform (AffineTransform::identity);
	}
}

void CtrlrComponentSelection::itemDeselected (CtrlrComponent *deselectedComponent)
{
	if (!deselectedComponent->getTransform().isIdentity())
	{
		deselectedComponent->setTransform (AffineTransform::identity);
	}
}

void CtrlrComponentSelection::deselectAll()
{
	for (int i=0; i<getNumSelected(); i++)
	{
		if (getSelectedItem(i))
		{
			getSelectedItem(i)->setTransform (AffineTransform::identity);
		}
	}
	SelectedItemSet<CtrlrComponent*>::deselectAll();
}