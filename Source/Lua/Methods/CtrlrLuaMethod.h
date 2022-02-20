#ifndef __CTRLR_LUA_METHOD__
#define __CTRLR_LUA_METHOD__

extern "C"
{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

#include "JuceHeader.h"

#ifdef _WIN32
#pragma warning(disable:4100)
#endif // _WIN

class CtrlrModulator;
class CtrlrPanel;
class CtrlrLuaObjectWrapper;
class CtrlrLuaMethodManager;
class CtrlrLuaMethodCodeEditor;

class CtrlrLuaMethod : public ValueTree::Listener
{
	public:
		CtrlrLuaMethod(CtrlrLuaMethodManager &_owner);
		CtrlrLuaMethod(CtrlrLuaMethodManager &_owner, ValueTree &_methodTree);
		~CtrlrLuaMethod();

		enum MethodSouce
		{
			codeInProperty,
			codeInFile
		};

	        enum Type
		{
			NONE = LUA_TNONE,
			NIL = LUA_TNIL,
			BOOLEAN = LUA_TBOOLEAN,
			LIGHTUSERDATA = LUA_TLIGHTUSERDATA,
			NUMBER = LUA_TNUMBER,
			STRING = LUA_TSTRING,
			TABLE = LUA_TTABLE,
			FUNCTION = LUA_TFUNCTION,
			USERDATA = LUA_TUSERDATA,
			THREAD = LUA_TTHREAD,
			SCRIPT
#if LUA_VERSION_NUM > 501
			= LUA_NUMTAGS
#endif
			,
			NUMTAGS = SCRIPT,
			ERROR,
			UNKNOWN,
			DISABLED
		};


		void setCodeEditor (CtrlrLuaMethodCodeEditor *_methodCodeEditor);
		CtrlrLuaMethodCodeEditor *getCodeEditor();
		void setObject (CtrlrLuaObjectWrapper _luaObject);

		const String getName() const;
		CtrlrLuaObjectWrapper &getObject();
		Type getType() const { return type ; }
		void setType(Type t);
		bool isValid() const;
		// void setValid (const bool _methodIsValid);
		bool isCallable() const;
		void remove();
		ValueTree &getMethodTree()											{ return (methodTree); }
		Uuid getUuid();
		const String getCode();
		const AttributedString getLastError()								{ return (errorString); }
		bool isSourceInFile();
		const File getSourceFile();
		int getCodeSize();
		void setSourceFile (const File &sourceFile);
		void triggerSourceChangeFromEditor(const bool recompile);
		bool isAudioThreadMethod();
		lua_State *getLuaState();
		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &/*treeWhoseChildHasChanged*/){}
		void valueTreeParentChanged (ValueTree &/*treeWhoseParentHasChanged*/){}
		void valueTreeChildAdded (ValueTree& /*parentTree*/, ValueTree& /*child*/){}
		void valueTreeChildRemoved (ValueTree& /*parentTree*/, ValueTree& /*child*/, int){}
		void valueTreeChildOrderChanged (ValueTree& /*parentTreeWhoseChildrenHaveMoved*/, int, int){}

		JUCE_LEAK_DETECTOR(CtrlrLuaMethod)

	private:
		Font out;
		Type setCodeInternal (const String &newMethodCode);
		WeakReference<CtrlrLuaMethod>::Master masterReference;
		friend class WeakReference<CtrlrLuaMethod>;
		CtrlrLuaObjectWrapper *luaObject;
		Type type;
		ValueTree methodTree;
		String methodName;
		CtrlrLuaMethodManager &owner;
		WeakReference <CtrlrLuaMethodCodeEditor> methodCodeEditor;
		AttributedString errorString;
		bool audioThreadMethod;
};

inline bool CtrlrLuaMethod::isValid() const {
	switch (getType()) {
	case BOOLEAN:
	case LIGHTUSERDATA:
	case NUMBER:
	case STRING:
	case TABLE:
	case FUNCTION:
	case USERDATA:
	case THREAD:
#if LUA_VERSION_NUM > 501
	case SCRIPT:
#endif
		return true;
	case NONE:
	case NIL:
	case ERROR:
	case UNKNOWN:
	case DISABLED:
	default:
		return false;
	}
}

inline bool CtrlrLuaMethod::isCallable() const {
	switch (getType()) {
	case FUNCTION:
		return true;
	case NONE:
	case NIL:
	case BOOLEAN:
	case LIGHTUSERDATA:
	case USERDATA:
	case THREAD:
	case SCRIPT:
	case NUMBER:
	case STRING:
	case TABLE:
	case ERROR:
	case UNKNOWN:
	case DISABLED:
	default:
		return false;
	}
}


#endif
