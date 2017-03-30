#ifndef CTRLR_EVALUATION_SCOPES
#define CTRLR_EVALUATION_SCOPES

#include "CtrlrMacros.h"

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