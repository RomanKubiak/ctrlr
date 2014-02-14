#ifndef __CTRLR_FILE_PROPERTY__
#define __CTRLR_FILE_PROPERTY__

#include "CtrlrPropertyEditors/CtrlrPropertyComponent.h"

class CtrlrFileProperty  : public Component, public Label::Listener, public ButtonListener, public CtrlrPropertyChild
{
	public:
		CtrlrFileProperty (const Value &_valeToControl);
		~CtrlrFileProperty();
		void refresh();
		void resized();
		void buttonClicked (Button* buttonThatWasClicked);
		void labelTextChanged (Label* labelThatHasChanged);

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrFileProperty);
		Value valueToControl;
		Label *path;
		TextButton *browse;
};


#endif
