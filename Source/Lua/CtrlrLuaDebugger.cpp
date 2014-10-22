/*
  ==============================================================================

    CtrlrLuaDebugger.cpp
    Created: 14 Oct 2014 12:59:44pm
    Author:  r.kubiak

  ==============================================================================
*/
#include "stdafx.h"
#include "CtrlrLuaDebugger.h"
#include "CtrlrLuaManager.h"
#include "CtrlrWindowManagers/CtrlrDialogWindow.h"
#include "CtrlrPanel/CtrlrPanel.h"

CtrlrLuaDebugger::CtrlrLuaDebugger(CtrlrLuaManager &_owner) : owner(_owner)
{
    _INF("CtrlrLuaManager::ctor create debugger");

    wrapForLua (owner.getLuaState());

    luabind::globals(owner.getLuaState())["ctrlrDebugger"]            = this;

    // String debugLua(String(BinaryData::debugger_lua, BinaryData::debugger_luaSize));
    // owner.runCode(debugLua, "debugger.lua");
}

CtrlrLuaDebugger::~CtrlrLuaDebugger()
{
}

void CtrlrLuaDebugger::dbgWrite(String data)
{
    owner.getOwner().getWindowManager().show (CtrlrPanelWindowManager::LuaMethodEditor);

    CtrlrLuaMethodEditor *ui = dynamic_cast<CtrlrLuaMethodEditor *>(owner.getOwner().getWindowManager().getContent(CtrlrPanelWindowManager::LuaMethodEditor));

    if (ui)
    {
        return (ui->setRawDebuggerOutput(data));
    }
}

void CtrlrLuaDebugger::dbgWriteJson(String jsonData)
{
    CtrlrLuaMethodEditor *ui = dynamic_cast<CtrlrLuaMethodEditor *>(owner.getOwner().getWindowManager().getContent(CtrlrPanelWindowManager::LuaMethodEditor));

    if (ui)
    {
        return (ui->setJsonDebuggerOutput(jsonData));
    }
}

std::string CtrlrLuaDebugger::dbgRead(String prompt)
{
	if (commandQueue.length() > 0)
	{
		const String sendNow = commandQueue.substring(0,1);
		commandQueue = commandQueue.substring(1);

        _DBG("to debugger->" +sendNow);
		return (sendNow.toStdString());
	}

	owner.getOwner().getWindowManager().show (CtrlrPanelWindowManager::LuaMethodEditor);

    CtrlrLuaMethodEditor *ui = dynamic_cast<CtrlrLuaMethodEditor *>(owner.getOwner().getWindowManager().getContent(CtrlrPanelWindowManager::LuaMethodEditor));
    if (ui)
    {
        if (ui->waitForCommand())
        {
            const String sendNow = ui->getLastDebuggerCommand().substring(0,1);
			commandQueue = ui->getLastDebuggerCommand().substring(1);
			_DBG("to debugger->" + sendNow);
			return (sendNow.toStdString());
        }
        else
        {
            _WRN("CtrlrLuaDebugger::dbgRead debugger UI didn't return any commands, continuing");
            return ("run");
        }
    }

    _WRN("CtrlrLuaDebugger::dbgRead debugger window is invalid, continuing");
    return ("run");
}

std::string CtrlrLuaDebugger::dbgRead()
{
    return (dbgRead (String::empty));
}

void CtrlrLuaDebugger::wrapForLua(lua_State *L)
{
    using namespace luabind;
    module(L)
    [
        class_<CtrlrLuaDebugger>("CtrlrLuaDebugger")
            .def("dbg_write_ctrlr", &CtrlrLuaDebugger::dbgWrite)
            .def("dbg_read_ctrlr", (std::string (CtrlrLuaDebugger::*)(String)) &CtrlrLuaDebugger::dbgRead)
            .def("dbg_read_ctrlr", (std::string (CtrlrLuaDebugger::*)(void)) &CtrlrLuaDebugger::dbgRead)
            .def("dbg_write_ctrlr_json", &CtrlrLuaDebugger::dbgWriteJson)
    ];
}
