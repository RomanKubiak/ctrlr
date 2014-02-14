/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  8 Apr 2011 11:10:12pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRBUTTON_CTRLRBUTTON_4EC1070F__
#define __JUCER_HEADER_CTRLRBUTTON_CTRLRBUTTON_4EC1070F__

//[Headers]     -- You can add your own extra header files here --
#include "../CtrlrComponent.h"
#include "CtrlrValueMap.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrButton  : public CtrlrComponent,
                     public ButtonListener,
					 public Timer
{
public:
    //==============================================================================
    CtrlrButton (CtrlrModulator &owner);
    ~CtrlrButton();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	const double getComponentValue();
	const int getComponentMidiValue();
	const double getComponentMaxValue();
	const String getComponentText();
	const bool getToggleState();
	void setComponentText (const String &componentText);
	void buttonContentChanged();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
	void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
	void click();
	const bool isToggleButton();
	void setToggleState(const bool toggleState, const bool sendChangeMessage=false);
	void timerCallback();
	static void wrapForLua(lua_State *L);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void mouseDown (const MouseEvent& e);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	CtrlrValueMap valueMap;
    //[/UserVariables]

    //==============================================================================
    TextButton* ctrlrButton;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrButton (const CtrlrButton&);
    const CtrlrButton& operator= (const CtrlrButton&);
};


#endif   // __JUCER_HEADER_CTRLRBUTTON_CTRLRBUTTON_4EC1070F__
