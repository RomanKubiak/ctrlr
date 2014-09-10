#ifndef L_LOOK_AND_FEEL
#define L_LOOK_AND_FEEL

#include "CtrlrLuaManager.h"
#include "CtrlrLog.h"

struct DrawFileBrowserRowParams
{
	DrawFileBrowserRowParams(Graphics &_g,
							int _width,
							int _height,
							const String &_filename,
							Image *_icon,
							const String &_fileSizeDescription,
							const String &_fileTimeDescription,
							bool _isDirectory,
							bool _isItemSelected,
							int _itemIndex,
							DirectoryContentsDisplayComponent &_component)
		:	g(_g), width(_width), height(_height), filename(_filename), icon(_icon), fileSizeDescription(_fileSizeDescription),
			fileTimeDescription(_fileTimeDescription), isDirectory(_isDirectory), isItemSelected(_isItemSelected),
			itemIndex(_itemIndex), component(_component) {}
    Graphics &g;
    int width;
    int height;
    const String &filename;
    Image *icon;
    const String &fileSizeDescription;
    const String &fileTimeDescription;
    bool isDirectory;
    bool isItemSelected;
    int itemIndex;
    DirectoryContentsDisplayComponent &component;
};

struct DrawPopupMenuItemParams
{
    DrawPopupMenuItemParams(Graphics &_g,
                            const Rectangle<int> &_area,
                            bool _isSeparator,
                            bool _isActive,
                            bool _isHighlighted,
                            bool _isTicked,
                            bool _hasSubMenu,
                            const String &_text,
                            const String &_shortcutKeyText,
                            const Drawable *_icon,
                            const Colour *_textColour)
        : g(_g), area(_area), isSeparator(_isSeparator), isActive(_isActive), isHighlighted(_isHighlighted),
            isTicked(_isTicked), hasSubMenu(_hasSubMenu), text(_text),
            shortcutKeyText(_shortcutKeyText), icon(_icon), textColour(_textColour)
            {}
    Graphics &g;
    const Rectangle<int> &area;
    bool isSeparator;
    bool isActive;
    bool isHighlighted;
    bool isTicked;
    bool hasSubMenu;
    const String &text;
    const String &shortcutKeyText;
    const Drawable *icon;
    const Colour *textColour;
};

class LLookAndFeel_V3 : public LookAndFeel_V3, public luabind::wrap_base
{
	public:
	    LLookAndFeel_V3() : LookAndFeel_V3() {}
		static void wrapForLua (lua_State *L);

        virtual Colour findColour (int colourId)
        { return (call<Colour>("findColour", colourId)); }
        static Colour def_findColour (LookAndFeel_V3 *ptr, int colourId)
        { return (ptr->LookAndFeel_V3::findColour (colourId)); }

        virtual void setColour (int colourId, Colour colour)
        { call<void>("setColour", colourId, colour); }
        static void def_setColour (LookAndFeel_V3 *ptr, int colourId, Colour colour)
        { return (ptr->LookAndFeel_V3::setColour (colourId, colour)); }

        virtual bool isColourSpecified (int colourId)
        { return (call<bool>("isColourSpecified", colourId)); }
        static bool def_isColourSpecified (LookAndFeel_V3 *ptr, int colourId)
        { return (ptr->LookAndFeel_V3::isColourSpecified (colourId)); }

        virtual Typeface::Ptr getTypefaceForFont (const Font &font) override
        { return (call<Typeface::Ptr>("getTypefaceForFont", font)); }
        static Typeface::Ptr def_getTypefaceForFont (LookAndFeel_V3 *ptr, const Font &font)
        { return (ptr->LookAndFeel_V3::getTypefaceForFont (font)); }

        virtual MouseCursor getMouseCursorFor (Component &component) override
        { try { MouseCursor mc (call<MouseCursor>("getMouseCursorFor", boost::ref(component))); return (mc); } catch (...) { return (component.getMouseCursor()); } }
        static MouseCursor def_getMouseCursorFor (LookAndFeel_V3 *ptr, Component &component)
        { return (ptr->LookAndFeel_V3::getMouseCursorFor (component)); }

