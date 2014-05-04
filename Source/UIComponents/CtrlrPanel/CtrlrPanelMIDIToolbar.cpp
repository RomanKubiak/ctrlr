#include "stdafx.h"
#include "CtrlrPanelMIDIToolbar.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrApplicationWindow/CtrlrEditor.h"
#include "CtrlrInlineUtilitiesGUI.h"
#include "CtrlrMIDILibrary/CtrlrMIDILibrary.h"

#define _ICON_HEIGHT 	(CTRLR_TOOLBAR_HEIGHT * 0.55f)
#define _LABEL_HEIGHT	(CTRLR_TOOLBAR_HEIGHT * 0.33f)

CtrlrPanelMIDIToolbarGroup::CtrlrPanelMIDIToolbarGroup (const int _itemId, const String &_itemName, CtrlrPanelMIDIToolbar &_owner, const int _numSubItems)
	:	owner(_owner),
		itemId(_itemId),
		itemName(_itemName),
		numSubItems(_numSubItems),
		ToolbarItemComponent(_itemId, _itemName, true),
		hasCombo(false)
{
	owner.getLibrary().addListener (this);
	setHasCombo (false);

	bottomLabel.addMouseListener (this, false);
	bottomLabel.setJustificationType (Justification::bottomLeft);
	bottomLabel.setText (itemName, dontSendNotification);

	addAndMakeVisible (&bottomLabel);
	setTooltip (String::empty);
	programListChanged();
}

void CtrlrPanelMIDIToolbarGroup::contentAreaChanged (const Rectangle <int> &newBounds)
{
	bottomLabel.setBounds (0, newBounds.getY() +_ICON_HEIGHT, newBounds.getWidth(), _LABEL_HEIGHT);

	for (int i=0; i<buttons.size(); i++)
	{
		buttons[i]->setBounds(2 + (i*_ICON_HEIGHT), 2 + newBounds.getY(), _ICON_HEIGHT - 4, _ICON_HEIGHT - 4);
	}
}

void CtrlrPanelMIDIToolbarGroup::paintButtonArea (Graphics &g, int width, int height, bool isMouseOver, bool isMouseDown)
{
}

void CtrlrPanelMIDIToolbarGroup::paintButton (Graphics &g, bool isMouseOver, bool isMouseDown)
{
}

bool CtrlrPanelMIDIToolbarGroup::getToolbarItemSizes (int toolbarThickness, bool isToolbarVertical, int &preferredSize, int &minSize, int &maxSize)
{
	preferredSize = minSize = maxSize = CTRLR_TOOLBAR_HEIGHT * numSubItems;
	return (true);
}

void CtrlrPanelMIDIToolbarGroup::addButton(const Image &iconToUse, const String &tooltip, const int subItemId, const Colour overlayColour)
{
	ImageButton *b = new ImageButton ();
	b->setImages (true, true, true, iconToUse, 0.35f, overlayColour, iconToUse, 0.65f, overlayColour, iconToUse, 1.0f, overlayColour);
	b->setTooltip (tooltip);
	b->addListener (this);
	b->addMouseListener (this, true);
	b->getProperties().set("subItemId", subItemId);
	addAndMakeVisible (b);
	buttons.add (b);
}

void CtrlrPanelMIDIToolbarGroup::setText (const String &text)
{
	if (text.isEmpty())
	{
		bottomLabel.setColour (Label::textColourId, Colours::black.withAlpha(0.3f));
		bottomLabel.setText (itemName, dontSendNotification);
	}
	else
	{
		bottomLabel.setColour (Label::textColourId, Colours::black);
		bottomLabel.setText ("> "+text, dontSendNotification);
	}
}

void CtrlrPanelMIDIToolbarGroup::setHasCombo (const bool _hasCombo)
{
	hasCombo = _hasCombo;
	if (hasCombo)
	{
		bottomLabel.setColour (Label::textColourId, Colours::black.withAlpha(0.7f));
		bottomLabel.setMouseCursor (MouseCursor::PointingHandCursor);
		bottomLabel.setFont (getLabelFont(false));
	}
	else
	{
		bottomLabel.setColour (Label::textColourId, Colours::black.withAlpha(0.9f));
		bottomLabel.setMouseCursor (MouseCursor::ParentCursor);
		bottomLabel.setFont (getLabelFont(false));
	}
}

Font CtrlrPanelMIDIToolbarGroup::getLabelFont(bool isMouseOver)
{
	if (isMouseOver)
	{
		return (Font(_LABEL_HEIGHT*0.7f, Font::bold|Font::underlined));
	}
	else
	{
		return (Font(_LABEL_HEIGHT*0.7f, Font::bold));
	}
}

