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
//[/Headers]

#include "CtrlrLuaMethodDebuggerPrompt.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrLuaMethodDebuggerPrompt::CtrlrLuaMethodDebuggerPrompt (CtrlrLuaMethodEditor &_owner)
    : owner(_owner)
{
    addAndMakeVisible (debuggerOutput = new TextEditor ("Debugger output"));
    debuggerOutput->setMultiLine (true);
    debuggerOutput->setReturnKeyStartsNewLine (false);
    debuggerOutput->setReadOnly (true);
    debuggerOutput->setScrollbarsShown (true);
    debuggerOutput->setCaretVisible (false);
    debuggerOutput->setPopupMenuEnabled (true);
    debuggerOutput->setColour (TextEditor::textColourId, Colour (0xff5c5c5c));
    debuggerOutput->setColour (TextEditor::outlineColourId, Colour (0x00000000));
    debuggerOutput->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    debuggerOutput->setText (String::empty);

    addAndMakeVisible (debuggerInput = new TextEditor ("Debugger input"));
    debuggerInput->setMultiLine (false);
    debuggerInput->setReturnKeyStartsNewLine (false);
    debuggerInput->setReadOnly (false);
    debuggerInput->setScrollbarsShown (false);
    debuggerInput->setCaretVisible (true);
    debuggerInput->setPopupMenuEnabled (true);
    debuggerInput->setColour (TextEditor::highlightColourId, Colour (0x5b247c8d));
    debuggerInput->setColour (TextEditor::outlineColourId, Colour (0x8a000000));
    debuggerInput->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    debuggerInput->setText (String::empty);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrLuaMethodDebuggerPrompt::~CtrlrLuaMethodDebuggerPrompt()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    debuggerOutput = nullptr;
    debuggerInput = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrLuaMethodDebuggerPrompt::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrLuaMethodDebuggerPrompt::resized()
{
    debuggerOutput->setBounds (0, 0, getWidth() - 0, proportionOfHeight (0.8000f));
    debuggerInput->setBounds (0, proportionOfHeight (0.8000f), getWidth() - 0, proportionOfHeight (0.2000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrLuaMethodDebuggerPrompt"
                 componentName="" parentClasses="public Component" constructorParams="CtrlrLuaMethodEditor &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TEXTEDITOR name="Debugger output" id="2220af475a8f6614" memberName="debuggerOutput"
              virtualName="" explicitFocusOrder="0" pos="0 0 0M 80%" textcol="ff5c5c5c"
              outlinecol="0" shadowcol="0" initialText="" multiline="1" retKeyStartsLine="0"
              readonly="1" scrollbars="1" caret="0" popupmenu="1"/>
  <TEXTEDITOR name="Debugger input" id="b2b8220d7f2d2565" memberName="debuggerInput"
              virtualName="" explicitFocusOrder="0" pos="0 80% 0M 20%" hilitecol="5b247c8d"
              outlinecol="8a000000" shadowcol="0" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
