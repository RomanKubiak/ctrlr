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
				.def("addItem", (void(PopupMenu::*)(int , const String& , bool , bool , const Image&))&PopupMenu::addItem)
				.def("addItem", (void(PopupMenu::*)(int , const String& , bool , bool , Drawable*))&PopupMenu::addItem)
				.def("addItem", (void(PopupMenu::*)(int , const String& , bool , bool))&PopupMenu::addItem)
				.def("addColouredItem", &PopupMenu::addColouredItem)
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
