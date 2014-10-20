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
#include "CtrlrLuaDebuggerUIControls.h"
//[/Headers]

#include "CtrlrLuaDebuggerUITopContainer.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrLuaDebuggerUITopContainer::CtrlrLuaDebuggerUITopContainer (CtrlrLuaDebuggerUI &_owner)
    : owner(_owner)
{
    addAndMakeVisible (currentDebuggedCode = new CodeEditorComponent (currentDocument, &luaTokeniser));

    addAndMakeVisible (stretcher = new StretchableLayoutResizerBar (&layout, 1, true));

    addAndMakeVisible (rightPanel = new ConcertinaPanel());


    //[UserPreSize]
    layout.setItemLayout (0, -0.001, -1.0, -0.69);
 	layout.setItemLayout (1, 8, 8, 8);
 	layout.setItemLayout (2, -0.001, -1.0, -0.29);

    rightPanel->addPanel (0, new StackTracePanel(*this), true);
    rightPanel->addPanel (1, new LocalVarsPanel(*this), true);
    rightPanel->addPanel (2, new CtrlrLuaDebuggerUIControls (owner), true);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrLuaDebuggerUITopContainer::~CtrlrLuaDebuggerUITopContainer()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    currentDebuggedCode = nullptr;
    stretcher = nullptr;
    rightPanel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrLuaDebuggerUITopContainer::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrLuaDebuggerUITopContainer::resized()
{
    currentDebuggedCode->setBounds (0, 0, proportionOfWidth (0.6900f), proportionOfHeight (1.0000f));
    stretcher->setBounds (proportionOfWidth (0.6900f), 0, proportionOfWidth (0.0100f), proportionOfHeight (1.0000f));
    rightPanel->setBounds (proportionOfWidth (0.7000f), 0, proportionOfWidth (0.3000f), proportionOfHeight (1.0000f));
    //[UserResized] Add your own custom resize handling here..
    Component* comps[] = { currentDebuggedCode, stretcher,  rightPanel};
	layout.layOutComponents (comps, 3, 0, 0, getWidth(), getHeight(), false, true);
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrLuaDebuggerUITopContainer::setDebuggerJsonOutput (const String &jsonEncodedData)
{
    _DBG("CtrlrLuaDebuggerUITopContainer::setDebuggerJsonOutput");
    var result;
    JSON::parse (jsonEncodedData, result);

    if (result.isObject())
    {
        _DBG("\tresult is an object");

        if (result.getProperty("traceback", var::null) != var::null)
        {
            setTracebackData (result.getProperty("traceback", var::null));
        }
    }
}

void CtrlrLuaDebuggerUITopContainer::setTracebackData(var tracebackData)
{
    _DBG("CtrlrLuaDebuggerUITopContainer::setTracebackData(");
    StringArray stack = StringArray::fromLines (tracebackData.toString());
    for (int i=0; i<stack.size(); i++)
    {
        // [string "debugger.lua"]:109: in function <[string "debugger.lua"]:95>
        _DBG("\tline "+_STR(i)+stack[i].trim());
    }
}

/* Stack trace panel implementation
*/
CtrlrLuaDebuggerUITopContainer::StackTracePanel::StackTracePanel (CtrlrLuaDebuggerUITopContainer &_owner) : owner(_owner), stackTraceList("Stack trace", this)
{
    setName ("Stack trace");
    addAndMakeVisible (&stackTraceList);
}

void CtrlrLuaDebuggerUITopContainer::StackTracePanel::paint (Graphics &g)
{
    g.fillAll (Colour::greyLevel (0.8f));
}

void CtrlrLuaDebuggerUITopContainer::StackTracePanel::resized()
{
    stackTraceList.setBounds (0, 0, getWidth(), getHeight());
}

int CtrlrLuaDebuggerUITopContainer::StackTracePanel::getNumRows()
{
    return (0);
}

void CtrlrLuaDebuggerUITopContainer::StackTracePanel::paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
}

/* Stack trace panel implementation
*/
CtrlrLuaDebuggerUITopContainer::LocalVarsPanel::LocalVarsPanel (CtrlrLuaDebuggerUITopContainer &_owner) : owner(_owner), localVarsList("Local vars", this)
{
    setName ("Variables");
    addAndMakeVisible (&localVarsList);
}

void CtrlrLuaDebuggerUITopContainer::LocalVarsPanel::paint (Graphics &g)
{
    g.fillAll (Colour::greyLevel (0.8f));
}

void CtrlrLuaDebuggerUITopContainer::LocalVarsPanel::resized()
{
    localVarsList.setBounds (0, 0, getWidth(), getHeight());
}

int CtrlrLuaDebuggerUITopContainer::LocalVarsPanel::getNumRows()
{
    return (0);
}

void CtrlrLuaDebuggerUITopContainer::LocalVarsPanel::paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrLuaDebuggerUITopContainer"
                 componentName="" parentClasses="public Component" constructorParams="CtrlrLuaDebuggerUI &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffff"/>
  <GENERICCOMPONENT name="" id="84936279aacdc59b" memberName="currentDebuggedCode"
                    virtualName="" explicitFocusOrder="0" pos="0 0 69% 100%" class="CodeEditorComponent"
                    params="currentDocument, &amp;luaTokeniser"/>
  <GENERICCOMPONENT name="" id="9c08ba0f4e40ee1c" memberName="stretcher" virtualName=""
                    explicitFocusOrder="0" pos="69% 0 1% 100%" class="StretchableLayoutResizerBar"
                    params="&amp;layout, 1, true"/>
  <GENERICCOMPONENT name="" id="62cc40400140897b" memberName="rightPanel" virtualName=""
                    explicitFocusOrder="0" pos="70% 0 30% 100%" class="ConcertinaPanel"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
