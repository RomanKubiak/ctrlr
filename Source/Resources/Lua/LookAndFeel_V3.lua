class '__method_name' (LookAndFeel_V3)

function __method_name:__init()
	--
	-- This is needed for luabind, please don't remove this line
	-- Add as much code as you like here, just leave this
	--
	LookAndFeel_V3.__init(self)
end

function __method_name:findColour (--[[int]] colourId)
	--
	-- Body
	--
	return LookAndFeel_V3.findColour (self, colourId)
end

function __method_name:setColour (--[[int]] colourId, --[[Colour]] colour)
	--
	-- Body
	--
	LookAndFeel_V3.setColour (self, colourId, colour)
end

function __method_name:isColourSpecified (--[[int]] colourId)
	--
	-- Body
	--
	return LookAndFeel_V3.isColourSpecified (self, colourId)
end

function __method_name:getTypefaceForFont (--[[Font]] font)
	--
	-- Body
	--
	return LookAndFeel_V3.getTypefaceForFont (self, font)
end

function __method_name:getMouseCursorFor (--[[Component]] component)
	--
	-- Body
	--
	return LookAndFeel_V3.getMouseCursorFor (self, component)
end

function __method_name:drawButtonBackground (--[[Graphics]] g, --[[Button]] b, --[[Colour]] c, --[[bool]] over, --[[bool]] down)
	--
	-- Body
	--
	LookAndFeel_V3.drawButtonBackground (self, g, b, c, over, down)
end

function __method_name:drawButtonText (--[[Graphics]] g, --[[TextButton]] button, --[[bool]] isMouseOverButton, --[[bool]] isButtonDown)
	--
	-- Body
	--
	LookAndFeel_V3.drawButtonText (self, g, button, isMouseOverButton, isButtonDown)
end

function __method_name:drawToggleButton (--[[Graphics]] g, --[[ToggleButton]] button, --[[bool]] isMouseOverButton, --[[bool]] isButtonDown)
	--
	-- Body
	--
	LookAndFeel_V3.drawToggleButton (self, g, button, isMouseOverButton, isButtonDown)
end

function __method_name:changeToggleButtonWidthToFitText (--[[ToggleButton]] button)
	--
	-- Body
	--
	LookAndFeel_V3.changeToggleButtonWidthToFitText (self, button)
end

function __method_name:drawTickBox (--[[Graphics]] g, --[[Component]] component, --[[float]] x, --[[float]] y, --[[float]] w, --[[float]] h, --[[bool]] ticked, --[[bool]] isEnabled, --[[bool]] isMouseOverButton, --[[bool]] isButtonDown)
	--
	-- Body
	--
	LookAndFeel_V3.drawTickBox (self, g, component, x, y, w, h, ticked, isEnabled, isMouseOverButton, isButtonDown)
end

function __method_name:createAlertWindow (--[[String]] title, --[[String]] message, --[[String]] button1, --[[String]] button2, --[[String]] button3, --[[AlertWindow::AlertIconType]] iconType, --[[int]] numButtons, --[[Component*]] associatedComponent)
	--
	-- Body
	--
	return LookAndFeel_V3.createAlertWindow (self, title, message, button1, button2, button3, iconType, numButtons, associatedComponent)
end

function __method_name:drawAlertBox (--[[Graphics]] g, --[[AlertWindow]] window, --[[Rectangle]] textArea, --[[TextLayout]] layout)
	--
	-- Body
	--
	LookAndFeel_V3.drawAlertBox (self, g, window, textArea, layout)
end

function __method_name:getAlertBoxWindowFlags ()
	--
	-- Body
	--
	return LookAndFeel_V3.getAlertBoxWindowFlags (self)
end

function __method_name:getAlertWindowButtonHeight ()
	--
	-- Body
	--
	return LookAndFeel_V3.getAlertWindowButtonHeight (self)
end

function __method_name:getAlertWindowMessageFont ()
	--
	-- Body
	--
	return LookAndFeel_V3.getAlertWindowMessageFont (self)
end

