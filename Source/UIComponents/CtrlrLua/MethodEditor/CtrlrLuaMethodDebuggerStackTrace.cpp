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

//[Headers] You can add your own extra header files here...
#include "stdafx.h"
#include "CtrlrInlineUtilitiesGUI.h"
#include "CtrlrLuaMethodEditor.h"
//[/Headers]

#include "CtrlrLuaMethodDebuggerStackTrace.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrLuaMethodDebuggerStackTrace::CtrlrLuaMethodDebuggerStackTrace (CtrlrLuaMethodEditor &_owner)
    : owner(_owner)
{
    addAndMakeVisible (stackTraceList = new TableListBox());


    //[UserPreSize]
    stackTraceList->setModel (this);
    stackTraceList->getHeader().addColumn ("No", 1, 30, 30, -1, TableHeaderComponent::notSortable);
    stackTraceList->getHeader().addColumn ("Script", 2, 120, 120, -1, TableHeaderComponent::notSortable);
    stackTraceList->getHeader().addColumn ("Method", 3, 150, 150, -1, TableHeaderComponent::notSortable);
    stackTraceList->getHeader().addColumn ("Line", 4, 40, 40, -1, TableHeaderComponent::notSortable);
    setName ("Stack trace");
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrLuaMethodDebuggerStackTrace::~CtrlrLuaMethodDebuggerStackTrace()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    stackTraceList = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrLuaMethodDebuggerStackTrace::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrLuaMethodDebuggerStackTrace::resized()
{
    stackTraceList->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrLuaMethodDebuggerStackTrace::setData(const String &data)
{
    // _DBG("CtrlrLuaMethodDebuggerStackTrace::setData");
    // _DBG(data);

    /*
    [debug][1]***	methodInATable in [string "triggerDebugger"]:32
[debug][2]	method2 in [string "triggerDebugger"]:24
[debug][3]	method1 in [string "triggerDebugger"]:20
[debug][4]	method0 in [string "triggerDebugger"]:16
[debug][5]	Lua in [string "triggerDebugger"]:10
*/
    traceLines = StringArray::fromLines (data);
    currentFrames.clear();

    for (auto line : traceLines)
    {
        if (!line.trim().isEmpty())
            currentFrames.add (getStackFrame(line));
    }

    stackTraceList->updateContent ();
}

CtrlrLuaMethodDebuggerStackTrace::StackFrame CtrlrLuaMethodDebuggerStackTrace::getStackFrame(const String &stackTraceInfoAsString)
{
    CtrlrLuaMethodDebuggerStackTrace::StackFrame frame;
    StringArray tokens = StringArray::fromTokens (stackTraceInfoAsString, " \t", "\"'");

    frame.positionOnTheStack    = tokens[0].fromFirstOccurrenceOf("[", false, true).getIntValue();
    frame.methodName            = tokens[1].trim();
    frame.scriptName            = tokens[4].upToFirstOccurrenceOf("]", false, true).unquoted();
    frame.lineNumber            = tokens[4].fromFirstOccurrenceOf(":", false, true).getIntValue();
    frame.isCurrent             = tokens[0].contains("*");

    return (frame);
}

int CtrlrLuaMethodDebuggerStackTrace::getNumRows()
{
    return (currentFrames.size());
}

void CtrlrLuaMethodDebuggerStackTrace::paintRowBackground (Graphics &g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
    {
        drawSelectionRectangle(g, width, height);
    }
    else
    {
        g.fillAll (Colours::white);
    }
}

void CtrlrLuaMethodDebuggerStackTrace::paintCell (Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour (Colours::black);

    if (currentFrames[rowNumber].isCurrent)
        g.setFont (Font (12.0f, Font::bold));
    else
        g.setFont (Font (12.0f, Font::plain));

    if (columnId == 1)
        g.drawText (_STR(currentFrames[rowNumber].positionOnTheStack), 0, 0, width, height, Justification::left, true);

    if (columnId == 2)
        g.drawText (currentFrames[rowNumber].scriptName, 0, 0, width, height, Justification::left, true);

    if (columnId == 3)
        g.drawText (currentFrames[rowNumber].methodName, 0, 0, width, height, Justification::left, true);

    if (columnId == 4)
        g.drawText (_STR(currentFrames[rowNumber].lineNumber), 0, 0, width, height, Justification::left, true);
}

void CtrlrLuaMethodDebuggerStackTrace::cellDoubleClicked (int rowNumber, int columnId, const MouseEvent &e)
{
    // int Ctrlr a script == a method, but there can be any functions/methods withing scripts
    // we can go only as far as a METHOD in ctrlr, that is those defined as internal methods
    // we can't really search for individual functions in all METHODS of Ctrlr
    owner.highlightCode (currentFrames[rowNumber].scriptName, currentFrames[rowNumber].lineNumber);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrLuaMethodDebuggerStackTrace"
                 componentName="" parentClasses="public Component, public TableListBoxModel"
                 constructorParams="CtrlrLuaMethodEditor &amp;_owner" variableInitialisers="owner(_owner)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="" id="2cfe8a97e1866b01" memberName="stackTraceList" virtualName=""
                    explicitFocusOrder="0" pos="0 0 0M 0M" class="TableListBox" params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
