#ifndef CTRLR_PROPERTIES
#define CTRLR_PROPERTIES

#include "CtrlrMacros.h"

class CtrlrManager;

class CtrlrProperties
{
	public:
		CtrlrProperties(CtrlrManager &_owner);
		~CtrlrProperties();
		ApplicationProperties &getProperties();
		bool saveIfNeeded(const bool force=true);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrProperties);

	private:
		CtrlrManager &owner;
		ApplicationProperties applicationProperties;
};

#endif
