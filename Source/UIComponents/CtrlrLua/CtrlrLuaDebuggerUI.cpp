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
CtrlrLuaDebuggerUI::CtrlrLuaDebuggerUI (CtrlrPanel &_owner)
    : owner(_owner)
{
    addAndMakeVisible (debuggerState = new TextEditor (String::empty));
    debuggerState->setMultiLine (true);
    debuggerState->setReturnKeyStartsNewLine (false);
    debuggerState->setReadOnly (true);
    debuggerState->setScrollbarsShown (true);
    debuggerState->setCaretVisible (false);
    debuggerState->setPopupMenuEnabled (true);
    debuggerState->setColour (TextEditor::textColourId, Colour (0xff343434));
    debuggerState->setColour (TextEditor::backgroundColourId, Colour (0xc5ffffff));
    debuggerState->setColour (TextEditor::outlineColourId, Colours::black);
    debuggerState->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    debuggerState->setText (String::empty);

    addAndMakeVisible (stretcher = new StretchableLayoutResizerBar (&layout, 1, false));

    addAndMakeVisible (topContainer = new CtrlrLuaDebuggerUITopContainer (*this));

    //[UserPreSize]
    layout.setItemLayout (0, -0.001, -1.0, -0.69);
 	layout.setItemLayout (1, 8, 8, 8);
 	layout.setItemLayout (2, -0.001, -1.0, -0.29);

    debuggerState->setFont (Font (Font::getDefaultMonospacedFontName(), 12.0f, Font::plain));
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrLuaDebuggerUI::~CtrlrLuaDebuggerUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    debuggerState = nullptr;
    stretcher = nullptr;
    topContainer = nullptr;


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
    debuggerState->setBounds (0, proportionOfHeight (0.7000f), proportionOfWidth (1.0000f), proportionOfHeight (0.3000f));
    stretcher->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.6900f), proportionOfWidth (1.0000f), proportionOfHeight (0.0100f));
    topContainer->setBounds (0, 0, getWidth() - 0, proportionOfHeight (0.6900f));
    //[UserResized] Add your own custom resize handling here..
    Component* comps[] = { topContainer, stretcher,  debuggerState};
	layout.layOutComponents (comps, 3, 0, 0, getWidth(), getHeight(), true, true);
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
int CtrlrLuaDebuggerUI::waitForCommand()
{
    return (runModalLoop());
}

void CtrlrLuaDebuggerUI::setOutputFromDebugger(const String &output)
{
    debuggerState->insertTextAtCaret (output.trim() + "\n");
}

String CtrlrLuaDebuggerUI::getLastCommand()
{
    return (lastCommand);
}

void CtrlrLuaDebuggerUI::setCommand(const String command)
{
    lastCommand = command;
    exitModalState(1);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrLuaDebuggerUI" componentName=""
                 parentClasses="public CtrlrChildWindowContent" constructorParams="CtrlrPanel &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffff"/>
  <TEXTEDITOR name="" id="4ed2b347c585c588" memberName="debuggerState" virtualName=""
              explicitFocusOrder="0" pos="0 70% 100% 30%" textcol="ff343434"
              bkgcol="c5ffffff" outlinecol="ff000000" shadowcol="0" initialText=""
              multiline="1" retKeyStartsLine="0" readonly="1" scrollbars="1"
              caret="0" popupmenu="1"/>
  <GENERICCOMPONENT name="" id="f56f3b59ce17a97b" memberName="stretcher" virtualName=""
                    explicitFocusOrder="0" pos="0% 69% 100% 1%" class="StretchableLayoutResizerBar"
                    params="&amp;layout, 1, false"/>
  <JUCERCOMP name="" id="4c015b173c60c9d3" memberName="topContainer" virtualName=""
             explicitFocusOrder="0" pos="0 0 0M 69%" sourceFile="CtrlrLuaDebuggerUITopContainer.cpp"
             constructorParams="*this"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
