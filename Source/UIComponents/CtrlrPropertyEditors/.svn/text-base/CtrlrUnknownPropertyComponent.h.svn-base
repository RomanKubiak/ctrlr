#ifndef __CTRLR_UNKNOWN_PROPERTY_COMPONENT__
#define __CTRLR_UNKNOWN_PROPERTY_COMPONENT__

#include "CtrlrPropertyComponent.h"
#include "CtrlrIDManager.h"

class CtrlrUnknownPropertyComponent : public Component, public CtrlrPropertyChild
{
	public:
		CtrlrUnknownPropertyComponent(const Identifier &_propertyName, 
										const ValueTree &_propertyElement, 
										const ValueTree &identifier,
										CtrlrPanel *panel=nullptr, 
										StringArray *possibleChoices=nullptr, 
										StringArray *possibleValues=nullptr);
		~CtrlrUnknownPropertyComponent();
		void resized();
		void refresh();

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrUnknownPropertyComponent);
		Label l;
		Identifier propertyName;
		ValueTree propertyElement;
};

#endif