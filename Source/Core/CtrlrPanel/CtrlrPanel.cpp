#include "stdafx.h"
#include "CtrlrLuaManager.h"
#include "CtrlrPanel.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrProcessor.h"
#include "CtrlrMacros.h"
#include "CtrlrUtilities.h"
#include "CtrlrLog.h"
#include "CtrlrPanel/CtrlrPanelCanvas.h"
#include "CtrlrComponents/CtrlrComponentTypeManager.h"
#include "JuceClasses/LMemoryBlock.h"
#include "CtrlrMIDI/CtrlrMIDISettingsDialog.h"
#include "CtrlrComponents/CtrlrComponent.h"

CtrlrPanel::CtrlrPanel(CtrlrManager &_owner)
		: owner(_owner),
		panelTree(Ids::panel),
		panelWindowManager(*this),
		ctrlrSysexProcessor(*this),
		processor(*this),
		snapshot(*this),
		panelEvaluationScope(*this),
		globalEvaluationScope(*this),
		resourceManager(*this),
		midiInputThread(*this, inputDevice),
		midiControllerInputThread(*this, controllerDevice),
		ctrlrLuaManager(nullptr),
		currentActionIndex(0),
		indexOfSavedState(-1)
{
}

CtrlrPanel::CtrlrPanel(CtrlrManager &_owner, const String &panelName, const int idx)
	:	owner(_owner),
		panelTree(Ids::panel),
		panelWindowManager(*this),
		ctrlrSysexProcessor(*this),
		processor(*this),
		snapshot(*this),
		panelEvaluationScope(*this),
		globalEvaluationScope(*this),
		resourceManager(*this),
		midiInputThread(*this, inputDevice),
		midiControllerInputThread(*this, controllerDevice),
		restoreStateStatus(true),
		ctrlrLuaManager(0),
		ctrlrPanelEditor(nullptr),
		initialProgram(Ids::panelState),
		boostrapStateStatus(false),
		outputDevicePtr(nullptr),
		ctrlrPanelUndoManager(nullptr),
		currentActionIndex(0),
		indexOfSavedState(-1)
{
	ctrlrPanelUndoManager	= new CtrlrPanelUndoManager(*this);
	ctrlrLuaManager 		= new CtrlrLuaManager(*this);

	if ((bool)getCtrlrManagerOwner().getProperty (Ids::ctrlrLuaDisabled) == false)
	{
		ctrlrLuaManager->getMethodManager().setDebug ((bool)owner.getProperty(Ids::ctrlrLuaDebug));
	}

	ctrlrPanelUndoManager->addChangeListener (this);

	getUndoManager()->beginNewTransaction ("Panel::ctor");
	setProperty (Ids::name, panelName);
	panelTree.addChild (ctrlrLuaManager->getLuaManagerTree(), -1, 0);
	panelTree.addChild (panelWindowManager.getManagerTree(), -1, 0);
	panelTree.addChild (resourceManager.getManagerTree(), -1, 0);

	panelTree.addListener (this);

	setProperty (Ids::panelScheme, CTRLR_PANEL_SCHEME);
	setProperty (Ids::panelShowDialogs, true);
	setProperty (Ids::panelMessageTime, 10000);
	setProperty (Ids::panelAuthorName, "");
	setProperty (Ids::panelAuthorEmail, "");
	setProperty (Ids::panelAuthorDonateUrl, "");
	setProperty (Ids::panelAuthorUrl, "");
	setProperty (Ids::panelAuthorDesc, "");
	setProperty (Ids::panelVersionMajor, 1);
	setProperty (Ids::panelVersionMinor, 0);
	setProperty (Ids::panelVersionName, "Hell-O-Kitty");
	setProperty (Ids::panelVendor, "");
	setProperty (Ids::panelDevice, "");
	setProperty (Ids::panelMidiSnapshotAfterLoad, false);
	setProperty (Ids::panelMidiSnapshotAfterProgramChange, false);
	setProperty (Ids::panelMidiSnapshotDelay, 10);
	setProperty (Ids::panelMidiSnapshotShowProgress, false);
	setProperty (Ids::panelMidiInputChannelDevice, 1);
	setProperty (Ids::panelMidiInputDevice, COMBO_NONE_ITEM);
	setProperty (Ids::panelMidiControllerChannelDevice, 1);
	setProperty (Ids::panelMidiControllerDevice, COMBO_NONE_ITEM);
	setProperty (Ids::panelMidiOutputChannelDevice, 1);
	setProperty (Ids::panelMidiOutputDevice, COMBO_NONE_ITEM);

	setProperty (Ids::panelMidiInputFromHost, false);
	setProperty (Ids::panelMidiInputChannelHost, 1);
	setProperty (Ids::panelMidiOutputToHost, false);
	setProperty (Ids::panelMidiOutputChannelHost, 1);

	setProperty (Ids::panelMidiThruH2H, false);
	setProperty (Ids::panelMidiThruH2HChannelize, false);
	setProperty (Ids::panelMidiThruH2D, false);
	setProperty (Ids::panelMidiThruH2DChannelize, false);
	setProperty (Ids::panelMidiThruD2D, false);
	setProperty (Ids::panelMidiThruD2DChannelize, false);
	setProperty (Ids::panelMidiThruD2H, false);
	setProperty (Ids::panelMidiThruD2HChannelize, false);
	setProperty (Ids::panelMidiRealtimeIgnore, true);
	setProperty (Ids::panelMidiInputThreadPriority, 7);
	setProperty (Ids::panelMidiProgram, 0);
	setProperty (Ids::panelMidiBankLsb, 0);
	setProperty (Ids::panelMidiBankMsb, 0);
	setProperty (Ids::panelMidiSendProgramChangeOnLoad, false);
	setProperty (Ids::panelMidiProgramCalloutOnprogramChange, false);
	setProperty (Ids::panelMidiMatchCacheSize, 32);
	setProperty (Ids::panelMidiGlobalDelay, 0);
	setProperty (Ids::panelMidiPauseOut, false);
	setProperty (Ids::panelMidiPauseIn, false);

	setProperty (Ids::panelOSCEnabled, false);
	setProperty (Ids::panelOSCPort, -1);
	setProperty (Ids::panelOSCProtocol, 0);

    setProperty (Ids::luaPanelMidiChannelChanged, COMBO_ITEM_NONE);
	setProperty (Ids::luaPanelMidiReceived, COMBO_ITEM_NONE);
	setProperty (Ids::luaPanelMidiMultiReceived, COMBO_ITEM_NONE);
	setProperty (Ids::luaPanelLoaded, COMBO_ITEM_NONE);
	setProperty (Ids::luaPanelBeforeLoad, COMBO_ITEM_NONE);
	setProperty (Ids::luaPanelSaved, COMBO_ITEM_NONE);
	setProperty (Ids::luaPanelResourcesLoaded, COMBO_ITEM_NONE);
	setProperty (Ids::luaPanelProgramChanged, COMBO_ITEM_NONE);
	setProperty (Ids::luaPanelGlobalChanged, COMBO_ITEM_NONE);
	setProperty (Ids::luaPanelMessageHandler, COMBO_ITEM_NONE);
	setProperty (Ids::luaPanelModulatorValueChanged, COMBO_ITEM_NONE);
	setProperty (Ids::luaPanelSaveState, COMBO_ITEM_NONE);
	setProperty (Ids::luaPanelRestoreState, COMBO_ITEM_NONE);
    setProperty (Ids::luaPanelMidiSnapshotPost, COMBO_ITEM_NONE);
    setProperty (Ids::luaPanelMidiSnapshotPre, COMBO_ITEM_NONE);
    setProperty (Ids::luaAudioProcessBlock, COMBO_ITEM_NONE);
    setProperty (Ids::luaPanelOSCReceived, COMBO_ITEM_NONE);

	setProperty (Ids::panelFilePath, "");
	setProperty (Ids::panelLastSaveDir, "");
	setProperty (Ids::panelUID, generateRandomUnique());
	setProperty (Ids::panelInstanceUID, generateRandomUniquePluginId());
    setProperty (Ids::panelInstanceManufacturerID, generateRandomUniquePluginId());
	setProperty (Ids::panelModulatorListColumns, COMBO_ITEM_NONE);
	setProperty (Ids::panelModulatorListCsvDelimiter, ",");
	setProperty (Ids::panelModulatorListXmlRoot, "ctrlrModulatorList");
	setProperty (Ids::panelModulatorListXmlModulator, "ctrlrModulator");
	setProperty (Ids::panelModulatorListSortOption, true);
	setProperty (Ids::panelGlobalVariables, "-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1:-1");
	setProperty (Ids::panelResources, COMBO_ITEM_NONE);
	setProperty (Ids::panelPropertyDisplayIDs, false);

	setProperty (Ids::ctrlrMenuItemBackgroundColour, 		Colours::white.toString());
	setProperty (Ids::ctrlrMenuItemTextColour, 				Colours::black.toString());
	setProperty (Ids::ctrlrMenuItemHighlightedTextColour, 	Colours::white.toString());
	setProperty (Ids::ctrlrMenuItemHighlightColour, 		Colour(HIGHLIGHT_COLOUR).toString());
	setProperty (Ids::ctrlrMenuItemFont, 					owner.getFontManager().getStringFromFont (Font (18.0f)));
	setProperty (Ids::ctrlrMenuItemSeparatorColour,			Colour (0x44000000).toString());
	setProperty (Ids::ctrlrMenuItemHeaderColour,			Colours::black.toString());

	setProperty (Ids::ctrlrMenuBarBackgroundColour1, 		Colour(0xfff7f7f7).toString());
	setProperty (Ids::ctrlrMenuBarBackgroundColour2, 		Colour(0xffcccccc).toString());
	setProperty (Ids::ctrlrMenuBarTextColour, 				Colours::black.toString());
	setProperty (Ids::ctrlrMenuBarHighlightedTextColour, 	Colours::white.toString());
	setProperty (Ids::ctrlrMenuBarHighlightColour, 			Colour(HIGHLIGHT_COLOUR).toString());
	setProperty (Ids::ctrlrMenuBarFont, 					owner.getFontManager().getStringFromFont (Font (18.0f)));
	setProperty (Ids::ctrlrUseEditorWrapper, false);

	owner.addChangeListener (this);
	midiMessageCollector.reset (SAMPLERATE);

	midiInputThread.startThread(5);
	midiControllerInputThread.startThread(5);
}

