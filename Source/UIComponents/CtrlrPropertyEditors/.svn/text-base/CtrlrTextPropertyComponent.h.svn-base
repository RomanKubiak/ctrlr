#ifndef __CTRLR_TEXT_PROPERTY_COMPONENT__
#define __CTRLR_TEXT_PROPERTY_COMPONENT__

#include "CtrlrPropertyComponent.h"
#include "CtrlrIDManager.h"

class CtrlrTextPropertyComponent : public Component, public CtrlrPropertyChild
{
	public:
		CtrlrTextPropertyComponent (const Value& _valueToControl, 
									const int maxNumChars, 
									const bool isMultiLine,
									const bool isReadOnly=false);

		~CtrlrTextPropertyComponent();
		void refresh();
		void setText (const String& newText);
		String getText() const;
		void textWasEdited();
		void resized();

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrTextPropertyComponent);

		ScopedPointer<Label> textEditor;
		void createEditor (int maxNumChars, bool isMultiLine);		
		Value valueToControl;
};

#endif