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
		LPathStrokeType(float strokeThickness, JointStyle jointStyle, EndCapStyle endStyle) : PathStrokeType(strokeThickness, jointStyle, endStyle) {}
		LPathStrokeType(float strokeThickness) : PathStrokeType(strokeThickness) {}
		LPathStrokeType(const LPathStrokeType &other) : PathStrokeType(other) {}
        void createDashedStrokeWrap (Path &destPath, const Path &sourcePath, const luabind::object dashLengths, const AffineTransform &transform, float extraAccuracy);
};

#endif
