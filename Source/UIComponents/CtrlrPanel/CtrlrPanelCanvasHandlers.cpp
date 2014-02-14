#include "stdafx.h"
#include "CtrlrPanelCanvas.h"
#include "CtrlrMacros.h"
#include "CtrlrPanelEditor.h"
#include "CtrlrProcessor.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrComponents/CtrlrComponentTypeManager.h"
#include "CtrlrComponents/Groups/CtrlrTabsComponent.h"
#include "CtrlrComponents/Groups/CtrlrGroup.h"
#include "CtrlrLog.h"

void CtrlrPanelCanvas::handleRightClickOnMultiSelection(const MouseEvent &e)
{
	PopupMenu m;
	PopupMenu componentSubMenu = CtrlrComponentTypeManager::getComponentMenu(true);
	getEditMenu(m);
	m.addSeparator();
	m.addSubMenu ("Replace with", componentSubMenu, true);
	const int ret = m.show();

	if (ret >= 2048 && ret < 4096)
	{
		handleEditMenu (ret, e);
	}
	else if (ret < 1024 && ret > 10)
	{
		String replaceWithComponentName;
		PopupMenu::MenuItemIterator iterator((const PopupMenu &)componentSubMenu);
		while (iterator.next())
		{
			if (iterator.subMenu)
			{
				PopupMenu::MenuItemIterator iterator2(*iterator.subMenu);
				while (iterator2.next())
				{
					if (iterator2.itemId == ret)
					{
						replaceWithComponentName = iterator2.itemName;
						break;
					}
				}
			}
		}

		if (!replaceWithComponentName.isEmpty())
		{
            Array <CtrlrComponent *> items;
            
            if (owner.getSelection())
                items = owner.getSelection()->getItemArray ();

			for (int i=0; i<items.size(); i++)
			{
				if (items[i])
				{
					replaceComponent (items[i]->getOwner(), replaceWithComponentName);
				}
			}
		}
	}
}

void CtrlrPanelCanvas::handleRightClickOnCanvas(const MouseEvent &e)
{
	const bool em = getOwner().getProperty(Ids::uiPanelEditMode);

	if (!em)
	{
		PopupMenu m = getRightClickComponentMenu(e);
		handleComponentPopupMenu(e, m.show());
		return;
	}

	PopupMenu m;

	if (em)
	{
		m = CtrlrComponentTypeManager::getComponentMenu(em);
		getEditMenu(m);
	}
	else
	{
		m = getRightClickComponentMenu(e);
	}

	const int ret = m.show();

	if (ret >= 4096)
	{
		handleComponentPopupMenu(e, ret);
	}
	else if (ret == 1024)
	{
		getOwner().setProperty (Ids::uiPanelEditMode, !em);
		getOwner().editModeChanged();
	}
	else if (ret < 1024 && ret > 10)
	{
		PopupMenu::MenuItemIterator iterator((const PopupMenu &)m);
		while (iterator.next())
		{
			if (iterator.subMenu)
			{
				PopupMenu::MenuItemIterator iterator2(*iterator.subMenu);
					while (iterator2.next())
				{
					if (iterator2.itemId == ret)
					{
						addNewComponent (iterator2.itemName, e.getPosition(), e.eventComponent);
					}
				}
			}
		}
	}
	else if (ret >= 2048 && ret < 4096)
	{
		handleEditMenu (ret, e);
	}
}

void CtrlrPanelCanvas::handleRightClickOnTabs(const MouseEvent &e)
{
}

