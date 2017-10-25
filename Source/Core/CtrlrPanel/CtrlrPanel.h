#ifndef CTRLR_PANEL
#define CTRLR_PANEL

#include "CtrlrMacros.h"
#include "CtrlrMIDIDeviceManager.h"
#include "CtrlrMIDIDevice.h"
#include "CtrlrUtilities.h"
#include "CtrlrMidiInputComparator.h"
#include "CtrlrWindowManagers/CtrlrPanelWindowManager.h"
#include "CtrlrLuaObject.h"
#include "Methods/CtrlrLuaMethod.h"
#include "CtrlrPanelMIDIInputThread.h"
#include "CtrlrPanelProcessor.h"
#include "CtrlrPanelMIDISnapshot.h"
#include "CtrlrApplicationWindow/CtrlrEditor.h"
#include "CtrlrEvaluationScopes.h"
#include "CtrlrPanelResourceManager.h"
#include "CtrlrPanelUndoManager.h"
#include "CtrlrPanelSchemeMigration.h"

typedef WeakReference <CtrlrModulator>					ModulatorReference;
typedef WeakReference <CtrlrComponent>					ComponentReference;
typedef std::multimap<int,ComponentReference>::iterator	RadioIterator;
typedef std::pair<int,ComponentReference>				RadioPair;

class CtrlrWaveform;
class CtrlrLCDLabel;
class CtrlrLabel;
class CtrlrLuaManager;
class CtrlrPanelEditor;
class CtrlrMidiProgramEditor;
class CtrlrPanelCanvas;
class CtrlrToggleButton;
class CtrlrImageButton;
class CtrlrButton;
class CtrlrCombo;
class CtrlrListBox;
class CtrlrFileListBox;
class CtrlrPanelCapabilities;
class CtrlrSlider;
class CtrlrFixedImageSlider;
class CtrlrImageSlider;
class CtrlrFixedSlider;

