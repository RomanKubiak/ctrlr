#include "stdafx.h"
#include "LookAndFeelBase.h"
#include "LLookAndFeel.h"
#include "LookAndFeelParamWrapper.h"


Colour LookAndFeelBase::findColour(int colourId)
{
	LookAndFeelParamWrapper p (colourId);
	owner.findColour(p);
}

void LookAndFeelBase::setColour(int colourId, Colour colour)
{
	LookAndFeelParamWrapper p (colourId, colour);
	owner.setColour(p);
}

bool LookAndFeelBase::isColourSpecified(int colourId)
{
	LookAndFeelParamWrapper p (colourId);
	owner.isColourSpecified(p);
}

Typeface::Ptr LookAndFeelBase::getTypefaceForFont(const Font &font)
{
	LookAndFeelParamWrapper p (font);
	owner.getTypefaceForFont(p);
}

MouseCursor LookAndFeelBase::getMouseCursorFor(Component &component)
{
	LookAndFeelParamWrapper p (component);
	owner.getMouseCursorFor(p);
}

void LookAndFeelBase::drawButtonBackground(Graphics &g, Button &button, const Colour &backgroundColourRef, bool isMouseOverButton, bool isButtonDown)
{
	LookAndFeelParamWrapper p (g, button, backgroundColourRef, isMouseOverButton, isButtonDown);
	owner.drawButtonBackground(p);
}

void LookAndFeelBase::drawButtonText(Graphics &g, TextButton &textButton, bool isMouseOverButton, bool isButtonDown)
{
	LookAndFeelParamWrapper p (g, textButton, isMouseOverButton, isButtonDown);
	owner.drawButtonText(p);
}

void LookAndFeelBase::drawToggleButton(Graphics &g, ToggleButton &toggleButton, bool isMouseOverButton, bool isButtonDown)
{
	LookAndFeelParamWrapper p (g, toggleButton, isMouseOverButton, isButtonDown);
	owner.drawToggleButton(p);
}

void LookAndFeelBase::changeToggleButtonWidthToFitText(ToggleButton &toggleButton)
{
	LookAndFeelParamWrapper p (toggleButton);
	owner.changeToggleButtonWidthToFitText(p);
}

void LookAndFeelBase::drawTickBox(Graphics &g, Component &component, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown)
{
	LookAndFeelParamWrapper p (g, component, x, y, w, h, ticked, isEnabled, isMouseOverButton, isButtonDown);
	owner.drawTickBox(p);
}

AlertWindow* LookAndFeelBase::createAlertWindow(const String &title, const String &message, const String &button1, const String &button2, const String &button3, AlertWindow::AlertIconType iconType, int numButtons, Component* component)
{
	LookAndFeelParamWrapper p (title, message, button1, button2, button3, iconType, numButtons, component);
	owner.createAlertWindow(p);
}

void LookAndFeelBase::drawAlertBox(Graphics &g, AlertWindow &window, const Rectangle<int> &textArea, TextLayout &layout)
{
	LookAndFeelParamWrapper p (g, window, textArea, layout);
	owner.drawAlertBox(p);
}

