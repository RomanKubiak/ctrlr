#ifndef LOOK_AND_FEEL_PARAM_WRAPPER
#define LOOK_AND_FEEL_PARAM_WRAPPER

#include "CtrlrMacros.h"

struct LookAndFeelParamWrapper
{
    /* Common */
	Graphics *g;
	int x;
	int y;
	int w;
	int h;
	int width;
	int height;
	int colourId;
	int buttonX;
	int buttonY;
	int buttonW;
	int buttonH;
	int titleSpaceX;
	int titleSpaceW;
	int buttonType;
	int titleBarX;
	int titleBarY;
	int titleBarW;
	int titleBarH;
	int tabDepth;
	int imageX;
	int imageY;
	int imageW;
	int imageH;
	int columnId;
	int columnFlags;

	float sliderPos;
	float minSliderPos;
	float maxSliderPos;
	float imageOpacity;
	float level;

	Font *font;
	Component *component;
	Button *button;
	ImageButton *imageButton;
	TextButton *textButton;
	ToggleButton *toggleButton;
	Colour colour;
	Colour backgroundColour;
	Colour textColour;
	Colour overlayColour;
	Colour *backgroundColourRef;
	Colour *colourRef;
	Colour *textColourPtr;
	Colour *overlayColourRef;

	bool isMouseOverButton;
	bool isButtonDown;
	bool ticked;
	bool isEnabled;
	bool isOpen;
	bool isMouseOver;
	bool isActive;
	bool isHighlighted;
	bool isTicked;
	bool hasSubMenu;
	bool isScrollUpArrow;
	bool isMouseOverBar;
	bool isMouseOverItem;
	bool isMenuOpen;
	bool isIncrement;
	bool isMouseDown;
	bool isMouseDragging;
	bool drawTitleTextOnLeft;
	bool positionTitleBarButtonsOnLeft;
	bool isVerticalBar;

	const String *keyDescription;
	const String *name;
	const String *text;
	const String *title;
	const String *message;
	const String *button1;
	const String *button2;
	const String *button3;
	const String *instructions;
	const String *filename;
	const String *shortcutKeyText;
	const String *itemText;
	const String *tipText;
	const String *columnName;

	Image *icon;
	Image *image;
	Drawable *drawableIcon;
	/* Common */

	/* getIdealPopupMenuItemSize */
	bool isSeparator;
	int standardMenuItemHeight;
	int idealWidth;
	int idealHeight;
	/* getIdealPopupMenuItemSize */

	/* drawRotarySlider */
	float sliderPosProportional, rotaryStartAngle, rotaryEndAngle;
	Slider *slider;
	/* drawRotarySlider */

	/* createAlertWindow */
	AlertWindow::AlertIconType  	iconType;
	int numButtons;
	Component *associatedComponent;
	/* createAlertWindow */

	/* drawAlertBox */
	AlertWindow *window;
	Rectangle<int> *textArea;
	TextLayout *layout;
	/* drawAlertBox */

	/* drawProgressBar */
	ProgressBar *progressBar;
	double progress;
	String *textToShow;
	/* drawProgressBar */

	ScrollBar *scrollBar;

	Rectangle<float> *area;
	Rectangle<int> *areaInt;

	TextEditor *textEditor, *editor;

	Component *keyFocusOwner;

	/* def_drawFileBrowserRow */
	DirectoryContentsDisplayComponent *directoryContentsDisplayComponent;
	String *fileSizeDescription;
	String *fileTimeDescription;
	bool isDirectory;
	bool isItemSelected;
	int itemIndex;
	/* def_drawFileBrowserRow */
	FileBrowserComponent *fileBrowserComponent;
	FilePreviewComponent *filePreviewComponent;
	ComboBox *currentPathBox;
	TextEditor *filenameBox;
	Button *goUpButton;
	BubbleComponent *bubble, *bubbleComponent;
	const Point<float> *tip;
	const Rectangle<float> *body;
	MenuBarComponent *menuBarComponent;
	ComboBox *comboBox;
	Label *label;
	Slider::SliderStyle sliderStyle;
	FilenameComponent *filenameComponent;
	ConcertinaPanel *concertinaPanel;
	BorderSize<int> *borderSize;
	ResizableWindow *resizableWindow;
	DocumentWindow *documentWindow;
	Button *minimiseButton;
	Button *maximiseButton;
	Button *closeButton;
	Justification *justification;
	GroupComponent *groupComponent;
	TabBarButton *tabBarButton;
	TabbedButtonBar *tabbedButtonBar;
	Path *p, *path;
	TableHeaderComponent *tableHeaderComponent;
	Toolbar *toolbar;
	ToolbarItemComponent *toolbarItemComponent;
	PropertyComponent *propertyComponent;
	CallOutBox *callOutBox;


