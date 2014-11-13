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

#ifndef __JUCE_HEADER_BA63E77F235AA466__
#define __JUCE_HEADER_BA63E77F235AA466__

//[Headers]     -- You can add your own extra header files here --
#include "CtrlrMacros.h"
class CtrlrLuaMethodEditor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrLuaMethodDebuggerVars  : public Component,
                                    public TableListBoxModel
{
public:
    //==============================================================================
    CtrlrLuaMethodDebuggerVars (CtrlrLuaMethodEditor &_owner);
    ~CtrlrLuaMethodDebuggerVars();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    struct Variable
    {
        String varName;
        String varType;
        var varValue;
    };

    int getNumRows();
    void paintRowBackground (Graphics &g, int rowNumber, int width, int height, bool rowIsSelected);
    void paintCell (Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected);
    void cellDoubleClicked (int rowNumber, int columnId, const MouseEvent &e);
    void setData (const String &data);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    CtrlrLuaMethodEditor &owner;
    Array <Variable> currentVars;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TableListBox> valueList;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLuaMethodDebuggerVars)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_BA63E77F235AA466__