void CtrlrPanelMIDIToolbarGroup::mouseDown (const MouseEvent &e)
{
	if (e.eventComponent == &bottomLabel && hasCombo)
	{
		PopupMenu m = owner.getMenuForItem (itemId);
		const int ret = m.showAt(e.eventComponent);
		if (ret >= 1)
			owner.comboChanged (itemId, ret - 1);
	}
}

void CtrlrPanelMIDIToolbarGroup::mouseEnter (const MouseEvent &e)
{
	if (e.eventComponent == &bottomLabel && hasCombo)
	{
		bottomLabel.setFont (getLabelFont(true));
	}
}

void CtrlrPanelMIDIToolbarGroup::mouseExit (const MouseEvent &e)
{
	if (e.eventComponent == &bottomLabel && hasCombo)
	{
		bottomLabel.setFont (getLabelFont(false));
	}
}

void CtrlrPanelMIDIToolbarGroup::buttonClicked (Button *button)
{
	ImageButton *ib = dynamic_cast<ImageButton*>(button);

	if (ib != nullptr)
	{
		if (buttons.indexOf (ib) >= 0)
		{
			owner.buttonClicked (button, itemId, ib->getProperties().getWithDefault("subItemId", -1));
		}
	}
}

void CtrlrPanelMIDIToolbarGroup::programListChanged()
{
	switch (itemId)
	{
		case CtrlrPanelMIDIToolbar::ProgramGroup:
			setText (owner.getLibrary().getCurrentProgram().getProperty(Ids::name));
			break;

		case CtrlrPanelMIDIToolbar::BankGroup:
			setText (owner.getLibrary().getCurrentBankName());
			break;

		case CtrlrPanelMIDIToolbar::SnapshotGroup:
			setText (owner.getLibrary().getCurrentSnapshot().getProperty(Ids::name));
			break;

		default:
			break;
	}
}

/**
 *
 */
CtrlrPanelMIDIToolbarButton::CtrlrPanelMIDIToolbarButton(const int _itemId, const String &_itemName, CtrlrPanelMIDIToolbar &_owner, Drawable *normal, Drawable *toggled)
	: ToolbarButton (_itemId, _itemName, normal, toggled)
{
}

void CtrlrPanelMIDIToolbarButton::paintButtonArea (Graphics &g, int width, int height, bool isMouseOver, bool isMouseDown)
{
}

void CtrlrPanelMIDIToolbarButton::paintButton (Graphics &g, bool isMouseOver, bool isMouseDown)
{
	g.fillAll (Colours::red);
}

/**
 *
 */
CtrlrPanelMIDIToolbar::CtrlrPanelMIDIToolbar(CtrlrPanelEditor &_owner) : owner(_owner)
{
	setLookAndFeel (this);
	setStyle (Toolbar::iconsOnly);
	addDefaultItems (*this);
}

CtrlrPanelMIDIToolbar::~CtrlrPanelMIDIToolbar()
{
}

CtrlrMIDILibrary &CtrlrPanelMIDIToolbar::getLibrary()
{
	return (owner.getOwner().getCtrlrMIDILibrary());
}

void CtrlrPanelMIDIToolbar::paint(Graphics &g)
{
	if (owner.getOwner().getOwner().getEditor())
	{
		CtrlrMenuBarLookAndFeel *lf = owner.getOwner().getOwner().getEditor()->getMenuBarLookAndFeel();

		drawCtrlrMenuBarBackground (g, getWidth(), getHeight(), false, lf->getColour(Ids::ctrlrMenuBarBackgroundColour1), lf->getColour(Ids::ctrlrMenuBarBackgroundColour2));
	}
}

void CtrlrPanelMIDIToolbar::getAllToolbarItemIds (Array <int> &ids)
{
	const int i[] = {
			separatorBarId,
			spacerId,
			flexibleSpacerId,
			ProgramGroup,
			BankGroup,
			SnapshotGroup,
			OptionsGroup,
			MiscGroup
	};

	ids.addArray (i, numElementsInArray (i));
}

void CtrlrPanelMIDIToolbar::getDefaultItemSet (Array <int> &ids)
{
	const int i[] = {
			OptionsGroup,
			separatorBarId,
			ProgramGroup,
			separatorBarId,
			BankGroup,
			separatorBarId,
			SnapshotGroup,
			separatorBarId,
			MiscGroup
	};

	ids.addArray (i, numElementsInArray (i));
}

