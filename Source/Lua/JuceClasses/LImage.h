#ifndef L_IMAGE
#define L_IMAGE

#include "JuceHeader.h"
extern  "C"
{
	#include "lua.h"
}

class LImage
{
	public:
        static Image null() { return (Image()); }
		static void wrapForLua (lua_State *L);
};

#endif
