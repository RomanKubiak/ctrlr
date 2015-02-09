#include "stdafx.h"
#include "LookAndFeelBase.h"
#include "LLookAndFeel.h"

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

Colour LookAndFeelBase::findColour(int colourId)
{
}

void LookAndFeelBase::setColour(int colourId, Colour colour)
{
}

bool LookAndFeelBase::isColourSpecified(int colourId)
{
}

Typeface::Ptr LookAndFeelBase::getTypefaceForFont(const Font &font)
{
}

MouseCursor LookAndFeelBase::getMouseCursorFor(Component &component)
{
}

void LookAndFeelBase::drawButtonBackground(Graphics &g, Button &button, const Colour &backgroundColourRef, bool isMouseOverButton, bool isButtonDown)
{
}

void LookAndFeelBase::drawButtonText(Graphics &g, TextButton &textButton, bool isMouseOverButton, bool isButtonDown)
{
}

void LookAndFeelBase::drawToggleButton(Graphics &g, ToggleButton &toggleButton, bool isMouseOverButton, bool isButtonDown)
{
}

void LookAndFeelBase::changeToggleButtonWidthToFitText(ToggleButton &toggleButton)
{
}

void LookAndFeelBase::drawTickBox(Graphics &g, Component &component, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown)
{
}

AlertWindow* LookAndFeelBase::createAlertWindow(const String &title, const String &message, const String &button1, const String &button2, const String &button3, AlertWindow::AlertIconType iconType, int numButtons, Component* component)
{
}

void LookAndFeelBase::drawAlertBox(Graphics &g, AlertWindow &window, const Rectangle<int> &textArea, TextLayout &layout)
{
}

int LookAndFeelBase::getAlertBoxWindowFlags()
{
}

int LookAndFeelBase::getAlertWindowButtonHeight()
{
}

Font LookAndFeelBase::getAlertWindowMessageFont()
{
}

Font LookAndFeelBase::getAlertWindowFont()
{
}

void LookAndFeelBase::drawProgressBar(Graphics &g, ProgressBar &progressBar, int width, int height, double progress, const String &textToShow)
{
}

void LookAndFeelBase::drawSpinningWaitAnimation(Graphics &g, const Colour &colourRef, int x, int y, int w, int h)
{
}

bool LookAndFeelBase::areScrollbarButtonsVisible()
{
}

ImageEffectFilter* LookAndFeelBase::getScrollbarEffect()
{
}

int LookAndFeelBase::getMinimumScrollbarThumbSize(ScrollBar &scrollBar)
{
}

int LookAndFeelBase::getDefaultScrollbarWidth()
{
}

int LookAndFeelBase::getScrollbarButtonSize(ScrollBar &scrollBar)
{
}

Path LookAndFeelBase::getTickShape(float height)
{
}

Path LookAndFeelBase::getCrossShape(float height)
{
}

void LookAndFeelBase::drawTreeviewPlusMinusBox(Graphics &g, const Rectangle<float> &area, Colour backgroundColour, bool isOpen, bool isMouseOver)
{
}

void LookAndFeelBase::fillTextEditorBackground(Graphics &g, int width, int height, TextEditor &editor)
{
}

void LookAndFeelBase::drawTextEditorOutline(Graphics &g, int width, int height, TextEditor &editor)
{
}

CaretComponent* LookAndFeelBase::createCaretComponent(Component* component)
{
}

const Drawable* LookAndFeelBase::getDefaultFolderImage()
{
}

const Drawable* LookAndFeelBase::getDefaultDocumentFileImage()
{
}

AttributedString LookAndFeelBase::createFileChooserHeaderText(const String &title, const String &instructions)
{
}

void LookAndFeelBase::drawFileBrowserRow(Graphics &g, int width, int height, const String &filename, Image* icon, const String &fileSizeDescription, const String &fileTimeDescription, bool isDirectory, bool isItemSelected, int itemIndex, DirectoryContentsDisplayComponent &directoryContentsDisplayComponent)
{
}

Button* LookAndFeelBase::createFileBrowserGoUpButton()
{
}

void LookAndFeelBase::layoutFileBrowserComponent(FileBrowserComponent &fileBrowserComponent, DirectoryContentsDisplayComponent *directoryContentsDisplayComponent, FilePreviewComponent *filePreviewComponent, ComboBox *comboBox, TextEditor *textEditor, Button *goUpButton)
{
}

void LookAndFeelBase::drawBubble(Graphics &g, BubbleComponent &bubbleComponent, const Point<float> &tip, const Rectangle<float> &body)
{
}

