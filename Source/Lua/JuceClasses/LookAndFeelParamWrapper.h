#ifndef LOOK_AND_FEEL_PARAM_WRAPPER
#define LOOK_AND_FEEL_PARAM_WRAPPER

#include "CtrlrMacros.h"

struct LookAndFeelParamWrapper
{
    /* MEMBERS START */
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
	const Font *font;
	Component *component;
	Button *button;
	ImageButton *imageButton;
	TextButton *textButton;
	ToggleButton *toggleButton;
	Colour colour;
	Colour backgroundColour;
	Colour textColour;
	Colour overlayColour;
	const Colour *backgroundColourRef;
	const Colour *colourRef;
	const Colour *textColourPtr;
	const Colour *overlayColourRef;
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
	const Image *icon;
	Image *image;
	const Drawable *drawableIcon;
	bool isSeparator;
	int standardMenuItemHeight;
	int idealWidth;
	int idealHeight;
	float sliderPosProportional, rotaryStartAngle, rotaryEndAngle;
	Slider *slider;
	AlertWindow::AlertIconType  	iconType;
	int numButtons;
	Component *associatedComponent;
	AlertWindow *window;
	const Rectangle<int> *textArea;
	TextLayout *layout;
	ProgressBar *progressBar;
	double progress;
	const String *textToShow;
	ScrollBar *scrollBar;
	const Rectangle<float> *area;
	Rectangle<int> *areaInt;
	const Rectangle<int> *areaIntConst;
	TextEditor *textEditor, *editor;
	Component *keyFocusOwner;
	DirectoryContentsDisplayComponent *directoryContentsDisplayComponent;
	const String *fileSizeDescription;
	const String *fileTimeDescription;
	bool isDirectory;
	bool isItemSelected;
	int itemIndex;
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
	const BorderSize<int> *borderSize;
	ResizableWindow *resizableWindow;
	DocumentWindow *documentWindow;
	Button *minimiseButton;
	Button *maximiseButton;
	Button *closeButton;
	const Justification *justification;
	GroupComponent *groupComponent;
	TabBarButton *tabBarButton;
	const TabBarButton *tabBarButtonConst;
	TabbedButtonBar *tabbedButtonBar;
	Path *p;
	const Path *path;
	TableHeaderComponent *tableHeaderComponent;
	Toolbar *toolbar;
	ToolbarItemComponent *toolbarItemComponent;
	PropertyComponent *propertyComponent;
	CallOutBox *callOutBox;
    /* MEMBERS END */

    LookAndFeelParamWrapper () {}
	LookAndFeelParamWrapper (int colourId_) : colourId(colourId_) {}
	LookAndFeelParamWrapper (int colourId_, Colour colour_) : colourId(colourId_), colour(colour_) {}
	LookAndFeelParamWrapper (const Font &font_) : font(&font_) {}
	LookAndFeelParamWrapper (Component &component_) : component(&component_) {}
	LookAndFeelParamWrapper (Graphics &g_, Button &button_, const Colour &backgroundColourRef_, bool isMouseOverButton_, bool isButtonDown_) : g(&g_), button(&button_), backgroundColourRef(&backgroundColourRef_), isMouseOverButton(isMouseOverButton_), isButtonDown(isButtonDown_) {}
	LookAndFeelParamWrapper (Graphics &g_, TextButton &textButton_, bool isMouseOverButton_, bool isButtonDown_) : g(&g_), textButton(&textButton_), isMouseOverButton(isMouseOverButton_), isButtonDown(isButtonDown_) {}
	LookAndFeelParamWrapper (Graphics &g_, ToggleButton &toggleButton_, bool isMouseOverButton_, bool isButtonDown_) : g(&g_), toggleButton(&toggleButton_), isMouseOverButton(isMouseOverButton_), isButtonDown(isButtonDown_) {}
	LookAndFeelParamWrapper (ToggleButton &toggleButton_) : toggleButton(&toggleButton_) {}
	LookAndFeelParamWrapper (Graphics &g_, Component &component_, float x_, float y_, float w_, float h_, bool ticked_, bool isEnabled_, bool isMouseOverButton_, bool isButtonDown_) : g(&g_), component(&component_), x(x_), y(y_), w(w_), h(h_), ticked(ticked_), isEnabled(isEnabled_), isMouseOverButton(isMouseOverButton_), isButtonDown(isButtonDown_) {}
	LookAndFeelParamWrapper (const String &title_, const String &message_, const String &button1_, const String &button2_, const String &button3_, AlertWindow::AlertIconType iconType_, int numButtons_, Component* component_) : title(&title_), message(&message_), button1(&button1_), button2(&button2_), button3(&button3_), iconType(iconType_), numButtons(numButtons_), component(component_) {}
	LookAndFeelParamWrapper (Graphics &g_, AlertWindow &window_, const Rectangle<int> &textArea_, TextLayout &layout_) : g(&g_), window(&window_), textArea(&textArea_), layout(&layout_) {}
	LookAndFeelParamWrapper (Graphics &g_, ProgressBar &progressBar_, int width_, int height_, double progress_, const String &textToShow_) : g(&g_), progressBar(&progressBar_), width(width_), height(height_), progress(progress_), textToShow(&textToShow_) {}
	LookAndFeelParamWrapper (Graphics &g_, const Colour &colourRef_, int x_, int y_, int w_, int h_) : g(&g_), colourRef(&colourRef_), x(x_), y(y_), w(w_), h(h_) {}
	LookAndFeelParamWrapper (ScrollBar &scrollBar_) : scrollBar(&scrollBar_) {}
	LookAndFeelParamWrapper (float height_) : height(height_) {}

