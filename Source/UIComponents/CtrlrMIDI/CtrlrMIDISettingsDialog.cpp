/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 4.0.2

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "stdafx.h"
#include "CtrlrInlineUtilitiesGUI.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
//[/Headers]

#include "CtrlrMIDISettingsDialog.h"
#include "CtrlrMIDISettingsDevices.h"
#include "CtrlrMIDISettingsRouting.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrMIDISettingsDialog::CtrlrMIDISettingsDialog (CtrlrPanel &_owner)
    : owner(_owner)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (midiTabs = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    midiTabs->setTabBarDepth (30);
    midiTabs->addTab (TRANS("Devices"), Colour (0xa2d2d2d2), new CtrlrMIDISettingsDevices (owner), true);
    midiTabs->addTab (TRANS("Routing"), Colour (0xa1d2d2d2), new CtrlrMIDISettingsRouting (owner), true);
    midiTabs->setCurrentTabIndex (0);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (500, 500);


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

void CtrlrMIDISettingsDialog::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    midiTabs->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrMIDISettingsDialog::showDialog(CtrlrPanel &_owner)
{
    DialogWindow::LaunchOptions opts;
    auto* dialogContent = new CtrlrMIDISettingsDialog(_owner);
    opts.content.setOwned(dialogContent);
    opts.dialogTitle = "MIDI Settings";
    opts.componentToCentreAround = dynamic_cast<Component*>(_owner.getEditor());
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
                 componentName="" parentClasses="public CtrlrChildWindowContent"
                 constructorParams="CtrlrPanel &amp;_owner" variableInitialisers="owner(_owner)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="500" initialHeight="500">
  <BACKGROUND backgroundColour="ffffff"/>
  <TABBEDCOMPONENT name="" id="d45866974b3b880b" memberName="midiTabs" virtualName=""
                   explicitFocusOrder="0" pos="0 0 0M 0M" orientation="top" tabBarDepth="30"
                   initialTab="0">
    <TAB name="Devices" colour="a2d2d2d2" useJucerComp="1" contentClassName=""
         constructorParams="owner" jucerComponentFile="CtrlrMIDISettingsDevices.cpp"/>
    <TAB name="Routing" colour="a1d2d2d2" useJucerComp="1" contentClassName=""
         constructorParams="owner" jucerComponentFile="CtrlrMIDISettingsRouting.cpp"/>
  </TABBEDCOMPONENT>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
