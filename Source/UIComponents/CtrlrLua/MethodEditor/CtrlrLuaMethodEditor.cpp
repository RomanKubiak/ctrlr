#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrLog.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrLuaManager.h"
#include "CtrlrWindowManagers/CtrlrManagerWindowManager.h"
#include "CtrlrLuaMethodEditor.h"
#include "CtrlrLuaMethodFind.h"
#include "CtrlrLuaMethodEditorTabs.h"
#include "CtrlrLuaMethodCodeEditor.h"
#include "CtrlrPropertyEditors/CtrlrFontPropertyComponent.h"
#include "CtrlrPropertyEditors/CtrlrColourPropertyComponent.h"
#include "CtrlrLuaMethodCodeEditorSettings.h"
#include "CtrlrWindowManagers/CtrlrDialogWindow.h"

CtrlrLuaMethodEditor::CtrlrLuaMethodEditor (CtrlrPanel &_owner)
    : owner(_owner),
      methodEditArea (nullptr),
	  methodTree(nullptr),
	  resizer(nullptr)
{
	addAndMakeVisible (resizer			= new StretchableLayoutResizerBar (&layoutManager, 1, true));
	addAndMakeVisible (methodTree		= new CtrlrValueTreeEditorTree ("LUA METHOD TREE"));
    addAndMakeVisible (methodEditArea	= new CtrlrLuaMethodEditArea(*this));

	methodTree->setRootItem (new CtrlrValueTreeEditorItem(*this, getMethodManager().getManagerTree(), Ids::luaMethodName));
	getMethodManager().setMethodEditor (this);
	methodTree->setMultiSelectEnabled (true);

	layoutManager.setItemLayout (0, -0.001, -1.0, -0.29);
 	layoutManager.setItemLayout (1, 8, 8, 8);
 	layoutManager.setItemLayout (2, -0.001, -1.0, -0.69);

	addKeyListener (this);
	getMethodManager().setMethodEditor (this);
	componentTree.addListener (this);
    setSize (700, 600);
}

CtrlrLuaMethodEditor::~CtrlrLuaMethodEditor()
{
	componentTree.removeListener (this);
	masterReference.clear();
	methodTree->deleteRootItem();
	deleteAndZero (methodTree);
	deleteAndZero (resizer);
    deleteAndZero (methodEditArea);
}

void CtrlrLuaMethodEditor::paint (Graphics& g)
{
}

TabbedComponent *CtrlrLuaMethodEditor::getTabs()
{
	if (methodEditArea)
	{
		return (methodEditArea->getTabs());
	}

	return (nullptr);
}

void CtrlrLuaMethodEditor::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::luaMethodEditorFont || property == Ids::luaMethodEditorBgColour)
	{
		for (int i=0; i<methodEditArea->getTabs()->getNumTabs(); i++)
		{
			CtrlrLuaMethodCodeEditor *ed = dynamic_cast<CtrlrLuaMethodCodeEditor*>(methodEditArea->getTabs()->getTabContentComponent(i));
			if (ed != nullptr)
			{
				ed->setFontAndColour (owner.getOwner().getFontManager().getFontFromString (componentTree.getProperty(Ids::luaMethodEditorFont)), VAR2COLOUR(componentTree.getProperty(Ids::luaMethodEditorBgColour)));
			}
		}
	}
}

void CtrlrLuaMethodEditor::restoreState(const ValueTree &savedState)
{
	restoreProperties (savedState, componentTree, nullptr);

	ScopedPointer <XmlElement> treeState(XmlDocument::parse (savedState.getProperty(Ids::luaMethodEditor).toString().upToLastOccurrenceOf(";", false, true)));

	if (treeState)
	{
		methodTree->restoreOpennessState (*treeState, true);
	}

	StringArray openedMethods;
	openedMethods.addTokens (savedState.getProperty(Ids::luaMethodEditor).toString().fromLastOccurrenceOf(";", false, true), ":", String::empty);

	for (int i=0; i<openedMethods.size(); i++)
	{
		setEditedMethod (Uuid (openedMethods[i]));
	}

	updateTabs();
}

