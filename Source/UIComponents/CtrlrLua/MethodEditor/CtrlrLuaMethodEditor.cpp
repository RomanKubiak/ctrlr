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
#include "CtrlrPropertyEditors/CtrlrPropertyComponent.h"
#include "CtrlrLuaMethodCodeEditorSettings.h"
#include "CtrlrWindowManagers/CtrlrDialogWindow.h"
#include "CtrlrInlineUtilitiesGUI.h"

CtrlrLuaMethodEditor::CtrlrLuaMethodEditor (CtrlrPanel &_owner)
    : owner(_owner),
      methodEditArea (nullptr),
	  methodTree(nullptr),
	  resizer(nullptr),
	  caseCansitive(true),
	  lookInString("Current"),
	  searchInString("Editor"),
	  findDialogActive(false),
	  currentSearchString("")
{
	addAndMakeVisible (resizer			= new StretchableLayoutResizerBar (&layoutManager, 1, true));
	addAndMakeVisible (methodTree		= new CtrlrValueTreeEditorTree ("LUA METHOD TREE", owner));
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
    deleteAndZero (methodEditArea);
	componentTree.removeListener (this);
	masterReference.clear();
	methodTree->deleteRootItem();
	deleteAndZero (methodTree);
	deleteAndZero (resizer);
}

void CtrlrLuaMethodEditor::paint (Graphics& g)
{
    g.fillAll(Colours::lightgrey.brighter(0.2f));
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
				ed->setFontAndColour (owner.getCtrlrManagerOwner().getFontManager().getFontFromString (componentTree.getProperty(Ids::luaMethodEditorFont)), VAR2COLOUR(componentTree.getProperty(Ids::luaMethodEditorBgColour)));
			}
		}
	}
}

void CtrlrLuaMethodEditor::restoreState(const ValueTree &savedState)
{
	restoreProperties (savedState, componentTree, nullptr);

	ScopedPointer <XmlElement> treeState(XmlDocument::parse (savedState.getProperty(Ids::luaMethodEditor).toString().upToLastOccurrenceOf(";", false, true)).release());

	if (treeState)
	{
		methodTree->restoreOpennessState (*treeState, true);
	}

	StringArray openedMethods;
	openedMethods.addTokens (savedState.getProperty(Ids::luaMethodEditor).toString().fromLastOccurrenceOf(";", false, true), ":", "");

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
		ScopedPointer <XmlElement> state (methodTree->getOpennessState(true).release());
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
	    if (key.getKeyCode() == 9)
        {
            // CTRL + TAB
            if (methodEditArea)
            {
                return (methodEditArea->keyPressed (key, originatingComponent));
            }
        }
		if (CharacterFunctions::toUpperCase ((juce_wchar) (key.getKeyCode())) == 70)
		{
			// CTRL + F
			if (getCurrentEditor())
			{
				getCurrentEditor()->getCodeComponent()->showFindPanel(false);
			}
			else
			{
				methodEditArea->showFindDialog();
			}
			return (true);
		}

		if (CharacterFunctions::toUpperCase ((juce_wchar) (key.getKeyCode())) == 71)
		{
			// CTRL + G
			if (getCurrentEditor())
			{
				getCurrentEditor()->getCodeComponent()->showGoTOPanel();
			}
			return (true);
		}

		if (CharacterFunctions::toUpperCase ((juce_wchar) (key.getKeyCode())) == 72)
		{
			// CTRL + H
			if (getCurrentEditor())
			{
				getCurrentEditor()->getCodeComponent()->showFindPanel(true);
			}
			else
			{
				methodEditArea->replaceNextMatch();
			}
			return (true);
		}

		if (key.getKeyCode() == KeyPress::deleteKey)
		{
			// CTRL + delete
			methodEditArea->clearOutputText();
			return (true);
		}
	}

	if (key.getKeyCode() == KeyPress::F3Key) // F3
	{
		methodEditArea->findNextMatch();
		return (true);
	}
	if (key.getModifiers().isAltDown())
	{
		if (CharacterFunctions::toUpperCase ((juce_wchar) (key.getKeyCode())) == 68) // alt+d
		{
			methodEditArea->showDebuggerTab();
			return (true);
		}
		else if (CharacterFunctions::toUpperCase ((juce_wchar) (key.getKeyCode())) == 67) // alt+c
		{
			methodEditArea->showConsoleTab();
			return (true);
		}
	}
    if (getCurrentEditor())
    {
        return (getCurrentEditor()->keyPressed (key,originatingComponent));
    }

    return false;
}