	LookAndFeelParamWrapper (int colourId) : colourId(_colourId) {}
	LookAndFeelParamWrapper (int colourId, Colour colour) : colourId(_colourId), colour(_colour) {}
	LookAndFeelParamWrapper (Font &font) : font(_font) {}
	LookAndFeelParamWrapper (Component &component) : component(_component) {}
	LookAndFeelParamWrapper (Graphics &g, Button &button, Colour &backgroundColourRef, bool isMouseOverButton, bool isButtonDown) : g(_g), button(_button), backgroundColourRef(_backgroundColourRef), isMouseOverButton(_isMouseOverButton), isButtonDown(_isButtonDown) {}
	LookAndFeelParamWrapper (Graphics &g, TextButton &textButton, bool isMouseOverButton, bool isButtonDown) : g(_g), textButton(_textButton), isMouseOverButton(_isMouseOverButton), isButtonDown(_isButtonDown) {}
	LookAndFeelParamWrapper (Graphics &g, ToggleButton &toggleButton, bool isMouseOverButton, bool isButtonDown) : g(_g), toggleButton(_toggleButton), isMouseOverButton(_isMouseOverButton), isButtonDown(_isButtonDown) {}
	LookAndFeelParamWrapper (ToggleButton &toggleButton) : toggleButton(_toggleButton) {}
	LookAndFeelParamWrapper (Graphics &g, Component &component, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown) : g(_g), component(_component), x(_x), y(_y), w(_w), h(_h), ticked(_ticked), isEnabled(_isEnabled), isMouseOverButton(_isMouseOverButton), isButtonDown(_isButtonDown) {}
	LookAndFeelParamWrapper (String &title, String &message, String &button1, String &button2, String &button3, AlertWindow::AlertIconType iconType, int numButtons, Component* component) : title(_title), message(_message), button1(_button1), button2(_button2), button3(_button3), iconType(_iconType), numButtons(_numButtons), component(_component) {}
	LookAndFeelParamWrapper (Graphics &g, AlertWindow &window, Rectangle<int> &textArea, TextLayout &layout) : g(_g), window(_window), textArea(_textArea), layout(_layout) {}
	LookAndFeelParamWrapper (Graphics &g, ProgressBar &progressBar, int width, int height, double progress, String &textToShow) : g(_g), progressBar(_progressBar), width(_width), height(_height), progress(_progress), textToShow(_textToShow) {}
	LookAndFeelParamWrapper (Graphics &g, Colour &colourRef, int x, int y, int w, int h) : g(_g), colourRef(_colourRef), x(_x), y(_y), w(_w), h(_h) {}
	LookAndFeelParamWrapper (ScrollBar &scrollBar) : scrollBar(_scrollBar) {}
	LookAndFeelParamWrapper (float height) : height(_height) {}
	LookAndFeelParamWrapper (Graphics &g, Rectangle<float> &area, Colour backgroundColour, bool isOpen, bool isMouseOver) : g(_g), area(_area), backgroundColour(_backgroundColour), isOpen(_isOpen), isMouseOver(_isMouseOver) {}
	LookAndFeelParamWrapper (Graphics &g, int width, int height, TextEditor &editor) : g(_g), width(_width), height(_height), editor(_editor) {}
	LookAndFeelParamWrapper (Component* component) : component(_component) {}
	LookAndFeelParamWrapper (String &title, String &instructions) : title(_title), instructions(_instructions) {}
	LookAndFeelParamWrapper (Graphics &g, int width, int height, String &filename, Image* icon, String &fileSizeDescription, String &fileTimeDescription, bool isDirectory, bool isItemSelected, int itemIndex, DirectoryContentsDisplayComponent &directoryContentsDisplayComponent) : g(_g), width(_width), height(_height), filename(_filename), icon(_icon), fileSizeDescription(_fileSizeDescription), fileTimeDescription(_fileTimeDescription), isDirectory(_isDirectory), isItemSelected(_isItemSelected), itemIndex(_itemIndex), directoryContentsDisplayComponent(_directoryContentsDisplayComponent) {}
	LookAndFeelParamWrapper (FileBrowserComponent &fileBrowserComponent, DirectoryContentsDisplayComponent *directoryContentsDisplayComponent, FilePreviewComponent *filePreviewComponent, ComboBox *comboBox, TextEditor *textEditor, Button *goUpButton) : fileBrowserComponent(_fileBrowserComponent), directoryContentsDisplayComponent(_directoryContentsDisplayComponent), filePreviewComponent(_filePreviewComponent), comboBox(_comboBox), textEditor(_textEditor), goUpButton(_goUpButton) {}
	LookAndFeelParamWrapper (Graphics &g, BubbleComponent &bubbleComponent, Point<float> &tip, Rectangle<float> &body) : g(_g), bubbleComponent(_bubbleComponent), tip(_tip), body(_body) {}
	LookAndFeelParamWrapper (Graphics &g, Component &component) : g(_g), component(_component) {}
	LookAndFeelParamWrapper (Graphics &g, int width, int height) : g(_g), width(_width), height(_height) {}
	LookAndFeelParamWrapper (Graphics &g, Rectangle<int> &areaInt, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, String &text, String &shortcutKeyText, Drawable* drawableIcon, Colour *textColourPtr) : g(_g), areaInt(_areaInt), isSeparator(_isSeparator), isActive(_isActive), isHighlighted(_isHighlighted), isTicked(_isTicked), hasSubMenu(_hasSubMenu), text(_text), shortcutKeyText(_shortcutKeyText), drawableIcon(_drawableIcon), textColourPtr(_textColourPtr) {}

