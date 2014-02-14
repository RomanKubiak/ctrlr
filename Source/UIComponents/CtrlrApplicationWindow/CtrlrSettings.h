#ifndef __CTRLR_SETTINGS__
#define __CTRLR_SETTINGS__

#include "CtrlrManager/CtrlrManager.h"


class CtrlrSettings  : public Component
{
	public:
		CtrlrSettings (CtrlrManager &_owner);
		~CtrlrSettings();
		void paint (Graphics& g);
		void resized();
		JUCE_LEAK_DETECTOR(CtrlrSettings)

	private:
		CtrlrManager &owner;
		PropertyPanel* propertyPanel;
};


#endif