void CtrlrLuaMethodEditor::highlightCode (const String &methodName, const int lineNumber)
{
    CtrlrLuaMethod *method = setEditedMethod(methodName);

    if (method)
    {
        CtrlrLuaMethodCodeEditor *editor = getEditorForMethod (method);

        if (editor)
        {
            editor->gotoLine (lineNumber, true);
        }
    }
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
	AlertWindow wnd(METHOD_NEW, "", AlertWindow::InfoIcon, this);
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

			getMethodManager().addMethod (parentGroup, wnd.getTextEditorContents("methodName"), initialCode, "");
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
	// See if group folder exists
	File groupFolder = owner.getLuaMethodGroupDir(parentGroup);
	if (groupFolder.exists() && groupFolder.isDirectory())
	{
		lastBrowsedSourceDir = groupFolder;
	}

	FileChooser fc ("Select LUA files",
					lastBrowsedSourceDir,
					"*.lua;*.txt",
					owner.getCtrlrManagerOwner().getProperty(Ids::ctrlrNativeFileDialogs));

	if (fc.browseForMultipleFilesToOpen ())
	{
		Array <File> results = fc.getResults();

		for (int i=0; i<results.size(); i++)
		{	// Check that a method with that name does not already exist
			String methodName = results[i].getFileNameWithoutExtension();
			bool nameOK = true;
			for (int j = 0; j < parentGroup.getNumChildren(); j++)
			{
				ValueTree child = parentGroup.getChild(j);
				if (child.hasType(Ids::luaMethod))
				{
					if (methodName == child.getProperty(Ids::luaMethodName).toString())
					{
						nameOK = false;
						break;
					}
				}
			}
			if (nameOK)
			{
				getMethodManager().addMethodFromFile(parentGroup, results[i]);
			}
			else
			{
				AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Add Files", "A method named '"+ methodName +"' already exists in this group, file will be ignored.");
			}
		}
	}

	updateRootItem();

	saveSettings(); // save settings
}

