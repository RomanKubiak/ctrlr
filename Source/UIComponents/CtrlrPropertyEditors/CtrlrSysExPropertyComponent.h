#ifndef CTRLR_SYSEX_PROPERTY_COMPONENT_H
#define CTRLR_SYSEX_PROPERTY_COMPONENT_H

#include "JuceHeader.h"
#include "CtrlrMidiMessage.h"
#include "CtrlrPropertyEditors/CtrlrPropertyComponent.h"

class CtrlrSysExPropertyComponent  : public Component,
                                     public LabelListener,
                                     public ButtonListener,
									 public CtrlrPropertyChild,
									 public ChangeListener
{
	public:
		CtrlrSysExPropertyComponent (const Value &_valueToControl, const ValueTree &_propertyTree, const Identifier &_propertyName, CtrlrPanel *_owner);
		~CtrlrSysExPropertyComponent();
		void refresh();
		void resized();
		void labelTextChanged (Label* labelThatHasChanged);
		void buttonClicked (Button* buttonThatWasClicked);
		void changeListenerCallback (ChangeBroadcaster *cb);
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrSysExPropertyComponent)

	private:
		Value valueToControl;
		Label* sysexPreview;
		TextButton* editButton;
		ImageButton* copy;
		ImageButton* paste;
		ValueTree propertyTree;
		Identifier propertyName;
		CtrlrPanel *owner;
};


#endif
