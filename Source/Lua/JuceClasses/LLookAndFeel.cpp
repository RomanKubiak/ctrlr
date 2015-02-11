#include "stdafx.h"
#include "LLookAndFeel.h"
#include <luabind/adopt_policy.hpp>

#define TRY_CALL(method,...)\
if (methods.contains(#method))\
{\
    try \
    {\
        luabind::call_function<void>(methods[#method], __VA_ARGS__);\
    }\
    catch (luabind::error &e)\
    {\
        _WRN(luabind::object_cast <std::string> (luabind::object(luabind::from_stack(e.state(), -1))));\
    }\
}\
else\
{\
   LookAndFeel_V3::method(__VA_ARGS__);\
}

#define TRY_CALL_RET(method,ReturnType,ReturnWhenError,...)\
if (methods.contains(#method))\
{\
    try \
    {\
        return (luabind::call_function<ReturnType>(methods[#method], ##__VA_ARGS__));\
    }\
    catch (luabind::error &e)\
    {\
        _WRN(luabind::object_cast <std::string> (luabind::object(luabind::from_stack(e.state(), -1))));\
		return (ReturnWhenError);\
    }\
}\
else\
{\
   return (LookAndFeel_V3::method(__VA_ARGS__));\
}

#define TRY_CALL_RET_NOP(method,ReturnType,ReturnWhenError,...)\
if (methods.contains(#method))\
{\
    try \
    {\
        return (luabind::call_function<ReturnType>(methods[#method]));\
    }\
    catch (luabind::error &e)\
    {\
        _WRN(luabind::object_cast <std::string> (luabind::object(luabind::from_stack(e.state(), -1))));\
		return (ReturnWhenError);\
    }\
}\
else\
{\
   return (LookAndFeel_V3::method());\
}

LookAndFeelBase::LookAndFeelBase()
{
}

void LookAndFeelBase::setMethod (const String &methodName, const luabind::object &method)
{
    _DBG("LookAndFeelBase::setMethod name="+methodName);
    if (luabind::type(method) != LUA_TNIL)
    {
        _DBG("\tmethod looks valid, set it in hash table");
        methods.set (methodName, method);
    }
    else
    {
        _DBG("\tmethod looks like a null pointer, clear it");
        methods.remove(methodName);
    }
}

void LookAndFeelBase::setImplementation (const luabind::object &implementationAsTable)
{
    _DBG("LookAndFeelBase::setImplementation");
    if (luabind::type(implementationAsTable) == LUA_TTABLE)
    {
        for (luabind::iterator i(implementationAsTable), end; i!=end; ++i)
        {
            String key          = luabind::object_cast<std::string>(i.key());
            luabind::object val = *i;

            if (luabind::type(val) == LUA_TFUNCTION)
            {
                _DBG("\tfound a function for implementation \""+key+"\"");
                setMethod (key, val);
            }
        }
    }
}

void LookAndFeelBase::wrapForLua (lua_State *L)
{
    using namespace luabind;

	module(L)
    [
		class_<LookAndFeelBase>("LookAndFeel")
            .def(constructor<>())
            .def("setMethod", &LookAndFeelBase::setMethod)
            .def("setImplementation", &LookAndFeelBase::setImplementation)
            .scope
            [
                def("createLabel", &LookAndFeelBase::createLabel),
                def("createTextButton", &LookAndFeelBase::createTextButton),
                def("createImageButton", &LookAndFeelBase::createImageButton),
                def("createToggleButton", &LookAndFeelBase::createToggleButton),
                def("createDropShadowEffect", &LookAndFeelBase::createDropShadowEffect),
                def("createGlowEffect", &LookAndFeelBase::createGlowEffect),
                def("createDrawableComposite", &LookAndFeelBase::createDrawableComposite),
                def("createDrawableImage", &LookAndFeelBase::createDrawableImage),
                def("createDrawablePath", &LookAndFeelBase::createDrawablePath),
                def("createDrawableRectangle", &LookAndFeelBase::createDrawableRectangle),
                def("createDrawableText", &LookAndFeelBase::createDrawableText)
            ]
    ];
}

Colour LookAndFeelBase::findColour(int colourId)
{
	TRY_CALL_RET (findColour, Colour, Colour(), colourId);
}

void LookAndFeelBase::setColour(int colourId, Colour colour)
{
    TRY_CALL(setColour, colourId, colour);
}

bool LookAndFeelBase::isColourSpecified(int colourId)
{
	TRY_CALL_RET (isColourSpecified, bool, false, colourId);
}

Typeface::Ptr LookAndFeelBase::getTypefaceForFont(const Font &font)
{
	TRY_CALL_RET (getTypefaceForFont, Typeface::Ptr, Typeface::Ptr(), font);
}

MouseCursor LookAndFeelBase::getMouseCursorFor(Component &component)
{
	TRY_CALL_RET (getMouseCursorFor, MouseCursor, MouseCursor(), boost::ref(component));
}

void LookAndFeelBase::drawButtonBackground(Graphics &g, Button &button, const Colour &backgroundColourRef, bool isMouseOverButton, bool isButtonDown)
{
    TRY_CALL(drawButtonBackground, boost::ref(g), boost::ref(button), backgroundColourRef, isMouseOverButton, isButtonDown);
}

void LookAndFeelBase::drawButtonText(Graphics &g, TextButton &textButton, bool isMouseOverButton, bool isButtonDown)
{
    TRY_CALL(drawButtonText, boost::ref(g), boost::ref(textButton), isMouseOverButton, isButtonDown);
}

void LookAndFeelBase::drawToggleButton(Graphics &g, ToggleButton &toggleButton, bool isMouseOverButton, bool isButtonDown)
{
    TRY_CALL(drawToggleButton, boost::ref(g), boost::ref(toggleButton), isMouseOverButton, isButtonDown);
}

void LookAndFeelBase::changeToggleButtonWidthToFitText(ToggleButton &toggleButton)
{
    TRY_CALL(changeToggleButtonWidthToFitText, boost::ref(toggleButton));
}

void LookAndFeelBase::drawTickBox(Graphics &g, Component &component, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown)
{
    TRY_CALL(drawTickBox, boost::ref(g), boost::ref(component), x, y, w, h, ticked, isEnabled, isMouseOverButton, isButtonDown);
}

AlertWindow* LookAndFeelBase::createAlertWindow(const String &title, const String &message, const String &button1, const String &button2, const String &button3, AlertWindow::AlertIconType iconType, int numButtons, Component* component)
{
	using namespace luabind;

    if (methods.contains("createAlertWindow"))
    {
        try
        {
            AlertWindow *wnd = call_function<AlertWindow*>(
                methods["createAlertWindow"], title, message, button1, button2, button3, iconType, numButtons, component
            );

            if (wnd != nullptr)
            {
                return (wnd);
            }

            return (LookAndFeel_V3::createAlertWindow(title, message, button1, button2, button3, iconType, numButtons, component));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createAlertWindow(title, message, button1, button2, button3, iconType, numButtons, component));
        }
    }
    else
    {
        return (LookAndFeel_V3::createAlertWindow(title, message, button1, button2, button3, iconType, numButtons, component));
    }
}

void LookAndFeelBase::drawAlertBox(Graphics &g, AlertWindow &window, const Rectangle<int> &textArea, TextLayout &layout)
{
    TRY_CALL(drawAlertBox,boost::ref(g), boost::ref(window), textArea, boost::ref(layout));
}

int LookAndFeelBase::getAlertBoxWindowFlags()
{
	TRY_CALL_RET_NOP(getAlertBoxWindowFlags, int, 0);
}

int LookAndFeelBase::getAlertWindowButtonHeight()
{
	TRY_CALL_RET_NOP(getAlertWindowButtonHeight, int, 0);
}

Font LookAndFeelBase::getAlertWindowMessageFont()
{
	TRY_CALL_RET_NOP(getAlertWindowMessageFont, Font, Font());
}

Font LookAndFeelBase::getAlertWindowFont()
{
	TRY_CALL_RET_NOP(getAlertWindowFont, Font, Font());
}

void LookAndFeelBase::drawProgressBar(Graphics &g, ProgressBar &progressBar, int width, int height, double progress, const String &textToShow)
{
    TRY_CALL(drawProgressBar, boost::ref(g), boost::ref(progressBar), width, height, progress, textToShow);
}

void LookAndFeelBase::drawSpinningWaitAnimation(Graphics &g, const Colour &colourRef, int x, int y, int w, int h)
{
    TRY_CALL(drawSpinningWaitAnimation, boost::ref(g), colourRef, x, y, w, h);
}

bool LookAndFeelBase::areScrollbarButtonsVisible()
{
	TRY_CALL_RET_NOP(areScrollbarButtonsVisible, bool, true);
}

ImageEffectFilter* LookAndFeelBase::getScrollbarEffect()
{
	using namespace luabind;

    if (methods.contains("getSliderEffect"))
    {
        try
        {
            ImageEffectFilter *eff = call_function<ImageEffectFilter*>(
                methods["getScrollbarEffect"]
            );

            if (eff != nullptr)
            {
                return (eff);
            }

            return (LookAndFeel_V3::getScrollbarEffect());
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::getScrollbarEffect());
        }
    }
    else
    {
        return (LookAndFeel_V3::getScrollbarEffect());
    }
}

int LookAndFeelBase::getMinimumScrollbarThumbSize(ScrollBar &scrollBar)
{
	TRY_CALL_RET(getMinimumScrollbarThumbSize, int, 0, boost::ref(scrollBar));
}

int LookAndFeelBase::getDefaultScrollbarWidth()
{
	TRY_CALL_RET_NOP(getDefaultScrollbarWidth, int, 0);
}

int LookAndFeelBase::getScrollbarButtonSize(ScrollBar &scrollBar)
{
	TRY_CALL_RET(getScrollbarButtonSize, int, 0, boost::ref(scrollBar));
}

Path LookAndFeelBase::getTickShape(float height)
{
	TRY_CALL_RET(getTickShape, Path, Path(), height);
}

Path LookAndFeelBase::getCrossShape(float height)
{
	TRY_CALL_RET(getCrossShape, Path, Path(), height);
}

void LookAndFeelBase::drawTreeviewPlusMinusBox(Graphics &g, const Rectangle<float> &area, Colour backgroundColour, bool isOpen, bool isMouseOver)
{
    TRY_CALL(drawTreeviewPlusMinusBox, boost::ref(g), area, backgroundColour, isOpen, isMouseOver);
}

void LookAndFeelBase::fillTextEditorBackground(Graphics &g, int width, int height, TextEditor &editor)
{
    TRY_CALL(fillTextEditorBackground, boost::ref(g), width, height, boost::ref(editor));
}

void LookAndFeelBase::drawTextEditorOutline(Graphics &g, int width, int height, TextEditor &editor)
{
    TRY_CALL(drawTextEditorOutline, boost::ref(g), width, height, boost::ref(editor));
}

CaretComponent* LookAndFeelBase::createCaretComponent(Component* component)
{
	TRY_CALL_RET(createCaretComponent, CaretComponent*, nullptr, component);
}

const Drawable* LookAndFeelBase::getDefaultFolderImage()
{
    using namespace luabind;

    if (methods.contains("getDefaultFolderImage"))
    {
        try
        {
            Drawable *drw = call_function<Drawable*>(
                methods["getDefaultFolderImage"]
            );

            if (drw != nullptr)
            {
                return (drw);
            }

            return (LookAndFeel_V3::getDefaultFolderImage());
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::getDefaultFolderImage());
        }
    }
    else
    {
        return (LookAndFeel_V3::getDefaultFolderImage());
    }
}

const Drawable* LookAndFeelBase::getDefaultDocumentFileImage()
{
	using namespace luabind;

    if (methods.contains("getDefaultDocumentFileImage"))
    {
        try
        {
            Drawable *drw = call_function<Drawable*>(
                methods["getDefaultDocumentFileImage"]
            );

            if (drw != nullptr)
            {
                return (drw);
            }

            return (LookAndFeel_V3::getDefaultDocumentFileImage());
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::getDefaultDocumentFileImage());
        }
    }
    else
    {
        return (LookAndFeel_V3::getDefaultDocumentFileImage());
    }
}

AttributedString LookAndFeelBase::createFileChooserHeaderText(const String &title, const String &instructions)
{
	TRY_CALL_RET(createFileChooserHeaderText, AttributedString, AttributedString(title+instructions), title, instructions);
}

void LookAndFeelBase::drawFileBrowserRow(Graphics &g, int width, int height, const String &filename, Image* icon, const String &fileSizeDescription, const String &fileTimeDescription, bool isDirectory, bool isItemSelected, int itemIndex, DirectoryContentsDisplayComponent &directoryContentsDisplayComponent)
{
    TRY_CALL(drawFileBrowserRow, boost::ref(g), width, height, filename, icon, fileSizeDescription, fileTimeDescription, isDirectory, isItemSelected, itemIndex, boost::ref(directoryContentsDisplayComponent));
}

Button* LookAndFeelBase::createFileBrowserGoUpButton()
{
	using namespace luabind;

    if (methods.contains("createFileBrowserGoUpButton"))
    {
        try
        {
            Button *b = call_function<Button*>(
                methods["createFileBrowserGoUpButton"]
            );

            if (b != nullptr)
            {
                return (b);
            }

            return (LookAndFeel_V3::createFileBrowserGoUpButton());
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createFileBrowserGoUpButton());
        }
    }
    else
    {
        return (LookAndFeel_V3::createFileBrowserGoUpButton());
    }
}

void LookAndFeelBase::layoutFileBrowserComponent(FileBrowserComponent &fileBrowserComponent, DirectoryContentsDisplayComponent *directoryContentsDisplayComponent, FilePreviewComponent *filePreviewComponent, ComboBox *comboBox, TextEditor *textEditor, Button *goUpButton)
{
    TRY_CALL(layoutFileBrowserComponent, boost::ref(fileBrowserComponent), directoryContentsDisplayComponent, filePreviewComponent, comboBox, textEditor, goUpButton);
}

void LookAndFeelBase::drawBubble(Graphics &g, BubbleComponent &bubbleComponent, const Point<float> &tip, const Rectangle<float> &body)
{
    TRY_CALL(drawBubble, boost::ref(g), boost::ref(bubbleComponent), tip, body);
}

void LookAndFeelBase::drawLasso(Graphics &g, Component &component)
{
    TRY_CALL(drawLasso, boost::ref(g), boost::ref(component));
}

void LookAndFeelBase::drawPopupMenuBackground(Graphics &g, int width, int height)
{
    TRY_CALL(drawPopupMenuBackground, boost::ref(g), width, height);
}

void LookAndFeelBase::drawPopupMenuItem(Graphics &g, const Rectangle<int> &area, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const String &text, const String &shortcutKeyText, const Drawable* icon, const Colour *textColour)
{
	TRY_CALL(drawPopupMenuItem, boost::ref(g),boost::ref(area),isSeparator,isActive,isHighlighted,isTicked,hasSubMenu,text,shortcutKeyText,icon,textColour);
}

Font LookAndFeelBase::getPopupMenuFont()
{
	TRY_CALL_RET_NOP(getPopupMenuFont, Font, Font());
}

void LookAndFeelBase::drawPopupMenuUpDownArrow(Graphics &g, int width, int height, bool isScrollUpArrow)
{
    TRY_CALL(drawPopupMenuUpDownArrow, boost::ref(g), width, height, isScrollUpArrow);
}

void LookAndFeelBase::getIdealPopupMenuItemSize(const String &text, bool isSeparator, int standardMenuItemHeight, int &idealWidth, int &idealHeight)
{
    TRY_CALL(getIdealPopupMenuItemSize, text, isSeparator, standardMenuItemHeight, boost::ref(idealWidth), boost::ref(idealHeight));
}

int LookAndFeelBase::getMenuWindowFlags()
{
	TRY_CALL_RET_NOP(getMenuWindowFlags, int, 0);
}

void LookAndFeelBase::drawMenuBarBackground(Graphics &g, int width, int height, bool isMouseOverBar, MenuBarComponent &menuBarComponent)
{
    TRY_CALL(drawMenuBarBackground, boost::ref(g), width, height, isMouseOverBar, boost::ref(menuBarComponent));
}

int LookAndFeelBase::getMenuBarItemWidth(MenuBarComponent &menuBarComponent, int itemIndex, const String &itemText)
{
	TRY_CALL_RET(getMenuBarItemWidth, int, 0, boost::ref(menuBarComponent), itemIndex, itemText);
}

Font LookAndFeelBase::getMenuBarFont(MenuBarComponent &menuBarComponent, int itemIndex, const String &itemText)
{
	TRY_CALL_RET(getMenuBarFont, Font, Font(), boost::ref(menuBarComponent), itemIndex, itemText);
}

void LookAndFeelBase::drawMenuBarItem(Graphics &g, int width, int height, int itemIndex, const String &itemText, bool isMouseOverItem, bool isMenuOpen, bool isMouseOverBar, MenuBarComponent &menuBarComponent)
{
    TRY_CALL(drawMenuBarItem, boost::ref(g), width, height, itemIndex, itemText, isMouseOverItem, isMenuOpen, isMouseOverBar, boost::ref(menuBarComponent));
}

void LookAndFeelBase::drawComboBox(Graphics &g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox &comboBox)
{
    TRY_CALL(drawComboBox, boost::ref(g), width, height, isButtonDown, buttonX, buttonY, buttonW, buttonH, boost::ref(comboBox));
}

Font LookAndFeelBase::getComboBoxFont(ComboBox &comboBox)
{
	TRY_CALL_RET(getComboBoxFont, Font, Font(), boost::ref(comboBox));
}

Label* LookAndFeelBase::createComboBoxTextBox(ComboBox &comboBox)
{
    using namespace luabind;

    if (methods.contains("createComboBoxTextBox"))
    {
        try
        {
            Label *l = call_function<Label*>(
                methods["createComboBoxTextBox"],
                boost::ref(comboBox)
            );

            if (l != nullptr)
            {
                return (l);
            }

            return (LookAndFeel_V3::createComboBoxTextBox(comboBox));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createComboBoxTextBox(comboBox));
        }
    }
    else
    {
        return (LookAndFeel_V3::createComboBoxTextBox(comboBox));
    }
}

void LookAndFeelBase::positionComboBoxText(ComboBox &comboBox, Label &label)
{
    TRY_CALL(positionComboBoxText, boost::ref(comboBox), boost::ref(label));
}

void LookAndFeelBase::drawLabel(Graphics &g, Label &label)
{
	TRY_CALL(drawLabel, boost::ref(g),boost::ref(label));
}

void LookAndFeelBase::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle sliderStyle, Slider &slider)
{
    TRY_CALL(drawLinearSlider, boost::ref(g), x, y, width, height, sliderPos, minSliderPos, maxSliderPos, sliderStyle, boost::ref(slider));
}

void LookAndFeelBase::drawLinearSliderBackground(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle sliderStyle, Slider &slider)
{
    TRY_CALL(drawLinearSliderBackground, boost::ref(g), x, y, width, height, sliderPos, minSliderPos, maxSliderPos, sliderStyle, boost::ref(slider));
}

void LookAndFeelBase::drawLinearSliderThumb(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle sliderStyle, Slider &slider)
{
    TRY_CALL(drawLinearSliderThumb, boost::ref(g), x, y, width, height, sliderPos, minSliderPos, maxSliderPos, sliderStyle, boost::ref(slider));
}

int LookAndFeelBase::getSliderThumbRadius(Slider &slider)
{
	TRY_CALL_RET(getSliderThumbRadius, int, 0, boost::ref(slider));
}

void LookAndFeelBase::drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider)
{
	TRY_CALL(drawRotarySlider,boost::ref(g),x,y,width,height,sliderPosProportional,rotaryStartAngle,rotaryEndAngle,boost::ref(slider));
}

Button* LookAndFeelBase::createSliderButton(Slider &slider, bool isIncrement)
{
	using namespace luabind;

    if (methods.contains("createSliderButton"))
    {
        try
        {
            Button *b = call_function<Button*>(
                methods["createSliderButton"],
                boost::ref(slider), isIncrement
            );

            if (b != nullptr)
            {
                return (b);
            }

            return (LookAndFeel_V3::createSliderButton(slider, isIncrement));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createSliderButton(slider, isIncrement));
        }
    }
    else
    {
        return (LookAndFeel_V3::createSliderButton(slider, isIncrement));
    }
}

Label* LookAndFeelBase::createSliderTextBox(Slider &slider)
{
	using namespace luabind;

    if (methods.contains("createSliderTextBox"))
    {
        try
        {
            Label *l = call_function<Label*>(
                methods["createSliderTextBox"],
                boost::ref(slider)
            );

            if (l != nullptr)
            {
                return (l);
            }

            return (LookAndFeel_V3::createSliderTextBox(slider));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createSliderTextBox(slider));
        }
    }
    else
    {
        return (LookAndFeel_V3::createSliderTextBox(slider));
    }
}

ImageEffectFilter* LookAndFeelBase::getSliderEffect(Slider &slider)
{
    using namespace luabind;

    if (methods.contains("getSliderEffect"))
    {
        try
        {
            ImageEffectFilter *b = call_function<ImageEffectFilter*>(
                methods["getSliderEffect"],
                boost::ref(slider)
            );

            if (b != nullptr)
            {
                return (b);
            }

            return (LookAndFeel_V3::getSliderEffect(slider));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::getSliderEffect(slider));
        }
    }
    else
    {
        return (LookAndFeel_V3::getSliderEffect(slider));
    }
}

void LookAndFeelBase::getTooltipSize(const String &tipText, int &width, int &height)
{
    TRY_CALL(getTooltipSize, tipText, boost::ref(width), boost::ref(height));
}

void LookAndFeelBase::drawTooltip(Graphics &g, const String &text, int width, int height)
{
    TRY_CALL(drawTooltip, boost::ref(g), text, width, height);
}

Button* LookAndFeelBase::createFilenameComponentBrowseButton(const String &text)
{
	using namespace luabind;

    if (methods.contains("createFilenameComponentBrowseButton"))
    {
        try
        {
            Button *b = call_function<Button*>(
                methods["createFilenameComponentBrowseButton"],
                text
            );

            if (b != nullptr)
            {
                return (b);
            }

            return (LookAndFeel_V3::createFilenameComponentBrowseButton(text));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createFilenameComponentBrowseButton(text));
        }
    }
    else
    {
        return (LookAndFeel_V3::createFilenameComponentBrowseButton(text));
    }
}

void LookAndFeelBase::layoutFilenameComponent(FilenameComponent &filenameComponent, ComboBox* comboBox, Button* button)
{
    TRY_CALL(layoutFilenameComponent, boost::ref(filenameComponent), comboBox, button);
}

void LookAndFeelBase::drawConcertinaPanelHeader(Graphics &g, const Rectangle<int> &areaInt, bool isMouseOver, bool isMouseDown, ConcertinaPanel &concertinaPanel, Component &component)
{
    TRY_CALL(drawConcertinaPanelHeader, boost::ref(g), areaInt, isMouseOver, isMouseDown, boost::ref(concertinaPanel), boost::ref(component));
}

void LookAndFeelBase::drawCornerResizer(Graphics &g, int w, int h, bool isMouseOver, bool isMouseDragging)
{
    TRY_CALL(drawCornerResizer, boost::ref(g), w, h, isMouseOver, isMouseDragging);
}

void LookAndFeelBase::drawResizableFrame(Graphics &g, int w, int h, const BorderSize<int> &borderSize)
{
    TRY_CALL(drawResizableFrame, boost::ref(g), w, h, borderSize);
}

void LookAndFeelBase::fillResizableWindowBackground(Graphics &g, int w, int h, const BorderSize<int> &borderSize, ResizableWindow &resizableWindow)
{
    TRY_CALL(fillResizableWindowBackground, boost::ref(g), w, h, borderSize, boost::ref(resizableWindow));
}

void LookAndFeelBase::drawResizableWindowBorder(Graphics &g, int w, int h, const BorderSize<int> &borderSize, ResizableWindow &resizableWindow)
{
    TRY_CALL(drawResizableWindowBorder, boost::ref(g), w, h, borderSize, boost::ref(resizableWindow));
}

void LookAndFeelBase::drawDocumentWindowTitleBar(DocumentWindow &documentWindow, Graphics &g, int w, int h, int titleSpaceX, int titleSpaceW, const Image* icon, bool drawTitleTextOnLeft)
{
    TRY_CALL(drawDocumentWindowTitleBar, boost::ref(documentWindow), boost::ref(g), w, h, titleSpaceX, titleSpaceW, icon, drawTitleTextOnLeft);
}

Button* LookAndFeelBase::createDocumentWindowButton(int buttonType)
{
	using namespace luabind;

    if (methods.contains("createDocumentWindowButton"))
    {
        try
        {
            Button *b = call_function<Button*>(
                methods["createDocumentWindowButton"],
                buttonType
            );

            if (b != nullptr)
            {
                return (b);
            }

            return (LookAndFeel_V3::createDocumentWindowButton(buttonType));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createDocumentWindowButton(buttonType));
        }
    }
    else
    {
        return (LookAndFeel_V3::createDocumentWindowButton(buttonType));
    }
}

void LookAndFeelBase::positionDocumentWindowButtons(DocumentWindow &documentWindow, int titleBarX, int titleBarY, int titleBarW, int titleBarH, Button* minimiseButton, Button* maximiseButton, Button* closeButton, bool positionTitleBarButtonsOnLeft)
{
    TRY_CALL(positionDocumentWindowButtons, boost::ref(documentWindow), titleBarX, titleBarY, titleBarW, titleBarH, minimiseButton, maximiseButton, closeButton, positionTitleBarButtonsOnLeft);
}

int LookAndFeelBase::getDefaultMenuBarHeight()
{
	TRY_CALL_RET_NOP(getDefaultMenuBarHeight, int, 0);
}

DropShadower* LookAndFeelBase::createDropShadowerForComponent(Component* component)
{
	using namespace luabind;

    if (methods.contains("createDropShadowerForComponent"))
    {
        try
        {
            DropShadower *s = call_function<DropShadower*>(
                methods["createDropShadowerForComponent"],
                component
            );

            if (s != nullptr)
            {
                return (s);
            }

            return (LookAndFeel_V3::createDropShadowerForComponent(component));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createDropShadowerForComponent(component));
        }
    }
    else
    {
        return (LookAndFeel_V3::createDropShadowerForComponent(component));
    }
}

