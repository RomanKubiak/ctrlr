#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrComponents/CtrlrComponent.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrPanel/CtrlrPanelCanvas.h"
#include "CtrlrPanelModulatorList.h"
#include "CtrlrInlineUtilitiesGUI.h"

/* ********************************************************************************** */
CtrlrPanelModulatorList::CtrlrPanelModulatorList (CtrlrPanel &_owner)
    : owner(_owner),
      modulatorList (0),
	  modulatorListTree(owner)
{
	addAndMakeVisible (&modulatorListTree);
	modulatorListTree.setVisible (false);

	owner.setProperty (Ids::uiPanelModulatorListViewTree, false);

    addAndMakeVisible (modulatorList = new TableListBox ("Modulator List", this));
    modulatorList->setName (L"modulatorList");
	modulatorList->getHeader().setStretchToFitActive(true);
	modulatorList->setMultipleSelectionEnabled (true);
	modulatorList->setHeaderHeight (20);

	if (owner.getProperty (Ids::panelModulatorListColumns).toString() != COMBO_ITEM_NONE)
	{
		restoreColumns (owner.getProperty (Ids::panelModulatorListColumns));
	}
	else
	{
		resetToDefaults();
	}
	owner.addPanelListener (this);
    setSize (600, 400);
	refresh();
}

CtrlrPanelModulatorList::~CtrlrPanelModulatorList()
{
	owner.removePanelListener (this);
    deleteAndZero (modulatorList);
}

void CtrlrPanelModulatorList::paint (Graphics& g)
{
}

void CtrlrPanelModulatorList::resized()
{
    modulatorList->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
	modulatorListTree.setBounds (0, 0, getWidth() - 0, getHeight() - 0);
}

void CtrlrPanelModulatorList::resetToDefaults()
{
	modulatorList->getHeader().removeAllColumns();
	modulatorList->getHeader().addColumn ("name", getColumnIdForIdentifier("name")+1, 100);
	modulatorList->getHeader().addColumn ("modulatorValue", getColumnIdForIdentifier("modulatorValue")+1, 60);
	modulatorList->getHeader().addColumn ("vstIndex", getColumnIdForIdentifier("vstIndex")+1, 60);
	modulatorList->getHeader().addColumn ("uiType", getColumnIdForIdentifier("uiType")+1, 100);
	modulatorList->getHeader().addColumn ("componentRectangle", getColumnIdForIdentifier("componentRectangle")+1, 80);
	modulatorList->getHeader().addColumn ("componentGroupName", getColumnIdForIdentifier("componentGroupName")+1, 60);
	modulatorList->getHeader().addColumn ("componentTabName", getColumnIdForIdentifier("componentTabName")+1, 60);
	modulatorList->getHeader().addColumn ("componentRadioGroupId", getColumnIdForIdentifier("componentRadioGroupId")+1, 60);
	modulatorList->getHeader().addColumn ("midiMessageType", getColumnIdForIdentifier("midiMessageType")+1, 60);
	modulatorList->getHeader().addColumn ("midiMessageCtrlrNumber", getColumnIdForIdentifier("midiMessageCtrlrNumber")+1, 60);
	modulatorList->getHeader().addColumn ("midiMessageSysExFormula", getColumnIdForIdentifier("midiMessageSysExFormula")+1, 100);
	modulatorList->getHeader().addColumn ("modulatorCustomIndex", getColumnIdForIdentifier("modulatorCustomIndex")+1, 60);
	modulatorList->getHeader().addColumn ("modulatorCustomIndexGroup", getColumnIdForIdentifier("modulatorCustomIndexGroup")+1, 60);
}

void CtrlrPanelModulatorList::visibilityChanged()
{
}

void CtrlrPanelModulatorList::mouseDown (const MouseEvent& e)
{
	Label *label = dynamic_cast <Label*>(e.eventComponent);
	if (label)
	{
		const int rowNumber		= label->getProperties().getWithDefault ("rowNumber", -1);
		modulatorList->selectRowsBasedOnModifierKeys (rowNumber, e.mods, false);
	}
}

void CtrlrPanelModulatorList::mouseUp (const MouseEvent& e)
{
}

void CtrlrPanelModulatorList::copyModulatorList()
{
	copyOfModulatorList.clear();

	for (int i=0; i<owner.getNumModulators(); i++)
	{
		copyOfModulatorList.set (i, owner.getModulatorByIndex(i));
	}
}

