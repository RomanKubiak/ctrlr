#include "stdafx.h"
#include <luabind/luabind.hpp>
#include "CtrlrLuaMethodManager.h"
#include "CtrlrLuaManager.h"
#include "CtrlrLog.h"
#include "CtrlrLuaObjectWrapper.h"
#include "CtrlrComponents/CtrlrCustomComponent.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrComponents/Specials/CtrlrWaveform.h"
#include "CtrlrPanel/CtrlrPanelCanvas.h"
#include "CtrlrComponents/CtrlrComponent.h"

#define CATCH_METHOD_EXCEPTION \
catch (luabind::error &e)\
{\
	o->setValid(false);\
	const char* a = lua_tostring(e.state(), -1);\
	lastExecutionError = String(a);\
	AlertWindow::showMessageBox (AlertWindow::WarningIcon, "Callback error: " + o->getName(), String(e.what()) + "\n" + lastExecutionError + "\n\nMethod disabled");\
	_LERR("Callback error: [" + o->getName() + "] " + String(e.what())+" "+lastExecutionError+".\nMethod disabled");\
	return (false);\
}

#define CATCH_METHOD_EXCEPTION_NO_DIALOG \
catch (luabind::error &e)\
{\
	o->setValid(false);\
	const char* a = lua_tostring(e.state(), -1);\
	lastExecutionError = String(a);\
	_LERR("Callback error: [" + o->getName() + "]\n" + lastExecutionError.fromLastOccurrenceOf("Error message:\n",false,false) + ".\nMethod disabled");\
	return (false);\
}

#define LUA_DEBUG						if (getDebug() && o) { _INF("CtrlrLuaMethodManager::call " + o->getName()); }

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
			luabind::call_function<void>(o->getObject().getObject());
	}
	CATCH_METHOD_EXCEPTION

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, CtrlrModulator *param1, const int param2)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
		{
			luabind::call_function<void>(o->getObject().getObject(), param1, param2);
		}
	}
	CATCH_METHOD_EXCEPTION

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, CtrlrModulator *param1, const String param2)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
		{
			luabind::call_function<void>(o->getObject().getObject(), param1, param2.toUTF8().getAddress());
		}
	}
	CATCH_METHOD_EXCEPTION

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, CtrlrComponent *param1, const String param2)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
		{
			luabind::call_function<void>(o->getObject().getObject(), param1, param2.toUTF8().getAddress());
		}
	}
	CATCH_METHOD_EXCEPTION

	return (true);

}
const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, const MidiMessage &param1)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
		{
			CtrlrMidiMessage mm(param1);
			const luabind::object &obj = o->getObject().getLuabindObject();
			if (obj.is_valid())
			{
				luabind::call_function<void>(obj, mm);
			}
		}
	}
	CATCH_METHOD_EXCEPTION

	return (true);
}



const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, const CtrlrMidiMessage &param1)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
		{
			const luabind::object &obj = o->getObject().getLuabindObject();
			if (obj.is_valid())
			{
				luabind::call_function<void>(obj, param1);
			}
		}
	}
	CATCH_METHOD_EXCEPTION

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, CtrlrCustomComponent *param1)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
			luabind::call_function<void>(o->getObject().getObject(), param1);
	}
	CATCH_METHOD_EXCEPTION

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, CtrlrCustomComponent *param1, Graphics &param2)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
			luabind::call_function<void>(o->getObject().getObject(), param1, boost::ref(param2));
	}
	CATCH_METHOD_EXCEPTION_NO_DIALOG

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, CtrlrPanelCanvas *param1, Graphics &param2)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
		{
			luabind::call_function<void>(o->getObject().getObject(), param1, boost::reference_wrapper<Graphics>(param2));
		}
	}
	CATCH_METHOD_EXCEPTION_NO_DIALOG

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, CtrlrPanel *param1)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
			luabind::call_function<void>(o->getObject().getObject(), param1);
	}
	CATCH_METHOD_EXCEPTION_NO_DIALOG

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, CtrlrCustomComponent *param1, const MouseEvent &param2)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
			luabind::call_function<void>(o->getObject().getObject(), param1, boost::ref(param2));
	}
	CATCH_METHOD_EXCEPTION

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, CtrlrCustomComponent *param1, const MouseEvent &param2, float param3, float param4)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
			luabind::call_function<void>(o->getObject().getObject(), param1, boost::ref(param2), param3, param4);
	}
	CATCH_METHOD_EXCEPTION

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, const int param1, const int param2, const int param3)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
			luabind::call_function<void>(o->getObject().getObject(), param1, param2, param3);
	}
	CATCH_METHOD_EXCEPTION

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, const int param1, const int param2)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
			luabind::call_function<void>(o->getObject().getObject(), param1, param2);
	}
	CATCH_METHOD_EXCEPTION

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, const int param1, const int param2, const int param3, luabind::object const &param4)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
			luabind::call_function<void>(o->getObject().getObject(), param1, param2, param3, param4);
	}
	CATCH_METHOD_EXCEPTION

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, const int param1, const File &param2)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
			luabind::call_function<void>(o->getObject().getObject(), param1, param2);
	}
	CATCH_METHOD_EXCEPTION

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, CtrlrModulator *param1, const File &param2)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
			luabind::call_function<void>(o->getObject().getObject(), param1, param2);
	}
	CATCH_METHOD_EXCEPTION

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, CtrlrWaveform *param1)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
			luabind::call_function<void>(o->getObject().getObject(), param1);
	}
	CATCH_METHOD_EXCEPTION

	return (true);
}



