#ifndef __CTRLR_BUTTON_PROPERTY_COMPONENT__
#define __CTRLR_BUTTON_PROPERTY_COMPONENT__

#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrPropertyEditors/CtrlrPropertyComponent.h"

class CtrlrButtonPropertyComponent : public Component, public Button::Listener, public CtrlrPropertyChild
{
	public:
		CtrlrButtonPropertyComponent (const Value &_valueToControl, const String &_propertyName);
		~CtrlrButtonPropertyComponent();
		void refresh();
		void resized();
		void buttonClicked (Button *button);

	private:
		Value valueToControl;
		String propertyName;
		TextButton button;
};

#endif