	LookAndFeelParamWrapper (Graphics &g, int width, int height, bool isScrollUpArrow) : g(_g), width(_width), height(_height), isScrollUpArrow(_isScrollUpArrow) {}
	LookAndFeelParamWrapper (String &text, bool isSeparator, int standardMenuItemHeight, int &idealWidth, int &idealHeight) : text(_text), isSeparator(_isSeparator), standardMenuItemHeight(_standardMenuItemHeight), idealWidth(_idealWidth), idealHeight(_idealHeight) {}

	LookAndFeelParamWrapper (Graphics &g, int width, int height, bool isMouseOverBar, MenuBarComponent &menuBarComponent) : g(_g), width(_width), height(_height), isMouseOverBar(_isMouseOverBar), menuBarComponent(_menuBarComponent) {}
	LookAndFeelParamWrapper (MenuBarComponent &menuBarComponent, int itemIndex, String &itemText) : menuBarComponent(_menuBarComponent), itemIndex(_itemIndex), itemText(_itemText) {}
	LookAndFeelParamWrapper (Graphics &g, int width, int height, int itemIndex, String &itemText, bool isMouseOverItem, bool isMenuOpen, bool isMouseOverBar, MenuBarComponent &menuBarComponent) : g(_g), width(_width), height(_height), itemIndex(_itemIndex), itemText(_itemText), isMouseOverItem(_isMouseOverItem), isMenuOpen(_isMenuOpen), isMouseOverBar(_isMouseOverBar), menuBarComponent(_menuBarComponent) {}
	LookAndFeelParamWrapper (Graphics &g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox &comboBox) : g(_g), width(_width), height(_height), isButtonDown(_isButtonDown), buttonX(_buttonX), buttonY(_buttonY), buttonW(_buttonW), buttonH(_buttonH), comboBox(_comboBox) {}
	LookAndFeelParamWrapper (ComboBox &comboBox) : comboBox(_comboBox) {}
	LookAndFeelParamWrapper (ComboBox &comboBox, Label &label) : comboBox(_comboBox), label(_label) {}
	LookAndFeelParamWrapper (Graphics &g, Label &label) : g(_g), label(_label) {}
	LookAndFeelParamWrapper (Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, Slider::SliderStyle sliderStyle, Slider &slider) : g(_g), x(_x), y(_y), width(_width), height(_height), sliderPos(_sliderPos), minSliderPos(_minSliderPos), maxSliderPos(_maxSliderPos), sliderStyle(_sliderStyle), slider(_slider) {}
	LookAndFeelParamWrapper (Slider &slider) : slider(_slider) {}
	LookAndFeelParamWrapper (Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider) : g(_g), x(_x), y(_y), width(_width), height(_height), sliderPosProportional(_sliderPosProportional), rotaryStartAngle(_rotaryStartAngle), rotaryEndAngle(_rotaryEndAngle), slider(_slider) {}
	LookAndFeelParamWrapper (Slider &slider, bool isIncrement) : slider(_slider), isIncrement(_isIncrement) {}


