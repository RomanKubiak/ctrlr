#include "stdafx.h"
#include "CtrlrBooleanPropertyComponent.h"

CtrlrBooleanPropertyComponent::CtrlrBooleanPropertyComponent (const Value& _valueToControl, const String& _stateText)
    : valueToControl(_valueToControl), stateText(_stateText)
{
	if (stateText.contains ("/"))
	{
		onText	= stateText.upToFirstOccurrenceOf ("/", false, false);
		offText	= stateText.fromFirstOccurrenceOf ("/", false, false);
	}
	else
	{
		onText = offText = stateText;
	}

    addAndMakeVisible (&button);
	button.addListener (this);
    button.setClickingTogglesState (false);
    button.setButtonText (offText);
    button.setClickingTogglesState (true);
	button.setToggleState (valueToControl.getValue(), dontSendNotification);
}

CtrlrBooleanPropertyComponent::~CtrlrBooleanPropertyComponent()
{
}

void CtrlrBooleanPropertyComponent::paint (Graphics& g)
{
    g.setColour (Colours::white);
    g.fillRect (button.getBounds());

    g.setColour (findColour (ComboBox::outlineColourId));
    g.drawRect (button.getBounds());
}

void CtrlrBooleanPropertyComponent::refresh()
{
	button.setToggleState (button.getToggleState(), dontSendNotification);
	button.setButtonText (button.getToggleState() ? onText : offText);
}

void CtrlrBooleanPropertyComponent::resized()
{
	button.setBounds (0, 0, getWidth(), getHeight());
}

void CtrlrBooleanPropertyComponent::buttonClicked (Button*)
{
	button.setButtonText (button.getToggleState() ? onText : offText);
	valueToControl = button.getToggleState();
}
