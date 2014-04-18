#ifndef __CTRLR_TIMESTAMP_PROPERTY__
#define __CTRLR_TIMESTAMP_PROPERTY__

#include "CtrlrPropertyComponent.h"
#include "CtrlrIDManager.h"

class CtrlrTimestampProperty : public Component, public CtrlrPropertyChild
{
	public:
		CtrlrTimestampProperty (const Value& _valueToControl);
		~CtrlrTimestampProperty();
		void refresh();
		void resized();

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrTimestampProperty);
		ScopedPointer<Label> textEditor;
		Value valueToControl;
};

#endif
