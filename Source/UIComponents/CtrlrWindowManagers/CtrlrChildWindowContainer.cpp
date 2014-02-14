#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  23 Oct 2012 11:11:41pm

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
#include "CtrlrChildWindowContent.h"
#include "CtrlrLog.h"
#include "CtrlrChildWindow.h"
#include "CtrlrPanelWindowManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
//[/Headers]

#include "CtrlrChildWindowContainer.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrChildWindowContainer::CtrlrChildWindowContainer (CtrlrWindowManager &_owner)
    : content(nullptr), owner(_owner),
      menuBar (0)
{
    addAndMakeVisible (menuBar = new MenuBarComponent (this));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrChildWindowContainer::~CtrlrChildWindowContainer()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (menuBar);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrChildWindowContainer::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrChildWindowContainer::resized()
{
    menuBar->setBounds (0, 0, getWidth() - 0, 20);
    //[UserResized] Add your own custom resize handling here..
	if (content)
	{
		content->setBounds (0, 20, getWidth(), getHeight() - 20);
	}
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrChildWindowContainer::setContent(CtrlrChildWindowContent *_content)
{
	content = _content;

	if (content != nullptr)
	{
		deleteAndZero (menuBar);
		addAndMakeVisible (menuBar = new MenuBarComponent (this));
		addAndMakeVisible (content);
		content->setContainer (this);
	}

	resized();
}

CtrlrChildWindowContent *CtrlrChildWindowContainer::getContent()
{
	return (content);
}

CtrlrWindowManager &CtrlrChildWindowContainer::getOwner()
{
	return (owner);
}

void CtrlrChildWindowContainer::closeWindow()
{
	if (getParentComponent())
	{
		delete getParentComponent();
	}
}

StringArray CtrlrChildWindowContainer::getMenuBarNames()
{
	if (content)
	{
		if (content->getMenuBarNames().size() != 0)
		{
			return (content->getMenuBarNames());
		}
	}
	const char* const names[] = { "File", nullptr };
	return StringArray (names);
}

PopupMenu CtrlrChildWindowContainer::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
	if (content)
	{
		if (content->getMenuForIndex (topLevelMenuIndex, menuName).getNumItems() > 0)
		{
			return (content->getMenuForIndex (topLevelMenuIndex, menuName));
		}
	}

	PopupMenu m;
	if (topLevelMenuIndex == 0)
	{
		m.addItem (1, "Close");
	}

	return (m);
}

void CtrlrChildWindowContainer::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	if (content)
	{
		content->menuItemSelected(menuItemID, topLevelMenuIndex);
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrChildWindowContainer"
                 componentName="" parentClasses="public Component, public MenuBarModel"
                 constructorParams="CtrlrWindowManager &amp;_owner" variableInitialisers="content(nullptr), owner(_owner)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffff"/>
  <GENERICCOMPONENT name="" id="92dec9facec2cf7d" memberName="menuBar" virtualName=""
                    explicitFocusOrder="0" pos="0 0 0M 20" class="MenuBarComponent"
                    params="this"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
