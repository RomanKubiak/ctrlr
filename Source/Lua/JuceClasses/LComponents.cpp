#include "stdafx.h"
#include "stdafx_luabind.h"
#include "LJuce.h"
#include "CtrlrLog.h"

LAlertWindow::LAlertWindow(const String &title, const String &message, AlertIconType iconType)
	: AlertWindow(title,message,iconType,nullptr)
{
}

LAlertWindow::~LAlertWindow()
{
}

void LAlertWindow::showMessageBox (AlertIconType iconType, const String& title, const String& message, const String& buttonText)
{
	AlertWindow::showMessageBox (iconType, title, message, buttonText, nullptr);
}

void LAlertWindow::showMessageBoxAsync (AlertIconType iconType, const String& title, const String& message, const String& buttonText)
{
	AlertWindow::showMessageBoxAsync (iconType, title, message, buttonText, nullptr);
}

bool LAlertWindow::showOkCancelBox (AlertIconType iconType, const String& title, const String& message, const String& button1Text, const String& button2Text)
{
	return (AlertWindow::showOkCancelBox (iconType, title, message, button1Text, button2Text, nullptr, nullptr));
}

int LAlertWindow::showYesNoCancelBox (AlertIconType iconType, const String& title, const String& message, const String& button1Text, const String& button2Text, const String& button3Text)
{
	return (AlertWindow::showYesNoCancelBox (iconType, title, message, button1Text, button2Text, button3Text, nullptr, nullptr));
}

bool LAlertWindow::showNativeDialogBox (const String& title, const String& bodyText, bool isOkCancel)
{
	return (AlertWindow::showNativeDialogBox (title, bodyText, isOkCancel));
}

void LAlertWindow::queryText(AlertIconType iconType, const String &title, const String &textMessage, const String &textAreaContent, const String &textAreaLabel, const String &button1Text, const String &button2Text, bool isContentPassword, luabind::object const &result)
{
	AlertWindow w(title, textMessage, iconType, 0);
	w.addTextEditor ("userInput", textAreaContent,  textAreaLabel, isContentPassword);
	w.addButton (button1Text, 1);
	w.addButton (button2Text, 0);
	result[1] = w.runModalLoop();
	result[2] = w.getTextEditorContents("userInput");
}

ComboBox *LAlertWindow::getComboBoxComponent(const String &comboName)
{
	ComboBox *box = AlertWindow::getComboBoxComponent (comboName);
	return (box);
}

int LAlertWindow::runModalLoop()
{
	const int ret = AlertWindow::runModalLoop();

	if (o.is_valid())
	{
		luabind::call_function<void> (o, ret, this);
	}

	return (ret);
}

void LAlertWindow::setModalHandler(luabind::object const& _o)
{
	o = _o;
}

void LAlertWindow::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<AlertWindow>("JAlertWindow"),
		class_<LAlertWindow, bases<AlertWindow, Component> >("AlertWindow")
            .def(constructor<const String &, const String &, AlertIconType>())
			.def("getAlertType", &AlertWindow::getAlertType)
			.def("setMessage", &AlertWindow::setMessage)
			.def("addButton", &AlertWindow::addButton)
			.def("getNumButtons", &AlertWindow::getNumButtons)
			.def("triggerButtonClick", &AlertWindow::triggerButtonClick)
			.def("setEscapeKeyCancels", &AlertWindow::setEscapeKeyCancels)
			.def("addTextEditor", &AlertWindow::addTextEditor)
			.def("getTextEditorContents", &AlertWindow::getTextEditorContents)
			.def("getTextEditor", &AlertWindow::getTextEditor)
			.def("addComboBox", &AlertWindow::addComboBox)
			.def("getComboBoxComponent", &LAlertWindow::getComboBoxComponent)
			.def("addTextBlock", &AlertWindow::addTextBlock)
			.def("addProgressBarComponent", &AlertWindow::addProgressBarComponent)
			.def("addCustomComponent", &AlertWindow::addCustomComponent)
			.def("getNumCustomComponents", &AlertWindow::getNumCustomComponents)
			.def("getCustomComponent", &AlertWindow::getCustomComponent)
			.def("removeCustomComponent", &AlertWindow::removeCustomComponent)
			.def("containsAnyExtraComponents", &AlertWindow::containsAnyExtraComponents)
			.def("setModalHandler", &LAlertWindow::setModalHandler)
			.def("runModalLoop", &LAlertWindow::runModalLoop)
			.def("exitModalState", &Component::exitModalState)
            .enum_("AlertIconType")
            [
                value("NoIcon", 0),
                value("QuestionIcon", 1),
                value("WarningIcon", 2),
                value("InfoIcon", 3)
            ]
			.scope
			[
				def("showMessageBox", &LAlertWindow::showMessageBox),
				def("showMessageBoxAsync", &LAlertWindow::showMessageBoxAsync),
				def("showOkCancelBox", &LAlertWindow::showOkCancelBox),
				def("showYesNoCancelBox", &LAlertWindow::showYesNoCancelBox),
				def("showNativeDialogBox", &LAlertWindow::showNativeDialogBox),
				def("queryText", &LAlertWindow::queryText)
             ]
	];
}

LBubbleMessageComponent::LBubbleMessageComponent(int fadeOutLengthMs) : BubbleMessageComponent(fadeOutLengthMs)
{
}

void LBubbleMessageComponent::showAt (Component *component, const String &message, int numMillisecondsBeforeRemoving, bool removeWhenMouseClicked, bool deleteSelfAfterUse)
{
	addToDesktop (0, nullptr);
	BubbleMessageComponent::showAt (component, AttributedString(message), numMillisecondsBeforeRemoving, removeWhenMouseClicked, deleteSelfAfterUse);
}

void LBubbleMessageComponent::showAt (Component *component, const AttributedString &message, int numMillisecondsBeforeRemoving, bool removeWhenMouseClicked, bool deleteSelfAfterUse)
{
	addToDesktop (0, nullptr);
	BubbleMessageComponent::showAt (component, AttributedString(message), numMillisecondsBeforeRemoving, removeWhenMouseClicked, deleteSelfAfterUse);
}

