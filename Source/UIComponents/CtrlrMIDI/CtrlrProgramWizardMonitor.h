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

#ifndef __JUCE_HEADER_A6EC9C027CD54328__
#define __JUCE_HEADER_A6EC9C027CD54328__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
class CtrlrProgramWizard;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrProgramWizardMonitor  : public Component,
                                   public TextEditor::Listener
{
public:
    //==============================================================================
    CtrlrProgramWizardMonitor (CtrlrProgramWizard &_owner);
    ~CtrlrProgramWizardMonitor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void textEditorTextChanged(TextEditor &editor);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void mouseMove (const MouseEvent& e);
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);
    void mouseDoubleClick (const MouseEvent& e);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    CtrlrProgramWizard &owner;
    Font monoDataFont, monoStatusFont;
    MemoryBlock statusData;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextEditor> dataDisplay;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrProgramWizardMonitor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_A6EC9C027CD54328__
