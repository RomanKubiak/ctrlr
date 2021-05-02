#include "stdafx.h"
#include "CtrlrEditor.h"
#include "CtrlrAbout.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"

class CtrlrMenuSlider : public PopupMenu::CustomComponent, public LookAndFeel_V2
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

		Label* createSliderTextBox (Slider& s)
		{
			Label* const l = new Label();
			l->setFont(LookAndFeel::getDefaultLookAndFeel().getPopupMenuFont().getHeight());
			l->setJustificationType (Justification::centred);
			l->setColour (Label::textColourId, s.findColour (Slider::textBoxTextColourId));
			l->setColour (Label::backgroundColourId, (s.getSliderStyle() == Slider::LinearBar) ? Colours::transparentBlack : s.findColour (Slider::textBoxBackgroundColourId));
			l->setColour (Label::outlineColourId, s.findColour (Slider::textBoxOutlineColourId));
			l->setColour (TextEditor::textColourId, s.findColour (Slider::textBoxTextColourId));
			l->setColour (TextEditor::backgroundColourId, s.findColour (Slider::textBoxBackgroundColourId).withAlpha (s.getSliderStyle() == Slider::LinearBar ? 0.7f : 1.0f));
			l->setColour (TextEditor::outlineColourId, s.findColour (Slider::textBoxOutlineColourId));
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
	StringArray n;

	if (!isRestricted())
	{
		const char* const names[] = { "File", "Edit", "View", "Panel", "MIDI", "Programs", "Tools", "Help", nullptr };
		n = StringArray (names);
	}
	else
	{
		if (hideProgramsMenu)
		{
			const char* const names[] = { "File", "Edit", "View",  "MIDI", "Tools", "Help", nullptr };
			n = StringArray(names);
		}
		else
		{
			const char* const names[] = { "File", "Edit", "View",  "MIDI", "Programs", "Tools", "Help", nullptr };
			n = StringArray(names);
		}
	}

	return (n);
}