void LBubbleMessageComponent::showAt (const Rectangle<int> &rectangle, const AttributedString &message, int numMillisecondsBeforeRemoving, bool removeWhenMouseClicked, bool deleteSelfAfterUse)
{
	addToDesktop (0, nullptr);
	BubbleMessageComponent::showAt (rectangle, message, numMillisecondsBeforeRemoving, removeWhenMouseClicked, deleteSelfAfterUse);
}

void LBubbleMessageComponent::showAt (const Rectangle<int> &rectangle, const String &message, int numMillisecondsBeforeRemoving, bool removeWhenMouseClicked, bool deleteSelfAfterUse)
{
	addToDesktop (0, nullptr);
	BubbleMessageComponent::showAt (rectangle, AttributedString(message), numMillisecondsBeforeRemoving, removeWhenMouseClicked, deleteSelfAfterUse);
}

void LBubbleMessageComponent::getContentSize (int &w, int &h)
{
	BubbleMessageComponent::getContentSize(w,h);
}

void LBubbleMessageComponent::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<LBubbleMessageComponent, bases<Component> >("BubbleMessageComponent")
			.def(constructor<int>())
			.def("showAt", (void (LBubbleMessageComponent::*)(const Rectangle<int> &, const AttributedString &, int, bool, bool)) &LBubbleMessageComponent::showAt)
			.def("showAt", (void (LBubbleMessageComponent::*)(const Rectangle<int> &, const String &, int, bool, bool)) &LBubbleMessageComponent::showAt)
			.def("showAt", (void (LBubbleMessageComponent::*)(Component *, const AttributedString &, int, bool, bool)) &LBubbleMessageComponent::showAt)
			.def("showAt", (void (LBubbleMessageComponent::*)(Component *, const String &, int, bool, bool)) &LBubbleMessageComponent::showAt)
			.def("getContentSize", &LBubbleMessageComponent::getContentSize)
	];
}

void LButton::wrapForLua (lua_State *L)
{
    using namespace luabind;

	module(L)
    [
        class_<SettableTooltipClient>("SettableTooltipClient"),
        class_<Button::ButtonState>("ButtonState"),
		class_<Button, bases<Component, SettableTooltipClient> >("Button")
            .def("setButtonText", &Button::setButtonText)
            .def("getButtonText", &Button::getButtonText)
            .def("isDown", &Button::isDown)
            .def("isOver", &Button::isOver)
            .def("setToggleState", (void (Button::*)(bool, NotificationType))&Button::setToggleState)
            //.def("setToggleState", (void (Button::*)(bool, bool))&Button::setToggleState)
            .def("getToggleState", &Button::getToggleState)
            .def("getToggleStateValue", &Button::getToggleStateValue)
            .def("setClickingTogglesState", &Button::setClickingTogglesState)
            .def("getClickingTogglesState", &Button::getClickingTogglesState)
            .def("setRadioGroupId", &Button::setRadioGroupId)
            .def("getRadioGroupId", &Button::getRadioGroupId)
            .def("addListener", &Button::addListener)
            .def("removeListener", &Button::removeListener)
            .def("triggerClick", &Button::triggerClick)
            .def("setCommandToTrigger", &Button::setCommandToTrigger)
            .def("getCommandID", &Button::getCommandID)
            .def("addShortcut", &Button::addShortcut)
            .def("clearShortcuts", &Button::clearShortcuts)
            .def("isRegisteredForShortcut", &Button::isRegisteredForShortcut)
            .def("setRepeatSpeed", &Button::setRepeatSpeed)
            .def("setTriggeredOnMouseDown", &Button::setTriggeredOnMouseDown)
            .def("getMillisecondsSinceButtonDown", &Button::getMillisecondsSinceButtonDown)
            .def("setTooltip", &Button::setTooltip)
            .def("getTooltip", &Button::getTooltip)
            .def("setConnectedEdges", &Button::setConnectedEdges)
            .def("getConnectedEdgeFlags", &Button::getConnectedEdgeFlags)
            .def("isConnectedOnLeft", &Button::isConnectedOnLeft)
            .def("isConnectedOnRight", &Button::isConnectedOnRight)
            .def("isConnectedOnTop", &Button::isConnectedOnTop)
            .def("isConnectedOnBottom", &Button::isConnectedOnBottom)
            .def("setState", &Button::setState)
    ];
}

void LComboBox::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<ComboBox, bases<Component> >("ComboBox")
			.def(constructor<>())
			.def(constructor<const String &>())
			.def("setEditableText", &ComboBox::setEditableText)
			.def("isTextEditable", &ComboBox::isTextEditable)
			.def("setJustificationType", &ComboBox::setJustificationType)
			.def("getJustificationType", &ComboBox::getJustificationType)
			.def("addItem", &ComboBox::addItem)
			.def("addItemList", &ComboBox::addItemList)
			.def("addSeparator", &ComboBox::addSeparator)
			.def("addSectionHeading", &ComboBox::addSectionHeading)
			.def("setItemEnabled", &ComboBox::setItemEnabled)
			.def("isItemEnabled", &ComboBox::isItemEnabled)
			.def("changeItemText", &ComboBox::changeItemText)
			.def("clear", (void (ComboBox::*)(NotificationType))&ComboBox::clear)
			.def("getNumItems", &ComboBox::getNumItems)
			.def("getItemText", &ComboBox::getItemText)
			.def("getItemId", &ComboBox::getItemId)
			.def("indexOfItemId", &ComboBox::indexOfItemId)
			.def("getSelectedId", &ComboBox::getSelectedId)
			.def("getSelectedIdAsValue", &ComboBox::getSelectedIdAsValue)
			.def("setSelectedId", (void (ComboBox::*)(int, NotificationType))&ComboBox::setSelectedId)
			.def("getSelectedItemIndex", &ComboBox::getSelectedItemIndex)
			.def("setSelectedItemIndex", (void (ComboBox::*)(int, NotificationType))&ComboBox::setSelectedItemIndex)
			.def("getText", &ComboBox::getText)
			.def("setText", (void (ComboBox::*)(const String &, NotificationType))&ComboBox::setText)
			.def("showEditor", &ComboBox::showEditor)
			.def("showPopup", &ComboBox::showPopup)
			.def("addListener", &ComboBox::addListener)
			.def("removeListener", &ComboBox::removeListener)
			.def("setTextWhenNothingSelected", &ComboBox::setTextWhenNothingSelected)
			.def("getTextWhenNothingSelected", &ComboBox::getTextWhenNothingSelected)
			.def("setTextWhenNoChoicesAvailable", &ComboBox::setTextWhenNoChoicesAvailable)
			.def("setTooltip", &ComboBox::setTooltip)
	];
}

