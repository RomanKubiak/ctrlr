Building luabind
================

Prerequisites
-------------

Apart from Lua 5.1 or (recommended) 5.2, Luabind depends on a number of Boost
libraries. It also depends on `CMake`_ to build the library and run the tests.

.. _CMake: http://www.cmake.org/


Windows
-------

If CMake has problems finding Lua, LUA_DIR needs to be set to point to a
directory containing the Lua include directory and built libraries.

The same applies to Boost and the BOOST_ROOT environment variable.


Linux and other \*nix flavors
-----------------------------

If your system already has Lua installed, it is very likely that the
build system will automatically find it and just work. If you have
Lua installed in a non-standard location, you may need to set
``LUA_DIR`` to point to the installation prefix.

``BOOST_ROOT`` can be set to a Boost installation directory. If left
unset, the build system will try to use boost headers from the standard
include path.


Building and testing
--------------------

Building the default variant of the library, which is a static release
library, is simply done by invoking cmake in the luabind root directory and
then running your native build tools on the generated files (e.g. make on Unix
or nmake/msbuild ALL_BUILD.vcxproj for MSVC).

.. note::
  To build your application against the shared library variant,
  LUABIND_DYNAMIC_LINK needs to be defined to properly import symbols.

To run the unit tests, invoke your build tool with the test target, e.g.
``make test`` on Unix or ``nmake test/msbuild RUN_TESTS.vcxproj`` for MSVC.
This run the (previously built) unit tests in the current variant. A clean
test run output should end with something like::

  100% tests passed, 0 tests failed out of 51
  Total Test time (real) =   1.23 sec

A failed run would end with something like::

  98% tests passed, 1 tests failed out of 51

  Total Test time (real) =   1.23 sec

  The following tests FAILED:
      1 - abstract_base (Failed)
