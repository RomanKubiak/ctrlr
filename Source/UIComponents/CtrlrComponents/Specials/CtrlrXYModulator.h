/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  27 Aug 2011 8:31:26pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRXYMODULATOR_CTRLRXYMODULATOR_F484986D__
#define __JUCER_HEADER_CTRLRXYMODULATOR_CTRLRXYMODULATOR_F484986D__

//[Headers]     -- You can add your own extra header files here --
#include "../CtrlrComponent.h"

class CtrlrXYSurface;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrXYModulator  : public Component
{
public:
    //==============================================================================
    CtrlrXYModulator (CtrlrXYSurface &_owner);
    ~CtrlrXYModulator();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void moved();
    void mouseEnter (const MouseEvent& e);
    void mouseExit (const MouseEvent& e);
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	CtrlrXYSurface &owner;
	ComponentDragger dragger;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrXYModulator (const CtrlrXYModulator&);
    const CtrlrXYModulator& operator= (const CtrlrXYModulator&);
};


#endif   // __JUCER_HEADER_CTRLRXYMODULATOR_CTRLRXYMODULATOR_F484986D__
