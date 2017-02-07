#include "CtrlrLuaObjectWrapper.h"
#include "CtrlrLuabind.h"


CtrlrLuaObjectWrapper::CtrlrLuaObjectWrapper()
{
	new luabind::object();
}

CtrlrLuaObjectWrapper::CtrlrLuaObjectWrapper(luabind::object const& other)
{
	o = new luabind::object(other);
}

CtrlrLuaObjectWrapper::operator luabind::object &()
{
	return *o;
}

CtrlrLuaObjectWrapper::operator luabind::object()
{
	return *o;
}

const luabind::object &CtrlrLuaObjectWrapper::getLuabindObject() const
{
	return *o;
}

const luabind::object &CtrlrLuaObjectWrapper::getObject() const
{
	return *o;
}
