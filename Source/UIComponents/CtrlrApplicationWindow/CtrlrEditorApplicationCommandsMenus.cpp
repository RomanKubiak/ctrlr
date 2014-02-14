#include "stdafx.h"
#include "CtrlrEditor.h"
#include "CtrlrAbout.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrMIDILibrary/CtrlrMIDILibrary.h"

class CtrlrMenuSlider : public PopupMenu::CustomComponent, public LookAndFeel_V3
{
	public:
		class CtrlrMenuSliderInternal : public Slider
		{
			public:
				CtrlrMenuSliderInternal(CtrlrMenuSlider &_owner, const String &_name) : owner(_owner), name(_name)
				{
				}

				String getTextFromValue (double value)
				{
					return ("(" + name + ") " + STR(value) + getTextValueSuffix());
				}

			private:
				CtrlrMenuSlider &owner;
				String name;
		};

		CtrlrMenuSlider(Slider::Listener *listener, const String &_name, const int initialValue, const int min, const int max, const int interval)
			:	PopupMenu::CustomComponent(false), name(_name),
				itemHeight(roundFloatToInt(LookAndFeel::getDefaultLookAndFeel().getPopupMenuFont().getHeight() * 1.25)),
				slider(*this, _name)
		{
			slider.setTextValueSuffix (" ms");
			slider.setLookAndFeel (this);
			slider.setName (name);
			slider.setSliderStyle (Slider::LinearBar);
			slider.setTextBoxStyle (Slider::TextBoxRight, false, 48, itemHeight);
			slider.setRange (min, max, interval);
			slider.addListener (listener);
			slider.setValue (initialValue, dontSendNotification);
			addAndMakeVisible (&slider);
		}

		void getIdealSize(int &idealWidth, int &idealHeight)
		{
			idealWidth	= 96;
			idealHeight	= itemHeight;
		}

		void resized()
		{
			slider.setBounds (getBounds());
			overlay.setBounds (getBounds());
		}

		Label* createSliderTextBox (Slider& slider)
		{
			Label* const l = new Label();
			l->setFont(LookAndFeel::getDefaultLookAndFeel().getPopupMenuFont().getHeight());
			l->setJustificationType (Justification::centred);
			l->setColour (Label::textColourId, slider.findColour (Slider::textBoxTextColourId));
			l->setColour (Label::backgroundColourId, (slider.getSliderStyle() == Slider::LinearBar) ? Colours::transparentBlack : slider.findColour (Slider::textBoxBackgroundColourId));
			l->setColour (Label::outlineColourId, slider.findColour (Slider::textBoxOutlineColourId));
			l->setColour (TextEditor::textColourId, slider.findColour (Slider::textBoxTextColourId));
			l->setColour (TextEditor::backgroundColourId, slider.findColour (Slider::textBoxBackgroundColourId).withAlpha (slider.getSliderStyle() == Slider::LinearBar ? 0.7f : 1.0f));
			l->setColour (TextEditor::outlineColourId, slider.findColour (Slider::textBoxOutlineColourId));
			return l;
		}

	private:
		int itemHeight;
		Label overlay;
		CtrlrMenuSliderInternal slider;
		String name;
};

StringArray CtrlrEditor::getMenuBarNames()
{
	const char* const names[] = { "File", "Edit", "View", "Panel", "MIDI", "Programs", "Tools", "Help", nullptr };
	StringArray n(names);
	return (n);
}

