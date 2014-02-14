#include "stdafx.h"
#include "CtrlrMIDILibraryEditor.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrMacros.h"

CtrlrMIDILibraryEditor::CtrlrMIDILibraryEditor (CtrlrPanel &_owner)
    : owner(_owner),
      spacerComponent(0),
	  libraryTree(0),
	  itemFont(12),
	  groupFont(13),
	  res(Result::fail("")),
	  clipboardTree("clipboard")
{
    addAndMakeVisible (spacerComponent			= new StretchableLayoutResizerBar (&layoutManager, 1, true));
	addAndMakeVisible (libraryTree				= new CtrlrValueTreeEditorTree ("Library Tree"));
	addAndMakeVisible (libraryItemProperties	= new PropertyPanel());

	layoutManager.setItemLayout (0, -0.001, -1.0, -0.29);
 	layoutManager.setItemLayout (1, -0.001, -0.01, -0.01);
 	layoutManager.setItemLayout (2, -0.001, -1.0, -0.69);

	libraryTree->setMultiSelectEnabled (true);
	libraryTree->setRootItem (new CtrlrValueTreeEditorItem (*this, getCore().getObjectTree(), Ids::name));

    setSize (500, 500);

	getCore().getObjectTree().addListener(this);

	if (getCore().getObjectTree().hasProperty(Ids::midiLibraryTreeState))
	{
		ScopedPointer <XmlElement> xml(XmlDocument::parse(getCore().getProperty(Ids::midiLibraryTreeState)));
		if (xml)
		{
			libraryTree->restoreOpennessState (*xml, true);
		}
	}
}

CtrlrMIDILibraryEditor::~CtrlrMIDILibraryEditor()
{
	getCore().getObjectTree().removeListener(this);

	libraryTree->deleteRootItem();
	deleteAndZero (libraryTree);
	deleteAndZero (libraryItemProperties);
    deleteAndZero (spacerComponent);
}

void CtrlrMIDILibraryEditor::paint (Graphics& g)
{
}

CtrlrMIDILibrary &CtrlrMIDILibraryEditor::getCore()
{
	return (owner.getCtrlrMIDILibrary());
}

void CtrlrMIDILibraryEditor::resized()
{
	Component* comps[] = { libraryTree, spacerComponent, libraryItemProperties  };
 	layoutManager.layOutComponents (comps, 3, 0, 0, getWidth(), getHeight(), false, true);
}

void CtrlrMIDILibraryEditor::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
}

void CtrlrMIDILibraryEditor::valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded)
{
	triggerAsyncUpdate();
}

void CtrlrMIDILibraryEditor::valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved)
{
	triggerAsyncUpdate();
}

void CtrlrMIDILibraryEditor::refresh()
{
	if (libraryTree->getRootItem())
	{
		ScopedPointer <XmlElement> state (libraryTree->getOpennessState(true));
		libraryTree->deleteRootItem();
		libraryTree->setRootItem (new CtrlrValueTreeEditorItem(*this, getCore().getObjectTree(), Ids::name));

		if (state)
		{
			libraryTree->restoreOpennessState (*state, false);
		}
	}
}

void CtrlrMIDILibraryEditor::handleAsyncUpdate()
{
	refresh();
}

const String CtrlrMIDILibraryEditor::getUniqueName(const ValueTree &item)	const
{
	if (item.getProperty(Ids::name).toString().isEmpty())
		return (item.getType().toString());
	else
		return (item.getProperty(Ids::name));
}