CtrlrPanel::~CtrlrPanel()
{
	midiInputThread.signalThreadShouldExit();
	midiInputThread.waitForThreadToExit (1200);
	midiControllerInputThread.signalThreadShouldExit();
	midiControllerInputThread.waitForThreadToExit (1200);

	masterReference.clear();

	panelTree.removeListener (this);

	if (ctrlrLuaManager)
		deleteAndZero (ctrlrLuaManager);

	owner.removeChangeListener(this);

	ctrlrModulators.clear();

	owner.getManagerTree().removeChild (panelTree, 0);
}

void CtrlrPanel::setRestoreState(const bool _restoreStateStatus)
{
	const ScopedWriteLock lock (panelLock);

	getUndoManager()->clearUndoHistory();
	restoreStateStatus = _restoreStateStatus;
}

void CtrlrPanel::setProgramState(const bool _programState)
{
	const ScopedWriteLock lock (panelLock);

	programState = _programState;
}

Result CtrlrPanel::restoreState (const ValueTree &savedState)
{
    _TXT("enter");

	setRestoreState (true);

	panelTree.removeProperty (Ids::panelScheme, nullptr);

	// We need panel file property to be able to restore relative paths on lua methods
	var filePath = savedState.getProperty(Ids::panelFilePath);
	if (filePath.isVoid())
	{	// File path not provided (new Panel) => get a default one
		File userDocsDir = File::getSpecialLocation(File::SpecialLocationType::userDocumentsDirectory);
		File panelFile = userDocsDir.getNonexistentChildFile("CtrlrPanel", ".panel");
		filePath = panelFile.getFullPathName();
	}
	panelTree.setProperty(Ids::panelFilePath, filePath, nullptr);

	ctrlrLuaManager->restoreState(savedState.getChildWithName(Ids::luaManager));

	if ((int)savedState.getProperty(Ids::panelScheme) < CTRLR_PANEL_SCHEME)
		upgradeScheme();

	for (int i=0; i<savedState.getNumProperties(); i++)
	{
		panelTree.setProperty (savedState.getPropertyName(i), savedState.getProperty(savedState.getPropertyName(i), 0), 0);
	}

	if (savedState.getChildWithName(Ids::resourceExportList).isValid())
	{
		Result resourceImport = resourceManager.restoreState(savedState.getChildWithName(Ids::resourceExportList));

		if (!resourceImport.wasOk())
		{
			WARN("Failed to load panel: " + resourceImport.getErrorMessage());

			setRestoreState (false);
			return (resourceImport);
		}
	}
	else if (owner.getInstanceResourcesTree().isValid())
	{
		Result resourceImport = getResourceManager().restoreState(owner.getInstanceResourcesTree());

		if (!resourceImport.wasOk())
		{
			WARN("Failed to load panel: " + resourceImport.getErrorMessage());

			setRestoreState (false);
			return (resourceImport);
		}
	}
	else
	{	// Try and load missing resources from source files
		ValueTree panelResourcesTree = savedState.getChildWithName(Ids::panelResources);
		if(panelResourcesTree.isValid())
		{
			getResourceManager().checkMissingResources(panelResourcesTree);
		}

	}

	if (luaPanelBeforeLoadCbk && !luaPanelBeforeLoadCbk.wasObjectDeleted())
	{
		if (luaPanelBeforeLoadCbk->isValid())
		{
			getCtrlrLuaManager().getMethodManager().call (luaPanelBeforeLoadCbk);
		}
	}
	if (savedState.getChildWithName(Ids::panelResources).isValid())
	{
		getResourceManager().restoreSavedState(savedState.getChildWithName(Ids::panelResources));
	}

	resourceImportFinished();

	// No modifications at this point
	setSavePoint();

	if (savedState.getChildWithName(Ids::uiPanelEditor).isValid())
	{
		getEditor(true)->restoreState(savedState);
	}
	if (savedState.getChildWithName(Ids::uiWindowManager).isValid())
	{
		panelWindowManager.restoreState (savedState.getChildWithName(Ids::uiWindowManager));
	}
	if (savedState.getChildWithName(Ids::panelCustomData).isValid())
	{
		setCustomData (savedState.getChildWithName(Ids::panelCustomData));
	}

	setRestoreState (false);

	if (owner.getInstanceMode() == InstanceMulti)
	{
		bootstrapPanel();
	}
	return Result::ok();
}

void CtrlrPanel::sendSnapshotOnLoad()
{
	if ((bool)getProperty (Ids::panelMidiSnapshotAfterLoad) == true)
	{
	    _INF("Snapshot on load selected, sending now");
		snapshot.sendSnapshot();
	}
}

