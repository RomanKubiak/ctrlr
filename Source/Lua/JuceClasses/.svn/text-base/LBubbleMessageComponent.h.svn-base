#ifndef __L_BUBBLE_MESSAGE_COMPONENT__
#define __L_BUBBLE_MESSAGE_COMPONENT__

#include "CtrlrLuaManager.h"

class LBubbleMessageComponent : public BubbleMessageComponent
{
	public:
		LBubbleMessageComponent(int fadeOutLengthMs=150);
		static void wrapForLua (lua_State *L);
		void showAt (Component *component, const String &message, int numMillisecondsBeforeRemoving, bool removeWhenMouseClicked=true, bool deleteSelfAfterUse=false);
		void showAt (Component *component, const AttributedString &message, int numMillisecondsBeforeRemoving, bool removeWhenMouseClicked=true, bool deleteSelfAfterUse=false);
		void showAt (const Rectangle<int> &rectangle, const AttributedString &message, int numMillisecondsBeforeRemoving, bool removeWhenMouseClicked=true, bool deleteSelfAfterUse=false);
		void showAt (const Rectangle<int> &rectangle, const String &message, int numMillisecondsBeforeRemoving, bool removeWhenMouseClicked=true, bool deleteSelfAfterUse=false);
		void getContentSize (int &w, int &h);
};

#endif