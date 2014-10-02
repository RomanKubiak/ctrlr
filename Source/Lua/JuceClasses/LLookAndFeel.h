#ifndef L_LOOK_AND_FEEL
#define L_LOOK_AND_FEEL

#include "LookAndFeelBase.h"

class LLookAndFeel : public LookAndFeelBase, public luabind::wrap_base
{
	public:
  		LLookAndFeel() : LookAndFeelBase(*this){}
	 	static void wrapForLua (lua_State *L);
};

#endif