		virtual void drawButtonBackground (Graphics &g, Button &b, const Colour &c, bool over, bool down) override
        { call<void>("drawButtonBackground", boost::ref (g), boost::ref(b), c, over, down); }
        static void def_drawButtonBackground (LookAndFeel_V3 *ptr, Graphics &g, Button &b, const Colour &c, bool over, bool down)
        { return (ptr->LookAndFeel_V3::drawButtonBackground (g,b,c,over,down)); }

        virtual void drawButtonText (Graphics &g, TextButton &button, bool isMouseOverButton, bool isButtonDown) override
        { call<void>("drawButtonText", boost::ref(g), boost::ref(button), isMouseOverButton, isButtonDown); }
        static void def_drawButtonText (LookAndFeel_V3 *ptr, Graphics &g, TextButton &button, bool isMouseOverButton, bool isButtonDown)
        { return (ptr->LookAndFeel_V3::drawButtonText (g, button, isMouseOverButton, isButtonDown)); }

        virtual void drawToggleButton (Graphics &g, ToggleButton &button, bool isMouseOverButton, bool isButtonDown) override
        { call<void>("drawToggleButton", boost::ref(g), boost::ref(button), isMouseOverButton, isButtonDown); }
        static void def_drawToggleButton (LookAndFeel_V3 *ptr, Graphics &g, ToggleButton &button, bool isMouseOverButton, bool isButtonDown)
        { return (ptr->LookAndFeel_V3::drawToggleButton (g, button, isMouseOverButton, isButtonDown)); }

        virtual void changeToggleButtonWidthToFitText (ToggleButton &button) override
        { call<void>("changeToggleButtonWidthToFitText", boost::ref(button)); }
        static void def_changeToggleButtonWidthToFitText (LookAndFeel_V3 *ptr, ToggleButton &button)
        { return (ptr->LookAndFeel_V3::changeToggleButtonWidthToFitText (button)); }

        virtual void drawTickBox (Graphics &g, Component &component, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown) override
        { call<void>("drawTickBox", boost::ref(g), boost::ref(component), x, y, w, h, ticked, isEnabled, isMouseOverButton, isButtonDown); }
        static void def_drawTickBox (LookAndFeel_V3 *ptr, Graphics &g, Component &component, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown)
        { return (ptr->LookAndFeel_V3::drawTickBox (g, component, x, y, w, h, ticked, isEnabled, isMouseOverButton, isButtonDown)); }

        virtual AlertWindow *createAlertWindow (const String &title, const String &message, const String &button1, const String &button2, const String &button3, AlertWindow::AlertIconType iconType, int numButtons, Component *associatedComponent) override
        { return (call<AlertWindow *>("createAlertWindow", title, message, button1, button2, button3, iconType, numButtons, associatedComponent)); }
        static AlertWindow * def_createAlertWindow (LookAndFeel_V3 *ptr, const String &title, const String &message, const String &button1, const String &button2, const String &button3, AlertWindow::AlertIconType iconType, int numButtons, Component *associatedComponent)
        { return (ptr->LookAndFeel_V3::createAlertWindow (title, message, button1, button2, button3, iconType, numButtons, associatedComponent)); }

        virtual void drawAlertBox (Graphics &g, AlertWindow &window, const Rectangle<int> &textArea, TextLayout &layout) override
        { call<void>("drawAlertBox", boost::ref(g), boost::ref(window), textArea, layout); }
        static void def_drawAlertBox (LookAndFeel_V3 *ptr, Graphics &g, AlertWindow &window, const Rectangle<int> &textArea, TextLayout &layout)
        { return (ptr->LookAndFeel_V3::drawAlertBox (g, window, textArea, layout)); }

        virtual int getAlertBoxWindowFlags () override
        { return (call<int>("getAlertBoxWindowFlags")); }
        static int def_getAlertBoxWindowFlags (LookAndFeel_V3 *ptr)
        { return (ptr->LookAndFeel_V3::getAlertBoxWindowFlags ()); }

        virtual int getAlertWindowButtonHeight () override
        { return (call<int>("getAlertWindowButtonHeight")); }
        static int def_getAlertWindowButtonHeight (LookAndFeel_V3 *ptr)
        { return (ptr->LookAndFeel_V3::getAlertWindowButtonHeight ()); }

