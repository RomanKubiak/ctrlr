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
//[/Headers]

#include "CtrlrLuaDebuggerUIControls.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrLuaDebuggerUIControls::CtrlrLuaDebuggerUIControls (CtrlrLuaDebuggerUI &_owner)
    : owner(_owner)
{
    addAndMakeVisible (continueExec = new TextButton (String::empty));
    continueExec->setTooltip (TRANS("contiue execution"));
    continueExec->setButtonText (TRANS("Continue"));
    continueExec->addListener (this);
    continueExec->setColour (TextButton::buttonColourId, Colour (0xffcaffbb));

    addAndMakeVisible (stepOver = new TextButton (String::empty));
    stepOver->setTooltip (TRANS("step forward by one line (skipping over functions)"));
    stepOver->setButtonText (TRANS("Step Over"));
    stepOver->addListener (this);
    stepOver->setColour (TextButton::buttonColourId, Colour (0xfff2bbff));

    addAndMakeVisible (textEditor = new TextEditor ("new text editor"));
    textEditor->setMultiLine (false);
    textEditor->setReturnKeyStartsNewLine (false);
    textEditor->setReadOnly (false);
    textEditor->setScrollbarsShown (true);
    textEditor->setCaretVisible (true);
    textEditor->setPopupMenuEnabled (true);
    textEditor->setColour (TextEditor::backgroundColourId, Colour (0xb6ffffff));
    textEditor->setColour (TextEditor::outlineColourId, Colours::black);
    textEditor->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    textEditor->setText (String::empty);

    addAndMakeVisible (stepInto = new TextButton ("new button"));
    stepInto->setTooltip (TRANS("step forward by one line (into functions)"));
    stepInto->setButtonText (TRANS("Step Into"));
    stepInto->addListener (this);
    stepInto->setColour (TextButton::buttonColourId, Colour (0xffbbffff));

    addAndMakeVisible (finish = new TextButton (String::empty));
    finish->setTooltip (TRANS("step forward until exiting the current function"));
    finish->setButtonText (TRANS("Finish"));
    finish->addListener (this);
    finish->setColour (TextButton::buttonColourId, Colour (0xffffa9a9));

    addAndMakeVisible (execute = new TextButton (String::empty));
    execute->setTooltip (TRANS("[expression] - execute the expression and print the result"));
    execute->setButtonText (TRANS("Execute"));
    execute->addListener (this);
    execute->setColour (TextButton::buttonColourId, Colour (0xffe2ff61));


    //[UserPreSize]
    setName ("Debugger control");
    //[/UserPreSize]

    setSize (200, 256);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrLuaDebuggerUIControls::~CtrlrLuaDebuggerUIControls()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    continueExec = nullptr;
    stepOver = nullptr;
    textEditor = nullptr;
    stepInto = nullptr;
    finish = nullptr;
    execute = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrLuaDebuggerUIControls::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrLuaDebuggerUIControls::resized()
{
    continueExec->setBounds (proportionOfWidth (0.0100f), proportionOfHeight (0.0117f), proportionOfWidth (0.9800f), proportionOfHeight (0.1016f));
    stepOver->setBounds (proportionOfWidth (0.0100f), proportionOfHeight (0.1211f), proportionOfWidth (0.9800f), proportionOfHeight (0.1016f));
    textEditor->setBounds (0, proportionOfHeight (0.6016f), proportionOfWidth (1.0000f), proportionOfHeight (0.3984f));
    stepInto->setBounds (proportionOfWidth (0.0100f), proportionOfHeight (0.2305f), proportionOfWidth (0.9800f), proportionOfHeight (0.1016f));
    finish->setBounds (proportionOfWidth (0.0100f), proportionOfHeight (0.3398f), proportionOfWidth (0.9800f), proportionOfHeight (0.1016f));
    execute->setBounds (proportionOfWidth (0.0100f), proportionOfHeight (0.4492f), proportionOfWidth (0.9800f), proportionOfHeight (0.1016f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CtrlrLuaDebuggerUIControls::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == continueExec)
    {
        //[UserButtonCode_continueExec] -- add your button handler code here..
        //[/UserButtonCode_continueExec]
    }
    else if (buttonThatWasClicked == stepOver)
    {
        //[UserButtonCode_stepOver] -- add your button handler code here..
        //[/UserButtonCode_stepOver]
    }
    else if (buttonThatWasClicked == stepInto)
    {
        //[UserButtonCode_stepInto] -- add your button handler code here..
        //[/UserButtonCode_stepInto]
    }
    else if (buttonThatWasClicked == finish)
    {
        //[UserButtonCode_finish] -- add your button handler code here..
        //[/UserButtonCode_finish]
    }
    else if (buttonThatWasClicked == execute)
    {
        //[UserButtonCode_execute] -- add your button handler code here..
        //[/UserButtonCode_execute]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrLuaDebuggerUIControls"
                 componentName="" parentClasses="public Component" constructorParams="CtrlrLuaDebuggerUI &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="200"
                 initialHeight="256">
  <BACKGROUND backgroundColour="ffffff"/>
  <TEXTBUTTON name="" id="8909a541a9ca8b7" memberName="continueExec" virtualName=""
              explicitFocusOrder="0" pos="1% 1.172% 98% 10.156%" tooltip="contiue execution"
              bgColOff="ffcaffbb" buttonText="Continue" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="4e56b2b479a3ea39" memberName="stepOver" virtualName=""
              explicitFocusOrder="0" pos="1% 12.109% 98% 10.156%" tooltip="step forward by one line (skipping over functions)"
              bgColOff="fff2bbff" buttonText="Step Over" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="new text editor" id="1406da25a03876df" memberName="textEditor"
              virtualName="" explicitFocusOrder="0" pos="0 60.156% 100% 39.844%"
              bkgcol="b6ffffff" outlinecol="ff000000" shadowcol="0" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="ac44638fc0c4a2a8" memberName="stepInto"
              virtualName="" explicitFocusOrder="0" pos="1% 23.047% 98% 10.156%"
              tooltip="step forward by one line (into functions)" bgColOff="ffbbffff"
              buttonText="Step Into" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="d7a8857b8cf3ce05" memberName="finish" virtualName=""
              explicitFocusOrder="0" pos="1% 33.984% 98% 10.156%" tooltip="step forward until exiting the current function"
              bgColOff="ffffa9a9" buttonText="Finish" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="" id="15aa85e957ac5024" memberName="execute" virtualName=""
              explicitFocusOrder="0" pos="1% 44.922% 98% 10.156%" tooltip="[expression] - execute the expression and print the result"
              bgColOff="ffe2ff61" buttonText="Execute" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
