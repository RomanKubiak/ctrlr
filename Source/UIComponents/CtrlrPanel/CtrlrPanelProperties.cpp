#include "stdafx.h"
#include "CtrlrPanelEditor.h"
#include "CtrlrPanelUtilities.h"
#include "CtrlrLog.h"
#include "CtrlrPanelComponentProperties.h"
#include "CtrlrPanelResourceEditor.h"


#include "CtrlrPanelProperties.h"

CtrlrPanelProperties::CtrlrPanelProperties (CtrlrPanelEditor &_owner)
    : Component (L"Properties"),
      owner(_owner),
      tabbedComponent (0)
{
    addAndMakeVisible (tabbedComponent = new TabbedComponent (TabbedButtonBar::TabsAtRight));
    tabbedComponent->setTabBarDepth (owner.getOwner().getOwner().getProperty(Ids::ctrlrTabBarDepth));
    tabbedComponent->setCurrentTabIndex (-1);

	CtrlrPanelComponentProperties *props = new CtrlrPanelComponentProperties (owner);
	tabbedComponent->setOutline (0);
	tabbedComponent->addTab ("General",		Colours::lightgrey, props, true);
    tabbedComponent->addTab ("Resources",	Colours::lightgrey, new CtrlrPanelResourceEditor (owner), true);
	tabbedComponent->addTab("Utility",		Colours::lightgrey, new CtrlrPanelUtilities(owner), true);

	ctrlrPanelFindProperty.reset(new CtrlrPanelFindProperty(owner, props));
	addAndMakeVisible(ctrlrPanelFindProperty.get());
	setSize (216, 364);
}

CtrlrPanelProperties::~CtrlrPanelProperties()
{
	CtrlrPanelComponentProperties *p = dynamic_cast <CtrlrPanelComponentProperties*>(tabbedComponent->getTabContentComponent (0));
	if (p)
	{
		owner.getOwner().getCtrlrManagerOwner().removeListener (p);
	}
    deleteAndZero (tabbedComponent);
}

void CtrlrPanelProperties::paint (Graphics& g)
{
}

void CtrlrPanelProperties::resized()
{
	ctrlrPanelFindProperty->setBounds(0,0,getWidth() - (int)owner.getOwner().getOwner().getProperty(Ids::ctrlrTabBarDepth),32);
    tabbedComponent->setBounds (0, 32, getWidth() - 0, getHeight() - 32);
}

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
