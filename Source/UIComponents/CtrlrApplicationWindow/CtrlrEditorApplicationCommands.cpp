#include "stdafx.h"
#include "CtrlrEditor.h"
#include "CtrlrAbout.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"

void CtrlrEditor::getAllCommands (Array< CommandID > &commands)
{
	const CommandID ids[] = {	doSaveState,
                                doOpenPanel,
                                doNewPanel,
                                showGlobalSettingsDialog,
                                showMidiMonitor,
                                showLogViewer,
                                showMidiCalculator,
                                showAboutDialog,
								showKeyboardMappingDialog,
								doViewPropertyDisplayIDs,
								doZoomIn,
								doZoomOut,
								doViewFullScreen,
								doCopy,
								doCut,
								doPaste,
								doUndo,
								doRedo,
								doSave,
								doClose,
								doSaveAs,
								doSaveVersioned,
								doPanelMode,
								doPanelLock,
								doPanelDisableCombosOnEdit,
								doSendSnapshot,
								doRefreshDeviceList,
								showLuaEditor,
								showLuaConsole,
								showComparatorTables,
								showModulatorList,
								showBufferEditor,
								showLayers,
								doRefreshPropertyLists,
								doExportFileText,
								doExportFileZText,
								doExportFileBin,
								doExportFileZBin,
								doExportFileZBinRes,
								doExportFileInstance,
								doExportFileInstanceRestricted,
								doExportGenerateUID,
                                 doSearchForProperty,
								doShowMidiSettingsDialog,
								optMidiInputFromHost,
								optMidiInputFromHostCompare,
								optMidiOutuptToHost,
								optMidiSnapshotOnLoad,
								optMidiSnapshotOnProgramChange,
								optMidiThruD2D,
								optMidiThruD2H,
								optMidiThruH2D,
								optMidiThruH2H,
								optMidiThruH2HChannelize,
								optMidiThruH2DChannelize,
								optMidiThruD2DChannelize,
								optMidiThruD2HChannelize,
								doSnapshotStore,
								doCrash,
								doDumpVstTables,
								doRegisterExtension,
								doKeyGenerator,
								doProgramWizard,
								doQuit
							};

        commands.addArray (ids, numElementsInArray (ids));
}

