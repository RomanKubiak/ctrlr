#ifndef __CTRLR_SLIDER_PROPERTY_COMPONENT__
#define __CTRLR_SLIDER_PROPERTY_COMPONENT__

#include "CtrlrPropertyComponent.h"
#include "CtrlrIDManager.h"

class CtrlrSliderPropertyComponent   : public Component, private SliderListener, public CtrlrPropertyChild
{
	public:
		CtrlrSliderPropertyComponent (const Value &_valueToControl, double rangeMin, double rangeMax, double interval);
		~CtrlrSliderPropertyComponent();
		virtual void setValue (double newValue);
		virtual double getValue() const;
		void refresh();
		void sliderValueChanged (Slider *sliderThatChanged);
		void resized();

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrSliderPropertyComponent);
		Slider slider;
		Value valueToControl;
};


#endif
