#ifndef __JUCER_HEADER_CTRLRLISTBOX_CTRLRLISTBOX_F60BFF20__
#define __JUCER_HEADER_CTRLRLISTBOX_CTRLRLISTBOX_F60BFF20__

#include "../CtrlrComponent.h"
class CtrlrValueMap;

class CtrlrListBox  : public CtrlrComponent,
                      public ListBoxModel
{
public:
    //==============================================================================
    CtrlrListBox (CtrlrModulator &owner);
    ~CtrlrListBox();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	int getNumRows();
	void paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected);
	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	double getComponentValue();
	int getComponentMidiValue();
	double getComponentMaxValue();
	const String getComponentText();
	const String getTextForValue(const double value);
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}
	void listboxContentChanged();
	void selectedRowsChanged (int lastRowSelected);

	void listBoxItemClicked (int value, const MouseEvent &e);
	void listBoxItemDoubleClicked (int value, const MouseEvent &e);
	void deleteKeyPressed (int value);
	void returnKeyPressed (int value);

	static void wrapForLua(lua_State *L);
	void updateContent();
	void selectRow(int rowNumber, bool dontScrollToShowThisRow=false, bool deselectOthersFirst=true);
	void selectRangeOfRows (int firstRow, int lastRow);
	void deselectRow (int rowNumber);
	void deselectAllRows ();
	void flipRowSelection (int rowNumber);
	int getNumSelectedRows () const;
	int getSelectedRow (int index=0) const;
	int getLastRowSelected () const;
	bool isRowSelected (int rowNumber) const;
	void setMultipleSelectionEnabled (bool shouldBeEnabled);
	SparseSet <int> getSelectedRows () const;
	void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr) {}
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	ScopedPointer<CtrlrValueMap> valueMap;
	WeakReference <CtrlrLuaMethod> itemClickedCbk,itemDoubleClickedCbk,itemDeleteKeyPressedCbk,itemReturnKeyPressedCbk;
    //[/UserVariables]

    //==============================================================================
    ListBox* listBox;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrListBox (const CtrlrListBox&);
    const CtrlrListBox& operator= (const CtrlrListBox&);
};


#endif   // __JUCER_HEADER_CTRLRLISTBOX_CTRLRLISTBOX_F60BFF20__
