#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  8 Apr 2011 11:10:07pm

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
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrModulator/CtrlrModulatorProcessor.h"
#include "CtrlrLog.h"
//[/Headers]

#include "CtrlrToggleButton.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrToggleButton::CtrlrToggleButton (CtrlrModulator &owner)
    : CtrlrComponent(owner),
      ctrlrButton (0)
{
    addAndMakeVisible (ctrlrButton = new ToggleButton ("ctrlrButton"));
    ctrlrButton->setButtonText ("Button");
    ctrlrButton->addListener (this);


    //[UserPreSize]
	setProperty (Ids::uiButtonTextColourOn, "0xff000000");
	setProperty (Ids::uiToggleButtonText, "Button");
	setProperty (Ids::uiButtonTrueValue, 1);
	setProperty (Ids::uiButtonFalseValue, 0);
	setProperty (Ids::uiButtonColourOff, "0xff0000ff");
	owner.setProperty (Ids::modulatorMax, 1);
	owner.setProperty (Ids::modulatorMin, 0);
    //[/UserPreSize]

    setSize (88, 32);

    //[Constructor] You can add your own custom stuff here..
	//owner.getProcessor().setValueFromGUI (0, true);
    //[/Constructor]
}

CtrlrToggleButton::~CtrlrToggleButton()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (ctrlrButton);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrToggleButton::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrToggleButton::resized()
{
    ctrlrButton->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CtrlrToggleButton::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
	if (!owner.getOwner().checkRadioGroup(this, buttonThatWasClicked->getToggleState()))
		return;
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == ctrlrButton)
    {
        //[UserButtonCode_ctrlrButton] -- add your button handler code here..
		setComponentValue (ctrlrButton->getToggleState(), true);
        //[/UserButtonCode_ctrlrButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void CtrlrToggleButton::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    //[/UserCode_mouseDown]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrToggleButton::setComponentValue (const double newValue, const bool sendChangeMessage)
{
	if (!owner.getOwner().checkRadioGroup(this, ctrlrButton->getToggleState()))
		return;

	if (ctrlrButton->getClickingTogglesState())
	{
		ctrlrButton->setToggleState (newValue ? true : false, false);
	}

	if (sendChangeMessage)
	{
		owner.getProcessor().setValueFromGUI (newValue, true);
	}
}

void CtrlrToggleButton::setComponentMidiValue (const int newValue, const bool sendChangeMessage)
{
	if (!owner.getOwner().checkRadioGroup(this, ctrlrButton->getToggleState()))
		return;

	if (ctrlrButton->getClickingTogglesState())
	{
		ctrlrButton->setToggleState (valueMap.getIndexForValue(newValue) ? true : false, false);
	}

	if (sendChangeMessage)
	{
		owner.getProcessor().setValueFromGUI (newValue, true);
	}
}

const double CtrlrToggleButton::getComponentMaxValue()
{
	return (1);
}

const bool CtrlrToggleButton::getToggleState()
{
	return (ctrlrButton->getToggleState());
}

const double CtrlrToggleButton::getComponentValue()
{
	if (ctrlrButton->getToggleState())
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

const int CtrlrToggleButton::getComponentMidiValue()
{
	return (valueMap.getMappedValue(ctrlrButton->getToggleState()));
}

void CtrlrToggleButton::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::componentRadioGroupId)
	{
		ctrlrButton->setToggleState (false, false);
	}

	if (property == Ids::uiButtonTextColourOn
		|| property == Ids::uiButtonColourOff)
	{
		ctrlrButton->setColour (ToggleButton::textColourId, VAR2COLOUR(getProperty(Ids::uiButtonTextColourOn)));
		ctrlrButton->setColour (TextButton::buttonColourId, VAR2COLOUR(getProperty(Ids::uiButtonColourOff)));
	}
	else if (property == Ids::uiToggleButtonText)
	{
		ctrlrButton->setButtonText (getProperty(Ids::uiToggleButtonText));
	}
	else if (property == Ids::uiButtonTrueValue || property == Ids::uiButtonFalseValue)
	{
		valueMap.setPair (0, getProperty(Ids::uiButtonFalseValue), String::empty);
		valueMap.setPair (1, getProperty(Ids::uiButtonTrueValue), String::empty);
		owner.getProcessor().setValueMap (valueMap);
	}
	else
	{
		CtrlrComponent::valueTreePropertyChanged(treeWhosePropertyHasChanged, property);
	}

	if (restoreStateInProgress == false)
	{
		resized();
	}
}

void CtrlrToggleButton::click()
{
	ctrlrButton->triggerClick();
}

const bool CtrlrToggleButton::isToggleButton()
{
	return (true);
}

void CtrlrToggleButton::setToggleState(const bool toggleState, const bool sendChangeMessage)
{
	ctrlrButton->setToggleState (toggleState, sendChangeMessage);
}

void CtrlrToggleButton::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrToggleButton, bases<CtrlrComponent,CtrlrLuaObject> >("CtrlrToggleButton")
			.def("getToggleState", &CtrlrToggleButton::getToggleState)
			.def("setToggleState", &CtrlrToggleButton::setToggleState)
	];
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrToggleButton" componentName=""
                 parentClasses="public CtrlrComponent" constructorParams="CtrlrModulator &amp;owner"
                 variableInitialisers="CtrlrComponent(owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="88"
                 initialHeight="32">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffff"/>
  <TOGGLEBUTTON name="ctrlrButton" id="ece5e33c201d706e" memberName="ctrlrButton"
                virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" buttonText="Button"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
