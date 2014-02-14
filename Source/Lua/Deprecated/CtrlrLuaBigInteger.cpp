#include "stdafx.h"
#include "CtrlrLuaBigInteger.h"

CtrlrLuaBigInteger::CtrlrLuaBigInteger(const int integer) : bi(integer)
{
}

CtrlrLuaBigInteger::~CtrlrLuaBigInteger()
{
}

void CtrlrLuaBigInteger::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrLuaBigInteger>("CtrlrLuaBigInteger")
			.def(constructor<const int>())
			.def("clear", &CtrlrLuaBigInteger::clear)
			.def("clearBit", &CtrlrLuaBigInteger::clearBit)
			.def("clearRange", &CtrlrLuaBigInteger::clearRange)
			.def("setBit", &CtrlrLuaBigInteger::setBit)
			.def("getBit", &CtrlrLuaBigInteger::getBit)
			.def("setRange", &CtrlrLuaBigInteger::setRange)
			.def("getBitRangeAsInt", &CtrlrLuaBigInteger::getBitRangeAsInt)
			.def("setBitRangeAsInt", &CtrlrLuaBigInteger::setBitRangeAsInt)
			.def("shiftBits", &CtrlrLuaBigInteger::shiftBits)
			.def("toString", &CtrlrLuaBigInteger::toString)
    ];
}

void CtrlrLuaBigInteger::clear()
{
	bi.clear();
}

void CtrlrLuaBigInteger::clearBit(const int bitPosition)
{
	bi.clearBit(bitPosition);
}

void CtrlrLuaBigInteger::clearRange(const int startBit, const int numBits)
{
	bi.setRange (startBit, numBits, false);
}

const bool CtrlrLuaBigInteger::getBit(const int bitPosition)
{
	return (bi[bitPosition]);
}

void CtrlrLuaBigInteger::setBit(const int bitPosition, const bool shouldBeSet)
{
	bi.setBit (bitPosition, shouldBeSet);
}

void CtrlrLuaBigInteger::setRange(const int startBit, const int numBits)
{
	bi.setRange (startBit, numBits, true);
}

const int CtrlrLuaBigInteger::getBitRangeAsInt(const int startBit, const int numBits)
{
	return (bi.getBitRangeAsInt(startBit,numBits));
}

void CtrlrLuaBigInteger::setBitRangeAsInt(const int startBit, const int numBits, const int valueToSet)
{
	bi.setBitRangeAsInt (startBit, numBits, valueToSet);
}

void CtrlrLuaBigInteger::shiftBits(int howManyBitsLeft, int startBit)
{
	bi.shiftBits(howManyBitsLeft, startBit);
}

const String CtrlrLuaBigInteger::toString(const int base, const int minimumNumCharacters)
{
	return (bi.toString (base, minimumNumCharacters));
}