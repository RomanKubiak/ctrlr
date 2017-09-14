Known issues
============

- You cannot use strings with extra nulls in them as member names that refers
  to C++ members.

- If one class registers two functions with the same name and the same
  signature, there's currently no error. The last registered function will
  be the one that's used.

- In VC7, classes can not be called test.

- If you register a function and later rename it, error messages will use the
  original function name.

- luabind does not support class hierarchies with virtual inheritance. Casts are
  done with static pointer offsets.
