/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  20 May 2011 11:32:48pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRLCDLABEL_CTRLRLCDLABEL_980087AF__
#define __JUCER_HEADER_CTRLRLCDLABEL_CTRLRLCDLABEL_980087AF__

//[Headers]     -- You can add your own extra header files here --
#include "../CtrlrComponent.h"
#include "CtrlrPanel/CtrlrPanel.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrLCDLabel  : public CtrlrComponent,
                       public CtrlrPanel::Listener,
					   public Label::Listener
{
public:
    //==============================================================================
    CtrlrLCDLabel (CtrlrModulator &owner);
    ~CtrlrLCDLabel();

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
	static void wrapForLua(lua_State *L);
	CtrlrLCDLabel &setLabelText(const String &text);
	CtrlrLCDLabel &appendText(const String &text);
	const String getText();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	WeakReference <CtrlrLuaMethod> labelChangedCbk;
    //[/UserVariables]

    //==============================================================================
    Label* ctrlrLabel;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrLCDLabel (const CtrlrLCDLabel&);
    const CtrlrLCDLabel& operator= (const CtrlrLCDLabel&);
};


#endif   // __JUCER_HEADER_CTRLRLCDLABEL_CTRLRLCDLABEL_980087AF__
