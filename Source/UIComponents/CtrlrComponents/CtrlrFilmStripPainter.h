#ifndef __CTRLR_FILM_STRIP_PAINTER__
#define __CTRLR_FILM_STRIP_PAINTER__

#include "CtrlrComponent.h"

class CtrlrFilmStripPainter;

class CtrlrFilmStripPainter
{
	public:
		CtrlrFilmStripPainter(const Image imageToSet=Image::null, const int frameWidth=-1, const int frameHeight=-1);
		~CtrlrFilmStripPainter();
		void setImage (const Image imageToSet, const int _frameWidth, const int _frameHeight);
		const int getMaxValue()																							{ return (maxValue); }
		const Rectangle<int> getCoords(const int value)																	{ return (possibleValues[value]); }
		void paint(Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider);
		void paint(Graphics &g, ToggleButton &button, bool isMouseOverButton, bool isButtonDown);
		void paint(Graphics &g, Button &button, bool isMouseOverButton, bool isButtonDown);
		Rectangle<int> getCoordsForValue(Slider& slider);
		Rectangle<int> getCoordsForValue(const bool value);
		void setPaintMode(const RectanglePlacement _paintMode);
		void setOrientation (const bool _isVertical)																	{ isVertical = _isVertical; }
		const bool getOrientation()																						{ return (isVertical); }

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrFilmStripPainter)
		Image filmStripImage;
		Array <Rectangle<int> > possibleValues;
		int frameWidth;
		int frameHeight;
		int maxValue;
		RectanglePlacement paintMode;
		bool isVertical;
};

class CtrlrImageSliderLF : public CtrlrFilmStripPainter, public LookAndFeel_V2
{
	public:
		CtrlrImageSliderLF(CtrlrComponent &_owner);
		void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider);
		void drawLinearSlider (Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &slider);
		void drawLinearSliderBackground (Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &slider);
		void drawLinearSliderThumb (Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &slider);
		Label *createSliderTextBox (Slider &slider);

		JUCE_LEAK_DETECTOR(CtrlrImageSliderLF)

	private:
		CtrlrComponent &owner;
};

class CtrlrImageToggleButton : public CtrlrFilmStripPainter, public LookAndFeel
{
	public:
		CtrlrImageToggleButton(CtrlrComponent &_owner);
		void setImage (const Image image, const int frameWidth, const int frameHeight);
		void drawToggleButton (Graphics &g, ToggleButton &button, bool isMouseOverButton, bool isButtonDown);

		JUCE_LEAK_DETECTOR(CtrlrImageToggleButton)

	private:
		CtrlrComponent &owner;
};
#endif