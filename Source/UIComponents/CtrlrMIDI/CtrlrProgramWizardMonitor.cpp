/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "stdafx.h"
#include "CtrlrProgramWizard.h"
#include "CtrlrFontManager.h"
//[/Headers]

#include "CtrlrProgramWizardMonitor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
static const String groupBinary(const String in)
{
    String ret;
    for (int i=0; i<in.length(); i+=4)
    {
        ret << in.substring (i, i+4);
        ret << " ";
    }
    return (ret);
}
//[/MiscUserDefs]

//==============================================================================
CtrlrProgramWizardMonitor::CtrlrProgramWizardMonitor (CtrlrProgramWizard &_owner)
    : owner(_owner)
{
    addAndMakeVisible (dataDisplay = new TextEditor (String::empty));
    dataDisplay->setMultiLine (true);
    dataDisplay->setReturnKeyStartsNewLine (false);
    dataDisplay->setReadOnly (true);
    dataDisplay->setScrollbarsShown (true);
    dataDisplay->setCaretVisible (false);
    dataDisplay->setPopupMenuEnabled (true);
    dataDisplay->setColour (TextEditor::textColourId, Colours::white);
    dataDisplay->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    dataDisplay->setColour (TextEditor::highlightColourId, Colours::white);
    dataDisplay->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    dataDisplay->setColour (CaretComponent::caretColourId, Colours::white);
    dataDisplay->setText (TRANS("F0 00 F7"));


    //[UserPreSize]
    dataDisplay->addListener (this);
    dataDisplay->addMouseListener (this, false);

    monoDataFont    = CtrlrFontManager::getBuiltInFont (10);
    monoStatusFont  = CtrlrFontManager::getBuiltInFont (10);
    monoDataFont.setHeight (14.0f);
    monoStatusFont.setHeight (12.0f);
    dataDisplay->applyFontToAllText (monoDataFont);
    //[/UserPreSize]

    setSize (600, 200);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrProgramWizardMonitor::~CtrlrProgramWizardMonitor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    dataDisplay = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrProgramWizardMonitor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xda000000));

    //[UserPaint] Add your own custom painting code here..
    const String str = dataDisplay->getHighlightedText();
    const int dataAsInt = str.getHexValue32();
    AttributedString status;

    status.append ("(int: ", monoStatusFont, Colours::lightgrey);
    status.append (_STR(dataAsInt), monoDataFont, Colours::white);
    status.append (") ", monoStatusFont, Colours::lightgrey);

    if (str.contains(" "))
    {
        const int f = str.upToFirstOccurrenceOf (" ", false, true).getHexValue32();
        const int s = str.fromFirstOccurrenceOf (" ", false, true).getHexValue32();

        BigInteger bi;
        bi.setBitRangeAsInt (0, 7, f);
        bi.setBitRangeAsInt (7, 7, s);
        status.append ("(lsb/msb=int: ", monoDataFont, Colours::lightgrey);
        status.append (_STR(f), monoDataFont, Colours::white);
        status.append ("/"+_STR(s), monoDataFont, Colours::white);
        status.append ("="+_STR(bi.toInteger()),  monoDataFont, Colours::white);
        status.append (")", monoDataFont, Colours::lightgrey);

        bi.setBitRangeAsInt (0, 32, dataAsInt);
        status.append (" (BIN: ", monoDataFont, Colours::lightgrey);
        status.append (groupBinary (bi.toString(2, 4)).trim(), monoDataFont, Colours::white);
        status.append (")", monoDataFont, Colours::lightgrey);
    }

    status.draw (g, Rectangle<float> (8.0f, getHeight() - 16.0f, getWidth() - 16.0f, 16.0f));
    //[/UserPaint]
}

void CtrlrProgramWizardMonitor::resized()
{
    dataDisplay->setBounds (0, 0, getWidth() - 0, getHeight() - 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CtrlrProgramWizardMonitor::mouseMove (const MouseEvent& e)
{
    //[UserCode_mouseMove] -- Add your code here...
    if (e.eventComponent == dataDisplay)
    {
        textEditorTextChanged (*dataDisplay);
    }
    //[/UserCode_mouseMove]
}

void CtrlrProgramWizardMonitor::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    if (e.eventComponent == dataDisplay)
    {
        textEditorTextChanged (*dataDisplay);
    }
    //[/UserCode_mouseDown]
}

void CtrlrProgramWizardMonitor::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
    if (e.eventComponent == dataDisplay)
    {
        textEditorTextChanged (*dataDisplay);
    }
    //[/UserCode_mouseDrag]
}

void CtrlrProgramWizardMonitor::mouseDoubleClick (const MouseEvent& e)
{
    //[UserCode_mouseDoubleClick] -- Add your code here...
    if (e.eventComponent == dataDisplay)
    {
        textEditorTextChanged (*dataDisplay);
    }
    //[/UserCode_mouseDoubleClick]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrProgramWizardMonitor::textEditorTextChanged(TextEditor &editor)
{
    repaint(0,getHeight()-16,getWidth(),16);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrProgramWizardMonitor"
                 componentName="" parentClasses="public Component, public TextEditor::Listener"
                 constructorParams="CtrlrProgramWizard &amp;_owner" variableInitialisers="owner(_owner)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="200">
  <METHODS>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="mouseMove (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDoubleClick (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="da000000"/>
  <TEXTEDITOR name="" id="48e4af2e8f250bc" memberName="dataDisplay" virtualName=""
              explicitFocusOrder="0" pos="0 0 0M 16M" textcol="ffffffff" bkgcol="0"
              hilitecol="ffffffff" shadowcol="0" caretcol="ffffffff" initialText="F0 00 F7"
              multiline="1" retKeyStartsLine="0" readonly="1" scrollbars="1"
              caret="0" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