function __method_name:getAlertWindowFont ()
	--
	-- Body
	--
	return LookAndFeel_V3.getAlertWindowFont (self)
end

function __method_name:drawProgressBar (--[[Graphics]] g, --[[ProgressBar]] bar, --[[int]] width, --[[int]] height, --[[double]] progress, --[[String]] textToShow)
	--
	-- Body
	--
	LookAndFeel_V3.drawProgressBar (self, g, bar, width, height, progress, textToShow)
end

function __method_name:drawSpinningWaitAnimation (--[[Graphics]] g, --[[Colour]] colour, --[[int]] x, --[[int]] y, --[[int]] w, --[[int]] h)
	--
	-- Body
	--
	LookAndFeel_V3.drawSpinningWaitAnimation (self, g, colour, x, y, w, h)
end

function __method_name:areScrollbarButtonsVisible ()
	--
	-- Body
	--
	return LookAndFeel_V3.areScrollbarButtonsVisible (self)
end

function __method_name:getScrollbarEffect ()
	--
	-- Body
	--
	return LookAndFeel_V3.getScrollbarEffect (self)
end

function __method_name:getMinimumScrollbarThumbSize (--[[ScrollBar]] bar)
	--
	-- Body
	--
	return LookAndFeel_V3.getMinimumScrollbarThumbSize (self, bar)
end

function __method_name:getDefaultScrollbarWidth ()
	--
	-- Body
	--
	return LookAndFeel_V3.getDefaultScrollbarWidth (self)
end

function __method_name:getScrollbarButtonSize (--[[ScrollBar]] bar)
	--
	-- Body
	--
	return LookAndFeel_V3.getScrollbarButtonSize (self, bar)
end

function __method_name:getTickShape (--[[float]] height)
	--
	-- Body
	--
	return LookAndFeel_V3.getTickShape (self, height)
end

function __method_name:getCrossShape (--[[float]] height)
	--
	-- Body
	--
	return LookAndFeel_V3.getCrossShape (self, height)
end

function __method_name:drawTreeviewPlusMinusBox (--[[Graphics]] g, --[[Rectangle]] area, --[[Colour]] backgroundColour, --[[bool]] isOpen, --[[bool]] isMouseOver)
	--
	-- Body
	--
	LookAndFeel_V3.drawTreeviewPlusMinusBox (self, g, area, backgroundColour, isOpen, isMouseOver)
end

function __method_name:fillTextEditorBackground (--[[Graphics]] g, --[[int]] width, --[[int]] height, --[[TextEditor]] editor)
	--
	-- Body
	--
	LookAndFeel_V3.fillTextEditorBackground (self, g, width, height, editor)
end

function __method_name:drawTextEditorOutline (--[[Graphics]] g, --[[int]] width, --[[int]] height, --[[TextEditor]] editor)
	--
	-- Body
	--
	LookAndFeel_V3.drawTextEditorOutline (self, g, width, height, editor)
end

function __method_name:createCaretComponent (--[[Component*]] keyFocusOwner)
	--
	-- Body
	--
	return LookAndFeel_V3.createCaretComponent (self, keyFocusOwner)
end

function __method_name:getDefaultFolderImage ()
	--
	-- Body
	--
	return LookAndFeel_V3.getDefaultFolderImage (self)
end

function __method_name:getDefaultDocumentFileImage ()
	--
	-- Body
	--
	return LookAndFeel_V3.getDefaultDocumentFileImage (self)
end

function __method_name:createFileChooserHeaderText (--[[String]] title, --[[String]] instructions)
	--
	-- Body
	--
	return LookAndFeel_V3.createFileChooserHeaderText (self, title, instructions)
end

function __method_name:drawFileBrowserRow (--[[Graphics]] g, --[[int]] width, --[[int]] height, --[[String]] filename, --[[Image*]] icon, --[[String]] fileSizeDescription, --[[String]] fileTimeDescription, --[[bool]] isDirectory, --[[bool]] isItemSelected, --[[int]] itemIndex, --[[DirectoryContentsDisplayComponent]] component)
	--
	-- Body
	--
	LookAndFeel_V3.drawFileBrowserRow (self, g, width, height, filename, icon, fileSizeDescription, fileTimeDescription, isDirectory, isItemSelected, itemIndex, component)