const AttributedString CtrlrMIDILibraryEditor::getDisplayString(const ValueTree &item) const
{
	AttributedString as;

	if (item.hasType(Ids::midiLibrary))
	{
		as.append ("MIDI Library", groupFont.boldened(), Colours::black);
	}
	else if (item.hasType (Ids::midiLibraryBank))
	{
		as.append (item.getProperty(Ids::name).toString(), groupFont, Colours::black);
	}
	else if (item.hasType (Ids::midiLibraryTransactions))
	{
		as.append (item.getProperty(Ids::name).toString(), groupFont, Colours::black);
	}
	else if (item.hasType (Ids::trans))
	{
		as.append (item.getProperty(Ids::name).toString(), groupFont, Colours::black);
	}
	else if (item.hasType (Ids::midiLibraryProgram))
	{
		as.append (item.getProperty(Ids::name).toString(), itemFont, Colours::black);
	}
	else if (item.hasType (Ids::panelState))
	{
		as.append ("Panel State", itemFont, Colours::darkgrey);
	}
	else if (item.hasType (Ids::midiLibraryData))
	{
		as.append (item.getProperty(Ids::name).toString(), itemFont, Colours::black);
	}
	else if (item.hasType (Ids::midiLibraryEditBuffer))
	{
		as.append ("Edit buffer", itemFont, Colours::darkgreen);
	}
	else if (item.hasType (Ids::midiLibrarySnapshots))
	{
		as.append ("Snapshots", groupFont, Colours::darkblue);
	}
	else if (item.hasType (Ids::midiLibraryFirmware))
	{
		as.append ("Firmware", groupFont, Colours::darkblue);
	}
	else
	{
		as.append (item.getProperty(Ids::name).toString(), itemFont, Colours::black.withAlpha(0.5f));
	}
	return (as);
}

const Font CtrlrMIDILibraryEditor::getItemFont(const ValueTree &item)	const
{
	if (item.hasType(Ids::midiLibrary))
	{
		return (groupFont.boldened());
	}
	else if (item.hasType(Ids::midiLibraryBank)
		|| item.hasType(Ids::midiLibrarySnapshots) )
	{
		return (groupFont);
	}
	else if (item.hasType(Ids::midiLibraryProgram))
	{
		return (itemFont);
	}

	return (itemFont);
}

const int CtrlrMIDILibraryEditor::getItemHeight(const ValueTree &item)const
{
	return (24);
}

bool CtrlrMIDILibraryEditor::canBeSelected(const ValueTree &item)	const
{
	return (true);
}

const bool CtrlrMIDILibraryEditor::isInterestedInDragSource(const ValueTree &item, const DragAndDropTarget::SourceDetails &dragSourceDetails) const
{
	return (true);
}

void CtrlrMIDILibraryEditor::itemDropped (ValueTree &targetItem, const DragAndDropTarget::SourceDetails &dragSourceDetails, int insertIndex)
{
	if (targetItem.hasType(Ids::midiLibraryBank) && insertIndex == 0 )
	{
		StringArray ar;
		ar.addTokens (dragSourceDetails.description.toString(), ";", "\"'");

		for (int i=0; i<ar.size(); i++)
		{
			CtrlrValueTreeEditorItem *sourceItem = dynamic_cast<CtrlrValueTreeEditorItem*>(libraryTree->findItemFromIdentifierString (ar[i]));
			if (sourceItem != nullptr)
			{
				ValueTree child		= sourceItem->getTree();
				ValueTree parent	= child.getParent();
				parent.removeChild (child, nullptr);
				targetItem.addChild (child, -1, nullptr);
			}
		}

		triggerAsyncUpdate();
	}
}

void CtrlrMIDILibraryEditor::itemClicked(const MouseEvent &e, ValueTree &item)
{
	if (!e.mods.isPopupMenu())
	{
		itemSelectionChanged (item);
		return;
	}

    PopupMenu m;
	if (getCore().isContainer(item))
    {
        getContainerMenu (m,item);
    }
    if (getCore().isItem(item))
    {
        getItemMenu (m,item);
    }

    /* Always get the utilities */
	getUtilityMenu (m, item);

	getCore().getTransactionMenu (m, item);

	handleItemMenu (item, m.show());
}

void CtrlrMIDILibraryEditor::itemDoubleClicked(const MouseEvent &e, ValueTree &item)
{
	if (item.hasType (Ids::midiLibraryProgram))
	{
		getCore().setProgram (item);
	}
}

void CtrlrMIDILibraryEditor::handleItemMenu(ValueTree &item, const int itemId)
{
	if (itemId >= MENU_TRANSACTIONS_START)
	{
		getCore().handleTransactionMenu (item, itemId);
		return;
	}

	switch (itemId)
	{
	    case ActCopy:
            copy();
            break;
        case ActCut:
            cut();
            break;
		case ActDelete:
			cut(false);
			break;
        case ActPaste:
            paste();
            break;
        case ActDuplicate:
            duplicate();
            break;
		case ActAddData:
			dialogAddCustomData(item);
			break;
		case ActAddProgram:
			dialogAddProgram(item);
			break;
		case ActAddProgramNum:
			dialogAddProgramNum(item);
			break;
		case ActAddBank:
			dialogAddBank(item);
			break;
		case ActAddTransaction:
			dialogAddTransaction(item);
			break;
	}
}

