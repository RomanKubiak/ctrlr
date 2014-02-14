/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  1 Apr 2012 5:46:28pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRLOGVIEWER_CTRLRLOGVIEWER_DDEA711A__
#define __JUCER_HEADER_CTRLRLOGVIEWER_CTRLRLOGVIEWER_DDEA711A__

//[Headers]     -- You can add your own extra header files here --
#include "CtrlrMacros.h"
#include "CtrlrLog.h"
#include "CtrlrWindowManagers/CtrlrChildWindowContent.h"
class CtrlrManager;
class CtrlrLogViewerTokeniser : public CodeTokeniser
{
	public:
		CtrlrLogViewerTokeniser();
		~CtrlrLogViewerTokeniser();
		int readNextToken (CodeDocument::Iterator& source);
		CodeEditorComponent::ColourScheme getDefaultColourScheme();
		JUCE_LEAK_DETECTOR (CtrlrLogViewerTokeniser);
};
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrLogViewer  : public CtrlrChildWindowContent,
                        public CtrlrLog::Listener
{
public:
    //==============================================================================
    CtrlrLogViewer (CtrlrManager &_owner);
    ~CtrlrLogViewer();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	enum ToolbarItems
	{
		_none,
		clearLog
	};
	void messageLogged (CtrlrLog::CtrlrLogMessage message);
	String getContentName()					{ return ("Log viewer"); }
	uint8 getType()							{ return (CtrlrManagerWindowManager::LogViewer); }
	StringArray getMenuBarNames();
	PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName);
	void menuItemSelected(int menuItemID, int topLevelMenuIndex);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	CtrlrManager &owner;
	CodeDocument logDocument;
	CtrlrLogViewerTokeniser logViewerTokeniser;
    //[/UserVariables]

    //==============================================================================
    CodeEditorComponent* logEditor;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrLogViewer (const CtrlrLogViewer&);
    const CtrlrLogViewer& operator= (const CtrlrLogViewer&);
};


#endif   // __JUCER_HEADER_CTRLRLOGVIEWER_CTRLRLOGVIEWER_DDEA711A__
