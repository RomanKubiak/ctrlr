#ifndef __CTRLR_LUA_METHOD_EDITOR_TABS__
#define __CTRLR_LUA_METHOD_EDITOR_TABS__

#include "CtrlrMethodEditorTabCloseButton.h"

class CtrlrLuaMethodEditor;

class CtrlrLuaMethodEditorTabsLF : public LookAndFeel_V3
{
	public:
		CtrlrLuaMethodEditorTabsLF();
		~CtrlrLuaMethodEditorTabsLF();
		int	getTabButtonBestWidth (TabBarButton &, int tabDepth);
		void drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown);
		static void createTabTextLayout (const TabBarButton& button, float length, float depth, Colour colour, TextLayout& textLayout);
		Rectangle <int> getTabButtonExtraComponentBounds (const TabBarButton &, Rectangle< int > &textArea, Component &extraComp);
};

class CtrlrLuaMethodEditorTabs : public TabbedComponent
{
	public:
		CtrlrLuaMethodEditorTabs(CtrlrLuaMethodEditor &_owner);
		~CtrlrLuaMethodEditorTabs();
		TabBarButton *createTabButton (const String &tabName, int tabIndex);
		JUCE_LEAK_DETECTOR(CtrlrLuaMethodEditorTabs)

	private:
		CtrlrLuaMethodEditor &owner;
		CtrlrLuaMethodEditorTabsLF *lf;
};

#endif