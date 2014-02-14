#ifndef __CTRLR_PROPERTIES__
#define __CTRLR_PROPERTIES__

#include "CtrlrMacros.h"

class CtrlrManager;

class CtrlrProperties
{
	public:
		CtrlrProperties(CtrlrManager &_owner);
		~CtrlrProperties();
		ApplicationProperties &getProperties();
		bool saveIfNeeded();

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrProperties);

	private:
		CtrlrManager &owner;
		ApplicationProperties applicationProperties;
};

#endif