const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, const ValueTree &param1, luabind::object &param2)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
		{
			luabind::call_function<void>(o->getObject().getObject(), param1, param2);
		}
	}
	CATCH_METHOD_EXCEPTION

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, const ValueTree &param1, CtrlrMIDILibraryRequest *param2)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
		{
			luabind::call_function<void>(o->getObject().getObject(), param1, param2);
		}
	}

	CATCH_METHOD_EXCEPTION

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, CtrlrMIDILibraryRequest *param1)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
		{
			luabind::call_function<void>(o->getObject().getObject(), param1);
		}
	}

	CATCH_METHOD_EXCEPTION

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, const String &param1, const CtrlrNotificationType param2)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
		{
			luabind::call_function<void>(o->getObject().getObject(), param1, param2);
		}
	}

	CATCH_METHOD_EXCEPTION

	return (true);
}

int CtrlrLuaMethodManager::callWithRet(CtrlrLuaMethod *o, CtrlrModulator *param1, const int param2)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
		{
			return (luabind::call_function<int>(o->getObject().getObject(), param1, param2));
		}
	}
	CATCH_METHOD_EXCEPTION

	return (param2);
}

int CtrlrLuaMethodManager::callWithRet(CtrlrLuaMethod *o, CtrlrModulator *param1, const CtrlrMidiMessage &param2, const int param3)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
		{
			return (luabind::call_function<int>(o->getObject().getObject(), param1, param2, param3));
		}
	}
	CATCH_METHOD_EXCEPTION

	return (param3);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, const StringArray &param1, const int param2, const int param3)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
		{
			luabind::call_function<void>(o->getObject().getObject(), param1, param2, param3);
		}
	}

	CATCH_METHOD_EXCEPTION

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, const StringArray &param1)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
		{
			luabind::call_function<void>(o->getObject().getObject(), param1);
		}
	}

	CATCH_METHOD_EXCEPTION

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, CtrlrMIDITransaction *midiTransaction)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
		{
			luabind::call_function<void>(o->getObject().getObject(), midiTransaction);
		}
	}

	CATCH_METHOD_EXCEPTION

	return (true);
}

const bool CtrlrLuaMethodManager::call(CtrlrLuaMethod *o, CtrlrMIDITransaction *midiTransaction, MemoryBlock *destinationMemoryBlock)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (true);

	try
	{
		if (o->isValid())
		{
			luabind::call_function<void>(o->getObject().getObject(), midiTransaction, destinationMemoryBlock);
		}
	}

	CATCH_METHOD_EXCEPTION

	return (true);
}

int CtrlrLuaMethodManager::callWithRet(CtrlrLuaMethod *o, CtrlrMIDITransaction *midiTransaction, ValueTree valueTree)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (-2);

	try
	{
		if (o->isValid())
		{
			return (luabind::call_function<int>(o->getObject().getObject(), midiTransaction, valueTree));
		}
	}
	CATCH_METHOD_EXCEPTION

	return (-1);
}

int CtrlrLuaMethodManager::callWithRet(CtrlrLuaMethod *o, ValueTree valueTree1, ValueTree valueTree2)
{
	const ScopedLock sl(methodManagerCriticalSection);

	LUA_DEBUG

	if (isLuaDisabled())
		return (-2);

	try
	{
		if (o->isValid())
		{
			return (luabind::call_function<int>(o->getObject().getObject(), valueTree1, valueTree2));
		}
	}
	CATCH_METHOD_EXCEPTION

	return (-1);
}
