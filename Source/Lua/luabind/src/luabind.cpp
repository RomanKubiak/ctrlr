// Copyright (c) 2004 Daniel Wallin and Arvid Norberg

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
// ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
// SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
// ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#define LUABIND_BUILDING

#include "stdafx.h"
#include <boost/foreach.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/version.hpp>

namespace luabind
{
   LUABIND_API detail::nil_type nil;
}

namespace luabind { namespace detail {


    namespace
    {
      struct cast_entry
      {
          cast_entry(class_id src, class_id target, cast_function cast)
            : src(src)
            , target(target)
            , cast(cast)
          {}

          class_id src;
          class_id target;
          cast_function cast;
      };

    } // namespace unnamed

    struct class_registration : registration
    {
        class_registration(char const* name);

        void register_(lua_State* L) const;

        const char* m_name;

        mutable std::map<const char*, int, detail::ltstr> m_static_constants;

        typedef std::pair<type_id, cast_function> base_desc;
        mutable std::vector<base_desc> m_bases;

        type_id m_type;
        class_id m_id;
        class_id m_wrapper_id;
        type_id m_wrapper_type;
        std::vector<cast_entry> m_casts;

        scope m_scope;
        scope m_members;
        scope m_default_members;
    };

    class_registration::class_registration(char const* name)
    {
        m_name = name;
    }

    void class_registration::register_(lua_State* L) const
    {
        LUABIND_CHECK_STACK(L);

        assert(lua_type(L, -1) == LUA_TTABLE);

        lua_pushstring(L, m_name);

        detail::class_rep* crep;

        detail::class_registry* r = detail::class_registry::get_registry(L);
        // create a class_rep structure for this class.
        // allocate it within lua to let lua collect it on
        // lua_close(). This is better than allocating it
        // as a static, since it will then be destructed
        // when the program exits instead.
        // warning: we assume that lua will not
        // move the userdata memory.
        lua_newuserdata(L, sizeof(detail::class_rep));
        crep = reinterpret_cast<detail::class_rep*>(lua_touserdata(L, -1));

        new(crep) detail::class_rep(
            m_type
            , m_name
            , L
		);

        // register this new type in the class registry
        r->add_class(m_type, crep);

        lua_pushstring(L, "__luabind_class_map");
        lua_rawget(L, LUA_REGISTRYINDEX);
        class_map& classes = *static_cast<class_map*>(
            lua_touserdata(L, -1));
        lua_pop(L, 1);

        classes.put(m_id, crep);

        bool const has_wrapper = m_wrapper_id != registered_class<null_type>::id;

        if (has_wrapper)
            classes.put(m_wrapper_id, crep);

        crep->m_static_constants.swap(m_static_constants);

		detail::class_registry* registry = detail::class_registry::get_registry(L);

        crep->get_default_table(L);
        m_scope.register_(L);
        m_default_members.register_(L);
        lua_pop(L, 1);

        crep->get_table(L);
        m_members.register_(L);
        lua_pop(L, 1);

        lua_pushstring(L, "__luabind_cast_graph");
        lua_gettable(L, LUA_REGISTRYINDEX);
        cast_graph* const casts = static_cast<cast_graph*>(
            lua_touserdata(L, -1));
        lua_pop(L, 1);

        lua_pushstring(L, "__luabind_class_id_map");
        lua_gettable(L, LUA_REGISTRYINDEX);
        class_id_map* const class_ids = static_cast<class_id_map*>(
            lua_touserdata(L, -1));
        lua_pop(L, 1);

        class_ids->put(m_id, m_type);

        if (has_wrapper)
            class_ids->put(m_wrapper_id, m_wrapper_type);

        BOOST_FOREACH(cast_entry const& e, m_casts)
        {
            casts->insert(e.src, e.target, e.cast);
        }

        for (std::vector<base_desc>::iterator i = m_bases.begin();
            i != m_bases.end(); ++i)
        {
            LUABIND_CHECK_STACK(L);

            // the baseclass' class_rep structure
            detail::class_rep* bcrep = registry->find_class(i->first);

            detail::class_rep::base_info base;
            base.pointer_offset = 0;
            base.base = bcrep;

            crep->add_base_class(base);

            // copy base class table
			crep->get_table(L);
			bcrep->get_table(L);
            lua_pushnil(L);

            while (lua_next(L, -2))
            {
                lua_pushvalue(L, -2); // copy key
                lua_gettable(L, -5);

                if (!lua_isnil(L, -1))
                {
                    lua_pop(L, 2);
                    continue;
                }

                lua_pop(L, 1);
                lua_pushvalue(L, -2); // copy key
                lua_insert(L, -2);

                lua_settable(L, -5);
            }
            lua_pop(L, 2);

            // copy base class detaults table
			crep->get_default_table(L);
			bcrep->get_default_table(L);
            lua_pushnil(L);

            while (lua_next(L, -2))
            {
                lua_pushvalue(L, -2); // copy key
                lua_gettable(L, -5);

                if (!lua_isnil(L, -1))
                {
                    lua_pop(L, 2);
                    continue;
                }

                lua_pop(L, 1);
                lua_pushvalue(L, -2); // copy key
                lua_insert(L, -2);

                lua_settable(L, -5);
            }
            lua_pop(L, 2);

		}

        lua_settable(L, -3);
    }

    // -- interface ---------------------------------------------------------

    class_base::class_base(char const* name)
        : scope(std::auto_ptr<registration>(
                m_registration = new class_registration(name))
          )
    {
    }

    void class_base::init(
        type_id const& type_id_, class_id id
      , type_id const& wrapper_type, class_id wrapper_id)
    {
        m_registration->m_type = type_id_;
        m_registration->m_id = id;
        m_registration->m_wrapper_type = wrapper_type;
        m_registration->m_wrapper_id = wrapper_id;
    }

    void class_base::add_base(type_id const& base, cast_function cast)
    {
        m_registration->m_bases.push_back(std::make_pair(base, cast));
    }

	void class_base::add_member(registration* member)
	{
		std::auto_ptr<registration> ptr(member);
		m_registration->m_members.operator,(scope(ptr));
	}

	void class_base::add_default_member(registration* member)
	{
		std::auto_ptr<registration> ptr(member);
		m_registration->m_default_members.operator,(scope(ptr));
	}

    const char* class_base::name() const
    {
        return m_registration->m_name;
    }

    void class_base::add_static_constant(const char* name, int val)
    {
        m_registration->m_static_constants[name] = val;
    }

    void class_base::add_inner_scope(scope& s)
    {
        m_registration->m_scope.operator,(s);
    }

    void class_base::add_cast(
        class_id src, class_id target, cast_function cast)
    {
        m_registration->m_casts.push_back(cast_entry(src, target, cast));
    }

	void add_custom_name(type_id const& i, std::string& s)
	{
		s += " [";
		s += i.name();
		s += "]";
	}

    std::string get_class_name(lua_State* L, type_id const& i)
    {
        std::string ret;

		assert(L);

		class_registry* r = class_registry::get_registry(L);
        class_rep* crep = r->find_class(i);

        if (crep == 0)
        {
            ret = "custom";
			add_custom_name(i, ret);
        }
        else
        {
            /* TODO reimplement this?
            if (i == crep->holder_type())
            {
                ret += "smart_ptr<";
                ret += crep->name();
                ret += ">";
            }
            else if (i == crep->const_holder_type())
            {
                ret += "smart_ptr<const ";
                ret += crep->name();
                ret += ">";
            }
            else*/
            {
                ret += crep->name();
            }
        }
        return ret;
    }

}} // namespace luabind::detail

