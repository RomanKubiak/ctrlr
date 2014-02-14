#ifndef __CTRLR_COMPONENT_TYPE_MANAGER__
#define __CTRLR_COMPONENT_TYPE_MANAGER__

#include "CtrlrIDs.h"
#include "CtrlrModulator/CtrlrModulator.h"

class CtrlrComponent;

class CtrlrComponentTypeManager
{
	public:
		enum CtrlrSliderStyle
		{
			LinearHorizontal=Slider::LinearHorizontal,
			LinearVertical=Slider::LinearVertical,
			LinearBar=Slider::LinearBar,
			Rotary=Slider::Rotary,
			RotaryHorizontalDrag=Slider::RotaryHorizontalDrag,
			RotaryVerticalDrag=Slider::RotaryVerticalDrag,
			IncDecButtons=Slider::IncDecButtons,
			__nCtrlrSliderStyle
		};

		static Slider::SliderStyle sliderTypes[];
		static const MidiKeyboardComponent::Orientation orientationFromString (const String &str);
		static CtrlrComponent *createComponent (const Identifier& uiType, CtrlrModulator &owner);
		static CtrlrComponent *createComponent (const ValueTree &savedState, CtrlrModulator &owner);
		static const Identifier findType (CtrlrComponent *componentToIdentify);
		static const String sliderStyleToString (CtrlrComponentTypeManager::CtrlrSliderStyle style);
		static const CtrlrComponentTypeManager::CtrlrSliderStyle sliderStringToStyle (const String& s);
		static const PopupMenu getComponentMenu(const bool areItemsEnabled=true);
		static const bool isStatic(CtrlrComponent *componentToIdentify);
		static const bool isStatic(const Identifier &guiType);
		static bool isGroupingComponent(CtrlrComponent *componentToCheck);
		static CtrlrComponent *getParentIfGroupped(CtrlrComponent *childComponent);
};

#endif