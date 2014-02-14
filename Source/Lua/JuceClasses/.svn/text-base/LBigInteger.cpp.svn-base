#include "stdafx.h"
#include "LBigInteger.h"


void LBigInteger::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
			class_<BigInteger>("JUCEBigInteger")
		,
			class_<LBigInteger,BigInteger>("BigInteger")
				.def(constructor<>())
				.def(constructor<int>())
				.def(const_self + BigInteger ())
				.def(const_self - BigInteger ())
				.def(const_self * BigInteger ())
				.def(const_self / BigInteger ())
				.def(const_self < BigInteger ())
				.def(const_self <= BigInteger ())
				.def(const_self == BigInteger ())
				//.def("xor", &LBigInteger::xor)
				//.def("and", &LBigInteger::and)
				//.def("or", &LBigInteger::or)
				.def("swapWith", &BigInteger::swapWith)
				.def("isZero", &BigInteger::isZero)
				.def("isOne", &BigInteger::isOne)
				.def("toInteger", &BigInteger::toInteger)
				.def("clear", &BigInteger::clear)
				.def("clearBit", &BigInteger::clearBit)
				.def("setBit", (void (BigInteger::*)(int))&BigInteger::setBit)
				.def("setBit", (void (BigInteger::*)(int,bool))&BigInteger::setBit)
				.def("setRange", &BigInteger::setRange)
				.def("insertBit", &BigInteger::insertBit)
				.def("getBitRange", &BigInteger::getBitRange)
				.def("getBitRangeAsInt", &BigInteger::getBitRangeAsInt)
				.def("setBitRangeAsInt", &BigInteger::setBitRangeAsInt)
				.def("shiftBits", &BigInteger::shiftBits)
				.def("countNumberOfSetBits", &BigInteger::countNumberOfSetBits)
				.def("findNextSetBit", &BigInteger::findNextSetBit)
				.def("findNextClearBit", &BigInteger::findNextClearBit)
				.def("getHighestBit", &BigInteger::getHighestBit)
				.def("compare", &BigInteger::compare)
				.def("compareAbsolute", &BigInteger::compareAbsolute)
				.def("divideBy", &BigInteger::divideBy)
				.def("findGreatestCommonDivisor", &BigInteger::findGreatestCommonDivisor)
				.def("exponentModulo", &BigInteger::exponentModulo)
				.def("inverseModulo", &BigInteger::inverseModulo)
				.def("isNegative", &BigInteger::isNegative)
				.def("setNegative", &BigInteger::setNegative)
				.def("negate", &BigInteger::negate)
				.def("toString", &BigInteger::toString)
				.def("parseString", &BigInteger::parseString)
				.def("toMemoryBlock", &BigInteger::toMemoryBlock)
				.def("loadFromMemoryBlock", &BigInteger::loadFromMemoryBlock)
	];
}