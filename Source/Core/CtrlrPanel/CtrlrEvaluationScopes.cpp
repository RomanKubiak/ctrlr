#include "stdafx.h"
#include "CtrlrEvaluationScopes.h"
#include "CtrlrPanel.h"

// Panel evaluation scope
CtrlrPanelEvaluationScope::CtrlrPanelEvaluationScope(CtrlrPanel &_owner) : owner(_owner)
{
}

String CtrlrPanelEvaluationScope::getScopeUID() const
{
	return ("panel");
}

Expression CtrlrPanelEvaluationScope::getSymbolValue (const String& symbol) const
{
	if (owner.getModulator (symbol))
	{
		return (Expression (owner.getModulator (symbol)->getValueNonMapped()));
	}
	return (Expression());
}

// Global evaluation scope
CtrlrGlobalEvaluationScope::CtrlrGlobalEvaluationScope(CtrlrPanel &_owner) : owner(_owner)
{
}

String CtrlrGlobalEvaluationScope::getScopeUID() const
{
	return ("global");
}

Expression CtrlrGlobalEvaluationScope::getSymbolValue (const String& symbol) const
{
	if ((symbol.startsWith("k") || symbol.startsWith("l") || symbol.startsWith("m") || symbol.startsWith("n")) && symbol.length() == 2)
	{
		return (Expression (owner.getGlobalVariable(symbol.substring(1,2).getIntValue())));
	}
	return (Expression());
}