void CtrlrLuaMethodEditor::updateRootItem()
{
	if (methodTree->getRootItem())
	{
		ScopedPointer <XmlElement> state (methodTree->getOpennessState(true));
		methodTree->deleteRootItem();
		methodTree->setRootItem (new CtrlrValueTreeEditorItem(*this, owner.getCtrlrLuaManager().getMethodManager().getManagerTree(), Ids::luaMethodName));
		if (state)
		{
			methodTree->restoreOpennessState (*state, false);
		}
	}
}

void CtrlrLuaMethodEditor::resized()
{
	Component* comps[] = { methodTree, resizer, methodEditArea  };
	layoutManager.layOutComponents (comps, 3, 0, 0, getWidth(), getHeight(), false, true);
}

bool CtrlrLuaMethodEditor::keyPressed (const KeyPress& key, Component* originatingComponent)
{
	if (key.getModifiers().isCommandDown())
	{
		if (key.getKeyCode() == 70)
		{
			// CTRL + F
			methodEditArea->showFindDialog();
		}

		if (key.getKeyCode() == 72)
		{
			methodEditArea->replaceNextMatch();
		}
	}

	if (key.getKeyCode() == 65650) // F3
	{
		methodEditArea->findNextMatch();
	}
    return false;
}

CtrlrLuaMethod *CtrlrLuaMethodEditor::setEditedMethod (const String &methodName)
{
	CtrlrLuaMethod *method = getMethodManager().getMethodByName(methodName);
	if (method != nullptr)
	{
		return (setEditedMethod (method->getUuid()));
	}

	return (nullptr);
}

CtrlrLuaMethod *CtrlrLuaMethodEditor::setEditedMethod (const Uuid &methodUuid)
{
	CtrlrLuaMethod *method = getMethodManager().getMethodByUuid(methodUuid);

	if (method != nullptr)
	{
		if (method->getCodeEditor() == nullptr)
		{
			/* the method is not yest beeing edited */
			createNewTab (method);
		}
		else
		{
			/* it looks like the method is edited, switch to the tab that has it */
			setCurrentTab (method);
		}

		return (method);
	}

	return (nullptr); // A method has been selected that's invalid
}

void CtrlrLuaMethodEditor::addNewMethod(ValueTree parentGroup)
{
	AlertWindow wnd(METHOD_NEW, String::empty, AlertWindow::InfoIcon, this);
	wnd.addTextEditor ("methodName", "myNewMethod", "Method name", false);
	wnd.addComboBox ("templateList", getMethodManager().getTemplateList(), "Initialize from template");

	wnd.addButton ("OK", 1, KeyPress(KeyPress::returnKey));
	wnd.addButton ("Cancel", 0, KeyPress(KeyPress::escapeKey));
	if (wnd.runModalLoop())
	{
		const String methodName = wnd.getTextEditorContents("methodName");

		if (getMethodManager().isValidMethodName(methodName))
		{
			const String initialCode = getMethodManager().getDefaultMethodCode(methodName, wnd.getComboBoxComponent("templateList")->getText());

			getMethodManager().addMethod (parentGroup, wnd.getTextEditorContents("methodName"), initialCode, String::empty);
		}
		else
		{
			WARN("Invalid method name, please correct");
		}
	}

	updateRootItem();

	saveSettings(); // save settings
}

void CtrlrLuaMethodEditor::addMethodFromFile(ValueTree parentGroup)
{
	FileChooser fc ("Select LUA files", lastBrowsedSourceDir, "*.lua;*.txt");
	if (fc.browseForMultipleFilesToOpen ())
	{
		Array <File> results = fc.getResults();

		for (int i=0; i<results.size(); i++)
		{
			getMethodManager().addMethodFromFile (parentGroup, results[i]);
		}
	}

	updateRootItem();

	saveSettings(); // save settings
}