void LookAndFeelBase::drawGroupComponentOutline(Graphics &g, int w, int h, const String &text, const Justification &justification, GroupComponent &groupComponent)
{
    TRY_CALL(drawGroupComponentOutline, boost::ref(g), w, h, text, justification, boost::ref(groupComponent));
}

int LookAndFeelBase::getTabButtonSpaceAroundImage()
{
	TRY_CALL_RET_NOP(getTabButtonSpaceAroundImage, int, 0);
}

int LookAndFeelBase::getTabButtonOverlap(int tabDepth)
{
	TRY_CALL_RET(getTabButtonOverlap, int, 0, tabDepth);
}

int LookAndFeelBase::getTabButtonBestWidth(TabBarButton &tabBarButton, int tabDepth)
{
	TRY_CALL_RET(getTabButtonBestWidth, int, 0, boost::ref(tabBarButton), tabDepth);
}

Rectangle<int> LookAndFeelBase::getTabButtonExtraComponentBounds(const TabBarButton &tabBarButton, Rectangle<int> &areaInt, Component &component)
{
	TRY_CALL_RET(getTabButtonExtraComponentBounds, Rectangle<int>, Rectangle<int>(), boost::ref(tabBarButton), areaInt, boost::ref(component));
}

void LookAndFeelBase::drawTabButton(TabBarButton &tabBarButton, Graphics &g, bool isMouseOver, bool isMouseDown)
{
    TRY_CALL(drawTabButton, boost::ref(tabBarButton), boost::ref(g), isMouseOver, isMouseDown);
}

