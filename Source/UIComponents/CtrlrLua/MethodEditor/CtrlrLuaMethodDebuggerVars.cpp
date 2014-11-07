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

#include "CtrlrLuaMethodDebuggerVars.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrLuaMethodDebuggerVars::CtrlrLuaMethodDebuggerVars (CtrlrLuaMethodEditor &_owner)
{
    addAndMakeVisible (valueList = new TableListBox());


    //[UserPreSize]
    setName ("Variables");
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrLuaMethodDebuggerVars::~CtrlrLuaMethodDebuggerVars()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    valueList = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrLuaMethodDebuggerVars::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrLuaMethodDebuggerVars::resized()
{
    valueList->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrLuaMethodDebuggerVars::setData (const String &data)
{
    _DBG("CtrlrLuaMethodDebuggerVars::setData");
    _DBG(data);
}

void CtrlrLuaMethodDebuggerVars::paintRowBackground (Graphics &g, int rowNumber, int width, int height, bool rowIsSelected)
{
}

void CtrlrLuaMethodDebuggerVars::paintCell (Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
}

void CtrlrLuaMethodDebuggerVars::cellDoubleClicked (int rowNumber, int columnId, const MouseEvent &e)
{
}

int CtrlrLuaMethodDebuggerVars::getNumRows()
{
    return (currentVars.size());
}

CtrlrLuaMethodDebuggerVars::Variable CtrlrLuaMethodDebuggerVars::getVariable(const String &variableAsString)
{
    Variable v;

    return (v);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrLuaMethodDebuggerVars"
                 componentName="" parentClasses="public Component, public TableListBoxModel"
                 constructorParams="CtrlrLuaMethodEditor &amp;_owner" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="" id="e62042fbd323c112" memberName="valueList" virtualName=""
                    explicitFocusOrder="0" pos="0 0 0M 0M" class="TableListBox" params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