	LookAndFeelParamWrapper (String &tipText, int &width, int &height) : tipText(_tipText), width(_width), height(_height) {}
	LookAndFeelParamWrapper (Graphics &g, String &text, int width, int height) : g(_g), text(_text), width(_width), height(_height) {}
	LookAndFeelParamWrapper (String &text) : text(_text) {}
	LookAndFeelParamWrapper (FilenameComponent &filenameComponent, ComboBox* comboBox, Button* button) : filenameComponent(_filenameComponent), comboBox(_comboBox), button(_button) {}
	LookAndFeelParamWrapper (Graphics &g, Rectangle<int> &areaInt, bool isMouseOver, bool isMouseDown, ConcertinaPanel &concertinaPanel, Component &component) : g(_g), areaInt(_areaInt), isMouseOver(_isMouseOver), isMouseDown(_isMouseDown), concertinaPanel(_concertinaPanel), component(_component) {}
	LookAndFeelParamWrapper (Graphics &g, int w, int h, bool isMouseOver, bool isMouseDragging) : g(_g), w(_w), h(_h), isMouseOver(_isMouseOver), isMouseDragging(_isMouseDragging) {}
	LookAndFeelParamWrapper (Graphics &g, int w, int h, BorderSize<int> &borderSize) : g(_g), w(_w), h(_h), borderSize(_borderSize) {}
	LookAndFeelParamWrapper (Graphics &g, int w, int h, BorderSize<int> &borderSize, ResizableWindow &resizableWindow) : g(_g), w(_w), h(_h), borderSize(_borderSize), resizableWindow(_resizableWindow) {}

	LookAndFeelParamWrapper (DocumentWindow &documentWindow, Graphics &g, int w, int h, int titleSpaceX, int titleSpaceW, Image* icon, bool drawTitleTextOnLeft) : documentWindow(_documentWindow), g(_g), w(_w), h(_h), titleSpaceX(_titleSpaceX), titleSpaceW(_titleSpaceW), icon(_icon), drawTitleTextOnLeft(_drawTitleTextOnLeft) {}

	LookAndFeelParamWrapper (DocumentWindow &documentWindow, int titleBarX, int titleBarY, int titleBarW, int titleBarH, Button* minimiseButton, Button* maximiseButton, Button* closeButton, bool positionTitleBarButtonsOnLeft) : documentWindow(_documentWindow), titleBarX(_titleBarX), titleBarY(_titleBarY), titleBarW(_titleBarW), titleBarH(_titleBarH), minimiseButton(_minimiseButton), maximiseButton(_maximiseButton), closeButton(_closeButton), positionTitleBarButtonsOnLeft(_positionTitleBarButtonsOnLeft) {}

	LookAndFeelParamWrapper (Graphics &g, int w, int h, String &text, Justification &justification, GroupComponent &groupComponent) : g(_g), w(_w), h(_h), text(_text), justification(_justification), groupComponent(_groupComponent) {}
	LookAndFeelParamWrapper (TabBarButton &tabBarButton, int tabDepth) : tabBarButton(_tabBarButton), tabDepth(_tabDepth) {}
	LookAndFeelParamWrapper (TabBarButton &tabBarButton, Rectangle<int> &areaInt, Component &component) : tabBarButton(_tabBarButton), areaInt(_areaInt), component(_component) {}
	LookAndFeelParamWrapper (TabBarButton &tabBarButton, Graphics &g, bool isMouseOver, bool isMouseDown) : tabBarButton(_tabBarButton), g(_g), isMouseOver(_isMouseOver), isMouseDown(_isMouseDown) {}

	LookAndFeelParamWrapper (TabbedButtonBar &tabbedButtonBar, Graphics &g, int w, int h) : tabbedButtonBar(_tabbedButtonBar), g(_g), w(_w), h(_h) {}
	LookAndFeelParamWrapper (TabBarButton &tabBarButton, Path &p, bool isMouseOver, bool isMouseDown) : tabBarButton(_tabBarButton), p(_p), isMouseOver(_isMouseOver), isMouseDown(_isMouseDown) {}
	LookAndFeelParamWrapper (TabBarButton &tabBarButton, Graphics &g, Path &p, bool isMouseOver, bool isMouseDown) : tabBarButton(_tabBarButton), g(_g), p(_p), isMouseOver(_isMouseOver), isMouseDown(_isMouseDown) {}

