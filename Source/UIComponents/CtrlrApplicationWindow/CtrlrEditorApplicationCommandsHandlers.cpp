#include "stdafx.h"
#include "CtrlrEditor.h"
#include "CtrlrAbout.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrWindowManagers/CtrlrDialogWindow.h"
#include "CtrlrMIDI/CtrlrMIDISettingsDialog.h"

bool CtrlrEditor::perform (const InvocationInfo &info)
{
    if (Time::getCurrentTime().toMilliseconds() - lastCommandInvocationMillis < 20)
    {
        return (true);
    }

	lastCommandInvocationMillis = Time::getCurrentTime().toMilliseconds();

	switch (info.commandID)
	{
		case showKeyboardMappingDialog:
			performShowKeyboardMappingDialog(info.commandID);
			break;

		case showMidiMonitor:
			owner.getWindowManager().toggle(CtrlrManagerWindowManager::MidiMonWindow, true);
			break;

		case showLogViewer:
			owner.getWindowManager().toggle(CtrlrManagerWindowManager::LogViewer, true);
			break;

		case showMidiCalculator:
			owner.getWindowManager().toggle(CtrlrManagerWindowManager::MIDICalculator, true);
			break;

		case doSaveState:
			owner.saveStateToDisk();
			break;

		case doOpenPanel:
			owner.openPanelFromFile(nullptr);
			break;

		case doNewPanel:
			owner.addPanel(ValueTree());
			break;

		case doRefreshPropertyLists:
			if (isPanelActive())
			{
				if (getActivePanel()->getEditor(false))
				{
					CtrlrPanelProperties *props = getActivePanel()->getEditor(false)->getPropertiesPanel();
					if (props)
					{
						props->refreshAll();
					}
				}
			}
			break;

		case showGlobalSettingsDialog:
			owner.getWindowManager().showModalDialog ("Ctrlr/Settings", ScopedPointer <CtrlrSettings> (new CtrlrSettings(owner)), true, this);
			break;

		case showAboutDialog:
			owner.getWindowManager().showModalDialog ("Ctrlr/About", ScopedPointer <CtrlrAbout> (new CtrlrAbout(owner)), false, this);
			break;

		case doZoomIn:
			if (getActivePanelEditor())
			{
				double newZoomFactor = (double)getActivePanelEditor()->getProperty(Ids::uiPanelZoom) + 0.1;
				if (newZoomFactor < MINZOOM || newZoomFactor > MAXZOOM)
					return true;
				getActivePanelEditor()->setProperty(Ids::uiPanelZoom, newZoomFactor);
			}
			break;

		case doZoomOut:
			if (getActivePanelEditor())
			{
				double newZoomFactor = (double)getActivePanelEditor()->getProperty(Ids::uiPanelZoom) - 0.1;
				if (newZoomFactor < MINZOOM || newZoomFactor >MAXZOOM)
					return true;
				getActivePanelEditor()->setProperty(Ids::uiPanelZoom, newZoomFactor);
			}
			break;

	    case doViewFullScreen:
	        toggleFullscreen();
	        break;

		case doCopy:
			getActivePanel()->getCanvas()->copy();
			break;

		case doCut:
			getActivePanel()->getCanvas()->cut();
			break;

		case doPaste:
			getActivePanel()->getCanvas()->paste();
			break;

		case doUndo:
			getActivePanel()->undo();
			break;

		case doRedo:
			getActivePanel()->redo();
			break;

        case doSearchForProperty:
            getActivePanelEditor()->searchForProperty();
            break;

		case doSave:
			getActivePanel()->savePanel();
			break;

		case doClose:
			if (getActivePanel()->canClose(true))
			{
				owner.removePanel(getActivePanelEditor());
			}
			break;

		case doSaveAs:
			getActivePanel()->savePanelAs(doExportFileText);
			break;

		case doSaveVersioned:
			getActivePanel()->savePanelVersioned();
			break;

		case doExportFileText:
		case doExportFileZText:
		case doExportFileBin:
		case doExportFileZBin:
		case doExportFileZBinRes:
		case doExportFileInstance:
		case doExportFileInstanceRestricted:
		case doExportGenerateUID:
			getActivePanel()->savePanelAs (info.commandID);
			break;

		case doViewPropertyDisplayIDs:
			if (getActivePanel()) getActivePanel()->setProperty (Ids::panelPropertyDisplayIDs, !getActivePanel()->getProperty(Ids::panelPropertyDisplayIDs));
			break;

		case doPanelMode:
			DBG("doPanelMode");
			if (getActivePanelEditor()) getActivePanelEditor()->setProperty (Ids::uiPanelEditMode, !getActivePanelEditor()->getProperty(Ids::uiPanelEditMode));
			break;

		case doPanelLock:
			if (getActivePanelEditor()) getActivePanelEditor()->setProperty (Ids::uiPanelLock, !(bool)getActivePanelEditor()->getProperty(Ids::uiPanelLock));
			break;

		case doPanelDisableCombosOnEdit:
			if (getActivePanelEditor()) getActivePanelEditor()->setProperty (Ids::uiPanelDisableCombosOnEdit, !(bool)getActivePanelEditor()->getProperty(Ids::uiPanelDisableCombosOnEdit));
			break;

		case showLuaEditor:
			if (getActivePanel()) getActivePanel()->getPanelWindowManager().toggle (CtrlrPanelWindowManager::LuaMethodEditor, true);
			break;

		case doRefreshDeviceList:
			performMidiDeviceRefresh();
			break;

		case showLuaConsole:
			if (getActivePanel()) getActivePanel()->getPanelWindowManager().toggle (CtrlrPanelWindowManager::LuaConsole, true);
			break;

		case showComparatorTables:
			if (getActivePanel()) getActivePanel()->dumpComparatorTables();
			break;

		case showModulatorList:
			if (getActivePanel()) getActivePanel()->getPanelWindowManager().toggle (CtrlrPanelWindowManager::ModulatorList, true);
			break;

		case showLayers:
			if (getActivePanel()) getActivePanel()->getPanelWindowManager().toggle (CtrlrPanelWindowManager::LayerEditor, true);
			break;

		case doSendSnapshot:
			if (getActivePanel()) getActivePanel()->sendSnapshot();
			break;

		case doShowMidiSettingsDialog:
			if (getActivePanel()) getActivePanel()->getPanelWindowManager().toggle (CtrlrPanelWindowManager::MIDISettings, true);
			break;

		case optMidiInputFromHost:
		case optMidiInputFromHostCompare:
		case optMidiOutuptToHost:
		    /* This should be fixed by the time check on the top of this method */
			//if (info.invocationMethod == ApplicationCommandTarget::InvocationInfo::direct)
            performMidiHostOptionChange(info.commandID);
			break;

		case optMidiSnapshotOnLoad:
		case optMidiSnapshotOnProgramChange:
            performMidiOptionChange(info.commandID);
			break;

		case optMidiThruD2D:
		case optMidiThruD2H:
		case optMidiThruH2D:
		case optMidiThruH2H:
		case optMidiThruD2DChannelize:
		case optMidiThruD2HChannelize:
		case optMidiThruH2DChannelize:
		case optMidiThruH2HChannelize:
		    /* This should be fixed by the time check on the top of this method */
			//if (info.invocationMethod == ApplicationCommandTarget::InvocationInfo::direct)
            performMidiThruChange(info.commandID);
			break;

		case doCrash:
			invalidCtrlrPtr->cancelPendingUpdate();
			break;

		case doDumpVstTables:
			owner.getVstManager().dumpDebugData();
			if (isPanelActive())
			{
				getActivePanel()->dumpDebugData();
			}
			break;

		case doQuit:
			if (owner.canCloseWindow())
			{
				JUCEApplication::quit();
			}
			break;

		case doRegisterExtension:
			tempResult = owner.getNativeObject().registerFileHandler();
			if (tempResult.wasOk())
			{
				INFO("Register file handler", "Registration successful");
			}
			else
			{
				WARN("Registration failed");
			}
			break;

		default:
			break;
	}

	return (true);
}