void LookAndFeelBase::drawTabButtonText(TabBarButton &tabBarButton, Graphics &g, bool isMouseOver, bool isMouseDown)
{
    TRY_CALL(drawTabButtonText, boost::ref(tabBarButton), boost::ref(g), isMouseOver, isMouseDown);
}

void LookAndFeelBase::drawTabAreaBehindFrontButton(TabbedButtonBar &tabbedButtonBar, Graphics &g, int w, int h)
{
    TRY_CALL(drawTabAreaBehindFrontButton, boost::ref(tabbedButtonBar), boost::ref(g), w, h);
}

void LookAndFeelBase::createTabButtonShape(TabBarButton &tabBarButton, Path &path, bool isMouseOver, bool isMouseDown)
{
    TRY_CALL(createTabButtonShape, boost::ref(tabBarButton), boost::ref(path), isMouseOver, isMouseDown);
}

void LookAndFeelBase::fillTabButtonShape(TabBarButton &tabBarButton, Graphics &g, const Path &path, bool isMouseOver, bool isMouseDown)
{
    TRY_CALL(drawTabButton, boost::ref(tabBarButton), boost::ref(g), isMouseOver, isMouseDown);
}

Button* LookAndFeelBase::createTabBarExtrasButton()
{
	using namespace luabind;

    if (methods.contains("createTabBarExtrasButton"))
    {
        try
        {
            Button *b = call_function<Button*>(
                methods["createTabBarExtrasButton"]
            );

            if (b != nullptr)
            {
                return (b);
            }

            return (LookAndFeel_V3::createTabBarExtrasButton());
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createTabBarExtrasButton());
        }
    }
    else
    {
        return (LookAndFeel_V3::createTabBarExtrasButton());
    }
}

