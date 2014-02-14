#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  14 Nov 2011 8:14:25pm

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
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrPanel/CtrlrPanelCanvas.h"
#include "CtrlrPanelLayerListItem.h"
//[/Headers]

#include "CtrlrPanelLayerList.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrPanelLayerList::CtrlrPanelLayerList (CtrlrPanel &_owner)
    : owner(_owner),
      layerList (0)
{
    addAndMakeVisible (layerList = new ListBox ("Layer List", this));


    //[UserPreSize]
	layerList->setRowHeight (40);
	layerList->setMultipleSelectionEnabled (false);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrPanelLayerList::~CtrlrPanelLayerList()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (layerList);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrPanelLayerList::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrPanelLayerList::resized()
{
    layerList->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
int CtrlrPanelLayerList::getNumRows()
{
	return (owner.getEditor()->getCanvas()->getNumLayers());
}

void CtrlrPanelLayerList::paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
	if (rowIsSelected)
	{
		g.fillAll(Colours::lightblue);
	}
	else
	{
		g.fillAll(Colours::white);
	}
}

Component* CtrlrPanelLayerList::refreshComponentForRow (int rowNumber, bool isRowSelected, Component* existingComponentToUpdate)
{
	CtrlrPanelLayerListItem* itemInfo = (CtrlrPanelLayerListItem*) existingComponentToUpdate;

	if (itemInfo == 0)
		itemInfo = new CtrlrPanelLayerListItem (*this);

	itemInfo->setRow (rowNumber);
	itemInfo->setLayer (owner.getEditor()->getCanvas()->getLayerFromArray(rowNumber));
	return itemInfo;
}

void CtrlrPanelLayerList::setSelectedRow(const int rowToSelect)
{
	layerList->selectRow (rowToSelect);
}

void CtrlrPanelLayerList::buttonClicked (Button *button)
{
}

CtrlrPanel &CtrlrPanelLayerList::getOwner()
{
	return (owner);
}

void CtrlrPanelLayerList::addLayer()
{
	if (owner.getEditor())
	{
		owner.getEditor()->getCanvas()->addLayer(ValueTree());
	}
	layerList->updateContent();
}

void CtrlrPanelLayerList::removeLayer()
{
	const int selectedRow = layerList->getSelectedRow();
	CtrlrPanelLayerListItem *item = dynamic_cast <CtrlrPanelLayerListItem*> (layerList->getComponentForRowNumber (selectedRow));
	CtrlrPanelCanvasLayer *layer = 0;
	if (item != nullptr)
	{
		layer = item->getLayer();
	}

	if (owner.getEditor())
	{
		owner.getEditor()->getCanvas()->removeLayer(layer);
	}
	layerList->updateContent();
}

void CtrlrPanelLayerList::moveLayerUp()
{
	const int selectedRow = layerList->getSelectedRow();
	CtrlrPanelLayerListItem *item = dynamic_cast <CtrlrPanelLayerListItem*> (layerList->getComponentForRowNumber (selectedRow));
	CtrlrPanelCanvasLayer *layer = 0;
	if (item != nullptr)
	{
		layer = item->getLayer();
	}

	if (selectedRow-1 < 0)
		return;

	if (owner.getEditor())
	{
		owner.getEditor()->getCanvas()->moveLayer(layer);
	}
	layerList->updateContent();
	layerList->selectRow (selectedRow-1);
}

void CtrlrPanelLayerList::moveLayerDown()
{
	const int selectedRow = layerList->getSelectedRow();
	CtrlrPanelLayerListItem *item = dynamic_cast <CtrlrPanelLayerListItem*> (layerList->getComponentForRowNumber (selectedRow));
	CtrlrPanelCanvasLayer *layer = 0;
	if (item != nullptr)
	{
		layer = item->getLayer();
	}

	if (selectedRow+1 >= getNumRows())
		return;

	if (owner.getEditor())
	{
		owner.getEditor()->getCanvas()->moveLayer(layer,false);
	}
	layerList->updateContent();
	layerList->selectRow (selectedRow+1);
}

void CtrlrPanelLayerList::refresh()
{
	layerList->updateContent();
}

StringArray CtrlrPanelLayerList::getMenuBarNames()
{
	const char* const names[] = { "File", "Edit", "View", nullptr };
	return StringArray (names);
}

PopupMenu CtrlrPanelLayerList::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
	PopupMenu menu;
	if (topLevelMenuIndex == 0)
	{
		menu.addItem (1, "Close");
	}
	else if (topLevelMenuIndex == 1)
	{
		menu.addItem (2, "Add layer");
		menu.addItem (3, "Remove layer");
		menu.addSectionHeader ("Reposition");
		menu.addItem (4, "Move up");
		menu.addItem (5, "Move down");
	}
	else if (topLevelMenuIndex == 2)
	{
		menu.addItem (6, "Refresh view");
	}
	return (menu);
}

void CtrlrPanelLayerList::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	if (menuItemID == 2)
		addLayer();
	if (menuItemID == 3)
		removeLayer();
	if (menuItemID == 4)
		moveLayerUp();
	if (menuItemID == 5)
		moveLayerDown();
	if (menuItemID == 6)
		refresh();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrPanelLayerList" componentName=""
                 parentClasses="public CtrlrChildWindowContent, public ListBoxModel"
                 constructorParams="CtrlrPanel &amp;_owner" variableInitialisers="owner(_owner)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffff"/>
  <GENERICCOMPONENT name="" id="bf3c104833fd7aa" memberName="layerList" virtualName=""
                    explicitFocusOrder="0" pos="0 0 0M 0M" class="ListBox" params="&quot;Layer List&quot;, this"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
