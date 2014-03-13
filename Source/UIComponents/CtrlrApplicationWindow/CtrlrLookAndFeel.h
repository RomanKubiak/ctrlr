#ifndef CTRLR_LOOK_AND_FEEL_H
#define CTRLR_LOOK_AND_FEEL_H

#include "CtrlrMacros.h"

class CtrlrManager;
class CtrlrFontManager;
class CtrlrEditor;
class CtrlrPanelEditor;

class CtrlrMenuBarLookAndFeel : public LookAndFeel_V2
{
	public:
		CtrlrMenuBarLookAndFeel (CtrlrEditor &_owner);
		void setPanel(CtrlrPanel *_panel);
		void drawPopupMenuBackground (Graphics &g, int width, int height);
		void drawPopupMenuItem (Graphics &g, int width, int height, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const String &text, const String &shortcutKeyText, Image *image, const Colour *textColourToUse);
		Font getPopupMenuFont ();
		void drawPopupMenuUpDownArrow (Graphics &g, int width, int height, bool isScrollUpArrow);
		void getIdealPopupMenuItemSize (const String &text, bool isSeparator, int standardMenuItemHeight, int &idealWidth, int &idealHeight);
		int getMenuWindowFlags();
		void drawMenuBarBackground (Graphics &g, int width, int height, bool isMouseOverBar, MenuBarComponent &menuBar);
		void drawShinyButtonShape (Graphics& g, float x, float y, float w, float h, float maxCornerSize, const Colour& baseColour, const float strokeWidth, const bool flatOnLeft, const bool flatOnRight, const bool flatOnTop, const bool flatOnBottom) noexcept;
		int getMenuBarItemWidth (MenuBarComponent &menuBar, int itemIndex, const String &itemText);
		Font getMenuBarFont (MenuBarComponent &menuBar, int itemIndex, const String &itemText);
		void drawMenuBarItem (Graphics &g, int width, int height, int itemIndex, const String &itemText, bool isMouseOverItem, bool isMenuOpen, bool isMouseOverBar, MenuBarComponent &menuBar);
		Colour getColour (const Identifier &property);
		Font getFont(const Identifier &property);

	private:
		WeakReference <CtrlrPanel> panel;
		CtrlrEditor &owner;
};

class CtrlrLookAndFeel : public LookAndFeel_V3
{
	public:
		CtrlrLookAndFeel(CtrlrManager &_owner);
		void drawPopupMenuBackground (Graphics &g, int width, int height);
		void drawMenuBarBackground (Graphics &g, int width, int height, bool isMouseOverBar, MenuBarComponent &menuBar);
		Font getMenuBarFont (MenuBarComponent &menuBar, int itemIndex, const String &itemText);
		Font getPopupMenuFont();
		void drawMenuBarItem (Graphics &g, int width, int height, int itemIndex, const String &itemText, bool isMouseOverItem, bool isMenuOpen, bool isMouseOverBar, MenuBarComponent &menuBar);
		void drawPopupMenuItem (Graphics& g, int width, int height, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const String& text, const String& shortcutKeyText, Image* image, const Colour *textColourToUses);
		CtrlrFontManager &getFontManager();
		void setActivePanelEditor(CtrlrPanelEditor *_editor);
		void drawBubble (Graphics &g, BubbleComponent&, const Point<float>& tip, const juce::Rectangle<float>& body);
		int getSliderPopupPlacement(Slider &);
		Font getSliderPopupFont(Slider &);
		void drawSliderPopup(Graphics&, const String &text, int width, int height);
		void drawStretchableLayoutResizerBar (Graphics &, int w, int h, bool isVerticalBar, bool isMouseOver, bool isMouseDragging);
		const var getPanelProperty(const Identifier &identifier, const var defaultValue);
		void setUsingNativeAlerts(const bool useNativeDialogs);
		bool areScrollbarButtonsVisible()        { return true; }
		void drawScrollbar (Graphics& g, ScrollBar& scrollbar, int x, int y, int width, int height, bool isScrollbarVertical, int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown);
	private:
		bool mark;
		WeakReference <CtrlrPanelEditor> editor;
		CtrlrManager &owner;
};

#endif
