#pragma once

#include "CtrlrMethodEditorTabCloseButton.h"

class CtrlrLuaMethodEditor;

class CtrlrLuaMethodEditorTabs : public TabbedComponent
{
	public:
		CtrlrLuaMethodEditorTabs(CtrlrLuaMethodEditor &_owner);
		~CtrlrLuaMethodEditorTabs();
		TabBarButton *createTabButton (const String &tabName, int tabIndex) override;
		void 	currentTabChanged (int newCurrentTabIndex, const String &newCurrentTabName) override;
		JUCE_LEAK_DETECTOR(CtrlrLuaMethodEditorTabs)

	private:
		CtrlrLuaMethodEditor &owner;
};
