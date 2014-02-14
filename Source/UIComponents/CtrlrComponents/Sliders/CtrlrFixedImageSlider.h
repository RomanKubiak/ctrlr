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

#ifndef __JUCER_HEADER_CTRLRFIXEDIMAGESLIDER_CTRLRFIXEDIMAGESLIDER_73B20E68__
#define __JUCER_HEADER_CTRLRFIXEDIMAGESLIDER_CTRLRFIXEDIMAGESLIDER_73B20E68__

//[Headers]     -- You can add your own extra header files here --
#include "../CtrlrComponent.h"
#include "../CtrlrComponentTypeManager.h"
#include "../CtrlrFilmStripPainter.h"
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
class CtrlrFixedImageSlider  : public CtrlrComponent,
                               public Slider::Listener
{
public:
    //==============================================================================
    CtrlrFixedImageSlider (CtrlrModulator &owner);
    ~CtrlrFixedImageSlider();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void sliderValueChanged (Slider* sliderThatWasMoved);
	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	const double getComponentValue();
	const int getComponentMidiValue();
	const double getComponentMaxValue();
	const String getComponentText();
	void sliderContentChanged();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
	void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
	Image &getFilmStripImage() { return (filmStripImage); }
	const String getTextForValue(const double value);
	void reloadResources(Array <CtrlrPanelResource*> resourcesThatChanged);
	void setResource();
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
	CtrlrValueMap valueMap;
	CtrlrImageSliderLF lf;
	Image filmStripImage;
    //[/UserVariables]

    //==============================================================================
    CtrlrSliderInternal* ctrlrSlider;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrFixedImageSlider (const CtrlrFixedImageSlider&);
    const CtrlrFixedImageSlider& operator= (const CtrlrFixedImageSlider&);
};


#endif   // __JUCER_HEADER_CTRLRFIXEDIMAGESLIDER_CTRLRFIXEDIMAGESLIDER_73B20E68__