void CtrlrMIDILibraryEditor::getUtilityMenu(PopupMenu &m, const ValueTree &item)
{
	m.addSectionHeader("Utilities");
	m.addItem (ActCopy, "Copy", !item.hasType(Ids::midiLibrary) && !item.hasType(Ids::midiLibrarySnapshots));
	m.addItem (ActCut, "Cut", !item.hasType(Ids::midiLibrary) && !item.hasType(Ids::midiLibrarySnapshots) && !CtrlrMIDILibrary::isFirmware(item) && !CtrlrMIDILibrary::isEditBuffer(item));
	m.addItem (ActDelete, "Delete", !item.hasType(Ids::midiLibrary) && !item.hasType(Ids::midiLibrarySnapshots) && !CtrlrMIDILibrary::isFirmware(item) && !CtrlrMIDILibrary::isEditBuffer(item));
	m.addItem (ActPaste, "Paste");
	m.addItem (ActDuplicate, "Duplicate", !item.hasType(Ids::midiLibrary) && !item.hasType(Ids::midiLibrarySnapshots) && !CtrlrMIDILibrary::isFirmware(item) && !CtrlrMIDILibrary::isEditBuffer(item));
	m.addItem (ActExport, "Export to file");
}

void CtrlrMIDILibraryEditor::getItemMenu(PopupMenu &m, const ValueTree &item)
{
}

void CtrlrMIDILibraryEditor::getContainerMenu(PopupMenu &m, const ValueTree &item)
{
    m.addSectionHeader("Container options");

    if (getCore().getRoot() == item)
		m.addItem (ActAddBank, "Add Bank");

	if (getCore().getTransactions() == item)
		m.addItem (ActAddTransaction, "Add transaction");

    m.addItem (ActAddProgram, "Add Program");
	m.addItem (ActAddProgramNum, "Add multiple programs");

	getItemMenu (m, item);

    m.addSeparator();
    m.addItem (ActAddData, "Add Custom Data");
}

Image CtrlrMIDILibraryEditor::getIconForItem(const ValueTree &item) const
{
	if (item.hasType (Ids::midiLibrary))
	{
		return (IMAGE(ico_box_png));
	}
	else if (item.hasType(Ids::midiLibraryProgram))
	{
		return (IMAGE(ico_document_png));
	}
	else if (item.hasType (Ids::midiLibraryData))
	{
		return (IMAGE(ico_unit_png));
	}
	else if (item.hasType (Ids::midiLibraryBank))
	{
		return (IMAGE(ico_folder_png));
	}
	else if (item.hasType(Ids::midiLibrarySnapshots))
	{
		return (IMAGE(ico_folder_alt_png));
	}
	else if (item.hasType (Ids::midiLibraryEditBuffer))
	{
		return (IMAGE(ico_unit_alt_png));
	}
	else if (item.hasType (Ids::midiLibraryFirmware))
	{
		return (IMAGE(ico_firmware_png));
	}
	else if (item.hasType (Ids::midiLibraryTransactions))
	{
		return (IMAGE(ico_transaction_png));
	}
	return (IMAGE(ico_unknown_png));
}

