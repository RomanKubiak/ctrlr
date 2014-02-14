#ifndef __CTRLR_PANEL_CANVAS_LAYER__
#define __CTRLR_PANEL_CANVAS_LAYER__

#include "JuceHeader.h"
#include "CtrlrIDs.h"
#include "CtrlrLuaObject.h"

class CtrlrPanelCanvas;

//==============================================================================
/** @brief Class that represents a canvas layer

*/
class CtrlrPanelCanvasLayer : public Component, public CtrlrLuaObject, public ValueTree::Listener
{
	public:
		CtrlrPanelCanvasLayer(CtrlrPanelCanvas &_owner);
		~CtrlrPanelCanvasLayer();
		void paint (Graphics &g);

		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
		void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
		void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
		void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
		void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
		void restoreState (const ValueTree &savedState);
		ValueTree &getObjectTree();
		void setProperty (const Identifier& name, const var &newValue, const bool isUndoable=false);
		const var &getProperty (const Identifier& name) const;
		const var getProperty (const Identifier& name, const var &defaultReturnValue) const;
		static void wrapForLua(lua_State *L);
		void moveUp();
		void moveDown();
		void resized();

		JUCE_LEAK_DETECTOR(CtrlrPanelCanvasLayer)

	private:
		ValueTree layerTree;
		CtrlrPanelCanvas &owner;
		bool mousePass;
};

#endif