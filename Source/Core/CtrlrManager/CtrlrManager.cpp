#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "Plugin/CtrlrProcessor.h"
#include "CtrlrComponents/CtrlrComponent.h"
#include "CtrlrPanel/CtrlrPanelCanvas.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrApplicationWindow/CtrlrEditor.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrLog.h"

CtrlrManager::CtrlrManager(CtrlrProcessor *_owner, CtrlrLog &_ctrlrLog)
	:	managerTree(Ids::manager),
		ctrlrLog(_ctrlrLog),
		owner(_owner),
		ctrlrWindowManager(*this),
		ctrlrMidiDeviceManager(*this),
		ctrlrDocumentPanel(nullptr),
		ctrlrManagerVst(nullptr),
		audioThumbnailCache(256),
		ctrlrPlayerInstanceMode(InstanceMulti),
		ctrlrManagerRestoring(false),
		invalidModulator(nullptr),
		nullPanel(nullptr),
		ctrlrFontManager(nullptr)
{
	ctrlrManagerVst.reset(new CtrlrManagerVst(*this));

	commandManager.addListener (this);
	audioFormatManager.registerBasicFormats ();

	ctrlrDocumentPanel.reset(new CtrlrDocumentPanel(*this));
	nullPanel = new CtrlrPanel(*this);
	nullModulator = new CtrlrModulator (*nullPanel);
    ctrlrFontManager.reset(new CtrlrFontManager (*this));
}

CtrlrManager::~CtrlrManager()
{
	commandManager.removeListener (this);
	ctrlrDocumentPanel->closeAllDocuments(false);
	ctrlrPanels.clear();
	managerTree.removeAllChildren(0);
	deleteAndZero (nullModulator);
	deleteAndZero (nullPanel);
}

void CtrlrManager::setManagerReady()
{
	managerTree.addListener (this);
	managerTree.addChild (ctrlrMidiDeviceManager.getManagerTree(), -1, 0);
	managerTree.addChild (ctrlrWindowManager.getManagerTree(), -1, 0);

	if (ctrlrEditor)
	{
		ctrlrEditor->activeCtrlrChanged();
	}
}

void CtrlrManager::setDefaults()
{
	if (ctrlrProperties != nullptr)
		delete (ctrlrProperties.release());

	ctrlrProperties.reset(new CtrlrProperties(*this));

	setProperty (Ids::ctrlrLogToFile, false);
	setProperty (Ids::ctrlrLuaDebug, false);
	setProperty (Ids::ctrlrVersionSeparator, "_");
	setProperty (Ids::ctrlrVersionCompressed, false);
	setProperty (Ids::ctrlrMidiMonInputBufferSize, 8192);
	setProperty (Ids::ctrlrMidiMonOutputBufferSize, 8192);
	setProperty (Ids::ctrlrLuaDisabled, false);
	setProperty (Ids::ctrlrOverwriteResources, true);
	setProperty (Ids::ctrlrAutoSave, true);
	setProperty (Ids::ctrlrAutoSaveInterval, 300);
	setProperty (Ids::ctrlrLogOptions, 32);
	setProperty (Ids::ctrlrUseEditorWrapper, true);
	setProperty (Ids::ctrlrPropertiesAreURLs, true);
	setProperty (Ids::ctrlrNativeAlerts, false);
	setProperty (Ids::ctrlrNativeFileDialogs, true);
	setProperty (Ids::ctrlrPrivateKey, "");
	setProperty (Ids::ctrlrFontSizeBaseValue, 14.0f);
    setProperty (Ids::ctrlrScrollbarThickness, 18.0f);
    setProperty (Ids::ctrlrColourScheme, "Light");
    setProperty (Ids::ctrlrLookAndFeel, "Light");
    setProperty (Ids::ctrlrMenuBarHeight, 24);
    setProperty (Ids::ctrlrTabBarDepth, 24.0);
	setProperty (Ids::uiLuaConsoleInputRemoveAfterRun, true);
	setProperty (Ids::luaCtrlrSaveState, COMBO_ITEM_NONE);
	setProperty (Ids::luaCtrlrRestoreState, COMBO_ITEM_NONE);
}