void CtrlrPanel::bootstrapPanel(const bool setInitialProgram)
{
    _TXT("enter");
	if (getRestoreState())
		return;

	boostrapStateStatus = true;

	for (int i=0; i<ctrlrModulators.size(); i++)
	{
		ctrlrModulators[i]->allModulatorsInitialized();
	}

	if (setInitialProgram)
		setProgram (initialProgram);

	if (luaPanelLoadedCbk.get())
	{
		if (luaPanelLoadedCbk->isValid())
		{
			getCtrlrLuaManager().getMethodManager().call (luaPanelLoadedCbk, (uint8)owner.getInstanceMode());
		}
	}

	if ((bool)getProperty (Ids::panelMidiSendProgramChangeOnLoad) == true)
	{
		sendMidiProgramChange();
	}

	editModeChanged(getProperty(Ids::uiPanelEditMode));

	sendSnapshotOnLoad();

	// Synchronously dispatch any pending change message in each modulator to prevent Lua Callback functions beeing called on startup
	for (int i = 0; i<ctrlrModulators.size(); i++)
	{
		ctrlrModulators[i]->getProcessor().handleUpdateNowIfNeeded();
	}

	boostrapStateStatus = false;
}

CtrlrPanelEditor *CtrlrPanel::getEditor(const bool createNewEditorIfNeeded)
{
	if (ctrlrPanelEditor.get() == nullptr)
	{
		if (createNewEditorIfNeeded)
		{
			ctrlrPanelEditor = new CtrlrPanelEditor(*this, owner, getPanelWindowTitle());
			getPanelTree().addChild (ctrlrPanelEditor->getPanelEditorTree(), -1, nullptr);
		}
	}
	return (ctrlrPanelEditor);
}

void CtrlrPanel::setProperty (const Identifier& name, const var &newValue, const bool isUndoable)
{
    if (isUndoable)
	{
		panelTree.setProperty (name, newValue, getPanelUndoManager());
	}
	else
	{
		panelTree.setProperty (name, newValue, nullptr);
	}
}

void CtrlrPanel::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (treeWhosePropertyHasChanged.hasType(Ids::modulator))
	{
		return;
	}
	else if (property == Ids::panelMidiInputDevice)
	{
		if (getProperty(property).toString() == "" || getProperty(property).toString() == COMBO_ITEM_NONE)
		{
			midiInputThread.closeInputDevice();
		}
		else
		{
			const bool result = midiInputThread.openInputDevice (getProperty(property));
			if (getEditor())
			{
				notify ( STR(result ? "Open OK: [" : "Open FAILED: [") + getProperty(property).toString() + "]", nullptr, result ? NotifySuccess : NotifyFailure);
			}
		}
	}
	else if (property == Ids::panelMidiOutputDevice)
	{
		if (getProperty(property).toString() == "" || getProperty(property).toString() == COMBO_ITEM_NONE)
		{
			if (outputDevicePtr)
				outputDevicePtr->closeDevice();
		}
		else
		{
			outputDevicePtr = owner.getCtrlrMidiDeviceManager().getDeviceByName(getProperty(property).toString(), outputDevice, true);

			if (getEditor())
			{
				notify ( STR(outputDevicePtr ? "Open OK: [" : "Open FAILED: [") + getProperty(property).toString() + "]", nullptr, outputDevicePtr ? NotifySuccess : NotifyFailure);
			}
		}
	}
	else if (property == Ids::panelMidiControllerDevice)
	{
		if (getProperty(property).toString() == "" || getProperty(property).toString() == COMBO_ITEM_NONE)
		{
			midiControllerInputThread.closeInputDevice();
		}
		else
		{
			midiControllerInputThread.openInputDevice (getProperty(property));
		}
	}
	else if (	property == Ids::panelMidiInputChannelDevice
			|| property == Ids::panelMidiOutputChannelDevice
			|| property == Ids::panelMidiInputChannelHost
			|| property == Ids::panelMidiOutputChannelHost
			|| property == Ids::panelMidiControllerChannelDevice
	)
	{
		setMidiChannel (midiChannelFromString(property), (uint8) (int)getProperty(property));
	}
	else if (property == Ids::panelMidiInputFromHost
			|| property == Ids::panelMidiInputFromHostCompare
			|| property == Ids::panelMidiOutputToHost
			|| property == Ids::panelMidiThruH2H
			|| property == Ids::panelMidiThruH2HChannelize
			|| property == Ids::panelMidiThruH2D
			|| property == Ids::panelMidiThruH2DChannelize
			|| property == Ids::panelMidiThruD2D
			|| property == Ids::panelMidiThruD2DChannelize
			|| property == Ids::panelMidiThruD2H
			|| property == Ids::panelMidiThruD2HChannelize
			|| property == Ids::panelMidiRealtimeIgnore
		)
	{
		setMidiOptionBool (midiOptionFromString(property), getProperty(property));
	}
	else if (property == Ids::name)
	{
		if (ctrlrPanelEditor)
		{
			ctrlrPanelEditor->setProperty (Ids::name, getProperty(Ids::name));
		}
	}
	else if (property == Ids::luaPanelMidiReceived)
	{
		if (getProperty(property) == "")
			return;

		luaPanelMidiReceivedCbk = getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaPanelMidiMultiReceived)
	{
		if (getProperty(property) == "")
			return;

		luaPanelMidiMultiReceivedCbk = getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaPanelMidiChannelChanged)
	{
		if (getProperty(property) == "")
			return;

		luaPanelMidiChannelChangedCbk = getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaPanelMessageHandler)
	{
		if (getProperty(property) == "")
			return;

		luaPanelMessageHandlerCbk = getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaPanelSaved)
	{
		if (getProperty(property) == "")
			return;

		luaPanelSavedCbk = getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaPanelLoaded)
	{
		if (getProperty(property) == "")
			return;

		luaPanelLoadedCbk = getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaPanelGlobalChanged)
	{
		if (getProperty(property) == "")
			return;

		luaPanelGlobalChangedCbk = getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaPanelBeforeLoad)
	{
		if (getProperty(property) == "")
			return;

		luaPanelBeforeLoadCbk = getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaPanelProgramChanged)
	{
		if (getProperty(property) == "")
			return;

		luaPanelProgramChangedCbk = getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaPanelResourcesLoaded)
	{
		if (getProperty(property) == "")
			return;

		luaPanelResourcesLoadedCbk = getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaPanelModulatorValueChanged)
	{
		if (getProperty(property) == "")
			return;

		luaPanelModulatorValueChangedCbk = getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaPanelSaveState)
	{
		if (getProperty(property) == "")
			return;

		luaPanelSaveStateCbk = getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaPanelRestoreState)
	{
		if (getProperty(property) == "")
			return;

		luaPanelRestoreStateCbk = getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaPanelMidiSnapshotPost)
	{
		if (getProperty(property) == "")
			return;

        snapshot.setPostLuaCallback (getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property)));
	}
	else if (property == Ids::luaPanelMidiSnapshotPre)
	{
		if (getProperty(property) == "")
			return;

		snapshot.setPreLuaCallback (getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property)));
	}
	else if (property == Ids::panelGlobalVariables)
	{
		globalVariables = globalsFromString (getProperty(property));
	}
	else if (property == Ids::panelResources)
	{
		panelResources = globalsFromString (getProperty(property));
	}
	else if (property == Ids::panelMidiSnapshotDelay)
	{
		snapshot.setDelay(getProperty(property));
	}
	else if (property == Ids::panelMidiProgram || property == Ids::panelMidiBankLsb || property == Ids::panelMidiBankMsb)
	{
		sendMidiProgramChange();
	}
	else if (property == Ids::panelUID)
	{
		resourceManager.panelUIDChanged();
	}
	else if (property == Ids::panelMidiGlobalDelay)
	{
		globalMidiDelay = getProperty(property);
	}
}