void CtrlrPanelModulatorList::modulatorChanged (CtrlrModulator *modulatorThatChanged)
{
}

void CtrlrPanelModulatorList::modulatorAdded (CtrlrModulator *modulatorThatWasAdded)
{
	refresh();
}

void CtrlrPanelModulatorList::modulatorRemoved (CtrlrModulator *modulatorRemoved)
{
	refresh();
}

File CtrlrPanelModulatorList::getModListFile(const String &suffix)
{
	return (File::getSpecialLocation(File::tempDirectory).getChildFile(owner.getProperty(Ids::panelUID).toString() + ".modlist." + suffix));
}

const bool CtrlrPanelModulatorList::isComponentOffPanel(const int indexInModulatorCopy)
{
	CtrlrModulator *m = copyOfModulatorList[indexInModulatorCopy];

	if (m)
	{
		CtrlrComponent *c		= m->getComponent();
		CtrlrPanelEditor *ed	= owner.getEditor();
		if (c && ed)
		{
			if (ed->getCanvas()->getBounds().contains (c->getBounds()))
			{
				return (false);
			}
		}
	}
	return (true);
}

void CtrlrPanelModulatorList::refresh()
{
	copyModulatorList();
	modulatorList->updateContent();
}

const Identifier CtrlrPanelModulatorList::getColumnCtrlrId(const int columnId)
{
	return (owner.getOwner().getIDManager().getObjectTree().getChild(columnId).getProperty(Ids::name).toString());
}

const String CtrlrPanelModulatorList::getValueStringForColumn (CtrlrModulator *m, const Identifier columnName)
{
	if (m == nullptr)
		return (String::empty);

	if (m->getObjectTree().hasProperty (columnName))
	{
		return (m->getObjectTree().getProperty(columnName));
	}
	else if (m->getComponent() && m->getComponent()->getObjectTree().hasProperty(columnName))
	{
		return (m->getComponent()->getObjectTree().getProperty(columnName));
	}
	else if (m->getMidiMessagePtr() && m->getMidiMessage().getObjectTree().hasProperty(columnName))
	{
		return (m->getMidiMessage().getObjectTree().getProperty(columnName));
	}
	return (String::empty);
}

Value CtrlrPanelModulatorList::getValueForColumn (CtrlrModulator *m, const Identifier columnName)
{
	if (m->getObjectTree().hasProperty (columnName))
	{
		return (m->getObjectTree().getPropertyAsValue(columnName, 0));
	}
	else if (m->getComponent() && m->getComponent()->getObjectTree().hasProperty(columnName))
	{
		return (m->getComponent()->getObjectTree().getPropertyAsValue(columnName, 0));
	}
	else if (m->getMidiMessagePtr() && m->getMidiMessage().getObjectTree().hasProperty(columnName))
	{
		return (m->getMidiMessage().getObjectTree().getPropertyAsValue(columnName, 0));
	}

	return (Value());
}

const int CtrlrPanelModulatorList::getColumnIdForIdentifier (const String &columnName)
{
	ValueTree id = owner.getOwner().getIDManager().getObjectTree().getChildWithProperty (Ids::name, columnName);
	if (id.isValid())
	{
		return (owner.getOwner().getIDManager().getObjectTree().indexOf(id));
	}

	return (-1);
}

int CtrlrPanelModulatorList::getNumRows()
{
	return (copyOfModulatorList.size());
}

void CtrlrPanelModulatorList::paintRowBackground (Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
	if (rowIsSelected)
	{
		drawSelectionRectangle (g, width, height);
	}
}

Component* CtrlrPanelModulatorList::refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
	WeakReference<CtrlrModulator> m = copyOfModulatorList[rowNumber];

	if (m.wasObjectDeleted() || m == nullptr)
	{
		refresh();
		return (nullptr);
	}

	Label *label = (Label*)existingComponentToUpdate;

	if (label == 0)
	{
		label = new Label ();
		label->setFont (Font(12));
		label->setEditable (false, true, false);
		label->setJustificationType (Justification::centred);
		label->addMouseListener (this, false);
		label->setColour (TextEditor::highlightColourId, Colour (0xa211ee6b));
	}

	label->setColour (Label::textColourId, isRowSelected ? Colours::white : Colours::black);
	label->getTextValue().referTo(Value());
	label->setText (getValueStringForColumn (m, getColumnCtrlrId (columnId-1)), dontSendNotification);
	label->getProperties().set ("rowNumber", rowNumber);
	label->getTextValue().referTo(getValueForColumn(m,getColumnCtrlrId(columnId-1)));
	return (label);
}

