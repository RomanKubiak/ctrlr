#include "stdafx_luabind.h"
#include "CtrlrComponents/Buttons/CtrlrButton.h"
#include "CtrlrComponents/Buttons/CtrlrImageButton.h"
#include "CtrlrComponents/Buttons/CtrlrToggleButton.h"
#include "CtrlrComponents/Sliders/CtrlrSlider.h"
#include "CtrlrComponents/Sliders/CtrlrImageSlider.h"
#include "CtrlrComponents/Sliders/CtrlrFixedImageSlider.h"
#include "CtrlrComponents/Sliders/CtrlrFixedSlider.h"
#include "CtrlrComponents/Specials/CtrlrFileListBox.h"
#include "CtrlrComponents/Specials/CtrlrListBox.h"
#include "CtrlrComponents/Labels/CtrlrLCDLabel.h"
#include "CtrlrComponents/Labels/CtrlrLabel.h"
#include "CtrlrComponents/Groups/CtrlrTabsComponent.h"
#include "CtrlrComponents/Groups/CtrlrGroup.h"
#include "CtrlrComponents/CtrlrCombo.h"

void CtrlrButton::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<CtrlrButton, bases<CtrlrComponent, CtrlrLuaObject> >("CtrlrToggleButton")
			.def("isToggleButton", &CtrlrButton::isToggleButton)
		.def("getToggleState", &CtrlrButton::getToggleState)
		.def("setToggleState", &CtrlrButton::setToggleState)
		.def("getValueMap", &CtrlrButton::getValueMap)
		];
}

void CtrlrImageButton::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<CtrlrImageButton, bases<CtrlrComponent, CtrlrLuaObject> >("CtrlrToggleButton")
			.def("isToggleButton", &CtrlrImageButton::isToggleButton)
		.def("getToggleState", &CtrlrImageButton::getToggleState)
		.def("setToggleState", &CtrlrImageButton::setToggleState)
		.def("getValueMap", &CtrlrImageButton::getValueMap)
		];
}

void CtrlrToggleButton::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<CtrlrToggleButton, bases<CtrlrComponent, CtrlrLuaObject> >("CtrlrToggleButton")
			.def("getToggleState", &CtrlrToggleButton::getToggleState)
		.def("setToggleState", &CtrlrToggleButton::setToggleState)
		.def("getValueMap", &CtrlrToggleButton::getValueMap)
		];
}

void CtrlrSlider::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<CtrlrSlider, bases<CtrlrComponent, CtrlrLuaObject> >("CtrlrSlider")
			.def("getOwnedSlider", &CtrlrSlider::getOwnedSlider)
		];
}

void CtrlrImageSlider::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<CtrlrImageSlider, bases<CtrlrComponent, CtrlrLuaObject> >("CtrlrSlider")
			.def("getOwnedSlider", &CtrlrImageSlider::getOwnedSlider)
		];
}

void CtrlrFixedImageSlider::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<CtrlrFixedImageSlider, bases<CtrlrComponent, CtrlrLuaObject> >("CtrlrSlider")
			.def("getOwnedSlider", &CtrlrFixedImageSlider::getOwnedSlider)
		];
}

void CtrlrFixedSlider::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<CtrlrFixedSlider, bases<CtrlrComponent, CtrlrLuaObject> >("CtrlrSlider")
			.def("getOwnedSlider", &CtrlrFixedSlider::getOwnedSlider)
		.def("getValueMap", &CtrlrFixedSlider::getValueMap)
		];
}

void CtrlrFileListBox::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<CtrlrFileListBox, bases<CtrlrComponent, CtrlrLuaObject> >("CtrlrFileListBox")
			.def("getNumSelectedFiles", &CtrlrFileListBox::getNumSelectedFiles)
		.def("getSelectedFile", &CtrlrFileListBox::getSelectedFile)
		.def("deselectAllFiles", &CtrlrFileListBox::deselectAllFiles)
		.def("scrollToTop", &CtrlrFileListBox::scrollToTop)
		.def("setSelectedFile", &CtrlrFileListBox::setSelectedFile)
		.def("refresh", &CtrlrFileListBox::refresh)
		];
}

void CtrlrListBox::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<CtrlrListBox, bases<CtrlrComponent, CtrlrLuaObject> >("CtrlrListBox")
			.def("getNumRows", &CtrlrListBox::getNumRows)
		.def("updateContent", &CtrlrListBox::updateContent)
		.def("selectRow", &CtrlrListBox::selectRow)
		.def("selectRangeOfRows", &CtrlrListBox::selectRangeOfRows)
		.def("deselectRow", &CtrlrListBox::deselectRow)
		.def("deselectAllRows", &CtrlrListBox::deselectAllRows)
		.def("flipRowSelection", &CtrlrListBox::flipRowSelection)
		.def("getNumSelectedRows", &CtrlrListBox::getNumSelectedRows)
		.def("getSelectedRow", &CtrlrListBox::getSelectedRow)
		.def("getLastRowSelected", &CtrlrListBox::getLastRowSelected)
		.def("isRowSelected", &CtrlrListBox::isRowSelected)
		.def("getSelectedRows", &CtrlrListBox::getSelectedRows)
		.def("setMultipleSelectionEnabled", &CtrlrListBox::setMultipleSelectionEnabled)
		];
}

void CtrlrLCDLabel::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<CtrlrLCDLabel, bases<CtrlrComponent, CtrlrLuaObject> >("CtrlrLCDLabel")
			.def("setText", &CtrlrLCDLabel::setLabelText)
		.def("appendText", &CtrlrLCDLabel::appendText)
		.def("append", &CtrlrLCDLabel::appendText)
		.def("getText", &CtrlrLCDLabel::getText)
		];
}

void CtrlrLabel::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<CtrlrLabel, bases<CtrlrComponent, CtrlrLuaObject> >("CtrlrLabel")
			.def("setText", &CtrlrLabel::setLabelText)
		.def("appendText", &CtrlrLabel::appendText)
		.def("append", &CtrlrLabel::appendText)
		.def("getText", &CtrlrLabel::getText)
		];
}

void CtrlrTabsComponent::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<CtrlrTabsComponent>("CtrlrTabsComponent")
		];
}

void CtrlrGroup::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<GroupComponent>("GroupComponent")
			.def(constructor<const String &, const String &>())
		.def("setText", &GroupComponent::setText)
		.def("getText", &GroupComponent::getText)
		];
}

void CtrlrCombo::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<CtrlrCombo, bases<CtrlrComponent, CtrlrLuaObject> >("CtrlrCombo")
			.def("getOwnedComboBox", &CtrlrCombo::getOwnedComboBox)
		.def("getSelectedId", &CtrlrCombo::getSelectedId)
		.def("getSelectedItemIndex", &CtrlrCombo::getSelectedItemIndex)
		.def("setSelectedId", &CtrlrCombo::setSelectedId)
		.def("setSelectedItemIndex", &CtrlrCombo::setSelectedItemIndex)
		.def("getText", &CtrlrCombo::getText)
		.def("setText", &CtrlrCombo::setText)
		.def("getValueMap", &CtrlrCombo::getValueMap)
		];
}