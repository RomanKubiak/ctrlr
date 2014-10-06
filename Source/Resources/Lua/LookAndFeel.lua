class '__method_name' (LookAndFeel)

function __method_name:__init()
	--
	-- This is needed for luabind, please don't remove this line
	-- Add as much code as you like here, just leave this
	--
	LookAndFeel.__init(self)
end

function __method_name:findColour (--[[ int p.colourId --]] p)
	--
	-- Body
	--

	-- return Colour
end

function __method_name:setColour (--[[ int p.colourId, Colour p.colour --]] p)
	--
	-- Body
	--
end

function __method_name:isColourSpecified (--[[ int p.colourId --]] p)
	--
	-- Body
	--

	-- return bool
end

function __method_name:getTypefaceForFont (--[[ Font p.font --]] p)
	--
	-- Body
	--

	-- return Typeface::Ptr
end

function __method_name:getMouseCursorFor (--[[ Component p.component --]] p)
	--
	-- Body
	--

	-- return MouseCursor
end

function __method_name:drawButtonBackground (--[[ Graphics p.g, Button p.button, Colour p.backgroundColour, bool p.isMouseOverButton, bool p.isButtonDown --]] p)
	--
	-- Body
	--
end

function __method_name:drawButtonText (--[[ Graphics p.g, TextButton p.textButton, bool p.isMouseOverButton, bool p.isButtonDown --]] p)
	--
	-- Body
	--
end

function __method_name:drawToggleButton (--[[ Graphics p.g, ToggleButton p.toggleButton, bool p.isMouseOverButton, bool p.isButtonDown --]] p)
	--
	-- Body
	--
end

function __method_name:changeToggleButtonWidthToFitText (--[[ ToggleButton p.toggleButton --]] p)
	--
	-- Body
	--
end

function __method_name:drawTickBox (--[[ Graphics p.g, Component p.component, float p.x, float p.y, float p.w, float p.h, bool p.ticked, bool p.isEnabled, bool p.isMouseOverButton, bool p.isButtonDown --]] p)
	--
	-- Body
	--
end

function __method_name:createAlertWindow (--[[ String p.title, String p.message, String p.button1, String p.button2, String p.button3, AlertWindow::AlertIconType p.iconType, int p.numButtons, Component* p.component --]] p)
	--
	-- Body
	--

	-- return AlertWindow*
end

function __method_name:drawAlertBox (--[[ Graphics p.g, AlertWindow p.window, Rectangle p.textArea, TextLayout p.layout --]] p)
	--
	-- Body
	--
end

function __method_name:getAlertBoxWindowFlags (--[[  --]] p)
	--
	-- Body
	--

	-- return int
end

function __method_name:getAlertWindowButtonHeight (--[[  --]] p)
	--
	-- Body
	--

	-- return int
end

function __method_name:getAlertWindowMessageFont (--[[  --]] p)
	--
	-- Body
	--

	-- return Font
end

function __method_name:getAlertWindowFont (--[[  --]] p)
	--
	-- Body
	--

	-- return Font
end

function __method_name:drawProgressBar (--[[ Graphics p.g, ProgressBar p.progressBar, int p.width, int p.height, double p.progress, String p.textToShow --]] p)
	--
	-- Body
	--
end

function __method_name:drawSpinningWaitAnimation (--[[ Graphics p.g, Colour p.colour, int p.x, int p.y, int p.w, int p.h --]] p)
	--
	-- Body
	--
end

function __method_name:areScrollbarButtonsVisible (--[[  --]] p)
	--
	-- Body
	--

	-- return bool
end

function __method_name:getScrollbarEffect (--[[  --]] p)
	--
	-- Body
	--

	-- return ImageEffectFilter*
end

function __method_name:getMinimumScrollbarThumbSize (--[[ ScrollBar p.scrollBar --]] p)
	--
	-- Body
	--

	-- return int
end

