#include "stdafx.h"
#include "LButton.h"

void LButton::wrapForLua (lua_State *L)
{
    using namespace luabind;

	module(L)
    [
        class_<SettableTooltipClient>("SettableTooltipClient")
        ,
		class_<Button, bases<Component, SettableTooltipClient> >("Button")
            .def("setButtonText", &Button::setButtonText)
            .def("getButtonText", &Button::getButtonText)
            .def("isDown", &Button::isDown)
            .def("isOver", &Button::isOver)
            .def("setToggleState", (void (Button::*)(bool, NotificationType))&Button::setToggleState)
            .def("setToggleState", (void (Button::*)(bool, bool))&Button::setToggleState)
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