namespace luabind
{
	LUABIND_API class_info get_class_info(argument const& o)
	{
		lua_State* L = o.interpreter();

		o.push(L);
        detail::object_rep* obj = detail::get_instance(L, -1);

        if (!obj)
        {
            class_info result;
            result.name = lua_typename(L, lua_type(L, -1));
            lua_pop(L, 1);
            result.methods = newtable(L);
            result.attributes = newtable(L);
            return result;
        }

        lua_pop(L, 1);

        obj->crep()->get_table(L);
        object table(from_stack(L, -1));
        lua_pop(L, 1);

        class_info result;
        result.name = obj->crep()->name();
        result.methods = newtable(L);
        result.attributes = newtable(L);

        std::size_t index = 1;

        for (iterator i(table), e; i != e; ++i)
        {
            if (type(*i) != LUA_TFUNCTION)
                continue;

            // We have to create a temporary `object` here, otherwise the proxy
            // returned by operator->() will mess up the stack. This is a known
            // problem that probably doesn't show up in real code very often.
            object member(*i);
            member.push(L);
            detail::stack_pop pop(L, 1);

            if (lua_tocfunction(L, -1) == &detail::property_tag)
            {
                result.attributes[index++] = i.key();
            }
            else
            {
                result.methods[i.key()] = *i;
            }
        }

        return result;
	}

    LUABIND_API object get_class_names(lua_State* L)
    {
        detail::class_registry* reg = detail::class_registry::get_registry(L);

        std::map<type_id, detail::class_rep*> const& classes = reg->get_classes();

        object result = newtable(L);
        std::size_t index = 1;

        for (std::map<type_id, detail::class_rep*>::const_iterator iter = classes.begin();
            iter != classes.end(); ++iter)
        {
            result[index++] = iter->second->name();
        }

        return result;
    }

	LUABIND_API void bind_class_info(lua_State* L)
	{
		module(L)
		[
			class_<class_info>("class_info_data")
				.def_readonly("name", &class_info::name)
				.def_readonly("methods", &class_info::methods)
				.def_readonly("attributes", &class_info::attributes),

            def("class_info", &get_class_info),
            def("class_names", &get_class_names)
		];
	}
}

namespace luabind { namespace detail {

    LUABIND_API void push_instance_metatable(lua_State* L);

    namespace {

        int create_cpp_class_metatable(lua_State* L)
        {
            lua_newtable(L);

            // mark the table with our (hopefully) unique tag
            // that says that the user data that has this
            // metatable is a class_rep
            lua_pushstring(L, "__luabind_classrep");
            lua_pushboolean(L, 1);
            lua_rawset(L, -3);

            lua_pushstring(L, "__gc");
            lua_pushcclosure(
                L
              , &garbage_collector_s<
                    detail::class_rep
                >::apply
                , 0);

            lua_rawset(L, -3);

            lua_pushstring(L, "__call");
            lua_pushcclosure(L, &class_rep::constructor_dispatcher, 0);
            lua_rawset(L, -3);

            lua_pushstring(L, "__index");
            lua_pushcclosure(L, &class_rep::static_class_gettable, 0);
            lua_rawset(L, -3);

            lua_pushstring(L, "__newindex");
            lua_pushcclosure(L, &class_rep::lua_settable_dispatcher, 0);
            lua_rawset(L, -3);

            return luaL_ref(L, LUA_REGISTRYINDEX);
        }

        int create_lua_class_metatable(lua_State* L)
        {
            lua_newtable(L);

            lua_pushstring(L, "__luabind_classrep");
            lua_pushboolean(L, 1);
            lua_rawset(L, -3);

            lua_pushstring(L, "__gc");
            lua_pushcclosure(
                L
              , &detail::garbage_collector_s<
                    detail::class_rep
                >::apply
                , 0);

            lua_rawset(L, -3);

            lua_pushstring(L, "__newindex");
            lua_pushcclosure(L, &class_rep::lua_settable_dispatcher, 0);
            lua_rawset(L, -3);

            lua_pushstring(L, "__call");
            lua_pushcclosure(L, &class_rep::constructor_dispatcher, 0);
            lua_rawset(L, -3);

            lua_pushstring(L, "__index");
            lua_pushcclosure(L, &class_rep::static_class_gettable, 0);
            lua_rawset(L, -3);

            return luaL_ref(L, LUA_REGISTRYINDEX);
        }

    } // namespace unnamed

    class class_rep;

    class_registry::class_registry(lua_State* L)
        : m_cpp_class_metatable(create_cpp_class_metatable(L))
        , m_lua_class_metatable(create_lua_class_metatable(L))
    {
        push_instance_metatable(L);
        m_instance_metatable = luaL_ref(L, LUA_REGISTRYINDEX);
    }

    class_registry* class_registry::get_registry(lua_State* L)
    {

#ifdef LUABIND_NOT_THREADSAFE

        // if we don't have to be thread safe, we can keep a
        // chache of the class_registry pointer without the
        // need of a mutex
        static lua_State* cache_key = 0;
        static class_registry* registry_cache = 0;
        if (cache_key == L) return registry_cache;

#endif

        lua_pushstring(L, "__luabind_classes");
        lua_gettable(L, LUA_REGISTRYINDEX);
        class_registry* p = static_cast<class_registry*>(lua_touserdata(L, -1));
        lua_pop(L, 1);

#ifdef LUABIND_NOT_THREADSAFE

        cache_key = L;
        registry_cache = p;

#endif

        return p;
    }

    void class_registry::add_class(type_id const& info, class_rep* crep)
    {
        // class is already registered
        assert((m_classes.find(info) == m_classes.end())
            && "you are trying to register a class twice");
        m_classes[info] = crep;
    }

    class_rep* class_registry::find_class(type_id const& info) const
    {
        std::map<type_id, class_rep*>::const_iterator i(
            m_classes.find(info));

        if (i == m_classes.end()) return 0; // the type is not registered
        return i->second;
    }

}} // namespace luabind::detail

using namespace luabind::detail;

namespace luabind { namespace detail
{
	LUABIND_API int property_tag(lua_State* L)
	{
		lua_pushstring(L, "luabind: property_tag function can't be called");
		lua_error(L);
		return 0;
	}
}}

luabind::detail::class_rep::class_rep(type_id const& type
	, const char* name
	, lua_State* L
)
	: m_type(type)
	, m_name(name)
	, m_class_type(cpp_class)
	, m_operator_cache(0)
{
	lua_newtable(L);
	handle(L, -1).swap(m_table);
	lua_newtable(L);
	handle(L, -1).swap(m_default_table);
	lua_pop(L, 2);

	class_registry* r = class_registry::get_registry(L);
	assert((r->cpp_class() != LUA_NOREF) && "you must call luabind::open()");

	lua_rawgeti(L, LUA_REGISTRYINDEX, r->cpp_class());
	lua_setmetatable(L, -2);

	lua_pushvalue(L, -1); // duplicate our user data
	m_self_ref.set(L);

	m_instance_metatable = r->cpp_instance();

    lua_pushstring(L, "__luabind_cast_graph");
    lua_gettable(L, LUA_REGISTRYINDEX);
    m_casts = static_cast<cast_graph*>(lua_touserdata(L, -1));
    lua_pop(L, 1);

    lua_pushstring(L, "__luabind_class_id_map");
    lua_gettable(L, LUA_REGISTRYINDEX);
    m_classes = static_cast<class_id_map*>(lua_touserdata(L, -1));
    lua_pop(L, 1);
}

