#include "stdafx.h"
#include "CtrlrModulatorListProperty.h"

CtrlrModulatorListProperty::CtrlrModulatorListProperty(const Value &_valueToControl, CtrlrPanel *_owner) 
	: owner(_owner), valueToControl(_valueToControl)
{
	addAndMakeVisible (combo = new ComboBox (String::empty));
    combo->setEditableText (false);
    combo->setJustificationType (Justification::centredLeft);
    combo->setTextWhenNothingSelected (COMBO_ITEM_NONE);
    combo->setTextWhenNoChoicesAvailable ("No modulators");
    combo->addListener (this);

	listChanged();
}

CtrlrModulatorListProperty::~CtrlrModulatorListProperty()
{
}

void CtrlrModulatorListProperty::resized()
{
	combo->setBounds (0, 0, getWidth(), getHeight());
}

void CtrlrModulatorListProperty::refresh()
{
	if (choices.contains (valueToControl.toString()))
	{
		combo->setColour (ComboBox::textColourId, Colours::black);
	}
	else
	{
		combo->setColour (ComboBox::textColourId, Colours::red);
	}

	combo->setText (valueToControl.toString(), sendNotification);
}

void CtrlrModulatorListProperty::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
	valueToControl = combo->getText();
}

void CtrlrModulatorListProperty::listChanged()
{
	choices.clear();
	choices.add (COMBO_ITEM_NONE);
	combo->addItem (COMBO_ITEM_NONE, 1);

	for (int i=0; i<owner->getModulators().size(); i++)
	{
		choices.add (owner->getModulatorByIndex(i)->getName());
		combo->addItem (owner->getModulatorByIndex(i)->getName(), i+2);
	}

	const String storedModulatorName = valueToControl.toString();

	if (choices.contains (storedModulatorName))
	{
		combo->setColour (ComboBox::textColourId, Colours::black);
		combo->setText (storedModulatorName, sendNotification);
	}
	else
	{
		combo->setColour (ComboBox::textColourId, Colours::red);
		combo->setText (storedModulatorName, dontSendNotification);
	}
}

void CtrlrModulatorListProperty::modulatorChanged (CtrlrModulator *modulatorThatChanged)
{
}

void CtrlrModulatorListProperty::modulatorAdded (CtrlrModulator *modulatorThatWasAdded)
{
	listChanged();
}

void CtrlrModulatorListProperty::modulatorRemoved (CtrlrModulator *modulatorRemoved)
{
	listChanged();
}