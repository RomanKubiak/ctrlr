#!/bin/bash
HEADER="$1"

if [ ! -f "$HEADER" ]; then
	echo "Need the header as parameter"
	exit 1
fi

cat << _EOF_
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

_EOF_

cat $HEADER | grep "def_" | awk '
function rindex(str,c)
{
	return (match(str,"\\" c "[^" c "]*$") ? RSTART : 0);
}
{
	constNow 	= 0;
	hack 		= 0;
	numParams	= 0;
	numRefParams	= 0;
	retTypeOffset  	= 2;
	funcNameOffset 	= 3;
	paramsOffset   	= 5;
	needsToReturn  	= 0;
	numRawParams	= 0;
	methodName	= "";
	returnType	= "";
	returnTypeStr	= "";

	for (i=1; i<=NF; i++)
	{
		if (i == retTypeOffset)
		{
			# Return type
			# printf ("[rettype] offset %d value %s\n", i, $i);
			if ($i == "const")
			{
				funcNameOffset++;
				paramsOffset++;
				needsToReturn = 1;
				returnType = sprintf ("const %s", $(i+1));
			}
			else if ($i != "void")
			{
				needsToReturn = 1;
				returnType = sprintf ("%s", $i);
			}
			else
			{
				needsToReturn = 0;
				returnType = sprintf ("void");
			}

			# printf ("returnType=%s funcNameOffset=%d\n", returnType, funcNameOffset);
		}

		if (i == funcNameOffset)
		{
			# printf ("[method] offset %d value %s\n", i, $i);
			methodName = sprintf ("%s", substr ($i,5));
			# printf ("methodName=%s\n", methodName);
		}
		if (i > paramsOffset)
		{
			#printf ("[params] offset %d value [%s]\n", i, $i);
			isReference 	= 0;

			if ($i == "const" && constNow == 0)
			{
				rawParams[++numRawParams] = sprintf ("const");
				constNow = 1;
				continue;
			}

			if (constNow == 1)
			{
				if ($i == "const")
				{
					rawParams[++numRawParams] = sprintf ("const");
					hack = 0;
					constNow = 0;
					continue;
				}
				else
				{
					hack = 1;
				}
			}

			param = i;
			if (index($param, ")"))
				$param = substr ($param, 0, index($param, ")") - 1);

			rawParams[++numRawParams] = sprintf ("%s", $param);

			if (index($param, ","))
				$param = substr ($param, 0, index($param, ",") - 1);



			if (index($param, "&"))
			{
				isReference = 1;
				$param = substr ($param, 2);
			}

			if (index($param, "*"))
			{
				$param = substr ($param, 2);
			}

			if (index($param, "<"))
				$param = substr ($param, 0, index($param, "<") - 1);


			if (hack)
			{
				if (! (i%2))
				{
					paramArray[++numParams] 	= param;
					paramRefArray[numParams] 	= isReference;
				}
			}
			else
			{
				if (i%2)
				{
					paramArray[++numParams] 	= param;
					paramRefArray[numParams]	= isReference;
				}
			}
		}
	}

	if (numParams > 0)
	{
		printf ("\n");
		printf ("\tLookAndFeelParamWrapper (");
		for (x=1;x<=numRawParams;x++)
		{
			if (x == numRawParams || numRawParams == 0)
			{
				printf ("%s_", rawParams[x])
			}
			else
			{
				if (rindex(rawParams[x], ",") > 0)
				{
					printf ("%s_, ", substr (rawParams[x], 0, index (rawParams[x], ",") - 1));
				}
				else
				{
					printf ("%s ", rawParams[x]);
				}
			}
		}

		printf (") : ");
		for (x=1;x<=numParams;x++)
		{
			if (x==numParams || numParams==0)
			{
				printf ("%s(%s%s_)", $paramArray[x], paramRefArray[x] ? "&" : "", $paramArray[x]);
			}
			else
			{
				printf ("%s(%s%s_), ", $paramArray[x], paramRefArray[x] ? "&" : "", $paramArray[x]);
			}
		}
		printf (" {}");
	}
}'

cat << _EOF_
	
	static void wrapForLua (lua_State *L)
	{
		using namespace luabind;
		module(L)
		[
	            class_<LookAndFeelParamWrapper>("LookAndFeelParamWrapper")
	            	.def_readwrite ("idealWidth", &LookAndFeelParamWrapper::idealWidth)
	                .def_readwrite ("idealHeight", &LookAndFeelParamWrapper::idealHeight)
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
	                
	        ];
	}
_EOF_
echo "};"
echo
echo "#endif"
echo