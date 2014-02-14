#ifndef __L_MEMORY_BLOCK__
#define __L_MEMORY_BLOCK__

#include "CtrlrLuaManager.h"

class LMemoryBlock : public MemoryBlock
{
	public:
		LMemoryBlock()
		{}
		LMemoryBlock(const size_t size,bool zero) : MemoryBlock(size,zero)
		{}
		LMemoryBlock(const MemoryBlock &other) : MemoryBlock(other)
		{}
		operator MemoryBlock() const noexcept;
		LMemoryBlock (const void *dataToInitialiseFrom, size_t sizeInBytes);
		LMemoryBlock(const String &hexData);
		LMemoryBlock(luabind::object const& table);
		char operator[] (const int offset) const noexcept;
		void insertIntoTable(luabind::object const& table);
		void createFromTable(luabind::object const &table);
		uint8 getByte(const int position) const;
		//void *getData() { MemoryBlock::getData(); }
		LMemoryBlock getRange(const int startingPosition, const int numBytes) const;
		String toHexString(const int groupSize);
		void insert (MemoryBlock &dataToInsert, int insertPosition);
		void insert (MemoryBlock &dataToInsert, int dataSize, int insertPosition);
		void append (MemoryBlock &dataToAppend);
		void copyFrom(MemoryBlock &dataToCopy, int destinationOffset, int numBytes);
		void copyTo(MemoryBlock &dataToCopy, int sourceOffset, int numBytes);
		void replaceWith(MemoryBlock &dataToReplace);
		void setByte (const int bytePosition, const uint8 byteValue);
		double getSize() const noexcept;
		void toLuaTable (luabind::object tableToWriteTo);
		static LMemoryBlock fromLuaTable (luabind::object const& table);
		static void wrapForLua (lua_State *L);
};

#endif