function __method_name:getDefaultScrollbarWidth (--[[  --]] p)
	--
	-- Body
	--

	-- return int
end

function __method_name:getScrollbarButtonSize (--[[ ScrollBar p.scrollBar --]] p)
	--
	-- Body
	--

	-- return int
end

function __method_name:getTickShape (--[[ float p.height --]] p)
	--
	-- Body
	--

	-- return Path
end

function __method_name:getCrossShape (--[[ float p.height --]] p)
	--
	-- Body
	--

	-- return Path
end

function __method_name:drawTreeviewPlusMinusBox (--[[ Graphics p.g, Rectangle p.area, Colour p.backgroundColour, bool p.isOpen, bool p.isMouseOver --]] p)
	--
	-- Body
	--
end

function __method_name:fillTextEditorBackground (--[[ Graphics p.g, int p.width, int p.height, TextEditor p.editor --]] p)
	--
	-- Body
	--
end

function __method_name:drawTextEditorOutline (--[[ Graphics p.g, int p.width, int p.height, TextEditor p.editor --]] p)
	--
	-- Body
	--
end

function __method_name:createCaretComponent (--[[ Component* p.component --]] p)
	--
	-- Body
	--

	-- return CaretComponent*
end

function __method_name:getDefaultFolderImage (--[[  --]] p)
	--
	-- Body
	--

	-- return Drawable*
end

function __method_name:getDefaultDocumentFileImage (--[[  --]] p)
	--
	-- Body
	--

	-- return Drawable*
end

function __method_name:createFileChooserHeaderText (--[[ String p.title, String p.instructions --]] p)
	--
	-- Body
	--

	-- return AttributedString
end

function __method_name:drawFileBrowserRow (--[[ Graphics p.g, int p.width, int p.height, String p.filename, Image* p.icon, String p.fileSizeDescription, String p.fileTimeDescription, bool p.isDirectory, bool p.isItemSelected, int p.itemIndex, DirectoryContentsDisplayComponent p.directoryContentsDisplayComponent --]] p)
	--
	-- Body
	--
end

function __method_name:createFileBrowserGoUpButton (--[[  --]] p)
	--
	-- Body
	--

	-- return Button*
end

function __method_name:layoutFileBrowserComponent (--[[ FileBrowserComponent p.fileBrowserComponent, DirectoryContentsDisplayComponent p.*directoryContentsDisplayComponent, FilePreviewComponent p.*filePreviewComponent, ComboBox p.*comboBox, TextEditor p.*textEditor, Button p.*goUpButton --]] p)
	--
	-- Body
	--
end

function __method_name:drawBubble (--[[ Graphics p.g, BubbleComponent p.bubbleComponent, Point p.tip, Rectangle p.body --]] p)
	--
	-- Body
	--
end

function __method_name:drawLasso (--[[ Graphics p.g, Component p.component --]] p)
	--
	-- Body
	--
end

function __method_name:drawPopupMenuBackground (--[[ Graphics p.g, int p.width, int p.height --]] p)
	--
	-- Body
	--
end

function __method_name:drawPopupMenuItem (--[[ Graphics p.g, Rectangle p.areaInt, bool p.isSeparator, bool p.isActive, bool p.isHighlighted, bool p.isTicked, bool p.hasSubMenu, String p.text, String p.shortcutKeyText, Drawable* p.drawableIcon, Colour* p.textColour --]] p)
	--
	-- Body
	--
end

function __method_name:getPopupMenuFont (--[[  --]] p)
	--
	-- Body
	--

	-- return Font
end

function __method_name:drawPopupMenuUpDownArrow (--[[ Graphics p.g, int p.width, int p.height, bool p.isScrollUpArrow --]] p)
	--
	-- Body
	--
end

function __method_name:getIdealPopupMenuItemSize (--[[ String p.text, bool p.isSeparator, int p.standardMenuItemHeight, int p.idealWidth, int p.idealHeight --]] p)
	--
	-- Body
	--