void LComponent::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
        class_<DropShadow>("DropShadow")
            .def(constructor<>())
            .def(constructor<Colour, int, Point<int> >())
            .def("drawForImage", &DropShadow::drawForImage)
            .def("drawForPath", &DropShadow::drawForPath)
            .def("drawForRectangle", &DropShadow::drawForRectangle)
        ,
        class_<DropShadower>("DropShadower")
            .def(constructor<const DropShadow &>())
            .def("setOwner", &DropShadower::setOwner)
        ,
		class_<LComponent>("LComponent")
		,
		class_<Component, LComponent>("Component")
			.def(constructor<>())
			.def(constructor<const String &>())
			.def("setName", &Component::setName)
			.def("getComponentID", &Component::getComponentID)
			.def("setComponentID", &Component::setComponentID)
			.def("setVisible", &Component::setVisible)
			.def("isVisible", &Component::isVisible)
			.def("visibilityChanged", &Component::visibilityChanged)
			.def("isShowing", &Component::isShowing)
			.def("addToDesktop", &LComponent::addToDesktop)
			.def("removeFromDesktop", &Component::removeFromDesktop)
			.def("isOnDesktop", &Component::isOnDesktop)
			.def("getPeer", &Component::getPeer)
			.def("userTriedToCloseWindow", &Component::userTriedToCloseWindow)
			.def("minimisationStateChanged", &Component::minimisationStateChanged)
			.def("toFront", &Component::toFront)
			.def("toBack", &Component::toBack)
			.def("toBehind", &Component::toBehind)
			.def("setAlwaysOnTop", &Component::setAlwaysOnTop)
			.def("isAlwaysOnTop", &Component::isAlwaysOnTop)
			.def("getX", &Component::getX)
			.def("getY", &Component::getY)
			.def("getWidth", &Component::getWidth)
			.def("getHeight", &Component::getHeight)
			.def("getRight", &Component::getRight)
			.def("getPosition", &Component::getPosition)
			.def("getBottom", &Component::getBottom)
			.def("getBounds", &Component::getBounds)
			.def("getLocalBounds", &Component::getLocalBounds)
			.def("getBoundsInParent", &Component::getBoundsInParent)
			.def("getScreenX", &Component::getScreenX)
			.def("getScreenY", &Component::getScreenY)
			.def("getScreenPosition", &Component::getScreenPosition)
			.def("getScreenBounds", &Component::getScreenBounds)
			.def("getLocalPoint", (Point<int> (Component::*)(const Component *, Point<int>) const) &Component::getLocalPoint)
			//.def("getLocalArea", &Component::getLocalArea)
			.def("localPointToGlobal", (Point<int> (Component::*)(Point<int>) const) &Component::localPointToGlobal)
			//.def("localAreaToGlobal", &Component::localAreaToGlobal)
			.def("setTopLeftPosition", (void (Component::*)(int,int))&Component::setTopLeftPosition)
			.def("setTopLeftPosition", (void (Component::*)(const Point<int>))&Component::setTopLeftPosition)
			.def("setTopRightPosition", &Component::setTopRightPosition)
			.def("setSize", &Component::setSize)
			.def("setBounds", (void (Component::*)(int,int,int,int))&Component::setBounds)
			.def("setBounds", (void (Component::*)(const Rectangle<int>))&Component::setBounds)
			//.def("setBounds", (void (Component::*)(const RelativeRectangle &))&Component::setBounds)
			//.def("setBounds", (void (Component::*)(const String &))&Component::setBounds)
			.def("setBoundsRelative", (void (Component::*)(const Rectangle<float>))&Component::setBoundsRelative)
			.def("setBoundsRelative", (void (Component::*)(float, float, float, float))&Component::setBoundsRelative)
			.def("setBoundsInset", &Component::setBoundsInset)
			.def("setBoundsToFit", &Component::setBoundsToFit)
			//.def("setCentrePosition", &Component::setCentrePosition)
			.def("setCentreRelative", &Component::setCentreRelative)
			.def("centreWithSize", &Component::centreWithSize)
			.def("setTransform", &Component::setTransform)
			.def("getTransform", &Component::getTransform)
			.def("isTransformed", &Component::isTransformed)
			.def("proportionOfWidth", &Component::proportionOfWidth)
			.def("proportionOfHeight", &Component::proportionOfHeight)
			.def("getParentWidth", &Component::getParentWidth)
			.def("getParentHeight", &Component::getParentHeight)
			.def("getParentMonitorArea", &Component::getParentMonitorArea)
			.def("getNumChildComponents", &Component::getNumChildComponents)
			.def("getChildComponent", &Component::getChildComponent)
			.def("getIndexOfChildComponent", &Component::getIndexOfChildComponent)
			.def("findChildWithID", &Component::findChildWithID)
			.def("addChildComponent", (void (Component::*)(Component *, int))&Component::addChildComponent)
			.def("addChildComponent", (void (Component::*)(Component &, int))&Component::addChildComponent)
			.def("addAndMakeVisible", (void (Component::*)(Component *, int))&Component::addAndMakeVisible)
			.def("addAndMakeVisible", (void (Component::*)(Component &, int))&Component::addAndMakeVisible)
			.def("addChildAndSetID", &Component::addChildAndSetID)
			.def("removeChildComponent", (void (Component::*)(Component *))&Component::removeChildComponent)
			.def("removeChildComponent", (Component *(Component::*)(int))&Component::removeChildComponent)
			.def("removeAllChildren", &Component::removeAllChildren)
			.def("deleteAllChildren", &Component::deleteAllChildren)
			.def("getParentComponent", &Component::getParentComponent)
			.def("getTopLevelComponent", &Component::getTopLevelComponent)
			.def("isParentOf", &Component::isParentOf)
			.def("parentHierarchyChanged", &Component::parentHierarchyChanged)
			.def("childrenChanged", &Component::childrenChanged)
			.def("hitTest", &Component::hitTest)
			.def("setInterceptsMouseClicks", &Component::setInterceptsMouseClicks)
			.def("getInterceptsMouseClicks", &Component::getInterceptsMouseClicks)
			.def("contains", (bool (Component::*)(const Point<int>))&Component::contains)
			.def("reallyContains", &Component::reallyContains)
			.def("getComponentAt", (Component *(Component::*)(int,int))&Component::getComponentAt)
			.def("getComponentAt", (Component *(Component::*)(const Point<int>))&Component::getComponentAt)
			.def("repaint", (void (Component::*)(void))&Component::repaint)
			.def("repaint", (void (Component::*)(int,int,int,int))&Component::repaint)
			//.def("repaint", (void (Component::*)(const Rectangle<int> &))&Component::repaint)
			.def("setBufferedToImage", &Component::setBufferedToImage)
			.def("createComponentSnapshot", &Component::createComponentSnapshot)
			.def("paintEntireComponent", &Component::paintEntireComponent)
			.def("setPaintingIsUnclipped", &Component::setPaintingIsUnclipped)
			.def("setComponentEffect", &Component::setComponentEffect)
			.def("getComponentEffect", &Component::getComponentEffect)
			.def("getLookAndFeel", &Component::getLookAndFeel)
			.def("setLookAndFeel", &Component::setLookAndFeel)
			.def("lookAndFeelChanged", &Component::lookAndFeelChanged)
			.def("sendLookAndFeelChange", &Component::sendLookAndFeelChange)
			.def("setOpaque", &Component::setOpaque)
			.def("isOpaque", &Component::isOpaque)
			.def("setBroughtToFrontOnMouseClick", &Component::setBroughtToFrontOnMouseClick)
			.def("isBroughtToFrontOnMouseClick", &Component::isBroughtToFrontOnMouseClick)
			.def("setWantsKeyboardFocus", &Component::setWantsKeyboardFocus)
			.def("getWantsKeyboardFocus", &Component::getWantsKeyboardFocus)
			.def("setMouseClickGrabsKeyboardFocus", &Component::setMouseClickGrabsKeyboardFocus)
			.def("getMouseClickGrabsKeyboardFocus", &Component::getMouseClickGrabsKeyboardFocus)
			.def("grabKeyboardFocus", &Component::grabKeyboardFocus)
			.def("hasKeyboardFocus", &Component::hasKeyboardFocus)
			.def("moveKeyboardFocusToSibling", &Component::moveKeyboardFocusToSibling)
			.def("createFocusTraverser", &Component::createFocusTraverser)
			.def("getExplicitFocusOrder", &Component::getExplicitFocusOrder)
			.def("setExplicitFocusOrder", &Component::setExplicitFocusOrder)
			.def("setFocusContainer", &Component::setFocusContainer)
			.def("isFocusContainer", &Component::isFocusContainer)
			.def("isEnabled", &Component::isEnabled)
			.def("setEnabled", &Component::setEnabled)
			.def("enablementChanged", &Component::enablementChanged)
			.def("setAlpha", &Component::setAlpha)
			.def("getAlpha", &Component::getAlpha)
			.def("setMouseCursor", &Component::setMouseCursor)
			.def("getMouseCursor", &Component::getMouseCursor)
			.def("updateMouseCursor", &Component::updateMouseCursor)
			.def("paint", &Component::paint)
			.def("paintOverChildren", &Component::paintOverChildren)
			.def("mouseMove", &Component::mouseMove)
			.def("mouseEnter", &Component::mouseEnter)
			.def("mouseExit", &Component::mouseExit)
			.def("mouseDown", &Component::mouseDown)
			.def("mouseDrag", &Component::mouseDrag)
			.def("mouseUp", &Component::mouseUp)
			.def("mouseDoubleClick", &Component::mouseDoubleClick)
			.def("mouseWheelMove", &Component::mouseWheelMove)
			.def("setRepaintsOnMouseActivity", &Component::setRepaintsOnMouseActivity)
			.def("addMouseListener", &Component::addMouseListener)
			.def("removeMouseListener", &Component::removeMouseListener)
			.def("addKeyListener", &Component::addKeyListener)
			.def("removeKeyListener", &Component::removeKeyListener)
			.def("keyPressed", &Component::keyPressed)
			.def("keyStateChanged", &Component::keyStateChanged)
			.def("modifierKeysChanged", &Component::modifierKeysChanged)
			.def("focusGained", &Component::focusGained)
			.def("focusLost", &Component::focusLost)
			.def("focusOfChildComponentChanged", &Component::focusOfChildComponentChanged)
			.def("isMouseOver", &Component::isMouseOver)
			.def("isMouseButtonDown", &Component::isMouseButtonDown)
			.def("isMouseOverOrDragging", &Component::isMouseOverOrDragging)
			.def("getMouseXYRelative", &Component::getMouseXYRelative)
			.def("resized", &Component::resized)
			.def("moved", &Component::moved)
			.def("childBoundsChanged", &Component::childBoundsChanged)
			.def("parentSizeChanged", &Component::parentSizeChanged)
			.def("broughtToFront", &Component::broughtToFront)
			.def("addComponentListener", &Component::addComponentListener)
			.def("removeComponentListener", &Component::removeComponentListener)
			.def("postCommandMessage", &Component::postCommandMessage)
			.def("handleCommandMessage", &Component::handleCommandMessage)
			.def("enterModalState", &Component::enterModalState)
			.def("exitModalState", &Component::exitModalState)
			.def("isCurrentlyModal", &Component::isCurrentlyModal)
			.def("isCurrentlyBlockedByAnotherModalComponent", &Component::isCurrentlyBlockedByAnotherModalComponent)
			.def("canModalEventBeSentToComponent", &Component::canModalEventBeSentToComponent)
			.def("inputAttemptWhenModal", &Component::inputAttemptWhenModal)
			.def("getProperties", (NamedValueSet &(Component::*)() noexcept)&Component::getProperties)
			.def("getProperties", (const NamedValueSet &(Component::*)() const noexcept)&Component::getProperties)
			.def("findColour", &Component::findColour)
			.def("setColour", &Component::setColour)
			.def("removeColour", &Component::removeColour)
			.def("isColourSpecified", &Component::isColourSpecified)
			.def("copyAllExplicitColoursTo", &Component::copyAllExplicitColoursTo)
			.def("colourChanged", &Component::colourChanged)
			//.def("getMarkers", &Component::getMarkers) removed from JUCE
			.def("getWindowHandle", &Component::getWindowHandle)
			.def("getPositioner", &Component::getPositioner)
			.def("setPositioner", &Component::setPositioner)
			.def("setCachedComponentImage", &Component::setCachedComponentImage)
			.def("getCachedComponentImage", &Component::getCachedComponentImage)
			.scope
			[
				def("getCurrentlyFocusedComponent", &LComponent::getCurrentlyFocusedComponent),
				def("beginDragAutoRepeat", &LComponent::beginDragAutoRepeat),
				def("isMouseButtonDownAnywhere", &LComponent::isMouseButtonDownAnywhere),
				def("getNumCurrentlyModalComponents", &LComponent::getNumCurrentlyModalComponents),
				def("getCurrentlyModalComponent", &LComponent::getCurrentlyModalComponent)
			]
	];
}

