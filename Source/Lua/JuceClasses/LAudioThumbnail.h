#ifndef L_AUDIO_THUMBNAIL
#define L_AUDIO_THUMBNAIL

extern  "C"
{
	#include "lua.h"
}

class LAudioThumbnail
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