CtrlrManagerVst &CtrlrManager::getVstManager()
{
	return (*ctrlrManagerVst);
}

void CtrlrManager::addModulator (CtrlrModulator *modulatorToAdd)
{
    // _DBG("CtrlrManager::addModulator [PRE] vstIndex=="+modulatorToAdd->getProperty(Ids::vstIndex).toString());
	ctrlrManagerVst->set (modulatorToAdd);
	ctrlrModulators.addIfNotAlreadyThere (modulatorToAdd);
	// _DBG("CtrlrManager::addModulator [POST] vstIndex=="+modulatorToAdd->getProperty(Ids::vstIndex).toString());

}

void CtrlrManager::removeModulator(CtrlrModulator *modulatorToDelete)
{
	ctrlrManagerVst->remove (modulatorToDelete);
	ctrlrModulators.removeAllInstancesOf (modulatorToDelete);
}

bool CtrlrManager::containsCtrlrComponent (CtrlrComponent *componentToLookFor)
{
	if (componentToLookFor == 0)
		return (false);

	return (ctrlrModulators.contains(&componentToLookFor->getOwner()));
}

CtrlrModulator* CtrlrManager::getModulator (const String& name) const
{
	for (int i=0; i<ctrlrModulators.size(); ++i)
	{
		if (ctrlrModulators[i]->getName() == name)
		{
			return (ctrlrModulators[i]);
		}
	}

	return (0);
}

const Array <CtrlrModulator*> CtrlrManager::getModulatorsByMidiType(const CtrlrMidiMessageType typeToFilter)
{
	Array <CtrlrModulator *>ret;
	for (int i=0; i<ctrlrModulators.size(); i++)
	{
		if (ctrlrModulators[i]->getMidiMessage().getMidiMessageType() == typeToFilter)
		{
			ret.add (ctrlrModulators[i]);
		}
	}

	return (ret);
}

const Array <CtrlrModulator*> CtrlrManager::getModulatorsByUIType(const Identifier &typeToFilter)
{
	Array <CtrlrModulator *>ret;
	for (int i=0; i<ctrlrModulators.size(); i++)
	{
		if (ctrlrModulators[i]->getComponentType() == typeToFilter)
		{
			ret.add (ctrlrModulators[i]);
		}
	}

	return (ret);
}

void CtrlrManager::allPanelsInitialized()
{
	listeners.call (&CtrlrManager::Listener::managerStateChanged, PanelsLoaded);

	for (int i=0; i<ctrlrModulators.size(); i++)
	{
		ctrlrModulators[i]->allModulatorsInitialized();
	}
}

CtrlrPanel *CtrlrManager::addPanel(const ValueTree &savedState, const bool showUI)
{
	CtrlrPanel *panel = new CtrlrPanel(*this, getUniquePanelName("Ctrlr Panel"), ctrlrPanels.size());

	ctrlrPanels.add (panel);
	panel->restoreState (savedState);
	managerTree.addChild (panel->getPanelTree(), -1, 0);

	if (showUI)
	{
		addPanel (panel->getEditor(true));
	}

	organizePanels();

	return (panel);
}

void CtrlrManager::addPanel (CtrlrPanelEditor *panelToAdd)
{
	ctrlrDocumentPanel->addDocument ((Component *)panelToAdd, Colours::lightgrey, true);
}