void CtrlrLuaMethodEditor::addNewGroup(ValueTree parentGroup)
{
	AlertWindow wnd(GROUP_NEW, String::empty, AlertWindow::InfoIcon, this);
	wnd.addTextEditor ("groupName", "New Group", "Group name", false);
	wnd.addButton ("OK", 1, KeyPress(KeyPress::returnKey));
	wnd.addButton ("Cancel", 0, KeyPress(KeyPress::escapeKey));
	if (wnd.runModalLoop())
	{
		if (parentGroup.hasType (Ids::luaMethodGroup))
		{
			getMethodManager().addGroup (wnd.getTextEditorContents("groupName"), parentGroup.getProperty(Ids::uuid).toString());
		}
		else
		{
			getMethodManager().addGroup (wnd.getTextEditorContents("groupName"));
		}
	}

	updateRootItem();

	saveSettings(); // save settings
}

void CtrlrLuaMethodEditor::removeGroup(ValueTree parentGroup)
{
	if (parentGroup.getNumChildren() > 0)
	{
		if (SURE("Remove group: "+parentGroup.getProperty(Ids::name).toString()+" ?", this))
		{
			getMethodManager().removeGroup(parentGroup);
		}
	}
	else
	{
		getMethodManager().removeGroup(parentGroup);
	}

	updateRootItem();

	saveSettings(); // save settings
}

void CtrlrLuaMethodEditor::renameGroup(ValueTree parentGroup)
{
	AlertWindow w ("Rename group", "", AlertWindow::QuestionIcon, this);
	w.addTextEditor("name", parentGroup.getProperty (Ids::name).toString());
	w.addButton ("OK", 1, KeyPress(KeyPress::returnKey));
	w.addButton ("Cancel", 0, KeyPress(KeyPress::escapeKey));

	if (w.runModalLoop())
	{
		parentGroup.setProperty (Ids::name, w.getTextEditorContents("name"), nullptr);
		updateRootItem();
	}

	saveSettings(); // save settings
}

CtrlrLuaMethodCodeEditor *CtrlrLuaMethodEditor::getCurrentEditor()
{
	return (dynamic_cast<CtrlrLuaMethodCodeEditor*>(methodEditArea->getTabs()->getCurrentContentComponent()));
}

void CtrlrLuaMethodEditor::setPositionLabelText (const String &text)
{
}

CtrlrPanel &CtrlrLuaMethodEditor::getOwner()
{
	return (owner);
}

CtrlrLuaMethodManager &CtrlrLuaMethodEditor::getMethodManager()
{
	return (owner.getCtrlrLuaManager().getMethodManager());
}

void CtrlrLuaMethodEditor::itemChanged (ValueTree &itemTreeThatChanged)
{
}

void CtrlrLuaMethodEditor::closeTab(const int tabIndex)
{
	CtrlrLuaMethodCodeEditor *ed = dynamic_cast<CtrlrLuaMethodCodeEditor*>(methodEditArea->getTabs()->getTabContentComponent(tabIndex));
	if (ed)
	{
		if (ed->getCodeDocument().hasChangedSinceSavePoint())
		{
			if (SURE("There might be some unsaved changes, are you sure?", this))
			{
				methodEditArea->getTabs()->removeTab (tabIndex);
			}
		}
		else
		{
			methodEditArea->getTabs()->removeTab (tabIndex);
		}

		methodEditArea->getTabs()->setCurrentTabIndex (tabIndex, false);

		saveSettings();
	}
}

void CtrlrLuaMethodEditor::updateTabs()
{
	for (int i=0; i<methodEditArea->getTabs()->getNumTabs(); i++)
	{
		CtrlrLuaMethodCodeEditor *ed = dynamic_cast<CtrlrLuaMethodCodeEditor*>(methodEditArea->getTabs()->getTabContentComponent(i));
		if (ed != nullptr)
		{
			if (ed->getMethod())
			{
				if (ed->getMethod()->isValid())
				{
					methodEditArea->getTabs()->setTabBackgroundColour(i, Colours::white);
				}
				else
				{
					methodEditArea->getTabs()->setTabBackgroundColour(i, Colours::red.brighter(0.6f));
				}
			}
		}
	}
}

