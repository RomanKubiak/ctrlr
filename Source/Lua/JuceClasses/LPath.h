#ifndef L_PATH
#define L_PATH

#include "JuceHeader.h"
#include "luabind/object_fwd.hpp"

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