PopupMenu CtrlrEditor::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
	ApplicationCommandManager* commandManager = &(owner.getCommandManager());
	PopupMenu menu;

	if (topLevelMenuIndex == MenuFile) // File
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
	else if (topLevelMenuIndex == MenuEdit) // Edit
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
		menu.addSeparator();
		menu.addCommandItem(commandManager, doSearchForProperty);
	}
	else if (topLevelMenuIndex == MenuView) // View
	{
		menu.addCommandItem (commandManager, doZoomIn);
		menu.addCommandItem (commandManager, doZoomOut);
		menu.addSeparator();
		if (!isRestricted()) menu.addCommandItem (commandManager, doRefreshPropertyLists);
		if (!isRestricted()) menu.addCommandItem (commandManager, doViewPropertyDisplayIDs);
        menu.addSeparator();
        if (!isRestricted()) menu.addCommandItem (commandManager, doViewFullScreen);
	}
	else if (!isRestricted() && (topLevelMenuIndex == MenuPanel)) // Panel
	{
		menu.addCommandItem (commandManager, doPanelMode);
		menu.addCommandItem (commandManager, doPanelLock);
		menu.addCommandItem (commandManager, doPanelDisableCombosOnEdit);
		menu.addSeparator();
		menu.addCommandItem (commandManager, showModulatorList);
		menu.addSeparator();
		if (!isRestricted()) menu.addCommandItem (commandManager, showLayers);
		if (!isRestricted()) menu.addCommandItem (commandManager, showLuaEditor);
		if (!isRestricted()) menu.addCommandItem (commandManager, showLuaConsole);
		// menu.addCommandItem (commandManager, showBufferEditor);
	}
	else if ((!isRestricted() && (topLevelMenuIndex == MenuMidi)) || (isRestricted() && (topLevelMenuIndex == MenuRestrictedMidi))) // MIDI
	{
		if(!isRestricted()) menu.addCommandItem(commandManager, doShowMidiSettingsDialog);
		menu.addCommandItem (commandManager, doRefreshDeviceList);
		menu.addSeparator();
		menu.addSectionHeader ("Input"+getMidiSummary(inputDevice));
		menu.addSubMenu ("Device", getMidiDeviceMenu(inputDevice), isPanelActive());
		if (!hideMidiChannelMenu) menu.addSubMenu ("Channel", getMidiChannelMenu(inputDevice), isPanelActive());

		if (!hideMidiControllerMenu)
		{
			menu.addSectionHeader("Controller" + getMidiSummary(controllerDevice));
			menu.addSubMenu("Device", getMidiDeviceMenu(controllerDevice), isPanelActive());
			if (!hideMidiChannelMenu) menu.addSubMenu("Channel", getMidiChannelMenu(controllerDevice), isPanelActive());
		}

		menu.addSectionHeader ("Output "+getMidiSummary(outputDevice));
		menu.addSubMenu ("Device", getMidiDeviceMenu(outputDevice), isPanelActive());
		if (!hideMidiChannelMenu) menu.addSubMenu ("Channel", getMidiChannelMenu(outputDevice), isPanelActive());

		menu.addSeparator();
		if (!hideMidiThruMenu)
		{
			PopupMenu thru;
			thru.addCommandItem(commandManager, optMidiThruD2D);
			thru.addCommandItem(commandManager, optMidiThruD2DChannelize);
			thru.addCommandItem(commandManager, optMidiThruD2H);
			thru.addCommandItem(commandManager, optMidiThruD2HChannelize);
			thru.addCommandItem(commandManager, optMidiThruH2D);
			thru.addCommandItem(commandManager, optMidiThruH2DChannelize);
			thru.addCommandItem(commandManager, optMidiThruH2H);
			thru.addCommandItem(commandManager, optMidiThruH2HChannelize);

			menu.addSubMenu("MIDI Thru", thru);
		}

		if (!JUCEApplication::isStandaloneApp())
		{
			menu.addSectionHeader("Plugin options");
			menu.addCommandItem(commandManager, optMidiInputFromHost);
			menu.addCommandItem(commandManager, optMidiInputFromHostCompare);
			menu.addCommandItem(commandManager, optMidiOutuptToHost);
			menu.addSubMenu("Input channel", getMidiChannelMenu(hostInputDevice), isPanelActive());
			menu.addSubMenu("Output channel", getMidiChannelMenu(hostOutputDevice), isPanelActive());
		}
    }
	else if ((!isRestricted() && (topLevelMenuIndex == MenuPrograms)) || (isRestricted() && !hideProgramsMenu && (topLevelMenuIndex == MenuRestrictedPrograms))) // Programs
	{
		menu.addSectionHeader ("Snapshots");
		menu.addCommandItem (commandManager, doSnapshotStore);
		menu.addCommandItem (commandManager, doSendSnapshot);
		menu.addCommandItem (commandManager, optMidiSnapshotOnLoad);
		menu.addCommandItem (commandManager, optMidiSnapshotOnProgramChange);
		//std::unique_ptr<PopupMenu::CustomComponent> slider;
		//slider.reset (new CtrlrMenuSlider(this, "Snapshot delay", getPanelProperty(Ids::panelMidiSnapshotDelay), 0, 2000, 1));
		//menu.addCustomItem (1, slider);
	}
	else if ((!isRestricted() && (topLevelMenuIndex == MenuTools)) || (isRestricted() && (topLevelMenuIndex == (hideProgramsMenu ? (MenuRestrictedTools - 1) : MenuRestrictedTools)))) // Tools
	{
		menu.addCommandItem (commandManager, showMidiMonitor);
		menu.addCommandItem (commandManager, showMidiCalculator);
		menu.addCommandItem (commandManager, showLogViewer);
		menu.addCommandItem (commandManager, showComparatorTables);
		if(!isRestricted())
		{
			menu.addCommandItem(commandManager, doRegisterExtension);
			menu.addCommandItem(commandManager, doKeyGenerator);
		}
	}
	else if ((!isRestricted() && (topLevelMenuIndex == MenuHelp)) || (isRestricted() && (topLevelMenuIndex == (hideProgramsMenu ? (MenuRestrictedHelp - 1) : MenuRestrictedHelp)))) // Help
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

	if (topLevelMenuIndex == 3 || topLevelMenuIndex == 4)
	{	// This is MIDI menu (3 if Panel menu is hidden, 4 otherwise)
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
			// this causes double invocation BAD
			//invokeDirectly (menuItemID, false);
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

uint32 CtrlrEditor::getMidiDeviceMenuOffset(const CtrlrMIDIDeviceType type)
{
    switch (type)
    {
        case inputDevice:
            return (MENU_OFFSET_MIDI_DEV_IN);
        case outputDevice:
            return (MENU_OFFSET_MIDI_DEV_OUT);
        case controllerDevice:
            return (MENU_OFFSET_MIDI_DEV_CTRLR);
        case hostInputDevice:
            return (MENU_OFFSET_MIDI_HOST_IN);
        case hostOutputDevice:
            return (MENU_OFFSET_MIDI_HOST_OUT);
        case oscInputDevice:
		case oscOutputDevice:
        case serialDevice:
            return (0);
    }

    return (0);
}

const Identifier CtrlrEditor::getMidiPropertyName(const CtrlrMIDIDeviceType type)
{
    switch (type)
    {
        case inputDevice:
            return (Ids::panelMidiInputDevice);
        case outputDevice:
            return (Ids::panelMidiOutputDevice);
        case controllerDevice:
            return (Ids::panelMidiControllerDevice);
        case hostInputDevice:
        case hostOutputDevice:
        default:
            break;
    }

    return (Identifier::null);
}

const PopupMenu CtrlrEditor::getMidiDeviceMenu(const CtrlrMIDIDeviceType type)
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
		    m.addItem (offset + 2 + i, devs[i], true, owner.getCtrlrMidiDeviceManager().getDeviceByIndex(i, type)->getState());
        }
		else
		{
			m.addItem (offset + 2 + i, devs[i], true, false);
		}
	}

	return (m);
}

