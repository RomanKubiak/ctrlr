/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  25 Jul 2011 7:59:52pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRLABEL_CTRLRLABEL_1082F2C2__
#define __JUCER_HEADER_CTRLRLABEL_CTRLRLABEL_1082F2C2__

//[Headers]     -- You can add your own extra header files here --
#include "../CtrlrComponent.h"
#include "CtrlrPanel/CtrlrPanel.h"

class CtrlrLabel;

class CtrlrLabelInternal : public Label
{
	public:
		CtrlrLabelInternal(CtrlrLabel &_owner, const String &componentName=String::empty, const String &labelText=String::empty);
		TextEditor *createEditorComponent();
		bool keyPressed (const KeyPress &key);
	private:
		CtrlrLabel &owner;
};
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrLabel  : public CtrlrComponent,
                    public CtrlrPanel::Listener,
                    public Label::Listener
{
public:
    //==============================================================================
    CtrlrLabel (CtrlrModulator &owner);
    ~CtrlrLabel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	const double getComponentValue();
	const int getComponentMidiValue();
	const double getComponentMaxValue();
	const String getComponentText();
	void setComponentText (const String &componentText);
	const Array<Font> getFontList();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
	void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
	void modulatorChanged (CtrlrModulator *modulatorThatChanged);
	void labelTextChanged (Label* labelThatHasChanged);
	void lookAndFeelChanged ();
	static void wrapForLua(lua_State *L);
	bool keyPressed (const KeyPress &key);
	CtrlrLabel &setLabelText(const String &text);
	CtrlrLabel &appendText(const String &text);
	const String getText();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	Array <int> values;
	WeakReference <CtrlrLuaMethod> labelChangedCbk;
    //[/UserVariables]

    //==============================================================================
    CtrlrLabelInternal* ctrlrLabel;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrLabel (const CtrlrLabel&);
    const CtrlrLabel& operator= (const CtrlrLabel&);
};


#endif   // __JUCER_HEADER_CTRLRLABEL_CTRLRLABEL_1082F2C2__