PopupMenu CtrlrEditor::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
	ApplicationCommandManager* commandManager = &(owner.getCommandManager());
	PopupMenu menu;

	if (topLevelMenuIndex == 0) // File
	{
		if (!isRestricted())
		{
			menu.addCommandItem (commandManager, doNewPanel);
			menu.addSeparator();
			menu.addCommandItem (commandManager, doOpenPanel);
			menu.addSubMenu ("Open recent", getRecentOpenedFilesMenu(), getRecentOpenedFilesMenu().getNumItems() ? true : false);
			menu.addSeparator();
			menu.addCommandItem (commandManager, doSave);
			menu.addCommandItem (commandManager, doSaveAs);
			menu.addCommandItem (commandManager, doSaveVersioned);

			PopupMenu exportMenu;
			exportMenu.addCommandItem (commandManager, doExportFileText);
			exportMenu.addCommandItem (commandManager, doExportFileZText);
			exportMenu.addCommandItem (commandManager, doExportFileBin);
			exportMenu.addCommandItem (commandManager, doExportFileZBin);
			exportMenu.addCommandItem (commandManager, doExportFileZBinRes);
			exportMenu.addCommandItem (commandManager, doExportFileInstance);
			exportMenu.addCommandItem (commandManager, doExportFileInstanceRestricted);
			exportMenu.addSeparator();
			exportMenu.addCommandItem (commandManager, doExportGenerateUID);
			menu.addSubMenu ("Export", exportMenu);

			menu.addCommandItem (commandManager, doClose);
			menu.addSeparator();
			menu.addCommandItem (commandManager, doSaveState);
		}

		menu.addSeparator();
		menu.addCommandItem (commandManager, doQuit);
	}
	else if (topLevelMenuIndex == 1) // Edit
	{
		menu.addCommandItem (commandManager, doCopy);
		menu.addCommandItem (commandManager, doCut);
		menu.addCommandItem (commandManager, doPaste);
		menu.addSeparator();
		menu.addCommandItem (commandManager, doUndo);
		menu.addCommandItem (commandManager, doRedo);
		menu.addSeparator();
		menu.addCommandItem (commandManager, showKeyboardMappingDialog);
		menu.addCommandItem (commandManager, showGlobalSettingsDialog);
	}
	else if (topLevelMenuIndex == 2) // View
	{
		menu.addCommandItem (commandManager, doZoomIn);
		menu.addCommandItem (commandManager, doZoomOut);
		menu.addSeparator();
		menu.addCommandItem (commandManager, showMidiToolbar);
		menu.addSeparator();
		if (!isRestricted()) menu.addCommandItem (commandManager, doRefreshPropertyLists);
		if (!isRestricted()) menu.addCommandItem (commandManager, doViewPropertyDisplayIDs);
	}
	else if (topLevelMenuIndex == 3 && !isRestricted()) // Panel
	{
		menu.addCommandItem (commandManager, doPanelMode);
		menu.addCommandItem (commandManager, doPanelLock);
		menu.addCommandItem (commandManager, doPanelDisableCombosOnEdit);
		menu.addSeparator();
		menu.addCommandItem (commandManager, showMidiLibrary);
		menu.addCommandItem (commandManager, showModulatorList);
		menu.addSeparator();
		if (!isRestricted()) menu.addCommandItem (commandManager, showLayers);
		menu.addCommandItem (commandManager, showLuaEditor);
		menu.addCommandItem (commandManager, showLuaConsole);
		menu.addCommandItem (commandManager, showBufferEditor);
	}
	else if (topLevelMenuIndex == 4) // MIDI
	{
		menu.addSectionHeader ("Input"+getMidiSummary(CtrlrMidiDeviceManager::inputDevice));
		menu.addSubMenu ("Device", getMidiDeviceMenu(CtrlrMidiDeviceManager::inputDevice), isPanelActive());
		menu.addSubMenu ("Channel", getMidiChannelMenu(CtrlrMidiDeviceManager::inputDevice), isPanelActive());

		menu.addSectionHeader ("Controller"+getMidiSummary(CtrlrMidiDeviceManager::controllerDevice));
		menu.addSubMenu ("Device", getMidiDeviceMenu(CtrlrMidiDeviceManager::controllerDevice), isPanelActive());
		menu.addSubMenu ("Channel", getMidiChannelMenu(CtrlrMidiDeviceManager::controllerDevice), isPanelActive());

		menu.addSectionHeader ("Output "+getMidiSummary(CtrlrMidiDeviceManager::outputDevice));
		menu.addSubMenu ("Device", getMidiDeviceMenu(CtrlrMidiDeviceManager::outputDevice), isPanelActive());
		menu.addSubMenu ("Channel", getMidiChannelMenu(CtrlrMidiDeviceManager::outputDevice), isPanelActive());

		PopupMenu thru;
		thru.addCommandItem (commandManager, optMidiThruD2D);
		thru.addCommandItem (commandManager, optMidiThruD2DChannelize);
		thru.addCommandItem (commandManager, optMidiThruD2H);
		thru.addCommandItem (commandManager, optMidiThruD2HChannelize);
		thru.addCommandItem (commandManager, optMidiThruH2D);
		thru.addCommandItem (commandManager, optMidiThruH2DChannelize);
		thru.addCommandItem (commandManager, optMidiThruH2H);
		thru.addCommandItem (commandManager, optMidiThruH2HChannelize);

		menu.addSubMenu ("MIDI Thru", thru);

		menu.addSectionHeader ("Plugin options");
		menu.addCommandItem (commandManager, optMidiInputFromHost);
		menu.addCommandItem (commandManager, optMidiInputFromHostCompare);
		menu.addCommandItem (commandManager, optMidiOutuptToHost);
		menu.addSubMenu ("Input channel", getMidiChannelMenu(CtrlrMidiDeviceManager::hostInputDevice),		(isPanelActive() && (JUCEApplication::isStandaloneApp() == false)) );
		menu.addSubMenu ("Output channel", getMidiChannelMenu(CtrlrMidiDeviceManager::hostOutputDevice),	(isPanelActive() && (JUCEApplication::isStandaloneApp() == false)) );

		menu.addSectionHeader ("Snapshot options");
		menu.addCommandItem (commandManager, doSendSnapshot);
		menu.addCommandItem (commandManager, optMidiSnapshotOnLoad);
		menu.addCommandItem (commandManager, optMidiSnapshotOnProgramChange);
		menu.addCustomItem (1, new CtrlrMenuSlider(this, "Snapshot delay", getPanelProperty(Ids::panelMidiSnapshotDelay), 0, 2000, 1));
	}
	else if (topLevelMenuIndex == 5) // Programs
	{
		menu.addCommandItem (commandManager, showMidiLibrary);
		menu.addSectionHeader("Local operations");
		menu.addCommandItem (commandManager, doSnapshotStore);
		menu.addCommandItem (commandManager, doSaveSaveToCurrentProgram);
		menu.addCommandItem (commandManager, doSaveSaveToNewProgram);
		menu.addCommandItem (commandManager, doNewBank);

		menu.addSectionHeader ("Request from device");
		menu.addCommandItem (commandManager, doIdentityRequest);
		menu.addCommandItem (commandManager, doEditBufferRequest);
		menu.addCommandItem (commandManager, doCurrentBankRequest);
		menu.addCommandItem (commandManager, doCurrentProgramRequest);
		menu.addCommandItem (commandManager, doAllProgramsRequest);

		if (getActivePanel())
		{
			menu.addSectionHeader ("Custom requests");
			getActivePanel()->getCtrlrMIDILibrary().attachCustomRequests (menu);

			menu.addSectionHeader ("Program change");
			getActivePanel()->getCtrlrMIDILibrary().attachToPopupMenu (menu);
		}
	}
	else if (topLevelMenuIndex == 6) // Tools
	{
		menu.addCommandItem (commandManager, showMidiMonitor);
		menu.addCommandItem (commandManager, showMidiCalculator);
		menu.addCommandItem (commandManager, showLogViewer);
		menu.addCommandItem (commandManager, showComparatorTables);
		menu.addCommandItem (commandManager, doRegisterExtension);
	}
	else if (topLevelMenuIndex == 7) // Help
	{
		menu.addCommandItem (commandManager, showAboutDialog);
		menu.addSeparator();
#ifdef JUCE_DEBUG
		menu.addCommandItem (commandManager, doCrash);
		menu.addCommandItem (commandManager, doDumpVstTables);
#endif
	}

	return menu;
}

