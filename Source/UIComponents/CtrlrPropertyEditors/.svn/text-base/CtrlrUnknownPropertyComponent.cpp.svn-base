#include "stdafx.h"
#include "CtrlrUnknownPropertyComponent.h"
#include "CtrlrLog.h"

CtrlrUnknownPropertyComponent::CtrlrUnknownPropertyComponent(const Identifier &_propertyName,
															const ValueTree &_propertyElement,
															const ValueTree &identifier,
															CtrlrPanel *panel,
															StringArray *possibleChoices,
															StringArray *possibleValues) : propertyName(_propertyName), propertyElement(_propertyElement)
{
	l.setColour (Label::backgroundColourId, Colours::white);
	l.setColour (Label::textColourId, Colours::red.brighter());
	l.setText (propertyElement.getProperty(propertyName), dontSendNotification);
	addAndMakeVisible (&l);
}

CtrlrUnknownPropertyComponent::~CtrlrUnknownPropertyComponent()
{
}

void CtrlrUnknownPropertyComponent::resized()
{
	l.setBounds (0, 0, getWidth(), getHeight());
}

void CtrlrUnknownPropertyComponent::refresh()
{
	l.setText (propertyElement.getPropertyAsValue(propertyName, 0).toString(), dontSendNotification);
}