void CtrlrEditor::performRecentFileOpen(const int menuItemID)
{
	File f = getRecentOpenedFilesList() [menuItemID - 0x9000];

	if (f.existsAsFile())
	{
		owner.addPanel (CtrlrPanel::openPanel (f), true);
	}
}

void CtrlrEditor::performShowKeyboardMappingDialog(const int menuItemID)
{
	ScopedPointer <KeyMappingEditorComponent> keys (new KeyMappingEditorComponent (*owner.getCommandManager().getKeyMappings(), true));
	owner.getWindowManager().showModalDialog ("Keyboard mapping", keys, true, this);

	ScopedPointer <XmlElement> keysXml (owner.getCommandManager().getKeyMappings()->createXml (true).release());

	if (keysXml)
	{
		owner.setProperty (Ids::ctrlrKeyboardMapping, keysXml->createDocument(""));
	}
}

void CtrlrEditor::performMidiChannelChange(const int menuItemID)
{
	if (isPanelActive())
	{
		if (menuItemID >= 0x6100 && menuItemID <= 0x6111)
		{
			getActivePanel()->setProperty (Ids::panelMidiInputChannelDevice, menuItemID - 0x6100);
		}
		else if (menuItemID >= 0x6200 && menuItemID <= 0x6211)
		{
			getActivePanel()->setProperty (Ids::panelMidiOutputChannelDevice, menuItemID - 0x6200);
		}
		else if (menuItemID >= 0x6300 && menuItemID <= 0x6311)
		{
			getActivePanel()->setProperty (Ids::panelMidiControllerChannelDevice, menuItemID - 0x6300);
		}
		else if (menuItemID >= 0x6400 && menuItemID <= 0x6411)
		{
			getActivePanel()->setProperty (Ids::panelMidiInputChannelHost, menuItemID - 0x6400);
		}
		else if (menuItemID >= 0x6500 && menuItemID <= 0x6511)
		{
			getActivePanel()->setProperty (Ids::panelMidiOutputChannelHost, menuItemID - 0x6500);
		}
	}
}

