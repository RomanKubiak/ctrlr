#ifndef __L_BIG_INTEGER__
#define __L_BIG_INTEGER__

#include "CtrlrLuaManager.h"

class LBigInteger : public BigInteger
{
	public:
		LBigInteger() {}
		LBigInteger(int value) : BigInteger(value) {}

		/*void xor(const BigInteger &other)
		{
			BigInteger i = *this ^ other;
			swapWith(i);
		}

		void and(const BigInteger &other)
		{
			BigInteger i = *this & other;
			swapWith(i);
		}

		void or(const BigInteger &other)
		{
			BigInteger i = *this | other;
			swapWith(i);
		}
		*/
		static void wrapForLua (lua_State *L);
};

#endif