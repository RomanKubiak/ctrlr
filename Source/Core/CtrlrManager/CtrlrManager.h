#pragma once

#include "CtrlrModulator/CtrlrModulator.h"
#include "Native/CtrlrNative.h"
#include "CtrlrApplicationWindow/CtrlrDocumentPanel.h"
#include "CtrlrMIDIDeviceManager.h"
#include "CtrlrSysexProcessorOwned.h"
#include "CtrlrWindowManagers/CtrlrManagerWindowManager.h"
#include "CtrlrManagerVst.h"
#include "CtrlrIDManager.h"
#include "CtrlrFontManager.h"

class CtrlrLuaManager;
class CtrlrPanelCanvas;
class CtrlrPanel;
class CtrlrPanelEditor;
class CtrlrEditor;
class CtrlrLog;
class CtrlrProcessor;
class CtrlrProperties;
class CtrlrDocument;

#define	TIMER_AUTO_SAVE	10

//==============================================================================
/**
    The main class that holds all panels, also connects LUA contexts.

*/
class CtrlrManager :    public ValueTree::Listener,
                        public ChangeBroadcaster,
                        public AsyncUpdater,
                        public ChangeListener,
                        public MultiTimer,
                        public ApplicationCommandManagerListener,
                        public ActionBroadcaster
{
	public:
		//==============================================================================
		/** Create a Manager instance, only one should be created.
		*/
		CtrlrManager(CtrlrProcessor *_owner, CtrlrLog &_ctrlrLog);
		void setDefaults();


		/** Destructor.
		*/
		~CtrlrManager();

		enum CtrlrModulatorMapType
		{
			ModulatorByName,
			ModulatorByMidiControllerNumber,
			ModulatorBySysexFormula
		};

		enum CtrlrManagerState
		{
			Constructor,
			InitGui,
			LoadingPanels,
			PanelsLoaded,
			Exiting,
			MidiChannelChanged,
			ModulatorCreated,
			ModulatorRemoved,
			NewUpdateFound,
			CheckingForUpdates,
			NoNewUpdatesFound
		};

		//==============================================================================
		/** The Manager Listener definition, pure virtual

		*/
		class Listener
		{
			public:
				virtual ~Listener(){}
				/** The listener will be informaed of manager state changes, the new state is passed
					as the first parameter

					@param newState		new Manager state

				*/
				virtual void managerStateChanged (const CtrlrManagerState newState)=0;
		};



		/** Adds a listener for the manager, you will be informed of Manager changes

			@param l					The listener to add
			@see removeListener
		*/
		void addListener (Listener *l)		{ listeners.add(l); }

		/** Remove a listener, remember to do that when you delete your objects

			@param l					The listener to remove
			@see addListener
		*/
		void removeListener (Listener *l)	{ listeners.remove(l); }

		/** Add a modulator to the list, modulators are not owned by the Manager.
			Panels should own modulators, the manager only holds pointers to them
			for easier access.

			@param modulatorToAdd					The modulator to add
			@see removeModulator
		*/
		void addModulator (CtrlrModulator *modulatorToAdd);

		/** Get a reference to all modulators in the Manager

		*/
		const Array <CtrlrModulator*> &getModulators()															{ return (ctrlrModulators); }

		/** Get a reference to all modulators with a specified MIDI type. MIDI type is
			determined based on the CtrlrMidiMessage inside the Modulator

			@param typeToFilter					MIDI type to filter by
			@see getModulatorsByUIType
		*/
		const Array <CtrlrModulator*> getModulatorsByMidiType(const CtrlrMidiMessageType typeToFilter);

		/** Get a reference to all modulators with a specified UI type. UI Type is
			determined based on the CtrlrComponent inside the Modulator

			@param uiType						UI type to filter by
			@see getModulatorsByMidiType
		*/
		const Array <CtrlrModulator*> getModulatorsByUIType(const Identifier &uiType);

		/** Utility method to see if a UI Element is in the Manager

			@param componentToLookFor			The CtrlrComponent to find
			@see getModulatorsByUIType
		*/
		bool containsCtrlrComponent(CtrlrComponent *componentToLookFor);

		/** Get a pointer to a Modulator using it's name.

			@param name							The name of the Modulator
		*/
		CtrlrModulator* getModulator (const String& name) const;

		/** This is called when all panels are finished loading, if you add a Listener
			to the Manager you will be informed about this.

		*/
		void allPanelsInitialized();

		/** Add a new Panel

			@param savedState	if it's available pass in the panels state
			@param showUI		if set to TRUE the UI of this panel will be shown, otherwise the panel will only be created

		*/
		CtrlrPanel *addPanel(const ValueTree &savedState, const bool showUI=true);

		/** Show panel id the DocumentManager (default UI)

			@param panelToAdd	a CtrlrPanelEditor object to show
		*/
		void addPanel (CtrlrPanelEditor *panelToAdd);

		/** Panels should also have unique names, this will generate one for you

			@param proposedName	if the passed in name is valid it will be returned
		*/
		const String getUniquePanelName(const String &proposedName);

		/** Get a pointer to a panel based on it's name

			@param panelName	the name of the panel to return, 0 if not found
		*/

		CtrlrPanel *getPanel(const String &panelName);

		/** Returns a reference to the internal window manager. The window manager keeps track of all non-modal
			windows in Ctrlr

		*/
		CtrlrManagerWindowManager &getWindowManager()															{ return (ctrlrWindowManager); }

		/**
			Checks if there are any unsaved data and if so asks for the user if he wants to save before exiting
		*/
		bool canCloseWindow();

		/** Remove a modulator from the manager


		*/
		void removeModulator (CtrlrModulator *modulatorToDelete);

		/** Restore state


		*/
		void restoreState(const XmlElement &savedState);

		/** Restore state

		*/
		void restoreState (const ValueTree &savedTree);

		/** Returns a reference to the manager tree, the root of all in Ctrlr, be careful

		*/
		ValueTree &getManagerTree()																				{ return (managerTree); }

		/** Return the number of all modulators available

		*/
		int getNumModulators(const bool onlyVstParameters);

		/** Return modulator based on it's vstIndex

		*/
		CtrlrModulator *getModulatorByVstIndex(const int index);

		/** A pointer to the AudioProcessor class

		*/
		CtrlrProcessor *owner;

		/** Returns a reference to the MIDI Device Manager

		*/
		CtrlrMIDIDeviceManager &getCtrlrMIDIDeviceManager()														{ return (ctrlrMidiDeviceManager); }
		CtrlrMIDIDeviceManager &getCtrlrMidiDeviceManager()														{ return (ctrlrMidiDeviceManager); }
		/** Returns the index of the panel that contains this modulator index

			@params modulatorIndex				the vst index of the searched modulator
		*/
		int getPanelForModulator(const int modulatorIndex);
		void applicationCommandInvoked(const ApplicationCommandTarget::InvocationInfo &info);
		void applicationCommandListChanged();
		int getNextVstIndex();
		int getModulatorVstIndexByName(const String &modulatorName);
		CtrlrProperties &getCtrlrProperties();
		ApplicationProperties *getApplicationProperties();
		CtrlrProcessor *getProcessorOwner()																				{ return (owner); }
		CtrlrDocumentPanel &getCtrlrDocumentPanel()																{ return (*ctrlrDocumentPanel); }
		void setProperty (const Identifier& name, const var &newValue)											{ managerTree.setProperty (name, newValue, 0); }
		const var &getProperty (const Identifier& name) const													{ return managerTree.getProperty (name); }
		const var getProperty (const Identifier& name, const var &defaultReturnValue) const						{ return managerTree.getProperty (name, defaultReturnValue); }
		CtrlrLog &getCtrlrLog()																					{ return (ctrlrLog); }
		void removePanel (CtrlrPanelEditor *editor);
		CtrlrPanel *getActivePanel();
		void toggleLayout();
		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &/*treeWhoseChildHasChanged*/){}
		void valueTreeParentChanged (ValueTree &/*treeWhoseParentHasChanged*/){}
		void valueTreeChildAdded (ValueTree& /*parentTree*/, ValueTree& /*childWhichHasBeenAdded*/){}
		void valueTreeChildRemoved (ValueTree& /*parentTree*/, ValueTree& /*childWhichHasBeenRemoved*/, int){}
		void valueTreeChildOrderChanged (ValueTree& /*parentTreeWhoseChildrenHaveMoved*/, int, int){}
		UndoManager* getUndoManager() const;
		void changeListenerCallback (ChangeBroadcaster* source);
		void setEditor (CtrlrEditor *editorToSet);
		CtrlrEditor *getEditor()																				{ return (ctrlrEditor); }
		void restoreEditorState();
		static bool isValidComponentName(const String &name);
		int compareElements (CtrlrModulator *first, CtrlrModulator *second);
		int compareElements (CtrlrPanel *first, CtrlrPanel *second);
		void organizeVstIndexes();
		void organizePanels();
		CtrlrManagerVst &getVstManager();
		void handleAsyncUpdate();
		void doUpdatePositionInfo(const AudioPlayHead::CurrentPositionInfo newTime);
		void updatePositionInfo(const AudioPlayHead::CurrentPositionInfo newTime);
		CtrlrNative &getNativeObject()																			{ return (*ctrlrNativeObject); }
		void openPanelFromFile(Component *componentToAttachMenu);
		CtrlrPanel *getPanelByUid(const String &uid);
		CtrlrPanel *getPanel(const int panelIndex);
		int getNumPanels();
		AudioFormatManager &getAudioFormatManager()																{ return (audioFormatManager); }
		AudioThumbnailCache &getAudioThumbnailCache()															{ return (audioThumbnailCache); }
		bool isRestoring()																				{ return (ctrlrManagerRestoring); }
		void saveStateToDisk();
        void sendActionMessageToWindow(const String &actionMessage);
		void timerCallback (int timerId);
		CtrlrIDManager &getIDManager()																			{ return (ctrlrIDManager); }
		const File getCtrlrPropertiesDirectory();
		CtrlrFontManager &getFontManager()																		{ return (*ctrlrFontManager); }
		ApplicationCommandManager &getCommandManager()															{ return (commandManager); }
		void panelFileOpened(const File &panelFile);
		CtrlrModulator *getInvalidModulator()																	{ return (nullModulator); }  
		
		/** Instance handlers **/
		const String getInstanceName() const;
        const String getInstanceNameForHost() const;
		CtrlrInstance getInstanceMode() const;
		const bool isSingleInstance() const;
		XmlElement *saveState();
		Result importInstanceResources(CtrlrNative *native);
		ValueTree &getInstanceTree();
		ValueTree &getInstanceResourcesTree();
		void openPanelInternal(const File &fileToOpen);
		Result initEmbeddedInstance();
		void setManagerReady();
		CtrlrPanel *nullPanel;
		CtrlrModulator *nullModulator;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrManager);

	private:

		void setEmbeddedDefaults();
		Result addInstancePanel();
		void restoreInstanceState(const ValueTree &instanceState);

		void openPanelInternal(const ValueTree &panelTree);
		ApplicationCommandManager commandManager;
		bool ctrlrManagerRestoring;
		CtrlrInstance ctrlrPlayerInstanceMode;
		AudioPlayHead::CurrentPositionInfo currentPositionInfo;
		OwnedArray <CtrlrPanel> ctrlrPanels;
		Array <CtrlrModulator*> ctrlrModulators;
		ListenerList <Listener> listeners;
		std::unique_ptr <CtrlrDocumentPanel> ctrlrDocumentPanel;
		CtrlrManagerWindowManager ctrlrWindowManager;
		ValueTree managerTree;
		CtrlrMIDIDeviceManager ctrlrMidiDeviceManager;
		WeakReference <CtrlrEditor> ctrlrEditor;
		CtrlrLog &ctrlrLog;
		std::unique_ptr <CtrlrProperties> ctrlrProperties;
		std::unique_ptr <CtrlrManagerVst> ctrlrManagerVst;
		std::unique_ptr <CtrlrNative> ctrlrNativeObject;
		AudioFormatManager audioFormatManager;
		AudioThumbnailCache audioThumbnailCache;
		CtrlrIDManager ctrlrIDManager;
		std::unique_ptr <CtrlrFontManager> ctrlrFontManager;
		ValueTree ctrlrPlayerInstanceTree;
		ValueTree ctrlrPlayerInstanceResources;
		CtrlrModulator *invalidModulator;
		WeakReference <CtrlrLuaMethod> luaCtrlrSaveState, luaCtrlrRestoreState;
};
