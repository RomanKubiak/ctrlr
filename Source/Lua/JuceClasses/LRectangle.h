#ifndef L_RECTANGLE
#define L_RECTANGLE

#include "JuceHeader.h"
extern  "C"
{
	#include "lua.h"
}

#ifdef _WIN32
#pragma warning(disable:4244)
#endif

class LRectangle : public Rectangle<float>
{
	public:
	    LRectangle() : Rectangle<float>() {}
	    LRectangle(const Rectangle<float> &other) : Rectangle<float>(other) {}
	    LRectangle(float x, float y, float w, float h) : Rectangle<float>(x,y,w,h) {}
	    LRectangle(float x, float y) : Rectangle<float>(x,y) {}
	    LRectangle(const Point<float> &top, const Point<float> &bottom) : Rectangle<float>(top,bottom) {}
		static void wrapForLua (lua_State *L);
		Rectangle<int> toInt()
		{
		    return (toType<int>());
		}
};

#endif
