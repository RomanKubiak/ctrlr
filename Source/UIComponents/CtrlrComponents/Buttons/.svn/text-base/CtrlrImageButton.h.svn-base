/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  16 Apr 2011 5:58:35pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRIMAGEBUTTON_CTRLRIMAGEBUTTON_56E3F9F9__
#define __JUCER_HEADER_CTRLRIMAGEBUTTON_CTRLRIMAGEBUTTON_56E3F9F9__

//[Headers]     -- You can add your own extra header files here --
#include "../CtrlrComponent.h"
#include "CtrlrValueMap.h"
//[/Headers]

#include "CtrlrCustomButtonInternal.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrImageButton  : public CtrlrComponent,
                          public SettableTooltipClient,
                          public Button::Listener,
						  public Timer
{
public:
    //==============================================================================
    CtrlrImageButton (CtrlrModulator &owner);
    ~CtrlrImageButton();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	enum ImageButtonMode
	{
		Normal,
		Momentary,
		NormalMouseOver,
		MomentaryMouseOver
	};

	void mouseDown (const MouseEvent &e);
	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	void setComponentMidiValue (const int newValue, const bool sendChangeMessage=false);
	const int getComponentMidiValue();
	const double getComponentValue();
	const double getComponentMaxValue();
	const String getComponentText();
	void buttonContentChanged();
	const Array<int> getResourceList();
	const Array<Font> getFontList();
	const bool getToggleState();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
	void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
	void buttonClicked (Button* button);
	void buttonModeChanged(const ImageButtonMode newMode);
	const ImageButtonMode getButtonMode();
	void click();
	const bool isToggleButton();
	void setToggleState(const bool toggleState, const bool sendChangeMessage=false);
	CtrlrValueMap &getValueMap() { return (valueMap); }
	void timerCallback();
	void reloadResources(Array <CtrlrPanelResource*> resourcesThatChanged);
	void setResource();
	static void wrapForLua(lua_State *L);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	Image filmStripImage;
	CtrlrValueMap valueMap;
    //[/UserVariables]

    //==============================================================================
    CtrlrCustomButtonInternal* ctrlrButton;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrImageButton (const CtrlrImageButton&);
    const CtrlrImageButton& operator= (const CtrlrImageButton&);
};


#endif   // __JUCER_HEADER_CTRLRIMAGEBUTTON_CTRLRIMAGEBUTTON_56E3F9F9__