void LookAndFeelBase::drawLasso(Graphics &g, Component &component)
{
}

void LookAndFeelBase::drawPopupMenuBackground(Graphics &g, int width, int height)
{
}

void LookAndFeelBase::drawPopupMenuItem(Graphics &g, const Rectangle<int> &area, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const String &text, const String &shortcutKeyText, const Drawable* icon, const Colour *textColour)
{
	TRY_CALL(drawPopupMenuItem, boost::ref(g),boost::ref(area),isSeparator,isActive,isHighlighted,isTicked,hasSubMenu,text,shortcutKeyText,icon,textColour);
}

Font LookAndFeelBase::getPopupMenuFont()
{
}

void LookAndFeelBase::drawPopupMenuUpDownArrow(Graphics &g, int width, int height, bool isScrollUpArrow)
{
}

void LookAndFeelBase::getIdealPopupMenuItemSize(const String &text, bool isSeparator, int standardMenuItemHeight, int &idealWidth, int &idealHeight)
{
}

int LookAndFeelBase::getMenuWindowFlags()
{
}

void LookAndFeelBase::drawMenuBarBackground(Graphics &g, int width, int height, bool isMouseOverBar, MenuBarComponent &menuBarComponent)
{
}

int LookAndFeelBase::getMenuBarItemWidth(MenuBarComponent &menuBarComponent, int itemIndex, const String &itemText)
{
}

Font LookAndFeelBase::getMenuBarFont(MenuBarComponent &menuBarComponent, int itemIndex, const String &itemText)
{
}

void LookAndFeelBase::drawMenuBarItem(Graphics &g, int width, int height, int itemIndex, const String &itemText, bool isMouseOverItem, bool isMenuOpen, bool isMouseOverBar, MenuBarComponent &menuBarComponent)
{
}

void LookAndFeelBase::drawComboBox(Graphics &g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox &comboBox)
{
}

Font LookAndFeelBase::getComboBoxFont(ComboBox &comboBox)
{
}

Label* LookAndFeelBase::createComboBoxTextBox(ComboBox &comboBox)
{
}

void LookAndFeelBase::positionComboBoxText(ComboBox &comboBox, Label &label)
{
}

void LookAndFeelBase::drawLabel(Graphics &g, Label &label)
{
	TRY_CALL(drawLabel, boost::ref(g),boost::ref(label));
}

void LookAndFeelBase::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle sliderStyle, Slider &slider)
{
}

void LookAndFeelBase::drawLinearSliderBackground(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle sliderStyle, Slider &slider)
{
}

void LookAndFeelBase::drawLinearSliderThumb(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle sliderStyle, Slider &slider)
{
}

int LookAndFeelBase::getSliderThumbRadius(Slider &slider)
{
}

void LookAndFeelBase::drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider)
{
	TRY_CALL(drawRotarySlider,boost::ref(g),x,y,width,height,sliderPosProportional,rotaryStartAngle,rotaryEndAngle,boost::ref(slider));
}

Button* LookAndFeelBase::createSliderButton(Slider &slider, bool isIncrement)
{
}

Label* LookAndFeelBase::createSliderTextBox(Slider &slider)
{
}

ImageEffectFilter* LookAndFeelBase::getSliderEffect(Slider &slider)
{
}

void LookAndFeelBase::getTooltipSize(const String &tipText, int &width, int &height)
{
}

void LookAndFeelBase::drawTooltip(Graphics &g, const String &text, int width, int height)
{
}

Button* LookAndFeelBase::createFilenameComponentBrowseButton(const String &text)
{
}

void LookAndFeelBase::layoutFilenameComponent(FilenameComponent &filenameComponent, ComboBox* comboBox, Button* button)
{
}

void LookAndFeelBase::drawConcertinaPanelHeader(Graphics &g, const Rectangle<int> &areaInt, bool isMouseOver, bool isMouseDown, ConcertinaPanel &concertinaPanel, Component &component)
{
}

void LookAndFeelBase::drawCornerResizer(Graphics &g, int w, int h, bool isMouseOver, bool isMouseDragging)
{
}

void LookAndFeelBase::drawResizableFrame(Graphics &g, int w, int h, const BorderSize<int> &borderSize)
{
}

void LookAndFeelBase::fillResizableWindowBackground(Graphics &g, int w, int h, const BorderSize<int> &borderSize, ResizableWindow &resizableWindow)
{
}

void LookAndFeelBase::drawResizableWindowBorder(Graphics &g, int w, int h, const BorderSize<int> &borderSize, ResizableWindow &resizableWindow)
{
}

