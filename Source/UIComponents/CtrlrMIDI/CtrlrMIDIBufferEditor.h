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

#ifndef __JUCE_HEADER_817734578EE0E242__
#define __JUCE_HEADER_817734578EE0E242__

//[Headers]     -- You can add your own extra header files here --
#include "CtrlrWindowManagers/CtrlrChildWindowContent.h"
#include "CtrlrWindowManagers/CtrlrPanelWindowManager.h"
//[/Headers]

#include "CtrlrMIDIBuffer.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrMIDIBufferEditor  : public CtrlrChildWindowContent
{
public:
    //==============================================================================
    CtrlrMIDIBufferEditor (CtrlrPanel &_owner);
    ~CtrlrMIDIBufferEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    String getContentName()					{ return ("Buffer Editor"); }
	uint8 getType()							{ return (CtrlrPanelWindowManager::BufferEditor); }
	StringArray getMenuBarNames();
	PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName);
	void menuItemSelected(int menuItemID, int topLevelMenuIndex);
	void compareBuffers();
	void restoreState (const ValueTree &savedState);
	void save();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ValueTree bufferState;
    CtrlrPanel &owner;
    StretchableLayoutManager layoutManager;
    CodeDocument leftDocument, rightDocument;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<StretchableLayoutResizerBar> layoutResizerBar;
    ScopedPointer<CtrlrMIDIBuffer> bufferLeft;
    ScopedPointer<CtrlrMIDIBuffer> bufferRight;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrMIDIBufferEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_817734578EE0E242__