void CtrlrPanel::removeModulator (CtrlrModulator *modulatorToDelete)
{
	if (ctrlrModulators.contains(modulatorToDelete))
	{
		owner.removeModulator (modulatorToDelete);
		radioGrouppedComponent.removeAllInstancesOf (modulatorToDelete->getComponent());

		listeners.call (&CtrlrPanel::Listener::modulatorRemoved, modulatorToDelete);

		ctrlrModulators.removeObject (modulatorToDelete);
		panelTree.removeChild (modulatorToDelete->getModulatorTree(), 0);
	}
}

void CtrlrPanel::addModulator (CtrlrModulator *modulatorToAdd)
{
	/* add it to the panels array */
	ctrlrModulators.add (modulatorToAdd);

	/* add it to the hash table, that uses the names to access the pointers,
		it should be faster then normal linear access */
    hashName (modulatorToAdd);

	/* add it to the Manager array, this is needed for the VST manager to work */
	owner.addModulator	(modulatorToAdd);

	/* add the modulator tree to our tree */
	panelTree.addChild	(modulatorToAdd->getModulatorTree(), -1, nullptr);

	/* call listeners to tell them */
	listeners.call (&CtrlrPanel::Listener::modulatorAdded, modulatorToAdd);
}

CtrlrModulator *CtrlrPanel::createNewModulator(const Identifier &guiType)
{
	CtrlrModulator *newModulator = nullptr;

	if (CtrlrComponentTypeManager::isStatic(guiType))
	{
		newModulator = new CtrlrModulator (*this);
	}
	else
	{
		newModulator = new CtrlrModulator (*this, owner.getNextVstIndex());
	}

	newModulator->setProperty (Ids::name, getUniqueModulatorName("modulator-1"));
	addModulator (newModulator);

	return (newModulator);
}

bool CtrlrPanel::containsCtrlrComponent(const CtrlrComponent *const componentToLookFor) const
{
	if (componentToLookFor == 0)
		return (false);

	return (ctrlrModulators.contains(&componentToLookFor->getOwner()));
}

const Array <CtrlrModulator*> CtrlrPanel::getModulatorsByMidiType(const CtrlrMidiMessageType typeToFilter)
{
	Array <CtrlrModulator *>ret;
	for (int i=0; i<ctrlrModulators.size(); i++)
	{
		if (ctrlrModulators[i]->getMidiMessagePtr())
		{
			if (ctrlrModulators[i]->getMidiMessage().getMidiMessageType() == typeToFilter)
			{
				ret.add (ctrlrModulators[i]);
			}
		}
	}

	return (ret);
}

const Array <CtrlrModulator*> CtrlrPanel::getModulatorsByUIType(const Identifier &typeToFilter)
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

const Array <CtrlrModulator*> CtrlrPanel::getModulatorsWithProperty(const Identifier &propertyName, const var &propertyValue)
{
	Array <CtrlrModulator *>ret;

	for (int i=0; i<ctrlrModulators.size(); i++)
	{
		if (ctrlrModulators[i]->getProperty(propertyName) == propertyValue)
		{
			ret.addIfNotAlreadyThere(ctrlrModulators[i]);
		}

		if (ctrlrModulators[i]->getComponent())
		{
			if (ctrlrModulators[i]->getComponent()->getProperty(propertyName) == propertyValue)
			{
				ret.addIfNotAlreadyThere(ctrlrModulators[i]);
			}
		}
	}

	return (ret);
}

const String CtrlrPanel::getUniqueModulatorName(const String &proposedName)
{
	if (getRestoreState())
		return (proposedName);

	uint32 marker=0;
	String basename="";
	String nameToLookFor;

	if (proposedName.fromLastOccurrenceOf("-", false, true) != "")
	{
		basename		= proposedName.upToLastOccurrenceOf("-", false, true);
		marker			= proposedName.fromLastOccurrenceOf("-", false, true).getIntValue();
		nameToLookFor	= proposedName;
	}
	else
	{
		basename		= proposedName;
		marker			= ctrlrModulators.size();
		nameToLookFor	= basename + "-" + String(marker);
	}

	while (getModulator(nameToLookFor))
	{
		nameToLookFor = basename + "-" + String(++marker);
	}

	return (nameToLookFor);
}

void CtrlrPanel::changeListenerCallback (ChangeBroadcaster* source)
{
	if (source == ctrlrPanelUndoManager)
	{
		Array <const UndoableAction *>actions;
		ctrlrPanelUndoManager->getActionsInCurrentTransaction (actions);
	}
	else
	{
		if (ctrlrPanelEditor)
		{
			ctrlrPanelEditor->getPropertiesPanel()->refreshAll();
			if (ctrlrPanelEditor->getSelection())
            {
                ctrlrPanelEditor->getSelection()->sendChangeMessage();
            }
		}
	}
}

void CtrlrPanel::setMidiChannelToAllModulators (const int newChannel)
{
	for (int i=0; i<ctrlrModulators.size(); i++)
	{
		if (ctrlrModulators[i]->getMidiMessagePtr())
		{
			ctrlrModulators[i]->getMidiMessage().setChannel (newChannel);
		}
	}
}

void CtrlrPanel::setInitialProgramValue (const String &modulatorName, const var &value)
{
	ValueTree v(Ids::value);
	v.setProperty(Ids::name, modulatorName, 0);
	v.setProperty(Ids::value, value, 0);
	initialProgram.addChild (v, -1, nullptr);
}

ValueTree CtrlrPanel::getProgram(ValueTree treeToWriteTo)
{
	if (treeToWriteTo.isValid())
	{
		treeToWriteTo.removeAllChildren(0);
	}

	ValueTree program(Ids::panelState);
	program.setProperty (Ids::panelVersionMajor, getProperty(Ids::panelVersionMajor), 0);
	program.setProperty (Ids::panelVersionMinor, getProperty(Ids::panelVersionMinor), 0);
	program.setProperty (Ids::time, Time::getCurrentTime().currentTimeMillis(), 0);

	for (int i=0; i<ctrlrModulators.size(); i++)
	{
		CtrlrModulator *m = ctrlrModulators[i];

		ValueTree v(Ids::value);

		if ((bool)m->getProperty (Ids::modulatorIsStatic) == true)
			continue;

		v.setProperty(Ids::name, m->getName(),0);
		v.setProperty(Ids::value, m->getModulatorValue(),0);

		if (treeToWriteTo.isValid())
		{
			treeToWriteTo.addChild (v,-1,0);
		}
		else
		{
			program.addChild (v,-1,0);
		}
	}

	return (program);
}

ValueTree CtrlrPanel::getCustomData()
{
	ValueTree customData (Ids::panelCustomData);

	if (luaPanelSaveStateCbk && !luaPanelSaveStateCbk.wasObjectDeleted())
	{
		if (luaPanelSaveStateCbk->isValid())
		{
			getCtrlrLuaManager().getMethodManager().call (luaPanelSaveStateCbk, customData);
		}
	}

	return (customData);
}