end

function __method_name:createFileBrowserGoUpButton ()
	--
	-- Body
	--
	return LookAndFeel_V3.createFileBrowserGoUpButton (self)
end

function __method_name:layoutFileBrowserComponent (--[[FileBrowserComponent]] component, --[[DirectoryContentsDisplayComponent*]] contentsComponent, --[[FilePreviewComponent*]] previewComponent, --[[ComboBox*]] currentPathBox, --[[TextEditor*]] filenameBox, --[[Button*]] goUpButton)
	--
	-- Body
	--
	LookAndFeel_V3.layoutFileBrowserComponent (self, component, contentsComponent, previewComponent, currentPathBox, filenameBox, goUpButton)
end

function __method_name:drawBubble (--[[Graphics]] g, --[[BubbleComponent]] bubble, --[[Point]] tip, --[[Rectangle]] body)
	--
	-- Body
	--
	LookAndFeel_V3.drawBubble (self, g, bubble, tip, body)
end

function __method_name:drawLasso (--[[Graphics]] g, --[[Component]] component)
	--
	-- Body
	--
	LookAndFeel_V3.drawLasso (self, g, component)
end

function __method_name:drawPopupMenuBackground (--[[Graphics]] g, --[[int]] width, --[[int]] height)
	--
	-- Body
	--
	LookAndFeel_V3.drawPopupMenuBackground (self, g, width, height)
end

function __method_name:drawPopupMenuItem (--[[Graphics]] g, --[[Rectangle]] area, --[[bool]] isSeparator, --[[bool]] isActive, --[[bool]] isHighlighted, --[[bool]] isTicked, --[[bool]] hasSubMenu, --[[String]] text, --[[String]] shortcutKeyText, --[[Drawable*]] icon, --[[Colour*]] textColour)
	--
	-- Body
	--
	LookAndFeel_V3.drawPopupMenuItem (self, g, area, isSeparator, isActive, isHighlighted, isTicked, hasSubMenu, text, shortcutKeyText, icon, textColour)
end

function __method_name:getPopupMenuFont ()
	--
	-- Body
	--
	return LookAndFeel_V3.getPopupMenuFont (self)
end

function __method_name:drawPopupMenuUpDownArrow (--[[Graphics]] g, --[[int]] width, --[[int]] height, --[[bool]] isScrollUpArrow)
	--
	-- Body
	--
	LookAndFeel_V3.drawPopupMenuUpDownArrow (self, g, width, height, isScrollUpArrow)
end

function __method_name:getIdealPopupMenuItemSize (--[[String]] text, --[[bool]] isSeparator, --[[int]] standardMenuItemHeight, --[[int]] idealWidth, --[[int]] idealHeight)
	--
	-- Body
	--
	LookAndFeel_V3.getIdealPopupMenuItemSize (self, text, isSeparator, standardMenuItemHeight, idealWidth, idealHeight)
end

function __method_name:getMenuWindowFlags ()
	--
	-- Body
	--
	return LookAndFeel_V3.getMenuWindowFlags (self)
end

function __method_name:drawMenuBarBackground (--[[Graphics]] g, --[[int]] width, --[[int]] height, --[[bool]] isMouseOverBar, --[[MenuBarComponent]] component)
	--
	-- Body
	--
	LookAndFeel_V3.drawMenuBarBackground (self, g, width, height, isMouseOverBar, component)
end

function __method_name:getMenuBarItemWidth (--[[MenuBarComponent]] component, --[[int]] itemIndex, --[[String]] itemText)
	--
	-- Body
	--
	return LookAndFeel_V3.getMenuBarItemWidth (self, component, itemIndex, itemText)
end

function __method_name:getMenuBarFont (--[[MenuBarComponent]] component, --[[int]] itemIndex, --[[String]] itemText)
	--
	-- Body
	--
	return LookAndFeel_V3.getMenuBarFont (self, component, itemIndex, itemText)
end

