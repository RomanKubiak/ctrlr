/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  2 Oct 2012 4:05:42pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRLUAMETHODEDITAREA_CTRLRLUAMETHODEDITAREA_1E6E329B__
#define __JUCER_HEADER_CTRLRLUAMETHODEDITAREA_CTRLRLUAMETHODEDITAREA_1E6E329B__

//[Headers]     -- You can add your own extra header files here --
#include "CtrlrLuaMethodEditorTabs.h"
#include "CtrlrLuaMethodFind.h"
#include "CtrlrTextEditor.h"
#include "CtrlrLuaMethodCodeEditor.h"

class CtrlrLuaMethodEditor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrLuaMethodEditArea  : public Component,
                                public CtrlrLog::Listener
{
public:
    //==============================================================================
    CtrlrLuaMethodEditArea (CtrlrLuaMethodEditor &_owner);
    ~CtrlrLuaMethodEditArea();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	CtrlrLuaMethodEditorTabs *getTabs();
	TabbedComponent *getLowerTabs();
	void insertOutput(const String &textToInsert, const Colour what);
	void insertOutput(const AttributedString stringToInsert);
	void showFindDialog();
	void findNextMatch();
	void replaceNextMatch();
	void closeTabWithMethod(const ValueTree &item);
	void messageLogged (CtrlrLog::CtrlrLogMessage message);
	void mouseDoubleClick (const MouseEvent &e);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	CtrlrLuaMethodEditor &owner;
	StretchableLayoutManager layoutManager;
	StretchableLayoutResizerBar *resizer;
	CtrlrTextEditor *output;
	CtrlrLuaMethodFind *find;
    //[/UserVariables]

    //==============================================================================
    TabbedComponent* lowerTabs;
    CtrlrLuaMethodEditorTabs* upperTabs;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLuaMethodEditArea);
};


#endif   // __JUCER_HEADER_CTRLRLUAMETHODEDITAREA_CTRLRLUAMETHODEDITAREA_1E6E329B__