const PopupMenu CtrlrEditor::getMidiChannelMenu(const CtrlrMIDIDeviceType type)
{
	PopupMenu m;
	if (type == inputDevice)
	{
		for (int i=0; i<17; i++)
		{
			m.addItem (0x6100 + i, (i ? String("Channel: " + String(i)) : "All channels"), true, (int)getPanelProperty(Ids::panelMidiInputChannelDevice) == i);
		}
	}
	else if (type == outputDevice)
	{
		for (int i=1; i<17; i++)
		{
			m.addItem (0x6200 + i, "Channel: " + String(i), true, (int)getPanelProperty(Ids::panelMidiOutputChannelDevice) == i);
		}
	}
	else if (type == controllerDevice)
	{
		for (int i=0; i<17; i++)
		{
			m.addItem (0x6300 + i, (i ? String("Channel: " + String(i)) : "All channels"), true, (int)getPanelProperty(Ids::panelMidiControllerChannelDevice) == i);
		}
	}
	else if (type == hostInputDevice)
	{
		for (int i=0; i<17; i++)
		{
			m.addItem (0x6400 + i, (i ? String("Channel: " + String(i)) : "All channels"), true, (int)getPanelProperty(Ids::panelMidiInputChannelHost) == i);
		}
	}
	else if (type == hostOutputDevice)
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
		return (var());
	}
}

const String CtrlrEditor::getMidiSummary(const CtrlrMIDIDeviceType type)
{
	if (!isPanelActive())
		return ("");

	String ret = " (";
	if (type == inputDevice)
	{
		ret << (getPanelProperty(Ids::panelMidiInputDevice).toString().isEmpty() ? "No device" : getPanelProperty(Ids::panelMidiInputDevice).toString());
		if (!hideMidiChannelMenu)
		{
			ret << " / CH:" + String(getActivePanel()->getMidiChannel(panelMidiInputChannelDevice));
		}
	}
	else if (type == outputDevice)
	{
		ret << (getPanelProperty(Ids::panelMidiOutputDevice).toString().isEmpty() ? "No device" : getPanelProperty(Ids::panelMidiOutputDevice).toString());
		if (!hideMidiChannelMenu)
		{
			ret << " / CH:" + String(getActivePanel()->getMidiChannel(panelMidiOutputChannelDevice));
		}
	}
	else if (type == controllerDevice)
	{
		ret << (getPanelProperty(Ids::panelMidiControllerDevice).toString().isEmpty() ? "No device" : getPanelProperty(Ids::panelMidiControllerDevice).toString());
		if (!hideMidiChannelMenu)
		{
			ret << " / CH:" + String(getActivePanel()->getMidiChannel(panelMidiControllerChannel));
		}
	}

	ret << ")";
	return (ret);
}