function __method_name:drawMenuBarItem (--[[Graphics]] g, --[[int]] width, --[[int]] height, --[[int]] itemIndex, --[[String]] itemText, --[[bool]] isMouseOverItem, --[[bool]] isMenuOpen, --[[bool]] isMouseOverBar, --[[MenuBarComponent]] component)
	--
	-- Body
	--
	LookAndFeel_V3.drawMenuBarItem (self, g, width, height, itemIndex, itemText, isMouseOverItem, isMenuOpen, isMouseOverBar, component)
end

function __method_name:drawComboBox (--[[Graphics]] g, --[[int]] width, --[[int]] height, --[[bool]] isButtonDown, --[[int]] buttonX, --[[int]] buttonY, --[[int]] buttonW, --[[int]] buttonH, --[[ComboBox]] component)
	--
	-- Body
	--
	LookAndFeel_V3.drawComboBox (self, g, width, height, isButtonDown, buttonX, buttonY, buttonW, buttonH, component)
end

function __method_name:getComboBoxFont (--[[ComboBox]] component)
	--
	-- Body
	--
	return LookAndFeel_V3.getComboBoxFont (self, component)
end

function __method_name:createComboBoxTextBox (--[[ComboBox]] component)
	--
	-- Body
	--
	return LookAndFeel_V3.createComboBoxTextBox (self, component)
end

function __method_name:positionComboBoxText (--[[ComboBox]] component, --[[Label]] label)
	--
	-- Body
	--
	LookAndFeel_V3.positionComboBoxText (self, component, label)
end

function __method_name:drawLabel (--[[Graphics]] g, --[[Label]] label)
	--
	-- Body
	--
	LookAndFeel_V3.drawLabel (self, g, label)
end

function __method_name:drawLinearSlider (--[[Graphics]] g, --[[int]] x, --[[int]] y, --[[int]] width, --[[int]] height, --[[float]] sliderPos, --[[float]] minSliderPos, --[[float]] maxSliderPos, --[[Slider::SliderStyle]] style, --[[Slider]] component)
	--
	-- Body
	--
	LookAndFeel_V3.drawLinearSlider (self, g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, component)
end

function __method_name:drawLinearSliderBackground (--[[Graphics]] g, --[[int]] x, --[[int]] y, --[[int]] width, --[[int]] height, --[[float]] sliderPos, --[[float]] minSliderPos, --[[float]] maxSliderPos, --[[Slider::SliderStyle]] style, --[[Slider]] component)
	--
	-- Body
	--
	LookAndFeel_V3.drawLinearSliderBackground (self, g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, component)
end

function __method_name:drawLinearSliderThumb (--[[Graphics]] g, --[[int]] x, --[[int]] y, --[[int]] width, --[[int]] height, --[[float]] sliderPos, --[[float]] minSliderPos, --[[float]] maxSliderPos, --[[Slider::SliderStyle]] style, --[[Slider]] component)
	--
	-- Body
	--
	LookAndFeel_V3.drawLinearSliderThumb (self, g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, component)
end

function __method_name:getSliderThumbRadius (--[[Slider]] component)
	--
	-- Body
	--
	return LookAndFeel_V3.getSliderThumbRadius (self, component)
end

function __method_name:drawRotarySlider (--[[Graphics]] g, --[[int]] x, --[[int]] y, --[[int]] width, --[[int]] height, --[[float]] sliderPosProportional, --[[float]] rotaryStartAngle, --[[float]] rotaryEndAngle, --[[Slider]] slider)
	--
	-- Body
	--
	LookAndFeel_V3.drawRotarySlider (self, g, x, y, width, height, sliderPosProportional, rotaryStartAngle, rotaryEndAngle, slider)
end

function __method_name:createSliderButton (--[[Slider]] component, --[[bool]] isIncrement)
	--
	-- Body
	--
	return LookAndFeel_V3.createSliderButton (self, component, isIncrement)
end

function __method_name:createSliderTextBox (--[[Slider]] component)
	--
	-- Body
	--
	return LookAndFeel_V3.createSliderTextBox (self, component)
end

