#ifndef __L_GLOBAL_FUNCTIONS__
#define __L_GLOBAL_FUNCTIONS__

#include "JuceHeader.h"
extern  "C"
{
	#include "lua.h"
}

class LGlobalFunctions
{
	public:
		LGlobalFunctions();
		static double double_Pi();
		static float float_Pi();
		static void debug(const String &argument);
		static void debug(const std::string &argument);
		static void sleep (const int milliseconds);
		static std::string stringToLua (const String &string);
		static String toJuceString (const std::string &string);
		static void console (const String &arg);
		static void console (const std::string &arg);
		static void wrapForLua (lua_State *L);
		static void setLookAndFeel (Component *component, luabind::object lookAndFeelObject);
};

#endif
