/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  11 Aug 2011 9:18:09pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRHYPERLINK_CTRLRHYPERLINK_843BD87D__
#define __JUCER_HEADER_CTRLRHYPERLINK_CTRLRHYPERLINK_843BD87D__

//[Headers]     -- You can add your own extra header files here --
#include "../CtrlrComponent.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrHyperlink  : public CtrlrComponent,
                        public ButtonListener
{
public:
    //==============================================================================
    CtrlrHyperlink (CtrlrModulator &owner);
    ~CtrlrHyperlink();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	const double getComponentValue();
	const int getComponentMidiValue();
	const double getComponentMaxValue();
	const String getComponentText();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
	void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    HyperlinkButton* hyperlinkButton;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrHyperlink (const CtrlrHyperlink&);
    const CtrlrHyperlink& operator= (const CtrlrHyperlink&);
};


#endif   // __JUCER_HEADER_CTRLRHYPERLINK_CTRLRHYPERLINK_843BD87D__