void CtrlrEditor::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	/* Some items are not commands, they need to be invoked manualy here */
	//_DBG("CtrlrEditor::menuItemSelected topLevelMenuIndex="+STR(topLevelMenuIndex)+" menuItemID="+STR(menuItemID)+" MENU_OFFSET_MIDI="+STR(MENU_OFFSET_MIDI));

	if (topLevelMenuIndex == 4)
	{
		if (menuItemID >= MENU_OFFSET_MIDI_DEV_IN && menuItemID < MENU_OFFSET_CUSTOM_REQUESTS)
		{
			performMidiDeviceChange(menuItemID);
			return;
		}
		else if (menuItemID >= 0x6100 && menuItemID <= 0x650f)
		{
			performMidiChannelChange(menuItemID);
			return;
		}
		else
		{
			invokeDirectly (menuItemID, true);
			return;
		}
	}
	else if (topLevelMenuIndex == 0)
	{
		if (menuItemID >= 0x9000 && menuItemID < 0x9100)
		{
			performRecentFileOpen (menuItemID);
		}
	}
	else if (topLevelMenuIndex == 5)
	{
		if (menuItemID >= MENU_OFFSET_CUSTOM_REQUESTS && menuItemID < MENU_OFFSET_CUSTOM_REQUESTS+512)
		{
			performCustomRequest (menuItemID);
		}
		else if (menuItemID >= MENU_OFFSET_PROGRAM_LIST)
		{
			performProgramChange(menuItemID);
		}
	}
}

