#ifndef __CTRLR_LUA_RECTANGLE__
#define __CTRLR_LUA_RECTANGLE__
#ifdef _WIN32
#pragma warning(disable:4100)
#endif

extern "C"
{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

#include "CtrlrMacros.h"

//==============================================================================
/** @brief A class that represents a rectangle area, used in Graphics see http://www.rawmaterialsoftware.com/juce/api/classRectangle.html for details
 *
 */
class CtrlrLuaRectangle
{
	public:
		CtrlrLuaRectangle();
		CtrlrLuaRectangle(const juce::Rectangle<int> &_r);
		CtrlrLuaRectangle(int x, int y, int width, int height);
		~CtrlrLuaRectangle();
		operator Rectangle<int> () { return r; }

		int getX();
		int getY();
		int getWidth();
		int getHeight();
		int getRight();
		int getBottom();
		int getCentreX();
		int getCentreY();
		int getAspectRatio();
		void setPosition(const int x, const int y);
		CtrlrLuaRectangle withPosition(const int x, const int y);
		void setSize (const int width, const int height);
		CtrlrLuaRectangle withSize(const int width, const int height);
		void setBounds (const int x, const int y, const int width, const int height);
		void setX(const int x);
		void setY(const int y);
		void setWidth(const int width);
		void setHeight(const int height);
		CtrlrLuaRectangle withX(const int p);
		CtrlrLuaRectangle withY(const int p);
		CtrlrLuaRectangle withWidth(const int p);
		CtrlrLuaRectangle withHeight(const int p);
		CtrlrLuaRectangle withTop(const int p);
		CtrlrLuaRectangle withBottom(const int p);
		CtrlrLuaRectangle withLeft(const int p);
		CtrlrLuaRectangle withRight(const int p);
		void setLeft(const int p);
		void setTop(const int p);
		void setRight(const int p);
		void setBottom(const int p);
		void translate (const int x, const int y);
		CtrlrLuaRectangle translated (const int x, const int y);
		void expand (const int x, const int y);
		void reduce (const int x, const int y);
		bool contains (const int x, const int y);
		bool contains (const CtrlrLuaRectangle &other);
		bool intersects (const CtrlrLuaRectangle &other);
		CtrlrLuaRectangle getIntersection (const CtrlrLuaRectangle &other);
		CtrlrLuaRectangle getUnion (const CtrlrLuaRectangle &other);
		bool enlargeIfAdjacent (const CtrlrLuaRectangle &other);
		bool reduceIfPartlyContainedIn (const CtrlrLuaRectangle &other);
		const CtrlrLuaRectangle getSmallestIntegerContainer();
		const String toString();

		juce::Rectangle<int> getRect() const { return (r); }
		static void wrapForLua (lua_State *L);

		JUCE_LEAK_DETECTOR(CtrlrLuaRectangle)

	private:
		juce::Rectangle<int> r;
};

#endif
