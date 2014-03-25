#ifndef CTRLR_NATIVE_H
#define CTRLR_NATIVE_H

#include "JuceHeader.h"
class CtrlrPanel;

#define	CTRLR_INTERNAL_PANEL_RESID			1040
#define CTRLR_INTERNAL_PANEL_SECTION		"ctrlr_panel"
#define CTRLR_INTERNAL_RESOURCES_RESID		1041
#define CTRLR_INTERNAL_RESOURCES_SECTION	"ctrl_panel_resources"
#define CTRLR_NEW_INSTANCE_DIALOG_TITLE		L"Write new instance here"
#define CTRLR_MAC_PANEL_FILE				L"PanelZ"
#define CTRLR_MAC_RESOURCES_FILE			L"ResourcesZ"

class CtrlrNative
{
	public:
		static CtrlrNative *getNativeObject();
		virtual const Result exportWithDefaultPanel(CtrlrPanel*  /* panelToWrite */, const bool isRestricted=false)		{ return (Result::fail("Native, implement me")); }
		virtual const Result getDefaultPanel(MemoryBlock& /*dataToWrite*/)												{ return (Result::fail("Native, implement me")); }
		virtual const Result getDefaultResources(MemoryBlock& /*dataToWrite*/)											{ return (Result::fail("Native, implement me")); }
		virtual const Result registerFileHandler()																		{ return (Result::fail("Native, implement me")); }
};

#endif
