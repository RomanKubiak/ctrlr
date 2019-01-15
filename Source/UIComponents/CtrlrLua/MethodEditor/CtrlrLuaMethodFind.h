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

#ifndef __JUCE_HEADER_F8FE78491B09FC26__
#define __JUCE_HEADER_F8FE78491B09FC26__

//[Headers]     -- You can add your own extra header files here --
#include "CtrlrMacros.h"
class CtrlrLuaMethodEditor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrLuaMethodFind  : public Component,
                            public TextEditor::Listener,
							public Button::Listener,
							public ComboBox::Listener
{
public:
    //==============================================================================
    CtrlrLuaMethodFind (CtrlrLuaMethodEditor &_owner);
    ~CtrlrLuaMethodFind();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void textEditorReturnKeyPressed (TextEditor &editor);
	void textEditorTextChanged (TextEditor &editor);
	void findNextMatch();
	void findInOpened();
	void findInAll();
	void replaceNextMatch();
	void replaceAllMatches();
	void setFocusOnFindInput();
	const Array<Range<int> > searchForMatchesInDocument(CodeDocument &doc);
	void reportFoundMatch (CodeDocument &document, const String &methodName, const Range<int> range);
    //[/UserMethods]
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void visibilityChanged();
    bool keyPressed (const KeyPress& key);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	CtrlrLuaMethodEditor &owner;
	int lastFoundPosition;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextEditor> findInput;
    ScopedPointer<TextEditor> replaceInput;
    ScopedPointer<TextButton> findNext;
    ScopedPointer<TextButton> replaceNextButton;
    ScopedPointer<TextButton> replaceAllButton;
    ScopedPointer<Label> label;
    ScopedPointer<ToggleButton> matchCase;
    ScopedPointer<Label> label2;
    ScopedPointer<ComboBox> whereToFindCombo;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLuaMethodFind)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_F8FE78491B09FC26__
