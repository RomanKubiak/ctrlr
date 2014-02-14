#ifndef __CTRLR_LUA_METHOD_EDITOR_TABS__
#define __CTRLR_LUA_METHOD_EDITOR_TABS__

#include "CtrlrMethodEditorTabCloseButton.h"

class CtrlrLuaMethodEditor;

class CtrlrLuaMethodEditorTabs : public TabbedComponent
{
	public:
		CtrlrLuaMethodEditorTabs(CtrlrLuaMethodEditor &_owner);
		TabBarButton *createTabButton (const String &tabName, int tabIndex);
		JUCE_LEAK_DETECTOR(CtrlrLuaMethodEditorTabs)

	private:
		CtrlrLuaMethodEditor &owner;
};

#endif