        virtual Font getAlertWindowMessageFont () override
        { return (call<Font>("getAlertWindowMessageFont")); }
        static Font def_getAlertWindowMessageFont (LookAndFeel_V3 *ptr)
        { return (ptr->LookAndFeel_V3::getAlertWindowMessageFont ()); }

        virtual Font getAlertWindowFont () override
        { return (call<Font>("getAlertWindowFont")); }
        static Font def_getAlertWindowFont (LookAndFeel_V3 *ptr)
        { return (ptr->LookAndFeel_V3::getAlertWindowFont ()); }

        virtual void drawProgressBar (Graphics &g, ProgressBar &bar, int width, int height, double progress, const String &textToShow) override
        { call<void>("drawProgressBar", boost::ref(g), boost::ref(bar), width, height, progress, textToShow); }
        static void def_drawProgressBar (LookAndFeel_V3 *ptr, Graphics &g, ProgressBar &bar, int width, int height, double progress, const String &textToShow)
        { return (ptr->LookAndFeel_V3::drawProgressBar (g, bar, width, height, progress, textToShow)); }

        virtual void drawSpinningWaitAnimation (Graphics &g, const Colour &colour, int x, int y, int w, int h) override
        { call<void>("drawSpinningWaitAnimation", boost::ref(g), colour, x, y, w, h); }
        static void def_drawSpinningWaitAnimation (LookAndFeel_V3 *ptr, Graphics &g, const Colour &colour, int x, int y, int w, int h)
        { return (ptr->LookAndFeel_V3::drawSpinningWaitAnimation (g, colour, x, y, w, h)); }

        virtual bool areScrollbarButtonsVisible () override
        { return (call<bool>("areScrollbarButtonsVisible")); }
        static bool def_areScrollbarButtonsVisible (LookAndFeel_V3 *ptr)
        { return (ptr->LookAndFeel_V3::areScrollbarButtonsVisible ()); }

        virtual ImageEffectFilter *getScrollbarEffect () override
        { return (call<ImageEffectFilter*>("getScrollbarEffect")); }
        static ImageEffectFilter *def_getScrollbarEffect (LookAndFeel_V3 *ptr)
        { return (ptr->LookAndFeel_V3::getScrollbarEffect ()); }

        virtual int getMinimumScrollbarThumbSize (ScrollBar &bar) override
        { return (call<int>("getMinimumScrollbarThumbSize", boost::ref(bar))); }
        static int def_getMinimumScrollbarThumbSize (LookAndFeel_V3 *ptr, ScrollBar &bar)
        { return (ptr->LookAndFeel_V3::getMinimumScrollbarThumbSize (bar)); }

        virtual int getDefaultScrollbarWidth () override
        { return (call<int>("getDefaultScrollbarWidth")); }
        static int def_getDefaultScrollbarWidth (LookAndFeel_V3 *ptr)
        { return (ptr->LookAndFeel_V3::getDefaultScrollbarWidth ()); }

        virtual int getScrollbarButtonSize (ScrollBar &bar) override
        { return (call<int>("getScrollbarButtonSize", boost::ref(bar))); }
        static int def_getScrollbarButtonSize (LookAndFeel_V3 *ptr, ScrollBar &bar)
        { return (ptr->LookAndFeel_V3::getScrollbarButtonSize (bar)); }

        virtual Path getTickShape (float height) override
        { return (call<Path>("getTickShape", height)); }
        static Path def_getTickShape (LookAndFeel_V3 *ptr, float height)
        { return (ptr->LookAndFeel_V3::getTickShape (height)); }

        virtual Path getCrossShape (float height) override
        { return (call<Path>("getCrossShape", height)); }
        static Path def_getCrossShape (LookAndFeel_V3 *ptr, float height)
        { return (ptr->LookAndFeel_V3::getCrossShape (height)); }

        virtual void drawTreeviewPlusMinusBox (Graphics &g, const Rectangle<float> &area, Colour backgroundColour, bool isOpen, bool isMouseOver) override
        { call<void>("drawTreeviewPlusMinusBox", boost::ref(g), area, backgroundColour, isOpen, isMouseOver); }
        static void def_drawTreeviewPlusMinusBox (LookAndFeel_V3 *ptr, Graphics &g, const Rectangle<float> &area, Colour backgroundColour, bool isOpen, bool isMouseOver)
        { return (ptr->LookAndFeel_V3::drawTreeviewPlusMinusBox (g, area, backgroundColour, isOpen, isMouseOver)); }

