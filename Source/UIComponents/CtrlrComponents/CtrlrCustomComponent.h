#ifndef __CTRLR_CUSTOM_COMPONENT__
#define __CTRLR_CUSTOM_COMPONENT__

#include "Methods/CtrlrLuaMethod.h"
#include "CtrlrComponent.h"
#include "CtrlrMacros.h"
#include "CtrlrIDs.h"

class CtrlrCustomComponent : public CtrlrComponent, public KeyListener
{
	public:
		CtrlrCustomComponent (CtrlrModulator &_owner);
		~CtrlrCustomComponent();
		bool keyPressed (const KeyPress &key, Component *originatingComponent);
		bool keyStateChanged (bool isKeyDown, Component *originatingComponent);
		void paint (Graphics &g);
		
		void paintOverChildren(Graphics &g);
		void resized();
		void mouseDown (const MouseEvent &e);
		void mouseUp (const MouseEvent &e);
		void mouseDrag (const MouseEvent &e);
		void mouseEnter (const MouseEvent &e);
		void mouseExit (const MouseEvent &e);
		void mouseMove (const MouseEvent &e);
		void mouseDoubleClick (const MouseEvent &e);
		void mouseWheelMove (const MouseEvent &e, const MouseWheelDetails& wheel);

		void restoreState (const ValueTree &savedState);

		void setComponentValue (const double newValue, const bool sendChangeMessage=false);
		const double getComponentValue();
		const int getComponentMidiValue();
		const double getComponentMaxValue();
		const String getComponentText();
		void setComponentText (const String &componentText);

		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
		void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
		void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded);
		void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
		void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
		static void wrapForLua(lua_State *L);

		JUCE_LEAK_DETECTOR(CtrlrCustomComponent)

	private:
		WeakReference <CtrlrLuaMethod> mouseDoubleClickCbk,mouseWheelMoveCbk,paintCbk,paintOverChildrenCbk,resizedCbk,mouseEnterCbk,mouseExitCbk,mouseDownCbk,mouseUpCbk,mouseMoveCbk,mouseDragCbk;
};

#endif