void CtrlrManager::restoreState (const ValueTree &savedTree)
{
	_DBG("CtrlrManager::restoreState enter");
	if (savedTree.isValid())
	{
		// Something has changed in Juce 4.0
		// and a lock is needed
		MessageManagerLock mmlock;

		ctrlrManagerRestoring = true;

		restoreProperties (savedTree, managerTree);

		if (owner->getOverrides().isValid())
		{
			for (int i=0; i<owner->getOverrides().getNumProperties(); i++)
			{
				setProperty (owner->getOverrides().getPropertyName(i), owner->getOverrides().getPropertyAsValue(owner->getOverrides().getPropertyName(i), 0));
			}
		}

		managerTree.removeAllChildren (0);
		managerTree.addChild (ctrlrMidiDeviceManager.getManagerTree(), -1, 0);
		managerTree.addChild (ctrlrWindowManager.getManagerTree(), -1, 0);

		if (savedTree.getChildWithName(Ids::midiDeviceManager).isValid())
		{
			ctrlrMidiDeviceManager.restoreState (savedTree.getChildWithName(Ids::midiDeviceManager));
		}

		if (savedTree.getChildWithName(Ids::uiWindowManager).isValid())
		{
			ctrlrWindowManager.restoreState (savedTree.getChildWithName(Ids::uiWindowManager));
		}

		if (getInstanceMode() != InstanceMulti && savedTree.hasType (Ids::panelState))
		{
			restoreInstanceState (savedTree);
			_DBG("CtrlrManager::restoreState instance is not multi, exit restoreInstanceState");
			return;
		}

		for (int i=0; i<savedTree.getNumChildren(); i++)
		{
			if (savedTree.getChild(i).hasType (Ids::panel))
			{
				addPanel (savedTree.getChild(i));
			}
		}

		if (ctrlrEditor)
		{
			restoreEditorState();
		}

		ctrlrManagerRestoring = false;
	}

	_DBG("CtrlrManager::restoreState exit");
}

void CtrlrManager::restoreState (const XmlElement &savedState)
{
	restoreState (ValueTree::fromXml(savedState));
}

const String CtrlrManager::getUniquePanelName(const String &proposedName)
{
	String n = proposedName;
	uint32 i = ctrlrPanels.size();

	while (getPanel(n))
	{
		n = proposedName + String(++i);
	}
	return (n);
}

CtrlrPanel *CtrlrManager::getPanel(const String &panelName)
{
	for (int i=0; i<ctrlrPanels.size(); i++)
	{
		CtrlrPanel *ctrlrPanel = ctrlrPanels[i];
		if (ctrlrPanel != 0)
		{
			if (ctrlrPanel->getProperty (Ids::name) == panelName)
			{
				return (ctrlrPanel);
			}
		}
	}
	return (0);
}

bool CtrlrManager::canCloseWindow()
{
	for (int i = 0; i<getNumPanels(); i++)
	{
		CtrlrPanel *panel = getPanel(i);
		if (panel != nullptr)
		{
			if (!panel->canClose(false))
			{
				return false;
			}
		}
	}
	return true;
}

void CtrlrManager::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::ctrlrAutoSave)
	{
		if ((bool)getProperty (property) == true)
		{
			startTimer (TIMER_AUTO_SAVE, (int)getProperty (Ids::ctrlrAutoSaveInterval)*1000);
		}
		else
		{
			stopTimer (TIMER_AUTO_SAVE);
		}
	}
	else if (property == Ids::ctrlrAutoSaveInterval)
	{
		stopTimer (TIMER_AUTO_SAVE);

		if ((bool)getProperty (Ids::ctrlrAutoSave) == true)
		{
			startTimer (TIMER_AUTO_SAVE, (int)getProperty (Ids::ctrlrAutoSaveInterval)*1000);
		}
	}
	else if (property == Ids::ctrlrLogToFile)
	{
		ctrlrLog.setLogToFile ((bool)getProperty(property));
	}
	else if (property == Ids::ctrlrLuaDebug)
	{
		for (int i=0; i<ctrlrPanels.size(); i++)
		{
			ctrlrPanels[i]->setLuaDebug((bool)getProperty(property));
		}
	}
	else if (property == Ids::ctrlrLogOptions)
	{
		ctrlrLog.setMidiLogOptions (getProperty(property));
	}
	else if (property == Ids::ctrlrNativeAlerts)
	{
		if (getEditor())
		    getEditor()->getLookAndFeel().setUsingNativeAlertWindows((bool)getProperty(property));
	}
}

