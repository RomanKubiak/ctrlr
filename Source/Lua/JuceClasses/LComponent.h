#ifndef __L_COMPONENT__
#define __L_COMPONENT__

#include "CtrlrLuaManager.h"

class LComponent : public Component
{
	public:
		void addToDesktop(const int windowStyleFlags)
		{
			Component::addToDesktop (windowStyleFlags, nullptr);
		}

		static Component *getCurrentlyFocusedComponent()
		{
			return (Component::getCurrentlyFocusedComponent());
		}

		static void beginDragAutoRepeat(int milisecondsBetweenCallbacks)
		{
			Component::beginDragAutoRepeat(milisecondsBetweenCallbacks);
		}

		static bool isMouseButtonDownAnywhere()
		{
			return (Component::isMouseButtonDownAnywhere());
		}

		static int getNumCurrentlyModalComponents()
		{
			return (Component::getNumCurrentlyModalComponents());
		}

		static Component *getCurrentlyModalComponent(int index=0)
		{
			return (Component::getCurrentlyModalComponent(index));
		}

		static void wrapForLua (lua_State *L);
};

#endif