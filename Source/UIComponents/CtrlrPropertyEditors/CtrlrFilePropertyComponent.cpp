#include "stdafx.h"
#include "CtrlrWindowManagers/CtrlrManagerWindowManager.h"
#include "CtrlrFilePropertyComponent.h"

CtrlrFileProperty::CtrlrFileProperty (const Value &_valeToControl) : valueToControl(_valeToControl)
{
    addAndMakeVisible (path = new Label (String::empty));
	path->setText (valueToControl.toString(), dontSendNotification);
	path->addListener (this);
	path->setColour (Label::backgroundColourId, Colours::white);
	path->setColour (Label::outlineColourId, findColour (ComboBox::outlineColourId));

    addAndMakeVisible (browse = new TextButton ("Browse", "Browse"));
    browse->addListener (this);
	browse->setConnectedEdges (TextButton::ConnectedOnRight);
    setSize (256, 48);
}

CtrlrFileProperty::~CtrlrFileProperty()
{
    deleteAndZero (path);
    deleteAndZero (browse);
}

void CtrlrFileProperty::resized()
{
	browse->setBounds (0, 0, 48, getHeight());
    path->setBounds (48, 0, getWidth() - 48, getHeight());
}

void CtrlrFileProperty::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == browse)
    {
		FileChooser myChooser ("Select a file", File::getSpecialLocation (File::userHomeDirectory), "*.*");

        if (myChooser.browseForFileToOpen())
        {
			valueToControl = myChooser.getResult().getFullPathName();
			path->setText (valueToControl.toString(), dontSendNotification);
        }
    }
}

void CtrlrFileProperty::refresh()
{
	path->setText (valueToControl.toString(), dontSendNotification);
}

void CtrlrFileProperty::labelTextChanged (Label* labelThatHasChanged)
{
	valueToControl = labelThatHasChanged->getText();
}
