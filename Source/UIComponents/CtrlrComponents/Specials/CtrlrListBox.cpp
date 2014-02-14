#include "stdafx.h"
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

//[Headers] You can add your own extra header files here...
#include "CtrlrUtilities.h"
#include "CtrlrIDs.h"
#include "CtrlrListBox.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrLuaManager.h"
//[/Headers]



//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrListBox::CtrlrListBox (CtrlrModulator &owner)
    : CtrlrComponent(owner),
      listBox (0)
{
	addAndMakeVisible (listBox = new ListBox ("List Box", this));
	listBox->setModel( this );

	//[UserPreSize]
	setProperty (Ids::uiListBoxContent, "");
	setProperty (Ids::uiListBoxRowHeight, 16);
	setProperty (Ids::uiListBoxBackgroundColour, "0xffffffff");
	setProperty (Ids::uiListBoxHighlightBgColour, "0xff0000ff");
	setProperty (Ids::uiListBoxHighlightFgColour, "0xff000000");
	setProperty (Ids::uiListBoxTextColour, "0xff000000");
	setProperty (Ids::uiListBoxFont, FONT2STR (Font(14)));
	setProperty (Ids::uiListBoxHighlightFont, FONT2STR (Font(14)));
	setProperty (Ids::uiListBoxOutline, 0);
	setProperty (Ids::uiListBoxOutlineColour, "0xff000000");
	setProperty (Ids::uiListBoxVScrollBgColour, "0xffffffff");
	setProperty (Ids::uiListBoxVScrollThumbColour, "0xffababab");
	setProperty (Ids::uiListBoxVScrollTrackColour, "0xffff0000");
	setProperty (Ids::uiListBoxHScrollBgColour, "0xffffffff");
	setProperty (Ids::uiListBoxHScrollThumbColour, "0xffababab");
	setProperty (Ids::uiListBoxHScrollTrackColour, "0xffff0000");
	setProperty (Ids::uiListBoxJustification, "centred");
	setProperty (Ids::uiListBoxMultipleSelection, false);
	setProperty (Ids::uiListBoxItemClicked, COMBO_NONE_ITEM);
	setProperty (Ids::uiListBoxItemDoubleClicked, COMBO_NONE_ITEM);
	setProperty (Ids::uiListBoxItemDeleteKeyPressed, COMBO_NONE_ITEM);
	setProperty (Ids::uiListBoxItemReturnKeyPressed, COMBO_NONE_ITEM);
    //[/UserPreSize]

    setSize (128, 256);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrListBox::~CtrlrListBox()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (listBox);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrListBox::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrListBox::resized()
{
    listBox->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
	listBox->setBounds (getUsableRect());
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
int CtrlrListBox::getNumRows()
{
	return (valueMap.getNumValues());
}

void CtrlrListBox::paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected)
{
	if (rowIsSelected)
	{
		g.setFont (STR2FONT(getProperty(Ids::uiListBoxHighlightFont)));
		g.fillAll (VAR2COLOUR(getProperty(Ids::uiListBoxHighlightBgColour)));
		g.setColour (VAR2COLOUR(getProperty(Ids::uiListBoxHighlightFgColour)));
		g.drawText (valueMap.getTextForIndex(rowNumber), 0, 0,  width, height, justificationFromProperty(getProperty(Ids::uiListBoxJustification)), true);
	}
	else
	{
		g.setFont (STR2FONT(getProperty(Ids::uiListBoxFont)));
		g.setColour (VAR2COLOUR(getProperty(Ids::uiListBoxTextColour)));
		g.drawText (valueMap.getTextForIndex(rowNumber), 0, 0,  width, height, justificationFromProperty(getProperty(Ids::uiListBoxJustification)), true);
	}
}

void CtrlrListBox::setComponentValue (const double newValue, const bool sendChangeMessage)
{
	listBox->selectRow (newValue, false, true);

	if (sendChangeMessage)
	{
		owner.getProcessor().setValueFromGUI (newValue);
	}
}

const double CtrlrListBox::getComponentValue()
{
	return (listBox->getSelectedRow());
}

const int CtrlrListBox::getComponentMidiValue()
{
	return (valueMap.getMappedValue(listBox->getSelectedRow()));
}

const double CtrlrListBox::getComponentMaxValue()
{
	return (valueMap.getNonMappedMax());
}

const String CtrlrListBox::getComponentText()
{
	return (valueMap.getTextForIndex(listBox->getSelectedRow()));
}

const String CtrlrListBox::getTextForValue(const double value)
{
	return (valueMap.getTextForIndex(value));
}

void CtrlrListBox::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiListBoxContent)
	{
		listboxContentChanged();
	}

	else if (property == Ids::uiListBoxBackgroundColour)
	{
		listBox->setColour (ListBox::backgroundColourId, VAR2COLOUR(getProperty (property)));
	}

	else if (property == Ids::uiListBoxOutline)
	{
		listBox->setOutlineThickness (getProperty (property));
	}

	else if (property == Ids::uiListBoxOutlineColour)
	{
		listBox->setColour (ListBox::outlineColourId, VAR2COLOUR(getProperty (property)));
	}

	else if (property == Ids::uiListBoxRowHeight)
	{
		listBox->setRowHeight (getProperty(property));
	}

	else if (property == Ids::uiListBoxHScrollBgColour
		|| property == Ids::uiListBoxHScrollThumbColour
		|| property == Ids::uiListBoxHScrollTrackColour
		|| property == Ids::uiListBoxVScrollBgColour
		|| property == Ids::uiListBoxVScrollThumbColour
		|| property == Ids::uiListBoxVScrollTrackColour
		)
	{
		if (listBox->getVerticalScrollBar())
		{
			listBox->getVerticalScrollBar()->setColour (ScrollBar::backgroundColourId, VAR2COLOUR(getProperty (Ids::uiListBoxVScrollBgColour)));
			listBox->getVerticalScrollBar()->setColour (ScrollBar::thumbColourId, VAR2COLOUR(getProperty (Ids::uiListBoxVScrollThumbColour)));
			listBox->getVerticalScrollBar()->setColour (ScrollBar::trackColourId, VAR2COLOUR(getProperty (Ids::uiListBoxVScrollTrackColour)));
		}

		if (listBox->getHorizontalScrollBar())
		{
			listBox->getHorizontalScrollBar()->setColour (ScrollBar::backgroundColourId, VAR2COLOUR(getProperty (Ids::uiListBoxHScrollBgColour)));
			listBox->getHorizontalScrollBar()->setColour (ScrollBar::thumbColourId, VAR2COLOUR(getProperty (Ids::uiListBoxHScrollThumbColour)));
			listBox->getHorizontalScrollBar()->setColour (ScrollBar::trackColourId, VAR2COLOUR(getProperty (Ids::uiListBoxHScrollTrackColour)));
		}
	}
	else if (property == Ids::uiListBoxItemClicked)
	{
		if (getProperty(property) == String::empty)
			return;

		itemClickedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiListBoxItemDoubleClicked)
	{
		if (getProperty(property) == String::empty)
			return;

		itemDoubleClickedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiListBoxItemDeleteKeyPressed)
	{
		if (getProperty(property) == String::empty)
			return;

		itemDeleteKeyPressedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiListBoxItemReturnKeyPressed)
	{
		if (getProperty(property) == String::empty)
			return;

		itemReturnKeyPressedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiListBoxMultipleSelection)
	{
		listBox->setMultipleSelectionEnabled ((bool)getProperty(property));
	}
	else
	{
		CtrlrComponent::valueTreePropertyChanged (treeWhosePropertyHasChanged, property);
	}

	resized();
	listBox->updateContent();
	listBox->repaint();
}

