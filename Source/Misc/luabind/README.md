Luabind
=======

Luabind is a library that helps you create bindings between C++ and Lua. It
has the ability to expose functions and classes, written in C++, to Lua. It
will also supply the functionality to define classes in lua and let them
derive from other lua classes or C++ classes. Lua classes can override virtual
functions from their C++ baseclasses. It is written towards Lua 5.x, and does
not work with Lua 4.

It is implemented utilizing template meta programming. That means that you
don't need an extra preprocess pass to compile your project (it is done by the
compiler). It also means you don't (usually) have to know the exact signature
of each function you register, since the library will generate code depending
on the compile-time type of the function (which includes the signature). The
main drawback of this approach is that the compilation time will increase for
the file that does the registration, it is therefore recommended that you
register everything in the same cpp-file.

Luabind is released under the terms of the [MIT license][1].

> Copyright Daniel Wallin, Arvid Norberg 2003.
> Extracted from <http://www.rasterbar.com/products/luabind/docs.html>

[1]: http://www.opensource.org/licenses/mit-license.php


This fork
---------

I forked the project since it seems abandoned (latest commit from January 2012
on the 0.9 branch) and I ran into certain bugs which needed fixing (see
commits).

This should actually have been forked from [rpavlik/luabind][rpavlik]: I
cherry-picked most commits from there. Additionally, many commits from
[fhoefler/luaponte][fhoefling] are incorporated (as the are in rpavlik's
fork). Thus, feel free to do the same with my fork.

[rpavlik]: http://github.com/rpavlik/luabind/
[fhoefling]: http://github.com/fhoefling/luaponte

In the following two sections, the improvements over the latest official
luabind release (0.9) are described.

### Fixed bugs ###

* Destroyed objects now have their metatable unset. Previously, one could
  easily cause segmentation faults and other undefined behavior by accessing
  destroyed objects from luabinds `__finalize` or Lua 5.2's `__gc`. Now you
  can simply check with `getmetatable(obj)`, and if you forget, you get an
  ordinary, well defined Lua error instead. Commit [a83aa][c-destroy].
* The Lua part of a `wrap_base` derived class randomly got lost after a few
  garbage collection cycles due to errors in the implementation of the
  internal `weak_ref` class. Credits for the fix go to Max McGuire who
  [posted][mmg-fix] a fix on luabind-user in 2010. Commit [a3a400][c-weakref].
* The error message displayed when a function could not be called from Lua
  with the provided arguments sometimes only contained the function signatures
  but not the actual error message. mrwonko's commit [9d15e0][c-errmsg] (and
  previous).
* Luabind did not work over shared library (DLL) boundaries on some
  platforms. fhoefling's commit [a83af3][c-dll] and my minor improvement
  [a8349d][c-dll2].
* Calling `call_function` with a return type but not using it resulted in a
  call to `std::terminate` if the called function produced an error and a
  C++11 compliant compiler is used. Commit [81bdcb][c-noexpect].
* Luabind failed to recognize Lua numbers correctly on MSVC x64. Commit
  [c9582c][c-longlong].

* Luabind failed to compile on g++ with Boost 1.49
  (`BOOST_PP_ITERATION_FLAGS` problem). The first one I know to have fixed
  this is [fhoefling][c-fh-gcc-ftbfs]. Commit [1aa80b][c-gcc-ftbsfs].
* Luabind failed to compile on Clang. Commit [4555b2][c-clang-ftbfs].

