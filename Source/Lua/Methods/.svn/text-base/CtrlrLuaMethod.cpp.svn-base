#include "stdafx.h"
#include "CtrlrLuaObjectWrapper.h"
#include "CtrlrLuaMethod.h"
#include "CtrlrIDs.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrLuaMethodManager.h"
#include "CtrlrLuaManager.h"
#include "CtrlrLua/MethodEditor/CtrlrLuaMethodCodeEditor.h"

CtrlrLuaMethod::CtrlrLuaMethod(CtrlrLuaMethodManager &_owner) 
	:	methodIsValid(false), 
		methodTree(Ids::luaMethod),
		owner(_owner),
		methodCodeEditor(nullptr),
		audioThreadMethod(false)
{
	luaObject = new CtrlrLuaObjectWrapper();
	methodTree.addListener (this);

	out = Font(owner.getOwner().getOwner().getOwner().getFontManager().getDefaultMonoFontName(), 10.0f, Font::plain);
}

CtrlrLuaMethod::CtrlrLuaMethod(CtrlrLuaMethodManager &_owner, ValueTree &_methodTree) 
	:	methodIsValid(false), 
		methodTree(_methodTree),
		owner(_owner),
		methodCodeEditor(nullptr),
		audioThreadMethod(false)
{
	luaObject = new CtrlrLuaObjectWrapper();
	
	setCodeInternal (getCode());

	methodTree.addListener (this);

	out = Font(owner.getOwner().getOwner().getOwner().getFontManager().getDefaultMonoFontName(), 10.0f, Font::plain);
}

CtrlrLuaMethod::~CtrlrLuaMethod()
{
	methodTree.removeListener (this);
	masterReference.clear();
	deleteAndZero (luaObject);
}

void CtrlrLuaMethod::remove() // this is called by the manager to remove us permanently, cleanup and stuff
{
	setValid (false);

	if (luaObject->getObject().is_valid())
	{
		luabind::globals (owner.getOwner().getLuaState()) [(const char *)getName().toUTF8()] = 0;
	}
	methodTree.removeListener (this);
	masterReference.clear();
	deleteAndZero (luaObject);
}

const bool CtrlrLuaMethod::isSourceInFile()
{
	if ((int)methodTree.getProperty(Ids::luaMethodSource) == codeInFile)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

const String CtrlrLuaMethod::getName() const
{
	return (methodTree.getProperty (Ids::luaMethodName).toString());
}

CtrlrLuaObjectWrapper &CtrlrLuaMethod::getObject()
{
	return (*luaObject);
}

Uuid CtrlrLuaMethod::getUuid()
{
	return (methodTree.getProperty (Ids::uuid).toString());
}

const File CtrlrLuaMethod::getSourceFile()
{
	return (File (methodTree.getProperty (Ids::luaMethodSourcePath)));
}

void CtrlrLuaMethod::setObject (CtrlrLuaObjectWrapper _luaObject)
{
	*luaObject = _luaObject;
}

void CtrlrLuaMethod::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::luaMethodValid)
	{
		methodIsValid = (bool)treeWhosePropertyHasChanged.getProperty(property);
	}
	else if (property == Ids::luaMethodName)
	{
		if (methodCodeEditor)
		{
			methodCodeEditor->triggerAsyncUpdate();
		}
	}
}

bool CtrlrLuaMethod::isAudioThreadMethod()
{
	return (audioThreadMethod);
}

lua_State *CtrlrLuaMethod::getLuaState()
{
	if (isAudioThreadMethod())
	{
		return(owner.getOwner().getAudioThreadLuaState());
	}

	return(owner.getOwner().getLuaState());
}

const String CtrlrLuaMethod::getCode()
{
	if (isSourceInFile())
	{
		return (getSourceFile().loadFileAsString());
	}
	else
	{
		if (methodTree.getProperty (Ids::luaMethodCode).toString().isEmpty())
		{
			return (owner.getDefaultMethodCode (methodTree.getProperty(Ids::name), methodTree.getProperty(Ids::luaMethodLinkedProperty)));
		}
		else
		{
			return (methodTree.getProperty (Ids::luaMethodCode).toString());
		}
	}
}

const bool CtrlrLuaMethod::setCodeInternal(const String &newMethodCode)
{
	bool compileRet			= owner.getOwner().runCode (newMethodCode);
	errorString.clear();
	errorString.append ("Compile: "+getName()+" - ", out, Colours::black);
	
	String error;

	if (compileRet && getName() != String::empty)
	{
		try
		{
			setObject ( (luabind::object)luabind::globals (getLuaState()) [(const char *)getName().toUTF8()] );
		}
		catch (const luabind::error &e)
		{
			error = String(e.what());
		}
	}
	else if (compileRet == false)
	{
		error = owner.getOwner().getLastError();
	}

	if (compileRet)
	{
		errorString.append ("OK\n", out.withStyle(Font::bold), Colours::black);
	}
	else
	{
		errorString.append ("FAILED\n", out.withStyle(Font::bold), Colours::darkred);
		errorString.append (error+"\n", out, Colours::darkred);
	}

	setValid(compileRet);

	return (compileRet);
}

void CtrlrLuaMethod::setValid (const bool _methodIsValid)
{
	methodIsValid = _methodIsValid;
	methodTree.setProperty (Ids::luaMethodValid, methodIsValid, nullptr);
}

const bool CtrlrLuaMethod::isValid () const
{
	return (methodIsValid);
}

void CtrlrLuaMethod::setCodeEditor (CtrlrLuaMethodCodeEditor *_methodCodeEditor)
{
	methodCodeEditor = _methodCodeEditor;
}

CtrlrLuaMethodCodeEditor *CtrlrLuaMethod::getCodeEditor()
{
	return (methodCodeEditor);
}

void CtrlrLuaMethod::triggerSourceChangeFromEditor(const bool recompile)
{
	if (methodCodeEditor == nullptr || methodCodeEditor.wasObjectDeleted())
	{
		jassertfalse;		// no editor and we got a trigger from it ? that's just fucked up
		return;
	}

	if (isSourceInFile())
	{
		// replace the contents of the file with the editors content
		getSourceFile().replaceWithText (methodCodeEditor->getCodeDocument().getAllContent());
	}
	else
	{
		// replace the contents of the property with the editors content
		methodTree.setProperty (Ids::luaMethodCode, methodCodeEditor->getCodeDocument().getAllContent(), nullptr);
	}

	if (recompile)
	{
		// we need to recompile our code
		setCodeInternal (getCode());
	}
	else
	{
		errorString.clear();
		errorString.append (Time::getCurrentTime().formatted (getName()+" saved at %m/%d/%y %H:%M:%S\n"), out, Colours::black);
	}
}

const int CtrlrLuaMethod::getCodeSize()
{
	return (getCode().length());
}