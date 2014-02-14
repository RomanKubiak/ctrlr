/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  10 Nov 2012 11:04:16pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRLUAMETHODFIND_CTRLRLUAMETHODFIND_4C687B6E__
#define __JUCER_HEADER_CTRLRLUAMETHODFIND_CTRLRLUAMETHODFIND_4C687B6E__

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
                            public ButtonListener,
                            public ComboBoxListener
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

    void paint (Graphics& g);
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
    TextEditor* findInput;
    TextEditor* replaceInput;
    TextButton* findNext;
    TextButton* replaceNextButton;
    TextButton* replaceAllButton;
    Label* label;
    ToggleButton* matchCase;
    Label* label2;
    ComboBox* whereToFindCombo;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLuaMethodFind);
};


#endif   // __JUCER_HEADER_CTRLRLUAMETHODFIND_CTRLRLUAMETHODFIND_4C687B6E__
