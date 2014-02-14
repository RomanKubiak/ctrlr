#ifndef __CTRLR_PANEL_MODULATOR_LIST__
#define __CTRLR_PANEL_MODULATOR_LIST__

#include "CtrlrPanelModulatorListTree.h"

class CtrlrModulatorListSorter
{
	public:
		CtrlrModulatorListSorter (CtrlrPanel &_owner, const Identifier &attributeToSort_, bool forwards);
		int compareElements (CtrlrModulator *first, CtrlrModulator *second) const;

	private:
		CtrlrPanel &owner;
		Identifier attributeToSort;
		int direction;
};

class CtrlrPanelModulatorList  : public CtrlrChildWindowContent,
                                 public TableListBoxModel,
								 public CtrlrPanel::Listener
{
	public:
		CtrlrPanelModulatorList (CtrlrPanel &_owner);
		~CtrlrPanelModulatorList();
		enum ColumnId
		{
			CNone,
			CVstIndex,
			CName,
			CVName,
			CMidiType,
			CUIType,
			CPositionedOffPanel
		};

		void copyModulatorList();
		int getNumRows();
		void paintRowBackground (Graphics& g, int rowNumber, int width, int height, bool rowIsSelected);
		void paintCell (Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) {}
		void sortOrderChanged (int newSortColumnId, bool isForwards);
		void cellDoubleClicked (int rowNumber, int columnId, const MouseEvent &e){}
		void cellClicked (int rowNumber, int columnId, const MouseEvent &e){}
		Component* refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate);
		void refresh();
		const bool isComponentOffPanel(const int indexInModulatorCopy);
		File getModListFile(const String &suffix);
		void selectedRowsChanged (int lastRowSelected);
		String getContentName()					{ return ("Panel modulator list"); }
		uint8 getType()							{ return (CtrlrPanelWindowManager::ModulatorList); }
		void makeVisibleItem();
		void exportListItem(const int format);
		void deleteSelected();
		const int getColumnIdForIdentifier (const String &columnName);
		const Identifier getColumnCtrlrId(const int columnId);
		static const String getValueStringForColumn (CtrlrModulator *m, const Identifier columnName);
		static Value getValueForColumn (CtrlrModulator *m, const Identifier columnName);
		void modulatorChanged (CtrlrModulator *modulatorThatChanged);
		void modulatorAdded (CtrlrModulator *modulatorThatWasAdded);
		void modulatorRemoved (CtrlrModulator *modulatorRemoved);
		void restoreColumns(const String &columnState);
		ValueTree &getIdTree();
		void paint (Graphics& g);
		void resized();
		void visibilityChanged();
		void mouseDown (const MouseEvent& e);
		void mouseUp (const MouseEvent& e);
		void switchView();
		void resetToDefaults();
		StringArray getMenuBarNames();
		PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName);
		void menuItemSelected(int menuItemID, int topLevelMenuIndex);
		void handleColumnSelection(const int itemId);
		void handleSortSelection(const int itemId);
		JUCE_LEAK_DETECTOR(CtrlrPanelModulatorList)

	private:
		CtrlrPanel &owner;
		Array <WeakReference<CtrlrModulator> > copyOfModulatorList;
		int sortColumnId;
		bool isSortedForward;
		CtrlrPanelModulatorListTree modulatorListTree;
	    TableListBox* modulatorList;
};


#endif