void LookAndFeelBase::drawImageButton(Graphics &g, Image* image, int imageX, int imageY, int imageW, int imageH, const Colour &overlayColourRef, float imageOpacity, ImageButton &imageButton)
{
    TRY_CALL(drawImageButton, boost::ref(g), image, imageX, imageY, imageW, imageH, overlayColourRef, imageOpacity, boost::ref(imageButton));
}

void LookAndFeelBase::drawTableHeaderBackground(Graphics &g, TableHeaderComponent &tableHeaderComponent)
{
    TRY_CALL(drawTableHeaderBackground, boost::ref(g), boost::ref(tableHeaderComponent));
}

void LookAndFeelBase::drawTableHeaderColumn(Graphics &g, const String &columnName, int columnId, int width, int height, bool isMouseOver, bool isMouseDown, int columnFlags)
{
    TRY_CALL(drawTableHeaderColumn, boost::ref(g), columnName, columnId, width, height, isMouseOver, isMouseDown, columnFlags);
}

void LookAndFeelBase::paintToolbarBackground(Graphics &g, int width, int height, Toolbar &toolbar)
{
    TRY_CALL(paintToolbarBackground, boost::ref(g), width, height, boost::ref(toolbar));
}

Button* LookAndFeelBase::createToolbarMissingItemsButton(Toolbar &toolbar)
{
	using namespace luabind;

    if (methods.contains("createToolbarMissingItemsButton"))
    {
        try
        {
            Button *b = call_function<Button*>(
                methods["createToolbarMissingItemsButton"],
                boost::ref(toolbar)
            );

            if (b != nullptr)
            {
                return (b);
            }

            return (LookAndFeel_V3::createToolbarMissingItemsButton(toolbar));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createToolbarMissingItemsButton(toolbar));
        }
    }
    else
    {
        return (LookAndFeel_V3::createToolbarMissingItemsButton(toolbar));
    }
}

