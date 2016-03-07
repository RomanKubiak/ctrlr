#ifndef __CTRLR_VALUE_MAP__
#define __CTRLR_VALUE_MAP__

#include "CtrlrMacros.h"

struct CtrlrValue
{
	CtrlrValue(const int _numericValue, const String &_textRepresentation)
		: numericValue(_numericValue), textRepresentation(_textRepresentation)
	{}
	CtrlrValue()
	{}

	static const String toString(const CtrlrValue &value)
	{
		return ("\"" + value.textRepresentation + "\" [" + _STR(value.numericValue) + "]");
	}
	JUCE_LEAK_DETECTOR(CtrlrValue);

	int		numericValue;
	String	textRepresentation;
};

class CtrlrValueMap
{
	public:
		CtrlrValueMap(const String &stringToParseAsMap);
		CtrlrValueMap();
		~CtrlrValueMap();

		/** @brief Parse a string as a value map

			@param stringToParseAsMap The string to parse, it will be trim()'ed out of EOLs on the end
		*/
		void parseString (const String &stringToParseAsMap);

		/** @brief Copy contents of another ValueMap to this one, this can't be done via the '=' operator

			@param map	the other map to copy data from
		*/
		void copyFrom (const CtrlrValueMap &map);

		/** @brief Get the maximum mapped value

			@return	the maximum of all mapped values
		*/
		int getMappedMax() const;

		/** @brief Get the minimum mapped value

			@return the minimum of all mapped values
		*/
		int getMappedMin() const;

		/** @brief Get the direct maximum value (this will be the number of elements-1)

			@return get the non-mapped maximum value
		*/
		int getNonMappedMax() const;
		int getNonMappedMin() const;
		int getNumValues() const;

		/** @brief For a mapped value, get the non-mapped value (index) in the map

			@return the index of the value in the map
		*/
		int getIndexForValue(const int value) const;

		/** @brief Get a mapped values for an index

			@param valueIndex		the index in the map to fetch
			@return					the mapped value with this index
		*/
		int getMappedValue(const int valueIndex) const;

		/** @brief Get the index of a value based on the value's text

			@param	textRepresentation	the text to look for
			@return	the index of the value with this text
		*/
		int getNonMappedValue(const String &textRepresentation) const;
		int getMappedValue(const String &textRepresentation) const;

		/** @brief Get the text representation of a value for an index in the map

			@param	valueIndex	index of the value to look for
			@return	the text representation of the searched value
		*/
		const String getTextForIndex(const int valueIndex) const;

		/** @brief The map can hold a state of a component, this method increments
				the current value by 1
		*/
		void increment();

		/** @brief The map can hold a state of a component, this method decrements
				the current value by 1
		*/
		void decrement();

		/** @brief See if a mapped value exists in the map

			@return true if the value exists false otherwise
		*/
		bool mappedValueExists (const int mappedValue);

		/** @brief If the map holds a state this fetches the current index that's stored

			@return	the index of the current value stored in the map
		*/
		int getCurrentNonMappedValue() const;

		/** @brief If the map holds a state, this fetches the current mapped value stored

			@return	the numeric value of the current value stored
		*/
		int getCurrentMappedValue() const;

		/** @brief If the map holds a state, this fetches the current text that represents a mapped value

			@return	the text value of the current value stored
		*/
		const String getCurrentText() const;

		/** @brief Set the current non-mapped value

			@param	_currentValue The current value this map should store state for (the index of the value in the map)
		*/
		void setCurrentNonMappedValue(const int _currentValue);

		/** @brief Set the current mapped value

			@param	_currentValue The mapped value this map should store
		*/
		void setCurrentMappedValue(const int _currentValue);

		/** @brief Set a pair of key=value

			@param index the index/key
			@param value the value to match the index
			@param text  the text that represents this pair
		*/
		void setPair (const int index, const int value, const String &text);

		/** @brief Empty the map

		*/
		void clear();

		const Array<CtrlrValue> &getMap() const;
		const Array<int> &getNumericValues() const;
		const HashMap<int,String> &getAdditionalData() const;
		void addAdditionalData (const int index, const String &data);
		void fillCombo (ComboBox &comboToFill, const bool clearBeforeFill);
		const String toString() const;

		static void wrapForLua(lua_State *L);

		JUCE_LEAK_DETECTOR(CtrlrValueMap);

	private:
		int currentValue;
		Array<CtrlrValue> values;
		Array<int> numericValues;
		HashMap<int,String> additionalData;
};

#endif