ToolbarItemComponent *CtrlrPanelMIDIToolbar::createItem (int itemId)
{
	CtrlrPanelMIDIToolbarGroup *g = nullptr;

	switch (itemId)
	{
		case BankGroup:
			g = new CtrlrPanelMIDIToolbarGroup (itemId, getItemName (itemId), *this, 3);
			g->setText (getLibrary().getCurrentBank().getProperty(Ids::name));
			g->addButton (IMAGE(ico_document_new_png), "New", ButtonNew);
			g->addButton (IMAGE(ico_delete_png), "Delete", ButtonDelete);
			break;

		case ProgramGroup:
			g = new CtrlrPanelMIDIToolbarGroup (itemId, getItemName (itemId), *this, 4);
			g->setText (getLibrary().getCurrentProgram().getProperty(Ids::name));
			g->addButton (IMAGE(ico_file_png), "Save", ButtonSave);
			g->addButton (IMAGE(ico_document_new_png), "New", ButtonNew);
			g->addButton (IMAGE(ico_delete_png), "Delete", ButtonDelete);
			break;

		case SnapshotGroup:
			g = new CtrlrPanelMIDIToolbarGroup (itemId, getItemName (itemId), *this, 4);
			g->setText (getLibrary().getCurrentSnapshot().getProperty(Ids::name));
			g->addButton (IMAGE(ico_snapshot_png), "Snapshot", ButtonNew);
			g->addButton (IMAGE(ico_delete_png), "Delete", ButtonDelete);
			break;

		case OptionsGroup:
			g = new CtrlrPanelMIDIToolbarGroup (itemId, getItemName (itemId), *this, 4);
			g->setHasCombo (false);
			g->addButton (IMAGE(ico_gui_png), "Library window", ButtonMisc1);
			g->addButton (IMAGE(ico_unit_png), "Options", ButtonMisc2);
			g->addButton (IMAGE(ico_midi_plug_out_png), "MIDI Output", ButtonMisc3, Colours::transparentBlack);
			g->addButton (IMAGE(ico_midi_plug_in_png), "MIDI Input", ButtonMisc4, Colours::transparentBlack);
			return (g);

		case MiscGroup:
			g = new CtrlrPanelMIDIToolbarGroup (itemId, getItemName (itemId), *this, 3);
            return (g);

		default:
			break;
	}

	if (g != nullptr)
	{
		g->addButton (IMAGE(ico_receive_png), "Receive", ButtonReceive);
		g->addButton (IMAGE(ico_send_png), "Send", ButtonSend);
		g->setHasCombo (true);
	}

	return (g);
}

String CtrlrPanelMIDIToolbar::getItemName(const int itemId)
{
	switch (itemId)
	{
		case ProgramGroup:
			return ("Program");
		case BankGroup:
			return ("Bank");
		case SnapshotGroup:
			return ("Snapshot");
		case OptionsGroup:
			return ("Options");
		case MiscGroup:
			return ("Misc");
		default:
			break;
	}

	return (String::empty);
}

Image CtrlrPanelMIDIToolbar::getItemIcon(const int itemId)
{
	return (Image::null);
}

Drawable *CtrlrPanelMIDIToolbar::getDrawableImage(const int itemId)
{
	DrawableImage *di = new DrawableImage();
	di->setImage (getItemIcon(itemId));
	return (di);
}

void CtrlrPanelMIDIToolbar::paintToolbarButtonBackground (Graphics &g, int width, int height, bool isMouseOver, bool isMouseDown, ToolbarItemComponent &component)
{
	if (isMouseDown)
	{
		drawSelectionRectangle (g, 1, 1, width - 2, height - 2, component.findColour (Toolbar::buttonMouseDownBackgroundColourId, true), 0.9f);
	}
    else if (isMouseOver)
	{
		drawSelectionRectangle (g, 1, 1, width - 2, height - 2, component.findColour (Toolbar::buttonMouseOverBackgroundColourId, true), 0.5f);
	}
}

void CtrlrPanelMIDIToolbar::paintToolbarButtonLabel (Graphics &g, int x, int y, int width, int height, const String &text, ToolbarItemComponent &component)
{
	g.setColour (component.findColour (Toolbar::labelTextColourId, true).withAlpha (component.isEnabled() ? 1.0f : 0.25f));

    const float fontHeight = jmin (14.0f, height * 0.75f);
    g.setFont (Font (fontHeight, Font::bold));
    g.drawFittedText (text, x, y, width, height, Justification::centred, jmax (1, height / (int) fontHeight));
}

PopupMenu CtrlrPanelMIDIToolbar::getMenuForItem (const int itemId)
{
	PopupMenu m;
	switch (itemId)
	{
		case ProgramGroup:
			return (getLibrary().getProgramMenu());
		case BankGroup:
			return (getLibrary().getBankMenu());
		case SnapshotGroup:
			return (getLibrary().getSnapshotMenu());
		default:
			break;
	}
	return (m);
}

void CtrlrPanelMIDIToolbar::comboChanged (const int itemId, const int menuItemId)
{
	switch (itemId)
	{
		case BankGroup:
			getLibrary().setCurrentBankFromMenu (menuItemId);
			break;
		case ProgramGroup:
			getLibrary().setCurrentProgramFromMenu (menuItemId);
			break;
		case SnapshotGroup:
			getLibrary().setCurrentSnapshotFromMenu (menuItemId);
			break;
		default:
			break;
	}
}

