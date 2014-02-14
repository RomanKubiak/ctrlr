#include "stdafx.h"
#include "LBubbleMessageComponent.h"
#include "LComponent.h"

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