function __method_name:getSliderEffect (--[[Slider]] component)
	--
	-- Body
	--
	return LookAndFeel_V3.getSliderEffect (self, component)
end

function __method_name:getTooltipSize (--[[String]] tipText, --[[int]] width, --[[int]] height)
	--
	-- Body
	--
	LookAndFeel_V3.getTooltipSize (self, tipText, width, height)
end

function __method_name:drawTooltip (--[[Graphics]] g, --[[String]] text, --[[int]] width, --[[int]] height)
	--
	-- Body
	--
	LookAndFeel_V3.drawTooltip (self, g, text, width, height)
end

function __method_name:createFilenameComponentBrowseButton (--[[String]] text)
	--
	-- Body
	--
	return LookAndFeel_V3.createFilenameComponentBrowseButton (self, text)
end

function __method_name:layoutFilenameComponent (--[[FilenameComponent]] component, --[[ComboBox*]] filenameBox, --[[Button*]] browseButton)
	--
	-- Body
	--
	LookAndFeel_V3.layoutFilenameComponent (self, component, filenameBox, browseButton)
end

function __method_name:drawConcertinaPanelHeader (--[[Graphics]] g, --[[Rectangle]] area, --[[bool]] isMouseOver, --[[bool]] isMouseDown, --[[ConcertinaPanel]] component, --[[Component]] panel)
	--
	-- Body
	--
	LookAndFeel_V3.drawConcertinaPanelHeader (self, g, area, isMouseOver, isMouseDown, component, panel)
end

function __method_name:drawCornerResizer (--[[Graphics]] g, --[[int]] w, --[[int]] h, --[[bool]] isMouseOver, --[[bool]] isMouseDragging)
	--
	-- Body
	--
	LookAndFeel_V3.drawCornerResizer (self, g, w, h, isMouseOver, isMouseDragging)
end

function __method_name:drawResizableFrame (--[[Graphics]] g, --[[int]] w, --[[int]] h, --[[BorderSize]] borderSize)
	--
	-- Body
	--
	LookAndFeel_V3.drawResizableFrame (self, g, w, h, borderSize)
end

function __method_name:fillResizableWindowBackground (--[[Graphics]] g, --[[int]] w, --[[int]] h, --[[BorderSize]] borderSize, --[[ResizableWindow]] window)
	--
	-- Body
	--
	LookAndFeel_V3.fillResizableWindowBackground (self, g, w, h, borderSize, window)
end

function __method_name:drawResizableWindowBorder (--[[Graphics]] g, --[[int]] w, --[[int]] h, --[[BorderSize]] borderSize, --[[ResizableWindow]] window)
	--
	-- Body
	--
	LookAndFeel_V3.drawResizableWindowBorder (self, g, w, h, borderSize, window)
end

function __method_name:drawDocumentWindowTitleBar (--[[DocumentWindow]] window, --[[Graphics]] g, --[[int]] w, --[[int]] h, --[[int]] titleSpaceX, --[[int]] titleSpaceW, --[[Image*]] icon, --[[bool]] drawTitleTextOnLeft)
	--
	-- Body
	--
	LookAndFeel_V3.drawDocumentWindowTitleBar (self, window, g, w, h, titleSpaceX, titleSpaceW, icon, drawTitleTextOnLeft)
end

function __method_name:createDocumentWindowButton (--[[int]] buttonType)
	--
	-- Body
	--
	return LookAndFeel_V3.createDocumentWindowButton (self, buttonType)
end

function __method_name:positionDocumentWindowButtons (--[[DocumentWindow]] window, --[[int]] titleBarX, --[[int]] titleBarY, --[[int]] titleBarW, --[[int]] titleBarH, --[[Button*]] minimiseButton, --[[Button*]] maximiseButton, --[[Button*]] closeButton, --[[bool]] positionTitleBarButtonsOnLeft)
	--
	-- Body
	--
	LookAndFeel_V3.positionDocumentWindowButtons (self, window, titleBarX, titleBarY, titleBarW, titleBarH, minimiseButton, maximiseButton, closeButton, positionTitleBarButtonsOnLeft)
end

