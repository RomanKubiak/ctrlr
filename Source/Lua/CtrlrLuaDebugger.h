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
#include "CtrlrLua/MethodEditor/CtrlrLuaMethodEditor.h"

class CtrlrLuaManager;

class CtrlrLuaDebugger
{
    public:
        CtrlrLuaDebugger(CtrlrLuaManager &_owner);
        ~CtrlrLuaDebugger();
        static void wrapForLua(lua_State *L);
        std::string dbgRead(std::string data);
        std::string dbgRead();
        void dbgWrite(std::string data);
        void setBreakpoint(const int line, const String &fileName, const bool shouldBeSet=true);

        struct PendingBreakpoint
        {
            PendingBreakpoint (int _line, String _fileName, bool _shouldBeSet)
            : line(_line), fileName(_fileName), shouldBeSet(_shouldBeSet) {}
            PendingBreakpoint() {}
            int line;
            String fileName;
            bool shouldBeSet;
        };

        JUCE_LEAK_DETECTOR(CtrlrLuaDebugger)

    private:
        void toggleBreakpoint(luabind::object &breakpoints, luabind::object &methodBreakpoints, int line, const String fileName, bool shouldBeSet);
        CtrlrLuaManager &owner;
        Array <String> commandQueue;
        Array <PendingBreakpoint> pendingBreakpoints;
};

#endif  // CTRLRLUADEBUGGER_H_INCLUDED