void LComponentPeer::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<ComponentPeer>("ComponentPeer")
			.enum_("StyleFlags")
			[
				value("windowAppearsOnTaskbar", (1 << 0)),
				value("windowIsTemporary", (1 << 1)),
				value("windowIgnoresMouseClicks", (1 << 2)),
				value("windowHasTitleBar", (1 << 3)),
				value("windowIsResizable", (1 << 4)),
				value("windowHasMinimiseButton", (1 << 5)),
				value("windowHasMaximiseButton", (1 << 6)),
				value("windowHasCloseButton", (1 << 7)),
				value("windowHasDropShadow", (1 << 8)),
				value("windowRepaintedExplictly", (1 << 9)),
				value("windowIgnoresKeyPresses", (1 << 10)),
				value("windowIsSemiTransparent", (1 << 31))
			]
	];
}

void LFileListComponent::wrapForLua (lua_State *)
{
	using namespace luabind;
}

void LFileTreeComponent::wrapForLua (lua_State *)
{
	using namespace luabind;
}

void LLabel::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Label, bases<Component> >("Label")
			.def("setText", (void (Label::*)(const String &, NotificationType))&Label::setText)
			.def("getText", &Label::getText)
			.def("getTextValue", &Label::getTextValue)
			.def("setFont", &Label::setFont)
			.def("getFont", &Label::getFont)
			.def("setJustificationType", &Label::setJustificationType)
			.def("getJustificationType", &Label::getJustificationType)
			.def("setBorderSize", &Label::setBorderSize)
			.def("attachToComponent", &Label::attachToComponent)
			.def("getAttachedComponent", &Label::getAttachedComponent)
			.def("isAttachedOnLeft", &Label::isAttachedOnLeft)
			.def("setMinimumHorizontalScale", &Label::setMinimumHorizontalScale)
			.def("getMinimumHorizontalScale", &Label::getMinimumHorizontalScale)
			.def("addListener", &Label::addListener)
			.def("removeListener", &Label::removeListener)
			.def("setEditable", &Label::setEditable)
			.def("isEditableOnSingleClick", &Label::isEditableOnSingleClick)
			.def("isEditableOnDoubleClick", &Label::isEditableOnDoubleClick)
			.def("doesLossOfFocusDiscardChanges", &Label::doesLossOfFocusDiscardChanges)
			.def("isEditable", &Label::isEditable)
			.def("showEditor", &Label::showEditor)
			.def("hideEditor", &Label::hideEditor)
			.def("isBeingEdited", &Label::isBeingEdited)
			.enum_("ColourIds")
			[
				value("backgroundColourId ", 0x1000280),
				value("textColourId", 0x1000281),
				value("outlineColourId", 0x1000282)
			]
	];
}

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
   LookAndFeel_V2::method(__VA_ARGS__);\
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
   return (LookAndFeel_V2::method(__VA_ARGS__));\
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
   return (LookAndFeel_V2::method());\
}