double evaluateFormulaFunction (CtrlrPanel &panel, const String& functionName, const double* parameters, int numParameters)
{
	if (functionName == "ceil")
	{
		if (numParameters == 1)
		{
			return (ceil(*parameters));
		}
		else
		{
			_WRN("CTRLR::expr: ceil incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "abs")
	{
		if (numParameters == 1)
		{
			return (abs(*parameters));
		}
		else
		{
			_WRN("CTRLR::expr: abs incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "floor")
	{
		if (numParameters == 1)
		{
			return (floor(*parameters));
		}
		else
		{
			_WRN("CTRLR::expr: floor incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "mod")
	{
		if (numParameters == 2)
		{
			return ((int)*parameters % (int)*(parameters+1));
		}
		else
		{
			_WRN("CTRLR::expr: mod incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "fmod")
	{
		if (numParameters == 2)
		{
			return (fmod (*parameters, *(parameters+1)));
		}
		else
		{
			_WRN("CTRLR::expr: fmod incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "pow")
	{
		if (numParameters == 2)
		{
			return (pow(*parameters, *(parameters+1)));
		}
		else
		{
			_WRN("CTRLR::expr: pow incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "gte")
	{
		if (numParameters == 4)
		{
			const double eq1	= *(parameters);
			const double eq2	= *(parameters+1);
			const double p1		= *(parameters+2);
			const double p2		= *(parameters+3);

			if (eq1 >= eq2)
			{
				return (p1);
			}
			else
			{
				return (p2);
			}
		}
		else
		{
			_WRN("CTRLR::expr: gte incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "gt")
	{
		if (numParameters == 4)
		{
			const double eq1	= *(parameters);
			const double eq2	= *(parameters+1);
			const double p1		= *(parameters+2);
			const double p2		= *(parameters+3);

			if (eq1 > eq2)
			{
				return (p1);
			}
			else
			{
				return (p2);
			}
		}
		else
		{
			_WRN("CTRLR::expr: gt incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "lte")
	{
		if (numParameters == 4)
		{
			const double eq1	= *(parameters);
			const double eq2	= *(parameters+1);
			const double p1		= *(parameters+2);
			const double p2		= *(parameters+3);

			if (eq1 <= eq2)
			{
				return (p1);
			}
			else
			{
				return (p2);
			}
		}
		else
		{
			_WRN("CTRLR::expr: lte incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "lt")
	{
		if (numParameters == 4)
		{
			const double eq1	= *(parameters);
			const double eq2	= *(parameters+1);
			const double p1		= *(parameters+2);
			const double p2		= *(parameters+3);

			if (eq1 < eq2)
			{
				return (p1);
			}
			else
			{
				return (p2);
			}
		}
		else
		{
			_WRN("CTRLR::expr: lt incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "eq")
	{
		if (numParameters == 4)
		{
			const double eq1	= *(parameters);
			const double eq2	= *(parameters+1);
			const double p1		= *(parameters+2);
			const double p2		= *(parameters+3);

			if (eq1 == eq2)
			{
				return (p1);
			}
			else
			{
				return (p2);
			}
		}
		else
		{
			_WRN("CTRLR::expr: eq incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "max")
	{
		if (numParameters == 2)
		{
			return (jmax<double> (*(parameters), *(parameters+1)));
		}
		else
		{
			_WRN("CTRLR::expr: max incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "min")
	{
		if (numParameters == 2)
		{
			return (jmin<double> (*(parameters), *(parameters+1)));
		}
		else
		{
			_WRN("CTRLR::expr: min incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "setBit")
	{
		if (numParameters == 3)
		{
			const double value		= *parameters;
			const int bitToSet		= (int)*(parameters+1);
			const bool shouldBeSet	= *(parameters+2) ? true : false;

			BigInteger bi((uint32)value);
			bi.setBit (bitToSet, shouldBeSet);
			
			return (bi.getBitRangeAsInt(0,32));
		}
		else
		{
			_WRN("CTRLR::expr: setBit incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "isBitSet")
	{
		if (numParameters == 2)
		{
			const double value		= *parameters;
			const int position		= (int)*(parameters+1);

			BigInteger bi((uint32)value);
			return (bi[position]);
		}
		else
		{
			_WRN("CTRLR::expr: isBitSet incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "clearBit")
	{
		if (numParameters == 2)
		{
			const double value		= *parameters;
			const double pre		= value;
			const int bitToClear	= (int)*(parameters+1);

			BigInteger bi((uint32)value);
			bi.setBit (bitToClear, false);

			return (bi.getBitRangeAsInt(0,32));
		}
		else
		{
			_WRN("CTRLR::expr: clearBit incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "setBitRangeAsInt")
	{
		if (numParameters == 4)
		{
			const double value		= *parameters;
			const int startBit		= (int)*(parameters+1);
			const int numBits		= (int)*(parameters+2);
			const uint32 valueToSet	= (uint32)*(parameters+3);

			BigInteger bi((uint32)value);
			bi.setBitRangeAsInt (startBit, numBits, valueToSet);

			return (bi.getBitRangeAsInt(0,32));
		}
		else
		{
			_WRN("CTRLR::expr: setBitRangeAsInt incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "getBitRangeAsInt")
	{
		if (numParameters == 3)
		{
			const double value		= *parameters;
			const int startBit		= (int)*(parameters+1);
			const int numBits		= (int)*(parameters+2);

			BigInteger bi((uint32)value);

			return (bi.getBitRangeAsInt (startBit, numBits));
		}
		else
		{
			_WRN("CTRLR::expr: getBitRangeAsInt incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "setGlobal")
	{
		if (numParameters == 2)
		{
			const int globalIndex	= (int)*parameters;
			const int valueToSet	= (int)*(parameters+1);

			panel.setGlobalVariable (globalIndex, valueToSet);

			return (valueToSet);
		}
		else
		{
			_WRN("CTRLR::expr: setGlobal incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "getModulatorByVstIndex")
	{
		if (numParameters == 1)
		{
			const int vstIndex	= (int)*parameters;

			CtrlrModulator *m = panel.getModulatorByVstIndex (vstIndex);

			if (m)
				return (m->getModulatorValue());
			else
				return (-1);
		}
		else
		{
			_WRN("CTRLR::expr: setGlobal incorrent number of parameters "+STR(numParameters));
		}
	}
	else if (functionName == "getModulatorByCustomIndex")
	{
		if (numParameters == 1)
		{
			const int vstIndex	= (int)*parameters;

			CtrlrModulator *m = panel.getModulatorByCustomIndex (vstIndex);

			if (m)
				return (m->getModulatorValue());
			else
				return (-1);
		}
		else
		{
			_WRN("CTRLR::expr: setGlobal incorrent number of parameters "+STR(numParameters));
		}
	}
	return (1.0);
}