	LookAndFeelParamWrapper (Graphics &g_, const Rectangle<float> &area_, Colour backgroundColour_, bool isOpen_, bool isMouseOver_) : g(&g_), area(&area_), backgroundColour(backgroundColour_), isOpen(isOpen_), isMouseOver(isMouseOver_) {}
	LookAndFeelParamWrapper (Graphics &g_, int width_, int height_, TextEditor &editor_) : g(&g_), width(width_), height(height_), editor(&editor_) {}

	LookAndFeelParamWrapper (Component* component_) : component(component_) {}
	LookAndFeelParamWrapper (const String &title_, const String &instructions_) : title(&title_), instructions(&instructions_) {}
	LookAndFeelParamWrapper (Graphics &g_, int width_, int height_, const String &filename_, Image* icon_, const String &fileSizeDescription_, const String &fileTimeDescription_, bool isDirectory_, bool isItemSelected_, int itemIndex_, DirectoryContentsDisplayComponent &directoryContentsDisplayComponent_) : g(&g_), width(width_), height(height_), filename(&filename_), icon(icon_), fileSizeDescription(&fileSizeDescription_), fileTimeDescription(&fileTimeDescription_), isDirectory(isDirectory_), isItemSelected(isItemSelected_), itemIndex(itemIndex_), directoryContentsDisplayComponent(&directoryContentsDisplayComponent_) {}
	LookAndFeelParamWrapper (FileBrowserComponent &fileBrowserComponent_, DirectoryContentsDisplayComponent *directoryContentsDisplayComponent_, FilePreviewComponent *filePreviewComponent_, ComboBox *comboBox_, TextEditor *textEditor_, Button *goUpButton_) : fileBrowserComponent(&fileBrowserComponent_), directoryContentsDisplayComponent(directoryContentsDisplayComponent_), filePreviewComponent(filePreviewComponent_), comboBox(comboBox_), textEditor(textEditor_), goUpButton(goUpButton_) {}
	LookAndFeelParamWrapper (Graphics &g_, BubbleComponent &bubbleComponent_, const Point<float> &tip_, const Rectangle<float> &body_) : g(&g_), bubbleComponent(&bubbleComponent_), tip(&tip_), body(&body_) {}
	LookAndFeelParamWrapper (Graphics &g_, Component &component_) : g(&g_), component(&component_) {}
	LookAndFeelParamWrapper (Graphics &g_, int width_, int height_) : g(&g_), width(width_), height(height_) {}
	LookAndFeelParamWrapper (Graphics &g_, const Rectangle<int> &areaInt_, bool isSeparator_, bool isActive_, bool isHighlighted_, bool isTicked_, bool hasSubMenu_, const String &text_, const String &shortcutKeyText_, const Drawable* drawableIcon_, const Colour *textColourPtr_) : g(&g_), areaIntConst(&areaInt_), isSeparator(isSeparator_), isActive(isActive_), isHighlighted(isHighlighted_), isTicked(isTicked_), hasSubMenu(hasSubMenu_), text(&text_), shortcutKeyText(&shortcutKeyText_), drawableIcon(drawableIcon_), textColourPtr(textColourPtr_) {}
	LookAndFeelParamWrapper (Graphics &g_, int width_, int height_, bool isScrollUpArrow_) : g(&g_), width(width_), height(height_), isScrollUpArrow(isScrollUpArrow_) {}
	LookAndFeelParamWrapper (const String &text_, bool isSeparator_, int standardMenuItemHeight_, int &idealWidth_, int &idealHeight_) : text(&text_), isSeparator(isSeparator_), standardMenuItemHeight(standardMenuItemHeight_), idealWidth(idealWidth_), idealHeight(idealHeight_) {}
	LookAndFeelParamWrapper (Graphics &g_, int width_, int height_, bool isMouseOverBar_, MenuBarComponent &menuBarComponent_) : g(&g_), width(width_), height(height_), isMouseOverBar(isMouseOverBar_), menuBarComponent(&menuBarComponent_) {}
	LookAndFeelParamWrapper (MenuBarComponent &menuBarComponent_, int itemIndex_, const String &itemText_) : menuBarComponent(&menuBarComponent_), itemIndex(itemIndex_), itemText(&itemText_) {}
	LookAndFeelParamWrapper (Graphics &g_, int width_, int height_, int itemIndex_, const String &itemText_, bool isMouseOverItem_, bool isMenuOpen_, bool isMouseOverBar_, MenuBarComponent &menuBarComponent_) : g(&g_), width(width_), height(height_), itemIndex(itemIndex_), itemText(&itemText_), isMouseOverItem(isMouseOverItem_), isMenuOpen(isMenuOpen_), isMouseOverBar(isMouseOverBar_), menuBarComponent(&menuBarComponent_) {}
	LookAndFeelParamWrapper (Graphics &g_, int width_, int height_, bool isButtonDown_, int buttonX_, int buttonY_, int buttonW_, int buttonH_, ComboBox &comboBox_) : g(&g_), width(width_), height(height_), isButtonDown(isButtonDown_), buttonX(buttonX_), buttonY(buttonY_), buttonW(buttonW_), buttonH(buttonH_), comboBox(&comboBox_) {}
	LookAndFeelParamWrapper (ComboBox &comboBox_) : comboBox(&comboBox_) {}
	LookAndFeelParamWrapper (ComboBox &comboBox_, Label &label_) : comboBox(&comboBox_), label(&label_) {}
	LookAndFeelParamWrapper (Graphics &g_, Label &label_) : g(&g_), label(&label_) {}
	LookAndFeelParamWrapper (Graphics &g_, int x_, int y_, int width_, int height_, float sliderPos_, float minSliderPos_, float maxSliderPos_, const Slider::SliderStyle sliderStyle_, Slider &slider_) : g(&g_), x(x_), y(y_), width(width_), height(height_), sliderPos(sliderPos_), minSliderPos(minSliderPos_), maxSliderPos(maxSliderPos_), sliderStyle(sliderStyle_), slider(&slider_) {}
	LookAndFeelParamWrapper (Slider &slider_) : slider(&slider_) {}
	LookAndFeelParamWrapper (Graphics &g_, int x_, int y_, int width_, int height_, float sliderPosProportional_, float rotaryStartAngle_, float rotaryEndAngle_, Slider &slider_) : g(&g_), x(x_), y(y_), width(width_), height(height_), sliderPosProportional(sliderPosProportional_), rotaryStartAngle(rotaryStartAngle_), rotaryEndAngle(rotaryEndAngle_), slider(&slider_) {}
	LookAndFeelParamWrapper (Slider &slider_, bool isIncrement_) : slider(&slider_), isIncrement(isIncrement_) {}
	LookAndFeelParamWrapper (const String &tipText_, int &width_, int &height_) : tipText(&tipText_), width(width_), height(height_) {}
	LookAndFeelParamWrapper (Graphics &g_, const String &text_, int width_, int height_) : g(&g_), text(&text_), width(width_), height(height_) {}
	LookAndFeelParamWrapper (const String &text_) : text(&text_) {}
	LookAndFeelParamWrapper (FilenameComponent &filenameComponent_, ComboBox* comboBox_, Button* button_) : filenameComponent(&filenameComponent_), comboBox(comboBox_), button(button_) {}
	LookAndFeelParamWrapper (Graphics &g_, const Rectangle<int> &areaInt_, bool isMouseOver_, bool isMouseDown_, ConcertinaPanel &concertinaPanel_, Component &component_) : g(&g_), areaIntConst(&areaInt_), isMouseOver(isMouseOver_), isMouseDown(isMouseDown_), concertinaPanel(&concertinaPanel_), component(&component_) {}
	LookAndFeelParamWrapper (Graphics &g_, int w_, int h_, bool isMouseOver_, bool isMouseDragging_) : g(&g_), w(w_), h(h_), isMouseOver(isMouseOver_), isMouseDragging(isMouseDragging_) {}
	LookAndFeelParamWrapper (Graphics &g_, int w_, int h_, const BorderSize<int> &borderSize_) : g(&g_), w(w_), h(h_), borderSize(&borderSize_) {}
	LookAndFeelParamWrapper (Graphics &g_, int w_, int h_, const BorderSize<int> &borderSize_, ResizableWindow &resizableWindow_) : g(&g_), w(w_), h(h_), borderSize(&borderSize_), resizableWindow(&resizableWindow_) {}
	LookAndFeelParamWrapper (DocumentWindow &documentWindow_, Graphics &g_, int w_, int h_, int titleSpaceX_, int titleSpaceW_, const Image* icon_, bool drawTitleTextOnLeft_) : documentWindow(&documentWindow_), g(&g_), w(w_), h(h_), titleSpaceX(titleSpaceX_), titleSpaceW(titleSpaceW_), icon(icon_), drawTitleTextOnLeft(drawTitleTextOnLeft_) {}
	LookAndFeelParamWrapper (DocumentWindow &documentWindow_, int titleBarX_, int titleBarY_, int titleBarW_, int titleBarH_, Button* minimiseButton_, Button* maximiseButton_, Button* closeButton_, bool positionTitleBarButtonsOnLeft_) : documentWindow(&documentWindow_), titleBarX(titleBarX_), titleBarY(titleBarY_), titleBarW(titleBarW_), titleBarH(titleBarH_), minimiseButton(minimiseButton_), maximiseButton(maximiseButton_), closeButton(closeButton_), positionTitleBarButtonsOnLeft(positionTitleBarButtonsOnLeft_) {}
	LookAndFeelParamWrapper (Graphics &g_, int w_, int h_, const String &text_, const Justification &justification_, GroupComponent &groupComponent_) : g(&g_), w(w_), h(h_), text(&text_), justification(&justification_), groupComponent(&groupComponent_) {}
	LookAndFeelParamWrapper (TabBarButton &tabBarButton_, int tabDepth_) : tabBarButton(&tabBarButton_), tabDepth(tabDepth_) {}
	LookAndFeelParamWrapper (const TabBarButton &tabBarButton_, Rectangle<int> &areaInt_, Component &component_) : tabBarButtonConst(&tabBarButton_), areaInt(&areaInt_), component(&component_) {}
	LookAndFeelParamWrapper (TabBarButton &tabBarButton_, Graphics &g_, bool isMouseOver_, bool isMouseDown_) : tabBarButton(&tabBarButton_), g(&g_), isMouseOver(isMouseOver_), isMouseDown(isMouseDown_) {}
	LookAndFeelParamWrapper (TabbedButtonBar &tabbedButtonBar_, Graphics &g_, int w_, int h_) : tabbedButtonBar(&tabbedButtonBar_), g(&g_), w(w_), h(h_) {}
	LookAndFeelParamWrapper (TabBarButton &tabBarButton_, Path &path_, bool isMouseOver_, bool isMouseDown_) : tabBarButton(&tabBarButton_), path(&path_), isMouseOver(isMouseOver_), isMouseDown(isMouseDown_) {}
	LookAndFeelParamWrapper (TabBarButton &tabBarButton_, Graphics &g_, const Path &path_, bool isMouseOver_, bool isMouseDown_) : tabBarButton(&tabBarButton_), g(&g_), path(&path_), isMouseOver(isMouseOver_), isMouseDown(isMouseDown_) {}
	LookAndFeelParamWrapper (Graphics &g_, Image* image_, int imageX_, int imageY_, int imageW_, int imageH_, const Colour &overlayColourRef_, float imageOpacity_, ImageButton &imageButton_) : g(&g_), image(image_), imageX(imageX_), imageY(imageY_), imageW(imageW_), imageH(imageH_), overlayColourRef(&overlayColourRef_), imageOpacity(imageOpacity_), imageButton(&imageButton_) {}
	LookAndFeelParamWrapper (Graphics &g_, TableHeaderComponent &tableHeaderComponent_) : g(&g_), tableHeaderComponent(&tableHeaderComponent_) {}
	LookAndFeelParamWrapper (Graphics &g_, const String &columnName_, int columnId_, int width_, int height_, bool isMouseOver_, bool isMouseDown_, int columnFlags_) : g(&g_), columnName(&columnName_), columnId(columnId_), width(width_), height(height_), isMouseOver(isMouseOver_), isMouseDown(isMouseDown_), columnFlags(columnFlags_) {}
	LookAndFeelParamWrapper (Graphics &g_, int width_, int height_, Toolbar &toolbar_) : g(&g_), width(width_), height(height_), toolbar(&toolbar_) {}
	LookAndFeelParamWrapper (Toolbar &toolbar_) : toolbar(&toolbar_) {}
	LookAndFeelParamWrapper (Graphics &g_, int width_, int height_, bool isMouseOver_, bool isMouseDown_, ToolbarItemComponent &toolbarItemComponent_) : g(&g_), width(width_), height(height_), isMouseOver(isMouseOver_), isMouseDown(isMouseDown_), toolbarItemComponent(&toolbarItemComponent_) {}
	LookAndFeelParamWrapper (Graphics &g_, int x_, int y_, int width_, int height_, const String &text_, ToolbarItemComponent &toolbarItemComponent_) : g(&g_), x(x_), y(y_), width(width_), height(height_), text(&text_), toolbarItemComponent(&toolbarItemComponent_) {}
	LookAndFeelParamWrapper (Graphics &g_, int w_, int h_, bool isVerticalBar_, bool isMouseOver_, bool isMouseDragging_) : g(&g_), w(w_), h(h_), isVerticalBar(isVerticalBar_), isMouseOver(isMouseOver_), isMouseDragging(isMouseDragging_) {}
	LookAndFeelParamWrapper (Graphics &g_, const String &name_, bool isOpen_, int width_, int height_) : g(&g_), name(&name_), isOpen(isOpen_), width(width_), height(height_) {}
	LookAndFeelParamWrapper (Graphics &g_, int width_, int height_, PropertyComponent &propertyComponent_) : g(&g_), width(width_), height(height_), propertyComponent(&propertyComponent_) {}