void LookAndFeelBase::paintToolbarButtonBackground(Graphics &g, int width, int height, bool isMouseOver, bool isMouseDown, ToolbarItemComponent &toolbarItemComponent)
{
    TRY_CALL(paintToolbarButtonBackground, boost::ref(g), width, height, isMouseOver, isMouseDown, boost::ref(toolbarItemComponent));
}

void LookAndFeelBase::paintToolbarButtonLabel(Graphics &g, int x, int y, int width, int height, const String &text, ToolbarItemComponent &toolbarItemComponent)
{
    TRY_CALL(paintToolbarButtonLabel, boost::ref(g), x, y, width, height, text, boost::ref(toolbarItemComponent));
}

void LookAndFeelBase::drawStretchableLayoutResizerBar(Graphics &g, int w, int h, bool isVerticalBar, bool isMouseOver, bool isMouseDragging)
{
    TRY_CALL(drawStretchableLayoutResizerBar, boost::ref(g), w, h, isVerticalBar, isMouseOver, isMouseDragging);
}

void LookAndFeelBase::drawPropertyPanelSectionHeader(Graphics &g, const String &name, bool isOpen, int width, int height)
{
    TRY_CALL(drawPropertyPanelSectionHeader, boost::ref(g), name, isOpen, width, height);
}