LookAndFeelBase::LookAndFeelBase()
{
}

void LookAndFeelBase::setMethod (const String &methodName, const luabind::object &method)
{
    if (luabind::type(method) != LUA_TNIL)
    {
        methods.set (methodName, method);
    }
    else
    {
        methods.remove(methodName);
    }
}

void LookAndFeelBase::setImplementation (const luabind::object &implementationAsTable)
{
    if (luabind::type(implementationAsTable) == LUA_TTABLE)
    {
        for (luabind::iterator i(implementationAsTable), end; i!=end; ++i)
        {
            String key          = luabind::object_cast<std::string>(i.key());
            luabind::object val = *i;

            if (luabind::type(val) == LUA_TFUNCTION)
            {
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

            return (LookAndFeel_V2::createAlertWindow(title, message, button1, button2, button3, iconType, numButtons, component));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V2::createAlertWindow(title, message, button1, button2, button3, iconType, numButtons, component));
        }
    }
    else
    {
        return (LookAndFeel_V2::createAlertWindow(title, message, button1, button2, button3, iconType, numButtons, component));
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

            return (LookAndFeel_V2::getScrollbarEffect());
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V2::getScrollbarEffect());
        }
    }
    else
    {
        return (LookAndFeel_V2::getScrollbarEffect());
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

            return (LookAndFeel_V2::getDefaultFolderImage());
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V2::getDefaultFolderImage());
        }
    }
    else
    {
        return (LookAndFeel_V2::getDefaultFolderImage());
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

            return (LookAndFeel_V2::getDefaultDocumentFileImage());
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V2::getDefaultDocumentFileImage());
        }
    }
    else
    {
        return (LookAndFeel_V2::getDefaultDocumentFileImage());
    }
}

AttributedString LookAndFeelBase::createFileChooserHeaderText(const String &title, const String &instructions)
{
	TRY_CALL_RET(createFileChooserHeaderText, AttributedString, AttributedString(title+instructions), title, instructions);
}

