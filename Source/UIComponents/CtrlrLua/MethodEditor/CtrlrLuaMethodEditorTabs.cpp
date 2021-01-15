#include "stdafx.h"
#include "CtrlrLuaMethodEditorTabs.h"
#include "CtrlrLuaMethodEditor.h"
#include "CtrlrLuaMethodCodeEditor.h"
#include "Core/CtrlrPanel/CtrlrPanel.h"

// Tabbed component
CtrlrLuaMethodEditorTabs::CtrlrLuaMethodEditorTabs(CtrlrLuaMethodEditor &_owner)
	:	owner(_owner),
		TabbedComponent(TabbedButtonBar::TabsAtTop)
{
	setTabBarDepth(owner.getOwner().getOwner().getProperty(Ids::ctrlrTabBarDepth));
}

CtrlrLuaMethodEditorTabs::~CtrlrLuaMethodEditorTabs()
{
}

TabBarButton *CtrlrLuaMethodEditorTabs::createTabButton (const String &tabName, int tabIndex)
{
	TabBarButton *btn = new TabBarButton (tabName, getTabbedButtonBar());
	return (btn);
}

void CtrlrLuaMethodEditorTabs::currentTabChanged(int newCurrentTabIndex, const String &newCurrentTabName)
{
	CtrlrLuaMethodCodeEditor * codeEditor = dynamic_cast<CtrlrLuaMethodCodeEditor*> (getCurrentContentComponent());
	if (owner.findDialogActive == true)
	{
		if (codeEditor)
			codeEditor->getCodeComponent()->showFindPanel(false);
	}
	else
	{
		if (codeEditor)
			codeEditor->getCodeComponent()->hideFindPanel();
	}
}
