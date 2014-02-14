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

#ifndef __JUCE_HEADER_CE3E3E530CE423A0__
#define __JUCE_HEADER_CE3E3E530CE423A0__

//[Headers]     -- You can add your own extra header files here --
#include "CtrlrMacros.h"
#include "CtrlrLog.h"
#include "CtrlrWindowManagers/CtrlrChildWindowContent.h"
#include "CtrlrWindowManagers/CtrlrManagerWindowManager.h"
class CtrlrManager;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrMIDICalculator  : public CtrlrChildWindowContent,
                             public TextEditor::Listener,
                             public ComboBoxListener,
                             public ButtonListener
{
public:
    //==============================================================================
    CtrlrMIDICalculator (CtrlrManager &_owner);
    ~CtrlrMIDICalculator();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	String getContentName()					{ return ("MIDI Calculator"); }
	uint8 getType()							{ return (CtrlrManagerWindowManager::MIDICalculator); }
	void textEditorTextChanged (TextEditor &editor);
	void formatData (const String &data, const bool isHex=false, const bool isDec=false, const bool isBin=false);
	String formatHex(const int d);
	String makeHexPretty(const String &hex);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	CtrlrManager &owner;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextEditor> hexDisplay;
    ScopedPointer<Label> label;
    ScopedPointer<Label> label2;
    ScopedPointer<TextEditor> binDisplay;
    ScopedPointer<Label> label3;
    ScopedPointer<TextEditor> decDisplay;
    ScopedPointer<ComboBox> hexFormat;
    ScopedPointer<ToggleButton> bit16Switch;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrMIDICalculator)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_CE3E3E530CE423A0__