function __method_name:getDefaultMenuBarHeight ()
	--
	-- Body
	--
	return LookAndFeel_V3.getDefaultMenuBarHeight (self)
end

function __method_name:createDropShadowerForComponent (--[[Component*]] component)
	--
	-- Body
	--
	return LookAndFeel_V3.createDropShadowerForComponent (self, component)
end

function __method_name:drawGroupComponentOutline (--[[Graphics]] g, --[[int]] w, --[[int]] h, --[[String]] text, --[[Justification]] justification, --[[GroupComponent]] component)
	--
	-- Body
	--
	LookAndFeel_V3.drawGroupComponentOutline (self, g, w, h, text, justification, component)
end

function __method_name:getTabButtonSpaceAroundImage ()
	--
	-- Body
	--
	return LookAndFeel_V3.getTabButtonSpaceAroundImage (self)
end

function __method_name:getTabButtonOverlap (--[[int]] tabDepth)
	--
	-- Body
	--
	return LookAndFeel_V3.getTabButtonOverlap (self, tabDepth)
end

function __method_name:getTabButtonBestWidth (--[[TabBarButton]] component, --[[int]] tabDepth)
	--
	-- Body
	--
	return LookAndFeel_V3.getTabButtonBestWidth (self, component, tabDepth)
end

function __method_name:getTabButtonExtraComponentBounds (--[[TabBarButton]] component, --[[Rectangle]] textArea, --[[Component]] extraComp)
	--
	-- Body
	--
	return LookAndFeel_V3.getTabButtonExtraComponentBounds (self, component, textArea, extraComp)
end

function __method_name:drawTabButton (--[[TabBarButton]] component, --[[Graphics]] g, --[[bool]] isMouseOver, --[[bool]] isMouseDown)
	--
	-- Body
	--
	LookAndFeel_V3.drawTabButton (self, component, g, isMouseOver, isMouseDown)
end

function __method_name:drawTabButtonText (--[[TabBarButton]] component, --[[Graphics]] g, --[[bool]] isMouseOver, --[[bool]] isMouseDown)
	--
	-- Body
	--
	LookAndFeel_V3.drawTabButtonText (self, component, g, isMouseOver, isMouseDown)
end

function __method_name:drawTabAreaBehindFrontButton (--[[TabbedButtonBar]] component, --[[Graphics]] g, --[[int]] w, --[[int]] h)
	--
	-- Body
	--
	LookAndFeel_V3.drawTabAreaBehindFrontButton (self, component, g, w, h)
end

function __method_name:createTabButtonShape (--[[TabBarButton]] component, --[[Path]] p, --[[bool]] isMouseOver, --[[bool]] isMouseDown)
	--
	-- Body
	--
	LookAndFeel_V3.createTabButtonShape (self, component, p, isMouseOver, isMouseDown)
end

function __method_name:fillTabButtonShape (--[[TabBarButton]] component, --[[Graphics]] g, --[[Path]] p, --[[bool]] isMouseOver, --[[bool]] isMouseDown)
	--
	-- Body
	--
	LookAndFeel_V3.fillTabButtonShape (self, component, g, p, isMouseOver, isMouseDown)
end

function __method_name:createTabBarExtrasButton ()
	--
	-- Body
	--
	return LookAndFeel_V3.createTabBarExtrasButton (self)
end

function __method_name:drawImageButton (--[[Graphics]] g, --[[Image*]] image, --[[int]] imageX, --[[int]] imageY, --[[int]] imageW, --[[int]] imageH, --[[Colour]] overlayColour, --[[float]] imageOpacity, --[[ImageButton]] component)
	--
	-- Body
	--
	LookAndFeel_V3.drawImageButton (self, g, image, imageX, imageY, imageW, imageH, overlayColour, imageOpacity, component)
end

function __method_name:drawTableHeaderBackground (--[[Graphics]] g, --[[TableHeaderComponent]] component)
	--
	-- Body
	--
	LookAndFeel_V3.drawTableHeaderBackground (self, g, component)
end

