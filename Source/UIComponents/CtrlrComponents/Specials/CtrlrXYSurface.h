/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  7 Oct 2011 4:24:16pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRXYSURFACE_CTRLRXYSURFACE_65B5F528__
#define __JUCER_HEADER_CTRLRXYSURFACE_CTRLRXYSURFACE_65B5F528__

//[Headers]     -- You can add your own extra header files here --
#include "../CtrlrComponent.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrIDs.h"
//[/Headers]

#include "CtrlrXYModulator.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrXYSurface  : public CtrlrComponent
{
public:
    //==============================================================================
    CtrlrXYSurface (CtrlrModulator &owner);
    ~CtrlrXYSurface();

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
	void modulatorMoved();
	void syncDestination();
	void allModulatorsInitialized();
	void showPopupMenu();
	const PopupMenu getModulatorListAsMenu(const int startIndex=0, const String &itemToSelect=String::empty);
	const int getValueForPosition(const int position, const bool forX=true);
	const int getPositionForValue(const int value, const bool forX=true);
	void rebuildModulatorList();
	void reloadResources(Array <CtrlrPanelResource*> resourcesThatChanged);
	void setResource();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	Image backgroundImage;
	WeakReference<CtrlrModulator> destinationX, destinationY;
	bool initialized;
	Rectangle<int> usableRectangle;
	StringArray modulatorList;
    //[/UserVariables]

    //==============================================================================
    CtrlrXYModulator* surfaceModulator;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrXYSurface (const CtrlrXYSurface&);
    const CtrlrXYSurface& operator= (const CtrlrXYSurface&);
};


#endif   // __JUCER_HEADER_CTRLRXYSURFACE_CTRLRXYSURFACE_65B5F528__
