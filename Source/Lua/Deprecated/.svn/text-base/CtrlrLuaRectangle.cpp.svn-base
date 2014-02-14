#include "stdafx.h"
#include <luabind/luabind.hpp>
#include "CtrlrLuaRectangle.h"

CtrlrLuaRectangle::CtrlrLuaRectangle(const Rectangle<int> &_r) : r(_r)
{
}

CtrlrLuaRectangle::CtrlrLuaRectangle(int x, int y, int width, int height)
{
}

CtrlrLuaRectangle::CtrlrLuaRectangle()
{
}

CtrlrLuaRectangle::~CtrlrLuaRectangle()
{
}

int CtrlrLuaRectangle::getX()
{
	return (r.getX());
}

int CtrlrLuaRectangle::getY()
{
	return (r.getY());
}

int CtrlrLuaRectangle::getWidth()
{
	return (r.getWidth());
}

int CtrlrLuaRectangle::getHeight()
{
	return (r.getHeight());
}

int CtrlrLuaRectangle::getRight()
{
	return (r.getRight());
}

int CtrlrLuaRectangle::getBottom()
{
	return (r.getBottom());
}

int CtrlrLuaRectangle::getCentreX()
{
	return (r.getCentreX());
}

int CtrlrLuaRectangle::getCentreY()
{
	return (r.getCentreY());
}

int CtrlrLuaRectangle::getAspectRatio()
{
	return (r.getAspectRatio());
}

void CtrlrLuaRectangle::setPosition(const int x, const int y)
{
	r.setPosition(x,y);
}

CtrlrLuaRectangle CtrlrLuaRectangle::withPosition(const int x, const int y)
{
	return (r.withPosition(x,y));
}

void CtrlrLuaRectangle::setSize (const int width, const int height)
{
	r.setSize(width,height);
}

CtrlrLuaRectangle CtrlrLuaRectangle::withSize(const int width, const int height)
{
	return (r.withSize(width,height));
}

void CtrlrLuaRectangle::setBounds (const int x, const int y, const int width, const int height)
{
	r.setSize(width,height);
}

void CtrlrLuaRectangle::setX(const int x)
{
	r.setX(x);
}

void CtrlrLuaRectangle::setY(const int y)
{
	r.setY(y);
}

void CtrlrLuaRectangle::setWidth(const int width)
{
	r.setWidth(width);
}

void CtrlrLuaRectangle::setHeight(const int height)
{
	r.setHeight(height);
}

CtrlrLuaRectangle CtrlrLuaRectangle::withX(const int p)
{
	return (r.withX(p));
}

CtrlrLuaRectangle CtrlrLuaRectangle::withY(const int p)
{
	return (r.withY(p));
}

CtrlrLuaRectangle CtrlrLuaRectangle::withWidth(const int p)
{
	return (r.withWidth(p));
}

CtrlrLuaRectangle CtrlrLuaRectangle::withHeight(const int p)
{
	return (r.withHeight(p));
}

CtrlrLuaRectangle CtrlrLuaRectangle::withTop(const int p)
{
	return (r.withTop(p));
}

CtrlrLuaRectangle CtrlrLuaRectangle::withBottom(const int p)
{
	return (r.withBottom(p));
}

CtrlrLuaRectangle CtrlrLuaRectangle::withLeft(const int p)
{
	return (r.withLeft(p));
}

CtrlrLuaRectangle CtrlrLuaRectangle::withRight(const int p)
{
	return (r.withRight(p));
}

void CtrlrLuaRectangle::setLeft(const int p)
{
	r.setLeft(p);
}

void CtrlrLuaRectangle::setTop(const int p)
{
	r.setTop(p);
}

void CtrlrLuaRectangle::setRight(const int p)
{
	r.setRight(p);
}

void CtrlrLuaRectangle::setBottom(const int p)
{
	r.setBottom(p);
}

void CtrlrLuaRectangle::translate (const int x, const int y)
{
	r.translate(x,y);
}

CtrlrLuaRectangle CtrlrLuaRectangle::translated (const int x, const int y)
{
	return (r.translated(x,y));
}

void CtrlrLuaRectangle::expand (const int x, const int y)
{
	r.expand(x,y);
}

void CtrlrLuaRectangle::reduce (const int x, const int y)
{
	r.reduce(x,y);
}

bool CtrlrLuaRectangle::contains (const int x, const int y)
{
	return (r.contains(x,y));
}

bool CtrlrLuaRectangle::contains (const CtrlrLuaRectangle &other)
{
	return (r.contains(other.getRect()));
}