void CtrlrPanel::generateCustomData()
{
	if (panelTree.getChildWithName (Ids::panelCustomData).isValid())
	{
		panelTree.removeChild (panelTree.getChildWithName(Ids::panelCustomData), nullptr);
	}

	panelTree.addChild (getCustomData(), -1, nullptr);
}

void CtrlrPanel::setCustomData (const ValueTree &customData)
{
	if (luaPanelRestoreStateCbk && !luaPanelRestoreStateCbk.wasObjectDeleted())
	{
		if (luaPanelRestoreStateCbk->isValid())
		{
			getCtrlrLuaManager().getMethodManager().call (luaPanelRestoreStateCbk, customData);
		}
	}
}

void CtrlrPanel::setProgram(ValueTree programTree, const bool sendSnapshotNow)
{
	_DBG("CtrlrPanel::setProgram");

	ValueTree program;

	if (programTree.hasType(Ids::panelState))
	{
		program = programTree;
	}
	else
	{
		if (programTree.getChildWithName(Ids::panelState).isValid())
		{
			program = programTree.getChildWithName(Ids::panelState);
		}
	}

	setProgramState (true);

	if (program.isValid())
	{
		for (int i=0; i<program.getNumChildren(); i++)
		{
			if (program.getChild(i).hasType(Ids::value))
			{
				CtrlrModulator *m = getModulator (program.getChild(i).getProperty(Ids::name));
				if (m)
				{
					m->setRestoreState (true);
					m->getProcessor().setValueGeneric (CtrlrModulatorValue(program.getChild(i).getProperty(Ids::value), CtrlrModulatorValue::changedByProgram), true);
					if (m->getComponent())
					{
						m->getComponent()->setComponentValue (program.getChild(i).getProperty(Ids::value), false);
					}
					m->getProcessor().handleUpdateNowIfNeeded();
					m->setRestoreState (false);
				}
			}

			if (program.getChild(i).hasType(Ids::panelCustomData))
            {
                setCustomData(program.getChild(i));
            }
		}

		if ((bool)getProperty (Ids::panelMidiSnapshotAfterProgramChange) == true)
		{
			snapshot.sendSnapshot();
		}

		if (luaPanelProgramChangedCbk && !luaPanelProgramChangedCbk.wasObjectDeleted())
		{
			if (luaPanelProgramChangedCbk->isValid())
			{
				getCtrlrLuaManager().getMethodManager().call (luaPanelProgramChangedCbk);
			}
		}
	}

	setProgramState (false);

	if (sendSnapshotNow)
	{
		sendSnapshot();
	}
}

int CtrlrPanel::getCurrentProgramNumber()
{
	return (3);
}

int CtrlrPanel::getCurrentBankNumber()
{
	return (4);
}

int CtrlrPanel::getPanelIndex()
{
	return (getProperty(Ids::panelIndex));
}

bool CtrlrPanel::getEditMode()
{
	return editMode;
}

void CtrlrPanel::editModeChanged(const bool isInEditMode)
{
	midiInputThread.panelEditModeChanged (isInEditMode);
    midiControllerInputThread.panelEditModeChanged (isInEditMode);
	editMode = isInEditMode;
	for (int i=0; i<ctrlrModulators.size(); i++)
	{
		if (ctrlrModulators[i]->getComponent())
		{
			ctrlrModulators[i]->getComponent()->panelEditModeChanged(isInEditMode);
		}
	}
}

const String CtrlrPanel::getVersionString(const bool includeVersionName, const bool includeTime, const String versionSeparator)
{
	String r;
	String sep;

	if (versionSeparator == "")
		sep = owner.getProperty(Ids::ctrlrVersionSeparator).toString();
	else
		sep = versionSeparator;

	int versionMajor = getProperty(Ids::panelVersionMajor);
	int versionMinor = getProperty(Ids::panelVersionMinor);

	r << versionMajor << sep << versionMinor;

	if (includeVersionName && getProperty (Ids::panelVersionName).toString() != "")
	{
		r << sep + getProperty (Ids::panelVersionName).toString();
	}

	if (includeTime)
	{
		Time t = Time::getCurrentTime();

		r << sep + t.formatted("%Y-%m-%d_%H-%M");
	}

	return (r);
}

int CtrlrPanel::cleanBogusProperties()
{
	return (cleanBogusPropertiesFromChild (panelTree));
}

int CtrlrPanel::cleanBogusPropertiesFromChild(ValueTree &treeToClean)
{
	int removedProperties = 0;

	for (int j=0; j<treeToClean.getNumProperties(); j++)
	{
		/*if (Ids::ctrlrIdContainer->getVid (treeToClean.getPropertyName(j)) < 0)
		{
			removedProperties++;
			treeToClean.removeProperty(treeToClean.getPropertyName(j), 0);
		}
		*/
	}

	if (treeToClean.getNumChildren() > 0)
	{
		for (int i=0; i<treeToClean.getNumChildren(); i++)
		{
			ValueTree child = treeToClean.getChild(i);
			const int r = cleanBogusPropertiesFromChild (child);
			removedProperties = removedProperties + r;
		}
	}

	return (removedProperties);
}

void CtrlrPanel::sync()
{
}

/** @brief Get the canvas for this panel

*/
CtrlrPanelCanvas *CtrlrPanel::getCanvas()
{
	if (getEditor())
	{
		return (getEditor()->getCanvas());
	}

	return (0);
}

CtrlrPanelWindowManager &CtrlrPanel::getWindowManager()
{
	return (panelWindowManager);
}

void CtrlrPanel::panelReceivedMidi(const MidiBuffer &buffer, const CtrlrMIDIDeviceType source)
{
	MidiBuffer::Iterator i(buffer);
	MidiMessage m;
	int time;

	while (i.getNextEvent(m,time))
	{
		midiMessageCollector.addMessageToQueue (m);
	}

	triggerAsyncUpdate();
}

void CtrlrPanel::handleAsyncUpdate()
{
	/* let's check any pending multi midi messages
	   in the queue */
	for (int i=0; i<multiMidiQueue.size(); i++)
	{
		if (luaPanelMidiMultiReceivedCbk)
			getCtrlrLuaManager().getMethodManager().call (luaPanelMidiMultiReceivedCbk, multiMidiQueue[i]);

		multiMidiQueue.remove(i);
	}

	MidiBuffer buffer;

	midiMessageCollector.removeNextBlockOfMessages (buffer, SAMPLERATE * 512);

	/* We mute here, so we don't have to lock the value tree in the MIDI thread
		we need to empty the queue so it doesn't grow */
	if (isMidiInPaused())
	{
		return;
	}

	MidiBuffer::Iterator i(buffer);
	int time;
	MidiMessage m;
	bool luaValid = false;

	if (luaPanelMidiReceivedCbk)
		luaValid  = luaPanelMidiReceivedCbk->isValid();

	while (i.getNextEvent(m,time))
	{
		if (luaValid)
			getCtrlrLuaManager().getMethodManager().call (luaPanelMidiReceivedCbk, CtrlrMidiMessage (m));

		listeners.call (&CtrlrPanel::Listener::midiReceived, m, inputDevice);
	}
}

bool CtrlrPanel::getMidiOptionBool(const CtrlrPanelMidiOption optionToCheck)
{
	const uint32 opt = midiOptions.get();

	return ((opt & optionToCheck) != 0);
}