void CtrlrPanelModulatorList::sortOrderChanged (int newSortColumnId, bool isForwards)
{
	sortColumnId	= newSortColumnId;
	isSortedForward	= isForwards;
	if (newSortColumnId != 0)
	{
		CtrlrModulatorListSorter sorter(owner, getColumnCtrlrId(newSortColumnId-1), isForwards);
		copyOfModulatorList.sort (sorter);
		modulatorList->updateContent();
	}

	owner.setProperty (Ids::panelModulatorListColumns, modulatorList->getHeader().toString());
}

void CtrlrPanelModulatorList::selectedRowsChanged (int lastRowSelected)
{
	SparseSet<int> selected = modulatorList->getSelectedRows();

	if (selected.size() <= 0)
		return;

	owner.getEditor()->getCanvas()->getSelection().deselectAll();

	for (int i=0; i<selected.size(); i++)
	{
		if (copyOfModulatorList[selected[i]].wasObjectDeleted())
		{
			continue;
		}
		else
		{
			CtrlrComponent *c = copyOfModulatorList[selected[i]]->getComponent();
			owner.getEditor()->getCanvas()->getSelection().addToSelection (c);
		}
	}
}

/** Sorter */
CtrlrModulatorListSorter::CtrlrModulatorListSorter(CtrlrPanel &_owner, const Identifier &attributeToSort_, bool forwards)
	: attributeToSort (attributeToSort_), direction (forwards ? 1 : -1), owner(_owner)
{
}

int CtrlrModulatorListSorter::compareElements (CtrlrModulator *first, CtrlrModulator *second) const
{
	int result = 0;

	if ((bool)owner.getProperty (Ids::panelModulatorListSortOption))
	{
		result = CtrlrPanelModulatorList::getValueStringForColumn (first, attributeToSort.toString()).compareNatural (CtrlrPanelModulatorList::getValueStringForColumn (second, attributeToSort.toString()));
	}
	else
	{

		const int f = CtrlrPanelModulatorList::getValueStringForColumn (first, attributeToSort.toString()).getIntValue();
		const int s = CtrlrPanelModulatorList::getValueStringForColumn (second, attributeToSort.toString()).getIntValue();

		if (f > s)
			result = 1;
		if (f < s)
			result = -1;
		if (f == s)
			result = 0;
	}

	return direction * result;
}

void CtrlrPanelModulatorList::makeVisibleItem()
{
	SparseSet<int> rows = modulatorList->getSelectedRows();

		for (int i=0; i<rows.size(); i++)
		{
			CtrlrModulator *m = copyOfModulatorList [rows[i]];

			if (m)
			{
				CtrlrComponent *c = m->getComponent();
				if (c)
				{
					c->setTopLeftPosition (0,0);

					if (c->getWidth() == 0)
						c->setSize (32, c->getHeight());

					if (c->getHeight() == 0)
						c->setSize (c->getWidth(), 32);
				}
			}
		}
}

ValueTree &CtrlrPanelModulatorList::getIdTree()
{
	return (owner.getOwner().getIDManager().getObjectTree());
}

