#ifndef __CTRLR_FONT_PROPERTY_COMPONENT__
#define __CTRLR_FONT_PROPERTY_COMPONENT__

#include "CtrlrPropertyEditors/CtrlrPropertyComponent.h"
class CtrlrPanel;

class CtrlrFontPropertyComponent  : public Component,
                                    public ComboBoxListener,
                                    public ButtonListener,
                                    public SliderListener,
									public CtrlrPropertyChild,
									public LookAndFeel_V3
{
	public:
		CtrlrFontPropertyComponent (const Value &_valueToControl, CtrlrPanel *_owner);
		~CtrlrFontPropertyComponent();
		void refresh();
		Font getFont();
		void resized();
		void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
		void buttonClicked (Button* buttonThatWasClicked);
		void sliderValueChanged (Slider* sliderThatWasMoved);
		Label* createSliderTextBox (Slider& slider);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrFontPropertyComponent);

		class SliderLabelComp : public Label
		{
			public:
				SliderLabelComp() : Label (String::empty, String::empty) {}
				void mouseWheelMove (const MouseEvent&, const MouseWheelDetails&) {}
		};

	private:
		Value valueToControl;
		Font font;
		StringArray choices;
		CtrlrPanel *owner;
		ComboBox* typeface;
		ImageButton* fontBold;
		ImageButton* fontItalic;
		ImageButton* fontUnderline;
		Slider* fontSize,*horizontalScale,*kerning;
};


#endif
