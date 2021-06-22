// Copyright Chsritian Neumüller 2013. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"

#include <luabind/intrusive_ptr_converter.hpp>
#include <luabind/luabind.hpp>

#include <boost/noncopyable.hpp>
#include <iostream>

using boost::intrusive_ptr;

namespace {

    struct B: private boost::noncopyable, counted_type<B>
    {
        B(int val_): ref_cnt(0), val(val_) {}
        virtual ~B() {
            std::cout << "~B\n";
            TEST_CHECK(ref_cnt == 0);
        }

        int ref_cnt;
        int val;
    };

    COUNTER_GUARD(B);

    struct D: B
    {
        D(int val_): B(val_) {}
    };

    void intrusive_ptr_add_ref(B* b)
    {
        ++b->ref_cnt;
    }

    void intrusive_ptr_release(B* b)
    {
        if (!--b->ref_cnt)
            delete b;
    }

    void needs_b(intrusive_ptr<B> pb, int expected_rc)
    {
        TEST_CHECK(pb->ref_cnt == expected_rc);
    }

    void needs_d(intrusive_ptr<D> pd)
    {
        TEST_CHECK(pd->ref_cnt == 2);
    }

    intrusive_ptr<B> filter_b(intrusive_ptr<B> pb)
    {
        TEST_CHECK(pb->ref_cnt == 2);
        return pb;
    }

} // namespace unnamed

void test_main(lua_State* L)
{
    using namespace luabind;

    module(L) [
        class_<B, intrusive_ptr<B> >("B")
            .def(constructor<int>())
            .def_readonly("val", &B::val)
            .def_readonly("ref_cnt", &B::ref_cnt),
        class_<D, B, intrusive_ptr<D> >("D")
            .def(constructor<int>()),
        def("needs_b", &needs_b),
        def("needs_d", &needs_d),
        def("filter_b", &filter_b)
    ];

    DOSTRING(L,
        "d = D(1)\n"
        "print(d.val, d.ref_cnt)\n"
        "assert(d.val == 1)\n"
        "assert(d.ref_cnt == 1)\n"
    );

    DOSTRING(L,
        "needs_d(d)\n"
        "needs_b(d, 2)\n"
    );

    DOSTRING(L,
        "bd = filter_b(d)\n"
        "assert(bd.val == 1)\n"
        "assert(bd.ref_cnt == 2)\n"
        "needs_b(bd, 3)\n"
        "assert(bd.ref_cnt == 2)\n"
    );

    DOSTRING(L,
         "d = nil\n"
         "collectgarbage()\n"
         "collectgarbage()\n"
         "assert(bd.ref_cnt == 1)\n"
    );
}