        virtual void fillTextEditorBackground (Graphics &g, int width, int height, TextEditor &editor) override
        { call<void>("fillTextEditorBackground", boost::ref(g), width, height, boost::ref(editor)); }
        static void def_fillTextEditorBackground (LookAndFeel_V3 *ptr, Graphics &g, int width, int height, TextEditor &editor)
        { return (ptr->LookAndFeel_V3::fillTextEditorBackground (g, width, height, editor)); }

        virtual void drawTextEditorOutline (Graphics &g, int width, int height, TextEditor &editor) override
        { call<void>("drawTextEditorOutline", boost::ref(g), width, height, boost::ref(editor)); }
        static void def_drawTextEditorOutline (LookAndFeel_V3 *ptr, Graphics &g, int width, int height, TextEditor &editor)
        { return (ptr->LookAndFeel_V3::drawTextEditorOutline (g, width, height, editor)); }

        virtual CaretComponent  *createCaretComponent (Component *keyFocusOwner) override
        { return (call<CaretComponent*>("createCaretComponent", keyFocusOwner)); }
        static CaretComponent *def_createCaretComponent (LookAndFeel_V3 *ptr, Component *keyFocusOwner)
        { return (ptr->LookAndFeel_V3::createCaretComponent (keyFocusOwner)); }

        virtual const Drawable *getDefaultFolderImage () override
        { return (call<const Drawable *>("getDefaultFolderImage")); }
        static const Drawable *def_getDefaultFolderImage (LookAndFeel_V3 *ptr)
        { return (ptr->LookAndFeel_V3::getDefaultFolderImage ()); }

        virtual const Drawable *getDefaultDocumentFileImage () override
        { return (call<const Drawable *>("getDefaultDocumentFileImage")); }
        static const Drawable *def_getDefaultDocumentFileImage (LookAndFeel_V3 *ptr)
        { return (ptr->LookAndFeel_V3::getDefaultDocumentFileImage ()); }

        virtual AttributedString createFileChooserHeaderText (const String &title, const String &instructions) override
        { return (call<AttributedString>("createFileChooserHeaderText", title, instructions)); }
        static AttributedString def_createFileChooserHeaderText (LookAndFeel_V3 *ptr, const String &title, const String &instructions)
        { return (ptr->LookAndFeel_V3::createFileChooserHeaderText (title, instructions)); }

        virtual void drawFileBrowserRow (Graphics &g, int width, int height, const String &filename, Image *icon, const String &fileSizeDescription, const String &fileTimeDescription, bool isDirectory, bool isItemSelected, int itemIndex, DirectoryContentsDisplayComponent &component) override
		{ call<void>("drawFileBrowserRow", DrawFileBrowserRowParams (boost::ref(g),width,height,filename,icon,fileSizeDescription,fileTimeDescription,isDirectory,isItemSelected,itemIndex,boost::ref(component))); }
        static void def_drawFileBrowserRow (LookAndFeel_V3 *ptr, Graphics &g, int width, int height, const String &filename, Image *icon, const String &fileSizeDescription, const String &fileTimeDescription, bool isDirectory, bool isItemSelected, int itemIndex, DirectoryContentsDisplayComponent &component)
        { return (ptr->LookAndFeel_V3::drawFileBrowserRow (g, width, height, filename, icon, fileSizeDescription, fileTimeDescription, isDirectory, isItemSelected, itemIndex, component)); }

        virtual Button *createFileBrowserGoUpButton () override
        { return (call<Button *>("createFileBrowserGoUpButton")); }
        static Button *def_createFileBrowserGoUpButton (LookAndFeel_V3 *ptr)
        { return (ptr->LookAndFeel_V3::createFileBrowserGoUpButton ()); }

