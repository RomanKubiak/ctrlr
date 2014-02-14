#include "stdafx.h"
#include "LPopupMenu.h"

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

void LPopupMenu::addSubMenu (const String& subMenuName,
                     const LPopupMenu& subMenu,
                     bool isEnabled,
                     const Image& iconToUse,
                     bool isTicked,
                     int itemResultID)
{
	PopupMenu::addSubMenu (subMenuName, subMenu, isEnabled, iconToUse, isTicked, itemResultID);
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
				.def("addItem", (void(PopupMenu::*)(int , const String& , bool , bool , const Image&))&PopupMenu::addItem)
				.def("addItem", (void(PopupMenu::*)(int , const String& , bool , bool , Drawable*))&PopupMenu::addItem)
				.def("addItem", (void(PopupMenu::*)(int , const String& , bool , bool))&PopupMenu::addItem)
				.def("addColouredItem", &PopupMenu::addColouredItem)
				.def("addSubMenu", &LPopupMenu::addSubMenu)
				.def("addSeparator", &PopupMenu::addSeparator)
				.def("addSectionHeader", &PopupMenu::addSectionHeader)
				.def("getNumItems", &PopupMenu::getNumItems)
				.def("show", &LPopupMenu::show)
	];
}