/** Exporters */
void CtrlrPanelModulatorList::exportListItem(const int format)
{
	String result,head,body,foot;

	TableHeaderComponent &header = modulatorList->getHeader();
	if (format == 10)
	{
		head << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">";
		head << "\n<HTML>\n\t<HEAD>\n\t\t<TITLE>\n\t\t\tModulator list for " + owner.getProperty(Ids::name).toString();
		head << "\n\t\t</TITLE>\n\t</HEAD>\n\n<BODY>\n";

		head << "<table>\n\t<tr>";

		for (int modulator=0; modulator<copyOfModulatorList.size(); modulator++)
		{
			body << "\n\t<tr>";

			for (int index=0; index<header.getNumColumns(true); index++)
			{
				const int columnId = header.getColumnIdOfIndex (index, false);

				if (modulator == 0)
				{
					head << "\n\t\t<th>" << header.getColumnName (columnId) << "</th>";
				}

				body << "\n\t\t<td>" << getValueStringForColumn(copyOfModulatorList[modulator], header.getColumnName (columnId)) << "</td>";
			}

			body << "\n\t</tr>";
		}

		head << "\n\t</tr>";
		foot << "\n</table>\n\n</BODY>";

		result = head + body + foot;

		File f = getModListFile("html");
		f.replaceWithText (result);
		URL u("file://" + f.getFullPathName());
		u.launchInDefaultBrowser();
	}

	if (format == 11)
	{
		String result,head;

		for (int modulator=0; modulator<copyOfModulatorList.size(); modulator++)
		{
			for (int index=0; index<header.getNumColumns(false); index++)
			{
				const int columnId = header.getColumnIdOfIndex (index, false);

				if (modulator == 0)
				{
					head << header.getColumnName(columnId).quoted() + owner.getProperty(Ids::panelModulatorListCsvDelimiter).toString();
				}

				if (modulator == 1)
					head = head.substring (0, head.length()-1);

				result << getValueStringForColumn(copyOfModulatorList[modulator], header.getColumnName (columnId)).quoted();
				result << owner.getProperty(Ids::panelModulatorListCsvDelimiter).toString();
			}
			result << "\n";
		}

		File f = getModListFile("txt");
		f.replaceWithText (head + "\n" + result);
		f.startAsProcess();
	}

	if (format == 12)
	{
		XmlElement xml(owner.getProperty(Ids::panelModulatorListXmlRoot).toString());

		for (int modulator=0; modulator<copyOfModulatorList.size(); modulator++)
		{
			XmlElement *currentMod = new XmlElement (owner.getProperty(Ids::panelModulatorListXmlModulator).toString());

			for (int index=0; index<header.getNumColumns(false); index++)
			{
				const int columnId = header.getColumnIdOfIndex (index, false);
				currentMod->setAttribute (header.getColumnName(columnId), getValueStringForColumn(copyOfModulatorList[modulator], header.getColumnName (columnId)));
			}

			xml.addChildElement (currentMod);
		}

		File f = getModListFile("xml");
		f.replaceWithText (xml.createDocument(""));
		f.startAsProcess();
	}
}

void CtrlrPanelModulatorList::deleteSelected()
{
	if (owner.getEditor())
	{
		if (owner.getEditor()->getCanvas() && owner.getEditor()->getSelection())
		{
			owner.getEditor()->getSelection()->deselectAll();

			SparseSet<int> selected = modulatorList->getSelectedRows();

			for (int range=selected.getNumRanges()-1; range>=0; range--)
			{
				for (int modulator=selected.getRange(range).getEnd()-1; modulator>=selected.getRange(range).getStart(); modulator--)
				{
					if (!copyOfModulatorList[modulator].wasObjectDeleted() && copyOfModulatorList[modulator]->getComponent())
					{
						owner.getEditor()->getCanvas()->removeComponent(copyOfModulatorList[modulator]->getComponent(), false);
					}
				}
			}

			modulatorList->deselectAllRows();
			refresh();
		}
	}
}

void CtrlrPanelModulatorList::restoreColumns(const String &columnState)
{
	//<TABLELAYOUT sortedCol="0" sortForwards="1"><COLUMN id="2" visible="1" width="100"/><COLUMN id="7" visible="1" width="60"/><COLUMN id="1" visible="1" width="60"/><COLUMN id="3" visible="1" width="100"/><COLUMN id="97" visible="1" width="80"/><COLUMN id="101" visible="1" width="60"/><COLUMN id="102" visible="1" width="60"/><COLUMN id="107" visible="1" width="60"/><COLUMN id="401" visible="1" width="60"/><COLUMN id="398" visible="1" width="60"/><COLUMN id="402" visible="1" width="100"/><COLUMN id="21" visible="1" width="60"/><COLUMN id="22" visible="1" width="60"/><COLUMN id="8" visible="1" width="60"/></TABLELAYOUT>
	XmlDocument doc(columnState);
	ScopedPointer <XmlElement> xml(doc.getDocumentElement());
	if (xml)
	{
		if (xml->hasTagName ("TABLELAYOUT"))
		{
			const int sortedColumn = xml->getIntAttribute("sortedCol");
			const bool isForwards  = xml->getBoolAttribute("sortForwards");
			forEachXmlChildElement (*xml, child)
			{
				if (child->hasTagName ("COLUMN"))
				{
					const int columnId	= child->getIntAttribute("id");
					const int width		= child->getIntAttribute("width");

					modulatorList->getHeader().addColumn (getColumnCtrlrId (columnId-1).toString(), columnId, width);
				}

				modulatorList->getHeader().setSortColumnId (sortedColumn, isForwards);
			}
		}
	}
}

