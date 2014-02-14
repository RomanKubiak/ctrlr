#ifndef CTRLR_MODULATOR_LIST_PROPERTY_H
#define CTRLR_MODULATOR_LIST_PROPERTY_H

#include "CtrlrMidiMessage.h"
#include "CtrlrPropertyEditors/CtrlrPropertyComponent.h"
#include "CtrlrPanel/CtrlrPanel.h"

class CtrlrModulatorListProperty :	public CtrlrPropertyChild, 
									public Component, 
									public ComboBoxListener,
									public CtrlrPanel::Listener
{
	public:
		CtrlrModulatorListProperty (const Value &_valueToControl, CtrlrPanel *_owner);
		~CtrlrModulatorListProperty();
		void refresh();
		void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
		void resized();
		void modulatorChanged (CtrlrModulator *modulatorThatChanged);
		void modulatorAdded (CtrlrModulator *modulatorThatWasAdded);
		void modulatorRemoved (CtrlrModulator *modulatorRemoved);
		void listChanged();

	private:
		CtrlrPanel *owner;
		Value valueToControl;
		StringArray choices;
		ScopedPointer <ComboBox> combo;
		bool numeric;
};

#endif