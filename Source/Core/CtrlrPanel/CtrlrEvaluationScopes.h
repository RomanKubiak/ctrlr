#ifndef __CTRLR_EVALUATION_SCOPES__
#define __CTRLR_EVALUATION_SCOPES__

#include "JuceHeader.h"

class CtrlrPanel;

class CtrlrPanelEvaluationScope : public Expression::Scope
{
	public:
		CtrlrPanelEvaluationScope (CtrlrPanel &_owner);
		String getScopeUID() const;
		Expression getSymbolValue (const String& symbol) const;

	private:
		CtrlrPanel &owner;
};

class CtrlrGlobalEvaluationScope : public Expression::Scope
{
	public:
		CtrlrGlobalEvaluationScope (CtrlrPanel &_owner);
		String getScopeUID() const;
		Expression getSymbolValue (const String& symbol) const;

	private:
		CtrlrPanel &owner;
};

#endif