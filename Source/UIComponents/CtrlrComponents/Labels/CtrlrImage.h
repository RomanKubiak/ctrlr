/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  7 Mar 2011 10:02:48pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRIMAGE_CTRLRIMAGE_F0F0FB10__
#define __JUCER_HEADER_CTRLRIMAGE_CTRLRIMAGE_F0F0FB10__

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
class CtrlrImage  : public CtrlrComponent
{
public:
    //==============================================================================
    CtrlrImage (CtrlrModulator &owner);
    ~CtrlrImage();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	const double getComponentValue();
	const int getComponentMidiValue();
	const double getComponentMaxValue();
	
	const Array<int> getResourceList();
	void resetSize();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
	void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
	void restoreState (const ValueTree &savedState);
	void reloadResources(Array <CtrlrPanelResource*> resourcesThatChanged);
	void setResource();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	Array <int> values;
	Image currentImage;
	String resourceName;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrImage (const CtrlrImage&);
    const CtrlrImage& operator= (const CtrlrImage&);
};


#endif   // __JUCER_HEADER_CTRLRIMAGE_CTRLRIMAGE_F0F0FB10__
