#ifndef CTRLR_PANEL_RESOURCE_EDITOR_H
#define CTRLR_PANEL_RESOURCE_EDITOR_H

#include "CtrlrMacros.h"
class CtrlrPanelEditor;
class CtrlrPanelResourceManager;

class CtrlrPanelResourceEditor  : public Component,
                                  public TableListBoxModel,
                                  public ButtonListener
{
	public:
		CtrlrPanelResourceEditor (CtrlrPanelEditor &_owner);
		~CtrlrPanelResourceEditor();
		int getNumRows();
		void paintRowBackground (Graphics& g, int rowNumber, int width, int height, bool rowIsSelected);
		void paintCell (Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected);
		void cellClicked(int rowNumber, int columnId, const MouseEvent &e);
		void cellDoubleClicked (int rowNumber, int columnId, const MouseEvent &e);
		void addResourceFromFile();
		void deleteSelectedResources();
		CtrlrPanelResourceManager &getResourceManager();
		void visibilityChanged();
		void sortOrderChanged(int newSortColumnId, bool isForwards);
		int compareElements(CtrlrPanelResource *first, CtrlrPanelResource *second);
		void paint (Graphics& g);
		void resized();
		void buttonClicked (Button* buttonThatWasClicked);
		void updateTable();
		void reloadAllResourcesFromSourceFiles();
		void backgroundClicked ();
		void showResourceInfo(const int resourceIndex);
	private:
		Array <CtrlrPanelResource*> resources;
		CtrlrPanelEditor &owner;
		int sortByColumnId;
		int sortForward;
		Font tableFont;
	    TableListBox* resourceList;
	    TextButton* add;
	    TextButton* remove, *reload;
	    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrPanelResourceEditor);
};


#endif