void LookAndFeelBase::drawPropertyComponentBackground(Graphics &g, int width, int height, PropertyComponent &propertyComponent)
{
    TRY_CALL(drawPropertyComponentBackground, boost::ref(g), width, height, boost::ref(propertyComponent));
}

void LookAndFeelBase::drawPropertyComponentLabel(Graphics &g, int width, int height, PropertyComponent &propertyComponent)
{
    TRY_CALL(drawPropertyComponentLabel, boost::ref(g), width, height, boost::ref(propertyComponent));
}

Rectangle<int> LookAndFeelBase::getPropertyComponentContentPosition(PropertyComponent &propertyComponent)
{
	TRY_CALL_RET(getPropertyComponentContentPosition, Rectangle<int>, Rectangle<int>(), boost::ref(propertyComponent));
}

void LookAndFeelBase::drawCallOutBoxBackground(CallOutBox &callOutBox, Graphics &g, const Path &path, Image &image)
{
    TRY_CALL(drawCallOutBoxBackground, boost::ref(callOutBox), boost::ref(g), path, boost::ref(image));
}

void LookAndFeelBase::drawLevelMeter(Graphics &g, int width, int height, float level)
{
    TRY_CALL(drawLevelMeter, boost::ref(g), width, height, level);
}

void LookAndFeelBase::drawKeymapChangeButton(Graphics &g, int width, int height, Button &button, const String &keyDescription)
{
    TRY_CALL(drawKeymapChangeButton, boost::ref(g), width, height, boost::ref(button), keyDescription);
}