int LookAndFeelBase::getAlertBoxWindowFlags(
{
	LookAndFeelParamWrapper p ();
	owner.getAlertBoxWindowFlags(p);
}

int LookAndFeelBase::getAlertWindowButtonHeight(
{
	LookAndFeelParamWrapper p ();
	owner.getAlertWindowButtonHeight(p);
}

Font LookAndFeelBase::getAlertWindowMessageFont(
{
	LookAndFeelParamWrapper p ();
	owner.getAlertWindowMessageFont(p);
}

Font LookAndFeelBase::getAlertWindowFont(
{
	LookAndFeelParamWrapper p ();
	owner.getAlertWindowFont(p);
}

void LookAndFeelBase::drawProgressBar(Graphics &g, ProgressBar &progressBar, int width, int height, double progress, const String &textToShow)
{
	LookAndFeelParamWrapper p (g, progressBar, width, height, progress, textToShow);
	owner.drawProgressBar(p);
}

void LookAndFeelBase::drawSpinningWaitAnimation(Graphics &g, const Colour &colourRef, int x, int y, int w, int h)
{
	LookAndFeelParamWrapper p (g, colourRef, x, y, w, h);
	owner.drawSpinningWaitAnimation(p);
}

bool LookAndFeelBase::areScrollbarButtonsVisible(
{
	LookAndFeelParamWrapper p ();
	owner.areScrollbarButtonsVisible(p);
}

ImageEffectFilter* LookAndFeelBase::getScrollbarEffect(
{
	LookAndFeelParamWrapper p ();
	owner.getScrollbarEffect(p);
}

int LookAndFeelBase::getMinimumScrollbarThumbSize(ScrollBar &scrollBar)
{
	LookAndFeelParamWrapper p (scrollBar);
	owner.getMinimumScrollbarThumbSize(p);
}

int LookAndFeelBase::getDefaultScrollbarWidth(
{
	LookAndFeelParamWrapper p ();
	owner.getDefaultScrollbarWidth(p);
}

int LookAndFeelBase::getScrollbarButtonSize(ScrollBar &scrollBar)
{
	LookAndFeelParamWrapper p (scrollBar);
	owner.getScrollbarButtonSize(p);
}

Path LookAndFeelBase::getTickShape(float height)
{
	LookAndFeelParamWrapper p (height);
	owner.getTickShape(p);
}

Path LookAndFeelBase::getCrossShape(float height)
{
	LookAndFeelParamWrapper p (height);
	owner.getCrossShape(p);
}

void LookAndFeelBase::drawTreeviewPlusMinusBox(Graphics &g, const Rectangle<float> &area, Colour backgroundColour, bool isOpen, bool isMouseOver)
{
	LookAndFeelParamWrapper p (g, area, backgroundColour, isOpen, isMouseOver);
	owner.drawTreeviewPlusMinusBox(p);
}

void LookAndFeelBase::fillTextEditorBackground(Graphics &g, int width, int height, TextEditor &editor)
{
	LookAndFeelParamWrapper p (g, width, height, editor);
	owner.fillTextEditorBackground(p);
}

void LookAndFeelBase::drawTextEditorOutline(Graphics &g, int width, int height, TextEditor &editor)
{
	LookAndFeelParamWrapper p (g, width, height, editor);
	owner.drawTextEditorOutline(p);
}

CaretComponent* LookAndFeelBase::createCaretComponent(Component* component)
{
	LookAndFeelParamWrapper p (component);
	owner.createCaretComponent(p);
}

const Drawable* LookAndFeelBase::getDefaultFolderImage(
{
	LookAndFeelParamWrapper p ();
	owner.getDefaultFolderImage(p);
}

const Drawable* LookAndFeelBase::getDefaultDocumentFileImage(
{
	LookAndFeelParamWrapper p ();
	owner.getDefaultDocumentFileImage(p);
}

AttributedString LookAndFeelBase::createFileChooserHeaderText(const String &title, const String &instructions)
{
	LookAndFeelParamWrapper p (title, instructions);
	owner.createFileChooserHeaderText(p);
}

void LookAndFeelBase::drawFileBrowserRow(Graphics &g, int width, int height, const String &filename, Image* icon, const String &fileSizeDescription, const String &fileTimeDescription, bool isDirectory, bool isItemSelected, int itemIndex, DirectoryContentsDisplayComponent &directoryContentsDisplayComponent)
{
	LookAndFeelParamWrapper p (g, width, height, filename, icon, fileSizeDescription, fileTimeDescription, isDirectory, isItemSelected, itemIndex, directoryContentsDisplayComponent);
	owner.drawFileBrowserRow(p);
}

Button* LookAndFeelBase::createFileBrowserGoUpButton(
{
	LookAndFeelParamWrapper p ();
	owner.createFileBrowserGoUpButton(p);
}

void LookAndFeelBase::layoutFileBrowserComponent(FileBrowserComponent &fileBrowserComponent, DirectoryContentsDisplayComponent *directoryContentsDisplayComponent, FilePreviewComponent *filePreviewComponent, ComboBox *comboBox, TextEditor *textEditor, Button *goUpButton)
{
	LookAndFeelParamWrapper p (fileBrowserComponent, directoryContentsDisplayComponent, filePreviewComponent, comboBox, textEditor, goUpButton);
	owner.layoutFileBrowserComponent(p);
}

void LookAndFeelBase::drawBubble(Graphics &g, BubbleComponent &bubbleComponent, const Point<float> &tip, const Rectangle<float> &body)
{
	LookAndFeelParamWrapper p (g, bubbleComponent, tip, body);
	owner.drawBubble(p);
}

void LookAndFeelBase::drawLasso(Graphics &g, Component &component)
{
	LookAndFeelParamWrapper p (g, component);
	owner.drawLasso(p);
}

void LookAndFeelBase::drawPopupMenuBackground(Graphics &g, int width, int height)
{
	LookAndFeelParamWrapper p (g, width, height);
	owner.drawPopupMenuBackground(p);
}

void LookAndFeelBase::drawPopupMenuItem(Graphics &g, const Rectangle<int> &areaInt, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const String &text, const String &shortcutKeyText, const Drawable* drawableIcon, const Colour *textColourPtr)
{
	LookAndFeelParamWrapper p (g, areaInt, isSeparator, isActive, isHighlighted, isTicked, hasSubMenu, text, shortcutKeyText, drawableIcon, textColourPtr);
	owner.drawPopupMenuItem(p);
}

Font LookAndFeelBase::getPopupMenuFont(
{
	LookAndFeelParamWrapper p ();
	owner.getPopupMenuFont(p);
}

void LookAndFeelBase::drawPopupMenuUpDownArrow(Graphics &g, int width, int height, bool isScrollUpArrow)
{
	LookAndFeelParamWrapper p (g, width, height, isScrollUpArrow);
	owner.drawPopupMenuUpDownArrow(p);
}

void LookAndFeelBase::getIdealPopupMenuItemSize(const String &text, bool isSeparator, int standardMenuItemHeight, int &idealWidth, int &idealHeight)
{
	LookAndFeelParamWrapper p (text, isSeparator, standardMenuItemHeight, idealWidth, idealHeight);
	owner.getIdealPopupMenuItemSize(p);
}

int LookAndFeelBase::getMenuWindowFlags(
{
	LookAndFeelParamWrapper p ();
	owner.getMenuWindowFlags(p);
}

void LookAndFeelBase::drawMenuBarBackground(Graphics &g, int width, int height, bool isMouseOverBar, MenuBarComponent &menuBarComponent)
{
	LookAndFeelParamWrapper p (g, width, height, isMouseOverBar, menuBarComponent);
	owner.drawMenuBarBackground(p);
}

int LookAndFeelBase::getMenuBarItemWidth(MenuBarComponent &menuBarComponent, int itemIndex, const String &itemText)
{
	LookAndFeelParamWrapper p (menuBarComponent, itemIndex, itemText);
	owner.getMenuBarItemWidth(p);
}

Font LookAndFeelBase::getMenuBarFont(MenuBarComponent &menuBarComponent, int itemIndex, const String &itemText)
{
	LookAndFeelParamWrapper p (menuBarComponent, itemIndex, itemText);
	owner.getMenuBarFont(p);
}

void LookAndFeelBase::drawMenuBarItem(Graphics &g, int width, int height, int itemIndex, const String &itemText, bool isMouseOverItem, bool isMenuOpen, bool isMouseOverBar, MenuBarComponent &menuBarComponent)
{
	LookAndFeelParamWrapper p (g, width, height, itemIndex, itemText, isMouseOverItem, isMenuOpen, isMouseOverBar, menuBarComponent);
	owner.drawMenuBarItem(p);
}

void LookAndFeelBase::drawComboBox(Graphics &g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox &comboBox)
{
	LookAndFeelParamWrapper p (g, width, height, isButtonDown, buttonX, buttonY, buttonW, buttonH, comboBox);
	owner.drawComboBox(p);
}

Font LookAndFeelBase::getComboBoxFont(ComboBox &comboBox)
{
	LookAndFeelParamWrapper p (comboBox);
	owner.getComboBoxFont(p);
}

Label* LookAndFeelBase::createComboBoxTextBox(ComboBox &comboBox)
{
	LookAndFeelParamWrapper p (comboBox);
	owner.createComboBoxTextBox(p);
}

void LookAndFeelBase::positionComboBoxText(ComboBox &comboBox, Label &label)
{
	LookAndFeelParamWrapper p (comboBox, label);
	owner.positionComboBoxText(p);
}

void LookAndFeelBase::drawLabel(Graphics &g, Label &label)
{
	LookAndFeelParamWrapper p (g, label);
	owner.drawLabel(p);
}

void LookAndFeelBase::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle sliderStyle, Slider &slider)
{
	LookAndFeelParamWrapper p (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, sliderStyle, slider);
	owner.drawLinearSlider(p);
}

void LookAndFeelBase::drawLinearSliderBackground(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle sliderStyle, Slider &slider)
{
	LookAndFeelParamWrapper p (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, sliderStyle, slider);
	owner.drawLinearSliderBackground(p);
}

void LookAndFeelBase::drawLinearSliderThumb(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle sliderStyle, Slider &slider)
{
	LookAndFeelParamWrapper p (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, sliderStyle, slider);
	owner.drawLinearSliderThumb(p);
}

int LookAndFeelBase::getSliderThumbRadius(Slider &slider)
{
	LookAndFeelParamWrapper p (slider);
	owner.getSliderThumbRadius(p);
}

void LookAndFeelBase::drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider)
{
	LookAndFeelParamWrapper p (g, x, y, width, height, sliderPosProportional, rotaryStartAngle, rotaryEndAngle, slider);
	owner.drawRotarySlider(p);
}

Button* LookAndFeelBase::createSliderButton(Slider &slider, bool isIncrement)
{
	LookAndFeelParamWrapper p (slider, isIncrement);
	owner.createSliderButton(p);
}

Label* LookAndFeelBase::createSliderTextBox(Slider &slider)
{
	LookAndFeelParamWrapper p (slider);
	owner.createSliderTextBox(p);
}

ImageEffectFilter* LookAndFeelBase::getSliderEffect(Slider &slider)
{
	LookAndFeelParamWrapper p (slider);
	owner.getSliderEffect(p);
}

void LookAndFeelBase::getTooltipSize(const String &tipText, int &width, int &height)
{
	LookAndFeelParamWrapper p (tipText, width, height);
	owner.getTooltipSize(p);
}

void LookAndFeelBase::drawTooltip(Graphics &g, const String &text, int width, int height)
{
	LookAndFeelParamWrapper p (g, text, width, height);
	owner.drawTooltip(p);
}

Button* LookAndFeelBase::createFilenameComponentBrowseButton(const String &text)
{
	LookAndFeelParamWrapper p (text);
	owner.createFilenameComponentBrowseButton(p);
}

void LookAndFeelBase::layoutFilenameComponent(FilenameComponent &filenameComponent, ComboBox* comboBox, Button* button)
{
	LookAndFeelParamWrapper p (filenameComponent, comboBox, button);
	owner.layoutFilenameComponent(p);
}

void LookAndFeelBase::drawConcertinaPanelHeader(Graphics &g, const Rectangle<int> &areaInt, bool isMouseOver, bool isMouseDown, ConcertinaPanel &concertinaPanel, Component &component)
{
	LookAndFeelParamWrapper p (g, areaInt, isMouseOver, isMouseDown, concertinaPanel, component);
	owner.drawConcertinaPanelHeader(p);
}

void LookAndFeelBase::drawCornerResizer(Graphics &g, int w, int h, bool isMouseOver, bool isMouseDragging)
{
	LookAndFeelParamWrapper p (g, w, h, isMouseOver, isMouseDragging);
	owner.drawCornerResizer(p);
}

void LookAndFeelBase::drawResizableFrame(Graphics &g, int w, int h, const BorderSize<int> &borderSize)
{
	LookAndFeelParamWrapper p (g, w, h, borderSize);
	owner.drawResizableFrame(p);
}

void LookAndFeelBase::fillResizableWindowBackground(Graphics &g, int w, int h, const BorderSize<int> &borderSize, ResizableWindow &resizableWindow)
{
	LookAndFeelParamWrapper p (g, w, h, borderSize, resizableWindow);
	owner.fillResizableWindowBackground(p);
}

void LookAndFeelBase::drawResizableWindowBorder(Graphics &g, int w, int h, const BorderSize<int> &borderSize, ResizableWindow &resizableWindow)
{
	LookAndFeelParamWrapper p (g, w, h, borderSize, resizableWindow);
	owner.drawResizableWindowBorder(p);
}

void LookAndFeelBase::drawDocumentWindowTitleBar(DocumentWindow &documentWindow, Graphics &g, int w, int h, int titleSpaceX, int titleSpaceW, const Image* icon, bool drawTitleTextOnLeft)
{
	LookAndFeelParamWrapper p (documentWindow, g, w, h, titleSpaceX, titleSpaceW, icon, drawTitleTextOnLeft);
	owner.drawDocumentWindowTitleBar(p);
}

Button* LookAndFeelBase::createDocumentWindowButton(int buttonType)
{
	LookAndFeelParamWrapper p (buttonType);
	owner.createDocumentWindowButton(p);
}

void LookAndFeelBase::positionDocumentWindowButtons(DocumentWindow &documentWindow, int titleBarX, int titleBarY, int titleBarW, int titleBarH, Button* minimiseButton, Button* maximiseButton, Button* closeButton, bool positionTitleBarButtonsOnLeft)
{
	LookAndFeelParamWrapper p (documentWindow, titleBarX, titleBarY, titleBarW, titleBarH, minimiseButton, maximiseButton, closeButton, positionTitleBarButtonsOnLeft);
	owner.positionDocumentWindowButtons(p);
}

int LookAndFeelBase::getDefaultMenuBarHeight(
{
	LookAndFeelParamWrapper p ();
	owner.getDefaultMenuBarHeight(p);
}

DropShadower* LookAndFeelBase::createDropShadowerForComponent(Component* component)
{
	LookAndFeelParamWrapper p (component);
	owner.createDropShadowerForComponent(p);
}

void LookAndFeelBase::drawGroupComponentOutline(Graphics &g, int w, int h, const String &text, const Justification &justification, GroupComponent &groupComponent)
{
	LookAndFeelParamWrapper p (g, w, h, text, justification, groupComponent);
	owner.drawGroupComponentOutline(p);
}

int LookAndFeelBase::getTabButtonSpaceAroundImage(
{
	LookAndFeelParamWrapper p ();
	owner.getTabButtonSpaceAroundImage(p);
}

int LookAndFeelBase::getTabButtonOverlap(int tabDepth)
{
	LookAndFeelParamWrapper p (tabDepth);
	owner.getTabButtonOverlap(p);
}

int LookAndFeelBase::getTabButtonBestWidth(TabBarButton &tabBarButton, int tabDepth)
{
	LookAndFeelParamWrapper p (tabBarButton, tabDepth);
	owner.getTabButtonBestWidth(p);
}

Rectangle<int> LookAndFeelBase::getTabButtonExtraComponentBounds(const TabBarButton &tabBarButton, Rectangle<int> &areaInt, Component &component)
{
	LookAndFeelParamWrapper p (tabBarButton, areaInt, component);
	owner.getTabButtonExtraComponentBounds(p);
}

void LookAndFeelBase::drawTabButton(TabBarButton &tabBarButton, Graphics &g, bool isMouseOver, bool isMouseDown)
{
	LookAndFeelParamWrapper p (tabBarButton, g, isMouseOver, isMouseDown);
	owner.drawTabButton(p);
}

void LookAndFeelBase::drawTabButtonText(TabBarButton &tabBarButton, Graphics &g, bool isMouseOver, bool isMouseDown)
{
	LookAndFeelParamWrapper p (tabBarButton, g, isMouseOver, isMouseDown);
	owner.drawTabButtonText(p);
}

void LookAndFeelBase::drawTabAreaBehindFrontButton(TabbedButtonBar &tabbedButtonBar, Graphics &g, int w, int h)
{
	LookAndFeelParamWrapper p (tabbedButtonBar, g, w, h);
	owner.drawTabAreaBehindFrontButton(p);
}

void LookAndFeelBase::createTabButtonShape(TabBarButton &tabBarButton, Path &p, bool isMouseOver, bool isMouseDown)
{
	LookAndFeelParamWrapper p (tabBarButton, p, isMouseOver, isMouseDown);
	owner.createTabButtonShape(p);
}

void LookAndFeelBase::fillTabButtonShape(TabBarButton &tabBarButton, Graphics &g, const Path &p, bool isMouseOver, bool isMouseDown)
{
	LookAndFeelParamWrapper p (tabBarButton, g, p, isMouseOver, isMouseDown);
	owner.fillTabButtonShape(p);
}

Button* LookAndFeelBase::createTabBarExtrasButton(
{
	LookAndFeelParamWrapper p ();
	owner.createTabBarExtrasButton(p);
}

void LookAndFeelBase::drawImageButton(Graphics &g, Image* image, int imageX, int imageY, int imageW, int imageH, const Colour &overlayColourRef, float imageOpacity, ImageButton &imageButton)
{
	LookAndFeelParamWrapper p (g, image, imageX, imageY, imageW, imageH, overlayColourRef, imageOpacity, imageButton);
	owner.drawImageButton(p);
}

void LookAndFeelBase::drawTableHeaderBackground(Graphics &g, TableHeaderComponent &tableHeaderComponent)
{
	LookAndFeelParamWrapper p (g, tableHeaderComponent);
	owner.drawTableHeaderBackground(p);
}

void LookAndFeelBase::drawTableHeaderColumn(Graphics &g, const String &columnName, int columnId, int width, int height, bool isMouseOver, bool isMouseDown, int columnFlags)
{
	LookAndFeelParamWrapper p (g, columnName, columnId, width, height, isMouseOver, isMouseDown, columnFlags);
	owner.drawTableHeaderColumn(p);
}

void LookAndFeelBase::paintToolbarBackground(Graphics &g, int width, int height, Toolbar &toolbar)
{
	LookAndFeelParamWrapper p (g, width, height, toolbar);
	owner.paintToolbarBackground(p);
}

Button* LookAndFeelBase::createToolbarMissingItemsButton(Toolbar &toolbar)
{
	LookAndFeelParamWrapper p (toolbar);
	owner.createToolbarMissingItemsButton(p);
}

void LookAndFeelBase::paintToolbarButtonBackground(Graphics &g, int width, int height, bool isMouseOver, bool isMouseDown, ToolbarItemComponent &toolbarItemComponent)
{
	LookAndFeelParamWrapper p (g, width, height, isMouseOver, isMouseDown, toolbarItemComponent);
	owner.paintToolbarButtonBackground(p);
}

void LookAndFeelBase::paintToolbarButtonLabel(Graphics &g, int x, int y, int width, int height, const String &text, ToolbarItemComponent &toolbarItemComponent)
{
	LookAndFeelParamWrapper p (g, x, y, width, height, text, toolbarItemComponent);
	owner.paintToolbarButtonLabel(p);
}

void LookAndFeelBase::drawStretchableLayoutResizerBar(Graphics &g, int w, int h, bool isVerticalBar, bool isMouseOver, bool isMouseDragging)
{
	LookAndFeelParamWrapper p (g, w, h, isVerticalBar, isMouseOver, isMouseDragging);
	owner.drawStretchableLayoutResizerBar(p);
}

void LookAndFeelBase::drawPropertyPanelSectionHeader(Graphics &g, const String &name, bool isOpen, int width, int height)
{
	LookAndFeelParamWrapper p (g, name, isOpen, width, height);
	owner.drawPropertyPanelSectionHeader(p);
}

void LookAndFeelBase::drawPropertyComponentBackground(Graphics &g, int width, int height, PropertyComponent &propertyComponent)
{
	LookAndFeelParamWrapper p (g, width, height, propertyComponent);
	owner.drawPropertyComponentBackground(p);
}

void LookAndFeelBase::drawPropertyComponentLabel(Graphics &g, int width, int height, PropertyComponent &propertyComponent)
{
	LookAndFeelParamWrapper p (g, width, height, propertyComponent);
	owner.drawPropertyComponentLabel(p);
}

Rectangle<int> LookAndFeelBase::getPropertyComponentContentPosition(PropertyComponent &propertyComponent)
{
	LookAndFeelParamWrapper p (propertyComponent);
	owner.getPropertyComponentContentPosition(p);
}

void LookAndFeelBase::drawCallOutBoxBackground(CallOutBox &callOutBox, Graphics &g, const Path &path, Image &image)
{
	LookAndFeelParamWrapper p (callOutBox, g, path, image);
	owner.drawCallOutBoxBackground(p);
}

void LookAndFeelBase::drawLevelMeter(Graphics &g, int width, int height, float level)
{
	LookAndFeelParamWrapper p (g, width, height, level);
	owner.drawLevelMeter(p);
}

void LookAndFeelBase::drawKeymapChangeButton(Graphics &g, int width, int height, Button &button, const String &keyDescription)
{
	LookAndFeelParamWrapper p (g, width, height, button, keyDescription);
	owner.drawKeymapChangeButton(p);
}

