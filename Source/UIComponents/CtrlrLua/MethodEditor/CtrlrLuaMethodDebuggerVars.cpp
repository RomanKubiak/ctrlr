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
//[/Headers]

#include "CtrlrLuaMethodDebuggerVars.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrLuaMethodDebuggerVars::CtrlrLuaMethodDebuggerVars (CtrlrLuaMethodEditor &_owner)
    : owner(_owner)
{
    addAndMakeVisible (valueList = new TableListBox());


    //[UserPreSize]
    setName ("Variables");
    valueList->setModel (this);
    valueList->getHeader().addColumn ("Name", 1, 120, 120, -1);
    valueList->getHeader().addColumn ("Type", 2, 120, 120, -1);
    valueList->getHeader().addColumn ("Value", 3, 140, 140, -1);
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
    // _DBG("CtrlrLuaMethodDebuggerVars::setData {"+data+"}");
    var result;
    JSON::parse ("{" + data + "}", result);

    if (result.isObject())
    {
        currentVars.clear();

        DynamicObject *o = result.getDynamicObject();

        if (o)
        {
            if (o->getProperty(o->getProperties().getName(0)).isObject())
            {
                DynamicObject *variables = o->getProperty(o->getProperties().getName(0)).getDynamicObject();
                if (variables)
                {
                    for (int i=0; i<variables->getProperties().size(); i++)
                    {
                        Variable v;
                        if (variables->getProperties().getName(i).toString() == "table")
                            continue;

                        v.varName   = variables->getProperties().getName(i).toString();
                        if (variables->getProperties().getValueAt(i).isObject())
                        {
                            DynamicObject *varDesc = variables->getProperties().getValueAt(i).getDynamicObject();

                            if (varDesc->getProperties().getName(0).toString() == "userdata")
                            {
                                if (isupper (varDesc->getProperties().getValueAt(0).toString()[0]))
                                {
                                    v.varType = _STR ("(" + varDesc->getProperties().getValueAt(0).toString() + ")");
                                }
                                else
                                {
                                    v.varType = varDesc->getProperties().getValueAt(0);
                                }
                            }
                            else if (varDesc->getProperties().getName(0).toString() == "table")
                            {
                                v.varType   = varDesc->getProperties().getName(0).toString();
                                v.varValue  = _STR("["+varDesc->getProperties().getValueAt(0).toString()+"]");
                            }
                            else
                            {
                                v.varType   = varDesc->getProperties().getName(0).toString();
                                v.varValue  = varDesc->getProperties().getValueAt(0);
                            }
                        }
                        else
                        {
                            v.varValue = variables->getProperties().getValueAt(i);
                        }

                        currentVars.add (v);
                    }
                }

                valueList->updateContent();
            }
        }
    }
}

void CtrlrLuaMethodDebuggerVars::paintRowBackground (Graphics &g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
    {
        gui::drawSelectionRectangle(g, width, height);
    }
    else
    {
        g.fillAll (Colours::white);
    }
}

void CtrlrLuaMethodDebuggerVars::paintCell (Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    if (columnId == 1)
        g.drawText (currentVars[rowNumber].varName, 0, 0, width, height, Justification::left, true);

    if (columnId == 2)
        g.drawText (currentVars[rowNumber].varType, 0, 0, width, height, Justification::left, true);

    if (columnId == 3)
        g.drawText (currentVars[rowNumber].varValue.toString(), 0, 0, width, height, Justification::left, true);
}

void CtrlrLuaMethodDebuggerVars::cellDoubleClicked (int rowNumber, int columnId, const MouseEvent &e)
{
}

int CtrlrLuaMethodDebuggerVars::getNumRows()
{
    return (currentVars.size());
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
                 constructorParams="CtrlrLuaMethodEditor &amp;_owner" variableInitialisers="owner(_owner)"
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
