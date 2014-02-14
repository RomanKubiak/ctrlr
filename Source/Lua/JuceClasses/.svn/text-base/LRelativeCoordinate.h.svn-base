#ifndef __L_RELATIVE_COORDINATE__
#define __L_RELATIVE_COORDINATE__

#include "CtrlrLuaManager.h"

class LRelativeCoordinate : public RelativeCoordinate
{
	public:
		LRelativeCoordinate (const Expression &expression) : RelativeCoordinate(expression)
		{}
		LRelativeCoordinate (const RelativeCoordinate &other) : RelativeCoordinate(other)
		{}
		LRelativeCoordinate (double absoluteDistanceFromOrigin) : RelativeCoordinate(absoluteDistanceFromOrigin)
		{}
		LRelativeCoordinate (const String &stringVersion) : RelativeCoordinate(stringVersion)
		{}

		bool references (const String &coordName, const Expression::Scope *evaluationScope) const
		{
			return (RelativeCoordinate::references(coordName, evaluationScope));
		}
		
		static void wrapForLua (lua_State *L);
};

#endif