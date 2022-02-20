// Copyright Daniel Wallin 2008. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef LUABIND_INSTANCE_HOLDER_081024_HPP
# define LUABIND_INSTANCE_HOLDER_081024_HPP

# include <luabind/detail/inheritance.hpp>
# include <luabind/get_pointer.hpp>
# include <luabind/typeid.hpp>

# include <boost/type_traits/is_polymorphic.hpp>

# include <stdexcept>

namespace luabind { namespace detail {

class instance_holder
{
public:
    instance_holder(bool is_pointee_const)
      : m_pointee_const(is_pointee_const)
    {}

    virtual ~instance_holder()
    {}

    virtual std::pair<void*, int> get(
        cast_graph const& casts, class_id target) const = 0;

    virtual void release() = 0;

    bool pointee_const() const
    {
        return m_pointee_const;
    }

private:
    bool m_pointee_const;
};

namespace mpl = boost::mpl;

inline mpl::false_ check_const_pointer(void*)
{
    return mpl::false_();
}

inline mpl::true_ check_const_pointer(void const*)
{
    return mpl::true_();
}

template <class T>
#ifdef LUABIND_USE_CXX11
void release_ownership(std::unique_ptr<T>& p)
#else
void release_ownership(std::auto_ptr<T>& p)
#endif
{
    p.release();
}

template <class P>
void release_ownership(P const&)
{
    throw std::runtime_error(
        "luabind: smart pointer does not allow ownership transfer");
}

template <class T>
class_id static_class_id(T*)
{
    return registered_class<T>::id;
}

template <class P, class Pointee = void const>
class pointer_holder : public instance_holder
{
public:
    pointer_holder(
        P p, class_id dynamic_id, void* dynamic_ptr
    )
      : instance_holder(check_const_pointer(false ? get_pointer(p) : 0))
#ifdef LUABIND_USE_CXX11
      , m_p(std::move(p))
#else
      , m_p(p)
#endif
      , m_weak(0)
      , m_dynamic_id(dynamic_id)
      , m_dynamic_ptr(dynamic_ptr)
    {}

    std::pair<void*, int> get(cast_graph const& casts, class_id target) const
    {
        if (target == registered_class<P>::id)
            return std::pair<void*, int>(&this->m_p, 0);

        void* naked_ptr = const_cast<void*>(static_cast<void const*>(
            m_weak ? m_weak : get_pointer(m_p)));

        if (!naked_ptr)
            return std::pair<void*, int>(static_cast<void*>(0), 0);

        return casts.cast(
            naked_ptr
          , static_class_id(false ? get_pointer(m_p) : 0)
          , target
          , m_dynamic_id
          , m_dynamic_ptr
        );
    }

    void release()
    {
        m_weak = const_cast<void*>(static_cast<void const*>(
            get_pointer(m_p)));
        release_ownership(m_p);
    }

private:
    mutable P m_p;
    // weak will hold a possibly stale pointer to the object owned
    // by p once p has released it's owership. This is a workaround
    // to make adopt() work with virtual function wrapper classes.
    void* m_weak;
    class_id m_dynamic_id;
    void* m_dynamic_ptr;
};

}} // namespace luabind::detail

#endif // LUABIND_INSTANCE_HOLDER_081024_HPP
