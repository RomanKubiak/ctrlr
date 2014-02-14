#ifndef __CTRLR_LUA_MEMORY_BLOCK__
#define __CTRLR_LUA_MEMORY_BLOCK__

#pragma warning(disable:4100)
#pragma warning(disable:4018)

#include <luabind/luabind.hpp>
#include "CtrlrMacros.h"

class CtrlrLuaObjectWrapper;

//==============================================================================
/** \brief A class for managing memory ranges (binary data in memory)

*/
class CtrlrLuaMemoryBlock
{
	public:
		CtrlrLuaMemoryBlock(const MemoryBlock &other);
		CtrlrLuaMemoryBlock();
		CtrlrLuaMemoryBlock(const int initialSize, bool zeroData);
		CtrlrLuaMemoryBlock(const void *dataToInitialiseFrom, int sizeInBytes);

		/** @brief Constructor that copies data from a LUA array

			@param initialData			LUA array to read the data from
		*/
		CtrlrLuaMemoryBlock(luabind::object const &initialData);
		
		/** @brief Destructor

		*/
		~CtrlrLuaMemoryBlock();

		/** @brief Internal

		*/
		static void wrapForLua(lua_State *L);

		/** @brief Append some data to this block

			@param dataToAppend		array of data to append
		*/
		void append(const CtrlrLuaObjectWrapper &dataToAppend);

		/** @brief Append a byte to the block

			@param byte		the byte to append
		*/
		void append(const uint8 byte);

		/** @brief Get a range of bytes from this block as a MemoryBlock

			@param startByte	starting byte
			@param numBytes		number of bytes
		*/
		const CtrlrLuaMemoryBlock getRange(const int startByte, const int numBytes) const;

		/** @brief Convert the block to a HEX string

			@param groupSize	byte groups
		*/
		const String toHexString(const int groupSize=1) const;

		/** @brief Get one byte from the block

			@param bytePosition		byte position
		*/
		const int getByte(const int bytePosition) const;

		/** @brief Set one of the bytes in the block

			@param bytePosition		byte position
			@param byteValue		value to set for the byte
		*/
		void setByte(const unsigned int bytePosition, const int byteValue);

		/** @brief Try to read the contents of this block as a utf8 encoded string

			@return the string that was read, if any
		*/
		const String toString ();

		/** @brief Try to read the contents of this block as a utf8 encoded string, and remove all non-printable characers

			@return the string that was read, if any
		*/
		const String toSafeString ();

		/** @brief Get the size of the block

			@return size of the block
		*/
		const int getSize() const;
		
		/** @brief Load data to this block using a string, the string is parsed as hex numbers seperated by spaces

		*/
		void loadFromHexString(const String &string);

		/** @brief Copy data to this block from another one, the first paramters is another MemoryBlock

			@param	sourceData			data to copy from
			@param	destinationOffset	offset to put the data at
			@param	numBytes			how many bytes to copy
		*/
		void copyFrom (CtrlrLuaMemoryBlock &sourceData, int destinationOffset, int numBytes);

		/** @brief Copy data from this block to another, the first paramters is another MemoryBlock

			@param	destinationData		data to copy to
			@param	sourceOffset		source offset where to start reading
			@param	numBytes			how many bytes to copy
		*/
		void copyTo (CtrlrLuaMemoryBlock &destinationData, int sourceOffset, int numBytes);

		/** @brief Inserts some data into the block. The dataToInsert pointer must not be null. 
					This block's size will be increased accordingly. 
					If the insert position lies outside the valid range of the block, it will be clipped 
					to within the range before being used.

			@param	dataToInsert		data to insert
			@param	numBytesToInsert	number of bytes to insert
			@param	insertPosition		position to insert the data at
		*/
		void insert (CtrlrLuaMemoryBlock &dataToInsert, int numBytesToInsert, int insertPosition);

		/** @brief Chops out a section of the block.
					This will remove a section of the memory block and close the gap around it, 
					shifting any subsequent data downwards and reducing the size of the block.
					If the range specified goes beyond the size of the block, it will be clipped.

			@param startByte			start removal at this byte
			@param numBytesToRemove		remove this many bytes
		*/
		void removeSection (int startByte, int numBytesToRemove);

		MemoryBlock &getMemoryBlock()			{ return (mb); }
		const MemoryBlock getCopy()				const { return (mb); }
		void *getData()					const	{ return (mb.getData()); }

		JUCE_LEAK_DETECTOR(CtrlrLuaMemoryBlock)

	private:
		MemoryBlock mb;
};

#endif