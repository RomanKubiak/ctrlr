#include "stdafx.h"
#include "CtrlrChoicePropertyComponent.h"
#include "CtrlrMacros.h"
#include "CtrlrLog.h"

CtrlrChoicePropertyComponent::CtrlrChoicePropertyComponent (const Value &_valueToControl, const StringArray *_choices, const Array<var> *_values, const bool _numeric)
    : valueToControl(_valueToControl),
      combo (0),
	  numeric(_numeric)
{
    addAndMakeVisible (combo = new ComboBox (String::empty));
    combo->setEditableText (false);
    combo->setJustificationType (Justification::centredLeft);
    combo->setTextWhenNothingSelected (String::empty);
    combo->setTextWhenNoChoicesAvailable (L"(no choices)");
    combo->addListener (this);

	if (_choices != nullptr)
	{
		choices = *_choices;

		for (int i=0; i<choices.size(); i++)
		{
			combo->addItem (choices[i], i+1);
		}
	}

	if (_values != nullptr)
	{
		values = *_values;

		if (values.size() == 0)
		{
			for (int i=0; i<choices.size(); i++)
			{
				values.add (i);
			}
		}
	}
    setSize (256, 25);

	refresh();
}

CtrlrChoicePropertyComponent::~CtrlrChoicePropertyComponent()
{
}

void CtrlrChoicePropertyComponent::resized()
{
	combo->setBounds (0, 0, getWidth(), getHeight());
}

void CtrlrChoicePropertyComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
	changed();
}

void CtrlrChoicePropertyComponent::refresh()
{
	if (numeric)
	{
		const int i = values.indexOf (valueToControl.toString());
		combo->setSelectedItemIndex (i, sendNotification);
	}
	else
	{
		combo->setText (valueToControl.toString(), sendNotification);
	}
}

void CtrlrChoicePropertyComponent::changed()
{
	if (numeric)
	{
		valueToControl = values[combo->getSelectedItemIndex()];
	}
	else
	{
		valueToControl = combo->getText();
	}
}
