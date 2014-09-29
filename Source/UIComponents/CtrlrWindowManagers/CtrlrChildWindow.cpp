#include "stdafx.h"
#include "CtrlrPanelWindowManager.h"
#include "CtrlrChildWindowContent.h"
#include "CtrlrInlineUtilitiesGUI.h"
#include "CtrlrChildWindow.h"

CtrlrChildWindow::CtrlrChildWindow (CtrlrWindowManager &_owner)
    : owner(_owner), DocumentWindow("Child window", Colours::lightgrey, DocumentWindow::allButtons, true), contentComponent(nullptr)
{
	setUsingNativeTitleBar (true);
	setResizable(true,false);
	containerComponent = new CtrlrChildWindowContainer(owner);
	setContentOwned (containerComponent, true);

	if (!JUCEApplication::isStandaloneApp())
	{
		setAlwaysOnTop(true);
	}
	addKeyListener (this);
    setSize (800, 500);
}

CtrlrChildWindow::~CtrlrChildWindow()
{
	deleteAndZero (containerComponent);
	if (contentComponent)
	{
		deleteAndZero (contentComponent);
	}
}

void CtrlrChildWindow::paint (Graphics& g)
{
	drawDefaultWindowBackground (g,getWidth(),getHeight());
}

void CtrlrChildWindow::resized()
{
	DocumentWindow::resized();
	owner.windowChanged(this);
}

void CtrlrChildWindow::enablementChanged()
{
}

void CtrlrChildWindow::moved()
{
	owner.windowChanged(this);
}

CtrlrChildWindowContent *CtrlrChildWindow::getContent()
{
	return (contentComponent);
}

uint8 CtrlrChildWindow::getType()
{
	if (contentComponent)
	{
		return (contentComponent->getType());
	}
	else
	{
		return (0);
	}
}

void CtrlrChildWindow::setContent(CtrlrChildWindowContent *_contentComponent)
{
	contentComponent = _contentComponent;
	if (contentComponent != nullptr)
	{
		setName (contentComponent->getName());
		containerComponent->setContent (contentComponent);
	}
}

void CtrlrChildWindow::closeButtonPressed()
{
	owner.windowClosedButtonPressed (this);
}

bool CtrlrChildWindow::keyPressed (const KeyPress &key, Component *originatingComponent)
{
	if (contentComponent)
	{
		return (contentComponent->keyPressed (key, originatingComponent));
	}

	return (false);
}