//==============================================================================
/** @brief Class that represents a Ctrlr Panel

*/
class CtrlrPanel:	public ValueTree::Listener,
					public ChangeListener,
					public CtrlrLuaObject,
					public AsyncUpdater,
					public CtrlrMidiMessageOwner
{
	public:
		/** @brief When saving a panel this tells the LUA callback what sort of format is beeing saved

		*/
		enum CtrlrPanelFileType
		{
			PanelFileXML,						/**< A plain XML file */
			PanelFileXMLCompressed,				/**< A compressed XML file */
			PanelFileBinary,					/**< A binary file (unreadable but loads faster) */
			PanelFileBinaryCompressed,			/**< A binary file with compression */
			PanelFileExport						/**< Used for exports, it's a binary compressed file with resources included */
		};

		CtrlrPanel(CtrlrManager &_owner);
		CtrlrPanel(CtrlrManager &_owner, const String &panelName, const int idx);
		~CtrlrPanel();
		Result restoreState (const ValueTree &savedState);
		CtrlrPanelEditor *getEditor(const bool createNewEditorIfNeeded=true);
		CtrlrPanelCanvas *getCanvas();
		CtrlrModulator *createNewModulator(const Identifier &guiType);
		void addModulator (CtrlrModulator *modulatorToAdd);
		int getModulatorIndex (const CtrlrModulator *const modulatorToFind) const;
		int getModulatorIndex (const String &modulatorToFind) const;
		void removeModulator (CtrlrModulator *modulatorToDelete);
		bool containsCtrlrComponent(const CtrlrComponent *const componentToLookFor) const;

		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &/*treeWhoseChildHasChanged*/){}
		void valueTreeParentChanged (ValueTree &/*treeWhoseParentHasChanged*/){}
		void valueTreeChildAdded (ValueTree& /*parentTree*/, ValueTree& /*childWhichHasBeenAdded*/){}
		void valueTreeChildRemoved (ValueTree& /*parentTree*/, ValueTree& /*childWhichHasBeenRemoved*/, int){}
		void valueTreeChildOrderChanged (ValueTree& /*parentTreeWhoseChildrenHaveMoved*/, int, int){}

		const String getUniqueModulatorName(const String &proposedName);
		const Array <CtrlrModulator*> getModulatorsByUIType(const Identifier &typeToFilter);
		const Array <CtrlrModulator*> getModulatorsByMidiType(const CtrlrMidiMessageType typeToFilter);
		const Array <CtrlrModulator*> getModulatorsWithProperty(const Identifier &propertyName, const var &propertyValue);

		CtrlrModulator *getModulatorWithProperty (const String &propertyName="", const String &propertyValue="");
		CtrlrModulator *getModulatorWithProperty (const String &propertyName="", const int propertyValue=0);

		luabind::object getModulatorsWildcardLua (const String &wildcardMatch="", const bool ignoreCase=true);
		luabind::object getModulatorsWildcardLua (const String &wildcardMatch, const String &propertyToMatch, const bool ignoreCase);
		luabind::object getModulatorsWithPropertyLua (const String &propertyName, const String &propertyValue);

		CtrlrWaveform *getWaveformComponent(const String &componentName);
		CtrlrLabel *getLabelComponent(const String &componentName);
		CtrlrLCDLabel *getLCDLabelComponent(const String &componentName);
		CtrlrToggleButton *getToggleButtonComponent (const String &componentName);
		CtrlrImageButton *getImageButtonComponent (const String &componentName);
		CtrlrButton *getButtonComponent (const String &componentName);
		CtrlrCombo *getComboComponent (const String &componentName);
		CtrlrListBox *getListBoxComponent (const String &componentName);
		CtrlrFileListBox *getFileListBoxComponent (const String &componentName);
		CtrlrSlider *getSliderComponent (const String &componentName);
		CtrlrFixedImageSlider *getFixedImageSliderComponent (const String &componentName);
		CtrlrFixedSlider *getFixedSliderComponent (const String &componentName);
		CtrlrImageSlider *getImageSliderComponent (const String &componentName);

		void changeListenerCallback (ChangeBroadcaster* source);
		void editorDeleted();

		void sendMidi (const MidiBuffer &buffer, double millisecondCounterToStartAt=0);
		void sendMidi (const MidiMessage &message, double millisecondCounterToStartAt=0);
		void sendMidi (CtrlrMidiMessage &m, double millisecondCounterToStartAt=0);
		void sendMidiNow (CtrlrMidiMessage &midiMessage);
		bool isMidiOutPaused();
		bool isMidiInPaused();

		void queueMessageForHostOutput(const CtrlrMidiMessage &m);
		void queueMessageForHostOutput(const MidiMessage &message);
		void queueMessagesForHostOutput(const MidiBuffer &messages);

		void setMidiChannelToAllModulators (const int newChannel);
		void setGlobalVariable(const int index, const int value);

		int getGlobalVariable (const int index);
		int getPanelIndex();
		ValueTree getProgram(ValueTree treeToWriteTo=ValueTree::invalid);
		ValueTree getProgramVar(ValueTree programTree=ValueTree::invalid);
		void setProgram(ValueTree programTree, const bool sendSnapshotNow=false);
		ValueTree getCustomData();
		void setCustomData (const ValueTree &customData);
		void generateCustomData();
		int getCurrentProgramNumber();
		int getCurrentBankNumber();
		Result savePanel();
		Result saveLuaCode(const File &panelDir, CtrlrPanel *panel);
		String getPanelContentDirPath();
		String getPanelLuaDirPath();
		String getPanelResourcesDirPath();
		File getPanelContentDir();
		File getPanelLuaDir();
		File getPanelResourcesDir();
		Result convertLuaMethodsToFiles(const String dirPath);
		File getLuaMethodGroupDir(const ValueTree &methodGroup);

		const File savePanelAs(const CommandID saveOption);
		void savePanelVersioned();
		Result savePanelXml(const File &fileToSave, CtrlrPanel *panel, const bool compressPanel=false);
		Result savePanelBin(const File &fileToSave, CtrlrPanel *panel, const bool compressPanel=false);

		void setSavePoint();
		bool hasChangedSinceSavePoint();
		bool isPanelDirty();
		void setPanelDirty(const bool dirty);
		void actionPerformed();
		void actionUndone();
		bool canClose(const bool closePanel);
		const String getPanelWindowTitle();
		void updatePanelWindowTitle();
		void luaManagerChanged();
		void panelResourcesChanged();

		static const String exportPanel(CtrlrPanel *panel, const File &lastBrowsedDir, const File &destinationFile=File::nonexistent, MemoryBlock *outputPanelData=nullptr, MemoryBlock *outputResourcesData=nullptr, const bool isRestricted=false);
		static bool isPanelFile(const File &fileToCheck, const bool beThorough=false);
		static const ValueTree openPanel(const File &panelFile);
		static const ValueTree openXmlPanel(const File &panelFile);
		static const ValueTree openBinPanel(const File &panelFile);
		static const ValueTree openBinPanel(const MemoryBlock &panelData, const bool isCompressed=false);
		static const File askForPanelFileToSave (CtrlrPanel *panel,
													const File &lastBrowsedDir,
													const bool isXml=true,
													const bool isCompressed=false);

		void luaSavePanel(const CtrlrPanelFileType fileType, const File &file);
		void setInstanceProperties(const ValueTree &instanceState);
		ValueTree getCleanPanelTree();

		static void writePanelXml(OutputStream &outputStream, CtrlrPanel *panel, const bool compressPanel);
		Result writeLuaMethod(const File &parentDir, ValueTree *method);
		Result writeLuaMethodGroup(const File &parentDir, ValueTree *methodGroup);
		Result writeLuaChildren(const File &parentDir, ValueTree *parentElement);
		File getLuaMethodSourceFile(const ValueTree *method);
		static void convertLuaMethodsToPropeties(const File &panelLuaDir, ValueTree &panelTree);
		static void convertLuaMethodToProperty(const File &panelLuaDir, ValueTree *method);
		static void convertLuaChildrenToProperties(const File &panelLuaDir, ValueTree *parentElement);


		const String getVersionString(const bool includeVersionName=true, const bool includeTime=true, const String versionSeparator=String::empty);
		void editModeChanged(const bool isInEditMode);
		bool getEditMode();
		const File getPanelDirectory();
		CtrlrPanelResourceManager &getResourceManager();
		CtrlrPanelWindowManager &getWindowManager();

		class Listener
		{
			public:
				virtual ~Listener(){}
				virtual void modulatorChanged (CtrlrModulator *) {}
				virtual void modulatorAdded (CtrlrModulator *) {}
				virtual void modulatorRemoved (CtrlrModulator *) {}
				virtual void panelChanged(CtrlrPanel *) {}
				virtual void midiReceived(MidiMessage &, CtrlrMIDIDeviceType source = inputDevice) {}
		};

		void setRadioGroupId(CtrlrComponent *componentMember, const int groupId);
		bool componentIsInRadioGroup(CtrlrComponent *component);
		bool checkRadioGroup(CtrlrComponent *c, const bool componentToggleState);
		CtrlrModulator* getModulatorByIndex (const int index);
		CtrlrModulator* getModulatorByVstIndex (const int vstIndex);
		CtrlrModulator* getModulatorByCustomIndex (const int customIndex);
		CtrlrModulator* getModulator (const String& name) const;
		int getNumModulators();
		void bootstrapPanel(const bool setInitialProgram=true);
		int cleanBogusProperties();
		int cleanBogusPropertiesFromChild(ValueTree &treeToClean);
		void sync();
		CtrlrComponent *getComponent(const String &modulatorName);
		void panelReceivedMidi(const MidiBuffer &buffer, const CtrlrMIDIDeviceType source = inputDevice);
		void handleAsyncUpdate();
		void sendSnapshotOnLoad();
		bool getRestoreState();
		bool getProgramState();
		bool getBootstrapState();
		void setRestoreState(const bool _restoreState);
		void setProgramState(const bool _programState);
		const String getName();
		void resourceImportFinished();
		void sendSnapshot();
		void modulatorValueChanged(CtrlrModulator *m);
		bool getMidiOptionBool(const CtrlrPanelMidiOption optionToCheck);
		uint8 getMidiChannel(const CtrlrPanelMidiChannel channelToGet);
		void setMidiOptionBool(const CtrlrPanelMidiOption optionToSet, const bool isSet);
		void setMidiChannel(const CtrlrPanelMidiChannel optionToSet, const uint8 value);
		CtrlrPanelMidiOption midiOptionFromString(const Identifier &i);
		CtrlrPanelMidiChannel midiChannelFromString(const Identifier &i);
		void dumpComparatorTables();
		void setLuaDebug (const bool _debug);
		void initEmbeddedInstance();
		void setInitialProgramValue (const String &modulatorName, const var &value);
		void addPanelResource (const int hashCode);
		void removePanelResource (const int hashCode);
		bool isPanelResource (const int hashCode);

		static const Identifier getMidiOptionIdentifier(const CtrlrPanelMidiOption option);
		LMemoryBlock getModulatorValuesAsData(const String &propertyToIndexBy,
                                                const CtrlrByteEncoding byteEncoding,
                                                const int bytesPerValue,
                                                const bool useMappedValues);

		LMemoryBlock getModulatorValuesAsData(const ValueTree &programTree,
                                                const String &propertyToIndexBy,
                                                const CtrlrByteEncoding byteEncoding,
                                                const int bytesPerValue,
                                                const bool useMappedValues);

		LMemoryBlock getModulatorValuesAsData(const String &propertyToIndexBy,
                                                const CtrlrByteEncoding byteEncoding,
                                                const int propertyValueStart,
                                                const int howMany,
                                                const int bytesPerValue,
                                                const bool useMappedValues);

		void setModulatorValuesFromData (const MemoryBlock &dataSource, const String &propertyToIndexBy, const CtrlrByteEncoding byteEncoding, int propertyOffset, int bytesPerValue, const bool useMappedValues);
		ValueTree createProgramFromData(const MemoryBlock &dataSource, const String &propertyToIndexBy, const CtrlrByteEncoding byteEncoding, int propertyOffset, int bytesPerValue, const bool useMappedValues);

		void modulatorNameChanged(CtrlrModulator *modulatorThatChanged, const String &newName);
		void hashName(CtrlrModulator *modulator);
		void setProperty (const Identifier& name, const var &newValue, const bool isUndoable=true);
		const var &getProperty (const Identifier& name) const											{ return panelTree.getProperty (name); }
		const var getProperty (const Identifier& name, const var &defaultReturnValue) const				{ return panelTree.getProperty (name, defaultReturnValue); }
		ValueTree &getPanelTree()																		{ return (panelTree); }
		const ValueTree getPanelTreeCopy()																{ return (panelTree); }
		CtrlrPanelEditor *getPanelEditor()																{ return (getEditor(true)); }
		CtrlrManager &getCtrlrManagerOwner()																	{ return (owner); }
		CtrlrManager &getOwner()																		{ return (owner); }
		OwnedArray<CtrlrModulator,CriticalSection> &getModulators()										{ return (ctrlrModulators); }
		CtrlrLuaManager &getCtrlrLuaManager()															{ return (*ctrlrLuaManager); }
		CtrlrPanelWindowManager &getPanelWindowManager()												{ return (panelWindowManager); }
		CtrlrMidiInputComparator &getInputComparator()													{ return (midiInputThread.getInputComparator()); }
		CtrlrPanelMIDIInputThread &getMIDIInputThread()													{ return (midiInputThread); }
		CtrlrPanelMIDIInputThread &getMIDIInputControllerThread()										{ return (midiControllerInputThread); }
		void addPanelListener (CtrlrPanel::Listener *l)													{ listeners.add(l); }
		void removePanelListener (CtrlrPanel::Listener *l)												{ listeners.remove(l); }
		CtrlrSysexProcessor &getSysExProcessor()														{ return (ctrlrSysexProcessor); }
		ValueTree &getObjectTree()																		{ return (panelTree); }
		CtrlrPanelProcessor &getProcessor()																{ return (processor); }
		CtrlrPanelMIDISnapshot &getSnapshot()															{ return (snapshot); }
		CtrlrPanelEvaluationScope &getPanelEvaluationScope() 											{ return (panelEvaluationScope); }
		CtrlrGlobalEvaluationScope &getGlobalEvaluationScope() 											{ return (globalEvaluationScope); }
		const Array<int,CriticalSection> getPanelResources() 											{ return (panelResources); }
		CtrlrPanelUndoManager *getPanelUndoManager()													{ return (ctrlrPanelUndoManager); }
		CtrlrPanelUndoManager *getUndoManager()															{ return (ctrlrPanelUndoManager); }
		void undo();
		void redo();
		void sendMidiProgramChange();
		bool isSchemeAtLeast(const int minimumLevel);
		void notify (const String &notification, CtrlrNotificationCallback *callback=nullptr, const CtrlrNotificationType ctrlrNotificationType = NotifyInformation);
		bool getDialogStatus();
		void upgradeScheme();
        void addMIDIControllerListener(CtrlrMIDIDevice::Listener *listenerToAdd);
        void removeMIDIControllerListener(CtrlrMIDIDevice::Listener *listenerToRemove);
		void dumpDebugData();
		void performInternalComponentFunction(CtrlrComponent *sourceComponent);
		void multiMidiReceived(CtrlrMidiMessage &multiMidiMessage);
		String getInternalFunctionsProperty(CtrlrComponent *component);

		static const String globalsToString(const Array<int,CriticalSection> &arrayOfGlobals);
		static const Array<int,CriticalSection> globalsFromString(const String &globalsString);
		static void wrapForLua (lua_State *L);

		/* Instance information methods */
		const String getPanelInstanceID();
		const String getPanelInstanceManufacturerID();
		const String getPanelInstanceVersionString();
		int getPanelInstanceVersionInt();
        const String getPanelInstanceName();
        const String getPanelInstanceManufacturer();


		WeakReference<CtrlrPanel>::Master masterReference;
		friend class WeakReference<CtrlrPanel>;

		int getMidiChannelForOwnedMidiMessages();
		CtrlrSysexProcessor *getSysexProcessor();
		Array<int,CriticalSection> &getGlobalVariables();

		Atomic<uint32> midiOptions;
		Atomic<uint32> deviceInputChannel,
					deviceOutputChannel,
					hostInputChannel,
					hostOutputChannel,
					controllerInputChannel;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrPanel)

	private:
		ValueTree initialProgram, panelTree;
		ReadWriteLock panelLock;
		CtrlrLuaManager *ctrlrLuaManager;
		double globalMidiDelay;
		bool restoreStateStatus, boostrapStateStatus, programState, editMode;
		ListenerList <CtrlrPanel::Listener> listeners;
		WeakReference<CtrlrPanelEditor> ctrlrPanelEditor;
		CtrlrManager &owner;
		OwnedArray <CtrlrModulator,CriticalSection> ctrlrModulators;
		Array <ComponentReference> radioGrouppedComponent;
		Array <int,CriticalSection> globalVariables;
		WeakReference <CtrlrLuaMethod>
			luaPanelMidiReceivedCbk,
			luaPanelMidiMultiReceivedCbk,
			luaPanelLoadedCbk,
			luaPanelBeforeLoadCbk,
			luaPanelSavedCbk,
			luaPanelProgramChangedCbk,
			luaPanelGlobalChangedCbk,
			luaPanelMessageHandlerCbk,
			luaPanelMidiChannelChangedCbk,
			luaPanelResourcesLoadedCbk,
			luaPanelModulatorValueChangedCbk,
			luaPanelSaveStateCbk,
			luaPanelRestoreStateCbk;
		CtrlrPanelWindowManager panelWindowManager;
		CtrlrSysexProcessorOwned ctrlrSysexProcessor;
		CtrlrPanelMIDIInputThread midiInputThread;
		CtrlrPanelMIDIInputThread midiControllerInputThread;
		MidiMessageCollector midiMessageCollector;
		CtrlrPanelProcessor processor;
		CtrlrPanelMIDISnapshot snapshot;
		CtrlrMIDIDevice *outputDevicePtr;
		ScopedPointer <CtrlrPanelUndoManager> ctrlrPanelUndoManager;
		CtrlrPanelEvaluationScope panelEvaluationScope;
		CtrlrGlobalEvaluationScope globalEvaluationScope;
		Array <int,CriticalSection> panelResources;
		CtrlrPanelResourceManager resourceManager;
		HashMap<String,CtrlrModulator*> modulatorsByName;
		Array<CtrlrMidiMessage,CriticalSection,4> multiMidiQueue;
		Array<MemoryBlock,CriticalSection> partialMidiQueue;
		int currentActionIndex, indexOfSavedState;
};

#endif
