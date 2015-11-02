#ifndef L_DRAWABLE
#define L_DRAWABLE

#include "JuceHeader.h"
extern  "C"
{
	#include "lua.h"
}

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
