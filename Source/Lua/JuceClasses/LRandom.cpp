#include "stdafx.h"
#include "LRandom.h"

void LRandom::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Random>("Random")
				.def(constructor<int64>())
				.def(constructor<>())
				.def("nextInt", (int (Random::*)(void) noexcept)&Random::nextInt)
				.def("nextInt", (int (Random::*)(int) noexcept)&Random::nextInt)
				.def("nextInt64", &Random::nextInt64)
				.def("nextFloat", &Random::nextFloat)
				.def("nextDouble", &Random::nextDouble)
				.def("nextBool", &Random::nextBool)
				.def("nextLargeNumber", &Random::nextLargeNumber)
				.def("fillBitsRandomly", (void (Random::*) (void *, size_t))&Random::fillBitsRandomly)
				.def("fillBitsRandomly", (void (Random::*) (BigInteger &, int, int))&Random::fillBitsRandomly)
				.def("setSeed", &Random::setSeed)
				.def("combineSeed", &Random::combineSeed)
				.def("setSeedRandomly", &Random::setSeedRandomly)
				.scope
				[
					def("getSystemRandom", &Random::getSystemRandom)
				]
	];
}