end

function __method_name:getMenuWindowFlags (--[[  --]] p)
	--
	-- Body
	--

	-- return int
end

function __method_name:drawMenuBarBackground (--[[ Graphics p.g, int p.width, int p.height, bool p.isMouseOverBar, MenuBarComponent p.menuBarComponent --]] p)
	--
	-- Body
	--
end

function __method_name:getMenuBarItemWidth (--[[ MenuBarComponent p.menuBarComponent, int p.itemIndex, String p.itemText --]] p)
	--
	-- Body
	--

	-- return int
end

function __method_name:getMenuBarFont (--[[ MenuBarComponent p.menuBarComponent, int p.itemIndex, String p.itemText --]] p)
	--
	-- Body
	--

	-- return Font
end

function __method_name:drawMenuBarItem (--[[ Graphics p.g, int p.width, int p.height, int p.itemIndex, String p.itemText, bool p.isMouseOverItem, bool p.isMenuOpen, bool p.isMouseOverBar, MenuBarComponent p.menuBarComponent --]] p)
	--
	-- Body
	--
end

function __method_name:drawComboBox (--[[ Graphics p.g, int p.width, int p.height, bool p.isButtonDown, int p.buttonX, int p.buttonY, int p.buttonW, int p.buttonH, ComboBox p.comobBox --]] p)
	--
	-- Body
	--
end

function __method_name:getComboBoxFont (--[[ ComboBox p.comobBox --]] p)
	--
	-- Body
	--

	-- return Font
end

function __method_name:createComboBoxTextBox (--[[ ComboBox p.comobBox --]] p)
	--
	-- Body
	--

	-- return Label*
end

function __method_name:positionComboBoxText (--[[ ComboBox p.comboBox, Label p.label --]] p)
	--
	-- Body
	--
end

function __method_name:drawLabel (--[[ Graphics p.g, Label p.label --]] p)
	--
	-- Body
	--
end

function __method_name:drawLinearSlider (--[[ Graphics p.g, int p.x, int p.y, int p.width, int p.height, float p.sliderPos, float p.minSliderPos, float p.maxSliderPos, Slider::SliderStyle p.sliderStyle, Slider p.slider --]] p)
	--
	-- Body
	--
end

function __method_name:drawLinearSliderBackground (--[[ Graphics p.g, int p.x, int p.y, int p.width, int p.height, float p.sliderPos, float p.minSliderPos, float p.maxSliderPos, Slider::SliderStyle p.sliderStyle, Slider p.slider --]] p)
	--
	-- Body
	--
end

function __method_name:drawLinearSliderThumb (--[[ Graphics p.g, int p.x, int p.y, int p.width, int p.height, float p.sliderPos, float p.minSliderPos, float p.maxSliderPos, Slider::SliderStyle p.sliderStyle, Slider p.slider --]] p)
	--
	-- Body
	--
end

function __method_name:getSliderThumbRadius (--[[ Slider p.slider --]] p)
	--
	-- Body
	--

	-- return int
end

function __method_name:drawRotarySlider (--[[ Graphics p.g, int p.x, int p.y, int p.width, int p.height, float p.sliderPosProportional, float p.rotaryStartAngle, float p.rotaryEndAngle, Slider p.slider --]] p)
	--
	-- Body
	--
end

function __method_name:createSliderButton (--[[ Slider p.slider, bool p.isIncrement --]] p)
	--
	-- Body
	--

	-- return Button*
end

function __method_name:createSliderTextBox (--[[ Slider p.slider --]] p)
	--
	-- Body
	--

	-- return Label*
end

function __method_name:getSliderEffect (--[[ Slider p.slider --]] p)
	--
	-- Body
	--

	-- return ImageEffectFilter*
end

function __method_name:getTooltipSize (--[[ String p.tipText, int p.width, int p.height --]] p)
	--
	-- Body
	--
end