luabind::detail::class_rep::class_rep(lua_State* L, const char* name)
	: m_type(typeid(null_type))
	, m_name(name)
	, m_class_type(lua_class)
	, m_operator_cache(0)
{
	lua_newtable(L);
	handle(L, -1).swap(m_table);
	lua_newtable(L);
	handle(L, -1).swap(m_default_table);
	lua_pop(L, 2);

	class_registry* r = class_registry::get_registry(L);
	assert((r->cpp_class() != LUA_NOREF) && "you must call luabind::open()");

	lua_rawgeti(L, LUA_REGISTRYINDEX, r->lua_class());
	lua_setmetatable(L, -2);
	lua_pushvalue(L, -1); // duplicate our user data
	m_self_ref.set(L);

	m_instance_metatable = r->lua_instance();

    lua_pushstring(L, "__luabind_cast_graph");
    lua_gettable(L, LUA_REGISTRYINDEX);
    m_casts = static_cast<cast_graph*>(lua_touserdata(L, -1));
    lua_pop(L, 1);

    lua_pushstring(L, "__luabind_class_id_map");
    lua_gettable(L, LUA_REGISTRYINDEX);
    m_classes = static_cast<class_id_map*>(lua_touserdata(L, -1));
    lua_pop(L, 1);
}

luabind::detail::class_rep::~class_rep()
{
}

// leaves object on lua stack
std::pair<void*,void*>
luabind::detail::class_rep::allocate(lua_State* L) const
{
	const int size = sizeof(object_rep);
	char* mem = static_cast<char*>(lua_newuserdata(L, size));
	return std::pair<void*,void*>(mem, (void*)0);
}

namespace
{

  bool super_deprecation_disabled = false;

} // namespace unnamed

// this is called as metamethod __call on the class_rep.
int luabind::detail::class_rep::constructor_dispatcher(lua_State* L)
{
    class_rep* cls = static_cast<class_rep*>(lua_touserdata(L, 1));

    int args = lua_gettop(L);

    push_new_instance(L, cls);

    if (super_deprecation_disabled
        && cls->get_class_type() == class_rep::lua_class
        && !cls->bases().empty())
    {

        lua_pushvalue(L, 1);
		lua_pushvalue(L, -2);
        lua_pushcclosure(L, super_callback, 2);
		lua_setglobal(L, "super");
    }

    lua_pushvalue(L, -1);
    lua_replace(L, 1);

    cls->get_table(L);
    lua_pushliteral(L, "__init");
    lua_gettable(L, -2);

    lua_insert(L, 1);

    lua_pop(L, 1);
    lua_insert(L, 1);

    lua_call(L, args, 0);

    if (super_deprecation_disabled)
    {
        lua_pushnil(L);
		lua_setglobal(L, "super");
    }

    return 1;
}

void luabind::detail::class_rep::add_base_class(const luabind::detail::class_rep::base_info& binfo)
{
	// If you hit this assert you are deriving from a type that is not registered
	// in lua. That is, in the class_<> you are giving a baseclass that isn't registered.
	// Please note that if you don't need to have access to the base class or the
	// conversion from the derived class to the base class, you don't need
	// to tell luabind that it derives.
	assert(binfo.base && "You cannot derive from an unregistered type");

	class_rep* bcrep = binfo.base;

	// import all static constants
	for (std::map<const char*, int, ltstr>::const_iterator i = bcrep->m_static_constants.begin();
			i != bcrep->m_static_constants.end(); ++i)
	{
		int& v = m_static_constants[i->first];
		v = i->second;
	}

	// also, save the baseclass info to be used for typecasts
	m_bases.push_back(binfo);
}

LUABIND_API void luabind::disable_super_deprecation()
{
    super_deprecation_disabled = true;
}

int luabind::detail::class_rep::super_callback(lua_State* L)
{
	int args = lua_gettop(L);

	class_rep* crep = static_cast<class_rep*>(lua_touserdata(L, lua_upvalueindex(1)));
	class_rep* base = crep->bases()[0].base;

	if (base->bases().empty())
	{
		lua_pushnil(L);
		lua_setglobal(L, "super");
	}
	else
	{
		lua_pushlightuserdata(L, base);
		lua_pushvalue(L, lua_upvalueindex(2));
		lua_pushcclosure(L, super_callback, 2);
		lua_setglobal(L, "super");
	}

	base->get_table(L);
	lua_pushstring(L, "__init");
	lua_gettable(L, -2);
	lua_insert(L, 1);
	lua_pop(L, 1);

	lua_pushvalue(L, lua_upvalueindex(2));
	lua_insert(L, 2);

	lua_call(L, args + 1, 0);

	// TODO: instead of clearing the global variable "super"
	// store it temporarily in the registry. maybe we should
	// have some kind of warning if the super global is used?
	lua_pushnil(L);
	lua_setglobal(L, "super");
	return 0;
}



int luabind::detail::class_rep::lua_settable_dispatcher(lua_State* L)
{
	class_rep* crep = static_cast<class_rep*>(lua_touserdata(L, 1));

	// get first table
	crep->get_table(L);

	// copy key, value
	lua_pushvalue(L, -3);
	lua_pushvalue(L, -3);
	lua_rawset(L, -3);
	// pop table
	lua_pop(L, 1);

	// get default table
	crep->get_default_table(L);
	lua_replace(L, 1);
	lua_rawset(L, -3);

	crep->m_operator_cache = 0; // invalidate cache

	return 0;
}

/*
	stack:
	1: class_rep
	2: member name
*/
int luabind::detail::class_rep::static_class_gettable(lua_State* L)
{
	class_rep* crep = static_cast<class_rep*>(lua_touserdata(L, 1));

	// look in the static function table
	crep->get_default_table(L);
	lua_pushvalue(L, 2);
	lua_gettable(L, -2);
	if (!lua_isnil(L, -1)) return 1;
	else lua_pop(L, 2);

	const char* key = lua_tostring(L, 2);

	if (std::strlen(key) != lua_rawlen(L, 2))
	{
		lua_pushnil(L);
		return 1;
	}

	std::map<const char*, int, ltstr>::const_iterator j = crep->m_static_constants.find(key);

	if (j != crep->m_static_constants.end())
	{
		lua_pushnumber(L, j->second);
		return 1;
	}

#ifndef LUABIND_NO_ERROR_CHECKING

	{
		std::string msg = "no static '";
		msg += key;
		msg += "' in class '";
		msg += crep->name();
		msg += "'";
		lua_pushstring(L, msg.c_str());
	}
	lua_error(L);

#endif

	lua_pushnil(L);

	return 1;
}

