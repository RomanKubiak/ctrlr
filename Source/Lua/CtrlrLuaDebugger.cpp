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

void CtrlrLuaDebugger::dbgWrite(std::string data)
{
    owner.getOwner().getWindowManager().show (CtrlrPanelWindowManager::LuaMethodEditor);

    CtrlrLuaMethodEditor *ui = dynamic_cast<CtrlrLuaMethodEditor *>(owner.getOwner().getWindowManager().getContent(CtrlrPanelWindowManager::LuaMethodEditor));

    if (ui)
    {
        return (ui->insertRawDebuggerOutput(_STR(data)));
    }
}

void CtrlrLuaDebugger::dbgWriteJson(std::string jsonData)
{
    CtrlrLuaMethodEditor *ui = dynamic_cast<CtrlrLuaMethodEditor *>(owner.getOwner().getWindowManager().getContent(CtrlrPanelWindowManager::LuaMethodEditor));

    if (ui)
    {
        return (ui->setJsonDebuggerOutput(jsonData));
    }
}

std::string CtrlrLuaDebugger::dbgRead(std::string prompt)
{
	if (commandQueue.length() > 0)
	{
		const String sendNow = commandQueue.substring(0,1);
		commandQueue = commandQueue.substring(1);

		return (sendNow.toStdString());
	}

	owner.getOwner().getWindowManager().show (CtrlrPanelWindowManager::LuaMethodEditor);

    CtrlrLuaMethodEditor *ui = dynamic_cast<CtrlrLuaMethodEditor *>(owner.getOwner().getWindowManager().getContent(CtrlrPanelWindowManager::LuaMethodEditor));
    if (ui)
    {
        if (ui->waitForCommand())
        {
            return (ui->getCurrentDebuggerCommand (true).toStdString());
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
    return (dbgRead (std::string()));
}

void CtrlrLuaDebugger::wrapForLua(lua_State *L)
{
    using namespace luabind;
    module(L)
    [
        class_<CtrlrLuaDebugger>("CtrlrLuaDebugger")
            .def("dbg_write_ctrlr", &CtrlrLuaDebugger::dbgWrite)
            .def("dbg_read_ctrlr", (std::string (CtrlrLuaDebugger::*)(std::string)) &CtrlrLuaDebugger::dbgRead)
            .def("dbg_read_ctrlr", (std::string (CtrlrLuaDebugger::*)(void)) &CtrlrLuaDebugger::dbgRead)
            .def("dbg_write_ctrlr_json", &CtrlrLuaDebugger::dbgWriteJson)
    ];
}