void CtrlrPanelModulatorList::switchView()
{
	if ((bool)owner.getProperty (Ids::uiPanelModulatorListViewTree) == false)
	{
		/* set to tree view */
		owner.setProperty (Ids::uiPanelModulatorListViewTree, true);
		modulatorList->setVisible (false);
		modulatorListTree.setVisible (true);
	}
	else
	{
		/* set to list view */
		owner.setProperty (Ids::uiPanelModulatorListViewTree, false);
		modulatorList->setVisible (true);
		modulatorListTree.setVisible (false);
	}
}

StringArray CtrlrPanelModulatorList::getMenuBarNames()
{
	const char* const names[] = { "File", "Edit", "View", nullptr };
	return StringArray (names);
}

PopupMenu CtrlrPanelModulatorList::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
	PopupMenu menu;
	if (topLevelMenuIndex == 0)
	{
		menu.addItem (1, "Close");
		menu.addSectionHeader ("Export list");
		menu.addItem (10, "Export as HTML");
		menu.addItem (11, "Export as CSV");
		menu.addItem (12, "Export as XML");
	}
	else if (topLevelMenuIndex == 1) /* Edit */
	{
		menu.addItem (2, "Delete selected");
		menu.addItem (7, "Make selected visible on canvas");
	}
	else if (topLevelMenuIndex == 2) /* View */
	{
		menu.addItem (4, "Refresh view");
		menu.addItem (5, "Sort using lexicographical algorithm", true, (bool)owner.getProperty (Ids::panelModulatorListSortOption));
		menu.addItem (6, "Sort using simple numeric comparison", true, !(bool)owner.getProperty (Ids::panelModulatorListSortOption));
		menu.addSeparator();
		menu.addItem (3, (bool)owner.getProperty (Ids::uiPanelModulatorListViewTree) ? "Switch to List" : "Switch to Tree", true);
		PopupMenu m;
		for (int i=0; i<getIdTree().getNumChildren(); i++)
		{
			m.addItem (8192+i, getIdTree().getChild(i).getProperty(Ids::name), true, modulatorList->getHeader().isColumnVisible(i+1));
		}
		menu.addSubMenu ("Visible columns", m);
		menu.addItem (13, "Reset columns to default");
	}
	return (menu);
}

void CtrlrPanelModulatorList::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	if (menuItemID == 2)
	{
		deleteSelected();
	}
	else if (menuItemID == 3)
	{
		switchView();
	}
	else if (menuItemID >= 8192)
	{
		handleColumnSelection(menuItemID);
	}
	else if (menuItemID == 4)
	{
		refresh();
	}
	else if (menuItemID == 5 || menuItemID == 6)
	{
		handleSortSelection (menuItemID);
	}
	else if (menuItemID == 7)
	{
		makeVisibleItem();
	}
	else if (menuItemID == 10 || menuItemID == 11 || menuItemID == 12)
	{
		exportListItem(menuItemID);
	}
	else if (menuItemID == 13)
	{
		resetToDefaults();
	}
}

void CtrlrPanelModulatorList::handleColumnSelection(const int itemId)
{
	if (modulatorList->getHeader().isColumnVisible ((itemId - 8192) + 1))
	{
		modulatorList->getHeader().removeColumn ((itemId - 8192) + 1);
	}
	else
	{
		modulatorList->getHeader().addColumn (getColumnCtrlrId(itemId - 8192).toString(), (itemId - 8192) + 1, 60);
	}

	owner.setProperty (Ids::panelModulatorListColumns, modulatorList->getHeader().toString());
}

void CtrlrPanelModulatorList::handleSortSelection(const int itemId)
{
	if (itemId == 5)
		owner.setProperty (Ids::panelModulatorListSortOption, true);
	if (itemId == 6)
		owner.setProperty (Ids::panelModulatorListSortOption, false);

	modulatorList->updateContent();
}
