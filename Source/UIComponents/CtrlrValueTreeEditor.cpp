#include "stdafx.h"
#include "CtrlrValueTreeEditor.h"
#include "CtrlrInlineUtilitiesGUI.h"

//=========================================================================================================
bool CtrlrValueTreeEditorTree::keyPressed (const KeyPress &key)
{
	if (getNumSelectedItems() == 1)
	{
		if (getSelectedItem(0))
		{
			CtrlrValueTreeEditorItem *item = dynamic_cast<CtrlrValueTreeEditorItem*>(getSelectedItem(0));

			if (item != nullptr)
			{
				item->keyPressed(key);
			}
		}
	}

	return (TreeView::keyPressed(key));
}

//=========================================================================================================
CtrlrValueTreeEditorItem::CtrlrValueTreeEditorItem(CtrlrValueTreeEditorLookProvider &_provider, ValueTree _treeToEdit, const Identifier &_nameIdentifier)
	: treeToEdit(_treeToEdit), provider(_provider), nameIdentifier(_nameIdentifier)
{
	treeToEdit.addListener (this);
}

CtrlrValueTreeEditorItem::~CtrlrValueTreeEditorItem()
{
	treeToEdit.removeListener (this);
}

bool CtrlrValueTreeEditorItem::mightContainSubItems()
{
	return (treeToEdit.getNumChildren() ? true : false);
}

String CtrlrValueTreeEditorItem::getUniqueName () const
{
	return (provider.getUniqueName(treeToEdit));
}

void CtrlrValueTreeEditorItem::itemSelectionChanged (bool isNowSelected)
{
}

int	CtrlrValueTreeEditorItem::getItemWidth () const
{
	return (jmax<int>(128, provider.getItemFont(treeToEdit).getStringWidth (provider.getUniqueName(treeToEdit))));
}

int	CtrlrValueTreeEditorItem::getItemHeight () const
{
	return (provider.getItemHeight(treeToEdit));
}

bool CtrlrValueTreeEditorItem::canBeSelected () const
{
	return (provider.canBeSelected(treeToEdit));
}

void CtrlrValueTreeEditorItem::itemOpennessChanged (bool isNowOpen)
{
	if (isNowOpen)
	{
		if (getNumSubItems() == 0)
		{
			for (int i=0; i<treeToEdit.getNumChildren(); i++)
			{
				addSubItem (new CtrlrValueTreeEditorItem (provider, treeToEdit.getChild(i), nameIdentifier));
			}
		}
	}
	else
	{
		clearSubItems();
	}

	provider.itemOpennessChanged(isNowOpen);
}

var CtrlrValueTreeEditorItem::getDragSourceDescription ()
{
	Array <ValueTree> selectedTreeItems;
	String returnValue;

	if (getOwnerView())
	{
		for (int i=0; i<getOwnerView()->getNumSelectedItems(); i++)
		{
			CtrlrValueTreeEditorItem *item = dynamic_cast<CtrlrValueTreeEditorItem*>(getOwnerView()->getSelectedItem(i));
			selectedTreeItems.add (item->getTree());
		}
	}

	if ((returnValue = provider.getDragSourceDescription(selectedTreeItems)) != String::empty)
	{
		return (returnValue);
	}
	else
	{
		for (int i=0; i<selectedTreeItems.size(); i++)
		{
			returnValue << selectedTreeItems[i].getType().toString() + ";";
		}
	}

	return (returnValue);
}

bool CtrlrValueTreeEditorItem::isInterestedInDragSource (const DragAndDropTarget::SourceDetails &dragSourceDetails)
{
	return (provider.isInterestedInDragSource (treeToEdit, dragSourceDetails));
}

void CtrlrValueTreeEditorItem::paintItem (Graphics &g, int width, int height)
{
	Image icon = provider.getIconForItem (treeToEdit);
	if (isSelected())
	{
		drawSelectionRectangle (g,width,height);
	}

	g.setColour (Colours::black);

	AttributedString as = provider.getDisplayString(treeToEdit);
	as.setJustification (Justification (Justification::centredLeft));
	as.draw (g, Rectangle <float> (24.0, 0.0, width - 24.0, height));
	g.drawImageWithin (icon, 4, 0, 16, height, RectanglePlacement (RectanglePlacement::centred));
}

void CtrlrValueTreeEditorItem::itemDropped (const DragAndDropTarget::SourceDetails &dragSourceDetails, int insertIndex)
{
	provider.itemDropped (treeToEdit, dragSourceDetails, insertIndex);
}

void CtrlrValueTreeEditorItem::itemClicked (const MouseEvent &e)
{
	provider.itemClicked (e, treeToEdit);
}

void CtrlrValueTreeEditorItem::itemDoubleClicked (const MouseEvent &e)
{
	provider.itemDoubleClicked (e, treeToEdit);
}

void CtrlrValueTreeEditorItem::keyPressed (const KeyPress &key)
{
	if (key.getKeyCode() == 65649) // F2
	{
		if (!provider.canBeRenamed(treeToEdit))
			return;

		AlertWindow wnd("Rename item","Rename current item type: " + treeToEdit.getType().toString(), AlertWindow::QuestionIcon, getOwnerView());
		wnd.addTextEditor ("name", treeToEdit.getProperty(nameIdentifier), "Name:", false);
		wnd.addButton ("OK", 1, KeyPress(KeyPress::returnKey));
		wnd.addButton ("Cancel", 0, KeyPress(KeyPress::escapeKey));
		if (wnd.runModalLoop())
		{
			if (provider.renameItem (treeToEdit, wnd.getTextEditorContents("name")))
			{
				treeToEdit.setProperty (Ids::name, wnd.getTextEditorContents("name"), nullptr);
			}

			provider.triggerAsyncUpdate();
		}
	}
}

void CtrlrValueTreeEditorItem::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	repaintItem();
}