bool CtrlrManager::isValidComponentName(const String &name)
{
	if (name.length() < 3 || name.length() > 256)
		return (false);

	return (true);
}

CtrlrPanel *CtrlrManager::getActivePanel()
{
	CtrlrPanelEditor *ed = dynamic_cast<CtrlrPanelEditor*>(ctrlrDocumentPanel->getActiveDocument());

	if (ed)
	{
		return (&ed->getOwner());
	}
	else
	{
		return (0);
	}
}

void CtrlrManager::removePanel (CtrlrPanelEditor *editor)
{
	if (editor)
	{
		CtrlrPanel *panel = &editor->getOwner();

		if (panel)
		{
			for (int i=0; i<panel->getModulators().size(); i++)
			{
				ctrlrModulators.removeAllInstancesOf (panel->getModulators() [i]);
				ctrlrManagerVst->remove (panel->getModulators() [i]);
			}

			ctrlrDocumentPanel->closeDocument (editor, true);
			ctrlrPanels.removeObject (panel, true);
		}

		organizePanels();
	}
}

void CtrlrManager::restoreEditorState()
{
	if (getProperty(Ids::ctrlrEditorBounds).toString() == "")
	{
		if (getInstanceMode() == InstanceSingle || getInstanceMode() == InstanceSingleRestriced)
		{
			Rectangle<int> r(32, 32, 800, 600);

			if (getActivePanel() && getActivePanel()->getEditor())
			{
				r = VAR2RECT(getActivePanel()->getEditor()->getProperty (Ids::uiPanelCanvasRectangle));
			}

			ctrlrEditor->setSize (r.getWidth(), r.getHeight());
			return;
		}
	}
	//ctrlrEditor->centreWithSize(800, 600);
}

void CtrlrManager::setEditor (CtrlrEditor *editorToSet)
{
	ctrlrEditor = editorToSet;

	restoreEditorState();
}

int CtrlrManager::getModulatorVstIndexByName(const String &modulatorName)
{
	CtrlrModulator *m = getModulator(modulatorName);

	if (m)
	{
		return (m->getVstIndex());
	}
	else
	{
		return (-1);
	}
}

int CtrlrManager::compareElements (CtrlrModulator *first, CtrlrModulator *second)
{
	if (first->getVstIndex() < second->getVstIndex())
		return (-1);
	else if (first->getVstIndex() == second->getVstIndex())
		return (0);
	else if (first->getVstIndex() > second->getVstIndex())
		return (1);
	else
		return (0);
}

int CtrlrManager::compareElements (CtrlrPanel *first, CtrlrPanel *second)
{
	if (first->getPanelIndex() < second->getPanelIndex())
		return (-1);
	else if (first->getPanelIndex() == second->getPanelIndex())
		return (0);
	else if (first->getPanelIndex() > second->getPanelIndex())
		return (1);
	else
		return (0);
}

void CtrlrManager::organizePanels()
{
	ctrlrPanels.sort (*this);
	for (int i=0; i<ctrlrPanels.size(); i++)
	{
		ctrlrPanels[i]->setProperty (Ids::panelIndex, i);
	}
}

void CtrlrManager::handleAsyncUpdate()
{
}

int CtrlrManager::getPanelForModulator(const int modulatorIndex)
{
	if (ctrlrModulators[modulatorIndex])
	{
		return (ctrlrModulators[modulatorIndex]->getOwnerPanel().getPanelIndex());
	}
	return (-1);
}

int CtrlrManager::getNextVstIndex()
{
	return (ctrlrManagerVst->getFirstFree());
}

void CtrlrManager::openPanelFromFile(Component *componentToAttachMenu)
{
	FileChooser fc ("Open panel",
						File(getProperty(Ids::ctrlrLastBrowsedFileDirectory)),
						"*.panel;*.panelz;*.bpanel;*.bpanelz;*.*",
						(bool)getProperty(Ids::ctrlrNativeFileDialogs));

	if (fc.browseForFileToOpen())
	{
		openPanelInternal(fc.getResult());
		panelFileOpened (fc.getResult());
	}
}