/*
void LookAndFeelBase::drawFileBrowserRow(Graphics &g, int width, int height, const String &filename, Image* icon, const String &fileSizeDescription, const String &fileTimeDescription, bool isDirectory, bool isItemSelected, int itemIndex, DirectoryContentsDisplayComponent &directoryContentsDisplayComponent)
{
	TRY_CALL(drawFileBrowserRow, boost::ref(g), width, height, filename, icon, fileSizeDescription, fileTimeDescription, isDirectory, isItemSelected, itemIndex, boost::ref(directoryContentsDisplayComponent));
}
*/

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

            return (LookAndFeel_V2::createFileBrowserGoUpButton());
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V2::createFileBrowserGoUpButton());
        }
    }
    else
    {
        return (LookAndFeel_V2::createFileBrowserGoUpButton());
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

/*
void LookAndFeelBase::drawPopupMenuItem(Graphics &g, const Rectangle<int> &area, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const String &text, const String &shortcutKeyText, const Drawable* icon, const Colour *textColour)
{
	TRY_CALL(drawPopupMenuItem, boost::ref(g),boost::ref(area),isSeparator,isActive,isHighlighted,isTicked,hasSubMenu,text,shortcutKeyText,icon,textColour);
}
*/

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

            return (LookAndFeel_V2::createComboBoxTextBox(comboBox));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V2::createComboBoxTextBox(comboBox));
        }
    }
    else
    {
        return (LookAndFeel_V2::createComboBoxTextBox(comboBox));
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

            return (LookAndFeel_V2::createSliderButton(slider, isIncrement));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V2::createSliderButton(slider, isIncrement));
        }
    }
    else
    {
        return (LookAndFeel_V2::createSliderButton(slider, isIncrement));
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

            return (LookAndFeel_V2::createSliderTextBox(slider));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V2::createSliderTextBox(slider));
        }
    }
    else
    {
        return (LookAndFeel_V2::createSliderTextBox(slider));
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

            return (LookAndFeel_V2::getSliderEffect(slider));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V2::getSliderEffect(slider));
        }
    }
    else
    {
        return (LookAndFeel_V2::getSliderEffect(slider));
    }
}

Rectangle<int> LookAndFeelBase::getTooltipBounds(const String &tipText, Point<int> screenPos, Rectangle<int> parentArea)
{
    TRY_CALL_RET(getTooltipBounds, Rectangle<int>, Rectangle<int>(), tipText, screenPos, parentArea);
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

            return (LookAndFeel_V2::createFilenameComponentBrowseButton(text));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V2::createFilenameComponentBrowseButton(text));
        }
    }
    else
    {
        return (LookAndFeel_V2::createFilenameComponentBrowseButton(text));
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

            return (LookAndFeel_V2::createDocumentWindowButton(buttonType));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V2::createDocumentWindowButton(buttonType));
        }
    }
    else
    {
        return (LookAndFeel_V2::createDocumentWindowButton(buttonType));
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

            return (LookAndFeel_V2::createDropShadowerForComponent(component));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V2::createDropShadowerForComponent(component));
        }
    }
    else
    {
        return (LookAndFeel_V2::createDropShadowerForComponent(component));
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

void LookAndFeelBase::fillTabButtonShape(TabBarButton &tabBarButton, Graphics &g, const Path &/*path*/, bool isMouseOver, bool isMouseDown)
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

            return (LookAndFeel_V2::createTabBarExtrasButton());
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V2::createTabBarExtrasButton());
        }
    }
    else
    {
        return (LookAndFeel_V2::createTabBarExtrasButton());
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

void LookAndFeelBase::drawTableHeaderColumn(Graphics &, const String &, int , int , int , bool , bool , int )
{
    //TRY_CALL(drawTableHeaderColumn, boost::ref(g), columnName, columnId, width, height, isMouseOver, isMouseDown, columnFlags);
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

            return (LookAndFeel_V2::createToolbarMissingItemsButton(toolbar));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V2::createToolbarMissingItemsButton(toolbar));
        }
    }
    else
    {
        return (LookAndFeel_V2::createToolbarMissingItemsButton(toolbar));
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

LPopupMenu::LPopupMenu()
{
}

int LPopupMenu::show(int itemIDThatMustBeVisible,
              int minimumWidth,
              int maximumNumColumns,
              int standardItemHeight)
{
	return (PopupMenu::show(itemIDThatMustBeVisible,minimumWidth,maximumNumColumns,standardItemHeight));
}

int LPopupMenu::show(int itemHeight)
{
    return (PopupMenu::show(-1,-1,-1,itemHeight));
}

void LPopupMenu::addSubMenu (const String& subMenuName,
                     const LPopupMenu& subMenu,
                     bool isEnabled,
                     const Image& iconToUse,
                     bool isTicked,
                     int itemResultID)
{
	PopupMenu::addSubMenu (subMenuName, subMenu, isEnabled, iconToUse, isTicked, itemResultID);
}

int LPopupMenu::showAt(Component *componentToAttachTo, int standardItemHeight)
{
    return (PopupMenu::showAt (componentToAttachTo, -1, -1, -1, standardItemHeight, nullptr));
}

int LPopupMenu::showAt(Rectangle<int> &areaToAttachTo, int standardItemHeight)
{
    return (PopupMenu::showAt (areaToAttachTo, -1, -1, -1, standardItemHeight, nullptr));
}

void LPopupMenu::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<PopupMenu>("JPopupMenu")
		,
		class_<LPopupMenu, bases<PopupMenu> >("PopupMenu")
				.def(constructor<>())
				.def("clear", &PopupMenu::clear)
				.def("addItem", (void(PopupMenu::*)(int , String , bool , bool , const Image&))&PopupMenu::addItem)
				//.def("addItem", (void(PopupMenu::*)(int , String , bool , bool , Drawable*))&PopupMenu::addItem)
				.def("addItem", (void(PopupMenu::*)(int , String , bool , bool))&PopupMenu::addItem)
				//.def("addColouredItem", (void(PopupMenu::*)(int, String, Colour, bool, bool, Drawable *))&PopupMenu::addColouredItem)
				.def("addColouredItem", (void(PopupMenu::*)(int, String, Colour, bool, bool, const Image &))&PopupMenu::addColouredItem)
				.def("addSubMenu", &LPopupMenu::addSubMenu)
				.def("addSeparator", &PopupMenu::addSeparator)
				.def("addSectionHeader", &PopupMenu::addSectionHeader)
				.def("getNumItems", &PopupMenu::getNumItems)
				.def("show", (int(PopupMenu::*)(int, int, int, int))&LPopupMenu::show)
				.def("show", (int(LPopupMenu::*)(int))&LPopupMenu::show)
				.def("showAt", (int(LPopupMenu::*)(Component*, int)) &LPopupMenu::showAt)
				.def("showAt", (int(LPopupMenu::*)(Rectangle<int> &, int)) &LPopupMenu::showAt)
	];
}