void CtrlrListBox::listBoxItemClicked (int value, const MouseEvent &e)
{
	if (itemClickedCbk && !itemClickedCbk.wasObjectDeleted())
	{
		if (itemClickedCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (itemClickedCbk, &owner, value);
		}
	}
}

void CtrlrListBox::listBoxItemDoubleClicked (int value, const MouseEvent &e)
{
	if (itemDoubleClickedCbk && !itemDoubleClickedCbk.wasObjectDeleted())
	{
		if (itemDoubleClickedCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (itemDoubleClickedCbk, &owner, value);
		}
	}
}

void CtrlrListBox::deleteKeyPressed (int value)
{
	if (itemDeleteKeyPressedCbk && !itemDeleteKeyPressedCbk.wasObjectDeleted())
	{
		if (itemDeleteKeyPressedCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (itemDeleteKeyPressedCbk, &owner, value);
		}
	}
}

void CtrlrListBox::returnKeyPressed (int value)
{
	if (itemReturnKeyPressedCbk && !itemReturnKeyPressedCbk.wasObjectDeleted())
	{
		if (itemReturnKeyPressedCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (itemReturnKeyPressedCbk, &owner, value);
		}
	}
}


void CtrlrListBox::listboxContentChanged()
{
	valueMap.copyFrom (owner.getProcessor().setValueMap (getProperty (Ids::uiListBoxContent)));
}

