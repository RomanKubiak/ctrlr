#ifndef CTRLR_LUA_OBJECT_WRAPPER
#define CTRLR_LUA_OBJECT_WRAPPER

#include "luabind/object_fwd.hpp"

class CtrlrLuaObjectWrapper
{
	public:
		CtrlrLuaObjectWrapper();
    CtrlrLuaObjectWrapper(luabind::object const& other);
		operator luabind::object &();
		operator luabind::object();
		const luabind::object &getLuabindObject() const;
		const luabind::object &getObject() const;

	private:
		luabind::object *o;
};

#endif
