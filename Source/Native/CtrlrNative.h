#ifndef CTRLR_NATIVE_H
#define CTRLR_NATIVE_H

#include "JuceHeader.h"
class CtrlrPanel;

#define CTRLR_NEW_INSTANCE_DIALOG_TITLE		L"Write new instance here"

#define	CTRLR_INTERNAL_PANEL_RESID				1040
#define CTRLR_INTERNAL_RESOURCES_RESID			1041
#define CTRLR_INTERNAL_SIGNATURE_RESID			1042
#define CTRLR_INTERNAL_SIGNATURE_MASTER_RESID	1043

#define CTRLR_MAC_PANEL_FILE					L"PanelZ"
#define CTRLR_MAC_RESOURCES_FILE				L"ResourcesZ"
#define CTRLR_MAC_SIGNATURE_FILE				L"Signature"
#define CTRLR_MAC_SIGNATURE_MASTER_FILE			L"MasterSignature"

#define CTRLR_INTERNAL_PANEL_SECTION			"ctrlr_panel"
#define CTRLR_INTERNAL_RESOURCES_SECTION		"ctrlr_panel_resources"
#define CTRLR_INTERNAL_SIGNATURE_SECTION		"ctrlr_panel_signature"
#define CTRLR_INTERNAL_SIGNATURE_MASTER_SECTION	"ctrlr_panel_signature_master"
class CtrlrNative
{
	public:
		static CtrlrNative *getNativeObject(CtrlrManager &owner);
		virtual const Result exportWithDefaultPanel (CtrlrPanel *panelToWrite,
                                                        const bool isRestricted=false,
                                                        const bool signPanel=false,
                                                        RSAKey privateKey = RSAKey())
		{
		    return (Result::fail("Native, implement me"));
        }
		virtual const Result getDefaultPanel(MemoryBlock& /*dataToWrite*/)												{ return (Result::fail("Native, implement me")); }
		virtual const Result getDefaultResources(MemoryBlock& /*dataToWrite*/)											{ return (Result::fail("Native, implement me")); }
		virtual const Result registerFileHandler()																		{ return (Result::fail("Native, implement me")); }
		virtual const Result getSignature(MemoryBlock &)                                                                  { return (Result::fail("Native, implement me")); }
};

#endif
