/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_1BD9D118493E65A2__
#define __JUCE_HEADER_1BD9D118493E65A2__

//[Headers]     -- You can add your own extra header files here --
#include "CtrlrLuaMethodEditorTabs.h"
#include "CtrlrLuaMethodFind.h"
#include "CtrlrTextEditor.h"
#include "CtrlrLuaMethodCodeEditor.h"
#include "CtrlrLuaMethodDebuggerPrompt.h"
#include "CtrlrLuaMethodEditorConsole.h"
class CtrlrLuaMethodEditor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrLuaMethodEditArea  : public Component,
                                public CtrlrLog::Listener
{
public:
    //==============================================================================
    CtrlrLuaMethodEditArea (CtrlrLuaMethodEditor &_owner);
    ~CtrlrLuaMethodEditArea();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	CtrlrLuaMethodEditorTabs *getTabs();
	TabbedComponent *getLowerTabs();
	void insertOutput(const String &textToInsert, const Colour what);
	void insertOutput(const AttributedString stringToInsert);
	void showFindDialog();
	void findNextMatch();
	void replaceNextMatch();
	void closeTabWithMethod(const ValueTree &item);
	void messageLogged (CtrlrLog::CtrlrLogMessage message);
	void mouseDoubleClick (const MouseEvent &e);
	bool keyPressed (const KeyPress &key, Component *event);
	void setActiveOutputTab();
	CtrlrLuaMethodDebuggerPrompt *getLuaDebuggerPrompt(const bool activateDebuggerNow=false);
    void clearOutputText();
	//[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	CtrlrLuaMethodEditor &owner;
	StretchableLayoutManager layoutManager;
	StretchableLayoutResizerBar *resizer;
	CtrlrTextEditor *output;
	CtrlrLuaMethodFind *find;
	CtrlrLuaMethodDebuggerPrompt *debuggerPrompt;
	CtrlrLuaMethodEditorConsole *luaConsole;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TabbedComponent> lowerTabs;
    ScopedPointer<CtrlrLuaMethodEditorTabs> upperTabs;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLuaMethodEditArea)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_1BD9D118493E65A2__
