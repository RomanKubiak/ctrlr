#ifndef __CTRLR_EDITOR__
#define __CTRLR_EDITOR__

#include "CtrlrMacros.h"
#include "CtrlrWindowManagers/CtrlrChildWindowContainer.h"
#include "CtrlrSettings.h"

class CtrlrManager;
class CtrlrProcessor;

class CtrlrEditor  : public AudioProcessorEditor,
					 public ApplicationCommandTarget,
					 public MenuBarModel,
					 public Slider::Listener,
					 public LookAndFeel_V4
{
	public:
		CtrlrEditor (CtrlrProcessor *ownerFilter, CtrlrManager &_owner);
		~CtrlrEditor();
		enum TopMenuIDs
		{
			MenuFile,
			MenuEdit,
			MenuView,
			MenuPanel,
			MenuMidi,
			MenuPrograms,
			MenuTools,
			MenuHelp
		};

		enum TopMenuRestrictedIDs
		{
			MenuRestrictedFile,
			MenuRestrictedEdit,
			MenuRestrictedView,
			MenuRestrictedMidi,
			MenuRestrictedPrograms,
			MenuRestrictedTools,
			MenuRestrictedHelp
		};

		enum CommandIDs
		{
			doSaveState					= 0x2000,
			doOpenPanel					= 0x2001,
			doNewPanel					= 0x2002,
			showGlobalSettingsDialog	= 0x2003,
			showMidiMonitor             = 0x2005,
			showLogViewer				= 0x2006,
			showMidiCalculator          = 0x2007,
			showAboutDialog             = 0x2008,
			showKeyboardMappingDialog	= 0x200a,

			/* Panel commands */

			doZoomIn					= 0x3001,
			doZoomOut					= 0x3002,
			doCopy						= 0x3003,
			doCut						= 0x3004,
			doPaste						= 0x3005,
			doUndo						= 0x3024,
			doRedo						= 0x3025,
			doSave						= 0x3006,
			doSaveAs					= 0x3007,
			doSaveVersioned				= 0x3008,
			doPanelMode					= 0x300a,
			doPanelLock					= 0x300b,
			doPanelDisableCombosOnEdit	= 0x3027,
			doSendSnapshot				= 0x300c,
			doRefreshDeviceList			= 0x200b,
			showLuaEditor				= 0x3011,
			showMidiLibrary				= 0x3012,
			showModulatorList			= 0x3013,
			showBufferEditor			= 0x3028,
			doClose						= 0x3015,
			showLayers					= 0x3016,
			showLuaConsole				= 0x3017,
			showComparatorTables		= 0x3018,
			doRefreshPropertyLists		= 0x3019,
			doViewPropertyDisplayIDs	= 0x3020,
            doViewFullScreen            = 0x3021,
			doExportFileText			= 0x4001,
			doExportFileZText			= 0x4002,
			doExportFileBin				= 0x4003,
			doExportFileZBin			= 0x4004,
			doExportFileZBinRes			= 0x4005,
			doExportFileInstance		= 0x4006,
			doExportGenerateUID			= 0x4007,
			doSearchForProperty         = 0x4018,
			doExportFileInstanceRestricted		= 0x4008,
			doSnapshotStore						= 0x4009,
			optMidiSnapshotOnLoad				= 0x6003,
			optMidiSnapshotOnProgramChange		= 0x6004,
			doPrevProgram						= 0x6005,
			doNextProgram						= 0x6006,
			doPrevBank							= 0x6007,
			doNextBank							= 0x6008,
			doShowMidiSettingsDialog			= 0x3010,
			optMidiInputFromHost		= MENU_OFFSET_MIDI + 2,
			optMidiInputFromHostCompare	= MENU_OFFSET_MIDI + 4,
			optMidiOutuptToHost			= MENU_OFFSET_MIDI + 8,
			optMidiThruH2H				= MENU_OFFSET_MIDI + 16,
			optMidiThruH2HChannelize	= MENU_OFFSET_MIDI + 32,
			optMidiThruH2D				= MENU_OFFSET_MIDI + 64,
			optMidiThruH2DChannelize	= MENU_OFFSET_MIDI + 128,
			optMidiThruD2D				= MENU_OFFSET_MIDI + 256,
			optMidiThruD2DChannelize	= MENU_OFFSET_MIDI + 512,
			optMidiThruD2H				= MENU_OFFSET_MIDI + 1024,
			optMidiThruD2HChannelize	= MENU_OFFSET_MIDI + 2048,

			doCrash						= 0x20,
			doDumpVstTables				= 0x21,
			doRegisterExtension			= 0x22,
			doKeyGenerator              = 0x23,
			doProgramWizard             = 0x24,
			doQuit						= 0x00fffffe
		};

		void activeCtrlrChanged();
		const WeakReference<CtrlrEditor>::SharedRef& getWeakReference();
		CtrlrManager &getOwner()											{ return (owner); }
		WeakReference<CtrlrEditor>::Master masterReference;
		void paint (Graphics& g);
		void resized();
		void getAllCommands (Array< CommandID > &commands);
		void getCommandInfo (CommandID commandID, ApplicationCommandInfo &result);
		bool perform (const InvocationInfo &info);

		ApplicationCommandTarget* getNextCommandTarget();
		StringArray getMenuBarNames();
		PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName);
		void menuItemSelected(int menuItemID, int topLevelMenuIndex);
		void sliderValueChanged (Slider* slider);
		MenuBarComponent *getMenuBar();
		CtrlrPanel *getActivePanel();
		CtrlrPanelEditor *getActivePanelEditor();
		bool isPanelActive(const bool checkRestrictedInstance=false);
		const PopupMenu getRecentOpenedFilesMenu();
		const PopupMenu getMidiDeviceMenu(const CtrlrMIDIDeviceType type=inputDevice);
		const PopupMenu getMidiChannelMenu(const CtrlrMIDIDeviceType type=inputDevice);
		uint32 getMidiDeviceMenuOffset(const CtrlrMIDIDeviceType type=inputDevice);
		const Identifier getMidiPropertyName(const CtrlrMIDIDeviceType type=inputDevice);
		const StringArray getRecentOpenedFilesList();
		const var getPanelProperty(const Identifier &propertyName);
		const String getMidiSummary(const CtrlrMIDIDeviceType type=inputDevice);
		bool isRestricted();
		void performShowKeyboardMappingDialog(const int menuItemID);
		void performMidiChannelChange(const int menuItemID);
		void performMidiDeviceChange(const int menuItemID);
		void performMidiOptionChange(const int menuItemID);
		void performProgramChange(const int menuItemID);
		void performMidiHostOptionChange(const int menuItemID);
		void performMidiThruChange(const int menuItemID);
		void performRecentFileOpen(const int menuItemID);
		void toggleFullscreen();
		void performKeyGenerator();
		void performMidiDeviceRefresh();
		void setMenuBarVisible(const bool shouldBeVisible=true);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrEditor)

	private:
		bool menuHandlerCalled;
		MenuBarComponent *menuBar;
		TooltipWindow tooltipWindow;
		CtrlrManager &owner;
		ResizableCornerComponent resizer;
		CtrlrProcessor *ownerFilter;
		ComponentBoundsConstrainer constrainer;
		Label l;
		CtrlrPanel *invalidCtrlrPtr;
		Result tempResult;
		int64 lastCommandInvocationMillis;
		bool hideProgramsMenu = false;
		bool hideMidiControllerMenu = false;
		bool hideMidiThruMenu = false;
		bool hideMidiChannelMenu = false;

};


#endif
