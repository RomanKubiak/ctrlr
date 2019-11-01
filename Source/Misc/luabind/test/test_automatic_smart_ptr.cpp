// Copyright Daniel Wallin 2009. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include <luabind/luabind.hpp>
#include <boost/shared_ptr.hpp>

namespace {

struct X
{
    X(int value_)
      : value(value_)
    {
        ++alive;
    }

    ~X()
    {
        --alive;
    }

    int value;

    static int alive;
};

int X::alive = 0;


struct D: X
{
    D(int value_): X(value_) {}
};

struct ptr
{
    ptr(X* p_)
      : p(p_)
    {}

    ptr(ptr const& other)
      : p(other.p)
    {
        const_cast<ptr&>(other).p = 0;
    }

    ~ptr()
    {
        delete p;
    }

    X* p;
};

X* get_pointer(ptr const& p)
{
    return p.p;
}

std::auto_ptr<X> make1()
{
    return std::auto_ptr<X>(new X(1));
}

boost::shared_ptr<X> make2()
{
    return boost::shared_ptr<X>(new X(2));
}

ptr make3()
{
    return ptr(new X(3));
}

boost::shared_ptr<D> make_d()
{
    return boost::shared_ptr<D>(new D(10));
}

void needs_x(boost::shared_ptr<X>) {}

} // namespace unnamed

void test_main(lua_State* L)
{
    using namespace luabind;

    module(L) [
        class_<X>("X")
          .def_readonly("value", &X::value),

        class_<D, X>("D"),

        def("make1", make1),
        def("make2", make2),
        def("make3", make3),

        def("make_d", make_d),
        def("needs_x", needs_x)
    ];

    DOSTRING(L,
        "x1 = make1()\n"
        "x2 = make2()\n"
        "x3 = make3()\n"
    );

    TEST_CHECK(X::alive == 3);

    DOSTRING(L,
        "assert(x1.value == 1)\n"
        "assert(x2.value == 2)\n"
        "assert(x3.value == 3)\n"
    );

    DOSTRING(L, "function get2() return x2 end");
    boost::shared_ptr<X> spx = call_function<boost::shared_ptr<X> >(L, "get2");
    TEST_CHECK(spx.use_count() == 2);

    DOSTRING(L,
        "x1 = nil\n"
        "x2 = nil\n"
        "x3 = nil\n"
        "collectgarbage()\n"
    );

    TEST_CHECK(spx.use_count() == 1);
    TEST_CHECK(X::alive == 1);
    spx.reset();
    TEST_CHECK(X::alive == 0);

    DOSTRING(L,
        "d = make_d()\n"
        "status, err = pcall(needs_x, d)\n"
        "assert(not status)\n"
        "pat = '^No matching overload found, candidates:\\n'\n"
        "pat = pat .. 'void needs_x%(custom %[.+%]%)$'\n"
        "if not err:match(pat) then\n"
        "  error('expected \"' .. pat .. '\", got \"' .. err .. '\"')\n"
        "end\n"
    );
}
