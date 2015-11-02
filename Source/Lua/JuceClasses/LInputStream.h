#ifndef L_INPUT_STREAM
#define L_INPUT_STREAM

extern  "C"
{
	#include "lua.h"
}

class LInputStream
{
	public:
		/*double getTotalLength();
		bool isExhausted();
		double getPosition();
		bool setPosition (double newPosition);
		void skipNextBytes (double numBytesToSkip);
		int readIntoMemoryBlock (LMemoryBlock &destBlock, double maxNumBytesToRead);
		*/
		static void wrapForLua (lua_State *L);
};

#endif