void CtrlrLuaMethodEditor::tabChanged(CtrlrLuaMethodCodeEditor *codeEditor, const bool save, const bool recompile)
{
	if (codeEditor == nullptr)
	{
		jassertfalse; // that's not nice
		return;
	}

	for (int i=0; i<methodEditArea->getTabs()->getNumTabs(); i++)
	{
		if (methodEditArea->getTabs()->getTabContentComponent(i) == codeEditor)
		{
			const String n = methodEditArea->getTabs()->getTabNames() [i];

			if (codeEditor->getMethod())
			{
				if (!n.endsWith("*"))
				{
					if (codeEditor->getMethod()->getName() != n)
					{
						/* the name of the method changed, update it */
						methodEditArea->getTabs()->setTabName (i, codeEditor->getMethod()->getName());
					}
				}
				else
				{
					if (codeEditor->getMethod()->getName() != n.substring(0, n.length()-1))
					{
						methodEditArea->getTabs()->setTabName (i, codeEditor->getMethod()->getName() + "*");
					}
				}
			}

			if (codeEditor->getCodeDocument().hasChangedSinceSavePoint())
			{
				if (n.endsWith("*"))
				{
					return;
				}
				else
				{
					methodEditArea->getTabs()->setTabName (i, n + "*");
				}
			}
			else if (n.endsWith("*"))
			{
				methodEditArea->getTabs()->setTabName (i, n.substring (0,n.length()-1));
			}
		}
	}

	if (codeEditor->getMethod() && (recompile || save))
	{
		// methodEditArea->insertOutput (codeEditor->getMethod()->getLastError(), codeEditor->getMethod()->isValid() ? Colours::green : Colours::red);
		methodEditArea->insertOutput(codeEditor->getMethod()->getLastError());
	}

	updateTabs();
}

void CtrlrLuaMethodEditor::setCurrentTab (CtrlrLuaMethod *methodToSetAsCurrent)
{
	for (int i=0; i<methodEditArea->getTabs()->getNumTabs(); i++)
	{
		if (methodEditArea->getTabs()->getTabContentComponent(i))
		{
			CtrlrLuaMethodCodeEditor *editor = dynamic_cast<CtrlrLuaMethodCodeEditor *>(methodEditArea->getTabs()->getTabContentComponent(i));
			if (editor)
			{
				if (editor->getMethod() == methodToSetAsCurrent)
				{
					methodEditArea->getTabs()->setCurrentTabIndex (i);
					return;
				}
			}
		}
	}
}

void CtrlrLuaMethodEditor::createNewTab (CtrlrLuaMethod *method)
{
	if (method == nullptr)
	{
		jassertfalse; // don't do that
		return;
	}

	CtrlrLuaMethodCodeEditor *methodEditor = new CtrlrLuaMethodCodeEditor (*this, method);
	methodEditor->addKeyListener (this);
	methodEditArea->getTabs()->addTab (method->getName(), Colours::white, methodEditor, true, -1);
	methodEditArea->getTabs()->setCurrentTabIndex (methodEditArea->getTabs()->getNumTabs() - 1, true);
	saveSettings(); // save settings
}

void CtrlrLuaMethodEditor::saveSettings()
{
	String settings;
	StringArray openedMethod;
	for (int i=0; i<methodEditArea->getTabs()->getNumTabs(); i++)
	{
		CtrlrLuaMethodCodeEditor *ed = dynamic_cast<CtrlrLuaMethodCodeEditor*>(methodEditArea->getTabs()->getTabContentComponent(i));
		if (ed != nullptr)
		{
			if (ed->getMethod())
			{
				openedMethod.add (ed->getMethod()->getUuid().toString());
			}
		}
	}

	if (methodTree->getRootItem())
	{
		ScopedPointer <XmlElement> treeState(methodTree->getOpennessState(true));

		if (treeState)
		{
			settings << treeState->createDocument("");
			settings << ";";
		}
		settings << openedMethod.joinIntoString(":");
		componentTree.setProperty (Ids::luaMethodEditor, settings, nullptr);
	}
}

// Value tree GUI stuff
const String CtrlrLuaMethodEditor::getUniqueName (const ValueTree &item) const
{
	if (item.hasType (Ids::luaMethod))
	{
		return (item.getProperty(Ids::luaMethodName).toString());
	}
	if (item.hasType(Ids::luaMethodGroup))
	{
		return (item.getProperty (Ids::name).toString());
	}
	if (item.hasType(Ids::luaManagerMethods))
	{
		return ("LUA Method");
	}

	return ("Unknown");
}

