#ifndef __CTRLR_BOOLEAN_PROPERTY_COMPONENT__
#define __CTRLR_BOOLEAN_PROPERTY_COMPONENT__

#include "CtrlrPropertyComponent.h"

class CtrlrBooleanPropertyComponent : public Component, public Button::Listener, public CtrlrPropertyChild
{
	public:
		CtrlrBooleanPropertyComponent (const Value& _valueToControl, const String& _stateText);
		~CtrlrBooleanPropertyComponent();
		void paint (Graphics& g);
		void refresh();
		void resized();
	    void buttonClicked (Button*);
	
	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrBooleanPropertyComponent);

		Value valueToControl;
		ToggleButton button;
		String onText,offText;
		String stateText;
};

#endif