void CtrlrListBox::selectedRowsChanged (int lastRowSelected)
{
	if ((bool)getProperty(Ids::uiListBoxMultipleSelection))
	{
		return;
	}
	else
	{
		if (lastRowSelected >= 0)
		{
			setComponentValue (lastRowSelected, true);
		}
	}
}

void CtrlrListBox::updateContent()
{
	listBox->updateContent();
}

void CtrlrListBox::selectRow(int rowNumber, bool dontScrollToShowThisRow, bool deselectOthersFirst)
{
	listBox->selectRow(rowNumber, dontScrollToShowThisRow, deselectOthersFirst);
}

void CtrlrListBox::selectRangeOfRows(int firstRow, int lastRow)
{
	listBox->selectRangeOfRows (firstRow, lastRow);
}

void CtrlrListBox::deselectRow(int rowNumber)
{
	listBox->deselectRow (rowNumber);
}

void CtrlrListBox::deselectAllRows()
{
	listBox->deselectAllRows();
}

void CtrlrListBox::flipRowSelection(int rowNumber)
{
	listBox->flipRowSelection(rowNumber);
}

int CtrlrListBox::getNumSelectedRows() const
{
	return (listBox->getNumSelectedRows());
}

int CtrlrListBox::getSelectedRow(int index) const
{
	return (listBox->getSelectedRow(index));
}

int CtrlrListBox::getLastRowSelected() const
{
	return (listBox->getLastRowSelected());
}

bool CtrlrListBox::isRowSelected(int rowNumber) const
{
	return (listBox->isRowSelected(rowNumber));
}

SparseSet <int> CtrlrListBox::getSelectedRows() const
{
	return (listBox->getSelectedRows());
}

void CtrlrListBox::setMultipleSelectionEnabled (bool shouldBeEnabled)
{
	listBox->setMultipleSelectionEnabled(shouldBeEnabled);
}

void CtrlrListBox::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrListBox,bases<CtrlrComponent,CtrlrLuaObject> >("CtrlrListBox")
			.def("getNumRows", &CtrlrListBox::getNumRows)
			.def("updateContent", &CtrlrListBox::updateContent)
			.def("selectRow", &CtrlrListBox::selectRow)
			.def("selectRangeOfRows", &CtrlrListBox::selectRangeOfRows)
			.def("deselectRow", &CtrlrListBox::deselectRow)
			.def("deselectAllRows", &CtrlrListBox::deselectAllRows)
			.def("flipRowSelection", &CtrlrListBox::flipRowSelection)
			.def("getNumSelectedRows", &CtrlrListBox::getNumSelectedRows)
			.def("getSelectedRow", &CtrlrListBox::getSelectedRow)
			.def("getLastRowSelected", &CtrlrListBox::getLastRowSelected)
			.def("isRowSelected", &CtrlrListBox::isRowSelected)
			.def("getSelectedRows", &CtrlrListBox::getSelectedRows)
			.def("setMultipleSelectionEnabled", &CtrlrListBox::setMultipleSelectionEnabled)
	];
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrListBox" componentName=""
                 parentClasses="public CtrlrComponent, public ListBoxModel" constructorParams="CtrlrModulator &amp;owner"
                 variableInitialisers="CtrlrComponent(owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="128"
                 initialHeight="256">
  <BACKGROUND backgroundColour="ffffff"/>
  <GENERICCOMPONENT name="" id="fdd8fa416d09ba08" memberName="listBox" virtualName=""
                    explicitFocusOrder="0" pos="0 0 0M 0M" class="ListBox" params="&quot;List Box&quot;, this"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
