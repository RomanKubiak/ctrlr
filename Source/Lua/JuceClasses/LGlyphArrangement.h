#ifndef L_GLYPH_ARRANGEMENT
#define L_GLYPH_ARRANGEMENT

extern  "C"
{
	#include "lua.h"
}

class LGlyphArrangement
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
