#ifndef __CTRLR_SYSEX_TOKEN__
#define __CTRLR_SYSEX_TOKEN__

#include "CtrlrMacros.h"

class CtrlrSysexToken
{
	public:
		CtrlrSysexToken(const int _tokenPosition=-1, const char _tokenIdentifier='\0', const CtrlrSysExFormulaToken _tokenType=NoToken, const int _tokenAdditionalData=0);
		virtual ~CtrlrSysexToken();

		int getAdditionalData() const;
		void setAdditionalData(const int _tokenAdditionalData);
		CtrlrSysExFormulaToken getType() const;
		void setType (const CtrlrSysExFormulaToken _tokenType);
		int getPosition() const;
		void setPosition(const int _tokenPosition);
		bool isHoldingValue();
		JUCE_LEAK_DETECTOR(CtrlrSysexToken)

	private:
		int tokenPosition, tokenAdditionalData;
		CtrlrSysExFormulaToken tokenType;
		char tokenIdentifier;
};

#endif
