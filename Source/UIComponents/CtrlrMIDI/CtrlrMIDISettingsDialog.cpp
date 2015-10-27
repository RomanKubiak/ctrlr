/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "stdafx.h"
#include "CtrlrInlineUtilitiesGUI.h"
//[/Headers]

#include "CtrlrMIDISettingsDialog.h"
#include "CtrlrMIDISettingsDevices.h"
#include "CtrlrMIDISettingsRouting.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrMIDISettingsDialog::CtrlrMIDISettingsDialog (CtrlrManager &_owner, Component *_editor)
    : owner(_owner), editor(_editor)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (midiTabs = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    midiTabs->setTabBarDepth (30);
    midiTabs->addTab (TRANS("Devices"), Colours::white, new CtrlrMIDISettingsDevices (owner), true);
    midiTabs->addTab (TRANS("Routing"), Colours::white, new CtrlrMIDISettingsRouting (owner), true);
    midiTabs->setCurrentTabIndex (0);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrMIDISettingsDialog::~CtrlrMIDISettingsDialog()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    midiTabs = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrMIDISettingsDialog::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    drawDefaultWindowBackground (g,getWidth(),getHeight());
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrMIDISettingsDialog::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    midiTabs->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrMIDISettingsDialog::showDialog(CtrlrManager &owner, Component *editor)
{
    DialogWindow::LaunchOptions opts;
    OptionalScopedPointer <Component> dialogContent (new CtrlrMIDISettingsDialog(owner, editor), true);
    opts.content = dialogContent;
    opts.dialogTitle = "MIDI Settings";
    opts.componentToCentreAround = editor;
    opts.dialogBackgroundColour = Colours::white;
    opts.useNativeTitleBar = true;
    opts.useBottomRightCornerResizer = true;
    opts.resizable = true;
    opts.escapeKeyTriggersCloseButton = true;
    opts.runModal();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrMIDISettingsDialog"
                 componentName="" parentClasses="public Component" constructorParams="CtrlrManager &amp;_owner, Component *_editor"
                 variableInitialisers="owner(_owner), editor(_editor)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffff"/>
  <TABBEDCOMPONENT name="" id="d45866974b3b880b" memberName="midiTabs" virtualName=""
                   explicitFocusOrder="0" pos="0 0 0M 0M" orientation="top" tabBarDepth="30"
                   initialTab="0">
    <TAB name="Devices" colour="ffffffff" useJucerComp="1" contentClassName=""
         constructorParams="owner" jucerComponentFile="CtrlrMIDISettingsDevices.cpp"/>
    <TAB name="Routing" colour="ffffffff" useJucerComp="1" contentClassName=""
         constructorParams="owner" jucerComponentFile="CtrlrMIDISettingsRouting.cpp"/>
  </TABBEDCOMPONENT>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