bool luabind::detail::is_class_rep(lua_State* L, int index)
{
	if (lua_getmetatable(L, index) == 0) return false;

	lua_pushstring(L, "__luabind_classrep");
	lua_gettable(L, -2);
	if (lua_toboolean(L, -1))
	{
		lua_pop(L, 2);
		return true;
	}

	lua_pop(L, 2);
	return false;
}

void luabind::detail::finalize(lua_State* L, class_rep* crep)
{
	if (crep->get_class_type() != class_rep::lua_class) return;

//	lua_pushvalue(L, -1); // copy the object ref
	crep->get_table(L);
    lua_pushliteral(L, "__finalize");
	lua_gettable(L, -2);
	lua_remove(L, -2);

	if (lua_isnil(L, -1))
	{
		lua_pop(L, 1);
	}
	else
	{
		lua_pushvalue(L, -2);
		lua_call(L, 1, 0);
	}

	for (std::vector<class_rep::base_info>::const_iterator
			i = crep->bases().begin(); i != crep->bases().end(); ++i)
	{
		if (i->base) finalize(L, i->base);
	}
}

void luabind::detail::class_rep::cache_operators(lua_State* L)
{
	m_operator_cache = 0x1;

	for (int i = 0; i < number_of_operators; ++i)
	{
		get_table(L);
		lua_pushstring(L, get_operator_name(i));
		lua_rawget(L, -2);

		if (lua_isfunction(L, -1)) m_operator_cache |= 1 << (i + 1);

		lua_pop(L, 2);
	}
}

bool luabind::detail::class_rep::has_operator_in_lua(lua_State* L, int id)
{
	if ((m_operator_cache & 0x1) == 0)
		cache_operators(L);

	const int mask = 1 << (id + 1);

	return (m_operator_cache & mask) != 0;
}

namespace luabind { namespace detail
{
	namespace
	{
		// expects two tables on the lua stack:
		// 1: destination
		// 2: source
		void copy_member_table(lua_State* L)
		{
			lua_pushnil(L);

			while (lua_next(L, -2))
			{
				lua_pushstring(L, "__init");
				if (lua_equal(L, -1, -3))
				{
					lua_pop(L, 2);
					continue;
				}
				else lua_pop(L, 1); // __init string

				lua_pushstring(L, "__finalize");
				if (lua_equal(L, -1, -3))
				{
					lua_pop(L, 2);
					continue;
				}
				else lua_pop(L, 1); // __finalize string

				lua_pushvalue(L, -2); // copy key
				lua_insert(L, -2);
				lua_settable(L, -5);
			}
		}
	}


	int create_class::stage2(lua_State* L)
	{
		class_rep* crep = static_cast<class_rep*>(lua_touserdata(L, lua_upvalueindex(1)));
		assert((crep != 0) && "internal error, please report");
		assert((is_class_rep(L, lua_upvalueindex(1))) && "internal error, please report");

	#ifndef LUABIND_NO_ERROR_CHECKING

		if (!is_class_rep(L, 1))
		{
			lua_pushstring(L, "expected class to derive from or a newline");
			lua_error(L);
		}

	#endif

		class_rep* base = static_cast<class_rep*>(lua_touserdata(L, 1));
		class_rep::base_info binfo;

		binfo.pointer_offset = 0;
		binfo.base = base;
		crep->add_base_class(binfo);

		// copy base class members

		crep->get_table(L);
		base->get_table(L);
		copy_member_table(L);

		crep->get_default_table(L);
		base->get_default_table(L);
		copy_member_table(L);

		crep->set_type(base->type());

		return 0;
	}

	int create_class::stage1(lua_State* L)
	{

	#ifndef LUABIND_NO_ERROR_CHECKING

		if (lua_gettop(L) != 1 || lua_type(L, 1) != LUA_TSTRING || lua_isnumber(L, 1))
		{
			lua_pushstring(L, "invalid construct, expected class name");
			lua_error(L);
		}

		if (std::strlen(lua_tostring(L, 1)) != lua_rawlen(L, 1))
		{
			lua_pushstring(L, "luabind does not support class names with extra nulls");
			lua_error(L);
		}

	#endif

		const char* name = lua_tostring(L, 1);

		void* c = lua_newuserdata(L, sizeof(class_rep));
		new(c) class_rep(L, name);

		// make the class globally available
		lua_pushvalue(L, -1);
		lua_setglobal(L, name);

		// also add it to the closure as return value
		lua_pushcclosure(L, &stage2, 1);

		return 1;
	}

}}

namespace luabind
{

	namespace
	{
		pcall_callback_fun pcall_callback = 0;
#ifdef LUABIND_NO_EXCEPTIONS
		error_callback_fun error_callback = 0;
		cast_failed_callback_fun cast_failed_callback = 0;
#endif
	}


#ifdef LUABIND_NO_EXCEPTIONS

	typedef void(*error_callback_fun)(lua_State*);
	typedef void(*cast_failed_callback_fun)(lua_State*, type_id const&);

	void set_error_callback(error_callback_fun e)
	{
		error_callback = e;
	}

	void set_cast_failed_callback(cast_failed_callback_fun c)
	{
		cast_failed_callback = c;
	}

	error_callback_fun get_error_callback()
	{
		return error_callback;
	}

	cast_failed_callback_fun get_cast_failed_callback()
	{
		return cast_failed_callback;
	}

#endif

	void set_pcall_callback(pcall_callback_fun e)
	{
		pcall_callback = e;
	}

	pcall_callback_fun get_pcall_callback()
	{
		return pcall_callback;
	}

}

#ifndef LUABIND_NO_EXCEPTIONS

namespace luabind { namespace detail {

namespace
{
  exception_handler_base* handler_chain = 0;

  void push_exception_string(lua_State* L, char const* exception, char const* what)
  {
      lua_pushstring(L, exception);
      lua_pushstring(L, ": '");
      lua_pushstring(L, what);
      lua_pushstring(L, "'");
      lua_concat(L, 4);
  }
}

void exception_handler_base::try_next(lua_State* L) const
{
    if (next)
        next->handle(L);
    else
        throw;
}

LUABIND_API void handle_exception_aux(lua_State* L)
{
    try
    {
        if (handler_chain)
            handler_chain->handle(L);
        else
            throw;
    }
    catch (error const&)
    {}
    catch (std::logic_error const& e)
    {
        push_exception_string(L, "std::logic_error", e.what());
    }
    catch (std::runtime_error const& e)
    {
        push_exception_string(L, "std::runtime_error", e.what());
    }
    catch (std::exception const& e)
    {
        push_exception_string(L, "std::exception", e.what());
    }
    catch (char const* str)
    {
        push_exception_string(L, "c-string", str);
    }
    catch (...)
    {
        lua_pushstring(L, "Unknown C++ exception");
    }
}

LUABIND_API void register_exception_handler(exception_handler_base* handler)
{
    if (!handler_chain) handler_chain = handler;
    else
    {
        exception_handler_base* p = handler_chain;

        for (; p->next; p = p->next);

        handler->next = 0;
        p->next = handler;
    }
}

}} // namespace luabind::detail

#endif // LUABIND_NO_EXCEPTIONS

namespace luabind { namespace detail {

namespace
{

  int function_destroy(lua_State* L)
  {
      function_object* fn = *(function_object**)lua_touserdata(L, 1);
      delete fn;
      return 0;
  }

