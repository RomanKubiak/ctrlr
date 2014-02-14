/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  16 Jan 2012 11:31:34pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRLISTBOX_CTRLRLISTBOX_F60BFF20__
#define __JUCER_HEADER_CTRLRLISTBOX_CTRLRLISTBOX_F60BFF20__

//[Headers]     -- You can add your own extra header files here --
#include "../CtrlrComponent.h"
#include "CtrlrValueMap.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
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
	const double getComponentValue();
	const int getComponentMidiValue();
	const double getComponentMaxValue();
	const String getComponentText();
	const String getTextForValue(const double value);
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
	void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
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
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	CtrlrValueMap valueMap;
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