void CtrlrPanelCanvas::handleRightClickOnComponent(const MouseEvent &e)
{
	CtrlrComponent *c = findEventComponent(e);

	if (c == 0)
		return;

	if (dynamic_cast<ResizableBorderComponent*>(e.eventComponent) == 0 && getOwner().getSelection())
	{
		getOwner().getSelection()->selectOnly (c);
	}

	PopupMenu m;
	PopupMenu componentSubMenu = CtrlrComponentTypeManager::getComponentMenu(true);
	m.addSectionHeader ("Actions");
	m.addItem (512, "Export component");
	m.addItem (513, "Lock", true, c->getProperty(Ids::componentIsLocked));

	m.addSectionHeader ("Layout");
	m.addItem (1024, "Send to back");
	m.addItem (1025, "Send to front");

	m.addSeparator();
	m.addSubMenu ("Replace with", componentSubMenu, true);

	m.addSeparator();
	getEditMenu(m);

	m.addSeparator();
	if (CtrlrComponentTypeManager::isGroupingComponent(c))
	{
		m.addItem (1026, "Delete with children");
		m.addItem (1027, "Copy with children");
	}

	const int ret = m.show();

	if (ret == 512)
	{
		exportSelectedComponents();
	}
	else if (ret == 513)
	{
		c->setProperty (Ids::componentIsLocked, !c->getProperty(Ids::componentIsLocked));
	}
	if (ret == 1024)
	{
		c->toBack();
		c->setProperty (Ids::componentSentBack, true);
	}
	else if (ret == 1025)
	{
		c->toFront(false);
		c->setProperty (Ids::componentSentBack, false);
	}
	else if (ret == 1026)
	{
		deleteWithChildren (c);
	}
	else if (ret == 1027)
	{
		copyWithChildren (c);
	}
	else if (ret >= 2048 && ret < 4096)
	{
		handleEditMenu (ret, e);
	}
	else if (ret < 1024 && ret > 10)
	{
		PopupMenu::MenuItemIterator iterator((const PopupMenu &)componentSubMenu);
		while (iterator.next())
		{
			if (iterator.subMenu)
			{
				PopupMenu::MenuItemIterator iterator2(*iterator.subMenu);
				while (iterator2.next())
				{
					if (iterator2.itemId == ret)
					{
						if (c)
						{
							replaceComponent (c->getOwner(), iterator2.itemName);
							return;
						}
					}
				}
			}
		}
	}
}

void CtrlrPanelCanvas::replaceComponent (CtrlrModulator &modulator, const String &targetComponentType)
{
	CtrlrComponent *oldComponent = modulator.getComponent();
	CtrlrComponent *newComponent = nullptr;

	/* detach the existing component so it doesn't get notified about anything, the pointer will be invalid */
    if (getOwner().getSelection())
    {
        getOwner().getSelection()->deselectAll();
        getOwner().getSelection()->dispatchPendingMessages();
        getOwner().getSelection()->removeChangeListener(oldComponent);
    }
    
	if (oldComponent)
	{
		/* keep a copy of the old properties, we need to find out if the component is in a group */
		ValueTree oldComponentProperties = oldComponent->getObjectTree().createCopy();

		modulator.setComponentType(targetComponentType, false);

		/* get the new component pointer and attach it */
		newComponent = modulator.getComponent();
        if (getOwner().getSelection())
            getOwner().getSelection()->addChangeListener (newComponent);
        
		addAndMakeVisibleNg (modulator.getComponent(), nullptr, true);

		/* attach the new component to any group components the old component was int */
		if (oldComponentProperties.hasProperty(Ids::componentGroupName))
		{
			CtrlrGroup *group = dynamic_cast<CtrlrGroup*>(owner.getOwner().getComponent(oldComponentProperties.getProperty(Ids::componentGroupName)));
			if (group)
			{
				group->setOwned (newComponent, true);
			}
		}

		if (oldComponentProperties.hasProperty(Ids::componentTabName))
		{
			CtrlrTabsComponent *tabs = dynamic_cast<CtrlrTabsComponent*>(owner.getOwner().getComponent(oldComponentProperties.getProperty(Ids::componentTabName)));
			if (tabs)
			{
				tabs->setOwned (newComponent, oldComponentProperties.getProperty(Ids::componentTabId), true);
			}
		}

		/* copy any old properties to the new component */
        for (int i=0; i<oldComponentProperties.getNumProperties(); i++)
		{
			const Identifier propName 	= oldComponentProperties.getPropertyName(i);
			const var propValue			= oldComponentProperties.getProperty(propName);

			if (propName != Ids::uiType)
			{
				if (newComponent->getObjectTree().hasProperty(propName))
					newComponent->setProperty (propName, propValue);
			}
		}
	}
}

