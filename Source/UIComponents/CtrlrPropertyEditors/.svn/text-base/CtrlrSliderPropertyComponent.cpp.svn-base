#include "stdafx.h"
#include "CtrlrSliderPropertyComponent.h"

CtrlrSliderPropertyComponent::CtrlrSliderPropertyComponent (const Value &_valueToControl, double rangeMin, double rangeMax, double interval)
	: valueToControl(_valueToControl)
{
    addAndMakeVisible (&slider);
    slider.setRange (rangeMin, rangeMax, interval);
    slider.setSliderStyle (Slider::LinearBar);
    slider.getValueObject().referTo (valueToControl);
}

CtrlrSliderPropertyComponent::~CtrlrSliderPropertyComponent()
{
}

void CtrlrSliderPropertyComponent::setValue (const double newValue)
{
}

double CtrlrSliderPropertyComponent::getValue() const
{
    return slider.getValue();
}

void CtrlrSliderPropertyComponent::refresh()
{
	slider.setValue (getValue(), dontSendNotification);
}

void CtrlrSliderPropertyComponent::sliderValueChanged (Slider *sliderThatChanged)
{
    if (getValue() != slider.getValue())
        setValue (slider.getValue());
}

void CtrlrSliderPropertyComponent::resized()
{
	slider.setBounds (0, 0, getWidth(), getHeight());
}