const AttributedString CtrlrLuaMethodEditor::getDisplayString(const ValueTree &item)	const
{
	AttributedString str;

	if (item.getType () == Ids::luaMethod)
	{
		Colour text;

		if ((bool)item.getProperty(Ids::luaMethodValid) == false)
			text = Colours::red;
		else
			text = Colours::black;

		str.append (item.getProperty(Ids::luaMethodName).toString()+"\n", Font(12.0f, Font::plain), text);

		if ((int)item.getProperty(Ids::luaMethodSource) == CtrlrLuaMethod::codeInFile)
		{
			str.append (File::descriptionOfSizeInBytes (File(item.getProperty(Ids::luaMethodSourcePath).toString()).getSize()), Font(10.0f, Font::italic), text.brighter(0.2f));
		}
		else
		{
			str.append (File::descriptionOfSizeInBytes (item.getProperty(Ids::luaMethodCode).toString().length()), Font(10.0f, Font::italic), text.brighter(0.2f));
		}

		str.setJustification (Justification::left);
	}

	if (item.getType() == Ids::luaMethodGroup)
	{
		str.append (item.getProperty(Ids::name), Font(14.0f, Font::plain), Colours::black);
		str.append (" ["+String(item.getNumChildren())+"]", Font(10.0f, Font::italic), Colours::darkgrey);

		str.setJustification (Justification::left);
	}

	if (item.getType() == Ids::luaManagerMethods)
	{
		str.append ("LUA Methods", Font(14.0f, Font::bold), Colours::black);

		str.setJustification (Justification::left);
	}

	return (str);
}

const Font CtrlrLuaMethodEditor::getItemFont(const ValueTree &item) const
{
	if (item.hasType(Ids::luaManagerMethods) || item.hasType(Ids::luaMethodGroup))
	{
		return (Font (14.0, Font::bold));
	}

	return (Font(12.0f, Font::plain));
}

Image CtrlrLuaMethodEditor::getIconForItem (const ValueTree &item) const
{
	if (item.hasType (Ids::luaMethod))
	{
		if ((int)item.getProperty (Ids::luaMethodSource) == (int)CtrlrLuaMethod::codeInProperty)
		{
			return (IMAGE(ico_unit_png));
		}

		if ((int)item.getProperty (Ids::luaMethodSource) == (int)CtrlrLuaMethod::codeInFile)
		{
			if (File(item.getProperty(Ids::luaMethodSourcePath)).existsAsFile())
			{
				return (IMAGE(ico_file_png));
			}
			else
			{
				return (IMAGE(ico_unknown_png));
			}
		}
	}
	else if (item.hasType (Ids::luaMethodGroup))
	{
		return (IMAGE(ico_folder_png));
	}
	else if (item.hasType (Ids::luaManagerMethods))
	{
		return (IMAGE(ico_box_png));
	}
	return (IMAGE(ico_unknown_png));
}

