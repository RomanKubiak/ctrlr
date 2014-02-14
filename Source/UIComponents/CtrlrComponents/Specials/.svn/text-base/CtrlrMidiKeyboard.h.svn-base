/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  14 Apr 2011 10:26:04pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRMIDIKEYBOARD_CTRLRMIDIKEYBOARD_51983327__
#define __JUCER_HEADER_CTRLRMIDIKEYBOARD_CTRLRMIDIKEYBOARD_51983327__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
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
class CtrlrMidiKeyboard  : public CtrlrComponent,
                           public MidiKeyboardStateListener,
						   public CtrlrPanel::Listener
{
public:
    //==============================================================================
    CtrlrMidiKeyboard (CtrlrModulator &owner);
    ~CtrlrMidiKeyboard();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	const double getComponentValue();
	const int getComponentMidiValue();
	const double getComponentMaxValue();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
	void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
	void handleNoteOn (MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity);
	void handleNoteOff (MidiKeyboardState* source, int midiChannel, int midiNoteNumber);
	void midiReceived(MidiMessage &message);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	MidiKeyboardState keyboardState;
	CtrlrMidiMessage noteOn, noteOff;
    //[/UserVariables]

    //==============================================================================
    MidiKeyboardComponent* midiKeyboard;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrMidiKeyboard (const CtrlrMidiKeyboard&);
    const CtrlrMidiKeyboard& operator= (const CtrlrMidiKeyboard&);
};


#endif   // __JUCER_HEADER_CTRLRMIDIKEYBOARD_CTRLRMIDIKEYBOARD_51983327__
