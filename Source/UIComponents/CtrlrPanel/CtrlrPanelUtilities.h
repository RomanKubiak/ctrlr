/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  22 Oct 2012 9:09:10pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRPANELUTILITIES_CTRLRPANELUTILITIES_1171006B__
#define __JUCER_HEADER_CTRLRPANELUTILITIES_CTRLRPANELUTILITIES_1171006B__

//[Headers]     -- You can add your own extra header files here --
#include "CtrlrMacros.h"
class CtrlrPanelEditor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrPanelUtilities  : public Component,
                             public ChangeListener
{
public:
    //==============================================================================
    CtrlrPanelUtilities (CtrlrPanelEditor &_owner);
    ~CtrlrPanelUtilities();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void changeListenerCallback (ChangeBroadcaster* source);
	void visibilityChanged();
	void reloadContent();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	CtrlrPanelEditor &owner;
	CodeDocument codeDocument;
	XmlTokeniser xmlTokeniser;
    //[/UserVariables]

    //==============================================================================
    CodeEditorComponent* xmlPreview;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrPanelUtilities);
};


#endif   // __JUCER_HEADER_CTRLRPANELUTILITIES_CTRLRPANELUTILITIES_1171006B__
