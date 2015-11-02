#ifndef L_BIG_INTEGER
#define L_BIG_INTEGER

#include "JuceHeader.h"
extern  "C"
{
	#include "lua.h"
}

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
