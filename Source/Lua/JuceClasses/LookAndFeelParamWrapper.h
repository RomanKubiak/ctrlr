#ifndef LOOK_AND_FEEL_PARAM_WRAPPER
#define LOOK_AND_FEEL_PARAM_WRAPPER

#include "CtrlrMacros.h"

struct LookAndFeelParamWrapper
{
	LookAndFeelParamWrapper(Graphics &_g, int _x, int _y, int _width, int _height, float _sliderPosProportional, float _rotaryStartAngle, float _rotaryEndAngle, Slider &_slider)
		:   g(&_g),
            x(_x),
            y(_y),
            width(_width),
            height(_height),
            sliderPosProportional(_sliderPosProportional),
            rotaryStartAngle(_rotaryStartAngle),
            rotaryEndAngle(_rotaryEndAngle),
            slider(&_slider) {}

	LookAndFeelParamWrapper(const String &_text, bool _isSeparator, int _standardMenuItemHeight, int &_idealWidth, int &_idealHeight)
		:   text(_text),
            isSeparator(_isSeparator),
            standardMenuItemHeight(_standardMenuItemHeight),
            idealWidth(_idealWidth),
            idealHeight(_idealHeight) {}

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

	Font font;
	Component *component;
	Button *button;
	ImageButton *imageButton;
	TextButton *textButton;
	ToggleButton *toggleButton;
	Colour colour;
	Colour backgroundColour;
	Colour textColour;
	Colour overlayColour;

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

    String keyDescription;
    String name;
    String text;
	String title;
	String message;
	String button1;
	String button2;
	String button3;
	String instructions;
	String filename;
	String shortcutKeyText;
	String itemText;
	String tipText;
    String columnName;

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
    Rectangle<int> textArea;
    TextLayout *layout;
    /* drawAlertBox */

    /* drawProgressBar */
    ProgressBar *progressBar;
    double progress;
    String textToShow;
    /* drawProgressBar */

    ScrollBar *scrollBar;

    Rectangle<float> area;
    Rectangle<int> areaInt;

    TextEditor *textEditor;

    Component *keyFocusOwner;

    /* def_drawFileBrowserRow */
    DirectoryContentsDisplayComponent *directoryContentsDisplayComponent;
    String fileSizeDescription;
    String fileTimeDescription;
    bool isDirectory;
    bool isItemSelected;
    int itemIndex;
    /* def_drawFileBrowserRow */

    FileBrowserComponent *fileBrowserComponent;
    FilePreviewComponent *filePreviewComponent;
    ComboBox *currentPathBox;
    TextEditor *filenameBox;
    Button *goUpButton;

    BubbleComponent *bubble;
    const Point<float> tip;
    const Rectangle<float> body;

    MenuBarComponent *menuBarComponent;

    ComboBox *comboBox;
    Label *label;

    Slider::SliderStyle sliderStyle;

    FilenameComponent *filenameComponent;

    ConcertinaPanel *concertinaPanel;

    BorderSize<int> borderSize;

    ResizableWindow *resizableWindow;
    DocumentWindow *documentWindow;

    Button *minimiseButton;
    Button *maximiseButton;
    Button *closeButton;

    Justification *justification;
    GroupComponent *groupComponent;

    TabBarButton *tabBarButton;
    TabbedButtonBar *tabbedButtonBar;
    Path *p;

    TableHeaderComponent *tableHeaderComponent;

    Toolbar *toolbar;
    ToolbarItemComponent *toolbarItemComponent;

    PropertyComponent *propertyComponent;

    CallOutBox *callOutBox;

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