void CtrlrLuaMethodEditor::itemClicked (const MouseEvent &e, ValueTree &item)
{
	if (e.mods.isPopupMenu())
	{
		if ( item.hasType (Ids::luaManagerMethods) || item.hasType (Ids::luaMethodGroup) )
		{
			PopupMenu m;
			m.addSectionHeader ("Group operations");
			m.addItem (1, "Add method");
			m.addItem (2, "Add files");
			m.addItem (3, "Add group");
			m.addSeparator();
			if (item.hasType (Ids::luaMethodGroup))
			{
				m.addItem (4, "Remove group");
				m.addItem (5, "Rename group");
			}

			m.addSeparator();
			m.addItem (6, "Sort by name");
			m.addItem (7, "Sort by size");

			const int ret = m.show();

			if (ret == 1)
			{
				addNewMethod (item);
			}
			else if (ret == 2)
			{
				addMethodFromFile (item);
			}
			else if (ret == 3)
			{
				addNewGroup (item);
			}
			else if (ret == 4)
			{
				removeGroup (item);
			}
			else if (ret == 5)
			{
				renameGroup (item);
			}
			else if (ret == 6)
			{
				ChildSorter sorter(true);
				getMethodManager().getManagerTree().sort (sorter, nullptr, false);

				triggerAsyncUpdate();
			}
			else if (ret == 7)
			{
				ChildSorter sorter(false);
				getMethodManager().getManagerTree().sort (sorter, nullptr, false);

				triggerAsyncUpdate();
			}
		}
		else if (item.hasType(Ids::luaMethod))
		{
			PopupMenu m;
			m.addSectionHeader ("Method " + item.getProperty(Ids::luaMethodName).toString());
			if ((int)item.getProperty(Ids::luaMethodSource) == CtrlrLuaMethod::codeInFile)
			{
				if (!File(item.getProperty(Ids::luaMethodSourcePath)).existsAsFile())
				{
					m.addItem (12, "Locate file on disk");
				}
			}

			m.addSeparator();
			m.addItem (2,"Remove method");

			const int ret = m.show();

			if (ret == 11)
			{
				/* convert a in-memory method to a file based one */
			}
			else if (ret == 12)
			{
				/* locate a missing file on disk */
			}
			else if (ret == 10)
			{
				/* convert a method from a file to a in-memory property */
			}
			else if (ret == 2)
			{
				/* remove a method */
				if (SURE("Delete the selected method?", this))
				{
					{
						methodEditArea->closeTabWithMethod (item);
						getMethodManager().removeMethod (item.getProperty(Ids::uuid).toString());
					}

					triggerAsyncUpdate();
				}
			}
		}
	}
}

void CtrlrLuaMethodEditor::itemDoubleClicked (const MouseEvent &e, ValueTree &item)
{
	setEditedMethod (Uuid(item.getProperty(Ids::uuid).toString()));
}

const bool CtrlrLuaMethodEditor::renameItem(const ValueTree &item, const String &newName) const
{
	return (true);
}

const bool CtrlrLuaMethodEditor::canBeRenamed(const ValueTree &item) const
{
	if ( item.getType() == Ids::luaMethod && ((int)item.getProperty(Ids::luaMethodSource) == CtrlrLuaMethod::codeInProperty) )
	{
		return (true);
	}

	if (item.getType() == Ids::luaMethodGroup)
	{
		return (true);
	}

	return (false);
}

const bool CtrlrLuaMethodEditor::isInterestedInDragSource(const ValueTree &item, const DragAndDropTarget::SourceDetails &dragSourceDetails) const
{
	if (item.hasType(Ids::luaMethodGroup) || item.hasType(Ids::luaManagerMethods))
	{
		return (true);
	}

	return (false);
}

var CtrlrLuaMethodEditor::getDragSourceDescription(Array <ValueTree> &selectedTreeItems)
{
	String returnValue;

	for (int i=0; i<methodTree->getNumSelectedItems(); i++)
	{
		CtrlrValueTreeEditorItem *item = dynamic_cast<CtrlrValueTreeEditorItem*>(methodTree->getSelectedItem(i));

		if (item != nullptr)
		{
			returnValue << item->getItemIdentifierString() + ";";
		}
	}

	return (returnValue);
}