void CtrlrPanel::setMidiOptionBool(const CtrlrPanelMidiOption optionToSet, const bool isSet)
{
	if (isSet)
	{
		uint32 opt = midiOptions.get();
		opt |= optionToSet;
		midiOptions.set (opt);
	}
	else
	{
		uint32 opt = midiOptions.get();
		opt &= ~optionToSet;
		midiOptions.set (opt);
	}
	BigInteger bi(midiOptions.get());

	processor.midiOptionChanged(optionToSet);
	midiInputThread.midiOptionChanged(optionToSet);
	midiControllerInputThread.midiOptionChanged(optionToSet);
}

uint8 CtrlrPanel::getMidiChannel(const CtrlrPanelMidiChannel channelToGet)
{
	switch (channelToGet)
	{
		case panelMidiInputChannelDevice:
			return (deviceInputChannel.get());

		case panelMidiOutputChannelDevice:
			return (deviceOutputChannel.get());

		case panelMidiInputChannelHost:
			return (hostInputChannel.get());

		case panelMidiOutputChannelHost:
			return (hostOutputChannel.get());

		case panelMidiControllerChannel:
			return (controllerInputChannel.get());
	}
	return (0);
}

void CtrlrPanel::setMidiChannel(const CtrlrPanelMidiChannel optionToSet, const uint8 value)
{
	switch (optionToSet)
	{
		case panelMidiInputChannelDevice:
			deviceInputChannel.set(value);
			break;

		case panelMidiOutputChannelDevice:
			deviceOutputChannel.set(value);
			setMidiChannelToAllModulators(jlimit<uint8>(1,16,value));
			break;

		case panelMidiInputChannelHost:
			hostInputChannel.set(value);
			break;

		case panelMidiOutputChannelHost:
			hostOutputChannel.set(value);
			break;

		case panelMidiControllerChannel:
			controllerInputChannel.set(value);
			break;
	}

	processor.midiChannelChaned(optionToSet);
	midiInputThread.midiChannelChaned(optionToSet);
	midiControllerInputThread.midiChannelChaned(optionToSet);

	if (luaPanelMidiChannelChangedCbk && !luaPanelMidiChannelChangedCbk.wasObjectDeleted())
	{
		if (luaPanelMidiChannelChangedCbk->isValid())
		{
			getCtrlrLuaManager().getMethodManager().call (luaPanelMidiChannelChangedCbk, (int)optionToSet, (int)value);
		}
    }
}

CtrlrPanelMidiChannel CtrlrPanel::midiChannelFromString(const Identifier &i)
{
	if (Ids::panelMidiInputChannelDevice == i)
	{
		return (panelMidiInputChannelDevice);
	}
	else if (Ids::panelMidiOutputChannelDevice == i)
	{
		return (panelMidiOutputChannelDevice);
	}
	else if (Ids::panelMidiInputChannelHost == i)
	{
		return (panelMidiInputChannelHost);
	}
	else if (Ids::panelMidiOutputChannelHost == i)
	{
		return (panelMidiOutputChannelHost);
	}
	else if (Ids::panelMidiControllerChannelDevice == i)
	{
		return (panelMidiControllerChannel);
	}
	return (panelMidiInputChannelDevice);
}

CtrlrPanelMidiOption CtrlrPanel::midiOptionFromString(const Identifier &i)
{
	if (Ids::panelMidiInputFromHost == i)
	{
		return (panelMidiInputFromHost);
	}
	else if (Ids::panelMidiInputFromHostCompare == i)
	{
		return (panelMidiInputFromHostCompare);
	}
	else if (Ids::panelMidiOutputToHost == i)
	{
		return (panelMidiOutputToHost);
	}
	else if (Ids::panelMidiThruH2H == i)
	{
		return (panelMidiThruH2H);
	}
	else if (Ids::panelMidiThruH2HChannelize == i)
	{
		return (panelMidiThruH2HChannelize);
	}
	else if (Ids::panelMidiThruH2D == i)
	{
		return (panelMidiThruH2D);
	}
	else if (Ids::panelMidiThruH2DChannelize == i)
	{
		return (panelMidiThruH2DChannelize);
	}
	else if (Ids::panelMidiThruD2D == i)
	{
		return (panelMidiThruD2D);
	}
	else if (Ids::panelMidiThruD2DChannelize == i)
	{
		return (panelMidiThruD2DChannelize);
	}
	else if (Ids::panelMidiThruD2H == i)
	{
		return (panelMidiThruD2H);
	}
	else if (Ids::panelMidiThruD2HChannelize == i)
	{
		return (panelMidiThruD2HChannelize);
	}
	else if (Ids::panelMidiRealtimeIgnore == i)
	{
		return (panelMidiRealtimeIgnore);
	}
	return (panelMidiInputFromHost);
}

void CtrlrPanel::modulatorValueChanged(CtrlrModulator *m)
{
	if (m->getComponent())
	{
		m->getComponent()->setComponentValue(m->getProperty(Ids::modulatorValue), false);
	}

	if (luaPanelModulatorValueChangedCbk && !luaPanelModulatorValueChangedCbk.wasObjectDeleted())
	{
		if (luaPanelModulatorValueChangedCbk->isValid())
		{
			getCtrlrLuaManager().getMethodManager().call (luaPanelModulatorValueChangedCbk, m, m->getValueNonMapped());
		}
	}

	listeners.call (&CtrlrPanel::Listener::modulatorChanged, m);
}

/** Radio group stuff

*/
void CtrlrPanel::setRadioGroupId(CtrlrComponent *componentMember, const int groupId)
{
	if (groupId == 0)
	{
		radioGrouppedComponent.removeAllInstancesOf (componentMember);
	}
	else
	{
		radioGrouppedComponent.addIfNotAlreadyThere (componentMember);
	}
}

bool CtrlrPanel::componentIsInRadioGroup(CtrlrComponent *component)
{
	return (radioGrouppedComponent.contains (component));
}

bool CtrlrPanel::checkRadioGroup(CtrlrComponent *c, const bool componentToggleState)
{
	if (c->isToggleButton())
	{
		const int groupId = c->getProperty (Ids::componentRadioGroupId);
		if (groupId > 0)
		{
			Array <ComponentReference> componentsToRemove;

			for (int i=0; i<radioGrouppedComponent.size(); i++)
			{
				if (radioGrouppedComponent[i].wasObjectDeleted())
				{
					componentsToRemove.addIfNotAlreadyThere (radioGrouppedComponent[i]);
				}
				else
				{
					if (
							(int)radioGrouppedComponent[i]->getProperty(Ids::componentRadioGroupId) == groupId
							&& radioGrouppedComponent[i]->getToggleState() == componentToggleState
							&& radioGrouppedComponent[i].get() != c
							&& componentToggleState == true
						)
					{
						/* need to change that state, only one in the group can have this state */
						radioGrouppedComponent[i]->setToggleState(false, false);
						radioGrouppedComponent[i]->getOwner().setProperty (Ids::modulatorValue, false);
					}
					else if (
								componentToggleState == false
								&& radioGrouppedComponent[i].get() == c
							)
					{
						c->setToggleState (true, false);
					}
				}
			}
		}
	}

	return (true);
}

void CtrlrPanel::sendSnapshot()
{
	snapshot.sendSnapshot();
}

bool CtrlrPanel::getRestoreState()
{
	const ScopedReadLock lock (panelLock);
	return (restoreStateStatus);
}

bool CtrlrPanel::getProgramState()
{
	const ScopedReadLock lock (panelLock);
	return (programState);
}

bool CtrlrPanel::getBootstrapState()
{
	const ScopedReadLock lock (panelLock);
	return (boostrapStateStatus);
}

