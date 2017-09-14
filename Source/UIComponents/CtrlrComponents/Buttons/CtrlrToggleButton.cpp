#include "stdafx.h"
#include "CtrlrToggleButton.h"
#include "CtrlrValueMap.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrIDs.h"
#include "CtrlrPanel/CtrlrPanel.h"

CtrlrToggleButton::CtrlrToggleButton (CtrlrModulator &owner)
    : CtrlrComponent(owner),
      ctrlrButton (0)
{
	valueMap = new CtrlrValueMap();
    addAndMakeVisible (ctrlrButton = new ToggleButton ("ctrlrButton"));
    ctrlrButton->setButtonText ("Button");
    ctrlrButton->addListener (this);


    //[UserPreSize]
	ctrlrButton->setBufferedToImage (true);
	setProperty (Ids::uiButtonTextColourOn, "0xff000000");
	setProperty (Ids::uiToggleButtonFocusOutline, "0x00000000");
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
    if (isInternal())
	{
		owner.getOwnerPanel().performInternalComponentFunction(this);
		return;
	}

	if (!owner.getOwnerPanel().checkRadioGroup(this, buttonThatWasClicked->getToggleState()))
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
    CtrlrComponent::mouseDown(e);
    //[/UserCode_mouseDown]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrToggleButton::setComponentValue (const double newValue, const bool sendChangeMessage)
{
	if (!owner.getOwnerPanel().checkRadioGroup(this, ctrlrButton->getToggleState()))
		return;

	if (ctrlrButton->getClickingTogglesState())
	{
		ctrlrButton->setToggleState (newValue ? true : false, dontSendNotification);
	}

	if (sendChangeMessage)
	{
		owner.getProcessor().setValueGeneric (CtrlrModulatorValue(newValue, CtrlrModulatorValue::changedByGUI), true);
	}
}

void CtrlrToggleButton::setComponentMidiValue (const int newValue, const bool sendChangeMessage)
{
	if (!owner.getOwnerPanel().checkRadioGroup(this, ctrlrButton->getToggleState()))
		return;

	if (ctrlrButton->getClickingTogglesState())
	{
		ctrlrButton->setToggleState (valueMap->getIndexForValue(newValue) ? true : false, dontSendNotification);
	}

	if (sendChangeMessage)
	{
		owner.getProcessor().setValueGeneric (CtrlrModulatorValue(newValue, CtrlrModulatorValue::changedByGUI), true);
	}
}

double CtrlrToggleButton::getComponentMaxValue()
{
	return (1);
}

bool CtrlrToggleButton::getToggleState()
{
	return (ctrlrButton->getToggleState());
}

double CtrlrToggleButton::getComponentValue()
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

int CtrlrToggleButton::getComponentMidiValue()
{
	return (valueMap->getMappedValue(ctrlrButton->getToggleState()));
}

void CtrlrToggleButton::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::componentRadioGroupId)
	{
		ctrlrButton->setToggleState (false, dontSendNotification);
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
		valueMap->setPair (0, getProperty(Ids::uiButtonFalseValue), String::empty);
		valueMap->setPair (1, getProperty(Ids::uiButtonTrueValue), String::empty);
		owner.getProcessor().setValueMap (*valueMap);
	}
	else if (property == Ids::uiToggleButtonFocusOutline)
    {
        ctrlrButton->setColour (TextEditor::focusedOutlineColourId, VAR2COLOUR(getProperty(Ids::uiToggleButtonFocusOutline)));
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

bool CtrlrToggleButton::isToggleButton()
{
	return (true);
}

void CtrlrToggleButton::setToggleState(const bool toggleState, const bool sendChangeMessage)
{
	ctrlrButton->setToggleState (toggleState, sendChangeMessage ? sendNotification : dontSendNotification);
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
