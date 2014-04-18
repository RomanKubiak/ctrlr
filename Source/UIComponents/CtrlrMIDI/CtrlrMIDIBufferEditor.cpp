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

#include "CtrlrMIDIBufferEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrMIDIBufferEditor::CtrlrMIDIBufferEditor (CtrlrPanel &_owner)
    : owner(_owner), bufferState(Ids::uiChildWindowContentState)
{
    addAndMakeVisible (layoutResizerBar = new StretchableLayoutResizerBar (&layoutManager, 1, true));

    addAndMakeVisible (bufferLeft = new CtrlrMIDIBuffer (owner));
    addAndMakeVisible (bufferRight = new CtrlrMIDIBuffer (owner));

    //[UserPreSize]
    layoutManager.setItemLayout (0, -0.01, -0.98, -0.48);
    layoutManager.setItemLayout (1, 8, 8, 8);
    layoutManager.setItemLayout (2, -0.01, -0.98, -0.48);
    //[/UserPreSize]

    setSize (400, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrMIDIBufferEditor::~CtrlrMIDIBufferEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    layoutResizerBar = nullptr;
    bufferLeft = nullptr;
    bufferRight = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrMIDIBufferEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrMIDIBufferEditor::resized()
{
    layoutResizerBar->setBounds ((getWidth() / 2) + -4, 0, 8, getHeight() - 0);
    bufferLeft->setBounds (0, 0, 122, 200);
    bufferRight->setBounds (264, 0, 130, 200);
    //[UserResized] Add your own custom resize handling here..
    Component *components[] = { bufferLeft,layoutResizerBar,bufferRight };
    layoutManager.layOutComponents (components, 3, 0, 0, getWidth(),getHeight(),false,true);
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
StringArray CtrlrMIDIBufferEditor::getMenuBarNames()
{
	const char *menus[] = { "File", "Edit", 0 };
	return (StringArray(menus));
}

PopupMenu CtrlrMIDIBufferEditor::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
	PopupMenu m;
	if (topLevelMenuIndex == 0)
	{
		m.addItem (10, "Save state");
		m.addItem (11, "Close");
	}
	else if (topLevelMenuIndex == 1)
	{
		m.addItem (100, "Compare buffers");
	}
	return (m);
}

void CtrlrMIDIBufferEditor::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	if (topLevelMenuIndex == 0)
	{
		if (menuItemID == 10)
		{
			save();
		}
	}
	else if (topLevelMenuIndex == 1)
	{
		if (menuItemID == 100)
		{
			compareBuffers();
		}
	}
}

void CtrlrMIDIBufferEditor::compareBuffers()
{
	MemoryBlock left 	= bufferLeft->getData();
	MemoryBlock right	= bufferRight->getData();

	bufferLeft->clearUnequalPositions();
	bufferRight->clearUnequalPositions();

	bufferLeft->setSizeMatch(left.getSize() == right.getSize());
	bufferRight->setSizeMatch(left.getSize() == right.getSize());

    uint8 *ref = (uint8*)left.getData();
	uint8 *cmp  = (uint8*)right.getData();

    for (size_t i=0; i<left.getSize(); i++)
	{
		if (*(ref+i) != *(cmp+i))
		{
            bufferLeft->addUnequalPosition (i*3);
            bufferRight->addUnequalPosition (i*3);
		}
	}
}

void CtrlrMIDIBufferEditor::restoreState (const ValueTree &savedState)
{
	if (bufferLeft && bufferRight)
	{
		bufferLeft->restoreState(savedState.getChildWithName(Ids::midiBufferEditorLeft));
		bufferRight->restoreState(savedState.getChildWithName(Ids::midiBufferEditorRight));
	}

	save();
}

void CtrlrMIDIBufferEditor::save()
{
	componentTree.removeAllChildren (nullptr);
	componentTree.addChild (bufferLeft->getState(Ids::midiBufferEditorLeft).createCopy(), -1, nullptr);
	componentTree.addChild (bufferRight->getState(Ids::midiBufferEditorRight).createCopy(), -1, nullptr);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrMIDIBufferEditor" componentName=""
                 parentClasses="public CtrlrChildWindowContent" constructorParams="CtrlrPanel &amp;_owner"
                 variableInitialisers="owner(_owner), bufferState(Ids::uiChildWindowContentState)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.33000001311302185059"
                 fixedSize="1" initialWidth="400" initialHeight="400">
  <BACKGROUND backgroundColour="ffffff"/>
  <GENERICCOMPONENT name="" id="fd385958e4170e67" memberName="layoutResizerBar" virtualName=""
                    explicitFocusOrder="0" pos="-4C 0 8 0M" class="StretchableLayoutResizerBar"
                    params="&amp;layoutManager, 1, true"/>
  <JUCERCOMP name="" id="c726bac072320cbe" memberName="bufferLeft" virtualName=""
             explicitFocusOrder="0" pos="0 0 122 200" sourceFile="CtrlrMIDIBuffer.cpp"
             constructorParams="owner"/>
  <JUCERCOMP name="" id="48395e59480db5cd" memberName="bufferRight" virtualName=""
             explicitFocusOrder="0" pos="264 0 130 200" sourceFile="CtrlrMIDIBuffer.cpp"
             constructorParams="owner"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
