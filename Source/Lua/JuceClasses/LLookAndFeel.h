#ifndef L_LOOK_AND_FEEL
#define L_LOOK_AND_FEEL

#include "CtrlrLuaManager.h"
#include "CtrlrLog.h"

class LLookAndFeel_V3 : public LookAndFeel_V3, public luabind::wrap_base
{
	public:
	    LLookAndFeel_V3() {_DBG("LLookAndFeel_V3::ctor"); }
		virtual void drawButtonBackground (Graphics &g, Button &b, const Colour &c, bool over, bool down) override
		{
		    _DBG("LLookAndFeel_V3::drawButtonBackground");
		    call<void>("drawButtonBackground", boost::ref (g), boost::ref(b), c, over, down);
		}

		static void def_drawButtonBackground (LookAndFeel_V3 *ptr, Graphics &g, Button &b, const Colour &c, bool over, bool down)
		{
		    _DBG("LLookAndFeel_V3::def_drawButtonBackground");
		    return (ptr->LookAndFeel_V3::drawButtonBackground (g,b,c,over,down));
		}

		static void wrapForLua (lua_State *L);
};

#endif
