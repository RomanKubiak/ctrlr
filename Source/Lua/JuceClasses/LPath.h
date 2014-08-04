#ifndef __L_PATH__
#define __L_PATH__

#include "CtrlrLuaManager.h"

class LPath
{
	public:
		LPath() {}
		static void wrapForLua (lua_State *L);
};

class LPathStrokeType : public PathStrokeType
{
    public:
        void createDashedStrokeWrap (Path &destPath, const Path &sourcePath, const luabind::object dashLengths, const AffineTransform &transform, float extraAccuracy);
};

#endif