void CtrlrPanelCanvas::getEditMenu(PopupMenu &m)
{
	m.addSectionHeader ("Edit");
	m.addItem (Copy, "Copy", getSelection().getNumSelected() ? true : false);
	m.addItem (Paste, "Paste");
	m.addItem (Cut, "Cut", getSelection().getNumSelected() ? true : false);
	m.addItem (Delete, "Delete", getSelection().getNumSelected() ? true : false);

	if (getSelection().getNumSelected() > 1)
	{
		m.addSectionHeader ("Align");
		m.addItem (AlignToTop, "Align to top", true, false);
		m.addItem (AlignToBottom, "Align to bottom", true, false);
		m.addItem (AlignToLeft, "Align to left", true, false);
		m.addItem (AlignToRight, "Align to right", true, false);
	}
}

void CtrlrPanelCanvas::handleEditMenu (const int returnCode, const MouseEvent &e)
{
	switch ((EditMenuItems)returnCode)
	{
		case Copy:
			editMenuCopy(&e);
			break;

		case Paste:
			editMenuPaste(e);
			break;

		case Cut:
			editMenuCopy(&e);
			editMenuDelete();
			break;

		case Delete:
			editMenuDelete();
			break;

		case AlignToTop:
		case AlignToLeft:
		case AlignToBottom:
		case AlignToRight:
			alignSelection ((EditMenuItems)returnCode);
			break;

		case FitToRect:
			fitSelection();
			break;

		default:
			break;
	}
}

void CtrlrPanelCanvas::handleLeftClickOnComponent(const MouseEvent &e)
{
	CtrlrComponent *c  = findEventComponent(e);

	if (c)
	{
		if (getSelection().isSelected(c))
		{
			getSelection().deselect(c);
		}
		else
		{
			getSelection().addToSelection(c);
		}
	}
}

void CtrlrPanelCanvas::copyWithChildren(CtrlrComponent *c)
{
	if (c)
	{
		ValueTree clipboardTree("groupTree");
		ValueTree groupTree = c->getOwner().getObjectTree().createCopy();

		Array<CtrlrComponent*> children = c->getOwnedChildren();
		for (int i=0; i<children.size(); i++)
		{
			groupTree.addChild (children[i]->getOwner().getObjectTree().createCopy(), -1, 0);
		}
		clipboardTree.addChild (groupTree, -1, 0);

		SystemClipboard::copyTextToClipboard (XML2STR(clipboardTree));
	}
}

void CtrlrPanelCanvas::deleteWithChildren(CtrlrComponent *c)
{
	if (c)
	{
        if (getOwner().getSelection())
            getOwner().getSelection()->deselectAll();
        
		Array<CtrlrComponent*> children = c->getOwnedChildren();
		for (int i=0; i<children.size(); i++)
		{
			removeComponent (children[i], false);
		}

		removeComponent (c, false);
		sendChangeMessage();
	}
}

void CtrlrPanelCanvas::pasteGroupComponent(const ValueTree &groupTree, const int destinationX, const int destinationY)
{
	if (groupTree.hasType ("groupTree"))
	{
		CtrlrComponent *parent		= addNewComponent (groupTree.getChild(0), 0, true);
		if (destinationX >= 0 && destinationY >= 0)
			parent->setTopLeftPosition (destinationX, destinationY);
		else
			parent->setTopLeftPosition (parent->getX()+(parent->getWidth()/2), parent->getY()+(parent->getHeight()/2));

		CtrlrGroup *group			= dynamic_cast<CtrlrGroup*>(parent);
		CtrlrTabsComponent *tabs	= dynamic_cast<CtrlrTabsComponent*>(parent);

		for (int i=0; i<groupTree.getChild(0).getNumChildren(); i++)
		{
			if (groupTree.getChild(0).getChild(i).hasType(Ids::modulator))
			{
				CtrlrComponent *child = addNewComponent (groupTree.getChild(0).getChild(i), 0, true);
				if (group && child)
				{
					group->setOwned(child, true);
				}

				if (tabs && child)
				{
					tabs->setOwned(child, child->getProperty(Ids::componentTabId), true);
				}
			}
		}
	}
}

void CtrlrPanelCanvas::pasteGroupComponent(const ValueTree &groupTree, const MouseEvent &e)
{
	pasteGroupComponent (groupTree, e.x, e.y);
}
