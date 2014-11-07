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

#ifndef __JUCE_HEADER_95CA9179E9D52EC2__
#define __JUCE_HEADER_95CA9179E9D52EC2__

//[Headers]     -- You can add your own extra header files here --
#include "CtrlrMacros.h"
#include "CtrlrLuaMethodDebuggerStackTrace.h"
#include "CtrlrLuaMethodDebuggerVars.h"
class CtrlrLuaMethodEditor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrLuaMethodDebuggerPrompt  : public Component,
                                      public TextEditor::Listener,
                                      public ButtonListener
{
public:
    //==============================================================================
    CtrlrLuaMethodDebuggerPrompt (CtrlrLuaMethodEditor &_owner);
    ~CtrlrLuaMethodDebuggerPrompt();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    enum CollectionState
    {
        Ended,
        Trace,
        Values
    };
    void insertRawDebuggerOutput(const String &debuggerOutput);
    void sendCommand (const String &text);
    void textEditorReturnKeyPressed (TextEditor &editor);
    StringArray &getCommandQueue();
    const String getCurrentDebuggerCommand(const bool clearTheReturnedCommand=true);
    void visibilityChanged();
    void insertToOutput(const String &what, const Colour textColour=Colour (0xff5c5c5c));
    void finishDataCollection();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    CtrlrLuaMethodEditor &owner;
    StringArray commandQueue;
    StretchableLayoutManager layoutManager;
	ScopedPointer <StretchableLayoutResizerBar> resizer;
	CollectionState collectionState;
	String collectedData;
	CtrlrLuaMethodDebuggerStackTrace *stackTracePanel;
    CtrlrLuaMethodDebuggerVars *varsPanel;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextEditor> debuggerOutput;
    ScopedPointer<TextEditor> debuggerInput;
    ScopedPointer<ImageButton> debugContinue;
    ScopedPointer<ImageButton> debugStepOver;
    ScopedPointer<ImageButton> debugStepInto;
    ScopedPointer<ConcertinaPanel> debuggerInfo;
    ScopedPointer<ImageButton> debugStepOut;
    ScopedPointer<ImageButton> debugRestart;
    ScopedPointer<ImageButton> debugStop;
	ScopedPointer<ImageButton> clearOutput;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLuaMethodDebuggerPrompt)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_95CA9179E9D52EC2__
