/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  8 Jun 2011 12:42:47am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRFIXEDSLIDER_CTRLRFIXEDSLIDER_AD4513E7__
#define __JUCER_HEADER_CTRLRFIXEDSLIDER_CTRLRFIXEDSLIDER_AD4513E7__

//[Headers]     -- You can add your own extra header files here --
#include "../CtrlrComponent.h"
#include "CtrlrSliderInternal.h"
#include "CtrlrValueMap.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrFixedSlider  : public CtrlrComponent,
                          public SettableTooltipClient,
                          public Slider::Listener
{
public:
    //==============================================================================
    CtrlrFixedSlider (CtrlrModulator &owner);
    ~CtrlrFixedSlider();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void sliderValueChanged (Slider* sliderThatWasMoved);
	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	const double getComponentValue();
	const int getComponentMidiValue();
	const double getComponentMaxValue();
	const String getComponentText();
	void sliderContentChanged();
	const String getTextForValue(const double value);
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
	void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}

	Slider *getOwnedSlider() { return (ctrlrSlider); }
	static void wrapForLua(lua_State *L);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void mouseUp (const MouseEvent& e);
    void mouseDoubleClick (const MouseEvent& e);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	CtrlrSliderLookAndFeel lf;
	CtrlrValueMap valueMap;
    //[/UserVariables]

    //==============================================================================
    CtrlrSliderInternal* ctrlrSlider;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrFixedSlider (const CtrlrFixedSlider&);
    const CtrlrFixedSlider& operator= (const CtrlrFixedSlider&);
};


#endif   // __JUCER_HEADER_CTRLRFIXEDSLIDER_CTRLRFIXEDSLIDER_AD4513E7__