	LookAndFeelParamWrapper (PropertyComponent &propertyComponent_) : propertyComponent(&propertyComponent_) {}
	LookAndFeelParamWrapper (CallOutBox &callOutBox_, Graphics &g_, const Path &path_, Image &image_) : callOutBox(&callOutBox_), g(&g_), path(&path_), image(&image_) {}
	LookAndFeelParamWrapper (Graphics &g_, int width_, int height_, float level_) : g(&g_), width(width_), height(height_), level(level_) {}
	LookAndFeelParamWrapper (Graphics &g_, int width_, int height_, Button &button_, const String &keyDescription_) : g(&g_), width(width_), height(height_), button(&button_), keyDescription(&keyDescription_) {}

	static void wrapForLua (lua_State *L)
	{
		using namespace luabind;
		module(L)
		[
			class_<LookAndFeelParamWrapper>("LookAndFeelParamWrapper")
				.def_readonly ("g", &LookAndFeelParamWrapper::g)
				.def_readonly ("x", &LookAndFeelParamWrapper::x)
				.def_readonly ("y", &LookAndFeelParamWrapper::y)
				.def_readonly ("w", &LookAndFeelParamWrapper::w)
				.def_readonly ("h", &LookAndFeelParamWrapper::h)
				.def_readonly ("width", &LookAndFeelParamWrapper::width)
				.def_readonly ("height", &LookAndFeelParamWrapper::height)
				.def_readonly ("colourId", &LookAndFeelParamWrapper::colourId)
				.def_readonly ("buttonX", &LookAndFeelParamWrapper::buttonX)
				.def_readonly ("buttonY", &LookAndFeelParamWrapper::buttonY)
				.def_readonly ("buttonW", &LookAndFeelParamWrapper::buttonW)
				.def_readonly ("buttonH", &LookAndFeelParamWrapper::buttonH)
				.def_readonly ("titleSpaceX", &LookAndFeelParamWrapper::titleSpaceX)
				.def_readonly ("titleSpaceW", &LookAndFeelParamWrapper::titleSpaceW)
				.def_readonly ("buttonType", &LookAndFeelParamWrapper::buttonType)
				.def_readonly ("titleBarX", &LookAndFeelParamWrapper::titleBarX)
				.def_readonly ("titleBarY", &LookAndFeelParamWrapper::titleBarY)
				.def_readonly ("titleBarW", &LookAndFeelParamWrapper::titleBarW)
				.def_readonly ("titleBarH", &LookAndFeelParamWrapper::titleBarH)
				.def_readonly ("tabDepth", &LookAndFeelParamWrapper::tabDepth)
				.def_readonly ("imageX", &LookAndFeelParamWrapper::imageX)
				.def_readonly ("imageY", &LookAndFeelParamWrapper::imageY)
				.def_readonly ("imageW", &LookAndFeelParamWrapper::imageW)
				.def_readonly ("imageH", &LookAndFeelParamWrapper::imageH)
				.def_readonly ("columnId", &LookAndFeelParamWrapper::columnId)
				.def_readonly ("columnFlags", &LookAndFeelParamWrapper::columnFlags)
				.def_readonly ("sliderPos", &LookAndFeelParamWrapper::sliderPos)
				.def_readonly ("minSliderPos", &LookAndFeelParamWrapper::minSliderPos)
				.def_readonly ("maxSliderPos", &LookAndFeelParamWrapper::maxSliderPos)
				.def_readonly ("imageOpacity", &LookAndFeelParamWrapper::imageOpacity)
				.def_readonly ("level", &LookAndFeelParamWrapper::level)
				.def_readonly ("font", &LookAndFeelParamWrapper::font)
				.def_readonly ("component", &LookAndFeelParamWrapper::component)
				.def_readonly ("button", &LookAndFeelParamWrapper::button)
				.def_readonly ("imageButton", &LookAndFeelParamWrapper::imageButton)
				.def_readonly ("textButton", &LookAndFeelParamWrapper::textButton)
				.def_readonly ("toggleButton", &LookAndFeelParamWrapper::toggleButton)
				.def_readonly ("colour", &LookAndFeelParamWrapper::colour)
				.def_readonly ("backgroundColour", &LookAndFeelParamWrapper::backgroundColour)
				.def_readonly ("textColour", &LookAndFeelParamWrapper::textColour)
				.def_readonly ("overlayColour", &LookAndFeelParamWrapper::overlayColour)
				.def_readonly ("backgroundColourRef", &LookAndFeelParamWrapper::backgroundColourRef)
				.def_readonly ("colourRef", &LookAndFeelParamWrapper::colourRef)
				.def_readonly ("textColourPtr", &LookAndFeelParamWrapper::textColourPtr)
				.def_readonly ("overlayColourRef", &LookAndFeelParamWrapper::overlayColourRef)
				.def_readonly ("isMouseOverButton", &LookAndFeelParamWrapper::isMouseOverButton)
				.def_readonly ("isButtonDown", &LookAndFeelParamWrapper::isButtonDown)
				.def_readonly ("ticked", &LookAndFeelParamWrapper::ticked)
				.def_readonly ("isEnabled", &LookAndFeelParamWrapper::isEnabled)
				.def_readonly ("isOpen", &LookAndFeelParamWrapper::isOpen)
				.def_readonly ("isMouseOver", &LookAndFeelParamWrapper::isMouseOver)
				.def_readonly ("isActive", &LookAndFeelParamWrapper::isActive)
				.def_readonly ("isHighlighted", &LookAndFeelParamWrapper::isHighlighted)
				.def_readonly ("isTicked", &LookAndFeelParamWrapper::isTicked)
				.def_readonly ("hasSubMenu", &LookAndFeelParamWrapper::hasSubMenu)
				.def_readonly ("isScrollUpArrow", &LookAndFeelParamWrapper::isScrollUpArrow)
				.def_readonly ("isMouseOverBar", &LookAndFeelParamWrapper::isMouseOverBar)
				.def_readonly ("isMouseOverItem", &LookAndFeelParamWrapper::isMouseOverItem)
				.def_readonly ("isMenuOpen", &LookAndFeelParamWrapper::isMenuOpen)
				.def_readonly ("isIncrement", &LookAndFeelParamWrapper::isIncrement)
				.def_readonly ("isMouseDown", &LookAndFeelParamWrapper::isMouseDown)
				.def_readonly ("isMouseDragging", &LookAndFeelParamWrapper::isMouseDragging)
				.def_readonly ("drawTitleTextOnLeft", &LookAndFeelParamWrapper::drawTitleTextOnLeft)
				.def_readonly ("positionTitleBarButtonsOnLeft", &LookAndFeelParamWrapper::positionTitleBarButtonsOnLeft)
				.def_readonly ("isVerticalBar", &LookAndFeelParamWrapper::isVerticalBar)
				.def_readonly ("keyDescription", &LookAndFeelParamWrapper::keyDescription)
				.def_readonly ("name", &LookAndFeelParamWrapper::name)
				.def_readonly ("text", &LookAndFeelParamWrapper::text)
				.def_readonly ("title", &LookAndFeelParamWrapper::title)
				.def_readonly ("message", &LookAndFeelParamWrapper::message)
				.def_readonly ("button1", &LookAndFeelParamWrapper::button1)
				.def_readonly ("button2", &LookAndFeelParamWrapper::button2)
				.def_readonly ("button3", &LookAndFeelParamWrapper::button3)
				.def_readonly ("instructions", &LookAndFeelParamWrapper::instructions)
				.def_readonly ("filename", &LookAndFeelParamWrapper::filename)
				.def_readonly ("shortcutKeyText", &LookAndFeelParamWrapper::shortcutKeyText)
				.def_readonly ("itemText", &LookAndFeelParamWrapper::itemText)
				.def_readonly ("tipText", &LookAndFeelParamWrapper::tipText)
				.def_readonly ("columnName", &LookAndFeelParamWrapper::columnName)
				.def_readonly ("icon", &LookAndFeelParamWrapper::icon)
				.def_readonly ("image", &LookAndFeelParamWrapper::image)
				.def_readonly ("drawableIcon", &LookAndFeelParamWrapper::drawableIcon)
				.def_readonly ("isSeparator", &LookAndFeelParamWrapper::isSeparator)
				.def_readonly ("standardMenuItemHeight", &LookAndFeelParamWrapper::standardMenuItemHeight)
				.def_readonly ("idealWidth", &LookAndFeelParamWrapper::idealWidth)
				.def_readonly ("idealHeight", &LookAndFeelParamWrapper::idealHeight)
				.def_readonly ("sliderPosProportional", &LookAndFeelParamWrapper::sliderPosProportional)
				.def_readonly ("rotaryStartAngle", &LookAndFeelParamWrapper::rotaryStartAngle)
				.def_readonly ("rotaryEndAngle", &LookAndFeelParamWrapper::rotaryEndAngle)
				.def_readonly ("slider", &LookAndFeelParamWrapper::slider)
				.def_readonly ("iconType", &LookAndFeelParamWrapper::iconType)
				.def_readonly ("numButtons", &LookAndFeelParamWrapper::numButtons)
				.def_readonly ("associatedComponent", &LookAndFeelParamWrapper::associatedComponent)
				.def_readonly ("window", &LookAndFeelParamWrapper::window)
				.def_readonly ("textArea", &LookAndFeelParamWrapper::textArea)
				.def_readonly ("layout", &LookAndFeelParamWrapper::layout)
				.def_readonly ("progressBar", &LookAndFeelParamWrapper::progressBar)
				.def_readonly ("progress", &LookAndFeelParamWrapper::progress)
				.def_readonly ("textToShow", &LookAndFeelParamWrapper::textToShow)
				.def_readonly ("scrollBar", &LookAndFeelParamWrapper::scrollBar)
				.def_readonly ("area", &LookAndFeelParamWrapper::area)
				.def_readonly ("areaInt", &LookAndFeelParamWrapper::areaInt)
				.def_readonly ("areaIntConst", &LookAndFeelParamWrapper::areaIntConst)
				.def_readonly ("editor", &LookAndFeelParamWrapper::editor)
				.def_readonly ("keyFocusOwner", &LookAndFeelParamWrapper::keyFocusOwner)
				.def_readonly ("directoryContentsDisplayComponent", &LookAndFeelParamWrapper::directoryContentsDisplayComponent)
				.def_readonly ("fileSizeDescription", &LookAndFeelParamWrapper::fileSizeDescription)
				.def_readonly ("fileTimeDescription", &LookAndFeelParamWrapper::fileTimeDescription)
				.def_readonly ("isDirectory", &LookAndFeelParamWrapper::isDirectory)
				.def_readonly ("isItemSelected", &LookAndFeelParamWrapper::isItemSelected)
				.def_readonly ("itemIndex", &LookAndFeelParamWrapper::itemIndex)
				.def_readonly ("fileBrowserComponent", &LookAndFeelParamWrapper::fileBrowserComponent)
				.def_readonly ("filePreviewComponent", &LookAndFeelParamWrapper::filePreviewComponent)
				.def_readonly ("currentPathBox", &LookAndFeelParamWrapper::currentPathBox)
				.def_readonly ("filenameBox", &LookAndFeelParamWrapper::filenameBox)
				.def_readonly ("goUpButton", &LookAndFeelParamWrapper::goUpButton)
				.def_readonly ("bubbleComponent", &LookAndFeelParamWrapper::bubbleComponent)
				.def_readonly ("tip", &LookAndFeelParamWrapper::tip)
				.def_readonly ("body", &LookAndFeelParamWrapper::body)
				.def_readonly ("menuBarComponent", &LookAndFeelParamWrapper::menuBarComponent)
				.def_readonly ("comboBox", &LookAndFeelParamWrapper::comboBox)
				.def_readonly ("label", &LookAndFeelParamWrapper::label)
				.def_readonly ("sliderStyle", &LookAndFeelParamWrapper::sliderStyle)
				.def_readonly ("filenameComponent", &LookAndFeelParamWrapper::filenameComponent)
				.def_readonly ("concertinaPanel", &LookAndFeelParamWrapper::concertinaPanel)
				.def_readonly ("borderSize", &LookAndFeelParamWrapper::borderSize)
				.def_readonly ("resizableWindow", &LookAndFeelParamWrapper::resizableWindow)
				.def_readonly ("documentWindow", &LookAndFeelParamWrapper::documentWindow)
				.def_readonly ("minimiseButton", &LookAndFeelParamWrapper::minimiseButton)
				.def_readonly ("maximiseButton", &LookAndFeelParamWrapper::maximiseButton)
				.def_readonly ("closeButton", &LookAndFeelParamWrapper::closeButton)
				.def_readonly ("justification", &LookAndFeelParamWrapper::justification)
				.def_readonly ("groupComponent", &LookAndFeelParamWrapper::groupComponent)
				.def_readonly ("tabBarButton", &LookAndFeelParamWrapper::tabBarButton)
				.def_readonly ("tabbedButtonBar", &LookAndFeelParamWrapper::tabbedButtonBar)
				.def_readonly ("p", &LookAndFeelParamWrapper::p)
				.def_readonly ("path", &LookAndFeelParamWrapper::path)
				.def_readonly ("tableHeaderComponent", &LookAndFeelParamWrapper::tableHeaderComponent)
				.def_readonly ("toolbar", &LookAndFeelParamWrapper::toolbar)
				.def_readonly ("toolbarItemComponent", &LookAndFeelParamWrapper::toolbarItemComponent)
				.def_readonly ("propertyComponent", &LookAndFeelParamWrapper::propertyComponent)
				.def_readonly ("callOutBox", &LookAndFeelParamWrapper::callOutBox)
			];
		}

};

#endif

