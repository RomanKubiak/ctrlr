#ifndef CTRLR_MIDI_LIBRARY
#define CTRLR_MIDI_LIBRARY

#include "CtrlrMIDIDevice.h"
#include "CtrlrOwnedMidiMessage.h"

class CtrlrPanel;
class CtrlrMIDIProgramManager;

#define MENU_TRANSACTIONS_START	1024

class CtrlrMIDILibrary : public ValueTree::Listener,
						public CtrlrLuaObject,
						public ChangeBroadcaster,
						public MultiTimer,
						public AsyncUpdater,
						public ChangeListener
{
	public:
		enum Item
		{
			Library		= 0x1001,
			Program		= 0x1002,
			Bank		= 0x1003,
			Folder		= 0x1004,
			Firmware	= 0x1005,
			Identity	= 0x1006,
			Waveform	= 0x1007,
			Data		= 0x1008,
			Unknown		= 0x100a
		};

		enum MidiProgramChangeControl
		{
			DontSendProgramChange,
			SendProgramChange,
			InheritFromLibrary
		};

		class Listener
		{
			public:
				virtual void programListChanged()	{}
		};

		CtrlrMIDILibrary(CtrlrPanel &_owner);
		~CtrlrMIDILibrary();

		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildAdded (ValueTree& /*parentTree*/, ValueTree& /*childWhichHasBeenAdded*/){}
		void valueTreeChildRemoved (ValueTree& /*parentTree*/, ValueTree& /*childWhichHasBeenRemoved*/, int){}
		void valueTreeChildrenChanged (ValueTree &/*treeWhoseChildHasChanged*/, int, int){}
		void valueTreeParentChanged (ValueTree &/*treeWhoseParentHasChanged*/){}
		void valueTreeChildOrderChanged (ValueTree& /*parentTreeWhoseChildrenHaveMoved*/, int, int){}
		void setProperty (const Identifier& name, const var &newValue, const bool isUndoable=false)		{ libraryTree.setProperty (name, newValue, 0); }
		const var &getProperty (const Identifier& name) const											{ return libraryTree.getProperty (name); }
		const var getProperty (const Identifier& name, const var &defaultReturnValue) const				{ return libraryTree.getProperty (name, defaultReturnValue); }
		UndoManager* getUndoManager() const;
		ValueTree &getObjectTree()																		{ return (libraryTree); }
		void restoreState (const ValueTree &savedState);

		void timerCallback(int timerId);
		void handleAsyncUpdate();
		void changeListenerCallback(ChangeBroadcaster *changeSource);

		int getNumBanks();
		int getNumPrograms(const Uuid &bankUuid);

		const String getProgramName(const Uuid &bankUuid, const Uuid &programUuid);
		const String getBankName(const Uuid &bankUuid);
		const String getCurrentBankName();
		const String getBankDescription(const Uuid &bankUuid);
		const String getProgramDescription(const Uuid &bankUuid, const Uuid &programUuid);
		const Uuid getCurrentProgramUuid();
		const Uuid getCurrentBankUuid();

		ValueTree &getRoot();
		ValueTree &getSnapshots();
		ValueTree &getFirmware();
		ValueTree &getCurrentBank();
		ValueTree &getTransactions();

		ValueTree getCurrentSnapshot();
		ValueTree getCurrentProgram();
		ValueTree getSnapshot(const Uuid &snapshotUuid);
		ValueTree getEditBuffer();
		ValueTree getProgram(const Uuid &bankUuid, const Uuid &programUuid);
		ValueTree getBank(const Uuid &bankUuid);

		void deleteCurrentProgram();
		void deleteCurrentBank();
		void deleteCurrentSnapshot();
		void setCurrentBank(ValueTree bank);
		void setCurrentBankFromMenu(const int menuItemId);
		void setCurrentBank(const Uuid &uuid);

		void setCurrentSnapshot(const Uuid &uuid, const MidiProgramChangeControl midiProgramChangeControl);
		void setCurrentSnapshotFromMenu(const int menuItemId);
		void setCurrentSnapshot(ValueTree snapshotTree, const MidiProgramChangeControl midiProgramChangeControl=InheritFromLibrary);

		void setCurrentProgram(const Uuid &uuid, const MidiProgramChangeControl midiProgramChangeControl, const bool changePanelState=true, const bool setAsCurrentProgram=true);
		void setCurrentProgram(ValueTree program, const MidiProgramChangeControl midiProgramChangeControl, const bool changePanelState=true, const bool setAsCurrentProgram=true);
		void setCurrentProgramFromMenu(const int menuItemId);
		void savePanelStateToCurrentProgram();
		void setProgram (const ValueTree &item);
		void setProgram (const int programMenuIndex);

		void addNewBank (const String bankName, const String bankDescription, const int number, const int lsb, const int msb, ValueTree unitToAddTo=ValueTree());
		void addNewProgram (const String programName, const int number, ValueTree unitToAddTo=ValueTree());
		void addNewCustomData (const String dataName, const int number, ValueTree unitToAddTo=ValueTree());
		void addListener (ValueTree::Listener *listener)												{ libraryTree.addListener(listener); }
		void removeListener (ValueTree::Listener *listener)												{ libraryTree.removeListener(listener); }

		int getCurrentProgramMIDINumber(const int suggestedProgramNumber=-1);
		int getCurrentBankMIDINumber(const int suggestedBankNumber=-1);

		PopupMenu getProgramMenu();
		PopupMenu getBankMenu();
		PopupMenu getSnapshotMenu();

		void sendMidiProgramChange();
		void processMidi (MidiBuffer &incommingData);
		void importFromFile(const File &fileToImport, ValueTree itemSelected=ValueTree());

		int getListenerInputMidiChannel();
		bool isCurrentProgram(const ValueTree item);
		void attachToPopupMenu(PopupMenu &m);
		void attachCustomRequests(PopupMenu &m);
		ValueTree getProgramForMenuIndex(const int itemIndexToFind);
		ValueTree scanChildrenForMenuIndex(ValueTree item, int itemIndexToFind, int &currentIndex);
		void snapshot();
		void factoryReset();

		const String getDefaultProgramName(const String &suggestedProgramName);
		const String getDefaultBankName(const String &suggestedBankName);
		const String getDefaultSnapshotName();

		MemoryBlock getProgramNameAsData(const String &programName);

		static ValueTree createEmptyProgramTree();
		static bool isProgram(const ValueTree tree);
		static bool isBank(const ValueTree tree);
		static bool isRoot(const ValueTree tree);
		static bool isCustomData(const ValueTree tree);
		static bool isFirmware(const ValueTree tree);
		static bool isContainer(const ValueTree item);
        static bool isItem(const ValueTree item);
        static bool isEditBuffer(const ValueTree item);
        static bool isTransaction(const ValueTree item);
		static String getItemName(const int itemId);
		static Image getItemIcon(const int itemId);
		static const String getName(const ValueTree &vt);
		static int getNumber(const ValueTree &vt);
		static int getLSB(const ValueTree &vt);
		static int getMSB(const ValueTree &vt);
		Uuid getUuid(const ValueTree &tree);
		CtrlrPanel &getOwner() { return (owner); }
		static void wrapForLua (lua_State *L);

		JUCE_LEAK_DETECTOR(CtrlrMIDILibrary)

	private:
		void attachItemToPopupMenu(const ValueTree &itemToAttach, PopupMenu &m, int &itemOffset);
		ValueTree invalidTree;
		CtrlrPanel &owner;
		ValueTree libraryTree;
		ListenerList <CtrlrMIDILibrary::Listener> listeners;
		int midiBankNumber, midiProgramNumber, midiBankNumberLSB, midiBankNumberMSB;
		CtrlrMIDIDevice *inputDevice;
		WeakReference <CtrlrLuaMethod> 	luaTransInfoCbk;
		ValueTree currentBank, currentProgram, snapshotsTree, firmwareTree, editBufferTree, currentSnapshot, transactions;
};

#endif
