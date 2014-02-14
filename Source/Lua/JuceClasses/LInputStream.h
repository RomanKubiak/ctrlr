#ifndef __L_INPUT_STREAM__
#define __L_INPUT_STREAM__

#include "CtrlrLuaManager.h"

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