/*
  ==============================================================================

    CtrlrLuaDebugger.h
    Created: 14 Oct 2014 12:59:44pm
    Author:  r.kubiak

  ==============================================================================
*/

#ifndef CTRLRLUADEBUGGER_H_INCLUDED
#define CTRLRLUADEBUGGER_H_INCLUDED

#include "CtrlrMacros.h"
#include "CtrlrLua/CtrlrLuaDebuggerUI.h"

class CtrlrLuaManager;

class CtrlrLuaDebugger
{
    public:
        CtrlrLuaDebugger(CtrlrLuaManager &_owner);
        ~CtrlrLuaDebugger();
        std::string dbgRead(String prompt);
        void dbgWrite(String data);
        void dbgWriteJson(String jsonData);
        static void wrapForLua(lua_State *L);

    private:
        CtrlrLuaManager &owner;
        String commandQueue;
};

#endif  // CTRLRLUADEBUGGER_H_INCLUDED
