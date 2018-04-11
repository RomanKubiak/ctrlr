#ifndef CTRLR_LUA_OBJECT_WRAPPER
#define CTRLR_LUA_OBJECT_WRAPPER

namespace luabind {
	namespace adl {
		class object;
		class argument;
		template <class Base> struct table;
	} // namespace adl
	using adl::object;
	using adl::argument;
	using adl::table;
} // namespace luabind

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