[c-destroy]: http://github.com/Oberon00/luabind/commit/a83aae710ccb5d4fad2d625e3c87008d450949cb
[mmg-fix]: http://lua.2524044.n2.nabble.com/weak-ref-issue-patch-td7581558.html
[c-weakref]: http://github.com/Oberon00/luabind/commit/a3a400e5fc5f31b5733ad0e595e7f5b474883174
[c-fh-gcc-ftbfs]: http://github.com/fhoefling/luaponte/commit/085f2e06204d6b2710db127806cfa855fca17d79
[c-gcc-ftbsfs]: http://github.com/Oberon00/luabind/commit/1aa80be0bb944e960919542b16c6a3a117a4cdb8
[c-errmsg]: http://github.com/Oberon00/luabind/commit/9d15e0288261ef83b227a3151d8f2ac238ef3759
[c-dll]: http://github.com/Oberon00/luabind/commit/a83af3c69a3cd6da5ba21ea5062205fa664e59d2
[c-dll2]: http://github.com/Oberon00/luabind/commit/a8349dfd94bcc456af5dc4b1bf4f175875d8ae54
[c-longlong]: http://github.com/Oberon00/luabind/commit/c9582cea44fd67301ee5940cf08ccf5ae8c90094
[c-noexpect]: http://github.com/Oberon00/luabind/commit/81bdcb72aa6ef7b321e59416b77be65c3944d6a9
[c-clang-ftbfs]: http://github.com/Oberon00/luabind/commit/4555b20f0553f073d9d9085a43174aea5f7abaa6

### Added features ###

* CMake replaces the broken Jamfile as build system (including installation
  and test support).
  A [`FindLuabind.cmake`][findluabind] file is also provided, as well as
  [`FindLua52.cmake`][findlua52].
* A bit of C++11 support:
    + `std::shared_ptr` is supported as smart pointer through
      [`luabind/std_shared_ptr_converter.hpp`][stdptr].
      Commit [118f80][c-11-ptr].
    + Scoped enums can be used with `enum_`.
    + Basic rvalue reference support. fhoefling's commit [a83af3][c-11-rval].
    + Support for `long long`. Commit [c9582c][c-longlong] (also for
      pre-C++11 compilers supporting it).
* A new (C++) function `set_package_preload` can be used to register a
  (loader) function to be called only if it is `require`d from Lua. rpavlik's
  commit [3502e9][c-preload].
* Modules can now register everything to arbitrary tables
  (`luabind::object`s). fhoefling's commit [dd4a16][c-table]. This plays
  together very nicely with `set_package_preload`.
* The modulo operator `%` can now be exported to Lua. rpavlik's commit
  [855b4a][c-modulo] and the following.
* `class_info` can now handle actual classes as arguments. Previously it could
  handle only *objects* of luabind classes. rpavlik's commit
  [c2ee1f][c-classinfo].

[findluabind]: cmake/Modules/FindLuabind.cmake
[findlua52]: cmake/Modules/FindLua52.cmake
[stdptr]: luabind/std_shared_ptr_converter.hpp
[c-11-ptr]: http://github.com/Oberon00/luabind/commit/118f808b068e93e78fc717749f757a2358b9a4af
[c-11-rval]: http://github.com/Oberon00/luabind/commit/a83af3c69a3cd6da5ba21ea5062205fa664e59d2
[c-classinfo]: http://github.com/Oberon00/luabind/commit/c2ee1f82598eb3ded6922e05decdcc7bb69a8d2a
[c-preload]: http://github.com/Oberon00/luabind/commit/3502e9c7234daf1b12f6dc7f545d361d5cee105d
[c-table]: http://github.com/Oberon00/luabind/commit/dd4a1695dcbabbe1541f229ff245178b0621cf0d
[c-modulo]: http://github.com/Oberon00/luabind/commit/855b4afba0204d0ae6e8fbd251dfc71f4d84353e

Additionally, the removal of many lines of death code, also unused (parts of)
member variables and other minor improvements make luabind generally
(a little bit) faster and less memory hungry.

Many compiler warnings have also been fixed. The remaining (irrelevant) ones
are silenced, so the build should be completely warning- (and of course
error-)free on Clang, g++ and MSVC.

This fork is fully source (API) compatible to the original luabind library,
but not binary compatible.

### A word on the branch names ###

First I worked against the 0.9 branch but then decided to rename it to master,
since it actually has become the master branch of development in this fork.
The original master branch is now named old-master.