const StringArray CtrlrEditor::getRecentOpenedFilesList()
{
	StringArray recentFiles;
	recentFiles.addTokens (owner.getProperty (Ids::ctrlrRecenetOpenedPanelFiles).toString(), ";", "'\"");

	return (recentFiles);
}

const PopupMenu CtrlrEditor::getRecentOpenedFilesMenu()
{
	PopupMenu m;
	StringArray recentFiles;
	recentFiles.addTokens (owner.getProperty (Ids::ctrlrRecenetOpenedPanelFiles).toString(), ";", "'\"");

	for (int i=0; i<recentFiles.size(); i++)
	{
		m.addItem (0x9000+i, recentFiles[i]);
	}

	return (m);
}

const uint32 CtrlrEditor::getMidiDeviceMenuOffset(const CtrlrMidiDeviceManager::DeviceType type)
{
    switch (type)
    {
        case CtrlrMidiDeviceManager::inputDevice:
            return (MENU_OFFSET_MIDI_DEV_IN);
        case CtrlrMidiDeviceManager::outputDevice:
            return (MENU_OFFSET_MIDI_DEV_OUT);
        case CtrlrMidiDeviceManager::controllerDevice:
            return (MENU_OFFSET_MIDI_DEV_CTRLR);
        case CtrlrMidiDeviceManager::hostInputDevice:
            return (MENU_OFFSET_MIDI_HOST_IN);
        case CtrlrMidiDeviceManager::hostOutputDevice:
            return (MENU_OFFSET_MIDI_HOST_OUT);
    }

    return (0);
}

const Identifier CtrlrEditor::getMidiPropertyName(const CtrlrMidiDeviceManager::DeviceType type)
{
    switch (type)
    {
        case CtrlrMidiDeviceManager::inputDevice:
            return (Ids::panelMidiInputDevice);
        case CtrlrMidiDeviceManager::outputDevice:
            return (Ids::panelMidiOutputDevice);
        case CtrlrMidiDeviceManager::controllerDevice:
            return (Ids::panelMidiControllerDevice);
        case CtrlrMidiDeviceManager::hostInputDevice:
        case CtrlrMidiDeviceManager::hostOutputDevice:
        default:
            break;
    }

    return (Identifier::null);
}

