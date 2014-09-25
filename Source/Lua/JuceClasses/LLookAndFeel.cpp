#include "stdafx.h"
#include "LLookAndFeel.h"

void setLookAndFeel (Component *component, luabind::object lookAndFeelObject)
{
	_DBG("setLookAndFeel");

	if (component != nullptr && luabind::type (lookAndFeelObject) != LUA_TNIL)
	{
		_DBG("\tcomponent and lua lf are valid");

		LookBase *lookAndFeel = luabind::object_cast<LookBase*>(lookAndFeelObject);

		if (lookAndFeel)
		{
			_DBG("\tLookBase is valid");
			component->setLookAndFeel (lookAndFeel);
		}
	}
}

void LLookAndFeel::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
	[
		def("setLookAndFeel", &setLookAndFeel)
		,
		class_<ParamWrapper>("ParamWrapper")
			.def_readwrite ("g", &ParamWrapper::g)
			.def_readonly ("x", &ParamWrapper::x)
			.def_readonly ("y", &ParamWrapper::y)
			.def_readonly ("width", &ParamWrapper::width)
			.def_readonly ("height", &ParamWrapper::height)
			.def_readwrite ("int_ptr_p0", &ParamWrapper::int_ptr_p0)
			.def_readwrite ("int_ptr_p1", &ParamWrapper::int_ptr_p1)
		,
		class_<LookBase, LLookAndFeel>("LookAndFeel")
			.def(constructor<>())
			.def("drawRotarySlider", (void (LLookAndFeel::*)(luabind::object))&LLookAndFeel::drawRotarySlider, &LLookAndFeel::def_drawRotarySlider)
			.def("getIdealPopupMenuItemSize", (void (LLookAndFeel::*)(luabind::object))&LLookAndFeel::getIdealPopupMenuItemSize, &LLookAndFeel::def_getIdealPopupMenuItemSize)
	];

//	LLookAndFeel_V3::wrapForLua (L);
}

void LookBase::drawRotarySlider (Graphics &g,
                                        int x,
                                        int y,
                                        int width,
                                        int height,
                                        float sliderPosProportional,
                                        float rotaryStartAngle,
                                        float rotaryEndAngle,
                                        Slider &slider)
{
	ParamWrapper wrappedParams (g, x, y, width, height, sliderPosProportional, rotaryStartAngle, rotaryEndAngle, slider);
	owner.drawRotarySlider (wrappedParams);
}