/** MIDI Stuff */

void CtrlrPanel::queueMessageForHostOutput(const CtrlrMidiMessage &m)
{
	if (isMidiInPaused())
		return;

	if (getMidiOptionBool (panelMidiOutputToHost))
	{
		owner.getProcessorOwner()->addMidiToOutputQueue (m);
	}
}

void CtrlrPanel::queueMessageForHostOutput(const MidiMessage &m)
{
	if (isMidiInPaused())
		return;

	if (getMidiOptionBool (panelMidiOutputToHost))
	{
		owner.getProcessorOwner()->addMidiToOutputQueue (m);
	}
}

void CtrlrPanel::queueMessagesForHostOutput(const MidiBuffer &messages)
{
	if (isMidiInPaused())
		return;

	if (getMidiOptionBool (panelMidiOutputToHost))
	{
		owner.getProcessorOwner()->addMidiToOutputQueue (messages);
	}
}

void CtrlrPanel::sendMidi (const MidiBuffer &messages, double millisecondCounterToStartAt)
{
	if (isMidiOutPaused())
		return;

	if (outputDevicePtr)
	{
		outputDevicePtr->sendMidiBuffer (messages, globalMidiDelay + millisecondCounterToStartAt);
	}

	queueMessagesForHostOutput (messages);
}

void CtrlrPanel::sendMidi (const MidiMessage &message, double millisecondCounterToStartAt)
{
	if (isMidiOutPaused())
		return;

	if (outputDevicePtr)
	{
		outputDevicePtr->sendMidiMessage (message, globalMidiDelay + millisecondCounterToStartAt);
	}

	if (millisecondCounterToStartAt >= 0)
		queueMessageForHostOutput (MidiMessage (message, millisecondCounterToStartAt));
	else
		queueMessageForHostOutput (message);
}

void CtrlrPanel::sendMidi (CtrlrMidiMessage &m, double millisecondCounterToStartAt)
{
	if (isMidiOutPaused())
		return;

	if (outputDevicePtr)
	{
		outputDevicePtr->sendMidiBuffer (m.getMidiBuffer(), globalMidiDelay + millisecondCounterToStartAt);
	}

	queueMessageForHostOutput (m);
}

bool CtrlrPanel::isMidiOutPaused()
{
	return (getProperty (Ids::panelMidiPauseOut));
}

bool CtrlrPanel::isMidiInPaused()
{
	return (getProperty (Ids::panelMidiPauseIn));
}

void CtrlrPanel::luaSavePanel(const CtrlrPanelFileType fileType, const File &file)
{
	if (luaPanelSavedCbk && !luaPanelSavedCbk.wasObjectDeleted())
	{
		if (luaPanelSavedCbk->isValid())
		{
			getCtrlrLuaManager().getMethodManager().call (luaPanelSavedCbk, (int)fileType, file);
		}
	}

	for (int i=0; i<ctrlrModulators.size(); i++)
	{
		ctrlrModulators[i]->getProcessor().handleUpdateNowIfNeeded();
	}
}

void CtrlrPanel::setLuaDebug (const bool _debug)
{
	if (ctrlrLuaManager)
	{
		ctrlrLuaManager->getMethodManager().setDebug (_debug);
	}
}

void CtrlrPanel::sendMidiProgramChange()
{
	if (getRestoreState())
		return;

	const int midiCh	= (int)getProperty(Ids::panelMidiOutputChannelDevice,1);
	const int program	= (int)getProperty(Ids::panelMidiProgram);
	const int bankLsb	= (int)getProperty(Ids::panelMidiBankLsb);
	const int bankMsb	= (int)getProperty(Ids::panelMidiBankMsb);

	sendMidi (MidiMessage::controllerEvent (midiCh, 0, bankMsb));
	sendMidi (MidiMessage::controllerEvent (midiCh, 32, bankLsb));
	sendMidi (MidiMessage::programChange(midiCh,program));

	if (luaPanelProgramChangedCbk && !luaPanelProgramChangedCbk.wasObjectDeleted())
	{
		if (luaPanelProgramChangedCbk->isValid())
		{
			getCtrlrLuaManager().getMethodManager().call (luaPanelProgramChangedCbk, program, bankLsb, bankMsb);
		}
	}
}

const String CtrlrPanel::globalsToString(const Array<int,CriticalSection> &arrayOfGlobals)
{
	String ret;

	for (int i=0; i<arrayOfGlobals.size(); i++)
	{
		ret << String(arrayOfGlobals[i]) + ":";
	}

	return (ret.upToLastOccurrenceOf(":", false, true));
}

const Array<int,CriticalSection> CtrlrPanel::globalsFromString(const String &globalsString)
{
	Array <int,CriticalSection> ar;
	ar.insertMultiple (0, 0, 64);
	StringArray temp;
	temp.addTokens (globalsString, ":", "\'\"");

	for (int i=0; i<temp.size(); i++)
	{
		ar.set (i, temp[i].getIntValue());
	}

	return (ar);
}

CtrlrModulator* CtrlrPanel::getModulator (const String& name) const
{
	// return (modulatorsByName[name]);
	for (int i=0; i<ctrlrModulators.size(); i++)
	{
		if (ctrlrModulators[i]->getProperty (Ids::name) == name)
		{
			return (ctrlrModulators[i]);
		}
	}
	return (0);
}

CtrlrModulator* CtrlrPanel::getModulatorByVstIndex (const int vstIndex)
{
	for (int i=0; i<ctrlrModulators.size(); i++)
	{
		if (ctrlrModulators[i]->getVstIndex() == vstIndex)
			return (ctrlrModulators[i]);
	}
	return (nullptr);
}

CtrlrModulator* CtrlrPanel::getModulatorByCustomIndex (const int customIndex)
{
	for (int i=0; i<ctrlrModulators.size(); i++)
	{
		if ((int)ctrlrModulators[i]->getProperty(Ids::modulatorCustomIndex) == customIndex)
			return (ctrlrModulators[i]);
	}
	return (nullptr);
}

int CtrlrPanel::getModulatorIndex (const CtrlrModulator *const modulatorToFind) const
{
	return (ctrlrModulators.indexOf (modulatorToFind));
}

int CtrlrPanel::getModulatorIndex (const String &modulatorToFind) const
{
	return (ctrlrModulators.indexOf(getModulator(modulatorToFind)));
}

void CtrlrPanel::setInstanceProperties(const ValueTree &instanceState)
{
	/* here we need to set all the MIDI properties for the instance */
	if (instanceState.hasType (Ids::panelState.toString()))
	{
		for (int i=0; i<instanceState.getNumProperties(); i++)
		{
			if (instanceState.getPropertyName(i).toString().startsWith ("panelMidi"))
			{
				// _DBG("\t"+instanceState.getPropertyName(i).toString() + "=" + instanceState.getProperty(instanceState.getPropertyName(i)).toString());
				setProperty (instanceState.getPropertyName(i), instanceState.getProperty(instanceState.getPropertyName(i)));
			}
		}
	}
}

void CtrlrPanel::initEmbeddedInstance()
{
	bootstrapPanel(false);
}

void CtrlrPanel::dumpComparatorTables()
{
	_INF ("\n----------------- MIDI INPUT START");
	_INF (midiInputThread.getInputComparator().dumpTables());
	_INF ("\n----------------- MIDI INPUT END");
	_INF (".");
	_INF (".");
	_INF ("\n----------------- MIDI CONTROLLER START");
	_INF (midiControllerInputThread.getInputComparator().dumpTables());
	_INF ("\n----------------- MIDI CONTROLLER END");
}

