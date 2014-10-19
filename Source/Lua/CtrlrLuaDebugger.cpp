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

    String debugLua(String(BinaryData::debugger_lua, BinaryData::debugger_luaSize));
    owner.runCode(debugLua, "debugger.lua");
}

CtrlrLuaDebugger::~CtrlrLuaDebugger()
{
}

void CtrlrLuaDebugger::dbgWrite(String data)
{
    owner.getOwner().getWindowManager().show (CtrlrPanelWindowManager::LuaDebugger);

    CtrlrLuaDebuggerUI *ui = dynamic_cast<CtrlrLuaDebuggerUI *>(owner.getOwner().getWindowManager().getContent(CtrlrPanelWindowManager::LuaDebugger));

    if (ui)
    {
        return (ui->setOutputFromDebugger(data));
    }
}

std::string CtrlrLuaDebugger::dbgRead(String prompt)
{
	if (commandQueue.length() > 0)
	{
		const String sendNow = commandQueue.substring(0,1);
		commandQueue = commandQueue.substring(1);

		return (sendNow.toStdString());
	}

    owner.getOwner().getWindowManager().show (CtrlrPanelWindowManager::LuaDebugger);

    CtrlrLuaDebuggerUI *ui = dynamic_cast<CtrlrLuaDebuggerUI *>(owner.getOwner().getWindowManager().getContent(CtrlrPanelWindowManager::LuaDebugger));
    if (ui)
    {
        if (ui->waitForCommand())
        {
			commandQueue = ui->getLastCommand().substring(1);
			return (ui->getLastCommand().substring(0,1).toStdString());
        }
        else
        {
            _WRN("CtrlrLuaDebugger::dbgRead debugger UI didn't return any commands, restarting debugger");
            return ("");
        }
    }

    _WRN("CtrlrLuaDebugger::dbgRead debugger window is invalid, continuing");
    return ("c");
}

void CtrlrLuaDebugger::wrapForLua(lua_State *L)
{
    using namespace luabind;
    module(L)
    [
        class_<CtrlrLuaDebugger>("CtrlrLuaDebugger")
            .def("dbg_write_ctrlr", &CtrlrLuaDebugger::dbgWrite)
            .def("dbg_read_ctrlr", &CtrlrLuaDebugger::dbgRead)
    ];
}
