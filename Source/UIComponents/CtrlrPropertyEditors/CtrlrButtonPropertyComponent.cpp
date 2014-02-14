#include "stdafx.h"
#include "CtrlrButtonPropertyComponent.h"

CtrlrButtonPropertyComponent::CtrlrButtonPropertyComponent(const Value &_valueToControl, const String &_propertyName)
	: valueToControl(_valueToControl), propertyName(_propertyName)
{
	button.setButtonText (propertyName);
	button.addListener (this);
	addAndMakeVisible (&button);
}

CtrlrButtonPropertyComponent::~CtrlrButtonPropertyComponent()
{
}

void CtrlrButtonPropertyComponent::resized()
{
	button.setBounds (0, 0, getWidth(), getHeight());
}

void CtrlrButtonPropertyComponent::refresh()
{
}

void CtrlrButtonPropertyComponent::buttonClicked (Button *button)
{
	valueToControl = true;
}