#include "stdafx.h"
#include "CtrlrTimestampProperty.h"

CtrlrTimestampProperty::CtrlrTimestampProperty (const Value& _valueToControl) : valueToControl(_valueToControl)
{
	addAndMakeVisible (textEditor = new Label ());
	textEditor->setColour (Label::backgroundColourId, Colours::white.withAlpha(0.2f));
}

CtrlrTimestampProperty::~CtrlrTimestampProperty()
{
}

void CtrlrTimestampProperty::refresh()
{
	if (textEditor)
	{
		textEditor->setText (Time ((int64)valueToControl.getValue()).formatted("%Y-%m-%d %H:%M:%S"), dontSendNotification);
	}
}

void CtrlrTimestampProperty::resized()
{
	if (textEditor)
		textEditor->setBounds (0,0,getWidth(),getHeight());
}
