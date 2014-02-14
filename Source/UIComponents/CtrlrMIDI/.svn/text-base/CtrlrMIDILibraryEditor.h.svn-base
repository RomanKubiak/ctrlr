#ifndef __CTRLR_MIDI_LIBRARY_EDITOR__
#define __CTRLR_MIDI_LIBRARY_EDITOR__

#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrWindowManagers/CtrlrPanelWindowManager.h"
#include "CtrlrWindowManagers/CtrlrChildWindowContent.h"
#include "CtrlrMIDILibrary/CtrlrMIDILibrary.h"
#include "CtrlrValueTreeEditor.h"

class CtrlrPanel;

class CtrlrMIDILibraryEditor  :	public CtrlrChildWindowContent,
								public ValueTree::Listener,
								public CtrlrValueTreeEditorLookProvider,
								public DragAndDropContainer
{
	public:
		CtrlrMIDILibraryEditor (CtrlrPanel &_owner);
		~CtrlrMIDILibraryEditor();

		enum ItemActions
		{
			ActCopy				= 0x301,
			ActPaste			= 0x302,
			ActCut				= 0x303,
			ActDelete			= 0x312,
			ActExport			= 0x304,
			ActDuplicate		= 0x305,
			ActAddBank			= 0x306,
			ActAddProgram		= 0x307,
			ActAddData			= 0x309,
			ActAddProgramNum	= 0x310,
			ActAddTransaction	= 0x311
		};
		StringArray getMenuBarNames();
		PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName);
		void menuItemSelected(int menuItemID, int topLevelMenuIndex);
		void setProgramTree (ValueTree programTree);
		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
		void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
		void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded);
		void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved);
		void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
		CtrlrPanel &getOwner()																							{ return (owner); }
		String getContentName()																							{ return ("Program Manager"); }
		uint8 getType()																									{ return (CtrlrPanelWindowManager::MIDILibrary); }
		void paint (Graphics& g);
		void resized();
		void refresh();
		void exportSelection();
		CtrlrMIDILibrary &getCore();
		void handleAsyncUpdate();
		const String getUniqueName(const ValueTree &item)	const;
		const AttributedString getDisplayString(const ValueTree &item)	const;
		const Font getItemFont(const ValueTree &item)		const;
		const int getItemHeight(const ValueTree &item)	const;
		bool canBeSelected(const ValueTree &item)	const;
		void itemClicked(const MouseEvent &e, ValueTree &item);
		void itemDoubleClicked(const MouseEvent &e, ValueTree &item);
		Image getIconForItem(const ValueTree &item) const;
		void itemSelectionChanged(ValueTree &item);
		const bool isInterestedInDragSource(const ValueTree &item, const DragAndDropTarget::SourceDetails &dragSourceDetails) const;
		void itemDropped (ValueTree &targetItem, const DragAndDropTarget::SourceDetails &dragSourceDetails, int insertIndex);
        void getContainerMenu(PopupMenu &m, const ValueTree &item);
        void getItemMenu(PopupMenu &m, const ValueTree &item);
        void getUtilityMenu(PopupMenu &m, const ValueTree &item);
		void handleItemMenu(ValueTree &item, const int itemId);
		void itemOpennessChanged(const bool isNowOpen);
		void cut(const bool copyToClipboard=true);
		void copy();
		void paste();
		void duplicate();
        bool isValidLibraryItem(const ValueTree &itemToCheck);
		void dialogAddProgram(ValueTree unitToAddTo);
		void dialogAddProgramNum(ValueTree unitToAddTo);
		void dialogAddCustomData(ValueTree unitToAddTo);
		void dialogAddBank(ValueTree unitToAddTo);
		void dialogAddFolder(ValueTree unitToAddTo);
		void dialogAddTransaction(ValueTree unitToAddTo);
		void visibilityChanged();
		void importFromFile(const File &fileToImport);
		bool keyPressed (const KeyPress &key, Component *originatingComponent);

		JUCE_LEAK_DETECTOR(CtrlrMIDILibraryEditor)

	private:
		Font itemFont, groupFont;
		CtrlrPanel &owner;
		Result res;
		ValueTree currentTree;
		StretchableLayoutManager layoutManager;
		StretchableLayoutResizerBar* spacerComponent;
		CtrlrValueTreeEditorTree *libraryTree;
		ValueTree clipboardTree;
		PropertyPanel *libraryItemProperties;
};


#endif