void LSlider::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
        class_<NotificationType>("NotificationType")
        ,
		class_<Slider, bases<Component> >("Slider")
			.def("setSliderStyle", &Slider::setSliderStyle)
			.def("getSliderStyle", &Slider::getSliderStyle)
			.def("setRotaryParameters", (void(Slider::*)(float, float, bool))&Slider::setRotaryParameters)
			.def("setMouseDragSensitivity", &Slider::setMouseDragSensitivity)
			.def("getMouseDragSensitivity", &Slider::getMouseDragSensitivity)
			.def("setVelocityBasedMode", &Slider::setVelocityBasedMode)
			.def("getVelocityBasedMode", &Slider::getVelocityBasedMode)
			.def("setVelocityModeParameters", &Slider::setVelocityModeParameters)
			.def("getVelocitySensitivity", &Slider::getVelocitySensitivity)
			.def("getVelocityThreshold", &Slider::getVelocityThreshold)
			.def("getVelocityOffset", &Slider::getVelocityOffset)
			.def("getVelocityModeIsSwappable", &Slider::getVelocityModeIsSwappable)
			.def("setSkewFactor", &Slider::setSkewFactor)
			.def("setSkewFactorFromMidPoint", &Slider::setSkewFactorFromMidPoint)
			.def("getSkewFactor", &Slider::getSkewFactor)
			.def("setIncDecButtonsMode", &Slider::setIncDecButtonsMode)
			.def("setTextBoxStyle", &Slider::setTextBoxStyle)
			.def("getTextBoxPosition", &Slider::getTextBoxPosition)
			.def("getTextBoxWidth", &Slider::getTextBoxWidth)
			.def("getTextBoxHeight", &Slider::getTextBoxHeight)
			.def("setTextBoxIsEditable", &Slider::setTextBoxIsEditable)
			.def("isTextBoxEditable", &Slider::isTextBoxEditable)
			.def("showTextBox", &Slider::showTextBox)
			.def("hideTextBox", &Slider::hideTextBox)
			.def("setValue", (void (Slider::*)(double,NotificationType))&Slider::setValue)
			.def("getValue", &Slider::getValue)
			.def("getValueObject", &Slider::getValueObject)
			.def("setRange", (void (Slider::*)(double, double, double))&Slider::setRange)
			.def("getMaximum", &Slider::getMaximum)
			.def("getMinimum", &Slider::getMinimum)
			.def("getInterval", &Slider::getInterval)
			.def("getMinValue", &Slider::getMinValue)
			.def("getMinValueObject", &Slider::getMinValueObject)
			.def("setMinValue", (void (Slider::*)(double,NotificationType,bool))&Slider::setMinValue)
			.def("getMaxValue", &Slider::getMaxValue)
			.def("getMaxValueObject", &Slider::getMaxValueObject)
			.def("setMaxValue", (void (Slider::*)(double,NotificationType,bool))&Slider::setMaxValue)
			.def("setMinAndMaxValues", (void (Slider::*)(double,double,NotificationType))&Slider::setMinAndMaxValues)
			.def("addListener", &Slider::addListener)
			.def("removeListener", &Slider::removeListener)
			.def("setDoubleClickReturnValue", &Slider::setDoubleClickReturnValue)
			.def("getDoubleClickReturnValue", &Slider::getDoubleClickReturnValue)
			.def("setChangeNotificationOnlyOnRelease", &Slider::setChangeNotificationOnlyOnRelease)
			.def("setSliderSnapsToMousePosition", &Slider::setSliderSnapsToMousePosition)
			.def("getSliderSnapsToMousePosition", &Slider::getSliderSnapsToMousePosition)
			.def("setPopupDisplayEnabled", &Slider::setPopupDisplayEnabled)
			.def("getCurrentPopupDisplay", &Slider::getCurrentPopupDisplay)
			.def("setPopupMenuEnabled", &Slider::setPopupMenuEnabled)
			.def("setScrollWheelEnabled", &Slider::setScrollWheelEnabled)
			.def("getThumbBeingDragged", &Slider::getThumbBeingDragged)
			.def("startedDragging", &Slider::startedDragging)
			.def("stoppedDragging", &Slider::stoppedDragging)
			.def("valueChanged", &Slider::valueChanged)
			.def("getValueFromText", &Slider::getValueFromText)
			.def("getTextFromValue", &Slider::getTextFromValue)
			.def("setTextValueSuffix", &Slider::setTextValueSuffix)
			.def("getTextValueSuffix", &Slider::getTextValueSuffix)
			.def("proportionOfLengthToValue", &Slider::proportionOfLengthToValue)
			.def("valueToProportionOfLength", &Slider::valueToProportionOfLength)
			.def("getPositionOfValue", &Slider::getPositionOfValue)
			.def("updateText", &Slider::updateText)
			.def("isHorizontal", &Slider::isHorizontal)
			.def("isVertical", &Slider::isVertical)
			.enum_("TextEntryBoxPosition")
			[
                value("NoTextBox", Slider::NoTextBox),
                value("TextBoxLeft", Slider::TextBoxLeft),
                value("TextBoxRight", Slider::TextBoxRight),
                value("TextBoxAbove", Slider::TextBoxAbove),
                value("TextBoxBelow", Slider::TextBoxBelow)
			]
			.enum_("SliderStyle")
			[
                value("LinearHorizontal", Slider::LinearHorizontal),
                value("LinearVertical", Slider::LinearVertical),
                value("LinearBar", Slider::LinearBar),
                value("LinearBarVertical", Slider::LinearBarVertical),
                value("Rotary", Slider::Rotary),
                value("RotaryHorizontalDrag", Slider::RotaryHorizontalDrag),
                value("RotaryVerticalDrag", Slider::RotaryVerticalDrag),
                value("RotaryHorizontalVerticalDrag", Slider::RotaryHorizontalVerticalDrag),
                value("IncDecButtons", Slider::IncDecButtons),
                value("TwoValueHorizontal", Slider::TwoValueHorizontal),
                value("TwoValueVertical", Slider::TwoValueVertical),
                value("ThreeValueHorizontal", Slider::ThreeValueHorizontal),
                value("ThreeValueVertical", Slider::ThreeValueVertical)
			]
			.enum_("DragMode")
			[
                value("notDragging", Slider::notDragging),
                value("absoluteDrag", Slider::absoluteDrag),
                value("velocityDrag", Slider::velocityDrag)
			]
	];
}

