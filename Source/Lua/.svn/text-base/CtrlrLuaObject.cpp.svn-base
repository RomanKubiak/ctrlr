#include "stdafx.h"
#include "CtrlrLuaObject.h"
#include "CtrlrUtilities.h"

CtrlrLuaObject::CtrlrLuaObject()
{
}

CtrlrLuaObject::~CtrlrLuaObject()
{
}

const int CtrlrLuaObject::getPropertyInt(const String &propertyName)
{
	return (getProperty(propertyName));
}

const double CtrlrLuaObject::getPropertyDouble(const String &propertyName)
{
	return (getProperty(propertyName));
}

const String CtrlrLuaObject::getPropertyString(const String &propertyName)
{
	return (getProperty(propertyName));
}

void CtrlrLuaObject::setPropertyDouble(const String &propertyName, const double value)
{
	if (Identifier::isValidIdentifier (propertyName))
		setProperty (propertyName, value);
}

void CtrlrLuaObject::setPropertyColour(const String &propertyName, const Colour value)
{
	if (Identifier::isValidIdentifier (propertyName))
		setProperty (propertyName, value.toString());
}

void CtrlrLuaObject::setPropertyInt(const String &propertyName, const int value)
{
	if (Identifier::isValidIdentifier (propertyName))
		setProperty (propertyName, value);
}

void CtrlrLuaObject::setPropertyString(const String &propertyName, const String &value)
{
	if (Identifier::isValidIdentifier (propertyName))
		setProperty (propertyName, removeInvalidChars(value));
}

void CtrlrLuaObject::removeProperty (const Identifier &propertyName)
{
	getObjectTree().removeProperty (propertyName, 0);
}

void CtrlrLuaObject::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrLuaObject>("CtrlrLuaObject")
			.def("getPropertyInt", &CtrlrLuaObject::getPropertyInt)
			.def("getPropertyDouble", &CtrlrLuaObject::getPropertyDouble)
			.def("getPropertyString", &CtrlrLuaObject::getPropertyString)
			.def("setPropertyInt", &CtrlrLuaObject::setPropertyInt)
			.def("setPropertyColour", &CtrlrLuaObject::setPropertyColour)
			.def("setPropertyDouble", &CtrlrLuaObject::setPropertyDouble)
			.def("setPropertyString", &CtrlrLuaObject::setPropertyString)
			.def("removeProperty", &CtrlrLuaObject::removeProperty)
			.def("setProperty", (void (CtrlrLuaObject::*)(const Identifier &, const var &, const bool))&CtrlrLuaObject::setProperty)
			.def("getProperty", &CtrlrLuaObject::getProperty)
			.def("getObjectTree", &CtrlrLuaObject::getObjectTree)
    ];
}