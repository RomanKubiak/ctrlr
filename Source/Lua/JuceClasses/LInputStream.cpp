#include "stdafx.h"
#include "LInputStream.h"

/*
double LInputStream::getTotalLength()
{
	return ( (double) InputStream::getTotalLength());
}

bool LInputStream::isExhausted()
{
}

double LInputStream::getPosition()
{
}

bool LInputStream::setPosition (double newPosition)
{
}

void LInputStream::skipNextBytes (double numBytesToSkip)
{
}

int LInputStream::readIntoMemoryBlock (LMemoryBlock &destBlock, double maxNumBytesToRead)
{
}
*/
void LInputStream::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<InputStream>("InputStream")
	];
}