// Copyright Daniel Wallin 2009. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include <luabind/luabind.hpp>


namespace {

// Test the following hierarchy:
//
//         X
//        / \.
//       Y   Z
//        \ /
//         U

struct X
{
    X(int x_)
      : value(x_)
    {}

    virtual ~X()
    {}

    int f() const
    {
        return value;
    }

    int value;
};

struct Y : virtual X
{
    Y(int value_)
      : X(value_)
      , dummy(2)
    {}

    int g() const
    {
        return dummy;
    }

    int dummy;
};

struct Z : virtual X
{
    Z(int value_)
      : X(value_)
      , dummy(3)
    {}

    int h() const
    {
        return dummy;
    }

    int dummy;
};

struct U : Y, Z
{
    U(int value_)
      : X(value_)
      , Y(value_)
      , Z(value_)
    {}

    int dummy;
};

X* upcast(U* p)
{
    return p;
}

// This hiearchy tries to prove that conversion and caching works for all sub
// object pointers:
//
//
//      Base  Base
//       |     |
//      Left  Right
//        \   /
//         \ /
//       Derived
//

struct Base
{
    Base(int value_)
      : value(value_)
    {}

    virtual ~Base()
    {}

    int value;
};

struct Left : Base
{
    Left()
      : Base(1)
    {}

    int left() const
    {
        return value;
    }

    int dummy;
};

struct Right : Base
{
    Right()
      : Base(2)
    {}

    int right() const
    {
        return value;
    }

    int dummy;
};

struct Derived : Left, Right
{
    int f() const
    {
        return 3;
    }

    int dummy;
};

Base* left(Left* p)
{
    return p;
}

Base* right(Right* p)
{
    return p;
}

} // namespace unnamed

void test_main(lua_State* L)
{
    using namespace luabind;

    module(L) [
        class_<X>("X")
            .def("f", &X::f),
        class_<Y, X>("Y")
            .def("g", &Y::g),
        class_<Z, X>("Z")
            .def("h", &Z::h),
        class_<U, bases<Y, Z> >("U")
            .def(constructor<int>()),
        def("upcast", &upcast)
    ];

    // Do everything twice to verify that caching works.

    DOSTRING(L,
        "x = U(1)\n"
        "assert(x:f() == 1)\n"
        "assert(x:f() == 1)\n"
        "assert(x:g() == 2)\n"
        "assert(x:g() == 2)\n"
        "assert(x:h() == 3)\n"
        "assert(x:h() == 3)\n"
    );

    DOSTRING(L,
        "y = upcast(x)\n"
        "assert(y:f() == 1)\n"
        "assert(y:f() == 1)\n"
        "assert(y:g() == 2)\n"
        "assert(y:g() == 2)\n"
        "assert(y:h() == 3)\n"
        "assert(y:h() == 3)\n"
    );

    module(L) [
        class_<Base>("Base"),
        class_<Left, Base>("Left")
            .def("left", &Left::left),
        class_<Right, Base>("Right")
            .def("right", &Right::right),
        class_<Derived, bases<Left, Right> >("Derived")
            .def(constructor<>())
            .def("f", &Derived::f),
        def("left", &left),
        def("right", &right)
    ];

    DOSTRING(L,
        "x = Derived()\n"
        "assert(x:left() == 1)\n"
        "assert(x:left() == 1)\n"
        "assert(x:right() == 2)\n"
        "assert(x:right() == 2)\n"
        "assert(x:f() == 3)\n"
        "assert(x:f() == 3)\n"
    );

    DOSTRING(L,
        "y = left(x)\n"
        "assert(y:left() == 1)\n"
        "assert(y:left() == 1)\n"
        "assert(y:right() == 2)\n"
        "assert(y:right() == 2)\n"
        "assert(y:f() == 3)\n"
        "assert(y:f() == 3)\n"
    );

    DOSTRING(L,
        "y = right(x)\n"
        "assert(y:left() == 1)\n"
        "assert(y:left() == 1)\n"
        "assert(y:right() == 2)\n"
        "assert(y:right() == 2)\n"
        "assert(y:f() == 3)\n"
        "assert(y:f() == 3)\n"
    );
}
