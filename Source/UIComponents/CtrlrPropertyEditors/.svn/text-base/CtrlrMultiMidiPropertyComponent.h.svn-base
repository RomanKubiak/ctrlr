#ifndef __CTRLR_MULTI_MIDI_PROPERTY_COMPONENT__
#define __CTRLR_MULTI_MIDI_PROPERTY_COMPONENT__

#include "CtrlrMidiMessage.h"
#include "CtrlrPropertyEditors/CtrlrPropertyComponent.h"

class MultiMidiAlert : public AlertWindow
{
	public:
		MultiMidiAlert ()
			:	AlertWindow (String::empty, "Add a new message to the multi list\n[-1 for parent value setting, -2 for parent number setting. For SysEx message the formula is the same as in the SysEx editor.]", AlertWindow::QuestionIcon, 0),
				valueSlider("Controller Value"), numberSlider("Controller Number")
		{
			const char *types[] = { "CC", "Aftertouch", "ChannelPressure", "NoteOn", "NoteOff", "SysEx", "--", "ProgramChange", "PitchWheel", 0 };
			const char *v[] = { "Direct", "LSB7bit", "MSB7bit", "LSB4bit", "MSB4bit", 0};
			addComboBox ("messageType", StringArray(types), "Midi message type");
			addComboBox ("value", StringArray(v), "Value mapping");
			addComboBox ("number", StringArray(v), "Number mapping");
			addTextEditor ("sysexFormula", "F0 00 F7", "SysEx Formula", false);
			valueSlider.setSize (300,32);
			valueSlider.setSliderStyle (Slider::LinearBar);
			valueSlider.setRange (-2,127,1);
			valueSlider.setValue (-1);

			numberSlider.setSize (300,32);
			numberSlider.setSliderStyle (Slider::LinearBar);
			numberSlider.setRange (-2,127,1);
			numberSlider.setValue (-1);

			addCustomComponent (&numberSlider);
			addCustomComponent (&valueSlider);

			addButton ("OK", 1);
			getComboBoxComponent("messageType")->setSelectedId (1, dontSendNotification);
			getComboBoxComponent("value")->setSelectedId (1, dontSendNotification);
			getComboBoxComponent("number")->setSelectedId (1, dontSendNotification);
		}

		void buttonClicked (Button* button)
		{
			getParentComponent()->exitModalState(1);
		}

		const String getValue()
		{
			String ret;
			ret << getComboBoxComponent("messageType")->getText() + ",";
			ret << getComboBoxComponent("number")->getText() + ",";
			ret << getComboBoxComponent("value")->getText() + ",";
			ret << String (((Slider*)getCustomComponent(0))->getValue()) + ",";
			ret << String (((Slider*)getCustomComponent(1))->getValue()) + ",";
			ret << getTextEditor ("sysexFormula")->getText();
			return (ret);
		}

	private:
		Slider valueSlider, numberSlider;
};

class CtrlrMultiMidiPropertyComponent  : public Component,
                                         public ListBoxModel,
                                         public Label::Listener,
                                         public ButtonListener,
										 public CtrlrPropertyChild 
{
	public:
		CtrlrMultiMidiPropertyComponent (const Value &_valueToControl);
		~CtrlrMultiMidiPropertyComponent();
		void paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected);
		int getNumRows();
		void refresh();
		void loadAdditionalTemplates(const File &templateFile);
		Component *refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate);
		void labelTextChanged (Label* labelThatHasChanged);
		void paint (Graphics& g);
		void resized();
		void buttonClicked (Button* buttonThatWasClicked);
		void mouseDown (const MouseEvent& e);
		void mouseDoubleClick (const MouseEvent& e);

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrMultiMidiPropertyComponent)
		MultiMidiAlert questionWindow;
		StringArray values;
		Value valueToControl;
		StringPairArray templates;
		ImageButton* add;
		ImageButton* remove;
		ListBox* list;
		ImageButton* copy;
		ImageButton* paste;
	    ImageButton* insert;
};


#endif