function __method_name:drawTableHeaderColumn (--[[Graphics]] g, --[[String]] columnName, --[[int]] columnId, --[[int]] width, --[[int]] height, --[[bool]] isMouseOver, --[[bool]] isMouseDown, --[[int]] columnFlags)
	--
	-- Body
	--
	LookAndFeel_V3.drawTableHeaderColumn (self, g, columnName, columnId, width, height, isMouseOver, isMouseDown, columnFlags)
end

function __method_name:paintToolbarBackground (--[[Graphics]] g, --[[int]] width, --[[int]] height, --[[Toolbar]] component)
	--
	-- Body
	--
	LookAndFeel_V3.paintToolbarBackground (self, g, width, height, component)
end

function __method_name:createToolbarMissingItemsButton (--[[Toolbar]] component)
	--
	-- Body
	--
	return LookAndFeel_V3.createToolbarMissingItemsButton (self, component)
end

function __method_name:paintToolbarButtonBackground (--[[Graphics]] g, --[[int]] width, --[[int]] height, --[[bool]] isMouseOver, --[[bool]] isMouseDown, --[[ToolbarItemComponent]] component)
	--
	-- Body
	--
	LookAndFeel_V3.paintToolbarButtonBackground (self, g, width, height, isMouseOver, isMouseDown, component)
end

function __method_name:paintToolbarButtonLabel (--[[Graphics]] g, --[[int]] x, --[[int]] y, --[[int]] width, --[[int]] height, --[[String]] text, --[[ToolbarItemComponent]] component)
	--
	-- Body
	--
	LookAndFeel_V3.paintToolbarButtonLabel (self, g, x, y, width, height, text, component)
end

function __method_name:drawStretchableLayoutResizerBar (--[[Graphics]] g, --[[int]] w, --[[int]] h, --[[bool]] isVerticalBar, --[[bool]] isMouseOver, --[[bool]] isMouseDragging)
	--
	-- Body
	--
	LookAndFeel_V3.drawStretchableLayoutResizerBar (self, g, w, h, isVerticalBar, isMouseOver, isMouseDragging)
end

function __method_name:drawPropertyPanelSectionHeader (--[[Graphics]] g, --[[String]] name, --[[bool]] isOpen, --[[int]] width, --[[int]] height)
	--
	-- Body
	--
	LookAndFeel_V3.drawPropertyPanelSectionHeader (self, g, name, isOpen, width, height)
end

function __method_name:drawPropertyComponentBackground (--[[Graphics]] g, --[[int]] width, --[[int]] height, --[[PropertyComponent]] component)
	--
	-- Body
	--
	LookAndFeel_V3.drawPropertyComponentBackground (self, g, width, height, component)
end

function __method_name:drawPropertyComponentLabel (--[[Graphics]] g, --[[int]] width, --[[int]] height, --[[PropertyComponent]] component)
	--
	-- Body
	--
	LookAndFeel_V3.drawPropertyComponentLabel (self, g, width, height, component)
end

function __method_name:getPropertyComponentContentPosition (--[[PropertyComponent]] component)
	--
	-- Body
	--
	return LookAndFeel_V3.getPropertyComponentContentPosition (self, component)
end

function __method_name:drawCallOutBoxBackground (--[[CallOutBox]] component, --[[Graphics]] g, --[[Path]] path, --[[Image]] cachedImage)
	--
	-- Body
	--
	LookAndFeel_V3.drawCallOutBoxBackground (self, component, g, path, cachedImage)
end

function __method_name:drawLevelMeter (--[[Graphics]] g, --[[int]] width, --[[int]] height, --[[float]] level)
	--
	-- Body
	--
	LookAndFeel_V3.drawLevelMeter (self, g, width, height, level)
end

function __method_name:drawKeymapChangeButton (--[[Graphics]] g, --[[int]] width, --[[int]] height, --[[Button]] component, --[[String]] keyDescription)
	--
	-- Body
	--
	LookAndFeel_V3.drawKeymapChangeButton (self, g, width, height, component, keyDescription)
end

function __method_name:playAlertSound ()
	--
	-- Body
	--
	LookAndFeel_V3.playAlertSound (self)
end