void CtrlrMIDILibraryEditor::itemSelectionChanged(ValueTree &item)
{
	libraryItemProperties->clear();

	Array <PropertyComponent*> library, transRequest, transResponse,transConfirmation, transGeneral;

	for (int i=0; i<item.getNumProperties(); i++)
	{
		const String propertyName = item.getPropertyName(i).toString();

		if (propertyName.startsWith ("midiLibrary"))
		{
			library.add (owner.getOwner().getIDManager().createComponentForProperty(	item.getPropertyName(i), item, &owner, nullptr, nullptr));
		}
		else if (propertyName.startsWith("trans") || propertyName.startsWith("luaTrans"))
		{
			if (propertyName.startsWith ("transResp"))
			{
				transResponse.add (owner.getOwner().getIDManager().createComponentForProperty(	item.getPropertyName(i), item, &owner, nullptr, nullptr));
			}
			else if (propertyName.startsWith("transReq"))
			{
				transRequest.add (owner.getOwner().getIDManager().createComponentForProperty(	item.getPropertyName(i), item, &owner, nullptr, nullptr));
			}
			else if (propertyName.startsWith("transConf"))
			{
				transConfirmation.add (owner.getOwner().getIDManager().createComponentForProperty(	item.getPropertyName(i), item, &owner, nullptr, nullptr));
			}
			else
			{
				transGeneral.add (owner.getOwner().getIDManager().createComponentForProperty(	item.getPropertyName(i), item, &owner, nullptr, nullptr));
			}
		}
		else
		{
			transGeneral.add (owner.getOwner().getIDManager().createComponentForProperty(	item.getPropertyName(i), item, &owner, nullptr, nullptr));
		}
	}

	if (library.size() > 0)
		libraryItemProperties->addSection ("Library", library);

	if (transRequest.size() > 0)
		libraryItemProperties->addSection ("Request", transRequest);

	if (transResponse.size() > 0)
		libraryItemProperties->addSection ("Response", transResponse);

	if (transConfirmation.size() > 0)
		libraryItemProperties->addSection ("Confirmation", transConfirmation);

	if (transGeneral.size() > 0)
		libraryItemProperties->addSection ("General", transGeneral);
}

void CtrlrMIDILibraryEditor::itemOpennessChanged(const bool isNowOpen)
{
	ScopedPointer <XmlElement> state (libraryTree->getOpennessState(true));

	if (state)
	{
		getCore().setProperty (Ids::midiLibraryTreeState, state->createDocument(String::empty), false);
	}
}

void CtrlrMIDILibraryEditor::cut(const bool copyToClipboard)
{
	const int numSelected = libraryTree->getNumSelectedItems();

	for (int i=0; i<numSelected; i++)
	{
		CtrlrValueTreeEditorItem *it = dynamic_cast<CtrlrValueTreeEditorItem*>(libraryTree->getSelectedItem (i));

		if (it != nullptr)
		{
			clipboardTree.removeAllChildren(nullptr);

			ValueTree child  = it->getTree();

			if (getCore().isFirmware(child) || getCore().isEditBuffer(child))
				continue;

			ValueTree parent = it->getTree().getParent();

			if (parent.isValid() && child.isValid())
			{
				if (copyToClipboard)
					clipboardTree.addChild (child.createCopy(), -1, nullptr);

				if (!child.hasType(Ids::midiLibrarySnapshots) && !child.hasType(Ids::midiLibrary))
				{
					parent.removeChild (child, nullptr);
				}
			}
		}
	}

	if (copyToClipboard)
	{
		ScopedPointer <XmlElement> xml (clipboardTree.createXml());
		if (xml)
		{
			SystemClipboard::copyTextToClipboard (xml->createDocument(String::empty));
		}
	}
}

void CtrlrMIDILibraryEditor::copy()
{
    const int numSelected = libraryTree->getNumSelectedItems();

	for (int i=0; i<numSelected; i++)
	{
		CtrlrValueTreeEditorItem *it = dynamic_cast<CtrlrValueTreeEditorItem*>(libraryTree->getSelectedItem (i));

		if (it != nullptr)
		{
			clipboardTree.removeAllChildren(nullptr);

			ValueTree child  = it->getTree();
			ValueTree parent = it->getTree().getParent();

			if (parent.isValid() && child.isValid())
			{
				clipboardTree.addChild (child.createCopy(), -1, nullptr);
			}
		}
	}

	ScopedPointer <XmlElement> xml (clipboardTree.createXml());
	if (xml)
	{
		SystemClipboard::copyTextToClipboard (xml->createDocument(String::empty));
	}
}

void CtrlrMIDILibraryEditor::paste()
{
	ScopedPointer <XmlElement> xml(XmlDocument::parse (SystemClipboard::getTextFromClipboard()));
    if (xml)
    {
    	CtrlrValueTreeEditorItem *it = dynamic_cast<CtrlrValueTreeEditorItem*>(libraryTree->getSelectedItem (0));
		ValueTree itemToAttachTo;

    	if (it != nullptr)
		{
			itemToAttachTo = it->getTree();
		}

        ValueTree item = ValueTree::fromXml(*xml);

		for (int i=0; i<item.getNumChildren(); i++)
		{
			if (isValidLibraryItem(item.getChild(i)) && itemToAttachTo.isValid())
			{
				itemToAttachTo.addChild (item.getChild(i).createCopy(), -1, nullptr);
			}
		}
    }
}

