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

#include "CtrlrLuaDebuggerUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrLuaDebuggerUI::CtrlrLuaDebuggerUI (CtrlrPanel *_owner) : owner(_owner), debugger(nullptr)
{
    addAndMakeVisible (debuggerOutput = new TextEditor (String::empty));
    debuggerOutput->setMultiLine (true);
    debuggerOutput->setReturnKeyStartsNewLine (false);
    debuggerOutput->setReadOnly (true);
    debuggerOutput->setScrollbarsShown (true);
    debuggerOutput->setCaretVisible (false);
    debuggerOutput->setPopupMenuEnabled (true);
    debuggerOutput->setText (String::empty);

    addAndMakeVisible (debuggerInput = new TextEditor (String::empty));
    debuggerInput->setMultiLine (false);
    debuggerInput->setReturnKeyStartsNewLine (false);
    debuggerInput->setReadOnly (false);
    debuggerInput->setScrollbarsShown (true);
    debuggerInput->setCaretVisible (true);
    debuggerInput->setPopupMenuEnabled (true);
    debuggerInput->setColour (TextEditor::backgroundColourId, Colour (0x97ffffff));
    debuggerInput->setColour (TextEditor::outlineColourId, Colour (0x79000000));
    debuggerInput->setText (String::empty);


    //[UserPreSize]
    debuggerInput->setFont (Font (Font::getDefaultMonospacedFontName(), 14.0f, Font::plain));
    debuggerOutput->setFont (Font (Font::getDefaultMonospacedFontName(), 14.0f, Font::plain));
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrLuaDebuggerUI::~CtrlrLuaDebuggerUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    debuggerOutput = nullptr;
    debuggerInput = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrLuaDebuggerUI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrLuaDebuggerUI::resized()
{
    debuggerOutput->setBounds (0, 0, proportionOfWidth (0.8000f), proportionOfHeight (0.8000f));
    debuggerInput->setBounds (0, proportionOfHeight (0.8000f), proportionOfWidth (0.8000f), proportionOfHeight (0.2000f));
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

<JUCER_COMPONENT documentType="Component" className="CtrlrLuaDebuggerUI" componentName=""
                 parentClasses="public CtrlrChildWindowContent" constructorParams="CtrlrPanel *_owner"
                 variableInitialisers="debugger(nullptr), owner(_owner)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffff"/>
  <TEXTEDITOR name="" id="f40d746c15284a53" memberName="debuggerOutput" virtualName=""
              explicitFocusOrder="0" pos="0 0 80% 80%" initialText="" multiline="1"
              retKeyStartsLine="0" readonly="1" scrollbars="1" caret="0" popupmenu="1"/>
  <TEXTEDITOR name="" id="4ed2b347c585c588" memberName="debuggerInput" virtualName=""
              explicitFocusOrder="0" pos="0 80% 80% 20%" bkgcol="97ffffff"
              outlinecol="79000000" initialText="" multiline="0" retKeyStartsLine="0"
              readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
