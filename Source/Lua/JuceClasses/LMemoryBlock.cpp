#include "stdafx.h"
#include "LMemoryBlock.h"

LMemoryBlock::LMemoryBlock(const String &hexData)
{
	MemoryBlock::loadFromHexString (hexData);
}

LMemoryBlock::LMemoryBlock(luabind::object const& table)
	: MemoryBlock(luaArrayTomemoryBlock(table))
{
}

LMemoryBlock LMemoryBlock::fromLuaTable (luabind::object const& table)
{
	return (luaArrayTomemoryBlock(table));
}

LMemoryBlock::LMemoryBlock (const void *dataToInitialiseFrom, size_t sizeInBytes)
	: MemoryBlock (dataToInitialiseFrom, sizeInBytes)
{
}

char LMemoryBlock::operator [] (const int offset) const noexcept
{
	return (*((uint8 *)getData()+offset));
}

void LMemoryBlock::insertIntoTable(luabind::object const& table)
{
	if (luabind::type(table) == LUA_TTABLE)
	{
		uint8 *ptr = (uint8 *)MemoryBlock::getData();

		for (unsigned int i=0; i<MemoryBlock::getSize(); i++)
		{
			table[i+1] = (uint8)*(ptr+i);
		}
	}
}

void LMemoryBlock::createFromTable(luabind::object const &table)
{
	for(luabind::iterator i(table), end; i != end; i++)
	{
		const uint8 v = luabind::object_cast<uint8>(*i);
		MemoryBlock::append (&v, 1);
	}
}

void LMemoryBlock::toLuaTable(luabind::object tableToWriteTo)
{
	for (int i=0; i<getSize(); i++)
	{
		tableToWriteTo[i+1] = getByte(i);
	}
}

uint8 LMemoryBlock::getByte(const int position) const
{
	uint8 *ptr = (uint8 *)getData();

	if (getSize() >= position)
		return (*(ptr + position));

	return (0);
}

LMemoryBlock LMemoryBlock::getRange(const int startingPosition, const int numBytes) const
{
	MemoryBlock bl;

	if (getSize() >= (startingPosition + numBytes))
	{
		bl.append ((uint8 *)getData() + startingPosition, numBytes);
	}
	return (bl);
}

String LMemoryBlock::toHexString(const int groupSize)
{
	return (String::toHexString(getData(), getSize(), groupSize));
}

void LMemoryBlock::insert (MemoryBlock &dataToInsert, int insertPosition)
{
	MemoryBlock::insert (dataToInsert.getData(), dataToInsert.getSize(), insertPosition);
}

void LMemoryBlock::insert (MemoryBlock &dataToInsert, int dataSize, int insertPosition)
{
	MemoryBlock::insert (dataToInsert.getData(), dataSize, insertPosition);
}

void LMemoryBlock::append (MemoryBlock &dataToAppend)
{
	MemoryBlock::append (dataToAppend.getData(), dataToAppend.getSize());
}

void LMemoryBlock::copyFrom(MemoryBlock &dataToCopy, int destinationOffset, int numBytes)
{
	MemoryBlock::copyFrom(dataToCopy.getData(), destinationOffset, numBytes);
}

void LMemoryBlock::copyTo(MemoryBlock &dataToCopy, int sourceOffset, int numBytes)
{
	MemoryBlock::copyTo(dataToCopy.getData(), sourceOffset, numBytes);
}

void LMemoryBlock::replaceWith(MemoryBlock &dataToReplace)
{
	MemoryBlock::replaceWith (dataToReplace.getData(), dataToReplace.getSize());
}

void LMemoryBlock::setByte (const int bytePosition, const uint8 byteValue)
{
	if (getSize() >= bytePosition)
	{
		*((uint8 *)getData() + bytePosition) = byteValue;
	}
}

double LMemoryBlock::getSize() const noexcept
{
	return ((double)MemoryBlock::getSize());
}

void LMemoryBlock::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<MemoryBlock>("JMemoryBlock")
		,
		class_<LMemoryBlock,bases<MemoryBlock> >("MemoryBlock")
				.def(constructor<>())
				.def(constructor<const size_t,bool>())
				.def(constructor<const MemoryBlock &>())
				.def(constructor<luabind::object const&>())
				.def(constructor<const String &>())
				.def("insertIntoTable", &LMemoryBlock::insertIntoTable)
				.def("createFromTable", &LMemoryBlock::createFromTable)
				.def("getByte", &LMemoryBlock::getByte)
				.def("setByte", &LMemoryBlock::setByte)
				.def("getRange", &LMemoryBlock::getRange)
				.def("toHexString", &LMemoryBlock::toHexString)
				.def("getData", &MemoryBlock::getData)
				.def("getSize", &LMemoryBlock::getSize)
				.def("setSize", &MemoryBlock::setSize)
				.def("ensureSize", &MemoryBlock::ensureSize)
				.def("fillWith", &MemoryBlock::fillWith)
				.def("append", &LMemoryBlock::append)
				.def("replaceWith", &LMemoryBlock::replaceWith)
				.def("insert", (void (LMemoryBlock::*) (MemoryBlock &, int)) &LMemoryBlock::insert)
				.def("insert", (void (LMemoryBlock::*) (MemoryBlock &, int, int)) &LMemoryBlock::insert)
				.def("removeSection", &MemoryBlock::removeSection)
				.def("copyFrom", &LMemoryBlock::copyFrom)
				.def("copyTo", &LMemoryBlock::copyTo)
				.def("swapWith", &MemoryBlock::swapWith)
				.def("toString", &MemoryBlock::toString)
				.def("loadFromHexString", &MemoryBlock::loadFromHexString)
				.def("setBitRange", &MemoryBlock::setBitRange)
				.def("getBitRange", &MemoryBlock::getBitRange)
				.def("toBase64Encoding", &MemoryBlock::toBase64Encoding)
				.def("fromBase64Encoding", &MemoryBlock::fromBase64Encoding)
				.def("toLuaTable", &LMemoryBlock::toLuaTable)
				.scope
				[
					def("fromLuaTable", &LMemoryBlock::fromLuaTable)
				]
	];
}
