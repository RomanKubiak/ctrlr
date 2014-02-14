#ifndef __L_DRAWABLE__
#define __L_DRAWABLE__

#include "CtrlrLuaManager.h"

class LDrawable
{
	public:
		static void wrapForLua (lua_State *L);

		static DrawableComposite *toDrawableComposite(Drawable *drawableToConvert)
		{
			return (dynamic_cast<DrawableComposite*>(drawableToConvert));
		}
};

#endif