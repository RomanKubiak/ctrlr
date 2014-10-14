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

CtrlrLuaDebugger::CtrlrLuaDebugger(CtrlrLuaManager &_owner) : owner(_owner)
{
    _INF("CtrlrLuaManager::ctor create debugger");

    wrapForLua (owner.getLuaState());

    luabind::globals(owner.getLuaState())["ctrlrDebugger"]            = this;

    String debugLua(String(BinaryData::debugger_lua, BinaryData::debugger_luaSize));
    owner.runCode(debugLua, "debugger.lua");

    ui = new CtrlrLuaDebuggerUI(this);
}

CtrlrLuaDebugger::~CtrlrLuaDebugger()
{
}

void CtrlrLuaDebugger::dbgWrite(String data)
{
    _DBG("CtrlrLuaDebugger::dbgWrite data \""+data.trim()+"\"");
}

std::string CtrlrLuaDebugger::dbgRead(String prompt)
{
    CtrlrDialogWindow::showModalDialog ("Title", ui, false, nullptr);

    return ("");
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