  void push_function_metatable(lua_State* L)
  {
      lua_pushstring(L, "luabind.function");
      lua_rawget(L, LUA_REGISTRYINDEX);

      if (lua_istable(L, -1))
          return;

      lua_pop(L, 1);

      lua_newtable(L);

      lua_pushstring(L, "__gc");
      lua_pushcclosure(L, &function_destroy, 0);
      lua_rawset(L, -3);

      lua_pushstring(L, "luabind.function");
      lua_pushvalue(L, -2);
      lua_rawset(L, LUA_REGISTRYINDEX);
  }

  // A pointer to this is used as a tag value to identify functions exported
  // by luabind.
  int function_tag = 0;

} // namespace unnamed

LUABIND_API bool is_luabind_function(lua_State* L, int index)
{
    if (!lua_getupvalue(L, index, 2))
        return false;
    bool result = lua_touserdata(L, -1) == &function_tag;
    lua_pop(L, 1);
    return result;
}

namespace
{

  inline bool is_luabind_function(object const& obj)
  {
      obj.push(obj.interpreter());
      bool result = detail::is_luabind_function(obj.interpreter(), -1);
      lua_pop(obj.interpreter(), 1);
      return result;
  }

} // namespace unnamed

LUABIND_API void add_overload(
    object const& context, char const* name, object const& fn)
{
    function_object* f = *touserdata<function_object*>(getupvalue(fn, 1));
    f->name = name;

    if (object overloads = context[name])
    {
        if (is_luabind_function(overloads) && is_luabind_function(fn))
        {
            f->next = *touserdata<function_object*>(getupvalue(overloads, 1));
            f->keepalive = overloads;
        }
    }

    context[name] = fn;
}

LUABIND_API object make_function_aux(lua_State* L, function_object* impl)
{
    void* storage = lua_newuserdata(L, sizeof(function_object*));
    push_function_metatable(L);
    *(function_object**)storage = impl;
    lua_setmetatable(L, -2);

    lua_pushlightuserdata(L, &function_tag);
    lua_pushcclosure(L, impl->entry, 2);
    stack_pop pop(L, 1);

    return object(from_stack(L, -1));
}

void invoke_context::format_error(
    lua_State* L, function_object const* overloads) const
{
    char const* function_name =
        overloads->name.empty() ? "<unknown>" : overloads->name.c_str();

    if (candidate_index == 0)
    {
        lua_pushstring(L, "No matching overload found, candidates:\n");
        int count = 0;
        for (function_object const* f = overloads; f != 0; f = f->next)
        {
            if (count != 0)
                lua_pushstring(L, "\n");
            f->format_signature(L, function_name);
            ++count;
        }
        lua_concat(L, count * 2);
    }
    else
    {
        // Ambiguous
        lua_pushstring(L, "Ambiguous, candidates:\n");
        for (int i = 0; i < candidate_index; ++i)
        {
            if (i != 0)
                lua_pushstring(L, "\n");
            candidates[i]->format_signature(L, function_name);
        }
        lua_concat(L, candidate_index * 2);
    }
}

}} // namespace luabind::detail

namespace luabind { namespace detail {

class_id const class_id_map::local_id_base =
    std::numeric_limits<class_id>::max() / 2;

namespace
{

  struct edge
  {
      edge(class_id target, cast_function cast)
        : target(target)
        , cast(cast)
      {}

      class_id target;
      cast_function cast;
  };

  bool operator<(edge const& x, edge const& y)
  {
      return x.target < y.target;
  }

  struct vertex
  {
      vertex(class_id id)
        : id(id)
      {}

      class_id id;
      std::vector<edge> edges;
  };

  typedef std::pair<std::ptrdiff_t, int> cache_entry;

  class cache
  {
  public:
      static std::ptrdiff_t const unknown;
      static std::ptrdiff_t const invalid;

      cache_entry get(
          class_id src, class_id target, class_id dynamic_id
        , std::ptrdiff_t object_offset) const;

      void put(
          class_id src, class_id target, class_id dynamic_id
        , std::ptrdiff_t object_offset
        , std::size_t distance, std::ptrdiff_t offset);

      void invalidate();

  private:
      typedef boost::tuple<
          class_id, class_id, class_id, std::ptrdiff_t> key_type;
      typedef std::map<key_type, cache_entry> map_type;
      map_type m_cache;
  };

  std::ptrdiff_t const cache::unknown =
      std::numeric_limits<std::ptrdiff_t>::max();
  std::ptrdiff_t const cache::invalid = cache::unknown - 1;

  cache_entry cache::get(
      class_id src, class_id target, class_id dynamic_id
    , std::ptrdiff_t object_offset) const
  {
      map_type::const_iterator i = m_cache.find(
          key_type(src, target, dynamic_id, object_offset));
      return i != m_cache.end() ? i->second : cache_entry(unknown, -1);
  }

  void cache::put(
      class_id src, class_id target, class_id dynamic_id
    , std::ptrdiff_t object_offset, std::size_t distance, std::ptrdiff_t offset)
  {
      m_cache.insert(std::make_pair(
          key_type(src, target, dynamic_id, object_offset)
        , cache_entry(offset, distance)
      ));
  }

  void cache::invalidate()
  {
      m_cache.clear();
  }

} // namespace unnamed

class cast_graph::impl
{
public:
    std::pair<void*, int> cast(
        void* p, class_id src, class_id target
      , class_id dynamic_id, void const* dynamic_ptr) const;
    void insert(class_id src, class_id target, cast_function cast);

private:
    std::vector<vertex> m_vertices;
    mutable cache m_cache;
};

namespace
{

  struct queue_entry
  {
      queue_entry(void* p, class_id vertex_id, int distance)
        : p(p)
        , vertex_id(vertex_id)
        , distance(distance)
      {}