void CtrlrMIDILibraryEditor::duplicate()
{
	const int numSelected = libraryTree->getNumSelectedItems();

	for (int i=0; i<numSelected; i++)
	{
		CtrlrValueTreeEditorItem *it = dynamic_cast<CtrlrValueTreeEditorItem*>(libraryTree->getSelectedItem (i));

		if (it != nullptr)
		{
			ValueTree itemToDuplicate = it->getTree();

			if (itemToDuplicate.isValid())
			{
				ValueTree parent = itemToDuplicate.getParent();

				if (parent.isValid())
				{
					parent.addChild (itemToDuplicate.createCopy(), -1, nullptr);
				}
			}
		}
	}

	/*ValueTree itemCopy = sourceItem.createCopy();
	itemCopy.setProperty (Ids::name, itemCopy.getProperty(Ids::name).toString()+"_dup", nullptr);
	sourceItem.getParent().addChild (itemCopy, -1, nullptr);
	*/
}

bool CtrlrMIDILibraryEditor::isValidLibraryItem(const ValueTree &itemToCheck)
{
    if (itemToCheck.hasType (Ids::midiLibraryBank)
        || itemToCheck.hasType (Ids::midiLibraryData)
        || itemToCheck.hasType (Ids::midiLibraryProgram))
    {
           return (true);
    }
    else
    {
        return (false);
    }
}

void CtrlrMIDILibraryEditor::dialogAddProgram(ValueTree unitToAddTo)
{
	AlertWindow w("Add new program", "Set new program name and description", AlertWindow::QuestionIcon);
	w.addTextEditor ("name", "New program", "Program Name", false);
    w.addTextEditor ("number", "0", "Program number", false);
	w.addButton ("OK", 1, KeyPress(KeyPress::returnKey));
	w.addButton ("Cancel", 0, KeyPress(KeyPress::escapeKey));

	if (w.runModalLoop() == 1)
	{
		getCore().addNewProgram ( w.getTextEditorContents("name"),
                        w.getTextEditorContents("number").getIntValue(),
                        unitToAddTo
                    );
	}
}

void CtrlrMIDILibraryEditor::dialogAddProgramNum(ValueTree unitToAddTo)
{
	const char *ch[]= { "No", "Yes", 0 };
	AlertWindow w("Add multiple new programs", "Set new program name and description. Number generated will be appended as a suffix", AlertWindow::QuestionIcon);
	w.addTextEditor ("name", "New program", "Program Name", false);
    w.addTextEditor ("number", "0", "Program number to start with", false);
	w.addTextEditor ("count",  "1", "How many programs", false);
	w.addComboBox ("incMidiNum", StringArray(ch), "Increment MIDI program number");

	w.addButton ("OK", 1, KeyPress(KeyPress::returnKey));
	w.addButton ("Cancel", 0, KeyPress(KeyPress::escapeKey));

	if (w.runModalLoop() == 1)
	{
		const int count		= w.getTextEditorContents ("count").getIntValue();
		const String name	= w.getTextEditorContents ("name");
		const int number	= w.getTextEditorContents ("number").getIntValue();
		const bool inc 		= w.getComboBoxComponent("incMidiNum")->getSelectedItemIndex() ? true : false;

		if (count >= 1)
		{
			for (int i=0; i<count; i++)
			{
				getCore().addNewProgram (name+"_"+STR(i), inc ? (number+i) : 0,unitToAddTo);
			}
		}
	}
}

void CtrlrMIDILibraryEditor::dialogAddBank(ValueTree unitToAddTo)
{
	AlertWindow w("Add new bank", "Set new bank name and description", AlertWindow::QuestionIcon);
	w.addTextEditor ("name", "New bank", "Bank name", false);
	w.addTextEditor ("description", "This is my bank", "Bank description", false);
	w.addTextEditor ("number", "0", "Bank number", false);
	w.addTextEditor ("lsb", "0", "LSB for bank change messages", false);
	w.addTextEditor ("msb", "0", "MSB for bank change messages", false);

	w.addButton ("OK", 1, KeyPress(KeyPress::returnKey));
	w.addButton ("Cancel", 0, KeyPress(KeyPress::escapeKey));

	if (w.runModalLoop() == 1)
	{
		getCore().addNewBank (w.getTextEditorContents("name"),
                    w.getTextEditorContents("description"),
                    w.getTextEditorContents("number").getIntValue(),
                    w.getTextEditorContents("lsb").getIntValue(),
                    w.getTextEditorContents("msb").getIntValue(),
					unitToAddTo
                );
	}
}