void LTextButton::wrapForLua (lua_State *L)
{
    using namespace luabind;

	module(L)
    [
		class_<TextButton, Button>("TextButton")
            .def(constructor<const String &>())
            .def(constructor<const String &, const String &>())
    ];
}

void LTextEditor::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<TextEditor, bases<Component> >("TextEditor")
			.def(constructor<>())
			.def(constructor<const String &>())
			.def("setMultiLine", &TextEditor::setMultiLine)
			.def("isMultiLine", &TextEditor::isMultiLine)
			.def("setReturnKeyStartsNewLine", &TextEditor::setReturnKeyStartsNewLine)
			.def("getReturnKeyStartsNewLine", &TextEditor::getReturnKeyStartsNewLine)
			.def("setTabKeyUsedAsCharacter", &TextEditor::setTabKeyUsedAsCharacter)
			.def("isTabKeyUsedAsCharacter", &TextEditor::isTabKeyUsedAsCharacter)
			.def("setEscapeAndReturnKeysConsumed", &TextEditor::setEscapeAndReturnKeysConsumed)
			.def("setReadOnly", &TextEditor::setReadOnly)
			.def("isReadOnly", &TextEditor::isReadOnly)
			.def("setCaretVisible", &TextEditor::setCaretVisible)
			.def("isCaretVisible", &TextEditor::isCaretVisible)
			.def("setScrollbarsShown", &TextEditor::setScrollbarsShown)
			.def("areScrollbarsShown", &TextEditor::areScrollbarsShown)
			.def("setPasswordCharacter", &TextEditor::setPasswordCharacter)
			.def("getPasswordCharacter", &TextEditor::getPasswordCharacter)
			.def("setPopupMenuEnabled", &TextEditor::setPopupMenuEnabled)
			.def("isPopupMenuEnabled", &TextEditor::isPopupMenuEnabled)
			.def("isPopupMenuCurrentlyActive", &TextEditor::isPopupMenuCurrentlyActive)
			.def("setFont", &TextEditor::setFont)
			.def("applyFontToAllText", &TextEditor::applyFontToAllText)
			.def("getFont", &TextEditor::getFont)
			.def("setSelectAllWhenFocused", &TextEditor::setSelectAllWhenFocused)
			.def("setTextToShowWhenEmpty", &TextEditor::setTextToShowWhenEmpty)
			.def("setScrollBarThickness", &TextEditor::setScrollBarThickness)
			.def("addListener", &TextEditor::addListener)
			.def("removeListener", &TextEditor::removeListener)
			.def("getText", &TextEditor::getText)
			.def("getTextInRange", &TextEditor::getTextInRange)
			.def("isEmpty", &TextEditor::isEmpty)
			.def("setText", &TextEditor::setText)
			.def("getTextValue", &TextEditor::getTextValue)
			.def("insertTextAtCaret", &TextEditor::insertTextAtCaret)
			.def("clear", &TextEditor::clear)
			.def("cut", &TextEditor::cut)
			.def("copy", &TextEditor::copy)
			.def("paste", &TextEditor::paste)
			.def("getCaretPosition", &TextEditor::getCaretPosition)
			.def("setCaretPosition", &TextEditor::setCaretPosition)
			.def("scrollEditorToPositionCaret", &TextEditor::scrollEditorToPositionCaret)
			.def("getCaretRectangle", &TextEditor::getCaretRectangle)
			.def("setHighlightedRegion", &TextEditor::setHighlightedRegion)
			.def("getHighlightedRegion", &TextEditor::getHighlightedRegion)
			.def("getHighlightedText", &TextEditor::getHighlightedText)
			.def("getTextIndexAt", &TextEditor::getTextIndexAt)
			.def("getTotalNumChars", &TextEditor::getTotalNumChars)
			.def("getTextWidth", &TextEditor::getTextWidth)
			.def("setIndents", &TextEditor::setIndents)
			.def("setBorder", &TextEditor::setBorder)
			.def("getBorder", &TextEditor::getBorder)
			.def("setScrollToShowCursor", &TextEditor::setScrollToShowCursor)
			.def("moveCaretToEnd", (void (TextEditor::*)()) &TextEditor::moveCaretToEnd)
			.def("moveCaretLeft", &TextEditor::moveCaretLeft)
			.def("moveCaretRight", &TextEditor::moveCaretRight)
			.def("moveCaretUp", &TextEditor::moveCaretUp)
			.def("moveCaretDown", &TextEditor::moveCaretDown)
			.def("pageUp", &TextEditor::pageUp)
			.def("pageDown", &TextEditor::pageDown)
			.def("scrollDown", &TextEditor::scrollDown)
			.def("scrollUp", &TextEditor::scrollUp)
			.def("moveCaretToTop", &TextEditor::moveCaretToTop)
			.def("moveCaretToStartOfLine", &TextEditor::moveCaretToStartOfLine)
			.def("moveCaretToEnd", (bool (TextEditor::*)(bool)) &TextEditor::moveCaretToEnd)
			.def("moveCaretToEndOfLine", &TextEditor::moveCaretToEndOfLine)
			.def("deleteBackwards", &TextEditor::deleteBackwards)
			.def("deleteForwards", &TextEditor::deleteForwards)
			.def("copyToClipboard", &TextEditor::copyToClipboard)
			.def("cutToClipboard", &TextEditor::cutToClipboard)
			.def("pasteFromClipboard", &TextEditor::pasteFromClipboard)
			.def("selectAll", &TextEditor::selectAll)
			.def("undo", &TextEditor::undo)
			.def("redo", &TextEditor::redo)
			.def("addPopupMenuItems", &TextEditor::addPopupMenuItems)
			.def("setInputFilter", &TextEditor::setInputFilter)
			.def("setInputRestrictions", &TextEditor::setInputRestrictions)
			.def("redo", &TextEditor::redo)
	];
}

void LToggleButton::wrapForLua (lua_State *L)
{
    using namespace luabind;

	module(L)
    [
		class_<ToggleButton, Button>("ToggleButton")
            .def(constructor<>())
            .def(constructor<const String &>())
            .def("changeWidthToFitText", &ToggleButton::changeWidthToFitText)

    ];
}
