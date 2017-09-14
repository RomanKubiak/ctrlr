Implementation notes
====================

The classes and objects are implemented as user data in Lua. To make sure that
the user data really is the internal structure it is supposed to be, we tag
their metatables. Previously a boolean at a string key was used, making it
relatively easy for the malevolent user to fool Luabind and crash the
application. However, this has been replaced with a light userdata key that
should be quite impossible to imitate.

In the Lua registry, luabind kept an entry called ``"__luabind_classes"``.
This string key is now also replaced with a light userdata one.

In the global table, a variable called ``super`` is used every time a
constructor in a lua-class is called. This is to make it easy for that
constructor to call its base class' constructor. So, if you have a global
variable named super it may be overwritten. This is probably not the best
solution, and this restriction may be removed in the future.

.. note:: Deprecated

  ``super()`` has been deprecated since version 0.8 in favor of directly
  invoking the base class' ``__init()`` function::

    function Derived:__init()
        Base.__init(self)
    end


The detail namespace and undocumented features
----------------------------------------------

Inside the luabind namespace, there’s another namespace called ``detail``.
Everything cotained therein should not be used by user code and is subject to
change or vanish even between patch versions. There also exist no explicit
tests or documentation for this namespace’s contents.

Classes and functions which reside directly in the ``luabind`` namespace but
are not documented should also rather not be used. However, if you have to
depend on undocumented features, these are still better than the ``detail``
ones.
