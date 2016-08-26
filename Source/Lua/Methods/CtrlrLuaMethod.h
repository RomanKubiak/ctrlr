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

		void setCodeEditor (CtrlrLuaMethodCodeEditor *_methodCodeEditor);
		CtrlrLuaMethodCodeEditor *getCodeEditor();
		void setObject (CtrlrLuaObjectWrapper _luaObject);

		const String getName() const;
		CtrlrLuaObjectWrapper &getObject();
		bool isValid() const;
		void setValid (const bool _methodIsValid);
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
		bool setCodeInternal (const String &newMethodCode);
		WeakReference<CtrlrLuaMethod>::Master masterReference;
		friend class WeakReference<CtrlrLuaMethod>;
		CtrlrLuaObjectWrapper *luaObject;
		bool methodIsValid;
		ValueTree methodTree;
		String methodName;
		CtrlrLuaMethodManager &owner;
		WeakReference <CtrlrLuaMethodCodeEditor> methodCodeEditor;
		AttributedString errorString;
		bool audioThreadMethod;
};

#endif