void CtrlrLuaMethodEditor::addNewGroup(ValueTree parentGroup)
{
	AlertWindow wnd(GROUP_NEW, "", AlertWindow::InfoIcon, this);
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

void CtrlrLuaMethodEditor::closeCurrentTab()
{
	closeTab(methodEditArea->getTabs()->getCurrentTabIndex());
}

void CtrlrLuaMethodEditor::closeAllTabs()
{
	CtrlrLuaMethodEditorTabs *tabs = methodEditArea->getTabs();
	while (tabs->getNumTabs() > 0)
	{
		if (!closeTab(0))
		{
			break;
		}
	}
}

bool CtrlrLuaMethodEditor::closeTab(const int tabIndex)
{
	int currentlySelectedTab = methodEditArea->getTabs()->getCurrentTabIndex();
	bool closed = true;
	CtrlrLuaMethodCodeEditor *ed = dynamic_cast<CtrlrLuaMethodCodeEditor*>(methodEditArea->getTabs()->getTabContentComponent(tabIndex));
	if (ed)
	{
		if (ed->getCodeDocument().hasChangedSinceSavePoint())
		{
			if (SURE("There might be some unsaved changes, are you sure?", this))
			{
				methodEditArea->getTabs()->removeTab (tabIndex);
			}
			else
			{
				closed = false;
			}
		}
		else
		{
			methodEditArea->getTabs()->removeTab (tabIndex);
		}

		if (closed)
		{
			if (tabIndex == currentlySelectedTab)
			{	// We closed the selected tab => move to previous tab
				if (currentlySelectedTab > 0)
				{
					currentlySelectedTab = currentlySelectedTab - 1;
				}
			}
			else if (tabIndex < currentlySelectedTab)
			{
				currentlySelectedTab = currentlySelectedTab - 1;
			}
			methodEditArea->getTabs()->setCurrentTabIndex(currentlySelectedTab, false);
			saveSettings();
		}
	}
	return closed;
}

bool CtrlrLuaMethodEditor::canCloseWindow()
{
	bool hasUnsavedChanges = false;
	CtrlrLuaMethodEditorTabs *tabs = methodEditArea->getTabs();
	CtrlrLuaMethodCodeEditor *ed;
	for (int i = 0; i < tabs->getNumTabs(); i++)
	{
		ed = dynamic_cast<CtrlrLuaMethodCodeEditor*>(methodEditArea->getTabs()->getTabContentComponent(i));
		if (ed)
		{
			if (ed->getCodeDocument().hasChangedSinceSavePoint())
			{
				hasUnsavedChanges = true;
				break;
			}
		}
	}
	if (hasUnsavedChanges)
	{
		int ret = AlertWindow::showYesNoCancelBox(AlertWindow::QuestionIcon, "Save changes ("+getOwner().getName()+")", "There are unsaved changes in Lua code. Do you want to save them berfore closing ?", "Save", "Discard", "Cancel", this);
		if (ret == 0)
		{	// Cancel
			return false;
		}
		else if (ret == 1)
		{	// Save all
			saveAndCompileAllMethods();
			return true;
		}
		else
		{	// Discard
			return true;
		}
	}
	else
	{
		return true;
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

CtrlrLuaMethodCodeEditor *CtrlrLuaMethodEditor::getEditorForMethod (CtrlrLuaMethod *method)
{
    for (int i=0; i<methodEditArea->getTabs()->getNumTabs(); i++)
    {
        if (methodEditArea->getTabs()->getTabContentComponent(i))
        {
            CtrlrLuaMethodCodeEditor *editor = dynamic_cast<CtrlrLuaMethodCodeEditor *>(methodEditArea->getTabs()->getTabContentComponent(i));
			if (editor)
			{
				if (editor->getMethod() == method)
                    return (editor);
			}
        }
    }
    return (nullptr);
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
		ScopedPointer <XmlElement> treeState(methodTree->getOpennessState(true).release());

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
		return ("LUA");
	}

	return ("Unknown");
}

const AttributedString CtrlrLuaMethodEditor::getDisplayString(const ValueTree &item)	const
{
	AttributedString str;
	Font fNormal = owner.getOwner().getFontManager().getDefaultNormalFont();
	Font fSmall = owner.getOwner().getFontManager().getDefaultSmallFont();
	if (item.getType () == Ids::luaMethod)
	{
		Colour text;

		if ((bool)item.getProperty(Ids::luaMethodValid) == false)
			text = Colours::red;
		else
			text = Colours::black;

		str.append (item.getProperty(Ids::luaMethodName).toString()+"\n", fNormal, text);

		if ((int)item.getProperty(Ids::luaMethodSource) == CtrlrLuaMethod::codeInFile)
		{
			str.append (File::descriptionOfSizeInBytes (owner.getLuaMethodSourceFile(&item).getSize()), fSmall, text.brighter(0.2f));
		}
		else
		{
			str.append (File::descriptionOfSizeInBytes (item.getProperty(Ids::luaMethodCode).toString().length()), fSmall, text.brighter(0.2f));
		}

		str.setJustification (Justification::left);
	}

	if (item.getType() == Ids::luaMethodGroup)
	{
		str.append (item.getProperty(Ids::name), fNormal, Colours::black);
		str.append (" ["+String(item.getNumChildren())+"]", fSmall, Colours::darkgrey);

		str.setJustification (Justification::left);
	}

	if (item.getType() == Ids::luaManagerMethods)
	{
		str.append ("LUA", fNormal.boldened(), Colours::black);

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

Drawable* CtrlrLuaMethodEditor::getIconForItem (const ValueTree &item) const
{
	if (item.hasType (Ids::luaMethod))
	{
		if ((int)item.getProperty (Ids::luaMethodSource) == (int)CtrlrLuaMethod::codeInProperty)
		{
			return gui::createDrawable(BIN2STR(cog_svg));
		}

		if ((int)item.getProperty (Ids::luaMethodSource) == (int)CtrlrLuaMethod::codeInFile)
		{
			if (owner.getLuaMethodSourceFile(&item).existsAsFile())
			{
				return gui::createDrawable(BIN2STR(file_svg));
			}
			else
			{
				return gui::createDrawable(BIN2STR(radio_svg));
			}
		}
	}
	else if (item.hasType (Ids::luaMethodGroup))
	{
		return gui::createDrawable(BIN2STR(folder_svg));
	}
	else if (item.hasType (Ids::luaManagerMethods))
	{
		return gui::createDrawable(BIN2STR(folder_open_svg));
	}

	return gui::createDrawable(BIN2STR(radio_svg));
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
			bool isMethodGroup = item.hasType(Ids::luaMethodGroup);
			if (isMethodGroup)
			{
				m.addItem (4, "Remove group");
				m.addItem (5, "Rename group");
			}
			else
			{	// Root element => add a menu to convert method to filesto files
				m.addItem(4, "Convert to files...");
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
				if (isMethodGroup)
				{	// Case of a method group => remove group
					removeGroup(item);
				}
				else
				{	// Case of to root element => export to files
					convertToFiles();
				}
			}
			else if (ret == 5)
			{
				renameGroup (item);
			}
			else if (ret == 6)
			{
				ChildSorter sorter(true,*this);
				getMethodManager().getManagerTree().sort (sorter, nullptr, false);

				triggerAsyncUpdate();
			}
			else if (ret == 7)
			{
				ChildSorter sorter(false,*this);
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
				if (!owner.getLuaMethodSourceFile(&item).existsAsFile())
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



ChildSorter::ChildSorter(const bool _sortByName, CtrlrLuaMethodEditor &_parent) :sortByName(_sortByName),parent(_parent)
{
}

int ChildSorter::compareElements (ValueTree first, ValueTree second)
{
	if (sortByName)
	{
		return (first.getProperty(Ids::luaMethodName).toString().compareNatural (second.getProperty(Ids::luaMethodName).toString()));
	}
	else
	{
		int firstSize, secondSize;

		if ((int)first.getProperty(Ids::luaMethodSource) == CtrlrLuaMethod::codeInFile)
		{
			firstSize = parent.getOwner().getLuaMethodSourceFile(&first).getSize();
		}
		else
		{
			firstSize = first.getProperty (Ids::luaMethodCode).toString().length();
		}

		if ((int)second.getProperty(Ids::luaMethodSource) == CtrlrLuaMethod::codeInFile)
		{
			secondSize = parent.getOwner().getLuaMethodSourceFile(&second).getSize();
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
		menu.addSeparator();
		menu.addItem(5, "Close current tab");
		menu.addItem(6, "Close all tabs");
		menu.addSeparator ();
		menu.addItem(7, "Convert to files...");
		menu.addSeparator();
		menu.addItem (1, "Close");
	}
	else if (topLevelMenuIndex == 1)
	{
		menu.addItem (4, "Find and replace");
		menu.addItem (7, "Debugger");
		menu.addItem (8, "Console");

		menu.addItem (5, "Clear Output");
		menu.addSeparator();
		menu.addItem (6, "Settings");
	}
	return (menu);
}

void CtrlrLuaMethodEditor::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	switch (topLevelMenuIndex) {
	case 0:
		switch (menuItemID) {
		case 1:
			if (isCurrentlyModal())
				exitModalState(-1);

			if (canCloseWindow()) {
				owner.getWindowManager().toggle(CtrlrPanelWindowManager::LuaMethodEditor, false);
			}
			break;
		case 2:
			if (getCurrentEditor())
				getCurrentEditor()->saveDocument();
			break;
		case 3:
			if (getCurrentEditor())
				getCurrentEditor()->saveAndCompileDocument();
			break;
		case 4:
			saveAndCompileAllMethods();
			break;
		case 5:
			closeCurrentTab();
			break;
		case 6:
			closeAllTabs();
			break;
		case 7:
			convertToFiles();
			break;
		};
		break;
	case 1:
		switch (menuItemID) {
		case 4:
			methodEditArea->showFindDialog();
			break;
		case 5:
			methodEditArea->clearOutputText();
			break;
		case 6:
			CtrlrLuaMethodCodeEditorSettings s(*this);
			CtrlrDialogWindow::showModalDialog ("Code editor settings", &s, false, this);

			componentTree.setProperty (Ids::luaMethodEditorFont,
						   owner.getCtrlrManagerOwner().getFontManager().getStringFromFont (s.getFont()),
						   nullptr);
			componentTree.setProperty (Ids::luaMethodEditorBgColour,
						   COLOUR2STR (s.getColour()), nullptr);
			break;
		case 7:
			methodEditArea->showDebuggerTab();
			break;
		case 8:
			methodEditArea->showConsoleTab();
		}
	}
}

void CtrlrLuaMethodEditor::saveAndCompileAllMethods()
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

void CtrlrLuaMethodEditor::convertToFiles()
{
	// Show confirmation dialog
	const String location = owner.getPanelLuaDirPath();
	const int confirm = AlertWindow::showOkCancelBox(AlertWindow::QuestionIcon, "Convert to files", "Do you want to convert all Lua methods to files (location=" + location + ")?", "Yes", "No");
	if (confirm == 1)
	{
		Result res = owner.convertLuaMethodsToFiles(location);
		if (res.wasOk())
		{
			owner.luaManagerChanged();
			triggerAsyncUpdate();
		}
		else
		{
			AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Convert to files", "Failed to convert Lua methods to files.\n" + res.getErrorMessage());
		}
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

void CtrlrLuaMethodEditor::insertRawDebuggerOutput(const String &debuggerOutput)
{
    if (methodEditArea->getLuaDebuggerPrompt())
        methodEditArea->getLuaDebuggerPrompt(true)->insertRawDebuggerOutput (debuggerOutput);
}

void CtrlrLuaMethodEditor::setJsonDebuggerOutput(const String &jsonData)
{
}

const String CtrlrLuaMethodEditor::getCurrentDebuggerCommand(const bool clearTheReturnedCommand)
{
    if (methodEditArea->getLuaDebuggerPrompt())
    {
        return (methodEditArea->getLuaDebuggerPrompt()->getCurrentDebuggerCommand(clearTheReturnedCommand));
    }

    return ("");
}

int CtrlrLuaMethodEditor::waitForCommand()
{
	return (getParentComponent()->runModalLoop());
}
