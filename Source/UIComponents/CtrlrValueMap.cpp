#define USING_LUABIND 1
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

int CtrlrValueMap::getMappedMax() const
{
	return (numericValues.getLast());
}

int CtrlrValueMap::getMappedMin() const
{
	return (numericValues.getFirst());
}

int CtrlrValueMap::getNumValues() const
{
	return (values.size());
}

int CtrlrValueMap::getNonMappedMax() const
{
	return (values.size() - 1);
}

int CtrlrValueMap::getNonMappedMin() const
{
	return (0);
}

int CtrlrValueMap::getMappedValue(const int valueIndex) const
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

int CtrlrValueMap::getCurrentNonMappedValue() const
{
	return (currentValue);
}

int CtrlrValueMap::getCurrentMappedValue() const
{
	return (values[currentValue].numericValue);
}

void CtrlrValueMap::setCurrentNonMappedValue(const int _currentValue)
{
	currentValue = _currentValue;
}

int CtrlrValueMap::getNonMappedValue(const String &textRepresentation) const
{
	for (int i=0; i<values.size(); i++)
	{
		if (values[i].textRepresentation == textRepresentation)
			return (i);
	}

	return (-1);
}

int CtrlrValueMap::getMappedValue(const String &textRepresentation) const
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

bool CtrlrValueMap::mappedValueExists (const int mappedValue)
{
	for (int i=0; i<values.size(); i++)
	{
		if (values[i].numericValue == mappedValue)
			return (true);
	}

	return (false);
}

int CtrlrValueMap::getIndexForValue(const int value) const
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
	String ret = "MAP: ";
	ret << " mappedMax=" + STR(getMappedMax());
	ret << ", mappedMin=" + STR(getMappedMin());
	ret << ", values:\n";

	for (int i=0; i<values.size(); i++)
	{
		ret << "{" << _STR(i) << "}: ( ";
		ret << CtrlrValue::toString(values[i]);
		ret << " )\n";
	}

	return (ret);
}

void CtrlrValueMap::clear()
{
	currentValue = 0;
	values.clear();
	numericValues.clear();
	additionalData.clear();
}

void CtrlrValueMap::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrValue>("CtrlrValue")
			.def_readwrite("numericValue", &CtrlrValue::numericValue)
			.def_readwrite("textRepresentation", &CtrlrValue::textRepresentation)
		,
		class_<CtrlrValueMap>("CtrlrValueMap")
			.def("parseString", &CtrlrValueMap::parseString)
			.def("copyFrom", &CtrlrValueMap::copyFrom)
			.def("getMappedMax", &CtrlrValueMap::getMappedMax)
			.def("getMappedMin", &CtrlrValueMap::getMappedMin)
			.def("getNonMappedMax", &CtrlrValueMap::getNonMappedMax)
			.def("getNonMappedMin", &CtrlrValueMap::getNonMappedMin)
			.def("getIndexForValue", &CtrlrValueMap::getIndexForValue)
			.def("getMappedValue", (int (CtrlrValueMap::*)(const String &) const) &CtrlrValueMap::getMappedValue)
            .def("getMappedValue", (int (CtrlrValueMap::*)(const int) const) &CtrlrValueMap::getMappedValue)
            .def("getNonMappedValue", &CtrlrValueMap::getNonMappedValue)
            .def("getTextForIndex", &CtrlrValueMap::getTextForIndex)
            .def("increment", &CtrlrValueMap::increment)
            .def("decrement", &CtrlrValueMap::decrement)
            .def("mappedValueExists", &CtrlrValueMap::mappedValueExists)
            .def("getCurrentNonMappedValue", &CtrlrValueMap::getCurrentNonMappedValue)
            .def("getCurrentMappedValue", &CtrlrValueMap::getCurrentMappedValue)
            .def("getCurrentText", &CtrlrValueMap::getCurrentText)
            .def("setCurrentNonMappedValue", &CtrlrValueMap::setCurrentNonMappedValue)
            .def("setCurrentMappedValue", &CtrlrValueMap::setCurrentMappedValue)
            .def("setPair", &CtrlrValueMap::setPair)
            .def("getMap", &CtrlrValueMap::getMap)
            .def("getNumericValues", &CtrlrValueMap::getNumericValues)
            .def("addAdditionalData", &CtrlrValueMap::addAdditionalData)
            .def("fillCombo", &CtrlrValueMap::fillCombo)
            .def("toString", &CtrlrValueMap::toString)
            .def("clear", &CtrlrValueMap::clear)
	];
}
