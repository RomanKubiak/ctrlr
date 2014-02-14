#include "stdafx.h"
#include "LLabel.h"

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
			.def("getHorizontalBorderSize", &Label::getHorizontalBorderSize)
			.def("getVerticalBorderSize", &Label::getVerticalBorderSize)
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
