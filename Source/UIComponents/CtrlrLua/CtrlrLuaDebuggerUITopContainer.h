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

#ifndef __JUCE_HEADER_CB1A7F53E88CBF24__
#define __JUCE_HEADER_CB1A7F53E88CBF24__

//[Headers]     -- You can add your own extra header files here --
#include "CtrlrMacros.h"
#include "CtrlrLua/MethodEditor/CtrlrLuaCodeTokeniser.h"
class CtrlrLuaDebuggerUI;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrLuaDebuggerUITopContainer  : public Component
{
public:
    //==============================================================================
    CtrlrLuaDebuggerUITopContainer (CtrlrLuaDebuggerUI &_owner);
    ~CtrlrLuaDebuggerUITopContainer();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    class StackTracePanel : public ListBoxModel, public Component
    {
        public:
            StackTracePanel (CtrlrLuaDebuggerUITopContainer &_owner);
            int getNumRows();
            void paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected);
            void resized();
            void paint (Graphics &g);

        private:
            ListBox stackTraceList;
            CtrlrLuaDebuggerUITopContainer &owner;
    };

    class LocalVarsPanel : public ListBoxModel, public Component
    {
        public:
            LocalVarsPanel (CtrlrLuaDebuggerUITopContainer &_owner);
            int getNumRows();
            void paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected);
            void resized();
            void paint (Graphics &g);

        private:
            ListBox localVarsList;
            CtrlrLuaDebuggerUITopContainer &owner;
    };
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    StretchableLayoutManager layout;
    CodeDocument currentDocument;
    CtrlrLuaCodeTokeniser luaTokeniser;
    CtrlrLuaDebuggerUI &owner;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<CodeEditorComponent> currentDebuggedCode;
    ScopedPointer<StretchableLayoutResizerBar> stretcher;
    ScopedPointer<ConcertinaPanel> rightPanel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLuaDebuggerUITopContainer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_CB1A7F53E88CBF24__
