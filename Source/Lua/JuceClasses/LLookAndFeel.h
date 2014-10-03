#ifndef L_LOOK_AND_FEEL
#define L_LOOK_AND_FEEL

#include "LookAndFeelBase.h"

class LLookAndFeel : public LookAndFeelBase, public luabind::wrap_base
{
	public:
  		LLookAndFeel() : LookAndFeelBase(*this){}
	 	static void wrapForLua (lua_State *L);

		Colour findColour (ParamWrapper &p)
		{ try { return (call<Colour>("findColour", p)); } catch (luabind::error e) { _WRN("findColour "+_STR(e.what())); }}
		static Colour def_findColour(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.findColour (p.colourId)); }

		void setColour (ParamWrapper &p)
		{ try { call<void>("setColour", p); } catch (luabind::error e) { _WRN("setColour "+_STR(e.what())); } }
		static void def_setColour(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.setColour (p.colourId, p.colour); }

		bool isColourSpecified (ParamWrapper &p)
		{ try { return (call<bool>("isColourSpecified", p)); } catch (luabind::error e) { _WRN("isColourSpecified "+_STR(e.what())); } }
		static bool def_isColourSpecified(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.isColourSpecified (p.colourId)); }

		Typeface::Ptr getTypefaceForFont (ParamWrapper &p)
		{ try { return (call<Typeface::Ptr>("getTypefaceForFont", p)); } catch (luabind::error e) { _WRN("getTypefaceForFont "+_STR(e.what())); } }
		static Typeface::Ptr def_getTypefaceForFont(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getTypefaceForFont (p.font)); }

		MouseCursor getMouseCursorFor (ParamWrapper &p)
		{ try { return (call<MouseCursor>("getMouseCursorFor", p)); } catch (luabind::error e) { _WRN("getMouseCursorFor "+_STR(e.what())); } }
		static MouseCursor def_getMouseCursorFor(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getMouseCursorFor (*p.component)); }

		void drawButtonBackground (ParamWrapper &p)
		{ try { call<void>("drawButtonBackground", p); } catch (luabind::error e) { _WRN("drawButtonBackground "+_STR(e.what())); } }
		static void def_drawButtonBackground(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawButtonBackground (*p.g, *p.button, p.backgroundColour, p.isMouseOverButton, p.isButtonDown); }

		void drawButtonText (ParamWrapper &p)
		{ try { call<void>("drawButtonText", p); } catch (luabind::error e) { _WRN("drawButtonText "+_STR(e.what())); } }
		static void def_drawButtonText(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawButtonText (*p.g, *p.textButton, p.isMouseOverButton, p.isButtonDown); }

		void drawToggleButton (ParamWrapper &p)
		{ try { call<void>("drawToggleButton", p); } catch (luabind::error e) { _WRN("drawToggleButton "+_STR(e.what())); } }
		static void def_drawToggleButton(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawToggleButton (*p.g, *p.toggleButton, p.isMouseOverButton, p.isButtonDown); }

		void changeToggleButtonWidthToFitText (ParamWrapper &p)
		{ try { call<void>("changeToggleButtonWidthToFitText", p); } catch (luabind::error e) { _WRN("changeToggleButtonWidthToFitText "+_STR(e.what())); } }
		static void def_changeToggleButtonWidthToFitText(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.changeToggleButtonWidthToFitText (*p.toggleButton); }

		void drawTickBox (ParamWrapper &p)
		{ try { call<void>("drawTickBox", p); } catch (luabind::error e) { _WRN("drawTickBox "+_STR(e.what())); } }
		static void def_drawTickBox(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawTickBox (*p.g, *p.component, p.x, p.y, p.w, p.h, p.ticked, p.isEnabled, p.isMouseOverButton, p.isButtonDown); }

		AlertWindow* createAlertWindow (ParamWrapper &p)
		{ try { return (call<AlertWindow*>("createAlertWindow", p)); } catch (luabind::error e) { _WRN("createAlertWindow "+_STR(e.what())); } }
		static AlertWindow* def_createAlertWindow(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.createAlertWindow (p.title, p.message, p.button1, p.button2, p.button3, p.iconType, p.numButtons, p.associatedComponent)); }

		void drawAlertBox (ParamWrapper &p)
		{ try { call<void>("drawAlertBox", p); } catch (luabind::error e) { _WRN("drawAlertBox "+_STR(e.what())); } }
		static void def_drawAlertBox(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawAlertBox (*p.g, *p.window, p.textArea, *p.layout); }

		int getAlertBoxWindowFlags (ParamWrapper &p)
		{ try { return (call<int>("getAlertBoxWindowFlags", p)); } catch (luabind::error e) { _WRN("getAlertBoxWindowFlags "+_STR(e.what())); } }
		static int def_getAlertBoxWindowFlags(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getAlertBoxWindowFlags ()); }

		int getAlertWindowButtonHeight (ParamWrapper &p)
		{ try { return (call<int>("getAlertWindowButtonHeight", p)); } catch (luabind::error e) { _WRN("getAlertWindowButtonHeight "+_STR(e.what())); } }
		static int def_getAlertWindowButtonHeight(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getAlertWindowButtonHeight ()); }

		Font getAlertWindowMessageFont (ParamWrapper &p)
		{ try { return (call<Font>("getAlertWindowMessageFont", p)); } catch (luabind::error e) { _WRN("getAlertWindowMessageFont "+_STR(e.what())); } }
		static Font def_getAlertWindowMessageFont(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getAlertWindowMessageFont ()); }

		Font getAlertWindowFont (ParamWrapper &p)
		{ try { return (call<Font>("getAlertWindowFont", p)); } catch (luabind::error e) { _WRN("getAlertWindowFont "+_STR(e.what())); } }
		static Font def_getAlertWindowFont(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getAlertWindowFont ()); }

		void drawProgressBar (ParamWrapper &p)
		{ try { call<void>("drawProgressBar", p); } catch (luabind::error e) { _WRN("drawProgressBar "+_STR(e.what())); } }
		static void def_drawProgressBar(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawProgressBar (*p.g, *p.progressBar, p.width, p.height, p.progress, p.textToShow); }

		void drawSpinningWaitAnimation (ParamWrapper &p)
		{ try { call<void>("drawSpinningWaitAnimation", p); } catch (luabind::error e) { _WRN("drawSpinningWaitAnimation "+_STR(e.what())); } }
		static void def_drawSpinningWaitAnimation(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawSpinningWaitAnimation (*p.g, p.colour, p.x, p.y, p.w, p.h); }

		bool areScrollbarButtonsVisible (ParamWrapper &p)
		{ try { return (call<bool>("areScrollbarButtonsVisible", p)); } catch (luabind::error e) { _WRN("areScrollbarButtonsVisible "+_STR(e.what())); } }
		static bool def_areScrollbarButtonsVisible(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.areScrollbarButtonsVisible ()); }

		ImageEffectFilter* getScrollbarEffect (ParamWrapper &p)
		{ try { return (call<ImageEffectFilter*>("getScrollbarEffect", p)); } catch (luabind::error e) { _WRN("getScrollbarEffect "+_STR(e.what())); } }
		static ImageEffectFilter* def_getScrollbarEffect(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getScrollbarEffect ()); }

		int getMinimumScrollbarThumbSize (ParamWrapper &p)
		{ try { return (call<int>("getMinimumScrollbarThumbSize", p)); } catch (luabind::error e) { _WRN("getMinimumScrollbarThumbSize "+_STR(e.what())); } }
		static int def_getMinimumScrollbarThumbSize(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getMinimumScrollbarThumbSize (*p.scrollBar)); }

		int getDefaultScrollbarWidth (ParamWrapper &p)
		{ try { return (call<int>("getDefaultScrollbarWidth", p)); } catch (luabind::error e) { _WRN("getDefaultScrollbarWidth "+_STR(e.what())); } }
		static int def_getDefaultScrollbarWidth(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getDefaultScrollbarWidth ()); }

		int getScrollbarButtonSize (ParamWrapper &p)
		{ try { return (call<int>("getScrollbarButtonSize", p)); } catch (luabind::error e) { _WRN("getScrollbarButtonSize "+_STR(e.what())); } }
		static int def_getScrollbarButtonSize(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getScrollbarButtonSize (*p.scrollBar)); }

		Path getTickShape (ParamWrapper &p)
		{ try { return (call<Path>("getTickShape", p)); } catch (luabind::error e) { _WRN("getTickShape "+_STR(e.what())); } }
		static Path def_getTickShape(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getTickShape (p.height)); }

		Path getCrossShape (ParamWrapper &p)
		{ try { return (call<Path>("getCrossShape", p)); } catch (luabind::error e) { _WRN("getCrossShape "+_STR(e.what())); } }
		static Path def_getCrossShape(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getCrossShape (p.height)); }

		void drawTreeviewPlusMinusBox (ParamWrapper &p)
		{ try { call<void>("drawTreeviewPlusMinusBox", p); } catch (luabind::error e) { _WRN("drawTreeviewPlusMinusBox "+_STR(e.what())); } }
		static void def_drawTreeviewPlusMinusBox(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawTreeviewPlusMinusBox (*p.g, p.area, p.backgroundColour, p.isOpen, p.isMouseOver); }

		void fillTextEditorBackground (ParamWrapper &p)
		{ try { call<void>("fillTextEditorBackground", p); } catch (luabind::error e) { _WRN("fillTextEditorBackground "+_STR(e.what())); } }
		static void def_fillTextEditorBackground(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.fillTextEditorBackground (*p.g, p.width, p.height, *p.textEditor); }

		void drawTextEditorOutline (ParamWrapper &p)
		{ try { call<void>("drawTextEditorOutline", p); } catch (luabind::error e) { _WRN("drawTextEditorOutline "+_STR(e.what())); } }
		static void def_drawTextEditorOutline(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawTextEditorOutline (*p.g, p.width, p.height, *p.textEditor); }

		CaretComponent* createCaretComponent (ParamWrapper &p)
		{ try { return (call<CaretComponent*>("createCaretComponent", p)); } catch (luabind::error e) { _WRN("createCaretComponent "+_STR(e.what())); } }
		static CaretComponent* def_createCaretComponent(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.createCaretComponent (p.keyFocusOwner)); }

		const Drawable* getDefaultFolderImage (ParamWrapper &p)
		{ try { return (call<const Drawable*>("getDefaultFolderImage", p)); } catch (luabind::error e) { _WRN("getDefaultFolderImage "+_STR(e.what())); } }
		static const Drawable* def_getDefaultFolderImage(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getDefaultFolderImage ()); }

		const Drawable* getDefaultDocumentFileImage (ParamWrapper &p)
		{ try { return (call<const Drawable*>("getDefaultDocumentFileImage", p)); } catch (luabind::error e) { _WRN("getDefaultDocumentFileImage "+_STR(e.what())); } }
		static const Drawable* def_getDefaultDocumentFileImage(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getDefaultDocumentFileImage ()); }

		AttributedString createFileChooserHeaderText (ParamWrapper &p)
		{ try { return (call<AttributedString>("createFileChooserHeaderText", p)); } catch (luabind::error e) { _WRN("createFileChooserHeaderText "+_STR(e.what())); } }
		static AttributedString def_createFileChooserHeaderText(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.createFileChooserHeaderText (p.title, p.instructions)); }

		void drawFileBrowserRow (ParamWrapper &p)
		{ try { call<void>("drawFileBrowserRow", p); } catch (luabind::error e) { _WRN("drawFileBrowserRow "+_STR(e.what())); } }
		static void def_drawFileBrowserRow(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawFileBrowserRow (*p.g, p.width, p.height, p.filename, p.icon, p.fileSizeDescription, p.fileTimeDescription, p.isDirectory, p.isItemSelected, p.itemIndex, *p.directoryContentsDisplayComponent); }

		Button* createFileBrowserGoUpButton (ParamWrapper &p)
		{ try { return (call<Button*>("createFileBrowserGoUpButton", p)); } catch (luabind::error e) { _WRN("createFileBrowserGoUpButton "+_STR(e.what())); } }
		static Button* def_createFileBrowserGoUpButton(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.createFileBrowserGoUpButton ()); }

		void layoutFileBrowserComponent (ParamWrapper &p)
		{ try { call<void>("layoutFileBrowserComponent", p); } catch (luabind::error e) { _WRN("layoutFileBrowserComponent "+_STR(e.what())); } }
		static void def_layoutFileBrowserComponent(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.layoutFileBrowserComponent (*p.fileBrowserComponent, p.directoryContentsDisplayComponent, p.filePreviewComponent, p.currentPathBox, p.filenameBox, p.goUpButton); }

		void drawBubble (ParamWrapper &p)
		{ try { call<void>("drawBubble", p); } catch (luabind::error e) { _WRN("drawBubble "+_STR(e.what())); } }
		static void def_drawBubble(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawBubble (*p.g, *p.bubble, p.tip, p.body); }

		void drawLasso (ParamWrapper &p)
		{ try { call<void>("drawLasso", p); } catch (luabind::error e) { _WRN("drawLasso "+_STR(e.what())); } }
		static void def_drawLasso(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawLasso (*p.g, *p.component); }

		void drawPopupMenuBackground (ParamWrapper &p)
		{ try { call<void>("drawPopupMenuBackground", p); } catch (luabind::error e) { _WRN("drawPopupMenuBackground "+_STR(e.what())); } }
		static void def_drawPopupMenuBackground(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawPopupMenuBackground (*p.g, p.width, p.height); }

		void drawPopupMenuItem (ParamWrapper &p)
		{ try { call<void>("drawPopupMenuItem", p); } catch (luabind::error e) { _WRN("drawPopupMenuItem "+_STR(e.what())); } }
		static void def_drawPopupMenuItem(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawPopupMenuItem (*p.g, p.areaInt, p.isSeparator, p.isActive, p.isHighlighted, p.isTicked, p.hasSubMenu, p.text, p.shortcutKeyText, p.drawableIcon, &p.textColour); }

		Font getPopupMenuFont (ParamWrapper &p)
		{ try { return (call<Font>("getPopupMenuFont", p)); } catch (luabind::error e) { _WRN("getPopupMenuFont "+_STR(e.what())); } }
		static Font def_getPopupMenuFont(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getPopupMenuFont ()); }

		void drawPopupMenuUpDownArrow (ParamWrapper &p)
		{ try { call<void>("drawPopupMenuUpDownArrow", p); } catch (luabind::error e) { _WRN("drawPopupMenuUpDownArrow "+_STR(e.what())); } }
		static void def_drawPopupMenuUpDownArrow(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawPopupMenuUpDownArrow (*p.g, p.width, p.height, p.isScrollUpArrow); }

		void getIdealPopupMenuItemSize (ParamWrapper &p)
		{ try { call<void>("getIdealPopupMenuItemSize", p); } catch (luabind::error e) { _WRN("getIdealPopupMenuItemSize "+_STR(e.what())); } }
		static void def_getIdealPopupMenuItemSize(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.getIdealPopupMenuItemSize (p.text, p.isSeparator, p.standardMenuItemHeight, p.idealWidth, p.idealHeight); }

		int getMenuWindowFlags (ParamWrapper &p)
		{ try { return (call<int>("getMenuWindowFlags", p)); } catch (luabind::error e) { _WRN("getMenuWindowFlags "+_STR(e.what())); } }
		static int def_getMenuWindowFlags(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getMenuWindowFlags ()); }

		void drawMenuBarBackground (ParamWrapper &p)
		{ try { call<void>("drawMenuBarBackground", p); } catch (luabind::error e) { _WRN("drawMenuBarBackground "+_STR(e.what())); } }
		static void def_drawMenuBarBackground(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawMenuBarBackground (*p.g, p.width, p.height, p.isMouseOverBar, *p.menuBarComponent); }

		int getMenuBarItemWidth (ParamWrapper &p)
		{ try { return (call<int>("getMenuBarItemWidth", p)); } catch (luabind::error e) { _WRN("getMenuBarItemWidth "+_STR(e.what())); } }
		static int def_getMenuBarItemWidth(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getMenuBarItemWidth (*p.menuBarComponent, p.itemIndex, p.itemText)); }

		Font getMenuBarFont (ParamWrapper &p)
		{ try { return (call<Font>("getMenuBarFont", p)); } catch (luabind::error e) { _WRN("getMenuBarFont "+_STR(e.what())); } }
		static Font def_getMenuBarFont(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getMenuBarFont (*p.menuBarComponent, p.itemIndex, p.itemText)); }

		void drawMenuBarItem (ParamWrapper &p)
		{ try { call<void>("drawMenuBarItem", p); } catch (luabind::error e) { _WRN("drawMenuBarItem "+_STR(e.what())); } }
		static void def_drawMenuBarItem(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawMenuBarItem (*p.g, p.width, p.height, p.itemIndex, p.itemText, p.isMouseOverItem, p.isMenuOpen, p.isMouseOverBar, *p.menuBarComponent); }

		void drawComboBox (ParamWrapper &p)
		{ try { call<void>("drawComboBox", p); } catch (luabind::error e) { _WRN("drawComboBox "+_STR(e.what())); } }
		static void def_drawComboBox(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawComboBox (*p.g, p.width, p.height, p.isButtonDown, p.buttonX, p.buttonY, p.buttonW, p.buttonH, *p.comboBox); }

		Font getComboBoxFont (ParamWrapper &p)
		{ try { return (call<Font>("getComboBoxFont", p)); } catch (luabind::error e) { _WRN("getComboBoxFont "+_STR(e.what())); } }
		static Font def_getComboBoxFont(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getComboBoxFont (*p.comboBox)); }

		Label* createComboBoxTextBox (ParamWrapper &p)
		{ try { return (call<Label*>("createComboBoxTextBox", p)); } catch (luabind::error e) { _WRN("createComboBoxTextBox "+_STR(e.what())); } }
		static Label* def_createComboBoxTextBox(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.createComboBoxTextBox (*p.comboBox)); }

		void positionComboBoxText (ParamWrapper &p)
		{ try { call<void>("positionComboBoxText", p); } catch (luabind::error e) { _WRN("positionComboBoxText "+_STR(e.what())); } }
		static void def_positionComboBoxText(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.positionComboBoxText (*p.comboBox, *p.label); }

		void drawLabel (ParamWrapper &p)
		{ try { call<void>("drawLabel", p); } catch (luabind::error e) { _WRN("drawLabel "+_STR(e.what())); } }
		static void def_drawLabel(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawLabel (*p.g, *p.label); }

		void drawLinearSlider (ParamWrapper &p)
		{ try { call<void>("drawLinearSlider", p); } catch (luabind::error e) { _WRN("drawLinearSlider "+_STR(e.what())); } }
		static void def_drawLinearSlider(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawLinearSlider (*p.g, p.x, p.y, p.width, p.height, p.sliderPos, p.minSliderPos, p.maxSliderPos, p.sliderStyle, *p.slider); }

		void drawLinearSliderBackground (ParamWrapper &p)
		{ try { call<void>("drawLinearSliderBackground", p); } catch (luabind::error e) { _WRN("drawLinearSliderBackground "+_STR(e.what())); } }
		static void def_drawLinearSliderBackground(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawLinearSliderBackground (*p.g, p.x, p.y, p.width, p.height, p.sliderPos, p.minSliderPos, p.maxSliderPos, p.sliderStyle, *p.slider); }

		void drawLinearSliderThumb (ParamWrapper &p)
		{ try { call<void>("drawLinearSliderThumb", p); } catch (luabind::error e) { _WRN("drawLinearSliderThumb "+_STR(e.what())); } }
		static void def_drawLinearSliderThumb(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawLinearSliderThumb (*p.g, p.x, p.y, p.width, p.height, p.sliderPos, p.minSliderPos, p.maxSliderPos, p.sliderStyle, *p.slider); }

		int getSliderThumbRadius (ParamWrapper &p)
		{ try { return (call<int>("getSliderThumbRadius", p)); } catch (luabind::error e) { _WRN("getSliderThumbRadius "+_STR(e.what())); } }
		static int def_getSliderThumbRadius(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getSliderThumbRadius (*p.slider)); }

		void drawRotarySlider (ParamWrapper &p)
		{ try { call<void>("drawRotarySlider", p); } catch (luabind::error e) { _WRN("drawRotarySlider "+_STR(e.what())); } }
		static void def_drawRotarySlider(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawRotarySlider (*p.g, p.x, p.y, p.width, p.height, p.sliderPosProportional, p.rotaryStartAngle, p.rotaryEndAngle, *p.slider); }

		Button* createSliderButton (ParamWrapper &p)
		{ try { return (call<Button*>("createSliderButton", p)); } catch (luabind::error e) { _WRN("createSliderButton "+_STR(e.what())); } }
		static Button* def_createSliderButton(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.createSliderButton (*p.slider, p.isIncrement)); }

		Label* createSliderTextBox (ParamWrapper &p)
		{ try { return (call<Label*>("createSliderTextBox", p)); } catch (luabind::error e) { _WRN("createSliderTextBox "+_STR(e.what())); } }
		static Label* def_createSliderTextBox(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.createSliderTextBox (*p.slider)); }

		ImageEffectFilter* getSliderEffect (ParamWrapper &p)
		{ try { return (call<ImageEffectFilter*>("getSliderEffect", p)); } catch (luabind::error e) { _WRN("getSliderEffect "+_STR(e.what())); } }
		static ImageEffectFilter* def_getSliderEffect(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getSliderEffect (*p.slider)); }

		void getTooltipSize (ParamWrapper &p)
		{ try { call<void>("getTooltipSize", p); } catch (luabind::error e) { _WRN("getTooltipSize "+_STR(e.what())); } }
		static void def_getTooltipSize(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.getTooltipSize (p.tipText, p.width, p.height); }

		void drawTooltip (ParamWrapper &p)
		{ try { call<void>("drawTooltip", p); } catch (luabind::error e) { _WRN("drawTooltip "+_STR(e.what())); } }
		static void def_drawTooltip(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawTooltip (*p.g, p.text, p.width, p.height); }

		Button* createFilenameComponentBrowseButton (ParamWrapper &p)
		{ try { return (call<Button*>("createFilenameComponentBrowseButton", p)); } catch (luabind::error e) { _WRN("createFilenameComponentBrowseButton "+_STR(e.what())); } }
		static Button* def_createFilenameComponentBrowseButton(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.createFilenameComponentBrowseButton (p.text)); }

		void layoutFilenameComponent (ParamWrapper &p)
		{ try { call<void>("layoutFilenameComponent", p); } catch (luabind::error e) { _WRN("layoutFilenameComponent "+_STR(e.what())); } }
		static void def_layoutFilenameComponent(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.layoutFilenameComponent (*p.filenameComponent, p.comboBox, p.button); }

		void drawConcertinaPanelHeader (ParamWrapper &p)
		{ try { call<void>("drawConcertinaPanelHeader", p); } catch (luabind::error e) { _WRN("drawConcertinaPanelHeader "+_STR(e.what())); } }
		static void def_drawConcertinaPanelHeader(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawConcertinaPanelHeader (*p.g, p.areaInt, p.isMouseOver, p.isMouseDown, *p.concertinaPanel, *p.component); }

		void drawCornerResizer (ParamWrapper &p)
		{ try { call<void>("drawCornerResizer", p); } catch (luabind::error e) { _WRN("drawCornerResizer "+_STR(e.what())); } }
		static void def_drawCornerResizer(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawCornerResizer (*p.g, p.w, p.h, p.isMouseOver, p.isMouseDragging); }

		void drawResizableFrame (ParamWrapper &p)
		{ try { call<void>("drawResizableFrame", p); } catch (luabind::error e) { _WRN("drawResizableFrame "+_STR(e.what())); } }
		static void def_drawResizableFrame(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawResizableFrame (*p.g, p.w, p.h, p.borderSize); }

		void fillResizableWindowBackground (ParamWrapper &p)
		{ try { call<void>("fillResizableWindowBackground", p); } catch (luabind::error e) { _WRN("fillResizableWindowBackground "+_STR(e.what())); } }
		static void def_fillResizableWindowBackground(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.fillResizableWindowBackground (*p.g, p.w, p.h, p.borderSize, *p.resizableWindow); }

		void drawResizableWindowBorder (ParamWrapper &p)
		{ try { call<void>("drawResizableWindowBorder", p); } catch (luabind::error e) { _WRN("drawResizableWindowBorder "+_STR(e.what())); } }
		static void def_drawResizableWindowBorder(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawResizableWindowBorder (*p.g, p.w, p.h, p.borderSize, *p.resizableWindow); }

		void drawDocumentWindowTitleBar (ParamWrapper &p)
		{ try { call<void>("drawDocumentWindowTitleBar", p); } catch (luabind::error e) { _WRN("drawDocumentWindowTitleBar "+_STR(e.what())); } }
		static void def_drawDocumentWindowTitleBar(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawDocumentWindowTitleBar (*p.documentWindow, *p.g, p.w, p.h, p.titleSpaceX, p.titleSpaceW, p.icon, p.drawTitleTextOnLeft); }

		Button* createDocumentWindowButton (ParamWrapper &p)
		{ try { return (call<Button*>("createDocumentWindowButton", p)); } catch (luabind::error e) { _WRN("createDocumentWindowButton "+_STR(e.what())); } }
		static Button* def_createDocumentWindowButton(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.createDocumentWindowButton (p.buttonType)); }

		void positionDocumentWindowButtons (ParamWrapper &p)
		{ try { call<void>("positionDocumentWindowButtons", p); } catch (luabind::error e) { _WRN("positionDocumentWindowButtons "+_STR(e.what())); } }
		static void def_positionDocumentWindowButtons(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.positionDocumentWindowButtons (*p.documentWindow, p.titleBarX, p.titleBarY, p.titleBarW, p.titleBarH, p.minimiseButton, p.maximiseButton, p.closeButton, p.positionTitleBarButtonsOnLeft); }

		int getDefaultMenuBarHeight (ParamWrapper &p)
		{ try { return (call<int>("getDefaultMenuBarHeight", p)); } catch (luabind::error e) { _WRN("getDefaultMenuBarHeight "+_STR(e.what())); } }
		static int def_getDefaultMenuBarHeight(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getDefaultMenuBarHeight ()); }

		DropShadower* createDropShadowerForComponent (ParamWrapper &p)
		{ try { return (call<DropShadower*>("createDropShadowerForComponent", p)); } catch (luabind::error e) { _WRN("createDropShadowerForComponent "+_STR(e.what())); } }
		static DropShadower* def_createDropShadowerForComponent(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.createDropShadowerForComponent (p.component)); }

		void drawGroupComponentOutline (ParamWrapper &p)
		{ try { call<void>("drawGroupComponentOutline", p); } catch (luabind::error e) { _WRN("drawGroupComponentOutline "+_STR(e.what())); } }
		static void def_drawGroupComponentOutline(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawGroupComponentOutline (*p.g, p.w, p.h, p.text, *p.justification, *p.groupComponent); }

		int getTabButtonSpaceAroundImage (ParamWrapper &p)
		{ try { return (call<int>("getTabButtonSpaceAroundImage", p)); } catch (luabind::error e) { _WRN("getTabButtonSpaceAroundImage "+_STR(e.what())); } }
		static int def_getTabButtonSpaceAroundImage(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getTabButtonSpaceAroundImage ()); }

		int getTabButtonOverlap (ParamWrapper &p)
		{ try { return (call<int>("getTabButtonOverlap", p)); } catch (luabind::error e) { _WRN("getTabButtonOverlap "+_STR(e.what())); } }
		static int def_getTabButtonOverlap(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getTabButtonOverlap (p.tabDepth)); }

		int getTabButtonBestWidth (ParamWrapper &p)
		{ try { return (call<int>("getTabButtonBestWidth", p)); } catch (luabind::error e) { _WRN("getTabButtonBestWidth "+_STR(e.what())); } }
		static int def_getTabButtonBestWidth(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getTabButtonBestWidth (*p.tabBarButton, p.tabDepth)); }

		Rectangle<int> getTabButtonExtraComponentBounds (ParamWrapper &p)
		{ try { return (call<Rectangle<int>>("getTabButtonExtraComponentBounds", p)); } catch (luabind::error e) { _WRN("getTabButtonExtraComponentBounds "+_STR(e.what())); } }
		static Rectangle<int> def_getTabButtonExtraComponentBounds(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getTabButtonExtraComponentBounds (*p.tabBarButton, p.textArea, *p.component)); }

		void drawTabButton (ParamWrapper &p)
		{ try { call<void>("drawTabButton", p); } catch (luabind::error e) { _WRN("drawTabButton "+_STR(e.what())); } }
		static void def_drawTabButton(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawTabButton (*p.tabBarButton, *p.g, p.isMouseOver, p.isMouseDown); }

		void drawTabButtonText (ParamWrapper &p)
		{ try { call<void>("drawTabButtonText", p); } catch (luabind::error e) { _WRN("drawTabButtonText "+_STR(e.what())); } }
		static void def_drawTabButtonText(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawTabButtonText (*p.tabBarButton, *p.g, p.isMouseOver, p.isMouseDown); }

		void drawTabAreaBehindFrontButton (ParamWrapper &p)
		{ try { call<void>("drawTabAreaBehindFrontButton", p); } catch (luabind::error e) { _WRN("drawTabAreaBehindFrontButton "+_STR(e.what())); } }
		static void def_drawTabAreaBehindFrontButton(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawTabAreaBehindFrontButton (*p.tabbedButtonBar, *p.g, p.w, p.h); }

		void createTabButtonShape (ParamWrapper &p)
		{ try { call<void>("createTabButtonShape", p); } catch (luabind::error e) { _WRN("createTabButtonShape "+_STR(e.what())); } }
		static void def_createTabButtonShape(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.createTabButtonShape (*p.tabBarButton, *p.p, p.isMouseOver, p.isMouseDown); }

		void fillTabButtonShape (ParamWrapper &p)
		{ try { call<void>("fillTabButtonShape", p); } catch (luabind::error e) { _WRN("fillTabButtonShape "+_STR(e.what())); } }
		static void def_fillTabButtonShape(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.fillTabButtonShape (*p.tabBarButton, *p.g, *p.p, p.isMouseOver, p.isMouseDown); }

		Button* createTabBarExtrasButton (ParamWrapper &p)
		{ try { return (call<Button*>("createTabBarExtrasButton", p)); } catch (luabind::error e) { _WRN("createTabBarExtrasButton "+_STR(e.what())); } }
		static Button* def_createTabBarExtrasButton(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.createTabBarExtrasButton ()); }

		void drawImageButton (ParamWrapper &p)
		{ try { call<void>("drawImageButton", p); } catch (luabind::error e) { _WRN("drawImageButton "+_STR(e.what())); } }
		static void def_drawImageButton(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawImageButton (*p.g, p.image, p.imageX, p.imageY, p.imageW, p.imageH, p.overlayColour, p.imageOpacity, *p.imageButton); }

		void drawTableHeaderBackground (ParamWrapper &p)
		{ try { call<void>("drawTableHeaderBackground", p); } catch (luabind::error e) { _WRN("drawTableHeaderBackground "+_STR(e.what())); } }
		static void def_drawTableHeaderBackground(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawTableHeaderBackground (*p.g, *p.tableHeaderComponent); }

		void drawTableHeaderColumn (ParamWrapper &p)
		{ try { call<void>("drawTableHeaderColumn", p); } catch (luabind::error e) { _WRN("drawTableHeaderColumn "+_STR(e.what())); } }
		static void def_drawTableHeaderColumn(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawTableHeaderColumn (*p.g, p.columnName, p.columnId, p.width, p.height, p.isMouseOver, p.isMouseDown, p.columnFlags); }

		void paintToolbarBackground (ParamWrapper &p)
		{ try { call<void>("paintToolbarBackground", p); } catch (luabind::error e) { _WRN("paintToolbarBackground "+_STR(e.what())); } }
		static void def_paintToolbarBackground(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.paintToolbarBackground (*p.g, p.width, p.height, *p.toolbar); }

		Button* createToolbarMissingItemsButton (ParamWrapper &p)
		{ try { return (call<Button*>("createToolbarMissingItemsButton", p)); } catch (luabind::error e) { _WRN("createToolbarMissingItemsButton "+_STR(e.what())); } }
		static Button* def_createToolbarMissingItemsButton(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.createToolbarMissingItemsButton (*p.toolbar)); }

		void paintToolbarButtonBackground (ParamWrapper &p)
		{ try { call<void>("paintToolbarButtonBackground", p); } catch (luabind::error e) { _WRN("paintToolbarButtonBackground "+_STR(e.what())); } }
		static void def_paintToolbarButtonBackground(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.paintToolbarButtonBackground (*p.g, p.width, p.height, p.isMouseOver, p.isMouseDown, *p.toolbarItemComponent); }

		void paintToolbarButtonLabel (ParamWrapper &p)
		{ try { call<void>("paintToolbarButtonLabel", p); } catch (luabind::error e) { _WRN("paintToolbarButtonLabel "+_STR(e.what())); } }
		static void def_paintToolbarButtonLabel(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.paintToolbarButtonLabel (*p.g, p.x, p.y, p.width, p.height, p.text, *p.toolbarItemComponent); }

		void drawStretchableLayoutResizerBar (ParamWrapper &p)
		{ try { call<void>("drawStretchableLayoutResizerBar", p); } catch (luabind::error e) { _WRN("drawStretchableLayoutResizerBar "+_STR(e.what())); } }
		static void def_drawStretchableLayoutResizerBar(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawStretchableLayoutResizerBar (*p.g, p.w, p.h, p.isVerticalBar, p.isMouseOver, p.isMouseDragging); }

		void drawPropertyPanelSectionHeader (ParamWrapper &p)
		{ try { call<void>("drawPropertyPanelSectionHeader", p); } catch (luabind::error e) { _WRN("drawPropertyPanelSectionHeader "+_STR(e.what())); } }
		static void def_drawPropertyPanelSectionHeader(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawPropertyPanelSectionHeader (*p.g, p.name, p.isOpen, p.width, p.height); }

		void drawPropertyComponentBackground (ParamWrapper &p)
		{ try { call<void>("drawPropertyComponentBackground", p); } catch (luabind::error e) { _WRN("drawPropertyComponentBackground "+_STR(e.what())); } }
		static void def_drawPropertyComponentBackground(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawPropertyComponentBackground (*p.g, p.width, p.height, *p.propertyComponent); }

		void drawPropertyComponentLabel (ParamWrapper &p)
		{ try { call<void>("drawPropertyComponentLabel", p); } catch (luabind::error e) { _WRN("drawPropertyComponentLabel "+_STR(e.what())); } }
		static void def_drawPropertyComponentLabel(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawPropertyComponentLabel (*p.g, p.width, p.height, *p.propertyComponent); }

		Rectangle<int> getPropertyComponentContentPosition (ParamWrapper &p)
		{ try { return (call<Rectangle<int>>("getPropertyComponentContentPosition", p)); } catch (luabind::error e) { _WRN("getPropertyComponentContentPosition "+_STR(e.what())); } }
		static Rectangle<int> def_getPropertyComponentContentPosition(LookAndFeelBase *ptr, ParamWrapper &p)
		{ return (ptr->LookAndFeelBase::v3.getPropertyComponentContentPosition (*p.propertyComponent)); }

		void drawCallOutBoxBackground (ParamWrapper &p)
		{ try { call<void>("drawCallOutBoxBackground", p); } catch (luabind::error e) { _WRN("drawCallOutBoxBackground "+_STR(e.what())); } }
		static void def_drawCallOutBoxBackground(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawCallOutBoxBackground (*p.callOutBox, *p.g, *p.p, *p.image); }

		void drawLevelMeter (ParamWrapper &p)
		{ try { call<void>("drawLevelMeter", p); } catch (luabind::error e) { _WRN("drawLevelMeter "+_STR(e.what())); } }
		static void def_drawLevelMeter(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawLevelMeter (*p.g, p.width, p.height, p.level); }

		void drawKeymapChangeButton (ParamWrapper &p)
		{ try { call<void>("drawKeymapChangeButton", p); } catch (luabind::error e) { _WRN("drawKeymapChangeButton "+_STR(e.what())); } }
		static void def_drawKeymapChangeButton(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.drawKeymapChangeButton (*p.g, p.width, p.height, *p.button, p.keyDescription); }

		void playAlertSound (ParamWrapper &p)
		{ try { call<void>("playAlertSound", p); } catch (luabind::error e) { _WRN("playAlertSound "+_STR(e.what())); } }
		static void def_playAlertSound(LookAndFeelBase *ptr, ParamWrapper &p)
		{ ptr->LookAndFeelBase::v3.playAlertSound (); }

};

#endif