void CtrlrPanelMIDIToolbar::buttonClicked (Button *button, const int itemId, const int buttonId)
{
	//_DBG("CtrlrPanelMIDIToolbar::buttonClicked buttonId="+STR(buttonId));
	switch (itemId)
	{
		case ProgramGroup:
			switch (buttonId)
			{
				case ButtonNew:
					getLibrary().addNewProgram (String::empty, -1);
					break;

				case ButtonSave:
					getLibrary().savePanelStateToCurrentProgram();
					break;

				case ButtonDelete:
					getLibrary().deleteCurrentProgram();
					break;

				case ButtonSend:
					break;

				case ButtonReceive:
					break;

				default:
					break;
			}
			break;

		case BankGroup:
			switch (buttonId)
			{
				case ButtonNew:
					getLibrary().addNewBank(String::empty, String::empty, -1, -1, -1);

				case ButtonDelete:
					getLibrary().deleteCurrentBank();
					break;

				default:
					break;
			}
			break;

		case SnapshotGroup:
			switch (buttonId)
			{
				case ButtonNew:
                    getLibrary().snapshot();
                    break;
				case ButtonDelete:
					getLibrary().deleteCurrentSnapshot();
					break;

				default:
					break;
			}
			break;

		case OptionsGroup:
			switch (buttonId)
			{
				case ButtonMisc1:
                    owner.getOwner().getOwner().getCommandManager().invokeDirectly (CtrlrEditor::showMidiLibrary, true);
                    break;

				case ButtonMisc2:
					midiLibraryOptionsMenu(button);
					break;

				case ButtonMisc3:
					midiOutputDeviceMenu(button);
					break;

				case ButtonMisc4:
					midiInputDeviceMenu(button);
					break;
			}
			break;
	}
}

void CtrlrPanelMIDIToolbar::midiLibraryOptionsMenu(Button *button)
{
	PopupMenu m;
	m.addSectionHeader ("Library options");
	m.addItem (1, "Send \"MIDI Snapshot\" after changing programs", true, (bool)getLibrary().getProperty(Ids::midiLibrarySendSnapAfterPChg));
	m.addItem (2, "Send \"MIDI program change\" after changing programs", true, (bool)getLibrary().getProperty(Ids::midiLibraryMidiProgramChangeControl));
	const int ret = m.showAt(button);
	if (ret == 1)
		getLibrary().setProperty (Ids::midiLibrarySendSnapAfterPChg, !(bool)getLibrary().getProperty(Ids::midiLibrarySendSnapAfterPChg));
	if (ret == 2)
		getLibrary().setProperty (Ids::midiLibraryMidiProgramChangeControl, !(bool)getLibrary().getProperty(Ids::midiLibraryMidiProgramChangeControl));
}

void CtrlrPanelMIDIToolbar::midiOutputDeviceMenu(Button *button)
{
	PopupMenu m;
	StringArray dev = owner.getOwner().getOwner().getCtrlrMidiDeviceManager().getManagedDevices (CtrlrMidiDeviceManager::outputDevice);

	m.addItem (1, "-- None", true, owner.getOwner().getProperty(Ids::panelMidiOutputDevice).toString().isEmpty() || (owner.getOwner().getProperty(Ids::panelMidiOutputDevice).toString() == COMBO_ITEM_NONE));

	for (int i=0; i<dev.size(); i++)
	{
		m.addItem (i+2, dev[i], true, owner.getOwner().getProperty(Ids::panelMidiOutputDevice) == dev[i]);
	}
	const int ret = m.showAt(button);
	if (ret > 1)
	{
		owner.getOwner().setProperty(Ids::panelMidiOutputDevice, dev[ret-2]);
	}
}

void CtrlrPanelMIDIToolbar::midiInputDeviceMenu(Button *button)
{
	PopupMenu m;
	StringArray dev = owner.getOwner().getOwner().getCtrlrMidiDeviceManager().getManagedDevices (CtrlrMidiDeviceManager::inputDevice);

	m.addItem (1, "-- None", true, owner.getOwner().getProperty(Ids::panelMidiInputDevice).toString().isEmpty() || (owner.getOwner().getProperty(Ids::panelMidiInputDevice).toString() == COMBO_ITEM_NONE));

	for (int i=0; i<dev.size(); i++)
	{
		m.addItem (i+2, dev[i], true, owner.getOwner().getProperty(Ids::panelMidiInputDevice) == dev[i]);
	}

	const int ret = m.showAt(button);
	if (ret > 1)
	{
		owner.getOwner().setProperty(Ids::panelMidiInputDevice, dev[ret-2]);
	}
}
