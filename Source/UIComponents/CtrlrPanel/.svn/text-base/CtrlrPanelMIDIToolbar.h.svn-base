#ifndef CTRLR_PANEL_MIDI_TOOLBAR
#define CTRLR_PANEL_MIDI_TOOLBAR

#include "CtrlrMacros.h"
#include "CtrlrInlineUtilitiesGUI.h"
#include "CtrlrMIDILibrary/CtrlrMIDILibrary.h"
#include "CtrlrApplicationWindow/CtrlrEditor.h"
#include "CtrlrMidiDeviceManager.h"

class CtrlrPanelEditor;
class CtrlrPanelMIDIToolbar;

class CtrlrPanelMIDIToolbarGroup : public ToolbarItemComponent, public Button::Listener, public CtrlrMIDILibrary::Listener
{
	public:
		CtrlrPanelMIDIToolbarGroup (const int _itemId, const String &_itemName, CtrlrPanelMIDIToolbar &_owner, const int _numSubItems=4);
		void contentAreaChanged (const Rectangle <int> &newBounds);
		void paintButtonArea (Graphics &g, int width, int height, bool isMouseOver, bool isMouseDown);
		void paintButton (Graphics &g, bool isMouseOver, bool isMouseDown);
		bool getToolbarItemSizes (int toolbarThickness, bool isToolbarVertical, int &preferredSize, int &minSize, int &maxSize);
		void setHasCombo (const bool _hasCombo);
		const bool getHasCombo()					{ return (hasCombo); 	}
		void addButton(const Image &iconToUse, const String &tooltip=String::empty, const int subItemId = -1,  const Colour overlayColour=Colours::transparentBlack);
		Font getLabelFont(bool isMouseOver);
        void mouseDown (const MouseEvent &e);
        void mouseEnter (const MouseEvent &e);
        void mouseExit (const MouseEvent &e);
		void buttonClicked (Button *button);
		void setText (const String &text);
		void programListChanged();
		void bankListChanged();
		void snapshotListChanged();

		JUCE_LEAK_DETECTOR(CtrlrPanelMIDIToolbarGroup)

	private:
		Label bottomLabel;
		CtrlrPanelMIDIToolbar &owner;
		String itemName;
		int itemId;
		int numSubItems;
		bool hasCombo;
		OwnedArray <ImageButton> buttons;
};

class CtrlrPanelMIDIToolbarButton : public ToolbarButton
{
	public:
		CtrlrPanelMIDIToolbarButton (const int _itemId, const String &_itemName, CtrlrPanelMIDIToolbar &_owner, Drawable *normal, Drawable *toggled);
		void paintButtonArea (Graphics &g, int width, int height, bool isMouseOver, bool isMouseDown);
		void paintButton (Graphics &g, bool isMouseOver, bool isMouseDown);
};

class CtrlrPanelMIDIToolbar : public Toolbar, public ToolbarItemFactory, public LookAndFeel_V3
{
	public:
		enum ToolbarItems
		{
			none,
			ProgramGroup,
			BankGroup,
			SnapshotGroup,
			MiscGroup,
			OptionsGroup
		};

		enum ToolbarGroupItems
		{
			ButtonSave,
			ButtonNew,
			ButtonSend,
			ButtonReceive,
			ButtonDelete,
			ButtonMisc1,
			ButtonMisc2,
			ButtonMisc3,
			ButtonMisc4
		};

		CtrlrPanelMIDIToolbar(CtrlrPanelEditor &_owner);
		~CtrlrPanelMIDIToolbar();
		void paint(Graphics &g);
		void getAllToolbarItemIds (Array< int > &ids);
		void getDefaultItemSet (Array< int > &ids);
		ToolbarItemComponent *createItem (int itemId);
		CtrlrMIDILibrary &getLibrary();
		String getItemName(const int itemId);
		Image getItemIcon(const int itemId);
		Drawable *getDrawableImage(const int itemId);
		PopupMenu getMenuForItem (const int itemId = -1);
		void paintToolbarButtonBackground (Graphics &g, int width, int height, bool isMouseOver, bool isMouseDown, ToolbarItemComponent &component);
		void paintToolbarButtonLabel (Graphics &g, int x, int y, int width, int height, const String &text, ToolbarItemComponent &component);
		void comboChanged (const int itemId, const int menuItemId);
		void buttonClicked (Button *button, const int itemId, const int buttonItemId);
		void midiLibraryOptionsMenu(Button *button);
		void midiOutputDeviceMenu(Button *button);
		void midiInputDeviceMenu(Button *button);

		JUCE_LEAK_DETECTOR(CtrlrPanelMIDIToolbar)

	private:
		CtrlrPanelEditor &owner;
};

#endif