        virtual void layoutFileBrowserComponent (FileBrowserComponent &component, DirectoryContentsDisplayComponent *contentsComponent, FilePreviewComponent *previewComponent, ComboBox *currentPathBox, TextEditor *filenameBox, Button *goUpButton) override
        { call<void>("layoutFileBrowserComponent", boost::ref(component), contentsComponent, previewComponent, currentPathBox, filenameBox, goUpButton); }
        static void def_layoutFileBrowserComponent (LookAndFeel_V3 *ptr, FileBrowserComponent &component, DirectoryContentsDisplayComponent *contentsComponent, FilePreviewComponent *previewComponent, ComboBox *currentPathBox, TextEditor *filenameBox, Button *goUpButton)
        { ptr->LookAndFeel_V3::layoutFileBrowserComponent (component, contentsComponent, previewComponent, currentPathBox, filenameBox, goUpButton); }

        virtual void drawBubble (Graphics &g, BubbleComponent &bubble, const Point<float> &tip, const Rectangle<float> &body) override
        { call<void>("drawBubble", boost::ref(g), boost::ref(bubble), tip, body); }
        static void def_drawBubble (LookAndFeel_V3 *ptr, Graphics &g, BubbleComponent &bubble, const Point<float> &tip, const Rectangle<float> &body)
        { ptr->LookAndFeel_V3::drawBubble (g, bubble, tip, body); }

        virtual void drawLasso (Graphics &g, Component &component) override
        { call<void>("drawLasso", boost::ref(g), boost::ref(component)); }
        static void def_drawLasso (LookAndFeel_V3 *ptr, Graphics &g, Component &component)
        { ptr->LookAndFeel_V3::drawLasso (g, component); }

        virtual void drawPopupMenuBackground (Graphics &g, int width, int height) override
        { call<void>("drawPopupMenuBackground", boost::ref(g), width, height); }
        static void def_drawPopupMenuBackground (LookAndFeel_V3 *ptr, Graphics &g, int width, int height)
        { ptr->LookAndFeel_V3::drawPopupMenuBackground (g, width, height); }

        virtual void drawPopupMenuItem (Graphics &g, const Rectangle<int> &area, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const String &text, const String &shortcutKeyText, const Drawable *icon, const Colour *textColour) override
        { call<void>("drawPopupMenuItem", DrawPopupMenuItemParams (boost::ref(g), area, isSeparator, isActive, isHighlighted, isTicked, hasSubMenu, text, shortcutKeyText, icon, textColour)); }
        static void def_drawPopupMenuItem (LookAndFeel_V3 *ptr, Graphics &g, const Rectangle<int> &area, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const String &text, const String &shortcutKeyText, const Drawable *icon, const Colour *textColour)
        { ptr->LookAndFeel_V3::drawPopupMenuItem (g, area, isSeparator, isActive, isHighlighted, isTicked, hasSubMenu, text, shortcutKeyText, icon, textColour); }

        virtual Font getPopupMenuFont (Graphics &g, int width, int height) override
        { return (call<Font>("getPopupMenuFont")); }
        static Font def_getPopupMenuFont (LookAndFeel_V3 *ptr)
        { return (ptr->LookAndFeel_V3::getPopupMenuFont ()); }

        virtual void drawPopupMenuUpDownArrow (Graphics &g, int width, int height, bool isScrollUpArrow) override
        { call<void>("drawPopupMenuUpDownArrow", boost::ref(g), width, height, isScrollUpArrow); }
        static void def_drawPopupMenuUpDownArrow (LookAndFeel_V3 *ptr, Graphics &g, int width, int height, bool isScrollUpArrow)
        { ptr->LookAndFeel_V3::drawPopupMenuUpDownArrow (g, width, height, isScrollUpArrow); }

        virtual void getIdealPopupMenuItemSize (const String &text, bool isSeparator, int standardMenuItemHeight, int &idealWidth, int &idealHeight) override
        { call<void>("getIdealPopupMenuItemSize", text, isSeparator, standardMenuItemHeight, idealWidth, idealHeight); }
        static void def_getIdealPopupMenuItemSize (LookAndFeel_V3 *ptr, const String &text, bool isSeparator, int standardMenuItemHeight, int &idealWidth, int &idealHeight)
        { ptr->LookAndFeel_V3::getIdealPopupMenuItemSize (text, isSeparator, standardMenuItemHeight, idealWidth, idealHeight); }

        virtual int getMenuWindowFlags () override
        { return (call<int>("getMenuWindowFlags")); }
        static int def_getMenuWindowFlags (LookAndFeel_V3 *ptr)
        { return (ptr->LookAndFeel_V3::getMenuWindowFlags ()); }