void CtrlrLuaMethodEditor::itemDropped (ValueTree &targetItem, const DragAndDropTarget::SourceDetails &dragSourceDetails, int insertIndex)
{
	if ( (targetItem.hasType(Ids::luaMethodGroup) || targetItem.hasType(Ids::luaManagerMethods)) && insertIndex == 0 )
	{
		StringArray ar;
		ar.addTokens (dragSourceDetails.description.toString(), ";", "\"'");

		for (int i=0; i<ar.size(); i++)
		{
			CtrlrValueTreeEditorItem *sourceItem = dynamic_cast<CtrlrValueTreeEditorItem*>(methodTree->findItemFromIdentifierString (ar[i]));
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

void CtrlrLuaMethodEditor::handleAsyncUpdate()
{
	updateRootItem();
}

ChildSorter::ChildSorter (const bool _sortByName) : sortByName(_sortByName)
{
}

int ChildSorter::compareElements (ValueTree first, ValueTree second)
{
	if (sortByName)
	{
		return (first.getProperty(Ids::luaMethodName).toString().compareLexicographically (second.getProperty(Ids::luaMethodName).toString()));
	}
	else
	{
		int firstSize, secondSize;

		if ((int)first.getProperty(Ids::luaMethodSource) == CtrlrLuaMethod::codeInFile)
		{
			firstSize = File (first.getProperty (Ids::luaMethodSourcePath).toString()).getSize();
		}
		else
		{
			firstSize = first.getProperty (Ids::luaMethodCode).toString().length();
		}

		if ((int)second.getProperty(Ids::luaMethodSource) == CtrlrLuaMethod::codeInFile)
		{
			secondSize = File (second.getProperty (Ids::luaMethodSourcePath).toString()).getSize();
		}
		else
		{
			secondSize = second.getProperty (Ids::luaMethodCode).toString().length();
		}

		if (firstSize > secondSize)
		{
			return (-1);
		}
		else
		{
			return (1);
		}
	}
}

StringArray CtrlrLuaMethodEditor::getMenuBarNames()
{
	const char* const names[] = { "File", "Edit", nullptr };
	return StringArray (names);
}

PopupMenu CtrlrLuaMethodEditor::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
	PopupMenu menu;
	if (topLevelMenuIndex == 0)
	{
		menu.addItem (2, "Save");
		menu.addItem (3, "Save and compile");
		menu.addItem (4, "Save and compile all");
		menu.addSeparator ();
		menu.addItem (1, "Close");
	}
	else if (topLevelMenuIndex == 1)
	{
		menu.addItem (4, "Find and replace");
		menu.addSeparator();
		menu.addItem (5, "Settings");
	}
	return (menu);
}

void CtrlrLuaMethodEditor::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	if (menuItemID == 2 && topLevelMenuIndex == 0)
	{
		if (getCurrentEditor())
		{
			getCurrentEditor()->saveDocument();
		}
	}
	else if (menuItemID == 3 && topLevelMenuIndex == 0)
	{
		if (getCurrentEditor())
		{
			getCurrentEditor()->saveAndCompileDocument();
		}
	}
	else if (menuItemID == 4 && topLevelMenuIndex == 0)
	{
		for (int i=0; i<getTabs()->getNumTabs(); i++)
		{
			CtrlrLuaMethodCodeEditor *ed = dynamic_cast<CtrlrLuaMethodCodeEditor*> (getTabs()->getTabContentComponent (i));

			if (ed)
			{
				ed->saveAndCompileDocument();
			}
		}
	}
	else if (menuItemID == 4 && topLevelMenuIndex == 1)
	{
		methodEditArea->showFindDialog();
	}
	else if (menuItemID == 5 && topLevelMenuIndex == 1)
	{
		CtrlrLuaMethodCodeEditorSettings s(*this);
		CtrlrDialogWindow::showModalDialog ("Code editor settings", &s, false, this);

		componentTree.setProperty (Ids::luaMethodEditorFont, owner.getOwner().getFontManager().getStringFromFont (s.getFont()), nullptr);
		componentTree.setProperty (Ids::luaMethodEditorBgColour, COLOUR2STR (s.getColour()), nullptr);
	}
}

ValueTree &CtrlrLuaMethodEditor::getComponentTree()
{
	return (componentTree);
}

CtrlrLuaMethodEditArea *CtrlrLuaMethodEditor::getMethodEditArea()
{
	return (methodEditArea);
}

void CtrlrLuaMethodEditor::searchResultClicked (const String &methodName, const int lineNumber, const int resultPositionStart, const int resultPositionEnd)
{
//	_DBG("CtrlrLuaMethodEditor::searchResultClicked");
//	_DBG("\t"+methodName+" ln:"+STR(lineNumber)+" s:"+STR(resultPositionStart)+" e:"+STR(resultPositionEnd));

	CtrlrLuaMethod *method = getMethodManager().getMethodByName(methodName);
	if (method != nullptr)
	{
		setEditedMethod (method->getUuid());

		if (method->getCodeEditor())
		{
			CodeEditorComponent *ed = method->getCodeEditor()->getCodeComponent();
			CodeDocument &doc		= method->getCodeEditor()->getCodeDocument();
			if (ed)
			{
				ed->selectRegion (CodeDocument::Position(doc,resultPositionStart), CodeDocument::Position(doc,resultPositionEnd));
			}
		}
	}
}
