#include "stdafx.h"
#include "CtrlrLuaObjectWrapper.h"
#include "CtrlrLuaMemoryBlock.h"
#include "CtrlrUtilities.h"
#include "CtrlrLog.h"

CtrlrLuaMemoryBlock::CtrlrLuaMemoryBlock()
{
}

CtrlrLuaMemoryBlock::CtrlrLuaMemoryBlock(const int initialSize, bool zeroData) : mb(initialSize, zeroData)
{
}

CtrlrLuaMemoryBlock::CtrlrLuaMemoryBlock(const void *dataToInitialiseFrom, int sizeInBytes) : mb(dataToInitialiseFrom, sizeInBytes)
{
}

CtrlrLuaMemoryBlock::CtrlrLuaMemoryBlock(const MemoryBlock &other) : mb(other)
{
}

CtrlrLuaMemoryBlock::CtrlrLuaMemoryBlock(luabind::object const &initialData)
{
	for(luabind::iterator i(initialData), end; i != end; i++)
	{
		const uint8 v = luabind::object_cast<uint8>(*i);
		mb.append (&v, 1);
	}
}

CtrlrLuaMemoryBlock::~CtrlrLuaMemoryBlock()
{
}

const CtrlrLuaMemoryBlock CtrlrLuaMemoryBlock::getRange(const int startByte, const int numBytes) const
{
	MemoryBlock ret(numBytes,true);

	for (int i=0; i<numBytes; i++)
	{
		if (i+startByte < mb.getSize())
			ret[i] = mb[i+startByte];
		else
			break;
	}

	return (ret);
}

const int CtrlrLuaMemoryBlock::getByte(const int bytePosition) const
{
	if (bytePosition >= mb.getSize())
	{
		_LERR("CtrlrLuaMemoryBlock::getByte position: "+String((unsigned int)bytePosition)+" is beyond bounds of this memory block with size: "+String((unsigned int)mb.getSize()));
		return (0);
	}

	return ((uint8)mb[bytePosition]);
}

void CtrlrLuaMemoryBlock::setByte(const unsigned int bytePosition, const int byteValue)
{
	if (bytePosition < mb.getSize())
	{
		mb[bytePosition] = byteValue;
	}
	else
	{
		_LERR("CtrlrLuaMemoryBlock::getByte position: "+String((unsigned int)bytePosition)+" is beyond bounds of this memory block with size: "+String((unsigned int)mb.getSize()));
	}
}

void CtrlrLuaMemoryBlock::append(const CtrlrLuaObjectWrapper &dataToAppend)
{
	for(luabind::iterator i(dataToAppend.getObject()), end; i != end; i++)
	{
		const uint8 v = luabind::object_cast<uint8>(*i);
		mb.append (&v, 1);
	}
}

void CtrlrLuaMemoryBlock::append(const uint8 byte)
{
	mb.append (&byte, 1);
}

const int CtrlrLuaMemoryBlock::getSize() const
{
	return (mb.getSize());
}

const String CtrlrLuaMemoryBlock::toString ()
{
	return (mb.toString());
}

const String CtrlrLuaMemoryBlock::toSafeString ()
{
	return (removeInvalidChars(mb.toString()));
}

const String CtrlrLuaMemoryBlock::toHexString(const int groupSize) const 
{
	return (String::toHexString (mb.getData(), mb.getSize(), groupSize));
}

void CtrlrLuaMemoryBlock::loadFromHexString(const String &string)
{
	mb.loadFromHexString (string);
}

void CtrlrLuaMemoryBlock::copyFrom (CtrlrLuaMemoryBlock &sourceData, int destinationOffset, int numBytes)
{
	mb.copyFrom (sourceData.getData(), destinationOffset, numBytes);
}

void CtrlrLuaMemoryBlock::copyTo (CtrlrLuaMemoryBlock &destinationData, int sourceOffset, int numBytes)
{
	mb.copyTo (destinationData.getData(), sourceOffset, numBytes);
}

void CtrlrLuaMemoryBlock::insert (CtrlrLuaMemoryBlock &dataToInsert, int numBytesToInsert, int insertPosition)
{
	mb.insert (dataToInsert.getData(), numBytesToInsert, insertPosition);
}

void CtrlrLuaMemoryBlock::removeSection (int startByte, int numBytesToRemove)
{
	mb.removeSection (startByte, numBytesToRemove);
}

void CtrlrLuaMemoryBlock::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrLuaMemoryBlock>("CtrlrLuaMemoryBlock")
			.def(constructor<>())
			.def(constructor<const int, bool>())
			.def(constructor<luabind::object const &>())
			.def("getByte", &CtrlrLuaMemoryBlock::getByte)
			.def("setByte", &CtrlrLuaMemoryBlock::setByte)
			.def("append", (void(CtrlrLuaMemoryBlock::*)(const uint8))&CtrlrLuaMemoryBlock::append)
			.def("append", (void(CtrlrLuaMemoryBlock::*)(const CtrlrLuaObjectWrapper &))&CtrlrLuaMemoryBlock::append)
			.def("getRange", &CtrlrLuaMemoryBlock::getRange)
			.def("toHexString", &CtrlrLuaMemoryBlock::toHexString)
			.def("toString", &CtrlrLuaMemoryBlock::toString)
			.def("getSize", &CtrlrLuaMemoryBlock::getSize)
			.def("loadFromHexString", &CtrlrLuaMemoryBlock::loadFromHexString)
			.def("toSafeString", &CtrlrLuaMemoryBlock::toSafeString)
			.def("copyFrom", (void(CtrlrLuaMemoryBlock::*)(CtrlrLuaMemoryBlock &, int, int))&CtrlrLuaMemoryBlock::copyFrom)
			.def("copyTo",   (void(CtrlrLuaMemoryBlock::*)(CtrlrLuaMemoryBlock &, int, int))&CtrlrLuaMemoryBlock::copyTo)
			.def("insert", &CtrlrLuaMemoryBlock::insert)
			.def("removeSection", &CtrlrLuaMemoryBlock::removeSection)
	];
}