function __method_name:drawTooltip (--[[ Graphics p.g, String p.text, int p.width, int p.height --]] p)
	--
	-- Body
	--
end

function __method_name:createFilenameComponentBrowseButton (--[[ String p.text --]] p)
	--
	-- Body
	--

	-- return Button*
end

function __method_name:layoutFilenameComponent (--[[ FilenameComponent p.filenameComponent, ComboBox* p.comboBox, Button* p.button --]] p)
	--
	-- Body
	--
end

function __method_name:drawConcertinaPanelHeader (--[[ Graphics p.g, Rectangle p.area, bool p.isMouseOver, bool p.isMouseDown, ConcertinaPanel p.concertinaPanel, Component p.component --]] p)
	--
	-- Body
	--
end

function __method_name:drawCornerResizer (--[[ Graphics p.g, int p.w, int p.h, bool p.isMouseOver, bool p.isMouseDragging --]] p)
	--
	-- Body
	--
end

function __method_name:drawResizableFrame (--[[ Graphics p.g, int p.w, int p.h, BorderSize p.borderSize --]] p)
	--
	-- Body
	--
end

function __method_name:fillResizableWindowBackground (--[[ Graphics p.g, int p.w, int p.h, BorderSize p.borderSize, ResizableWindow p.resizableWindow --]] p)
	--
	-- Body
	--
end

function __method_name:drawResizableWindowBorder (--[[ Graphics p.g, int p.w, int p.h, BorderSize p.borderSize, ResizableWindow p.resizableWindow --]] p)
	--
	-- Body
	--
end

function __method_name:drawDocumentWindowTitleBar (--[[ DocumentWindow p.documentWindow, Graphics p.g, int p.w, int p.h, int p.titleSpaceX, int p.titleSpaceW, Image* p.icon, bool p.drawTitleTextOnLeft --]] p)
	--
	-- Body
	--
end

function __method_name:createDocumentWindowButton (--[[ int p.buttonType --]] p)
	--
	-- Body
	--

	-- return Button*
end

function __method_name:positionDocumentWindowButtons (--[[ DocumentWindow p.documentWindow, int p.titleBarX, int p.titleBarY, int p.titleBarW, int p.titleBarH, Button* p.minimiseButton, Button* p.maximiseButton, Button* p.closeButton, bool p.positionTitleBarButtonsOnLeft --]] p)
	--
	-- Body
	--
end

function __method_name:getDefaultMenuBarHeight (--[[  --]] p)
	--
	-- Body
	--

	-- return int
end

function __method_name:createDropShadowerForComponent (--[[ Component* p.component --]] p)
	--
	-- Body
	--

	-- return DropShadower*
end

function __method_name:drawGroupComponentOutline (--[[ Graphics p.g, int p.w, int p.h, String p.text, Justification p.justification, GroupComponent p.groupComponent --]] p)
	--
	-- Body
	--
end

function __method_name:getTabButtonSpaceAroundImage (--[[  --]] p)
	--
	-- Body
	--

	-- return int
end

function __method_name:getTabButtonOverlap (--[[ int p.tabDepth --]] p)
	--
	-- Body
	--

	-- return int
end

function __method_name:getTabButtonBestWidth (--[[ TabBarButton p.tabBarButton, int p.tabDepth --]] p)
	--
	-- Body
	--

	-- return int
end

function __method_name:getTabButtonExtraComponentBounds (--[[ TabBarButton p.tabBarButton, Rectangle p.areaInt, Component p.component --]] p)
	--
	-- Body
	--

	-- return Rectangle<int>
end

function __method_name:drawTabButton (--[[ TabBarButton p.tabBarButton, Graphics p.g, bool p.isMouseOver, bool p.isMouseDown --]] p)
	--
	-- Body
	--
end

function __method_name:drawTabButtonText (--[[ TabBarButton p.tabBarButton, Graphics p.g, bool p.isMouseOver, bool p.isMouseDown --]] p)
	--
	-- Body
	--
