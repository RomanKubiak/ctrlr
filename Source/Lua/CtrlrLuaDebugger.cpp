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

    // Paused at file disableMidi line 7 (1) (breakpoint)

    if (_STR(data).contains ("Paused at"))
    {
        if (_STR(data).contains ("(breakpoint)"))
        {
            /* a breakppoint was hit */
        }
        commandQueue.add ("trace");
        commandQueue.add ("vars");
    }


    if (ui)
    {
        return (ui->insertRawDebuggerOutput(_STR(data)));
    }
}

std::string CtrlrLuaDebugger::dbgRead(std::string prompt)
{
    if (pendingBreakpoints.size() > 0)
    {
        for (int i=0; i<pendingBreakpoints.size(); i++)
        {
            if (pendingBreakpoints[i].shouldBeSet)
            {
                commandQueue.add ("setb " + _STR(pendingBreakpoints[i].line) + " " + pendingBreakpoints[i].fileName);
            }
            else
            {
                commandQueue.add ("delb " + _STR(pendingBreakpoints[i].line) + " " + pendingBreakpoints[i].fileName);
            }
        }

        pendingBreakpoints.clear();
    }

	if (commandQueue.size() > 0)
	{
	    return (commandQueue.remove (commandQueue.size() - 1).toStdString());
	}

	owner.getOwner().getWindowManager().show (CtrlrPanelWindowManager::LuaMethodEditor);

    CtrlrLuaMethodEditor *ui = dynamic_cast<CtrlrLuaMethodEditor *>(owner.getOwner().getWindowManager().getContent(CtrlrPanelWindowManager::LuaMethodEditor));
    if (ui)
    {
        if (ui->waitForCommand())
        {
            commandQueue.add ("trace");
            commandQueue.add ("vars");
            commandQueue.add (ui->getCurrentDebuggerCommand (true).toStdString());
            return (commandQueue.remove (commandQueue.size() - 1).toStdString());
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

void CtrlrLuaDebugger::setBreakpoint(const int line, const String &fileName, const bool shouldBeSet)
{
    pendingBreakpoints.add (PendingBreakpoint(line, fileName, shouldBeSet));
    owner.runCode("pause(\"__breakpoints\")");
}

void CtrlrLuaDebugger::toggleBreakpoint(luabind::object &breakpoints, luabind::object &lineBreakpoints, int line, const String fileName, bool shouldBeSet)
{
}
void CtrlrLuaDebugger::wrapForLua(lua_State *L)
{
    using namespace luabind;
    module(L)
    [
        class_<CtrlrLuaDebugger>("CtrlrLuaDebugger")
            .def("write", &CtrlrLuaDebugger::dbgWrite)
            .def("read", (std::string (CtrlrLuaDebugger::*)(std::string)) &CtrlrLuaDebugger::dbgRead)
            .def("read", (std::string (CtrlrLuaDebugger::*)(void)) &CtrlrLuaDebugger::dbgRead)
    ];
}
