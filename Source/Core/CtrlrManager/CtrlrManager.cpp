#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrProcessor.h"
#include "CtrlrComponents/CtrlrComponent.h"
#include "CtrlrPanel/CtrlrPanelCanvas.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrApplicationWindow/CtrlrEditor.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrLog.h"
#include "CtrlrApplicationWindow/CtrlrLookAndFeel.h"

CtrlrManager::CtrlrManager(CtrlrProcessor *_owner, CtrlrLog &_ctrlrLog)
	:	managerTree(Ids::manager),
		ctrlrLog(_ctrlrLog),
		owner(_owner),
		ctrlrWindowManager(*this),
		ctrlrMidiDeviceManager(*this),
		ctrlrDocumentPanel(0),
		ctrlrManagerVst(nullptr),
		audioThumbnailCache(256),
		ctrlrPlayerInstanceMode(InstanceMulti),
		ctrlrManagerRestoring(false),
		updateManager(*this),
		invalidModulator(nullptr),
		nullPanel(nullptr),
		ctrlrFontManager(nullptr)
{
	commandManager.addListener (this);

	LookAndFeel::setDefaultLookAndFeel (ctrlrLookAndFeel = new CtrlrLookAndFeel(*this));

	audioFormatManager.registerBasicFormats ();

	ctrlrManagerVst			= new CtrlrManagerVst(*this);
	ctrlrDocumentPanel		= new CtrlrDocumentPanel(*this);
	nullPanel				= new CtrlrPanel(*this);
	nullModulator			= new CtrlrModulator (*nullPanel);
    ctrlrFontManager        = new CtrlrFontManager (*this);

	if (!initEmbeddedInstance())
	{
		setDefaults();
	}

	managerTree.addListener (this);
	managerTree.addChild (ctrlrMidiDeviceManager.getManagerTree(), -1, 0);
	managerTree.addChild (ctrlrWindowManager.getManagerTree(), -1, 0);

	if (ctrlrEditor)
	{
		ctrlrEditor->activeCtrlrChanged();
	}
}

CtrlrManager::~CtrlrManager()
{
	commandManager.removeListener (this);
	ctrlrDocumentPanel->closeAllDocuments(false);
	ctrlrPanels.clear();
	managerTree.removeAllChildren(0);
	deleteAndZero (ctrlrLookAndFeel);
	deleteAndZero (nullModulator);
	deleteAndZero (nullPanel);
}

void CtrlrManager::setDefaults()
{
	if (ctrlrProperties != nullptr)
		delete (ctrlrProperties.get());

	ctrlrProperties = new CtrlrProperties(*this);

	setProperty (Ids::ctrlrLogToFile, false);
	setProperty (Ids::ctrlrLuaDebug, false);
	setProperty (Ids::ctrlrCheckForUpdates, false);
	setProperty (Ids::ctrlrUpdateUrl, "http://ctrlr.org/update/");
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
	setProperty (Ids::uiLuaConsoleInputRemoveAfterRun, true);
}

CtrlrManagerVst &CtrlrManager::getVstManager()
{
	return (*ctrlrManagerVst);
}

void CtrlrManager::addModulator (CtrlrModulator *modulatorToAdd)
{
	// ctrlrManagerVst->set (modulatorToAdd);
	ctrlrModulators.addIfNotAlreadyThere (modulatorToAdd);
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
	_DBG("CtrlrManager::restoreState ValueTree");
	if (savedTree.isValid())
	{
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
}

void CtrlrManager::restoreState (const XmlElement &savedState)
{
	_DBG("CtrlrManager::restoreState XML");
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
		if (getCtrlrLookAndFeel())
		{
			getCtrlrLookAndFeel()->setUsingNativeAlerts(getProperty(property));
		}
	}
}

const bool CtrlrManager::isValidComponentName(const String &name)
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
	Rectangle<int> r;

	if (getProperty(Ids::ctrlrEditorBounds).toString() == String::empty)
	{
		if (getInstanceMode() == InstanceSingle || getInstanceMode() == InstanceSingleRestriced)
		{
			if (getActivePanel() && getActivePanel()->getEditor())
			{
				Rectangle<int> r1 = VAR2RECT(getActivePanel()->getEditor()->getProperty (Ids::uiPanelCanvasRectangle));
				r = r1.withHeight (r1.getHeight());
			}
		}
	}
	else
	{
		r = VAR2RECT(getProperty(Ids::ctrlrEditorBounds, "0 0 720 480"));
	}

	ctrlrEditor->setSize (r.getWidth(), r.getHeight());
}

void CtrlrManager::setEditor (CtrlrEditor *editorToSet)
{
	ctrlrEditor = editorToSet;

	restoreEditorState();
}

const int CtrlrManager::getModulatorVstIndexByName(const String &modulatorName)
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

const int CtrlrManager::getPanelForModulator(const int modulatorIndex)
{
	if (ctrlrModulators[modulatorIndex])
	{
		return (ctrlrModulators[modulatorIndex]->getOwner().getPanelIndex());
	}
	return (-1);
}

const int CtrlrManager::getNextVstIndex()
{
	return (ctrlrManagerVst->getFirstFree());
}

void CtrlrManager::openPanelFromFile(Component *componentToAttachMenu)
{
	FileChooser fc ("Open panel", File(getProperty(Ids::ctrlrLastBrowsedFileDirectory)), "*.panel;*.panelz;*.bpanel;*.bpanelz;*.*", true);

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
	setProperty(Ids::lastBrowsedPanelDir, fileToOpen.getParentDirectory().getFullPathName());

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

const int CtrlrManager::getNumPanels()
{
	return (ctrlrPanels.size());
}

CtrlrModulator *CtrlrManager::getModulatorByVstIndex(const int index)
{
	if (ctrlrManagerVst.get())
		return (ctrlrManagerVst->get(index));
	else
		return (nullptr);
}

const int CtrlrManager::getNumModulators(const bool onlyVstParameters)
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
	if (JUCEApplication::isStandaloneApp())
	{
		if (getCtrlrProperties().saveIfNeeded())
		{
			_INF("CtrlrManager::saveStateToDisk ok");
		}
		else
		{
			_INF("CtrlrManager::saveStateToDisk failed");
		}
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
