#ifndef __L_POPUP_MENU__
#define __L_POPUP_MENU__

#include "CtrlrLuaManager.h"

class LPopupMenu : public PopupMenu
{
	public:
		LPopupMenu();
		int show(int itemIDThatMustBeVisible = 0,
              int minimumWidth = 0,
              int maximumNumColumns = 0,
              int standardItemHeight = 0);

		void addSubMenu (const String& subMenuName,
                     const LPopupMenu& subMenu,
                     bool isEnabled = true,
                     const Image& iconToUse = Image::null,
                     bool isTicked = false,
                     int itemResultID = 0);

		static void wrapForLua (lua_State *L);
};

#endif