void CtrlrEditor::getCommandInfo (CommandID commandID, ApplicationCommandInfo &result)
{
	const String globalCategory ("Global");
	const String panelCategory ("Panel");

	switch (commandID)
	{
		case doSaveState:
			result.setInfo ("Save CTRLR state", "Saves the CTRLR state to disk", globalCategory, 0);
			result.addDefaultKeypress ('s', ModifierKeys::commandModifier | ModifierKeys::altModifier);
			break;

		case doOpenPanel:
			result.setInfo ("Open Panel", "Open a panel from a file", globalCategory, 0);
			result.addDefaultKeypress ('o', ModifierKeys::commandModifier);
			break;

		case doNewPanel:
			result.setInfo ("New Panel", "Create a new empty panel", globalCategory, 0);
			result.addDefaultKeypress ('n', ModifierKeys::commandModifier);
			break;

		case showGlobalSettingsDialog:
			result.setInfo ("Preferences", "Show global CTRLR preferences", globalCategory, 0);
			result.addDefaultKeypress ('p', ModifierKeys::commandModifier);
			break;

		case showMidiMonitor:
			result.setInfo ("MIDI Monitor", "A small MIDI monitor that will display received and sent data", globalCategory, 0);
			result.addDefaultKeypress ('m', ModifierKeys::commandModifier);
			break;

		case showLogViewer:
			result.setInfo ("Log viewer", "You can view diagnostic messages here, useful when debugging problems", globalCategory, 0);
			result.addDefaultKeypress ('l', ModifierKeys::commandModifier);
			break;

		case showMidiCalculator:
			result.setInfo ("MIDI Calculator", "A useful tool to translate Heximal, Binary, Decimal values", globalCategory, 0);
			result.addDefaultKeypress ('j', ModifierKeys::commandModifier);
			break;

		case showAboutDialog:
			result.setInfo ("About", "About CTRLR", globalCategory, 0);
			result.addDefaultKeypress ('a', ModifierKeys::commandModifier);
			break;

		case showKeyboardMappingDialog:
			result.setInfo ("Keyboard mapping", "Change default keyboard mappings", globalCategory, 0);
			result.addDefaultKeypress ('k', ModifierKeys::commandModifier);
			break;

		case doViewPropertyDisplayIDs:
			result.setInfo ("Property IDs/Names", "View property names or property IDs", panelCategory, 0);
			result.setTicked (isPanelActive() ? (bool)getActivePanel()->getProperty(Ids::panelPropertyDisplayIDs) : false);
			result.setActive (isPanelActive());
			break;

		case doZoomIn:
			result.setInfo ("Zoom In", "Zoom in the panel", panelCategory, 0);
			result.addDefaultKeypress ('+', ModifierKeys::commandModifier);
			result.setActive (isPanelActive());
			break;

		case doZoomOut:
			result.setInfo ("Zoom Out", "Zoom out the panel", panelCategory, 0);
			result.addDefaultKeypress ('-', ModifierKeys::commandModifier);
			result.setActive (isPanelActive());
			break;

        case doViewFullScreen:
            result.setInfo ("Full screen", "Switch Ctrlr window to full screen", globalCategory, 0);
            result.addDefaultKeypress (KeyPress::F11Key, ModifierKeys::noModifiers);
            result.setActive (true);
            break;

		case doCopy:
			result.setInfo ("Copy", "Copy selected components to clipboard", panelCategory, 0);
			result.addDefaultKeypress ('c', ModifierKeys::commandModifier);
			result.setActive (isPanelActive(true));
			break;

		case doCut:
			result.setInfo ("Cut", "Cut selected components to clipboard", panelCategory, 0);
			result.addDefaultKeypress ('x', ModifierKeys::commandModifier);
			result.setActive (isPanelActive(true));
			break;

		case doPaste:
			result.setInfo ("Paste", "Paste components from clipboard", panelCategory, 0);
			result.addDefaultKeypress ('v', ModifierKeys::commandModifier);
			result.setActive (isPanelActive(true));
			break;

		case doUndo:
			result.setInfo ("Undo", "Undo last transaction", panelCategory, 0);
			result.addDefaultKeypress ('z', ModifierKeys::commandModifier);
			result.setActive (isPanelActive(true));
			break;

		case doRedo:
			result.setInfo ("Redo", "Redo last transaction", panelCategory, 0);
			result.addDefaultKeypress ('y', ModifierKeys::commandModifier);
			result.setActive (isPanelActive(true));
			break;
	    case doSearchForProperty:
            result.setInfo ("Search for property", "Search for any property in the current panel or selected component", panelCategory, 0);
            result.addDefaultKeypress ('f', ModifierKeys::commandModifier);
            result.setActive (isPanelActive(true));
            break;

		case doSave:
			result.setInfo ("Save", "Save panel to a file", panelCategory, 0);
			result.addDefaultKeypress ('s', ModifierKeys::commandModifier);
			result.setActive (isPanelActive(true));
			break;

		case doClose:
			result.setInfo ("Close", "Close the current panel", panelCategory, 0);
			result.setActive (isPanelActive(true));
			break;

		case doSaveAs:
			result.setInfo ("Save As", "Save panel as a new file", panelCategory, 0);
			result.addDefaultKeypress ('s', ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
			result.setActive (isPanelActive(true));
			break;

		case doSaveVersioned:
			result.setInfo ("Save versioned", "Save panel to a new versioned file", panelCategory, 0);
			result.addDefaultKeypress ('s', ModifierKeys::altModifier | ModifierKeys::shiftModifier);
			result.setActive (isPanelActive(true));
			break;

		case doPanelMode:
			result.setInfo ("Panel mode", "Switches panel from and to EDIT mode", panelCategory, 0);
			result.addDefaultKeypress ('e', ModifierKeys::commandModifier);
			result.setActive (isPanelActive(true));
			break;

		case doPanelLock:
			result.setInfo ("Panel lock", "Locks components in edit mode", panelCategory, 0);
			result.addDefaultKeypress ('l', ModifierKeys::commandModifier);
			result.setActive (isPanelActive(true));
			if (isPanelActive(true))
			{
				result.setTicked ((bool)getActivePanelEditor()->getProperty(Ids::uiPanelLock));
			}
			break;

		case doPanelDisableCombosOnEdit:
			result.setInfo ("Disable combos on edit", "Combo boxes will not open when editing panel", panelCategory, 0);
			result.setActive (isPanelActive(true));
			if (isPanelActive(true))
			{
				result.setTicked ((bool)getActivePanelEditor()->getProperty(Ids::uiPanelDisableCombosOnEdit));
			}
			break;

		case showLuaEditor:
			result.setInfo ("LUA Editor", "Show/hide the LUA editor window", panelCategory, 0);
			result.setActive (isPanelActive(true));
			break;

		case doRefreshDeviceList:
			result.setInfo ("Refresh devices", "Refresh the list of devices available in the OS", panelCategory, 0);
			result.setActive (true);
			break;

		case showLuaConsole:
			result.setInfo ("LUA Console", "Show/hide the LUA console", panelCategory, 0);
			result.setActive (isPanelActive(true));
			break;

		case showComparatorTables:
			result.setInfo ("Comparator tables", "Show/hide the dump for the comparator tables", panelCategory, 0);
			result.setActive (isPanelActive());
			break;

		case showMidiLibrary:
			result.setInfo ("MIDI Library", "Show/hide the MIDI LIbrary window", panelCategory, 0);
			result.setActive (isPanelActive());
			result.addDefaultKeypress ('l', ModifierKeys::altModifier | ModifierKeys::shiftModifier);
			break;

		case showLayers:
			result.setInfo ("Layer editor", "Show/hide the layer editor", panelCategory, 0);
			result.setActive (isPanelActive(true));
			break;

		case showModulatorList:
			result.setInfo ("Modulator list", "Show/hide the modulator list window", panelCategory, 0);
			result.setActive (isPanelActive(true));
			break;

		case showBufferEditor:
			result.setInfo ("Buffer Editor", "Show/hide the buffer editor", panelCategory, 0);
			result.addDefaultKeypress ('b', ModifierKeys::commandModifier);
			result.setActive (isPanelActive(true));
			break;

		case doSendSnapshot:
			result.setInfo ("Send Snapshot", "Send all values from the panel as their defines MIDI messages", panelCategory, 0);
			result.setActive (isPanelActive());
			break;

		case doSnapshotStore:
			result.setInfo ("Program snapshot", "Save the current panel state as a snapshot", panelCategory, 0);
			result.setActive (isPanelActive());
			break;

		case doRefreshPropertyLists:
			result.setInfo ("Refresh property lists", "Refreshes all dynamic lists that occur in the property pane", panelCategory, 0);
			result.setActive (isPanelActive());
			break;

		case doExportFileText:
			result.setInfo ("Export XML", "Export panel to a XML file with no compression, might be very large", panelCategory, 0);
			result.setActive (isPanelActive(true));
			break;

		case doExportFileZText:
			result.setInfo ("Export compressed XML", "Export panel to a zlib compressed XML file", panelCategory, 0);
			result.setActive (isPanelActive(true));
			break;

		case doExportFileBin:
			result.setInfo ("Export binary", "Export panel to a binary file, unlike XML is unreadable but loads faster", panelCategory, 0);
			result.setActive (isPanelActive(true));
			break;

		case doExportFileZBin:
			result.setInfo ("Export compressed binary", "Export panel to a zlib compressed binary file", panelCategory, 0);
			result.setActive (isPanelActive(true));
			break;

		case doExportFileZBinRes:
			result.setInfo ("Export compressed binary + resources", "Export panel to a zlib compressed binary file with resources included", panelCategory, 0);
			result.setActive (isPanelActive(true));
			break;

		case doExportFileInstance:
			result.setInfo ("Export instance", "Exports the panel as a standalone instance (executable/loadable file)", panelCategory, 0);
			result.setActive (isPanelActive(true));
			break;

		case doExportFileInstanceRestricted:
			result.setInfo ("Export restricted instance", "Exports the panel as a standalone restricted instance (executable/loadable file). It won't be editable.", panelCategory, 0);
			result.setActive (isPanelActive(true));
			break;

		case doExportGenerateUID:
			result.setInfo ("Re-generate UID ["+getPanelProperty(Ids::panelUID).toString()+"]", "Each panel has a Unique ID that can be re-generated", panelCategory, 0);
			result.setActive (isPanelActive(true));
			break;

		case optMidiInputFromHost:
			result.setInfo ("Input from plugin host", "Accept MIDI events from host and process them", panelCategory, 0);
			result.setActive (!JUCEApplication::isStandaloneApp());
			result.setTicked (isPanelActive() ? getActivePanel()->getMidiOptionBool((const CtrlrPanelMidiOption)optMidiInputFromHost) : false);
			break;

		case doShowMidiSettingsDialog:
			result.setInfo("Settings", "Show a more user friendly MIDI settings dialog", panelCategory, 0);
			result.setActive (isPanelActive(true));
			break;

		case optMidiInputFromHostCompare:
			result.setInfo ("Input from host to comparator", "This option tells Ctrlr to route all incomming MIDI events from the MIDI host to the Comparator engine, messages that will match modulators in the panel will be treated as comming from a MIDI device", panelCategory, 0);
			result.setActive (!JUCEApplication::isStandaloneApp());
			result.setTicked (isPanelActive() ? getActivePanel()->getMidiOptionBool((const CtrlrPanelMidiOption)optMidiInputFromHostCompare) : false);
			break;

		case optMidiOutuptToHost:
			result.setInfo ("Output to plugin host", "All MIDI output goes to the MIDI host (if supported by the plugin format and the host)", panelCategory, 0);
			result.setActive (!JUCEApplication::isStandaloneApp());
			result.setTicked (isPanelActive() ? getActivePanel()->getMidiOptionBool((const CtrlrPanelMidiOption)optMidiOutuptToHost) : false);
			break;

		case optMidiSnapshotOnLoad:
			result.setInfo ("Snapshot on load", "After the panel is loaded a Snapshot will be sent", panelCategory, 0);
			result.setActive (isPanelActive());
			result.setTicked (getPanelProperty(Ids::panelMidiSnapshotAfterLoad));
			break;

		case optMidiSnapshotOnProgramChange:
			result.setInfo ("Snapshot on program change", "After each program change event on the panel a Snapshot will be sent", panelCategory, 0);
			result.setActive (isPanelActive());
			result.setTicked (getPanelProperty(Ids::panelMidiSnapshotAfterProgramChange));
			break;

		case optMidiThruD2D:
			result.setInfo ("Input device -> Output device", "Send all MIDI messages comming from the MIDI input device via the MIDI output device", panelCategory, 0);
			result.setActive (isPanelActive());
			if (isPanelActive())
				result.setTicked (getActivePanel()->getMidiOptionBool (panelMidiThruD2D));
			break;

		case optMidiThruD2H:
			result.setInfo ("Input device -> Plugin host", "Send all MIDI messages from the MIDI input device to the plugin host (if supported by the plugin format and the host)", panelCategory, 0);
			result.setActive (isPanelActive() && (JUCEApplication::isStandaloneApp() == false));
			if (isPanelActive())
				result.setTicked (getActivePanel()->getMidiOptionBool (panelMidiThruD2H));

			break;

		case optMidiThruH2D:
			result.setInfo ("Plugin host -> Output device", "Send all MIDI messages comming from the plugin host the MIDI output device", panelCategory, 0);
			result.setActive (isPanelActive() && (JUCEApplication::isStandaloneApp() == false));
			if (isPanelActive())
				result.setTicked (getActivePanel()->getMidiOptionBool (panelMidiThruH2D));
			break;

		case optMidiThruH2H:
			result.setInfo ("Plugin host -> Plugin host", "Send all MIDI messages comming from the plugin host back to it (if supported by the plugin format and the host)", panelCategory, 0);
			result.setActive (isPanelActive() && (JUCEApplication::isStandaloneApp() == false));
			if (isPanelActive())
				result.setTicked (getActivePanel()->getMidiOptionBool (panelMidiThruH2H));
			break;

		case optMidiThruD2DChannelize:
			result.setInfo ("Change channel: Input device -> Output device", "Change the channel of MIDI messages comming in on the MIDI input device to the MIDI channel set for the output device", panelCategory, 0);
			result.setActive (isPanelActive() && (JUCEApplication::isStandaloneApp() == false));
			if (isPanelActive())
				result.setTicked (getActivePanel()->getMidiOptionBool (panelMidiThruD2DChannelize));
			break;

		case optMidiThruD2HChannelize:
			result.setInfo ("Change channel: Input device -> Plugin host", "Change the channel of MIDI messages comming in on the MIDI input device to the MIDI channel set for the output to plugin host", panelCategory, 0);
			result.setActive (isPanelActive() && (JUCEApplication::isStandaloneApp() == false));
			if (isPanelActive())
				result.setTicked (getActivePanel()->getMidiOptionBool (panelMidiThruD2HChannelize));
			break;

		case optMidiThruH2DChannelize:
			result.setInfo ("Change channel: Plugin host -> Output device", "Change the channel of MIDI messages comming in from the plugin host to the MIDI channel set for the output device", panelCategory, 0);
			result.setActive (isPanelActive() && (JUCEApplication::isStandaloneApp() == false));
			if (isPanelActive())
				result.setTicked (getActivePanel()->getMidiOptionBool (panelMidiThruH2DChannelize));
			break;

		case optMidiThruH2HChannelize:
			result.setInfo ("Change channel: Plugin host -> Plugin host", "Change the channel of MIDI messages comming in from the plugin host to the MIDI channel set for the output to plugin host", panelCategory, 0);
			result.setActive (isPanelActive() && (JUCEApplication::isStandaloneApp() == false));
			if (isPanelActive())
				result.setTicked (getActivePanel()->getMidiOptionBool (panelMidiThruH2HChannelize));
			break;

		case doCrash:
			result.setInfo ("Crash Ctrlr", "Simulate Ctrlr crashing to see what happens", globalCategory, 0);
			result.setActive (true);
			break;

		case doDumpVstTables:
			result.setInfo ("Dump Memory Info", "Dump information stored in memory in some readable format", globalCategory, 0);
			result.setActive (true);
			break;

		case doRegisterExtension:
			result.setInfo ("Register file extensions", "Register Ctrlr to hanle .panel file extension", globalCategory, 0);
			result.setActive (true);
			break;

        case doKeyGenerator:
            result.setInfo ("Key Generator", "Generate a private key for signing panels", globalCategory, 0);
            result.setActive (true);
            break;

        case doProgramWizard:
            result.setInfo ("Program wizard", "Wizard to generate program requests", globalCategory, 0);
            result.setActive (true);
            break;

		case doQuit:
			result.setInfo ("Quit", "Quit Ctrlr", globalCategory, 0);
			result.setActive (JUCEApplication::isStandaloneApp());
			break;
	}
}

ApplicationCommandTarget* CtrlrEditor::getNextCommandTarget()
{
	return findFirstTargetParentComponent();
}
