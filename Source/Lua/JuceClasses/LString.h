#ifndef __L_STRING__
#define __L_STRING__

#include "JuceHeader.h"
extern  "C"
{
	#include "lua.h"
}

class LString
{
	public:
		static void wrapForLua (lua_State *L);
};

class LStringArray : public StringArray
{
    public:
        LStringArray(const StringArray &other) : StringArray(other) {}
        LStringArray() {}
        LStringArray (const String &string) : StringArray (string) {}
        LStringArray (const char *const *pointer, const int size) : StringArray (pointer, size) {}
        LStringArray (const char *const *pointer) : StringArray (pointer) {}
        String get(const int index)
        {
            return (StringArray::strings[index]);
        }
};

#endif
