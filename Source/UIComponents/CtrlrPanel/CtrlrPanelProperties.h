/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  14 Nov 2011 4:00:00pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRPANELPROPERTIES_CTRLRPANELPROPERTIES_F06D6A41__
#define __JUCER_HEADER_CTRLRPANELPROPERTIES_CTRLRPANELPROPERTIES_F06D6A41__

//[Headers]     -- You can add your own extra header files here --
#include "CtrlrMacros.h"
class CtrlrPanelEditor;
class CtrlrLookAndFeel;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrPanelProperties  : public Component,
                              public ChangeListener,
                              public ChangeBroadcaster
{
public:
    //==============================================================================
    CtrlrPanelProperties (CtrlrPanelEditor &_owner);
    ~CtrlrPanelProperties();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void changeListenerCallback (ChangeBroadcaster* source);
	void refreshAll();
	void layoutChanged();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



    //==============================================================================
    JUCE_LEAK_DETECTOR(CtrlrPanelProperties)

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	CtrlrPanelEditor &owner;
    //[/UserVariables]

    //==============================================================================
    TabbedComponent* tabbedComponent;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrPanelProperties (const CtrlrPanelProperties&);
    const CtrlrPanelProperties& operator= (const CtrlrPanelProperties&);
};


#endif   // __JUCER_HEADER_CTRLRPANELPROPERTIES_CTRLRPANELPROPERTIES_F06D6A41__
