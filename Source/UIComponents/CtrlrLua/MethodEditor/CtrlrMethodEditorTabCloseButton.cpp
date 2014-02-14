#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  28 Aug 2012 11:27:10pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "CtrlrLuaMethodEditor.h"
//[/Headers]

#include "CtrlrMethodEditorTabCloseButton.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrMethodEditorTabCloseButton::CtrlrMethodEditorTabCloseButton (CtrlrLuaMethodEditor &_owner, const int _tabIndex)
    : Button (String::empty),
      owner(_owner), tabIndex(_tabIndex)
{

    //[UserPreSize]
    //[/UserPreSize]

    setSize (24, 24);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrMethodEditorTabCloseButton::~CtrlrMethodEditorTabCloseButton()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrMethodEditorTabCloseButton::resized()
{
    internalPath1.clear();
    internalPath1.startNewSubPath ((float) (proportionOfWidth (0.7000f)), (float) (proportionOfHeight (0.2500f)));
    internalPath1.lineTo ((float) (proportionOfWidth (0.7500f)), (float) (proportionOfHeight (0.3000f)));
    internalPath1.lineTo ((float) (proportionOfWidth (0.3000f)), (float) (proportionOfHeight (0.7500f)));
    internalPath1.lineTo ((float) (proportionOfWidth (0.2500f)), (float) (proportionOfHeight (0.7000f)));
    internalPath1.closeSubPath();

    internalPath2.clear();
    internalPath2.startNewSubPath ((float) (proportionOfWidth (0.3000f)), (float) (proportionOfHeight (0.2500f)));
    internalPath2.lineTo ((float) (proportionOfWidth (0.7500f)), (float) (proportionOfHeight (0.7000f)));
    internalPath2.lineTo ((float) (proportionOfWidth (0.7000f)), (float) (proportionOfHeight (0.7500f)));
    internalPath2.lineTo ((float) (proportionOfWidth (0.2500f)), (float) (proportionOfHeight (0.3000f)));
    internalPath2.closeSubPath();

    internalPath3.clear();
    internalPath3.startNewSubPath ((float) (proportionOfWidth (0.7000f)), (float) (proportionOfHeight (0.2500f)));
    internalPath3.lineTo ((float) (proportionOfWidth (0.7500f)), (float) (proportionOfHeight (0.3000f)));
    internalPath3.lineTo ((float) (proportionOfWidth (0.3000f)), (float) (proportionOfHeight (0.7500f)));
    internalPath3.lineTo ((float) (proportionOfWidth (0.2500f)), (float) (proportionOfHeight (0.7000f)));
    internalPath3.closeSubPath();

    internalPath4.clear();
    internalPath4.startNewSubPath ((float) (proportionOfWidth (0.3000f)), (float) (proportionOfHeight (0.2500f)));
    internalPath4.lineTo ((float) (proportionOfWidth (0.7500f)), (float) (proportionOfHeight (0.7000f)));
    internalPath4.lineTo ((float) (proportionOfWidth (0.7000f)), (float) (proportionOfHeight (0.7500f)));
    internalPath4.lineTo ((float) (proportionOfWidth (0.2500f)), (float) (proportionOfHeight (0.3000f)));
    internalPath4.closeSubPath();

    internalPath5.clear();
    internalPath5.startNewSubPath ((float) (proportionOfWidth (0.7000f)), (float) (proportionOfHeight (0.2500f)));
    internalPath5.lineTo ((float) (proportionOfWidth (0.7500f)), (float) (proportionOfHeight (0.3000f)));
    internalPath5.lineTo ((float) (proportionOfWidth (0.3000f)), (float) (proportionOfHeight (0.7500f)));
    internalPath5.lineTo ((float) (proportionOfWidth (0.2500f)), (float) (proportionOfHeight (0.7000f)));
    internalPath5.closeSubPath();

    internalPath6.clear();
    internalPath6.startNewSubPath ((float) (proportionOfWidth (0.3000f)), (float) (proportionOfHeight (0.2500f)));
    internalPath6.lineTo ((float) (proportionOfWidth (0.7500f)), (float) (proportionOfHeight (0.7000f)));
    internalPath6.lineTo ((float) (proportionOfWidth (0.7000f)), (float) (proportionOfHeight (0.7500f)));
    internalPath6.lineTo ((float) (proportionOfWidth (0.2500f)), (float) (proportionOfHeight (0.3000f)));
    internalPath6.closeSubPath();

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CtrlrMethodEditorTabCloseButton::paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    if (isButtonDown)
    {
        g.setGradientFill (ColourGradient (Colour (0xff9e9e9e),
                                           (float) ((getWidth() / 2)), (float) ((getHeight() / 2)),
                                           Colour (0xffe0e0e0),
                                           (float) (getWidth()), 0.0f,
                                           true));
        g.fillEllipse ((float) (proportionOfWidth (0.0500f)), (float) (proportionOfHeight (0.0500f)), (float) (proportionOfWidth (0.9000f)), (float) (proportionOfHeight (0.9000f)));

        g.setColour (Colour (0xcf000000));
        g.fillPath (internalPath5);

        g.setColour (Colour (0xcf000000));
        g.fillPath (internalPath6);
    }
    else if (isMouseOverButton)
    {
        g.setGradientFill (ColourGradient (Colour (0xffdbdbdb),
                                           (float) ((getWidth() / 2)), (float) ((getHeight() / 2)),
                                           Colour (0xffcfcfcf),
                                           (float) (getWidth()), 0.0f,
                                           true));
        g.fillEllipse ((float) (proportionOfWidth (0.0500f)), (float) (proportionOfHeight (0.0500f)), (float) (proportionOfWidth (0.9000f)), (float) (proportionOfHeight (0.9000f)));

        g.setColour (Colour (0xcf000000));
        g.fillPath (internalPath3);

        g.setColour (Colour (0xcf000000));
        g.fillPath (internalPath4);
    }
    else
    {
        g.setColour (Colour (0xcf000000));
        g.fillPath (internalPath1);

        g.setColour (Colour (0xcf000000));
        g.fillPath (internalPath2);
    }
}

void CtrlrMethodEditorTabCloseButton::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
	Button::mouseDown (e);
	TabBarButton *parent = dynamic_cast<TabBarButton*>(getParentComponent());

	if (parent)
	{
		owner.closeTab (parent->getIndex());
	}
    //[/UserCode_mouseDown]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Button" className="CtrlrMethodEditorTabCloseButton"
                 componentName="" parentClasses="public Button" constructorParams="CtrlrLuaMethodEditor &amp;_owner, const int _tabIndex"
                 variableInitialisers="owner(_owner), tabIndex(_tabIndex)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330000013" fixedSize="1"
                 initialWidth="24" initialHeight="24">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="0" buttonState="normal" enabled="1">
    <PATH pos="0 0 100 100" fill="solid: cf000000" hasStroke="0" nonZeroWinding="1">s 70% 25% l 75% 30% l 30% 75% l 25% 70% x</PATH>
    <PATH pos="0 0 100 100" fill="solid: cf000000" hasStroke="0" nonZeroWinding="1">s 30% 25% l 75% 70% l 70% 75% l 25% 30% x</PATH>
  </BACKGROUND>
  <BACKGROUND backgroundColour="ffffff" buttonState="over" enabled="1">
    <ELLIPSE pos="5% 5% 90% 90%" fill=" radial: 0C 0C, 0R 0, 0=ffdbdbdb, 1=ffcfcfcf"
             hasStroke="0"/>
    <PATH pos="0 0 100 100" fill="solid: cf000000" hasStroke="0" nonZeroWinding="1">s 70% 25% l 75% 30% l 30% 75% l 25% 70% x</PATH>
    <PATH pos="0 0 100 100" fill="solid: cf000000" hasStroke="0" nonZeroWinding="1">s 30% 25% l 75% 70% l 70% 75% l 25% 30% x</PATH>
  </BACKGROUND>
  <BACKGROUND backgroundColour="ffffff" buttonState="down" enabled="1">
    <ELLIPSE pos="5% 5% 90% 90%" fill=" radial: 0C 0C, 0R 0, 0=ff9e9e9e, 1=ffe0e0e0"
             hasStroke="0"/>
    <PATH pos="0 0 100 100" fill="solid: cf000000" hasStroke="0" nonZeroWinding="1">s 70% 25% l 75% 30% l 30% 75% l 25% 70% x</PATH>
    <PATH pos="0 0 100 100" fill="solid: cf000000" hasStroke="0" nonZeroWinding="1">s 30% 25% l 75% 70% l 70% 75% l 25% 30% x</PATH>
  </BACKGROUND>
  <BACKGROUND backgroundColour="0" buttonState="normal on" enabled="0"/>
  <BACKGROUND backgroundColour="0" buttonState="over on" enabled="0"/>
  <BACKGROUND backgroundColour="0" buttonState="down on" enabled="0"/>
  <BACKGROUND backgroundColour="0" buttonState="common background" enabled="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
