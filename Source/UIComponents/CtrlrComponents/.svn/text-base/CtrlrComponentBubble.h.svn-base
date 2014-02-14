/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  8 Jun 2011 12:39:27am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRCOMPONENTBUBBLE_CTRLRCOMPONENTBUBBLE_5899BF48__
#define __JUCER_HEADER_CTRLRCOMPONENTBUBBLE_CTRLRCOMPONENTBUBBLE_5899BF48__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
class CtrlrComponent;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrComponentBubble  : public Component,
                              public LabelListener,
							  public ValueTree::Listener,
							  public KeyListener
{
public:
    //==============================================================================
    CtrlrComponentBubble (CtrlrComponent &_owner);
    ~CtrlrComponentBubble();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void show();
	Label &getValueLabel();
	Label &getNameLabel();
	void mouseDoubleClick(const MouseEvent& e);
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
	void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
	bool keyPressed (const KeyPress& key, Component* originatingComponent);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void labelTextChanged (Label* labelThatHasChanged);
    void mouseDown (const MouseEvent& e);


    //==============================================================================
    JUCE_LEAK_DETECTOR(CtrlrComponentBubble)

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	CtrlrComponent &owner;
    //[/UserVariables]

    //==============================================================================
    Label* value;
    Label* name;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrComponentBubble (const CtrlrComponentBubble&);
    const CtrlrComponentBubble& operator= (const CtrlrComponentBubble&);
};


#endif   // __JUCER_HEADER_CTRLRCOMPONENTBUBBLE_CTRLRCOMPONENTBUBBLE_5899BF48__
