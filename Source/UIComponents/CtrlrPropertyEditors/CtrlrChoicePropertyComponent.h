#ifndef __CTRLR_CHOICE_PROPERTY_COMPONENT__
#define __CTRLR_CHOICE_PROPERTY_COMPONENT__

#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrPropertyEditors/CtrlrPropertyComponent.h"

class CtrlrChoicePropertyComponent  : public Component,
                                      public ComboBoxListener,
									  public CtrlrPropertyChild
{
	public:
		CtrlrChoicePropertyComponent (const Value &_valueToControl, const StringArray *_choices, const Array<var> *_values, const bool _numeric);
		~CtrlrChoicePropertyComponent();
		void refresh();
		void resized();
		void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
		void changed();

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrChoicePropertyComponent)
		Value valueToControl;
		Array <var> values;
		StringArray choices;
		ScopedPointer <ComboBox> combo;
		bool numeric;
};


#endif
