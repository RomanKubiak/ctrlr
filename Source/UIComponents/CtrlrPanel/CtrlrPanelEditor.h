#pragma once

#ifdef _WIN32
#pragma warning(disable:4355)
#endif // _WIN32

#include "CtrlrComponentSelection.h"
#include "CtrlrPanelCanvas.h"
#include "CtrlrUtilities.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrLuaObject.h"
#include "CtrlrPanelProperties.h"
#include "CtrlrPanelViewport.h"
#include "CtrlrPanel/CtrlrPanelUndoManager.h"
#include "CtrlrPanelFindProperty.h"

class CtrlrPanelEditor;

class CtrlrPanelEditor  :	public Component,
							public ValueTree::Listener,
							public CtrlrLuaObject
{
	public:
		CtrlrPanelEditor (CtrlrPanel &_owner, CtrlrManager &_ctrlrManager, const String &panelName);
		~CtrlrPanelEditor();
		enum BackgroundImageLayout
		{
			Stretched,
			Center,
			Tile
		};
		void restoreState(const ValueTree &savedSate);
		void setBackgroundImage (const File &imageFile);
		CtrlrPanelCanvas *getCanvas();
        CtrlrComponentSelection *getSelection();
		void editModeChanged();
		CtrlrPanelProperties *getPanelProperties() { return (ctrlrPanelProperties); }
		CtrlrPanelViewport *getPanelViewport()															{ return (ctrlrPanelViewport); }
		CtrlrComponent *getSelected(const Identifier &uiType);
		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
		void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
		void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
		void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int){}
		void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}

		CtrlrPanel &getOwner()																			{ return (owner); }
		void setProperty (const Identifier& name, const var &newValue, const bool isUndoable=false);
		const var &getProperty (const Identifier& name) const;
		const var getProperty (const Identifier& name, const var &defaultReturnValue) const;
		ValueTree &getPanelEditorTree()																	{ return (panelEditorTree); }

		void layoutItems();
		CtrlrPanelProperties *getPropertiesPanel()														{ return (ctrlrPanelProperties); }
		const bool getMode();
		AffineTransform moveSelectionToPosition(const int newX, const int newY);
		static void wrapForLua (lua_State *L);
		ValueTree &getObjectTree()																		{ return (panelEditorTree); }
		void initSingleInstance();
		void resized();
		void visibilityChanged();
		void setAllCombosDisabled();
		void setAllCombosEnabled();
		void saveLayout();
		bool getRestoreState()					{ return (currentRestoreState); }
		void setRestoreState(const bool _state) { currentRestoreState = _state; }
		void reloadResources (Array <CtrlrPanelResource*> resourcesThatChanged);
        void showComponentRuntimeConfig(CtrlrComponent *componentToConfigure);
		void searchForProperty();
        static LookAndFeel* getLookAndFeelFromDescription(const String &lookAndFeelDesc);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrPanelEditor)

	private:
		ComponentAnimator componentAnimator;
		CtrlrPanel &owner;
		ScopedPointer <CtrlrComponentSelection> ctrlrComponentSelection;
		StretchableLayoutManager layoutManager;
		bool lastEditMode, currentRestoreState;
		CtrlrManager &ctrlrManager;
		ValueTree panelEditorTree;
		friend class WeakReference<CtrlrPanelEditor>;
		WeakReference<CtrlrPanelEditor>::Master masterReference;
		CtrlrPanelProperties* ctrlrPanelProperties;
		StretchableLayoutResizerBar* spacerComponent;
		CtrlrPanelViewport* ctrlrPanelViewport;
		WeakReference<CtrlrNotificationCallback> notificationCallback;
		Component* editorComponentsInEditMode[3];
		Component* editorComponents[2];
		std::unique_ptr<LookAndFeel> lookAndFeel;
};