      void* p;
      class_id vertex_id;
      int distance;
  };

} // namespace unnamed

std::pair<void*, int> cast_graph::impl::cast(
    void* const p, class_id src, class_id target
  , class_id dynamic_id, void const* dynamic_ptr) const
{
    if (src == target)
        return std::make_pair(p, 0);

    if (src >= m_vertices.size() || target >= m_vertices.size())
        return std::pair<void*, int>((void*)0, -1);

    std::ptrdiff_t const object_offset =
        (char const*)dynamic_ptr - (char const*)p;

    cache_entry cached = m_cache.get(src, target, dynamic_id, object_offset);

    if (cached.first != cache::unknown)
    {
        if (cached.first == cache::invalid)
            return std::pair<void*, int>((void*)0, -1);
        return std::make_pair((char*)p + cached.first, cached.second);
    }

    std::queue<queue_entry> q;
    q.push(queue_entry(p, src, 0));

    boost::dynamic_bitset<> visited(m_vertices.size());

    while (!q.empty())
    {
        queue_entry const qe = q.front();
        q.pop();

        visited[qe.vertex_id] = true;
        vertex const& v = m_vertices[qe.vertex_id];

        if (v.id == target)
        {
            m_cache.put(
                src, target, dynamic_id, object_offset
              , qe.distance, (char*)qe.p - (char*)p
            );

            return std::make_pair(qe.p, qe.distance);
        }

        BOOST_FOREACH(edge const& e, v.edges)
        {
            if (visited[e.target])
                continue;
            if (void* casted = e.cast(qe.p))
                q.push(queue_entry(casted, e.target, qe.distance + 1));
        }
    }

    m_cache.put(src, target, dynamic_id, object_offset, cache::invalid, -1);

    return std::pair<void*, int>((void*)0, -1);
}

void cast_graph::impl::insert(
    class_id src, class_id target, cast_function cast)
{
    class_id const max_id = std::max(src, target);

    if (max_id >= m_vertices.size())
    {
        m_vertices.reserve(max_id + 1);
        for (class_id i = m_vertices.size(); i < max_id + 1; ++i)
            m_vertices.push_back(vertex(i));
    }

    std::vector<edge>& edges = m_vertices[src].edges;

    std::vector<edge>::iterator i = std::lower_bound(
        edges.begin(), edges.end(), edge(target, 0)
    );

    if (i == edges.end() || i->target != target)
    {
        edges.insert(i, edge(target, cast));
        m_cache.invalidate();
    }
}

std::pair<void*, int> cast_graph::cast(
    void* p, class_id src, class_id target
  , class_id dynamic_id, void const* dynamic_ptr) const
{
    return m_impl->cast(p, src, target, dynamic_id, dynamic_ptr);
}

void cast_graph::insert(class_id src, class_id target, cast_function cast)
{
    m_impl->insert(src, target, cast);
}

cast_graph::cast_graph()
  : m_impl(new impl)
{}

cast_graph::~cast_graph()
{}

LUABIND_API class_id allocate_class_id(type_id const& cls)
{
    typedef std::map<type_id, class_id> map_type;

    static map_type registered;
    static class_id id = 0;

    std::pair<map_type::iterator, bool> inserted = registered.insert(
        std::make_pair(cls, id));

    if (inserted.second)
        ++id;

    return inserted.first->second;
}

}} // namespace luabind::detail

namespace luabind { namespace detail
{

#ifdef LUABIND_NOT_THREADSAFE
	void not_threadsafe_defined_conflict() {}
#else
	void not_threadsafe_not_defined_conflict() {}
#endif

#ifdef LUABIND_NO_ERROR_CHECKING
	void no_error_checking_defined_conflict() {}
#else
	void no_error_checking_not_defined_conflict() {}
#endif

}}

namespace luabind { namespace detail
{

	// dest is a function that is called to delete the c++ object this struct holds
	object_rep::object_rep(instance_holder* instance, class_rep* crep)
		: m_instance(instance)
		, m_classrep(crep)
		, m_dependency_cnt(0)
	{}

	object_rep::~object_rep()
	{
        if (!m_instance)
            return;
        m_instance->~instance_holder();
        deallocate(m_instance);
	}

	void object_rep::add_dependency(lua_State* L, int index)
	{
        assert(m_dependency_cnt < sizeof(object_rep));

        void* key = (char*)this + m_dependency_cnt;

        lua_pushlightuserdata(L, key);
        lua_pushvalue(L, index);
        lua_rawset(L, LUA_REGISTRYINDEX);

        ++m_dependency_cnt;
	}

    void object_rep::release_dependency_refs(lua_State* L)
    {
        for (std::size_t i = 0; i < m_dependency_cnt; ++i)
        {
            void* key = (char*)this + i;
            lua_pushlightuserdata(L, key);
            lua_pushnil(L);
            lua_rawset(L, LUA_REGISTRYINDEX);
        }
    }

    int destroy_instance(lua_State* L)
    {
        object_rep* instance = static_cast<object_rep*>(lua_touserdata(L, 1));

        lua_pushstring(L, "__finalize");
        lua_gettable(L, 1);

        if (lua_isnil(L, -1))
        {
            lua_pop(L, 1);
        }
        else
        {
            lua_pushvalue(L, 1);
            lua_call(L, 1, 0);
        }

        instance->release_dependency_refs(L);
        instance->~object_rep();
        return 0;
    }

    namespace
    {

      int set_instance_value(lua_State* L)
      {
          lua_getuservalue(L, 1);
          lua_pushvalue(L, 2);
          lua_rawget(L, -2);

          if (lua_isnil(L, -1) && lua_getmetatable(L, -2))
          {
              lua_pushvalue(L, 2);
              lua_rawget(L, -2);
              lua_replace(L, -3);
              lua_pop(L, 1);
          }

          if (lua_tocfunction(L, -1) == &property_tag)
          {
              // this member is a property, extract the "set" function and call it.
              lua_getupvalue(L, -1, 2);

              if (lua_isnil(L, -1))
              {
                  lua_pushfstring(L, "property '%s' is read only", lua_tostring(L, 2));
                  lua_error(L);
              }

              lua_pushvalue(L, 1);
              lua_pushvalue(L, 3);
              lua_call(L, 2, 0);
              return 0;
          }

          lua_pop(L, 1);

          if (!lua_getmetatable(L, 4))
          {
              lua_newtable(L);
              lua_pushvalue(L, -1);
              lua_setuservalue(L, 1);
              lua_pushvalue(L, 4);
              lua_setmetatable(L, -2);
          }
          else
          {
              lua_pop(L, 1);
          }

          lua_pushvalue(L, 2);
          lua_pushvalue(L, 3);
          lua_rawset(L, -3);

          return 0;
      }

      int get_instance_value(lua_State* L)
      {
		  lua_getuservalue(L, 1);
          lua_pushvalue(L, 2);
          lua_rawget(L, -2);

          if (lua_isnil(L, -1) && lua_getmetatable(L, -2))
          {
              lua_pushvalue(L, 2);
              lua_rawget(L, -2);
          }

          if (lua_tocfunction(L, -1) == &property_tag)
          {
              // this member is a property, extract the "get" function and call it.
              lua_getupvalue(L, -1, 1);
              lua_pushvalue(L, 1);
              lua_call(L, 1, 1);
          }

          return 1;
      }

      int dispatch_operator(lua_State* L)
      {
          for (int i = 0; i < 2; ++i)
          {
              if (get_instance(L, 1 + i))
              {
                  int nargs = lua_gettop(L);

                  lua_pushvalue(L, lua_upvalueindex(1));
                  lua_gettable(L, 1 + i);

                  if (lua_isnil(L, -1))
                  {
                      lua_pop(L, 1);
                      continue;
                  }

                  lua_insert(L, 1); // move the function to the bottom

                  nargs = lua_toboolean(L, lua_upvalueindex(2)) ? 1 : nargs;

                  if (lua_toboolean(L, lua_upvalueindex(2))) // remove trailing nil
                  lua_remove(L, 3);

                  lua_call(L, nargs, 1);
                  return 1;
              }
          }

          lua_pop(L, lua_gettop(L));
          lua_pushstring(L, "No such operator defined");
          lua_error(L);

          return 0;
      }

    } // namespace unnamed

    LUABIND_API void push_instance_metatable(lua_State* L)
    {
        lua_newtable(L);

        // This is used as a tag to determine if a userdata is a luabind
        // instance. We use a numeric key and a cclosure for fast comparision.
        lua_pushnumber(L, 1);
        lua_pushcclosure(L, get_instance_value, 0);
        lua_rawset(L, -3);

        lua_pushcclosure(L, destroy_instance, 0);
        lua_setfield(L, -2, "__gc");

        lua_pushcclosure(L, get_instance_value, 0);
        lua_setfield(L, -2, "__index");

        lua_pushcclosure(L, set_instance_value, 0);
        lua_setfield(L, -2, "__newindex");

        for (int op = 0; op < number_of_operators; ++op)
        {
            lua_pushstring(L, get_operator_name(op));
            lua_pushvalue(L, -1);
            lua_pushboolean(L, op == op_unm || op == op_len);
            lua_pushcclosure(L, &dispatch_operator, 2);
            lua_settable(L, -3);
        }
    }