bool CtrlrLuaRectangle::intersects (const CtrlrLuaRectangle &other)
{
	return (r.intersects(other.getRect()));
}

CtrlrLuaRectangle CtrlrLuaRectangle::getIntersection (const CtrlrLuaRectangle &other)
{
	return (r.getIntersection(other.getRect()));
}

CtrlrLuaRectangle CtrlrLuaRectangle::getUnion (const CtrlrLuaRectangle &other)
{
	return (r.getUnion(other.getRect()));
}

bool CtrlrLuaRectangle::enlargeIfAdjacent (const CtrlrLuaRectangle &other)
{
	return (r.enlargeIfAdjacent(other.getRect()));
}

bool CtrlrLuaRectangle::reduceIfPartlyContainedIn (const CtrlrLuaRectangle &other)
{
	return (r.reduceIfPartlyContainedIn(other.getRect()));
}

/*const CtrlrLuaRectangle CtrlrLuaRectangle::getSmallestIntegerContainer()
{
	return (r.getSmallestIntegerContainer());
}
*/
const String CtrlrLuaRectangle::toString()
{
	return (r.toString());
}

void CtrlrLuaRectangle::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrLuaRectangle>("CtrlrLuaRectangle")
			.def("getX", &CtrlrLuaRectangle::getX)
			.def("getY", &CtrlrLuaRectangle::getY)
			.def("getWidth", &CtrlrLuaRectangle::getWidth)
			.def("getHeight", &CtrlrLuaRectangle::getHeight)
			.def("getRight", &CtrlrLuaRectangle::getRight)
			.def("getBottom", &CtrlrLuaRectangle::getBottom)
			.def("getCentreX", &CtrlrLuaRectangle::getCentreX)
			.def("getCentreY", &CtrlrLuaRectangle::getCentreY)
			.def("getAspectRatio", &CtrlrLuaRectangle::getAspectRatio)
			.def("setPosition", &CtrlrLuaRectangle::setPosition)
			.def("withPosition", &CtrlrLuaRectangle::withPosition)
			.def("setSize", &CtrlrLuaRectangle::setSize)
			.def("setBounds", &CtrlrLuaRectangle::setBounds)
			.def("setX", &CtrlrLuaRectangle::setX)
			.def("setY", &CtrlrLuaRectangle::setY)
			.def("setWidth", &CtrlrLuaRectangle::setWidth)
			.def("setHeight", &CtrlrLuaRectangle::setHeight)
			.def("withX", &CtrlrLuaRectangle::withX)
			.def("withY", &CtrlrLuaRectangle::withY)
			.def("withWidth", &CtrlrLuaRectangle::withWidth)
			.def("withHeight", &CtrlrLuaRectangle::withHeight)
			.def("withTop", &CtrlrLuaRectangle::withTop)
			.def("withBottom", &CtrlrLuaRectangle::withBottom)
			.def("withLeft", &CtrlrLuaRectangle::withLeft)
			.def("withRight", &CtrlrLuaRectangle::withRight)
			.def("setLeft", &CtrlrLuaRectangle::setLeft)
			.def("setTop", &CtrlrLuaRectangle::setTop)
			.def("setRight", &CtrlrLuaRectangle::setRight)
			.def("setBottom", &CtrlrLuaRectangle::setBottom)
			.def("translate", &CtrlrLuaRectangle::translate)
			.def("translated", &CtrlrLuaRectangle::translated)
			.def("expand", &CtrlrLuaRectangle::expand)
			.def("reduce", &CtrlrLuaRectangle::reduce)
			.def("contains", (bool (CtrlrLuaRectangle::*)(const int, const int)) &CtrlrLuaRectangle::contains)
			.def("contains", (bool (CtrlrLuaRectangle::*)(const CtrlrLuaRectangle &)) &CtrlrLuaRectangle::contains)
			.def("intersects", &CtrlrLuaRectangle::intersects)
			.def("getIntersection", &CtrlrLuaRectangle::getIntersection)
			.def("getUnion", &CtrlrLuaRectangle::getUnion)
			.def("enlargeIfAdjacent", &CtrlrLuaRectangle::enlargeIfAdjacent)
			.def("reduceIfPartlyContainedIn", &CtrlrLuaRectangle::reduceIfPartlyContainedIn)
			//.def("getSmallestIntegerContainer", &CtrlrLuaRectangle::getSmallestIntegerContainer)
			.def("toString", &CtrlrLuaRectangle::toString)
	];

}