void LookBase::getIdealPopupMenuItemSize (const String &text, bool isSeparator, int standardMenuItemHeight, int &idealWidth, int &idealHeight)
{
	ParamWrapper wrappedParams (text, isSeparator, standardMenuItemHeight, idealWidth, idealHeight);
	owner.getIdealPopupMenuItemSize (wrappedParams);
	idealWidth  = wrappedParams.int_ptr_p0;
	idealHeight = wrappedParams.int_ptr_p1;
}
/*
void setLookAndFeel_V3(Component *c, luabind::object o)
{
    _DBG("::setLookAndFeel_V3");
    if (luabind::type (o) != LUA_TNIL)
    {
        LLookAndFeel_V3 *lookAndFeel_V3= luabind::object_cast<LLookAndFeel_V3*>(o);

        if (lookAndFeel_V3)
        {
            _DBG("\tobject cast to LLookAndFeel_V3 success");

            if (c)
            {
                _DBG("\t\tset look and feel to component");
                c->setLookAndFeel (lookAndFeel_V3);
            }
        }
    }
    else
    {
        if (c)
        {
            _DBG("\tset look and feel to nullptr");
            c->setLookAndFeel (nullptr);
        }
    }
}

void LLookAndFeel_V3::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
        class_<DrawFileBrowserRowParams>("DrawFileBrowserRowParams")
            .property("g", &DrawFileBrowserRowParams::get_g, &DrawFileBrowserRowParams::set_g)
        ,
        class_<DrawPopupMenuItemParams>("DrawPopupMenuItemParams")
            .def(constructor<Graphics &, const Rectangle<int> &, bool, bool, bool, bool, bool, const String &, const String &, const Drawable *, const Colour *>())
        ,
        class_<GetIdealPopupMenuItemSizeParams>("GetIdealPopupMenuItemSizeParams")
			.def(constructor<const String &, bool, int, int, int>())
            .property("text", &GetIdealPopupMenuItemSizeParams::get_text, &GetIdealPopupMenuItemSizeParams::set_text)
        ,
        def("setLookAndFeel_V3", &setLookAndFeel_V3)
        ,
        class_<LookAndFeel_V3, LLookAndFeel_V3>("LookAndFeel_V3")
            .def(constructor<>())
			.def("findColour", &LookAndFeel_V3::findColour, &LLookAndFeel_V3::def_findColour)
			.def("setColour", &LookAndFeel_V3::setColour, &LLookAndFeel_V3::def_setColour)
			.def("isColourSpecified", &LookAndFeel_V3::isColourSpecified, &LLookAndFeel_V3::def_isColourSpecified)
			.def("getTypefaceForFont", &LookAndFeel_V3::getTypefaceForFont, &LLookAndFeel_V3::def_getTypefaceForFont)
			.def("setDefaultSansSerifTypefaceName", &LookAndFeel_V3::setDefaultSansSerifTypefaceName)
			.def("getMouseCursorFor", &LookAndFeel_V3::getMouseCursorFor, &LLookAndFeel_V3::def_getMouseCursorFor, copy(result))
			.def("drawButtonBackground", &LookAndFeel_V3::drawButtonBackground, &LLookAndFeel_V3::def_drawButtonBackground)
			.def("drawButtonText", &LookAndFeel_V3::drawButtonText, &LLookAndFeel_V3::def_drawButtonText)
			.def("drawToggleButton", &LookAndFeel_V3::drawToggleButton, &LLookAndFeel_V3::def_drawToggleButton)
			.def("changeToggleButtonWidthToFitText", &LookAndFeel_V3::changeToggleButtonWidthToFitText, &LLookAndFeel_V3::def_changeToggleButtonWidthToFitText)
			.def("drawTickBox", &LookAndFeel_V3::drawTickBox, &LLookAndFeel_V3::def_drawTickBox)
			.def("createAlertWindow", &LookAndFeel_V3::createAlertWindow, &LLookAndFeel_V3::def_createAlertWindow)
			.def("drawAlertBox", &LookAndFeel_V3::drawAlertBox, &LLookAndFeel_V3::def_drawAlertBox)
			.def("getAlertBoxWindowFlags", &LookAndFeel_V3::getAlertBoxWindowFlags, &LLookAndFeel_V3::def_getAlertBoxWindowFlags)
			.def("getAlertWindowButtonHeight", &LookAndFeel_V3::getAlertWindowButtonHeight, &LLookAndFeel_V3::def_getAlertWindowButtonHeight)
			.def("getAlertWindowMessageFont", &LookAndFeel_V3::getAlertWindowMessageFont, &LLookAndFeel_V3::def_getAlertWindowMessageFont)
			.def("getAlertWindowFont", &LookAndFeel_V3::getAlertWindowFont, &LLookAndFeel_V3::def_getAlertWindowFont)
			.def("setUsingNativeAlertWindows", &LookAndFeel_V3::setUsingNativeAlertWindows)
			.def("isUsingNativeAlertWindows", &LookAndFeel_V3::isUsingNativeAlertWindows)
			.def("drawProgressBar", &LookAndFeel_V3::drawProgressBar, &LLookAndFeel_V3::def_drawProgressBar)
			.def("drawSpinningWaitAnimation", &LookAndFeel_V3::drawSpinningWaitAnimation, &LLookAndFeel_V3::def_drawSpinningWaitAnimation)
			.def("areScrollbarButtonsVisible", &LookAndFeel_V3::areScrollbarButtonsVisible, &LLookAndFeel_V3::def_areScrollbarButtonsVisible)
			.def("getScrollbarEffect", &LookAndFeel_V3::getScrollbarEffect, &LLookAndFeel_V3::def_getScrollbarEffect)
			.def("getMinimumScrollbarThumbSize", &LookAndFeel_V3::getMinimumScrollbarThumbSize, &LLookAndFeel_V3::def_getMinimumScrollbarThumbSize)
			.def("getDefaultScrollbarWidth", &LookAndFeel_V3::getDefaultScrollbarWidth, &LLookAndFeel_V3::def_getDefaultScrollbarWidth)
			.def("getScrollbarButtonSize", &LookAndFeel_V3::getScrollbarButtonSize, &LLookAndFeel_V3::def_getScrollbarButtonSize)
			.def("getTickShape", &LookAndFeel_V3::getTickShape, &LLookAndFeel_V3::def_getTickShape)
			.def("getCrossShape", &LookAndFeel_V3::getCrossShape, &LLookAndFeel_V3::def_getCrossShape)
			.def("drawTreeviewPlusMinusBox", &LookAndFeel_V3::drawTreeviewPlusMinusBox, &LLookAndFeel_V3::def_drawTreeviewPlusMinusBox)
			.def("fillTextEditorBackground", &LookAndFeel_V3::fillTextEditorBackground, &LLookAndFeel_V3::def_fillTextEditorBackground)
			.def("drawTextEditorOutline", &LookAndFeel_V3::drawTextEditorOutline, &LLookAndFeel_V3::def_drawTextEditorOutline)
			.def("createCaretComponent", &LookAndFeel_V3::createCaretComponent, &LLookAndFeel_V3::def_createCaretComponent)
			.def("getDefaultFolderImage", &LookAndFeel_V3::getDefaultFolderImage, &LLookAndFeel_V3::def_getDefaultFolderImage)
			.def("getDefaultDocumentFileImage", &LookAndFeel_V3::getDefaultDocumentFileImage, &LLookAndFeel_V3::def_getDefaultDocumentFileImage)
			.def("createFileChooserHeaderText", &LookAndFeel_V3::createFileChooserHeaderText, &LLookAndFeel_V3::def_createFileChooserHeaderText)
			.def("drawFileBrowserRow", &LookAndFeel_V3::drawFileBrowserRow, &LLookAndFeel_V3::def_drawFileBrowserRow)
			.def("createFileBrowserGoUpButton", &LookAndFeel_V3::createFileBrowserGoUpButton, &LLookAndFeel_V3::def_createFileBrowserGoUpButton)
			.def("layoutFileBrowserComponent", &LookAndFeel_V3::layoutFileBrowserComponent, &LLookAndFeel_V3::def_layoutFileBrowserComponent)
			.def("drawBubble", &LookAndFeel_V3::drawBubble, &LLookAndFeel_V3::def_drawBubble)
			.def("drawLasso", &LookAndFeel_V3::drawLasso, &LLookAndFeel_V3::def_drawLasso)
			.def("drawPopupMenuBackground", &LookAndFeel_V3::drawPopupMenuBackground, &LLookAndFeel_V3::def_drawPopupMenuBackground)
			.def("drawPopupMenuItem", &LookAndFeel_V3::drawPopupMenuItem, &LLookAndFeel_V3::def_drawPopupMenuItem)
			.def("getPopupMenuFont", &LookAndFeel_V3::getPopupMenuFont, &LLookAndFeel_V3::def_getPopupMenuFont)
			.def("drawPopupMenuUpDownArrow", &LookAndFeel_V3::drawPopupMenuUpDownArrow, &LLookAndFeel_V3::def_drawPopupMenuUpDownArrow)
			//.def("getIdealPopupMenuItemSize", &LookAndFeel_V3::getIdealPopupMenuItemSize, &LLookAndFeel_V3::def_getIdealPopupMenuItemSize)
			.def("getMenuWindowFlags", &LookAndFeel_V3::getMenuWindowFlags, &LLookAndFeel_V3::def_getMenuWindowFlags)
			.def("drawMenuBarBackground", &LookAndFeel_V3::drawMenuBarBackground, &LLookAndFeel_V3::def_drawMenuBarBackground)
			.def("getMenuBarItemWidth", &LookAndFeel_V3::getMenuBarItemWidth, &LLookAndFeel_V3::def_getMenuBarItemWidth)
			.def("getMenuBarFont", &LookAndFeel_V3::getMenuBarFont, &LLookAndFeel_V3::def_getMenuBarFont)
			.def("drawMenuBarItem", &LookAndFeel_V3::drawMenuBarItem, &LLookAndFeel_V3::def_drawMenuBarItem)
			.def("drawComboBox", &LookAndFeel_V3::drawComboBox, &LLookAndFeel_V3::def_drawComboBox)
			.def("getComboBoxFont", &LookAndFeel_V3::getComboBoxFont, &LLookAndFeel_V3::def_getComboBoxFont)
			.def("createComboBoxTextBox", &LookAndFeel_V3::createComboBoxTextBox, &LLookAndFeel_V3::def_createComboBoxTextBox)
			.def("positionComboBoxText", &LookAndFeel_V3::positionComboBoxText, &LLookAndFeel_V3::def_positionComboBoxText)
			.def("drawLabel", &LookAndFeel_V3::drawLabel, &LLookAndFeel_V3::def_drawLabel)
			.def("drawLinearSlider", &LookAndFeel_V3::drawLinearSlider, &LLookAndFeel_V3::def_drawLinearSlider)
			.def("drawLinearSliderBackground", &LookAndFeel_V3::drawLinearSliderBackground, &LLookAndFeel_V3::def_drawLinearSliderBackground)
			.def("drawLinearSliderThumb", &LookAndFeel_V3::drawLinearSliderThumb, &LLookAndFeel_V3::def_drawLinearSliderThumb)
			.def("getSliderThumbRadius", &LookAndFeel_V3::getSliderThumbRadius, &LLookAndFeel_V3::def_getSliderThumbRadius)
			.def("drawRotarySlider", &LookAndFeel_V3::drawRotarySlider, &LLookAndFeel_V3::def_drawRotarySlider)
			.def("createSliderButton", &LookAndFeel_V3::createSliderButton, &LLookAndFeel_V3::def_createSliderButton)
			.def("createSliderTextBox", &LookAndFeel_V3::createSliderTextBox, &LLookAndFeel_V3::def_createSliderTextBox)
			.def("getSliderEffect", &LookAndFeel_V3::getSliderEffect, &LLookAndFeel_V3::def_getSliderEffect)
			.def("getTooltipSize", &LookAndFeel_V3::getTooltipSize, &LLookAndFeel_V3::def_getTooltipSize)
			.def("drawTooltip", &LookAndFeel_V3::drawTooltip, &LLookAndFeel_V3::def_drawTooltip)
			.def("createFilenameComponentBrowseButton", &LookAndFeel_V3::createFilenameComponentBrowseButton, &LLookAndFeel_V3::def_drawTooltip)
			.def("layoutFilenameComponent", &LookAndFeel_V3::layoutFilenameComponent, &LLookAndFeel_V3::def_layoutFilenameComponent)
			.def("drawConcertinaPanelHeader", &LookAndFeel_V3::drawConcertinaPanelHeader, &LLookAndFeel_V3::def_drawConcertinaPanelHeader)
			.def("drawCornerResizer", &LookAndFeel_V3::drawCornerResizer, &LLookAndFeel_V3::def_drawCornerResizer)
			.def("drawResizableFrame", &LookAndFeel_V3::drawResizableFrame, &LLookAndFeel_V3::def_drawResizableFrame)
			.def("fillResizableWindowBackground", &LookAndFeel_V3::fillResizableWindowBackground, &LLookAndFeel_V3::def_fillResizableWindowBackground)
			.def("drawResizableWindowBorder", &LookAndFeel_V3::drawResizableWindowBorder, &LLookAndFeel_V3::def_drawResizableWindowBorder)
			.def("drawDocumentWindowTitleBar", &LookAndFeel_V3::drawDocumentWindowTitleBar, &LLookAndFeel_V3::def_drawDocumentWindowTitleBar)
			.def("createDocumentWindowButton", &LookAndFeel_V3::createDocumentWindowButton, &LLookAndFeel_V3::def_createDocumentWindowButton)
			.def("positionDocumentWindowButtons", &LookAndFeel_V3::positionDocumentWindowButtons, &LLookAndFeel_V3::def_positionDocumentWindowButtons)
			.def("getDefaultMenuBarHeight", &LookAndFeel_V3::getDefaultMenuBarHeight, &LLookAndFeel_V3::def_getDefaultMenuBarHeight)
			.def("createDropShadowerForComponent", &LookAndFeel_V3::createDropShadowerForComponent, &LLookAndFeel_V3::def_createDropShadowerForComponent)
			.def("drawStretchableLayoutResizerBar", &LookAndFeel_V3::drawStretchableLayoutResizerBar, &LLookAndFeel_V3::def_drawStretchableLayoutResizerBar)
			.def("drawGroupComponentOutline", &LookAndFeel_V3::drawGroupComponentOutline, &LLookAndFeel_V3::def_drawGroupComponentOutline)
			.def("getTabButtonSpaceAroundImage", &LookAndFeel_V3::getTabButtonSpaceAroundImage, &LLookAndFeel_V3::def_getTabButtonSpaceAroundImage)
			.def("getTabButtonOverlap", &LookAndFeel_V3::getTabButtonOverlap, &LLookAndFeel_V3::def_getTabButtonOverlap)
			.def("getTabButtonBestWidth", &LookAndFeel_V3::getTabButtonBestWidth, &LLookAndFeel_V3::def_getTabButtonBestWidth)
			.def("getTabButtonExtraComponentBounds", &LookAndFeel_V3::getTabButtonExtraComponentBounds, &LLookAndFeel_V3::def_getTabButtonExtraComponentBounds)
			.def("drawTabButton", &LookAndFeel_V3::drawTabButton, &LLookAndFeel_V3::def_drawTabButton)
			.def("drawTabButtonText", &LookAndFeel_V3::drawTabButtonText, &LLookAndFeel_V3::def_drawTabButtonText)
			.def("drawTabAreaBehindFrontButton", &LookAndFeel_V3::drawTabAreaBehindFrontButton, &LLookAndFeel_V3::def_drawTabAreaBehindFrontButton)
			.def("createTabButtonShape", &LookAndFeel_V3::createTabButtonShape, &LLookAndFeel_V3::def_createTabButtonShape)
			.def("fillTabButtonShape", &LookAndFeel_V3::fillTabButtonShape, &LLookAndFeel_V3::def_fillTabButtonShape)
			.def("createTabBarExtrasButton", &LookAndFeel_V3::createTabBarExtrasButton, &LLookAndFeel_V3::def_createTabBarExtrasButton)
			.def("drawImageButton", &LookAndFeel_V3::drawImageButton, &LLookAndFeel_V3::def_drawImageButton)
			.def("drawTableHeaderBackground", &LookAndFeel_V3::drawTableHeaderBackground, &LLookAndFeel_V3::def_drawTableHeaderBackground)
			.def("drawTableHeaderColumn", &LookAndFeel_V3::drawTableHeaderColumn, &LLookAndFeel_V3::def_drawTableHeaderColumn)
			.def("paintToolbarBackground", &LookAndFeel_V3::paintToolbarBackground, &LLookAndFeel_V3::def_paintToolbarBackground)
			.def("createToolbarMissingItemsButton", &LookAndFeel_V3::createToolbarMissingItemsButton, &LLookAndFeel_V3::def_createToolbarMissingItemsButton)
			.def("paintToolbarButtonBackground", &LookAndFeel_V3::paintToolbarButtonBackground, &LLookAndFeel_V3::def_paintToolbarButtonBackground)
			.def("paintToolbarButtonLabel", &LookAndFeel_V3::paintToolbarButtonLabel, &LLookAndFeel_V3::def_paintToolbarButtonLabel)
			.def("drawPropertyPanelSectionHeader", &LookAndFeel_V3::drawPropertyPanelSectionHeader, &LLookAndFeel_V3::def_drawPropertyPanelSectionHeader)
			.def("drawPropertyComponentBackground", &LookAndFeel_V3::drawPropertyComponentBackground, &LLookAndFeel_V3::def_drawGroupComponentOutline)
			.def("drawPropertyComponentLabel", &LookAndFeel_V3::drawPropertyComponentLabel, &LLookAndFeel_V3::def_drawPropertyComponentLabel)
			.def("getPropertyComponentContentPosition", &LookAndFeel_V3::getPropertyComponentContentPosition, &LLookAndFeel_V3::def_getPropertyComponentContentPosition)
			.def("drawCallOutBoxBackground", &LookAndFeel_V3::drawCallOutBoxBackground, &LLookAndFeel_V3::def_drawCallOutBoxBackground)
			.def("drawLevelMeter", &LookAndFeel_V3::drawLevelMeter, &LLookAndFeel_V3::def_drawLevelMeter)
			.def("drawKeymapChangeButton", &LookAndFeel_V3::drawKeymapChangeButton, &LLookAndFeel_V3::def_drawKeymapChangeButton)
			.def("playAlertSound", &LookAndFeel_V3::playAlertSound, &LLookAndFeel_V3::def_playAlertSound)
			.scope
			[
                def("getDefaultLookAndFeel", &LookAndFeel_V3::getDefaultLookAndFeel),
                def("setDefaultLookAndFeel", &LookAndFeel_V3::setDefaultLookAndFeel),
                def("drawGlassSphere", &LookAndFeel_V3::drawGlassSphere),
                def("drawGlassPointer", &LookAndFeel_V3::drawGlassPointer),
                def("drawBevel", &LookAndFeel_V3::drawBevel)
			]
	];
}
*/