        virtual void drawMenuBarBackground (Graphics &g, int width, int height, bool isMouseOverBar, MenuBarComponent &component) override
        { call<void>("drawMenuBarBackground", boost::ref(g), width, height, isMouseOverBar, boost::ref(component)); }
        static void def_drawMenuBarBackground (LookAndFeel_V3 *ptr, Graphics &g, int width, int height, bool isMouseOverBar, MenuBarComponent &component)
        { ptr->LookAndFeel_V3::drawMenuBarBackground (g, width, height, isMouseOverBar, component); }

        virtual int getMenuBarItemWidth (MenuBarComponent &component, int itemIndex, const String &itemText) override
        { return (call<int>("getMenuBarItemWidth", boost::ref(component), itemIndex, itemText)); }
        static int def_getMenuBarItemWidth (LookAndFeel_V3 *ptr, MenuBarComponent &component, int itemIndex, const String &itemText)
        { return (ptr->LookAndFeel_V3::getMenuBarItemWidth (component, itemIndex, itemText)); }

        virtual Font getMenuBarFont (MenuBarComponent &component, int itemIndex, const String &itemText) override
        { return (call<Font>("getMenuBarFont", boost::ref(component), itemIndex, itemText)); }
        static Font def_getMenuBarFont (LookAndFeel_V3 *ptr, MenuBarComponent &component, int itemIndex, const String &itemText)
        { return (ptr->LookAndFeel_V3::getMenuBarFont (component, itemIndex, itemText)); }

        virtual void drawMenuBarItem (Graphics &g, int width, int height, int itemIndex, const String &itemText, bool isMouseOverItem, bool isMenuOpen, bool isMouseOverBar, MenuBarComponent &component) override
        { call<void>("drawMenuBarItem", boost::ref(g), width, height, itemIndex, itemText, isMouseOverItem, isMenuOpen, isMouseOverBar, boost::ref(component)); }
        static void def_drawMenuBarItem (LookAndFeel_V3 *ptr, Graphics &g, int width, int height, int itemIndex, const String &itemText, bool isMouseOverItem, bool isMenuOpen, bool isMouseOverBar, MenuBarComponent &component)
        { ptr->LookAndFeel_V3::drawMenuBarItem (g, width, height, itemIndex, itemText, isMouseOverItem, isMenuOpen, isMouseOverBar, component); }

        virtual void drawComboBox (Graphics &g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox &component) override
        { call<void>("drawComboBox", boost::ref(g), width, height, isButtonDown, buttonX, buttonY, buttonW, buttonH, boost::ref(component)); }
        static void def_drawComboBox (LookAndFeel_V3 *ptr, Graphics &g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox &component)
        { return (ptr->LookAndFeel_V3::drawComboBox (g, width, height, isButtonDown, buttonX, buttonY, buttonW, buttonH, component)); }

        virtual void drawLabel (Graphics &g, Label &label) override
        { call<void>("drawLabel", boost::ref(g), boost::ref(label)); }
        static void def_drawLabel (LookAndFeel_V3 *ptr, Graphics &g, Label &label)
        { return (ptr->LookAndFeel_V3::drawLabel (g, label)); }

        virtual void drawRotarySlider (Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override
        { call<void>("drawRotarySlider", boost::ref(g), x, y, width, height, sliderPosProportional, rotaryStartAngle, rotaryEndAngle, boost::ref(slider)); }
        static void def_drawRotarySlider (LookAndFeel_V3 *ptr, Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider)
        { ptr->LookAndFeel_V3::drawRotarySlider (g, x, y, width, height, sliderPosProportional, rotaryStartAngle, rotaryEndAngle, slider); }

        virtual void drawGroupComponentOutline (Graphics &g, int w, int h, const String &text, const Justification &justification, GroupComponent &component) override
        { call<void>("drawGroupComponentOutline", boost::ref(g), w, h, text, justification, boost::ref(component)); }
        static void def_drawGroupComponentOutline (LookAndFeel_V3 *ptr, Graphics &g, int w, int h, const String &text, const Justification &justification, GroupComponent &component)
        { ptr->LookAndFeel_V3::drawGroupComponentOutline (g, w, h, text, justification, component); }
};

#endif
