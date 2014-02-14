#include "stdafx.h"
#include "LComboBox.h"

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