void CtrlrPanel::addPanelResource (const int hashCode)
{
	panelResources.addIfNotAlreadyThere (hashCode);
	setProperty (Ids::panelResources, globalsToString(panelResources));
}

void CtrlrPanel::removePanelResource (const int hashCode)
{
	panelResources.removeFirstMatchingValue (hashCode);
	setProperty (Ids::panelResources, globalsToString(panelResources));
}

bool CtrlrPanel::isPanelResource (const int hashCode)
{
	return (panelResources.contains (hashCode));
}

const File CtrlrPanel::getPanelDirectory()
{
	return (owner.getCtrlrPropertiesDirectory().getChildFile(getProperty(Ids::panelUID).toString()));
}

CtrlrPanelResourceManager &CtrlrPanel::getResourceManager()
{
	return (resourceManager);
}

const String CtrlrPanel::getName()
{
	return (getProperty(Ids::name));
}

void CtrlrPanel::undo()
{
	getUndoManager()->undo();
}

void CtrlrPanel::redo()
{
	getUndoManager()->redo();
}

bool CtrlrPanel::isSchemeAtLeast(const int minimumLevel)
{
	if ((int)getProperty(Ids::panelScheme) >= minimumLevel)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

void CtrlrPanel::notify (const String &notification, CtrlrNotificationCallback *callback, const CtrlrNotificationType ctrlrNotificationType)
{
	if (luaPanelMessageHandlerCbk && !luaPanelMessageHandlerCbk.wasObjectDeleted())
	{
		if (luaPanelMessageHandlerCbk->isValid())
		{
			getCtrlrLuaManager().getMethodManager().call (luaPanelMessageHandlerCbk, notification, ctrlrNotificationType);
		}
	}

	_INF (notification);
}

bool CtrlrPanel::getDialogStatus()
{
	return ( (bool)getProperty (Ids::panelShowDialogs));
}

void CtrlrPanel::upgradeScheme()
{
}

void CtrlrPanel::hashName(CtrlrModulator *modulator)
{
	modulatorsByName.set (modulator->getName(), modulator);
}

void CtrlrPanel::modulatorNameChanged(CtrlrModulator *modulatorThatChanged, const String &newName)
{
	modulatorsByName.removeValue (modulatorThatChanged);
	modulatorsByName.set (newName, modulatorThatChanged);
}

void CtrlrPanel::dumpDebugData()
{
	_DBG("CtrlrPanel::dumpDebugData");

	_DBG("---------- modulators by name hash table ----------");
	HashMap<String,CtrlrModulator*>::Iterator it (modulatorsByName);

	while (it.next())
	{
		_DBG ("["+it.getKey()+"]: " + it.getValue()->getName());
	}
	_DBG("---------- modulators by name hash table ----------");
}

const Identifier CtrlrPanel::getMidiOptionIdentifier(const CtrlrPanelMidiOption option)
{
	switch (option)
	{
		case panelMidiInputFromHost:
			return (Ids::panelMidiInputFromHost);
		case panelMidiInputFromHostCompare:
			return (Ids::panelMidiInputFromHostCompare);
		case panelMidiOutputToHost:
			return (Ids::panelMidiOutputToHost);
		case panelMidiThruH2H:
			return (Ids::panelMidiThruH2H);
		case panelMidiThruH2HChannelize:
			return (Ids::panelMidiThruH2HChannelize);
		case panelMidiThruH2D:
			return (Ids::panelMidiThruH2D);
		case panelMidiThruH2DChannelize:
			return (Ids::panelMidiThruH2DChannelize);
		case panelMidiThruD2D:
			return (Ids::panelMidiThruD2D);
		case panelMidiThruD2DChannelize:
			return (Ids::panelMidiThruD2DChannelize);
		case panelMidiThruD2H:
			return (Ids::panelMidiThruD2H);
		case panelMidiThruD2HChannelize:
			return (Ids::panelMidiThruD2HChannelize);
		case panelMidiRealtimeIgnore:
			return (Ids::panelMidiRealtimeIgnore);
		case panelMidiControllerToLua:
			return (Ids::panelMidiControllerToLua);
		default:
			break;
	}
	return (Ids::null);
}

int CtrlrPanel::getMidiChannelForOwnedMidiMessages()
{
	return (getProperty(Ids::panelMidiOutputChannelDevice));
}

CtrlrSysexProcessor *CtrlrPanel::getSysexProcessor()
{
	return (&ctrlrSysexProcessor);
}

Array<int,CriticalSection> &CtrlrPanel::getGlobalVariables()
{
	return (globalVariables);
}

void CtrlrPanel::resourceImportFinished()
{
	owner.getFontManager().reloadImportedFonts(this);

    if (luaPanelResourcesLoadedCbk && !luaPanelResourcesLoadedCbk.wasObjectDeleted())
	{
		if (luaPanelResourcesLoadedCbk->isValid())
		{
			getCtrlrLuaManager().getMethodManager().call (luaPanelResourcesLoadedCbk);
		}
	}
}

const String CtrlrPanel::getPanelInstanceID()
{
    if (getProperty(Ids::panelInstanceUID).toString().length() < 4)
    {
        setProperty (Ids::panelInstanceUID, generateRandomUniquePluginId());
    }

    return (getProperty(Ids::panelInstanceUID).toString());
}

const String CtrlrPanel::getPanelInstanceManufacturerID()
{
    if (getProperty(Ids::panelInstanceManufacturerID).toString().length() < 4)
    {
        setProperty (Ids::panelInstanceManufacturerID, generateRandomUniquePluginId());
    }

    return (getProperty(Ids::panelInstanceManufacturerID).toString());
}

const String CtrlrPanel::getPanelInstanceVersionString()
{
    return (getVersionString (false, false, "."));
}

int CtrlrPanel::getPanelInstanceVersionInt()
{
    return (getVersionAsHexInteger (getVersionString (false, false, ".")));
}

const String CtrlrPanel::getPanelInstanceName()
{
    return (getProperty (Ids::name).toString());
}

const String CtrlrPanel::getPanelInstanceManufacturer()
{
    return (getProperty(Ids::panelAuthorName).toString());
}

void CtrlrPanel::addMIDIControllerListener(CtrlrMIDIDevice::Listener *listenerToAdd)
{
}

void CtrlrPanel::removeMIDIControllerListener(CtrlrMIDIDevice::Listener *listenerToRemove)
{
}

void CtrlrPanel::performInternalComponentFunction(CtrlrComponent *sourceComponent)
{
	const CtrlrComponentInternalFunctions functionId = (CtrlrComponentInternalFunctions)(int)sourceComponent->getProperty(Ids::componentInternalFunction);

	switch (functionId)
	{
		case MIDIDeviceSelection:
			CtrlrMIDISettingsDialog::showDialog(*this);
			break;
		case none:
		default:
			break;
	}
}

String CtrlrPanel::getInternalFunctionsProperty(CtrlrComponent *component)
{
	if (CtrlrComponentTypeManager::findType(component) == Ids::uiButton)
	{
		return (_STR(COMBO_ITEM_NONE) + "\nShow MIDI device settings");
	}
	return ("");
}

void CtrlrPanel::multiMidiReceived(CtrlrMidiMessage &multiMidiMessage)
{
	multiMidiQueue.add (multiMidiMessage);
	triggerAsyncUpdate();
}
