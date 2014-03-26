#include "stdafx.h"
#include "CtrlrLuaMethodEditorTabs.h"

// Tabbed component
CtrlrLuaMethodEditorTabs::CtrlrLuaMethodEditorTabs(CtrlrLuaMethodEditor &_owner) 
	:	owner(_owner),
		TabbedComponent(TabbedButtonBar::TabsAtTop)
{
}

TabBarButton *CtrlrLuaMethodEditorTabs::createTabButton (const String &tabName, int tabIndex)
{
	TabBarButton *btn = new TabBarButton (tabName, getTabbedButtonBar());
	CtrlrMethodEditorTabCloseButton *close = new CtrlrMethodEditorTabCloseButton(owner, tabIndex);
	close->setSize (20,20);
	btn->setExtraComponent (close, TabBarButton::afterText);
	return (btn);
}