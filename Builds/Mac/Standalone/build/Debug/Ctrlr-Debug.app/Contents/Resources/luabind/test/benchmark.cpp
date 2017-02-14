#include <ctime>
#include <iostream>

namespace std
{
    using ::clock_t;
//  using ::clock;
}

extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
}

#include <luabind/luabind.hpp>

struct A {};

// luabind function
static float f1(int, float, const char*, A*)
{
    return 3.14f;
}

// empty function
static int f2(lua_State*)
{
    return 0;
}

inline double clocks_to_seconds(std::clock_t c)
{
    return static_cast<double>(c) / CLOCKS_PER_SEC;
}


int main()
{
    const int num_calls = 100000;
    const int loops = 10;

    using namespace luabind;

    lua_State* L = luaL_newstate();
    open(L);

    module(L) [
        class_<A>("A")
            .def(constructor<>()),
        def("test1", &f1)
    ];

    lua_pushcclosure(L, &f2, 0);
    lua_setglobal(L, "test2");

    std::clock_t total1 = 0;
    std::clock_t total2 = 0;

    for (int i = 0; i < loops; ++i)
    {
        // benchmark luabind
        std::clock_t start1 = std::clock();
        luaL_dostring(L, "a = A()\n"
                         "  for i = 1, 100000 do\n"
                         "  test1(5, 4.6, 'foo', a)\n"
                         "end");

        std::clock_t end1 = std::clock();


        // benchmark empty binding
        std::clock_t start2 = std::clock();
        luaL_dostring(L, "a = A()\n"
                         "for i = 1, 100000 do\n"
                         "  test2(5, 4.6, 'foo', a)\n"
                         "end");

        std::clock_t end2 = std::clock();
        total1 += end1 - start1;
        total2 += end2 - start2;
    }


    double time1 = clocks_to_seconds(total1);
    double time2 = clocks_to_seconds(total2);

#ifdef LUABIND_NO_ERROR_CHECKING
    std::cout << "without error-checking\n";
#endif
    std::cout << "luabind: " << time1 * 1000000 / num_calls / loops << " microseconds per call\n"
              << "empty  : " << time2 * 1000000 / num_calls / loops << " microseconds per call\n"
              << "diff   : " << ((time1 - time2) * 1000000 / num_calls / loops) << " microseconds\n\n";

    lua_close(L);
}
