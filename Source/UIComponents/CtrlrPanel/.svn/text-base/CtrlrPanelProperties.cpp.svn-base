#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  14 Nov 2011 4:00:00pm

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
#include "CtrlrPanelEditor.h"
#include "CtrlrPanelUtilities.h"
#include "CtrlrLog.h"
#include "CtrlrPanelComponentProperties.h"
#include "CtrlrPanelResourceEditor.h"
//[/Headers]

#include "CtrlrPanelProperties.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrPanelProperties::CtrlrPanelProperties (CtrlrPanelEditor &_owner)
    : Component (L"Properties"),
      owner(_owner),
      tabbedComponent (0)
{
    addAndMakeVisible (tabbedComponent = new TabbedComponent (TabbedButtonBar::TabsAtRight));
    tabbedComponent->setTabBarDepth (24);
    tabbedComponent->setCurrentTabIndex (-1);


    //[UserPreSize]
	tabbedComponent->setOutline (0);
	tabbedComponent->addTab ("General",		Colours::lightgrey, new CtrlrPanelComponentProperties (owner), true);
    tabbedComponent->addTab ("Resources",	Colours::lightgrey, new CtrlrPanelResourceEditor (owner), true);
	tabbedComponent->addTab("Utility",		Colours::lightgrey, new CtrlrPanelUtilities(owner), true);
    //[/UserPreSize]

    setSize (216, 364);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrPanelProperties::~CtrlrPanelProperties()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	CtrlrPanelComponentProperties *p = dynamic_cast <CtrlrPanelComponentProperties*>(tabbedComponent->getTabContentComponent (0));
	if (p)
	{
		owner.getOwner().getOwner().removeListener (p);
	}
    //[/Destructor_pre]

    deleteAndZero (tabbedComponent);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrPanelProperties::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrPanelProperties::resized()
{
    tabbedComponent->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrPanelProperties::changeListenerCallback (ChangeBroadcaster* source)
{
}

void CtrlrPanelProperties::refreshAll()
{
	for (int i=0; i<tabbedComponent->getNumTabs(); i++)
	{
		CtrlrPanelComponentProperties *cp = dynamic_cast<CtrlrPanelComponentProperties*>(tabbedComponent->getTabContentComponent(i));
		if (cp!=0)
		{
			cp->refreshAll();
		}
	}
}

void CtrlrPanelProperties::layoutChanged()
{
	if ((bool)owner.getProperty(Ids::uiPanelPropertiesOnRight) == true)
	{
		tabbedComponent->setOrientation(TabbedButtonBar::TabsAtLeft);
	}
	else
	{
		tabbedComponent->setOrientation(TabbedButtonBar::TabsAtRight);
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrPanelProperties" componentName="Properties"
                 parentClasses="public Component, public ChangeListener, public ChangeBroadcaster"
                 constructorParams="CtrlrPanelEditor &amp;_owner" variableInitialisers="owner(_owner)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="216" initialHeight="364">
  <BACKGROUND backgroundColour="0"/>
  <TABBEDCOMPONENT name="" id="5a325b72673141f2" memberName="tabbedComponent" virtualName=""
                   explicitFocusOrder="0" pos="0 0 0M 0M" orientation="right" tabBarDepth="24"
                   initialTab="-1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
