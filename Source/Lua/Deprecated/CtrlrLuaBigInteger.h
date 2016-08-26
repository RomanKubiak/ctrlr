#ifndef __CTRLR_LUA_BIG_INTEGER__
#define __CTRLR_LUA_BIG_INTEGER__
#ifdef _WIN32
#pragma warning(disable:4100)
#endif

extern "C"
{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

#include "JuceHeader.h"

//==============================================================================
/** \brief A class for bit level operations.

*/
class CtrlrLuaBigInteger
{
	public:
		/** @brief Constructor

			@param integer	creates a BigInteger class from this value
		*/
		CtrlrLuaBigInteger(const int integer);

		/** @brief Destructor

		*/
		~CtrlrLuaBigInteger();

		/** @brief Internal

		*/
		static void wrapForLua(lua_State *L);

		/** @brief Clear or bits and set them to 0

		*/
		void clear();

		/** @brief Clear a specific bit (set to 0)

			@param bitPosition	the bit to clear
		*/
		void clearBit(const int bitPosition);

		/** @brief Clear a range of bits (set to 0)

			@param startBit		range start
			@param numBits		number of bits to clear
		*/
		void clearRange(const int startBit, const int numBits);

		/** @brief Set a bit (set to 1)

			@param bitPosition	the bit to set
			@param shouldBeSet	if the bit should be set or cleared
		*/
		void setBit(const int bitPosition, const bool shouldBeSet);

		/** @brief See if a bit is set

			@param bitPosition	bit position to read
		*/
		const bool getBit(const int bitPosition);

		/** @brief Set a range of bits (set to 1)

			@param startBit		range start
			@param numBits		number of bits to set
		*/
		void setRange(const int startBit, const int numBits);

		/** @brief Returns a number that is a representation of a range of bits

			@param startBit		range start
			@param numBits		number of bits to set
		*/
		const int getBitRangeAsInt(const int startBit, const int numBits);

		/** @brief Set a range of bits, the bits are read from the value passed in

			@param startBit		range start
			@param numBits		number of bits to set
			@param valueToSet	value to use for source bits
		*/
		void setBitRangeAsInt(const int startBit, const int numBits, const int valueToSet);

		/** @brief Bit shift operation

			@param howManyBitsLeft		number of bits to shift
			@param startBit				starting bit
		*/
		void shiftBits(int howManyBitsLeft, int startBit);

		/** @brief Returs the bits as a human readable string of '0' and '1'

			@param base								Specify a base such as 2 (binary), 8 (octal), 10 (decimal), 16 (hex)
			@param minimumNumCharacters				If minimumNumCharacters is greater than 0, the returned string will be padded with leading zeros to reach at least that length
		*/
		const String toString(const int base, const int minimumNumCharacters);

		JUCE_LEAK_DETECTOR(CtrlrLuaBigInteger)

	private:
		BigInteger bi;
};

#endif