	LookAndFeelParamWrapper (Graphics &g, Image* image, int imageX, int imageY, int imageW, int imageH, Colour &overlayColourRef, float imageOpacity, ImageButton &imageButton) : g(_g), image(_image), imageX(_imageX), imageY(_imageY), imageW(_imageW), imageH(_imageH), overlayColourRef(_overlayColourRef), imageOpacity(_imageOpacity), imageButton(_imageButton) {}
	LookAndFeelParamWrapper (Graphics &g, TableHeaderComponent &tableHeaderComponent) : g(_g), tableHeaderComponent(_tableHeaderComponent) {}
	LookAndFeelParamWrapper (Graphics &g, String &columnName, int columnId, int width, int height, bool isMouseOver, bool isMouseDown, int columnFlags) : g(_g), columnName(_columnName), columnId(_columnId), width(_width), height(_height), isMouseOver(_isMouseOver), isMouseDown(_isMouseDown), columnFlags(_columnFlags) {}
	LookAndFeelParamWrapper (Graphics &g, int width, int height, Toolbar &toolbar) : g(_g), width(_width), height(_height), toolbar(_toolbar) {}
	LookAndFeelParamWrapper (Toolbar &toolbar) : toolbar(_toolbar) {}
	LookAndFeelParamWrapper (Graphics &g, int width, int height, bool isMouseOver, bool isMouseDown, ToolbarItemComponent &toolbarItemComponent) : g(_g), width(_width), height(_height), isMouseOver(_isMouseOver), isMouseDown(_isMouseDown), toolbarItemComponent(_toolbarItemComponent) {}
	LookAndFeelParamWrapper (Graphics &g, int x, int y, int width, int height, String &text, ToolbarItemComponent &toolbarItemComponent) : g(_g), x(_x), y(_y), width(_width), height(_height), text(_text), toolbarItemComponent(_toolbarItemComponent) {}
	LookAndFeelParamWrapper (Graphics &g, int w, int h, bool isVerticalBar, bool isMouseOver, bool isMouseDragging) : g(_g), w(_w), h(_h), isVerticalBar(_isVerticalBar), isMouseOver(_isMouseOver), isMouseDragging(_isMouseDragging) {}
	LookAndFeelParamWrapper (Graphics &g, String &name, bool isOpen, int width, int height) : g(_g), name(_name), isOpen(_isOpen), width(_width), height(_height) {}
	LookAndFeelParamWrapper (Graphics &g, int width, int height, PropertyComponent &propertyComponent) : g(_g), width(_width), height(_height), propertyComponent(_propertyComponent) {}

	LookAndFeelParamWrapper (PropertyComponent &propertyComponent) : propertyComponent(_propertyComponent) {}
	LookAndFeelParamWrapper (CallOutBox &callOutBox, Graphics &g, Path &path, Image &image) : callOutBox(_callOutBox), g(_g), path(_path), image(_image) {}
	LookAndFeelParamWrapper (Graphics &g, int width, int height, float level) : g(_g), width(_width), height(_height), level(_level) {}
	LookAndFeelParamWrapper (Graphics &g, int width, int height, Button &button, String &keyDescription) : g(_g), width(_width), height(_height), button(_button), keyDescription(_keyDescription) {}

	static void wrapForLua (lua_State *L)
	{
		using namespace luabind;
		module(L)
		[
	            class_<LookAndFeelParamWrapper>("LookAndFeelParamWrapper")
        	        .def_readwrite ("g", &LookAndFeelParamWrapper::g)
	                .def_readonly ("x", &LookAndFeelParamWrapper::x)
	                .def_readonly ("y", &LookAndFeelParamWrapper::y)
	                .def_readonly ("width", &LookAndFeelParamWrapper::width)
	                .def_readonly ("height", &LookAndFeelParamWrapper::height)
	                .def_readonly ("isSeparator", &LookAndFeelParamWrapper::isSeparator)
	                .def_readonly ("standardMenuItemHeight", &LookAndFeelParamWrapper::standardMenuItemHeight)
	                .def_readonly ("sliderPosProportional", &LookAndFeelParamWrapper::sliderPosProportional)
	                .def_readonly ("rotaryStartAngle", &LookAndFeelParamWrapper::rotaryStartAngle)
	                .def_readonly ("rotaryEndAngle", &LookAndFeelParamWrapper::rotaryEndAngle)
	                .def_readwrite ("slider", &LookAndFeelParamWrapper::slider)
	                .def_readwrite ("idealWidth", &LookAndFeelParamWrapper::idealWidth)
	                .def_readwrite ("idealHeight", &LookAndFeelParamWrapper::idealHeight)
	        ];
	}
};

#endif

