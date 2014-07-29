#include "stdafx.h"
#include "CtrlrValueMap.h"
#include "CtrlrLog.h"

CtrlrValueMap::CtrlrValueMap(const String &stringToParseAsMap) : currentValue(0)
{
	parseString(stringToParseAsMap);
}

CtrlrValueMap::CtrlrValueMap() : currentValue(0)
{
}

CtrlrValueMap::~CtrlrValueMap()
{
}

void CtrlrValueMap::parseString (const String &stringToParseAsMap)
{
	values.clear();
	numericValues.clear();
	additionalData.clear();

	StringArray arLines;
	arLines.addTokens (stringToParseAsMap.trim(), "\n", "\"\'");
	for (int line=0; line<arLines.size(); line++)
	{
		if (arLines[line].startsWith("__"))
		{
			addAdditionalData (line, arLines[line]);
			continue;
		}

		CtrlrValue val;
		StringArray arLine;
		arLine.addTokens (arLines[line], "=", "\'\"");

		if (arLine.size() == 2)
		{
			val.numericValue			= arLine[1].getIntValue();
			val.textRepresentation		= arLine[0];
		}
		if (arLine.size() == 1)
		{
			val.textRepresentation		= arLine[0];
			val.numericValue			= line;
		}

		values.add (val);
		numericValues.add (val.numericValue);
	}

	DefaultElementComparator<int> sorter;
	numericValues.sort (sorter);
}

const int CtrlrValueMap::getMappedMax() const
{
	return (numericValues.getLast());
}

const int CtrlrValueMap::getMappedMin() const
{
	return (numericValues.getFirst());
}

const int CtrlrValueMap::getNumValues() const
{
	return (values.size());
}

const int CtrlrValueMap::getNonMappedMax() const
{
	return (values.size() - 1);
}

const int CtrlrValueMap::getNonMappedMin() const
{
	return (0);
}

const int CtrlrValueMap::getMappedValue(const int valueIndex) const
{
	return (values[valueIndex].numericValue);
}

const String CtrlrValueMap::getTextForIndex(const int valueIndex) const
{
	return (values[valueIndex].textRepresentation);
}

void CtrlrValueMap::increment()
{
	if (currentValue == getNonMappedMax())
		currentValue = 0;
	else
		currentValue++;
}

void CtrlrValueMap::decrement()
{
	if (currentValue == 0)
		currentValue = getNonMappedMax();
	else
		currentValue--;
}

const int CtrlrValueMap::getCurrentNonMappedValue() const
{
	return (currentValue);
}

const int CtrlrValueMap::getCurrentMappedValue() const
{
	return (values[currentValue].numericValue);
}

void CtrlrValueMap::setCurrentNonMappedValue(const int _currentValue)
{
	currentValue = _currentValue;
}

const int CtrlrValueMap::getNonMappedValue(const String &textRepresentation) const
{
	for (int i=0; i<values.size(); i++)
	{
		if (values[i].textRepresentation == textRepresentation)
			return (i);
	}

	return (-1);
}

const int CtrlrValueMap::getMappedValue(const String &textRepresentation) const
{
	for (int i=0; i<values.size(); i++)
	{
		if (values[i].textRepresentation == textRepresentation)
			return (values[i].numericValue);
	}

	return (-1);
}

const String CtrlrValueMap::getCurrentText() const
{
	return (values[currentValue].textRepresentation);
}

const Array<CtrlrValue> &CtrlrValueMap::getMap() const
{
	return (values);
}

const Array<int> &CtrlrValueMap::getNumericValues() const
{
	return (numericValues);
}

const HashMap<int,String> &CtrlrValueMap::getAdditionalData() const
{
	return (additionalData);
}

void CtrlrValueMap::copyFrom (const CtrlrValueMap &map)
{
	values			= map.getMap();
	numericValues	= map.getNumericValues();
	currentValue	= map.getCurrentNonMappedValue();

	additionalData.clear();

	HashMap<int,String>::Iterator i(map.getAdditionalData());
	while (i.next())
	{
		additionalData.set (i.getKey(), i.getValue());
	}
}

const bool CtrlrValueMap::mappedValueExists (const int mappedValue)
{
	for (int i=0; i<values.size(); i++)
	{
		if (values[i].numericValue == mappedValue)
			return (true);
	}

	return (false);
}

const int CtrlrValueMap::getIndexForValue(const int value) const
{
	for (int i=0; i<values.size(); i++)
	{
		if (values[i].numericValue == value)
			return (i);
	}
	return (-1);
}

void CtrlrValueMap::addAdditionalData (const int index, const String &data)
{
	if (data.startsWith ("__SECTION"))
	{
		additionalData.set (index, data.fromFirstOccurrenceOf("__SECTION ", false, false));
	}
	else if (data.startsWith ("__SEPARATOR"))
	{
		additionalData.set (index, String::empty);
	}
}

void CtrlrValueMap::fillCombo (ComboBox &comboToFill, const bool clearBeforeFill)
{
	if (clearBeforeFill)
	{
		comboToFill.clear(sendNotification);
	}

	for (int i=0; i<values.size(); i++)
	{
		if (additionalData.contains (i))
		{
			if (additionalData[i] == String::empty)
			{
				comboToFill.addSeparator();
			}
			else
			{
				comboToFill.addSectionHeading (additionalData[i]);
			}
		}

		if ((i+1) <= 0)
		{
			_WRN("CtrlrValueMap::fillCombo trying to insert an item with newItemId="+String(i+1));
		}
		comboToFill.addItem (values[i].textRepresentation, i+1);
	}
}

void CtrlrValueMap::setPair (const int index, const int value, const String &text)
{
	values.set (index, CtrlrValue(value, text));
	numericValues.addUsingDefaultSort (value);
}

void CtrlrValueMap::setCurrentMappedValue(const int _currentValue)
{
	setCurrentNonMappedValue (getIndexForValue(_currentValue));
}

const String CtrlrValueMap::toString() const
{
	String ret = "ValueMap";
	ret << " mappedMax=" + STR(getMappedMax());
	ret << " mappedMin=" + STR(getMappedMin());
	ret << " values:";

	for (int i=0; i<values.size(); i++)
	{
		ret << " " + STR(values[i].numericValue);
	}

	ret << "\nNumeric values:";

	for (int i=0; i<numericValues.size(); i++)
	{
		ret << " " + STR(numericValues[i]);
	}
	return (ret);
}