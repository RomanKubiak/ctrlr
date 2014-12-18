/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  3 Apr 2012 10:45:28pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRLUACONSOLE_CTRLRLUACONSOLE_8D76A685__
#define __JUCER_HEADER_CTRLRLUACONSOLE_CTRLRLUACONSOLE_8D76A685__

//[Headers]     -- You can add your own extra header files here --
#include "CtrlrWindowManagers/CtrlrChildWindowContent.h"
#include "CtrlrLog.h"

class CtrlrPanel;
class CtrlrLookAndFeel;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrLuaConsole  : public CtrlrChildWindowContent,
                         public CtrlrLog::Listener,
                         public KeyListener
{
public:
    //==============================================================================
    CtrlrLuaConsole (CtrlrPanel &_owner);
    ~CtrlrLuaConsole();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	enum ToolbarItems
	{
		_none,
		snipsItem,
		historyItem,
		clearOutput
	};

	enum MoveDirection
	{
		NONE,
		UP,
		DOWN
	};

	void messageLogged (CtrlrLog::CtrlrLogMessage message);
	bool keyPressed (const KeyPress& key, Component* originatingComponent);
	void runCode(const String &code);
	const PopupMenu getSnipsMenu(const int mask);
	const PopupMenu getRecentFilesMenu(const int mask);
	void snipsItemClicked(Button *b);
	void historyItemClicked(Button *b);

	uint8 getType()							{ return (CtrlrPanelWindowManager::LuaConsole); }
	String getContentName()					{ return ("LUA Console"); }
	void buttonClicked (Button *button);
	void getAllToolbarItemIds (Array< int > &ids);
	void getDefaultItemSet (Array< int > &ids);
	ToolbarItemComponent *createItem (int itemId);

	StringArray getMenuBarNames();
	PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName);
	void menuItemSelected(int menuItemID, int topLevelMenuIndex);
	void focusGained(FocusChangeType cause);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    bool keyPressed (const KeyPress& key);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	CtrlrPanel &owner;
	StringArray snips;
	CodeDocument outputDocument, inputDocument;
	StretchableLayoutManager layoutManager;

	// Maintain console history and allow user to explore it via up/down keys
	bool nextUpKeyPressWillbeFirst;
	int lastMoveDirection;
	int lastCommandNumInHistory;
	String currentInputString;
	StringArray inputHistory;
    //[/UserVariables]

    //==============================================================================
    CodeEditorComponent* luaConsoleOutput;
    CodeEditorComponent* luaConsoleInput;
    StretchableLayoutResizerBar* resizer;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrLuaConsole (const CtrlrLuaConsole&);
    const CtrlrLuaConsole& operator= (const CtrlrLuaConsole&);
};


#endif   // __JUCER_HEADER_CTRLRLUACONSOLE_CTRLRLUACONSOLE_8D76A685__