const PopupMenu CtrlrEditor::getMidiDeviceMenu(const CtrlrMidiDeviceManager::DeviceType type)
{
	PopupMenu m;
	Image deviceStateIcon;
    uint32 offset = getMidiDeviceMenuOffset(type);
    const String currentDevName = getPanelProperty(getMidiPropertyName(type));

    m.addItem (offset + 1, COMBO_NONE_ITEM, true, currentDevName == COMBO_NONE_ITEM);

	const StringArray devs = owner.getCtrlrMidiDeviceManager().getManagedDevices(type);
	for (int i=0; i<devs.size(); i++)
	{
		if (currentDevName == devs[i])
		{
				if (owner.getCtrlrMidiDeviceManager().getDeviceByIndex(i, type))
				{
					if (owner.getCtrlrMidiDeviceManager().getDeviceByIndex(i, type)->getState() == false)
						deviceStateIcon = IMAGE(ico_sad_png);
					else
						deviceStateIcon = IMAGE(ico_happy_png);
				}

				m.addItem (offset + 2 + i, devs[i], true, true, deviceStateIcon);
        }
		else
		{
			m.addItem (offset + 2 + i, devs[i], true, false);
		}
	}

	return (m);
}

const PopupMenu CtrlrEditor::getMidiChannelMenu(const CtrlrMidiDeviceManager::DeviceType type)
{
	PopupMenu m;
	if (type == CtrlrMidiDeviceManager::inputDevice)
	{
		for (int i=0; i<17; i++)
		{
			m.addItem (0x6100 + i, (i ? String("Channel: " + String(i)) : "All channels"), true, (int)getPanelProperty(Ids::panelMidiInputChannelDevice) == i);
		}
	}
	else if (type == CtrlrMidiDeviceManager::outputDevice)
	{
		for (int i=1; i<17; i++)
		{
			m.addItem (0x6200 + i, "Channel: " + String(i), true, (int)getPanelProperty(Ids::panelMidiOutputChannelDevice) == i);
		}
	}
	else if (type == CtrlrMidiDeviceManager::controllerDevice)
	{
		for (int i=0; i<17; i++)
		{
			m.addItem (0x6300 + i, (i ? String("Channel: " + String(i)) : "All channels"), true, (int)getPanelProperty(Ids::panelMidiControllerChannelDevice) == i);
		}
	}
	else if (type == CtrlrMidiDeviceManager::hostInputDevice)
	{
		for (int i=0; i<17; i++)
		{
			m.addItem (0x6400 + i, (i ? String("Channel: " + String(i)) : "All channels"), true, (int)getPanelProperty(Ids::panelMidiInputChannelHost) == i);
		}
	}
	else if (type == CtrlrMidiDeviceManager::hostOutputDevice)
	{
		for (int i=1; i<17; i++)
		{
			m.addItem (0x6500 + i, "Channel: " + String(i), true, (int)getPanelProperty(Ids::panelMidiOutputChannelHost) == i);
		}
	}
	return (m);
}

const var CtrlrEditor::getPanelProperty(const Identifier &propertyName)
{
	if (isPanelActive())
	{
		return (getActivePanel()->getProperty(propertyName));
	}
	else
	{
		return (var::null);
	}
}

const String CtrlrEditor::getMidiSummary(const CtrlrMidiDeviceManager::DeviceType type)
{
	if (!isPanelActive())
		return (String::empty);

	String ret = " (";
	if (type == CtrlrMidiDeviceManager::inputDevice)
	{
		ret << (getPanelProperty(Ids::panelMidiInputDevice).toString().isEmpty() ? "No device" : getPanelProperty(Ids::panelMidiInputDevice).toString());
		ret << " / CH:" + String(getActivePanel()->getMidiChannel (panelMidiInputChannelDevice));
	}
	else if (type == CtrlrMidiDeviceManager::outputDevice)
	{
		ret << (getPanelProperty(Ids::panelMidiOutputDevice).toString().isEmpty() ? "No device" : getPanelProperty(Ids::panelMidiOutputDevice).toString());
		ret << " / CH:" + String(getActivePanel()->getMidiChannel (panelMidiOutputChannelDevice));
	}
	else if (type == CtrlrMidiDeviceManager::controllerDevice)
	{
		ret << (getPanelProperty(Ids::panelMidiControllerDevice).toString().isEmpty() ? "No device" : getPanelProperty(Ids::panelMidiControllerDevice).toString());
		ret << " / CH:" + String(getActivePanel()->getMidiChannel (panelMidiControllerChannel));
	}

	ret << ")";
	return (ret);
}