    LUABIND_API object_rep* get_instance(lua_State* L, int index)
    {
        object_rep* result = static_cast<object_rep*>(lua_touserdata(L, index));

        if (!result || !lua_getmetatable(L, index))
            return 0;

        lua_rawgeti(L, -1, 1);

        if (lua_tocfunction(L, -1) != &get_instance_value)
            result = 0;

        lua_pop(L, 2);

        return result;
    }

    LUABIND_API object_rep* push_new_instance(lua_State* L, class_rep* cls)
    {
        void* storage = lua_newuserdata(L, sizeof(object_rep));
        object_rep* result = new (storage) object_rep(0, cls);
        cls->get_table(L);
        lua_setuservalue(L, -2);
        lua_rawgeti(L, LUA_REGISTRYINDEX, cls->metatable_ref());
        lua_setmetatable(L, -2);
        return result;
    }

}}

namespace luabind {

namespace
{

  int make_property(lua_State* L)
  {
      int args = lua_gettop(L);

      if (args == 0 || args > 2)
      {
          lua_pushstring(L, "make_property() called with wrong number of arguments.");
          lua_error(L);
      }

      if (args == 1)
          lua_pushnil(L);

      lua_pushcclosure(L, &detail::property_tag, 2);
      return 1;
  }

  int main_thread_tag;

  int deprecated_super(lua_State* L)
  {
      lua_pushstring(L,
          "DEPRECATION: 'super' has been deprecated in favor of "
          "directly calling the base class __init() function. "
          "This error can be disabled by calling 'luabind::disable_super_deprecation()'."
      );
      lua_error(L);

      return 0;
  }

  int destroy_class_id_map(lua_State* L)
  {
      detail::class_id_map* m =
          (detail::class_id_map*)lua_touserdata(L, 1);
      m->~class_id_map();
      return 0;
  }

  int destroy_cast_graph(lua_State* L)
  {
      detail::cast_graph* g =
          (detail::cast_graph*)lua_touserdata(L, 1);
      g->~cast_graph();
      return 0;
  }

  int destroy_class_map(lua_State* L)
  {
      detail::class_map* m =
          (detail::class_map*)lua_touserdata(L, 1);
      m->~class_map();
      return 0;
  }

} // namespace unnamed

    LUABIND_API lua_State* get_main_thread(lua_State* L)
    {
        lua_pushlightuserdata(L, &main_thread_tag);
        lua_rawget(L, LUA_REGISTRYINDEX);
        lua_State* result = static_cast<lua_State*>(lua_touserdata(L, -1));
        lua_pop(L, 1);

        if (!result)
            throw std::runtime_error("Unable to get main thread, luabind::open() not called?");

        return result;
    }

    LUABIND_API void open(lua_State* L)
    {
        bool is_main_thread = lua_pushthread(L) == 1;
        lua_pop(L, 1);

        if (!is_main_thread)
        {
            throw std::runtime_error(
                "luabind::open() must be called with the main thread "
                "lua_State*"
            );
        }

        if (detail::class_registry::get_registry(L))
            return;

        lua_pushstring(L, "__luabind_classes");
        detail::class_registry* r = static_cast<detail::class_registry*>(
            lua_newuserdata(L, sizeof(detail::class_registry)));

        // set gc metatable
        lua_newtable(L);
        lua_pushstring(L, "__gc");
        lua_pushcclosure(
            L
          , detail::garbage_collector_s<
                detail::class_registry
            >::apply
          , 0);

        lua_settable(L, -3);
        lua_setmetatable(L, -2);

        new(r) detail::class_registry(L);
        lua_settable(L, LUA_REGISTRYINDEX);

        lua_pushstring(L, "__luabind_class_id_map");
        void* classes_storage = lua_newuserdata(L, sizeof(detail::class_id_map));
        detail::class_id_map* class_ids = new (classes_storage) detail::class_id_map;
        (void)class_ids;

        lua_newtable(L);
        lua_pushcclosure(L, &destroy_class_id_map, 0);
        lua_setfield(L, -2, "__gc");
        lua_setmetatable(L, -2);

        lua_settable(L, LUA_REGISTRYINDEX);

        lua_pushstring(L, "__luabind_cast_graph");
        void* cast_graph_storage = lua_newuserdata(
            L, sizeof(detail::cast_graph));
        detail::cast_graph* graph = new (cast_graph_storage) detail::cast_graph;
        (void)graph;

        lua_newtable(L);
        lua_pushcclosure(L, &destroy_cast_graph, 0);
        lua_setfield(L, -2, "__gc");
        lua_setmetatable(L, -2);

        lua_settable(L, LUA_REGISTRYINDEX);

        lua_pushstring(L, "__luabind_class_map");
        void* class_map_storage = lua_newuserdata(
            L, sizeof(detail::class_map));
        detail::class_map* classes = new (class_map_storage) detail::class_map;
        (void)classes;

        lua_newtable(L);
        lua_pushcclosure(L, &destroy_class_map, 0);
        lua_setfield(L, -2, "__gc");
        lua_setmetatable(L, -2);

        lua_settable(L, LUA_REGISTRYINDEX);

        // add functions (class, cast etc...)

        lua_pushcclosure(L, detail::create_class::stage1, 0);
		lua_setglobal(L, "class");


        lua_pushcclosure(L, &make_property, 0);
		lua_setglobal(L, "property");

        lua_pushlightuserdata(L, &main_thread_tag);
        lua_pushlightuserdata(L, L);
        lua_rawset(L, LUA_REGISTRYINDEX);


        lua_pushcclosure(L, &deprecated_super, 0);
		lua_setglobal(L, "super");
    }

} // namespace luabind

namespace luabind { namespace detail {

    registration::registration()
        : m_next(0)
    {
    }

    registration::~registration()
    {
        delete m_next;
    }

    } // namespace detail

    scope::scope()
        : m_chain(0)
    {
    }

    scope::scope(std::auto_ptr<detail::registration> reg)
        : m_chain(reg.release())
    {
    }

    scope::scope(scope const& other)
        : m_chain(other.m_chain)
    {
        const_cast<scope&>(other).m_chain = 0;
    }

    scope& scope::operator=(scope const& other_)
    {
        delete m_chain;
        m_chain = other_.m_chain;
        const_cast<scope&>(other_).m_chain = 0;
        return *this;
    }

    scope::~scope()
    {
        delete m_chain;
    }

    scope& scope::operator,(scope s)
    {
        if (!m_chain)
        {
            m_chain = s.m_chain;
            s.m_chain = 0;
            return *this;
        }

        for (detail::registration* c = m_chain;; c = c->m_next)
        {
            if (!c->m_next)
            {
                c->m_next = s.m_chain;
                s.m_chain = 0;
                break;
            }
        }

        return *this;
    }

