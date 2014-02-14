#ifndef __CTRLR_SLIDER_INTERNAL__
#define __CTRLR_SLIDER_INTERNAL__

#include "../CtrlrComponentTypeManager.h"
#include "CtrlrMacros.h"
#include "CtrlrUtilities.h"
#include "CtrlrPanel/CtrlrPanel.h"

class CtrlrSliderInternal : public Slider
{
	public:
		CtrlrSliderInternal (CtrlrComponent &_owner);
		~CtrlrSliderInternal();
		String getTextFromValue(double value);
		void mouseWheelMove (const MouseEvent &e, const MouseWheelDetails& wheel);

	private:
		CtrlrComponent &owner;
};

class CtrlrSliderLookAndFeel : public LookAndFeel_V2
{
	public:
		CtrlrSliderLookAndFeel(CtrlrComponent &_owner, ValueTree &_ownerTree) : ownerTree(_ownerTree), owner(_owner)
		{
		}

		Button *createSliderButton (Slider&, bool isIncrement)
		{
			TextButton *tb = new TextButton (isIncrement ? "+" : "-", String::empty);
			tb->setLookAndFeel (&LookAndFeel::getDefaultLookAndFeel());
			tb->setColour (TextButton::buttonColourId, VAR2COLOUR(ownerTree.getProperty(Ids::uiSliderIncDecButtonColour)));
			tb->setColour (TextButton::textColourOffId, VAR2COLOUR(ownerTree.getProperty(Ids::uiSliderIncDecTextColour)));
			return (tb);
		}

		Label* createSliderTextBox (Slider& slider)
		{
			Label* const l = new Label();
			l->setFont(owner.getOwner().getOwner().getOwner().getFontManager().getFontFromString (ownerTree.getProperty(Ids::uiSliderValueFont)));
			l->setJustificationType (justificationFromProperty(ownerTree.getProperty(Ids::uiSliderValueTextJustification)));
			l->setColour (Label::textColourId, slider.findColour (Slider::textBoxTextColourId));
			l->setColour (Label::backgroundColourId, (slider.getSliderStyle() == Slider::LinearBar) ? Colours::transparentBlack : slider.findColour (Slider::textBoxBackgroundColourId));
			l->setColour (Label::outlineColourId, slider.findColour (Slider::textBoxOutlineColourId));
			l->setColour (TextEditor::textColourId, slider.findColour (Slider::textBoxTextColourId));
			l->setColour (TextEditor::backgroundColourId, slider.findColour (Slider::textBoxBackgroundColourId).withAlpha (slider.getSliderStyle() == Slider::LinearBar ? 0.7f : 1.0f));
			l->setColour (TextEditor::outlineColourId, slider.findColour (Slider::textBoxOutlineColourId));
			return l;
		}

		Colour createBaseColour (const Colour& buttonColour, const bool hasKeyboardFocus, const bool isMouseOverButton, const bool isButtonDown) noexcept
		{
			const float sat = hasKeyboardFocus ? 1.3f : 0.9f;
			const Colour baseColour (buttonColour.withMultipliedSaturation (sat));

			if (isButtonDown)
	            return baseColour.contrasting (0.2f);
			else if (isMouseOverButton)
	            return baseColour.contrasting (0.1f);

			return baseColour;
		}

		int getSliderThumbRadius (Slider& slider)
		{
			return jmin (7,slider.getHeight() / 2,slider.getWidth() / 2) + 2;
		}
		Colour findColour (int colourId) const noexcept;
		int getSliderPopupPlacement(Slider &);
		Font getSliderPopupFont(Slider &);
		void drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height, float /*sliderPos*/, float /*minSliderPos*/, float /*maxSliderPos*/, const Slider::SliderStyle /*style*/, Slider& slider);
		void drawLinearSliderThumb (Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider);

	private:
		ValueTree &ownerTree;
		CtrlrComponent &owner;
};

#endif
