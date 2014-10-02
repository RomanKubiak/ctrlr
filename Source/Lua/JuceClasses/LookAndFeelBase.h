#ifndef LOOK_AND_FEEL_BASE
#define LOOK_AND_FEEL_BASE

#include "CtrlrLuaManager.h"
#include "LookAndFeelParamWrapper.h"

class LLookAndFeel;

class LookAndFeelBase : public LookAndFeel_V3
{
	public:
		LookAndFeelBase(LLookAndFeel &_owner) : owner(_owner) {}
		void getIdealPopupMenuItemSize (const String &text, bool isSeparator, int standardMenuItemHeight, int &idealWidth, int &idealHeight);
		void drawRotarySlider (Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider);

        LookAndFeel_V3 v3;

	private:
		LLookAndFeel &owner;
};

#endif
