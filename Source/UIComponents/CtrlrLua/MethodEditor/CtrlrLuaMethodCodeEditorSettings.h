/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  27 Oct 2012 8:17:44pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRLUAMETHODCODEEDITORSETTINGS_CTRLRLUAMETHODCODEEDITORSETTINGS_FC2CDFB3__
#define __JUCER_HEADER_CTRLRLUAMETHODCODEEDITORSETTINGS_CTRLRLUAMETHODCODEEDITORSETTINGS_FC2CDFB3__

//[Headers]     -- You can add your own extra header files here --
#include "Methods/CtrlrLuaMethod.h"
#include "CtrlrTextEditor.h"
#include "CtrlrWindowManagers/CtrlrChildWindowContent.h"
#include "CtrlrWindowManagers/CtrlrPanelWindowManager.h"
#include "CtrlrLuaCodeTokeniser.h"
#include "CtrlrPropertyEditors/CtrlrColourPropertyComponent.h"
class CtrlrLuaMethodEditor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrLuaMethodCodeEditorSettings  : public Component,
                                          public ChangeListener,
                                          public ComboBoxListener,
                                          public ButtonListener,
                                          public SliderListener
{
public:
    //==============================================================================
    CtrlrLuaMethodCodeEditorSettings (CtrlrLuaMethodEditor &_owner);
    ~CtrlrLuaMethodCodeEditorSettings();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void changeListenerCallback (ChangeBroadcaster* source);
	const Font getFont();
	const Colour getColour();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	CtrlrLuaCodeTokeniser luaTokeniser;
	CodeDocument codeDocument;
	CtrlrLuaMethodEditor &owner;
	Font codeFont;
    //[/UserVariables]

    //==============================================================================
    ComboBox* fontTypeface;
    ToggleButton* fontBold;
    ToggleButton* fontUnderline;
    ToggleButton* fontItalic;
    Slider* fontSize;
    CtrlrColourEditorComponent* bgColour;
    CodeEditorComponent* fontTest;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLuaMethodCodeEditorSettings);
};


#endif   // __JUCER_HEADER_CTRLRLUAMETHODCODEEDITORSETTINGS_CTRLRLUAMETHODCODEEDITORSETTINGS_FC2CDFB3__