    void scope::register_(lua_State* L) const
    {
        for (detail::registration* r = m_chain; r != 0; r = r->m_next)
        {
			LUABIND_CHECK_STACK(L);
            r->register_(L);
        }
    }

} // namespace luabind

namespace luabind {

    namespace {

        struct lua_pop_stack
        {
            lua_pop_stack(lua_State* L)
                : m_state(L)
            {
            }

            ~lua_pop_stack()
            {
                lua_pop(m_state, 1);
            }

            lua_State* m_state;
        };

    } // namespace unnamed

    module_::module_(lua_State* L, char const* name = 0)
        : m_state(L)
        , m_name(name)
    {
    }

    void module_::operator[](scope s)
    {
        if (m_name)
        {
            lua_getglobal(m_state, m_name);

            if (!lua_istable(m_state, -1))
            {
                lua_pop(m_state, 1);

                lua_newtable(m_state);
				lua_pushvalue(m_state, -1);
				lua_setglobal(m_state, m_name);
            }
        }
        else
        {
#if LUA_VERSION_NUM >= 502
	lua_rawgeti(m_state, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
#else
	lua_pushvalue(m_state, LUA_GLOBALSINDEX);
#endif
        }

        lua_pop_stack guard(m_state);

        s.register_(m_state);
    }

    struct namespace_::registration_ : detail::registration
    {
        registration_(char const* name)
            : m_name(name)
        {
        }

        void register_(lua_State* L) const
        {
			LUABIND_CHECK_STACK(L);
            assert(lua_gettop(L) >= 1);

            lua_pushstring(L, m_name);
            lua_gettable(L, -2);

			detail::stack_pop p(L, 1); // pops the table on exit

            if (!lua_istable(L, -1))
            {
                lua_pop(L, 1);

                lua_newtable(L);
                lua_pushstring(L, m_name);
                lua_pushvalue(L, -2);
                lua_settable(L, -4);
            }

            m_scope.register_(L);
        }

        char const* m_name;
        scope m_scope;
    };

    namespace_::namespace_(char const* name)
        : scope(std::auto_ptr<detail::registration>(
              m_registration = new registration_(name)))
    {
    }

    namespace_& namespace_::operator[](scope s)
    {
        m_registration->m_scope.operator,(s);
        return *this;
    }

} // namespace luabind

using namespace luabind::detail;

std::string luabind::detail::stack_content_by_name(lua_State* L, int start_index)
{
	std::string ret;
	int top = lua_gettop(L);
	for (int i = start_index; i <= top; ++i)
	{
		object_rep* obj = get_instance(L, i);
		class_rep* crep = is_class_rep(L, i)?(class_rep*)lua_touserdata(L, i):0;
		if (obj == 0 && crep == 0)
		{
			int type = lua_type(L, i);
			ret += lua_typename(L, type);
		}
		else if (obj)
		{
			if (obj->is_const()) ret += "const ";
			ret += obj->crep()->name();
		}
		else if (crep)
		{
			ret += "<";
			ret += crep->name();
			ret += ">";
		}
		if (i < top) ret += ", ";
	}
	return ret;
}

namespace luabind {

namespace
{

  int weak_table_tag;

} // namespace unnamed

LUABIND_API void get_weak_table(lua_State* L)
{
    lua_pushlightuserdata(L, &weak_table_tag);
    lua_rawget(L, LUA_REGISTRYINDEX);

    if (lua_isnil(L, -1))
    {
        lua_pop(L, 1);
        lua_newtable(L);
        // metatable
        lua_newtable(L);
        lua_pushliteral(L, "__mode");
        lua_pushliteral(L, "v");
        lua_rawset(L, -3);
        // set metatable
        lua_setmetatable(L, -2);

        lua_pushlightuserdata(L, &weak_table_tag);
        lua_pushvalue(L, -2);
        lua_rawset(L, LUA_REGISTRYINDEX);
    }
}

} // namespace luabind

namespace luabind
{

    struct weak_ref::impl
    {
        impl(lua_State* main, lua_State* s, int index)
            : count(0)
            , state(main)
            , ref(0)
        {
            get_weak_table(s);
            lua_pushvalue(s, index);
            ref = luaL_ref(s, -2);
            lua_pop(s, 1);
        }

        ~impl()
        {
            get_weak_table(state);
            luaL_unref(state, -1, ref);
            lua_pop(state, 1);
        }

        int count;
        lua_State* state;
        int ref;
    };

    weak_ref::weak_ref()
        : m_impl(0)
    {
    }

    weak_ref::weak_ref(lua_State* main, lua_State* L, int index)
        : m_impl(new impl(main, L, index))
    {
        m_impl->count = 1;
    }

    weak_ref::weak_ref(weak_ref const& other)
        : m_impl(other.m_impl)
    {
        if (m_impl) ++m_impl->count;
    }

    weak_ref::~weak_ref()
    {
        if (m_impl && --m_impl->count == 0)
        {
            delete m_impl;
        }
    }

    weak_ref& weak_ref::operator=(weak_ref const& other)
    {
        weak_ref(other).swap(*this);
        return *this;
    }

    void weak_ref::swap(weak_ref& other)
    {
        std::swap(m_impl, other.m_impl);
    }

    int weak_ref::id() const
    {
        assert(m_impl);
		return m_impl->ref;
    }

	// L may not be the same pointer as
	// was used when creating this reference
	// since it may be a thread that shares
	// the same globals table.
    void weak_ref::get(lua_State* L) const
    {
        assert(m_impl);
		assert(L);
        get_weak_table(L);
        lua_rawgeti(L, -1, m_impl->ref);
        lua_remove(L, -2);
    }

    lua_State* weak_ref::state() const
    {
        assert(m_impl);
        return m_impl->state;
    }

} // namespace luabind

namespace luabind { namespace detail
{
	LUABIND_API void do_call_member_selection(lua_State* L, char const* name)
	{
		object_rep* obj = static_cast<object_rep*>(lua_touserdata(L, -1));

        lua_pushstring(L, name);
        lua_gettable(L, -2);
        lua_replace(L, -2);

		if (!is_luabind_function(L, -1))
			return;

		// this (usually) means the function has not been
		// overridden by lua, call the default implementation
		lua_pop(L, 1);
		obj->crep()->get_default_table(L); // push the crep table
		lua_pushstring(L, name);
		lua_gettable(L, -2);
		lua_remove(L, -2); // remove the crep table
	}
}}

namespace luabind { namespace detail
{
	int pcall(lua_State *L, int nargs, int nresults)
	{
		pcall_callback_fun e = get_pcall_callback();
		int en = 0;
		if ( e )
		{
			int base = lua_gettop(L) - nargs;
			lua_pushcfunction(L, e);
			lua_insert(L, base);  // push pcall_callback under chunk and args
			en = base;
  		}
		int result = lua_pcall(L, nargs, nresults, en);
		if ( en )
			lua_remove(L, en);  // remove pcall_callback
		return result;
	}

	int resume_impl(lua_State *L, int nargs, int)
	{
#if LUA_VERSION_NUM >= 501
		// Lua 5.1 added  LUA_YIELD as a possible return value,
		// this was causing crashes, because the caller expects 0 on success.
		int res = lua_resume(L, NULL, nargs);
		return (res == LUA_YIELD) ? 0 : res;
#else
		return lua_resume(L, nargs);
#endif
	}

}}
