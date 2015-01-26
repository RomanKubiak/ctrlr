#include "stdafx.h"
#include "CtrlrProgressBar.h"

CtrlrProgressBar::CtrlrProgressBar(CtrlrModulator &owner)
    : CtrlrComponent(owner), progress(-1)
{
    addAndMakeVisible (bar = new ProgressBar(progress));

    owner.setProperty (Ids::modulatorIsStatic, true);
	owner.setProperty (Ids::modulatorVstExported, false);
    setProperty (Ids::uiProgressBarBackgroundColour, "0xffffffff");
    setProperty (Ids::uiProgressBarForegroundColour, "0xff0f0f0f");
    setProperty (Ids::uiProgressBarDisplayPercent, true);

    componentTree.addListener (this);

    setSize (128,32);
}

CtrlrProgressBar::~CtrlrProgressBar()
{
}

void CtrlrProgressBar::resized()
{
	bar->setBounds (getUsableRect());
	CtrlrComponent::resized();
}

void CtrlrProgressBar::setComponentValue (const double newValue, const bool sendChangeMessage)
{
    progress = newValue;
}

double CtrlrProgressBar::getComponentValue()
{
    return (progress);
}

int CtrlrProgressBar::getComponentMidiValue()
{
	return ((int)progress * 100);
}

double CtrlrProgressBar::getComponentMaxValue()
{
    return (1.0);
}

const String CtrlrProgressBar::getComponentText()
{
    return (textToDisplay);
}

void CtrlrProgressBar::setComponentText (const String &componentText)
{
    textToDisplay = componentText;
    bar->setTextToDisplay (textToDisplay);
}

void CtrlrProgressBar::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
    if (property == Ids::uiProgressBarBackgroundColour)
    {
        bar->setColour (ProgressBar::backgroundColourId, VAR2COLOUR(getProperty(property)));
    }
    else if (property == Ids::uiProgressBarForegroundColour)
    {
        bar->setColour (ProgressBar::foregroundColourId, VAR2COLOUR(getProperty(property)));
    }
    else if (property == Ids::uiProgressBarDisplayPercent)
    {
        bar->setPercentageDisplay ((bool)getProperty(property));
    }
    else
	{
		CtrlrComponent::valueTreePropertyChanged(treeWhosePropertyHasChanged, property);
	}

	if (restoreStateInProgress == false)
	{
		resized();
	}
}
