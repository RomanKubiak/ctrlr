Introduction
============

Luabind is a library that helps you create bindings between C++ and Lua. It has
the ability to expose functions and classes, written in C++, to Lua. It will
also supply the functionality to define classes in Lua and let them derive from
other Lua classes or C++ classes. Lua classes can override virtual functions
from their C++ base classes. It is written towards Lua 5.2 but should also
work with 5.1.

It is implemented utilizing template meta programming. That means that you
don't need an extra preprocess pass to compile your project (it is done by the
compiler). It also means you don't (usually) have to know the exact signature
of each function you register, since the library will generate code depending
on the compile-time type of the function (which includes the signature). The
main drawback of this approach is that the compilation time will increase for
the file that does the registration, it is therefore recommended that you
register everything in the same cpp-file.

Luabind is released under the terms of the `MIT license`_.

We are very interested in hearing about projects that use luabind, please let
us know about your project.

The main channel for help and feedback is the `luabind mailing list`_.
There's also an IRC channel ``#luabind`` on irc.freenode.net.

Additionally, this fork’s `github issue tracker`_ can also be used for bug reports, feature requests and questions.

.. _`luabind mailing list`: https://lists.sourceforge.net/lists/listinfo/luabind-user
.. _MIT license: http://www.opensource.org/licenses/mit-license.php
.. _Boost: http://www.boost.org
.. _github issue tracker: https://github.com/Oberon00/luabind/issues


Features
========

Luabind supports:

 - Overloaded free functions
 - C++ classes in Lua
 - Overloaded member functions
 - Operators
 - Properties
 - Enums (also C++11 ``enum class`` if available)
 - Lua functions in C++
 - Lua classes in C++
 - Lua classes (single inheritance)
 - Derives from Lua or C++ classes
 - Override virtual functions from C++ classes
 - Implicit casts between registered types
 - Best match signature matching
 - Return value policies and parameter policies


Portability
===========

Luabind is currently tested regularly with

    * Microsoft Visual C++ 11 (2012) x32 and x64
    * gcc 4.8 x64 (with and without -std=c++11)
    * Clang 3.2 x64 (with and without -std=c++11)

It should work with any compiler conformant with C++03. However, probably only
versions of the above threecompilers will work out of the box with the
provided CMake build files. Please report any issues you have to the
`github issue tracker`_.