void CtrlrEditor::performMidiDeviceChange(const int menuItemID)
{
	if (isPanelActive())
	{
		if (menuItemID > MENU_OFFSET_MIDI_DEV_IN && menuItemID < MENU_OFFSET_MIDI_DEV_OUT)
		{
			getActivePanel()->setProperty(Ids::panelMidiInputDevice, owner.getCtrlrMidiDeviceManager().getDeviceName(menuItemID - MENU_OFFSET_MIDI_DEV_IN - 2, inputDevice));
		}
		else if (menuItemID > MENU_OFFSET_MIDI_DEV_OUT && menuItemID < MENU_OFFSET_MIDI_DEV_CTRLR)
		{
			getActivePanel()->setProperty(Ids::panelMidiOutputDevice, owner.getCtrlrMidiDeviceManager().getDeviceName(menuItemID - MENU_OFFSET_MIDI_DEV_OUT - 2, outputDevice));
		}
		else if (menuItemID > MENU_OFFSET_MIDI_DEV_CTRLR && menuItemID < MENU_OFFSET_MIDI_HOST_IN)
		{
			getActivePanel()->setProperty(Ids::panelMidiControllerDevice, owner.getCtrlrMidiDeviceManager().getDeviceName(menuItemID - MENU_OFFSET_MIDI_DEV_CTRLR - 2, controllerDevice));
		}
	}
}

void CtrlrEditor::performMidiThruChange(const int menuItemID)
{
	const Identifier optionId = CtrlrPanel::getMidiOptionIdentifier((const CtrlrPanelMidiOption)(menuItemID - MENU_OFFSET_MIDI));

	if (isPanelActive() && optionId != Ids::null)
	{
		getActivePanel()->setProperty (optionId, !getActivePanel()->getProperty(optionId));
	}
}

void CtrlrEditor::performMidiOptionChange(const int menuItemID)
{
	if (menuItemID == optMidiSnapshotOnLoad)
	{
		if (isPanelActive())
		{
			getActivePanel()->setProperty (Ids::panelMidiSnapshotAfterLoad, !getPanelProperty(Ids::panelMidiSnapshotAfterLoad));
		}
	}
	else if (menuItemID == optMidiSnapshotOnProgramChange)
	{
		if (isPanelActive())
		{
			getActivePanel()->setProperty (Ids::panelMidiSnapshotAfterProgramChange, !getPanelProperty(Ids::panelMidiSnapshotAfterProgramChange));
		}
	}
}

void CtrlrEditor::performProgramChange(const int menuItemID)
{
	if (isPanelActive())
	{
		// getActivePanel()->getCtrlrMIDILibrary().setProgram (menuItemID);
	}
}

void CtrlrEditor::performMidiHostOptionChange(const int menuItemID)
{
	if (isPanelActive())
	{
		CtrlrPanel *p = getActivePanel();

		switch (menuItemID)
		{
			case optMidiInputFromHost:
				p->setProperty(Ids::panelMidiInputFromHost, !(bool)p->getProperty(Ids::panelMidiInputFromHost));
				break;
			case optMidiInputFromHostCompare:
				p->setProperty(Ids::panelMidiInputFromHostCompare, !(bool)p->getProperty(Ids::panelMidiInputFromHostCompare));
				break;
			case optMidiOutuptToHost:
				p->setProperty(Ids::panelMidiOutputToHost, !(bool)p->getProperty(Ids::panelMidiOutputToHost));
				break;
		}

		//getActivePanel()->setMidiOptionBool ((const CtrlrPanelMidiOption)(menuItemID - MENU_OFFSET_MIDI), !getActivePanel()->getMidiOptionBool((const CtrlrPanelMidiOption)(menuItemID - MENU_OFFSET_MIDI)));
	}
}

void CtrlrEditor::sliderValueChanged (Slider* slider)
{
	if (slider->getName() == "Snapshot delay")
	{
		if (isPanelActive())
		{
			getActivePanel()->setProperty(Ids::panelMidiSnapshotDelay, slider->getValue());
		}
	}
}

void CtrlrEditor::performMidiDeviceRefresh()
{
	owner.getCtrlrMidiDeviceManager().refreshDevices();
}

void CtrlrEditor::toggleFullscreen()
{
    owner.sendActionMessageToWindow("fullscreen");
}