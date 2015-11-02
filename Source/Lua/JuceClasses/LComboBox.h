#ifndef L_COMBO_BOX
#define L_COMBO_BOX

extern  "C"
{
	#include "lua.h"
}

class LComboBox
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
