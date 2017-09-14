#ifndef L_LOOK_AND_FEEL
#define L_LOOK_AND_FEEL

#include "JuceHeader.h"
#include "luabind/object_fwd.hpp"

class LookAndFeelBase : public LookAndFeel_V3
{
	public:
		LookAndFeelBase();
		void setMethod (const String &methodName, const luabind::object &method);
		void setImplementation (const luabind::object &implementationAsTable);
        static void wrapForLua (lua_State *L);

		Colour findColour (int colourId);
		void setColour (int colourId, Colour colour);
		bool isColourSpecified (int colourId);
		Typeface::Ptr getTypefaceForFont (const Font &font);
		MouseCursor getMouseCursorFor (Component &component);
		void drawButtonBackground (Graphics &g, Button &button, const Colour &backgroundColourRef, bool isMouseOverButton, bool isButtonDown);
		void drawButtonText (Graphics &g, TextButton &textButton, bool isMouseOverButton, bool isButtonDown);
		void drawToggleButton (Graphics &g, ToggleButton &toggleButton, bool isMouseOverButton, bool isButtonDown);
		void changeToggleButtonWidthToFitText (ToggleButton &toggleButton);
		void drawTickBox (Graphics &g, Component &component, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown);
		AlertWindow* createAlertWindow (const String &title, const String &message, const String &button1, const String &button2, const String &button3, AlertWindow::AlertIconType iconType, int numButtons, Component* component);
		void drawAlertBox (Graphics &g, AlertWindow &window, const Rectangle<int> &textArea, TextLayout &layout);
		int getAlertBoxWindowFlags ();
		int getAlertWindowButtonHeight ();
		Font getAlertWindowMessageFont ();
		Font getAlertWindowFont ();
		void drawProgressBar (Graphics &g, ProgressBar &progressBar, int width, int height, double progress, const String &textToShow);
		void drawSpinningWaitAnimation (Graphics &g, const Colour &colourRef, int x, int y, int w, int h);
		bool areScrollbarButtonsVisible ();
		ImageEffectFilter* getScrollbarEffect ();
		int getMinimumScrollbarThumbSize (ScrollBar &scrollBar);
		int getDefaultScrollbarWidth ();
		int getScrollbarButtonSize (ScrollBar &scrollBar);
		Path getTickShape (float height);
		Path getCrossShape (float height);
		void drawTreeviewPlusMinusBox (Graphics &g, const Rectangle<float> &area, Colour backgroundColour, bool isOpen, bool isMouseOver);
		void fillTextEditorBackground (Graphics &g, int width, int height, TextEditor &editor);
		void drawTextEditorOutline (Graphics &g, int width, int height, TextEditor &editor);
		CaretComponent* createCaretComponent (Component* component);
		const Drawable* getDefaultFolderImage ();
		const Drawable* getDefaultDocumentFileImage ();
		AttributedString createFileChooserHeaderText (const String &title, const String &instructions);
		//void drawFileBrowserRow (Graphics &g, int width, int height, const String &filename, Image* icon, const String &fileSizeDescription, const String &fileTimeDescription, bool isDirectory, bool isItemSelected, int itemIndex, DirectoryContentsDisplayComponent &directoryContentsDisplayComponent);
		Button* createFileBrowserGoUpButton ();
		void layoutFileBrowserComponent (FileBrowserComponent &fileBrowserComponent, DirectoryContentsDisplayComponent *directoryContentsDisplayComponent, FilePreviewComponent *filePreviewComponent, ComboBox *comboBox, TextEditor *textEditor, Button *goUpButton);
		void drawBubble (Graphics &g, BubbleComponent &bubbleComponent, const Point<float> &tip, const Rectangle<float> &body);
		void drawLasso (Graphics &g, Component &component);
		void drawPopupMenuBackground (Graphics &g, int width, int height);
		//void drawPopupMenuItem (Graphics &g, const Rectangle<int> &areaInt, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const String &text, const String &shortcutKeyText, const Drawable* drawableIcon, const Colour *textColourPtr);
		Font getPopupMenuFont ();
		void drawPopupMenuUpDownArrow (Graphics &g, int width, int height, bool isScrollUpArrow);
		void getIdealPopupMenuItemSize (const String &text, bool isSeparator, int standardMenuItemHeight, int &idealWidth, int &idealHeight);
		int getMenuWindowFlags ();
		void drawMenuBarBackground (Graphics &g, int width, int height, bool isMouseOverBar, MenuBarComponent &menuBarComponent);
		int getMenuBarItemWidth (MenuBarComponent &menuBarComponent, int itemIndex, const String &itemText);
		Font getMenuBarFont (MenuBarComponent &menuBarComponent, int itemIndex, const String &itemText);
		void drawMenuBarItem (Graphics &g, int width, int height, int itemIndex, const String &itemText, bool isMouseOverItem, bool isMenuOpen, bool isMouseOverBar, MenuBarComponent &menuBarComponent);
		void drawComboBox (Graphics &g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox &comboBox);
		Font getComboBoxFont (ComboBox &comboBox);
		Label* createComboBoxTextBox (ComboBox &comboBox);
		void positionComboBoxText (ComboBox &comboBox, Label &label);
		void drawLabel (Graphics &g, Label &label);
		void drawLinearSlider (Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle sliderStyle, Slider &slider);
		void drawLinearSliderBackground (Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle sliderStyle, Slider &slider);
		void drawLinearSliderThumb (Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle sliderStyle, Slider &slider);
		int getSliderThumbRadius (Slider &slider);
		void drawRotarySlider (Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider);
		Button* createSliderButton (Slider &slider, bool isIncrement);
		Label* createSliderTextBox (Slider &slider);
		ImageEffectFilter* getSliderEffect (Slider &slider);
		Rectangle<int> getTooltipBounds(const String &tipText, Point<int> screenPos, Rectangle<int> parentArea);
		void drawTooltip (Graphics &g, const String &text, int width, int height);
		Button* createFilenameComponentBrowseButton (const String &text);
		void layoutFilenameComponent (FilenameComponent &filenameComponent, ComboBox* comboBox, Button* button);
		void drawConcertinaPanelHeader (Graphics &g, const Rectangle<int> &areaInt, bool isMouseOver, bool isMouseDown, ConcertinaPanel &concertinaPanel, Component &component);
		void drawCornerResizer (Graphics &g, int w, int h, bool isMouseOver, bool isMouseDragging);
		void drawResizableFrame (Graphics &g, int w, int h, const BorderSize<int> &borderSize);
		void fillResizableWindowBackground (Graphics &g, int w, int h, const BorderSize<int> &borderSize, ResizableWindow &resizableWindow);
		void drawResizableWindowBorder (Graphics &g, int w, int h, const BorderSize<int> &borderSize, ResizableWindow &resizableWindow);
		void drawDocumentWindowTitleBar (DocumentWindow &documentWindow, Graphics &g, int w, int h, int titleSpaceX, int titleSpaceW, const Image* icon, bool drawTitleTextOnLeft);
		Button* createDocumentWindowButton (int buttonType);
		void positionDocumentWindowButtons (DocumentWindow &documentWindow, int titleBarX, int titleBarY, int titleBarW, int titleBarH, Button* minimiseButton, Button* maximiseButton, Button* closeButton, bool positionTitleBarButtonsOnLeft);
		int getDefaultMenuBarHeight ();
		DropShadower* createDropShadowerForComponent (Component* component);
		void drawGroupComponentOutline (Graphics &g, int w, int h, const String &text, const Justification &justification, GroupComponent &groupComponent);
		int getTabButtonSpaceAroundImage ();
		int getTabButtonOverlap (int tabDepth);
		int getTabButtonBestWidth (TabBarButton &tabBarButton, int tabDepth);
		Rectangle<int> getTabButtonExtraComponentBounds (const TabBarButton &tabBarButton, Rectangle<int> &areaInt, Component &component);
		void drawTabButton (TabBarButton &tabBarButton, Graphics &g, bool isMouseOver, bool isMouseDown);
		void drawTabButtonText (TabBarButton &tabBarButton, Graphics &g, bool isMouseOver, bool isMouseDown);
		void drawTabAreaBehindFrontButton (TabbedButtonBar &tabbedButtonBar, Graphics &g, int w, int h);
		void createTabButtonShape (TabBarButton &tabBarButton, Path &p, bool isMouseOver, bool isMouseDown);
		void fillTabButtonShape (TabBarButton &tabBarButton, Graphics &g, const Path &p, bool isMouseOver, bool isMouseDown);
		Button* createTabBarExtrasButton ();
		void drawImageButton (Graphics &g, Image* image, int imageX, int imageY, int imageW, int imageH, const Colour &overlayColourRef, float imageOpacity, ImageButton &imageButton);
		void drawTableHeaderBackground (Graphics &g, TableHeaderComponent &tableHeaderComponent);
		void drawTableHeaderColumn (Graphics &g, const String &columnName, int columnId, int width, int height, bool isMouseOver, bool isMouseDown, int columnFlags);
		void paintToolbarBackground (Graphics &g, int width, int height, Toolbar &toolbar);
		Button* createToolbarMissingItemsButton (Toolbar &toolbar);
		void paintToolbarButtonBackground (Graphics &g, int width, int height, bool isMouseOver, bool isMouseDown, ToolbarItemComponent &toolbarItemComponent);
		void paintToolbarButtonLabel (Graphics &g, int x, int y, int width, int height, const String &text, ToolbarItemComponent &toolbarItemComponent);
		void drawStretchableLayoutResizerBar (Graphics &g, int w, int h, bool isVerticalBar, bool isMouseOver, bool isMouseDragging);
		void drawPropertyPanelSectionHeader (Graphics &g, const String &name, bool isOpen, int width, int height);
		void drawPropertyComponentBackground (Graphics &g, int width, int height, PropertyComponent &propertyComponent);
		void drawPropertyComponentLabel (Graphics &g, int width, int height, PropertyComponent &propertyComponent);
		Rectangle<int> getPropertyComponentContentPosition (PropertyComponent &propertyComponent);
		void drawCallOutBoxBackground (CallOutBox &callOutBox, Graphics &g, const Path &path, Image &image);
		void drawLevelMeter (Graphics &g, int width, int height, float level);
		void drawKeymapChangeButton (Graphics &g, int width, int height, Button &button, const String &keyDescription);

		static Label *createLabel() { return (new Label()); }
		static Button *createTextButton() { return (new TextButton()); }
		static Button *createImageButton() { return (new ImageButton()); }
		static Button *createToggleButton() { return (new ToggleButton()); }
		static ImageEffectFilter *createDropShadowEffect() { return (new DropShadowEffect()); }
		static ImageEffectFilter *createGlowEffect() { return (new GlowEffect()); }
		static Drawable *createDrawableComposite() { return (new DrawableComposite()); }
		static Drawable *createDrawableImage() { return (new DrawableImage()); }
		static Drawable *createDrawablePath() { return (new DrawablePath()); }
		static Drawable *createDrawableRectangle() { return (new DrawableRectangle()); }
		static Drawable *createDrawableText() { return (new DrawableText()); }
	private:
	    HashMap<String,luabind::object> methods;
};
#endif
