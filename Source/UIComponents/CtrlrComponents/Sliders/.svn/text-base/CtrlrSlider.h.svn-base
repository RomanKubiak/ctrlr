#ifndef __CTRLR_SLIDER__
#define __CTRLR_SLIDER__

#include "../CtrlrComponent.h"
#include "CtrlrSliderInternal.h"

class CtrlrSlider  : public CtrlrComponent,
                     public SettableTooltipClient,
                     public SliderListener
{
	public:
		CtrlrSlider (CtrlrModulator &owner);
		~CtrlrSlider();
		void paint(Graphics &g) {}
		void setComponentValue (const double newValue, const bool sendChangeMessage=false);
		const double getComponentValue();
		const int getComponentMidiValue();
		const double getComponentMaxValue();
		const String getComponentText();
		const Array<Font> getFontList();
		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
		void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
		void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
		void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
		void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
		Slider &getOwnedSlider() { return (ctrlrSlider); }
		static void wrapForLua(lua_State *L);
		void resized();
		void sliderValueChanged (Slider* sliderThatWasMoved);
		void mouseUp (const MouseEvent& e);
		void mouseDoubleClick (const MouseEvent& e);
		JUCE_LEAK_DETECTOR(CtrlrSlider)

	private:
		CtrlrSliderLookAndFeel lf;
		CtrlrSliderInternal ctrlrSlider;
};


#endif
