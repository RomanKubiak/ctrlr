#ifndef __CTRLR_PANEL_EDITOR__
#define __CTRLR_PANEL_EDITOR__

#pragma warning(disable:4355)

#include "CtrlrComponentSelection.h"
#include "CtrlrPanelCanvas.h"
#include "CtrlrUtilities.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrLuaObject.h"
#include "CtrlrPanelProperties.h"
#include "CtrlrPanelViewport.h"
#include "CtrlrPanel/CtrlrPanelUndoManager.h"
#include "CtrlrPanel/CtrlrPanelMIDIToolbar.h"

class CtrlrPanelEditor;

class CtrlrPanelNotifier : public Component
{
	public:
		CtrlrPanelNotifier(CtrlrPanelEditor &_owner);
		~CtrlrPanelNotifier() {}
		void paint (Graphics &g);
		void resized();
		void setNotification (const String &notification, const CtrlrNotificationType ctrlrNotificationType);
		Colour getBackgroundColourForNotification(const CtrlrNotificationType ctrlrNotificationType);
		void mouseDown (const MouseEvent &e);

		JUCE_LEAK_DETECTOR(CtrlrPanelNotifier)

	private:
		Colour background;
		ScopedPointer <Label> text;
		CtrlrPanelEditor &owner;
};

class CtrlrPanelEditor  :	public Component,
							public ValueTree::Listener,
							public CtrlrLuaObject,
							public ChangeListener
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
		CtrlrPanelViewport *getPanelViewport()															{ return (ctrlrPanelViewport); }
		CtrlrComponent *getSelected(const Identifier &uiType);
		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
		void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
		void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
		void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
		void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}

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
		void paint (Graphics& g);
		void resized();
		void visibilityChanged();
		void notify(const String &notification, CtrlrNotificationCallback *callback, const CtrlrNotificationType ctrlrNotificationType = NotifyInformation);
		void notificationClicked(const MouseEvent e);
		void changeListenerCallback (ChangeBroadcaster *source);
		void toggleMIDIToolbar();
		const bool isMidiToolbarVisible() { return (midiToolbar.isVisible()); }
		void setAllCombosDisabled();
		void setAllCombosEnabled();
		void saveLayout();
		bool getRestoreState()					{ return (currentRestoreState); }
		void setRestoreState(const bool _state) { currentRestoreState = _state; }
		void reloadResources (Array <CtrlrPanelResource*> resourcesThatChanged);


		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrPanelEditor)

	private:
		ScopedPointer <CtrlrPanelNotifier> ctrlrPanelNotifier;
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
		CtrlrPanelMIDIToolbar midiToolbar;
		Component* editorComponentsInEditMode[3];
		Component* editorComponents[2];
};


#endif
