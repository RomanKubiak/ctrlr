#ifndef L_AFFINE_TRANSFORM
#define L_AFFINE_TRANSFORM

extern  "C"
{
	#include "lua.h"
}

class LAffineTransform
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