void CtrlrMIDILibraryEditor::dialogAddCustomData(ValueTree unitToAddTo)
{
	AlertWindow w("Add new custom data", "Set description", AlertWindow::QuestionIcon);
	w.addTextEditor ("name", "New custom data", "Custom data name", false);
    w.addTextEditor ("number", "0", "Data number", false);

	w.addButton ("OK", 1, KeyPress(KeyPress::returnKey));
	w.addButton ("Cancel", 0, KeyPress(KeyPress::escapeKey));

	if (w.runModalLoop() == 1)
	{
        getCore().addNewCustomData (  w.getTextEditorContents("name"),
                            w.getTextEditorContents("number").getIntValue(),
                            unitToAddTo
                        );
	}
}

void CtrlrMIDILibraryEditor::dialogAddTransaction(ValueTree unitToAddTo)
{
	AlertWindow w("Add new transaction", "Set description", AlertWindow::QuestionIcon);
	w.addTextEditor ("name", "Transaction", "Name", false);

	w.addButton ("OK", 1, KeyPress(KeyPress::returnKey));
	w.addButton ("Cancel", 0, KeyPress(KeyPress::escapeKey));

	if (w.runModalLoop() == 1)
	{
        getCore().addNewTransaction (w.getTextEditorContents("name"),unitToAddTo);
	}
}

void CtrlrMIDILibraryEditor::visibilityChanged()
{
	if (isVisible())
	{
		refresh();
	}
}

void CtrlrMIDILibraryEditor::importFromFile(const File &fileToImport)
{
}

StringArray CtrlrMIDILibraryEditor::getMenuBarNames()
{
	const char* const names[] = { "File", "View", nullptr };
	return StringArray (names);
}

PopupMenu CtrlrMIDILibraryEditor::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
	PopupMenu m;

	if (topLevelMenuIndex == 0)
	{
		m.addSectionHeader ("Import");
		m.addItem (2, "Import from file");

		m.addSectionHeader ("Export");
		m.addItem (3, "Export to file (xml)");
		m.addItem (4, "Export to file (syx)");

		m.addSeparator ();
		m.addItem (5, "Factory reset");
		m.addItem (1, "Close");
	}

	if (topLevelMenuIndex == 1)
	{
		m.addItem (1, "Refresh");
	}
	return (m);
}

void CtrlrMIDILibraryEditor::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	if (topLevelMenuIndex == 1)
	{
		if (menuItemID == 1)
			refresh();
	}

	if (topLevelMenuIndex == 0)
	{
		if (menuItemID == 2)
		{
			FileChooser dialog("Import MIDI data", File (owner.getProperty(Ids::lastBrowsedComponentDir).toString()), "*.syx;*.dat;*.mid;*.*", true);
			if (dialog.browseForFileToOpen(0))
			{
				owner.setProperty(Ids::lastBrowsedComponentDir, dialog.getResult().getFullPathName());
				if (libraryTree->getSelectedItem(0))
				{
					CtrlrValueTreeEditorItem *item = dynamic_cast<CtrlrValueTreeEditorItem*>(libraryTree->getSelectedItem(0));

					if (item)
					{
						getCore().importFromFile (dialog.getResult(), item->getTree());
					}
				}

				getCore().importFromFile(dialog.getResult());
			}
		}
		if (menuItemID == 5)
		{
			getCore().factoryReset();
			refresh();
		}
	}
}

bool CtrlrMIDILibraryEditor::keyPressed (const KeyPress &key, Component *originatingComponent)
{
	// _DBG("CtrlrMIDILibraryEditor::keyPressed "+key.getTextDescription()+" keyCode=["+STR(key.getKeyCode())+"]");
	if (key.getModifiers().isCommandDown())
	{
		switch (key.getKeyCode())
		{
			case 88:
				cut();
				break;
			case 67:
				copy();
				break;
			case 86:
				paste();
				break;
			case 68:
				duplicate();
				break;
			default:
				break;
		}
	}

	if (key.isKeyCode(KeyPress::deleteKey))
	{
        cut(false);
	}

	return (false);
}