void LookAndFeelBase::drawDocumentWindowTitleBar(DocumentWindow &documentWindow, Graphics &g, int w, int h, int titleSpaceX, int titleSpaceW, const Image* icon, bool drawTitleTextOnLeft)
{
}

Button* LookAndFeelBase::createDocumentWindowButton(int buttonType)
{
}

void LookAndFeelBase::positionDocumentWindowButtons(DocumentWindow &documentWindow, int titleBarX, int titleBarY, int titleBarW, int titleBarH, Button* minimiseButton, Button* maximiseButton, Button* closeButton, bool positionTitleBarButtonsOnLeft)
{
}

int LookAndFeelBase::getDefaultMenuBarHeight()
{
}

DropShadower* LookAndFeelBase::createDropShadowerForComponent(Component* component)
{
}

void LookAndFeelBase::drawGroupComponentOutline(Graphics &g, int w, int h, const String &text, const Justification &justification, GroupComponent &groupComponent)
{
}

int LookAndFeelBase::getTabButtonSpaceAroundImage()
{
}

int LookAndFeelBase::getTabButtonOverlap(int tabDepth)
{
}

int LookAndFeelBase::getTabButtonBestWidth(TabBarButton &tabBarButton, int tabDepth)
{
}

Rectangle<int> LookAndFeelBase::getTabButtonExtraComponentBounds(const TabBarButton &tabBarButton, Rectangle<int> &areaInt, Component &component)
{
}

void LookAndFeelBase::drawTabButton(TabBarButton &tabBarButton, Graphics &g, bool isMouseOver, bool isMouseDown)
{
}

void LookAndFeelBase::drawTabButtonText(TabBarButton &tabBarButton, Graphics &g, bool isMouseOver, bool isMouseDown)
{
}

void LookAndFeelBase::drawTabAreaBehindFrontButton(TabbedButtonBar &tabbedButtonBar, Graphics &g, int w, int h)
{
}

void LookAndFeelBase::createTabButtonShape(TabBarButton &tabBarButton, Path &path, bool isMouseOver, bool isMouseDown)
{
}

void LookAndFeelBase::fillTabButtonShape(TabBarButton &tabBarButton, Graphics &g, const Path &path, bool isMouseOver, bool isMouseDown)
{
}

Button* LookAndFeelBase::createTabBarExtrasButton()
{
}

void LookAndFeelBase::drawImageButton(Graphics &g, Image* image, int imageX, int imageY, int imageW, int imageH, const Colour &overlayColourRef, float imageOpacity, ImageButton &imageButton)
{
}

void LookAndFeelBase::drawTableHeaderBackground(Graphics &g, TableHeaderComponent &tableHeaderComponent)
{
}

void LookAndFeelBase::drawTableHeaderColumn(Graphics &g, const String &columnName, int columnId, int width, int height, bool isMouseOver, bool isMouseDown, int columnFlags)
{
}

void LookAndFeelBase::paintToolbarBackground(Graphics &g, int width, int height, Toolbar &toolbar)
{
}

Button* LookAndFeelBase::createToolbarMissingItemsButton(Toolbar &toolbar)
{
}

void LookAndFeelBase::paintToolbarButtonBackground(Graphics &g, int width, int height, bool isMouseOver, bool isMouseDown, ToolbarItemComponent &toolbarItemComponent)
{
}

void LookAndFeelBase::paintToolbarButtonLabel(Graphics &g, int x, int y, int width, int height, const String &text, ToolbarItemComponent &toolbarItemComponent)
{
}

void LookAndFeelBase::drawStretchableLayoutResizerBar(Graphics &g, int w, int h, bool isVerticalBar, bool isMouseOver, bool isMouseDragging)
{
}

void LookAndFeelBase::drawPropertyPanelSectionHeader(Graphics &g, const String &name, bool isOpen, int width, int height)
{
}

void LookAndFeelBase::drawPropertyComponentBackground(Graphics &g, int width, int height, PropertyComponent &propertyComponent)
{
}

void LookAndFeelBase::drawPropertyComponentLabel(Graphics &g, int width, int height, PropertyComponent &propertyComponent)
{
}

Rectangle<int> LookAndFeelBase::getPropertyComponentContentPosition(PropertyComponent &propertyComponent)
{
}

void LookAndFeelBase::drawCallOutBoxBackground(CallOutBox &callOutBox, Graphics &g, const Path &path, Image &image)
{
}

void LookAndFeelBase::drawLevelMeter(Graphics &g, int width, int height, float level)
{
}

void LookAndFeelBase::drawKeymapChangeButton(Graphics &g, int width, int height, Button &button, const String &keyDescription)
{
}
