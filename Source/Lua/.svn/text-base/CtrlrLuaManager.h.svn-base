#ifndef __CTRLR_LUA_MANAGER__
#define __CTRLR_LUA_MANAGER__

#pragma warning(disable:4100)

#include "Methods/CtrlrLuaMethodManager.h"
#include "CtrlrLuaUtils.h"
#include "CtrlrLuaMultiTimer.h"
#include "CtrlrLuaAudioConverter.h"

class LAudioFormatManager;
class CtrlrPanel;
class CtrlrModulator;

class CtrlrLuaManager : public ValueTree::Listener
{
	public:
		CtrlrLuaManager(CtrlrPanel &_owner);
		~CtrlrLuaManager();
		static void console (const String &arg);
		static void assert_();
		static void debug (const String &arg);
		static void sleep (const int milliseconds);
		static std::string stringToLua (const String &string);
		static const String toJuceString (const std::string &arg);
		static const double int64ToDouble(const int64 value);
		static const int int64ToInt(const int64 value);

		void assignDefaultObjects(lua_State* L);
		void wrapBasicIO(lua_State* L);
		void wrapCore(lua_State* L);
		void wrapCtrlrClasses(lua_State* L);
		void wrapJuceClasses(lua_State* L);
		void wrapJuceCoreClasses(lua_State *L);
		void wrapConverters(lua_State* L);
		void wrapUtilities(lua_State* L);
		bool runCode (const String &code);

		void setProperty (const Identifier& name, const var &newValue, const bool isUndoable=false);
		const var &getProperty (const Identifier& name) const											{ return luaManagerTree.getProperty (name); }
		const var getProperty (const Identifier& name, const var &defaultReturnValue) const				{ return luaManagerTree.getProperty (name, defaultReturnValue); }
		UndoManager* getUndoManager()																	{ return (0); }
		ValueTree &getLuaManagerTree()																	{ return (luaManagerTree); }

		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
		void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
		void valueTreeChildAdded (ValueTree& parentTree, ValueTree& child){}
		void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& child){}
		void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
		static void log(const String &message);
		void createAudioThreadState();

		void restoreState (const ValueTree &savedState);
		const String getLastError()							{ return (lastError); }
		lua_State *getLuaState()							{ return (luaState); }
		lua_State *getAudioThreadLuaState()					{ return (audioThreadState); }

		const bool isRestoring();
		CtrlrPanel &getOwner()								{ return (owner); }
		CtrlrLuaMethodManager &getMethodManager();

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLuaManager);
		CtrlrLuaMethodManager *methodManager;
		String lastError;
		ValueTree luaManagerTree;
		File scriptsDir;
		File importersDir;
		CtrlrPanel &owner;
		lua_State* luaState, *audioThreadState;
		CtrlrLuaUtils utils;
		CtrlrLuaMultiTimer *multiTimer;
		CtrlrLuaAudioConverter audioConverter;
		LAudioFormatManager *luaAudioFormatManager;
};

#endif
