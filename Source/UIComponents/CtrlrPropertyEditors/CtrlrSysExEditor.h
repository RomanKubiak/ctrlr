#ifndef CTRLR_SYSEX_EDITOR_H
#define CTRLR_SYSEX_EDITOR_H

#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrUtilities.h"

class SysExRow : public Component
{
	public:
		SysExRow(const int _n=1, const int _w=32, const int _gap=4);
		void paint (Graphics &g);
		void resized();

	private:
		int n,w,gap;
};

class CtrlrSysExEditor  : public Component,
                          public SliderListener,
                          public LabelListener,
                          public ChangeBroadcaster
{
	public:
		CtrlrSysExEditor (Value &_val, CtrlrPanel *_panel);
		~CtrlrSysExEditor();
		void setLength (const int newLength);
		Label *addByte(const String &byteAsString);
		const String getValue();
		const PopupMenu getVendorIdMenu();
		void paint (Graphics& g);
		void resized();
		void sliderValueChanged (Slider* sliderThatWasMoved);
		void labelTextChanged (Label* labelThatHasChanged);
		void mouseDown (const MouseEvent& e);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrSysExEditor)

	private:
		Value val;
		CtrlrPanel *owner;
		StringArray splitMessage;
		OwnedArray <Label> byteValueLabels;
		OwnedArray <SysExRow> rows;
		int currentMessageLength;
		Slider* messageLength;
		Label* label;

};


#endif