end

function __method_name:drawTabAreaBehindFrontButton (--[[ TabbedButtonBar p.tabbedButtonBar, Graphics p.g, int p.w, int p.h --]] p)
	--
	-- Body
	--
end

function __method_name:createTabButtonShape (--[[ TabBarButton p.tabBarButton, Path p.p, bool p.isMouseOver, bool p.isMouseDown --]] p)
	--
	-- Body
	--
end

function __method_name:fillTabButtonShape (--[[ TabBarButton p.tabBarButton, Graphics p.g, Path p.p, bool p.isMouseOver, bool p.isMouseDown --]] p)
	--
	-- Body
	--
end

function __method_name:createTabBarExtrasButton (--[[  --]] p)
	--
	-- Body
	--

	-- return Button*
end

function __method_name:drawImageButton (--[[ Graphics p.g, Image* p.image, int p.imageX, int p.imageY, int p.imageW, int p.imageH, Colour p.overlayColour, float p.imageOpacity, ImageButton p.imageButton --]] p)
	--
	-- Body
	--
end

function __method_name:drawTableHeaderBackground (--[[ Graphics p.g, TableHeaderComponent p.component --]] p)
	--
	-- Body
	--
end

function __method_name:drawTableHeaderColumn (--[[ Graphics p.g, String p.columnName, int p.columnId, int p.width, int p.height, bool p.isMouseOver, bool p.isMouseDown, int p.columnFlags --]] p)
	--
	-- Body
	--
end

function __method_name:paintToolbarBackground (--[[ Graphics p.g, int p.width, int p.height, Toolbar p.toolbar --]] p)
	--
	-- Body
	--
end

function __method_name:createToolbarMissingItemsButton (--[[ Toolbar p.toolbar --]] p)
	--
	-- Body
	--

	-- return Button*
end

function __method_name:paintToolbarButtonBackground (--[[ Graphics p.g, int p.width, int p.height, bool p.isMouseOver, bool p.isMouseDown, ToolbarItemComponent p.toolbarItemComponent --]] p)
	--
	-- Body
	--
end

function __method_name:paintToolbarButtonLabel (--[[ Graphics p.g, int p.x, int p.y, int p.width, int p.height, String p.text, ToolbarItemComponent p.toolbarItemComponent --]] p)
	--
	-- Body
	--
end

function __method_name:drawStretchableLayoutResizerBar (--[[ Graphics p.g, int p.w, int p.h, bool p.isVerticalBar, bool p.isMouseOver, bool p.isMouseDragging --]] p)
	--
	-- Body
	--
end

function __method_name:drawPropertyPanelSectionHeader (--[[ Graphics p.g, String p.name, bool p.isOpen, int p.width, int p.height --]] p)
	--
	-- Body
	--
end

function __method_name:drawPropertyComponentBackground (--[[ Graphics p.g, int p.width, int p.height, PropertyComponent p.propertyComponent --]] p)
	--
	-- Body
	--
end

function __method_name:drawPropertyComponentLabel (--[[ Graphics p.g, int p.width, int p.height, PropertyComponent p.propertyComponent --]] p)
	--
	-- Body
	--
end

function __method_name:getPropertyComponentContentPosition (--[[ PropertyComponent p.propertyComponent --]] p)
	--
	-- Body
	--

	-- return Rectangle<int>
end

function __method_name:drawCallOutBoxBackground (--[[ CallOutBox p.callOutBox, Graphics p.g, Path p.path, Image p.image --]] p)
	--
	-- Body
	--
end

function __method_name:drawLevelMeter (--[[ Graphics p.g, int p.width, int p.height, float p.level --]] p)
	--
	-- Body
	--
end

function __method_name:drawKeymapChangeButton (--[[ Graphics p.g, int p.width, int p.height, Button p.button, String p.keyDescription --]] p)
	--
	-- Body
	--
end

