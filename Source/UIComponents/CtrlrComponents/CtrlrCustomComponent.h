#ifndef __CTRLR_CUSTOM_COMPONENT__
#define __CTRLR_CUSTOM_COMPONENT__

#include "Methods/CtrlrLuaMethod.h"
#include "CtrlrComponent.h"
#include "CtrlrMacros.h"
#include "CtrlrIDs.h"

class CtrlrCustomComponent :    public CtrlrComponent,
                                public KeyListener,
                                public FileDragAndDropTarget,
                                public TextDragAndDropTarget,
                                public DragAndDropTarget
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
		double getComponentValue();
		int getComponentMidiValue();
		double getComponentMaxValue();
		const String getComponentText();
		void setComponentText (const String &componentText);

		bool isInterestedInDragSource (const SourceDetails& dragSourceDetails);
		bool isInterestedInFileDrag (const StringArray& files);
		bool isInterestedInTextDrag (const String& text);

        void fileDragEnter (const StringArray& files, int x, int y);
        void fileDragMove (const StringArray& files, int x, int y);
        void fileDragExit (const StringArray& files);
        void filesDropped (const StringArray& files, int x, int y);
        void textDragEnter (const String& text, int x, int y);
        void textDragMove (const String& text, int x, int y);
        void textDragExit (const String& text);
        void textDropped (const String& text, int x, int y);
		void itemDragEnter (const SourceDetails &dragSourceDetails);
		void itemDragMove (const SourceDetails &dragSourceDetails);
		void itemDragExit (const SourceDetails &dragSourceDetails);
		void itemDropped (const SourceDetails& dragSourceDetails);
		bool shouldDrawDragImageWhenOver ();
		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
		void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
		void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded);
		void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
		void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
		static void wrapForLua(lua_State *L);
		void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr) {}
		JUCE_LEAK_DETECTOR(CtrlrCustomComponent)

	private:
		WeakReference <CtrlrLuaMethod> setValueCbk, getValueCbk, setTextCbk, getTextCbk,
										keyStateChangedCbk, keyPressedCbk, mouseDoubleClickCbk,
										mouseWheelMoveCbk,paintCbk,paintOverChildrenCbk,resizedCbk,
										mouseEnterCbk,mouseExitCbk,mouseDownCbk,mouseUpCbk,mouseMoveCbk,mouseDragCbk,
										dadStartCbk,dadIsInterestedCbk,dadEnterCbk,dadExitCbk,dadMoveCbk,dadDroppedCbk;
		bool isADragAndDropContainer;
};

#endif