void CtrlrManager::panelFileOpened(const File &panelFile)
{
	StringArray recentFiles;
	recentFiles.addTokens (getProperty (Ids::ctrlrRecenetOpenedPanelFiles).toString(), ";", "\"'");
	recentFiles.insert (0, panelFile.getFullPathName());
	recentFiles.removeRange (9, recentFiles.size() - 10);
	setProperty (Ids::ctrlrRecenetOpenedPanelFiles, recentFiles.joinIntoString(";"));

	setProperty (Ids::ctrlrLastBrowsedFileDirectory, panelFile.getFullPathName());
}

void CtrlrManager::openPanelInternal(const File &fileToOpen)
{
	setProperty(Ids::panelLastSaveDir, fileToOpen.getParentDirectory().getFullPathName());

	ValueTree panelTree;

	if (fileToOpen.getFileExtension().startsWith(".b"))
	{
		panelTree = CtrlrPanel::openBinPanel(fileToOpen);
	}
	else
	{
		panelTree = CtrlrPanel::openXmlPanel(fileToOpen);
	}
	if (panelTree.isValid())
	{
		// Patch panelFilePath property to match the actual file
		panelTree.setProperty(Ids::panelFilePath, fileToOpen.getFullPathName(), nullptr);
		addPanel(panelTree, true);
	}
}

void CtrlrManager::openPanelInternal(const ValueTree &panelTree)
{
	if (panelTree.isValid())
	{
		addPanel(panelTree, true);
	}
}

void CtrlrManager::changeListenerCallback (ChangeBroadcaster* source)
{
}

CtrlrPanel *CtrlrManager::getPanelByUid(const String &uid)
{
	for (int i=0; i<ctrlrPanels.size(); i++)
	{
		if (ctrlrPanels[i]->getProperty (Ids::panelUID) == uid)
		{
			return (ctrlrPanels[i]);
		}
	}

	return (0);
}

CtrlrPanel *CtrlrManager::getPanel(const int panelIndex)
{
	if (panelIndex < ctrlrPanels.size())
	{
		return (ctrlrPanels[panelIndex]);
	}
	return (0);
}

int CtrlrManager::getNumPanels()
{
	return (ctrlrPanels.size());
}

CtrlrModulator *CtrlrManager::getModulatorByVstIndex(const int index)
{
	if (ctrlrManagerVst)
		return (ctrlrManagerVst->get(index));
	else
		return (nullptr);
}

int CtrlrManager::getNumModulators(const bool onlyVstParameters)
{
	if (onlyVstParameters)
	{
		if (ctrlrManagerVst.get())
			return (ctrlrManagerVst->getLargestIndex() + 1);
		else
			return (CTRLR_DEFAULT_PARAMETER_COUNT);
	}
	else
	{
		return (ctrlrModulators.size() + 1);
	}
}

void CtrlrManager::saveStateToDisk()
{
    sendActionMessageToWindow("save");
}

void CtrlrManager::sendActionMessageToWindow(const String &actionMessage)
{
    if (JUCEApplication::isStandaloneApp())
    {
        sendActionMessage (actionMessage);
    }
}

void CtrlrManager::timerCallback (int timerId)
{
	if (timerId == TIMER_AUTO_SAVE)
	{
		saveStateToDisk();
	}
}

const File CtrlrManager::getCtrlrPropertiesDirectory()
{
	return (getCtrlrProperties().getProperties().getUserSettings()->getFile().getParentDirectory());
}

CtrlrProperties &CtrlrManager::getCtrlrProperties()
{
	return (*ctrlrProperties);
}

ApplicationProperties *CtrlrManager::getApplicationProperties()
{
	if (ctrlrProperties)
	{
		return (&ctrlrProperties->getProperties());
	}
	else
	{
		return (nullptr);
	}
}

void CtrlrManager::applicationCommandInvoked (const ApplicationCommandTarget::InvocationInfo &info)
{
}

void CtrlrManager::applicationCommandListChanged ()
{
}
