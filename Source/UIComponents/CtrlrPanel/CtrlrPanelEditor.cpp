#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrLog.h"
#include "CtrlrPanelEditor.h"
#include "CtrlrProcessor.h"
#include "CtrlrComponents/CtrlrComponentTypeManager.h"
#include "CtrlrApplicationWindow/CtrlrLookAndFeel.h"
#include "CtrlrPanel/CtrlrPanelMIDIToolbar.h"
#include "CtrlrInlineUtilitiesGUI.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrComponents/CtrlrCombo.h"
#include "CtrlrPanel/CtrlrPanelResource.h"

CtrlrPanelNotifier::CtrlrPanelNotifier(CtrlrPanelEditor &_owner)
	: owner(_owner), background(Colours::lightgrey)
{
	addAndMakeVisible (text = new Label());
	text->addMouseListener (this,true);
	text->setColour (Label::backgroundColourId, Colours::transparentBlack);
	text->setColour (Label::textColourId, Colours::white.withAlpha (0.85f));
	text->setFont (Font (12.0f, Font::bold));
}

void CtrlrPanelNotifier::paint (Graphics &g)
{
	drawSelectionRectangle (g, getWidth(), getHeight(), background);
}

void CtrlrPanelNotifier::resized()
{
	text->setBounds (16,0,getWidth()-32,getHeight());
}

void CtrlrPanelNotifier::setNotification (const String &notification, const CtrlrNotificationType ctrlrNotificationType)
{
	background = getBackgroundColourForNotification(ctrlrNotificationType);
	text->setText (notification, dontSendNotification);
}

void CtrlrPanelNotifier::mouseDown (const MouseEvent &e)
{
	owner.notificationClicked(e);
}

Colour CtrlrPanelNotifier::getBackgroundColourForNotification(const CtrlrNotificationType ctrlrNotificationType)
{
	switch (ctrlrNotificationType)
	{
		case NotifySuccess:
			return (Colours::green.brighter(0.2f));
		case NotifyFailure:
			return (Colours::red.brighter(0.2f));
		case NotifyWarning:
			return (Colours::yellow.darker(0.5f));
		case NotifyInformation:
			return (Colours::grey);
	}

	return (Colours::lightgrey);
}

/**
 */

CtrlrPanelEditor::CtrlrPanelEditor (CtrlrPanel &_owner, CtrlrManager &_ctrlrManager, const String &panelName)
    : Component (L"Ctrlr Panel Editor"),
      lastEditMode(true),
	  ctrlrManager(_ctrlrManager),
	  owner(_owner),
	  panelEditorTree(Ids::uiPanelEditor),
	  ctrlrComponentSelection(nullptr),
      ctrlrPanelProperties (nullptr),
      spacerComponent (nullptr),
	  ctrlrPanelNotifier(nullptr),
	  midiToolbar(*this)
{
	ctrlrComponentSelection = new CtrlrComponentSelection (*this);

	removeColour (TooltipWindow::textColourId);

	addAndMakeVisible (ctrlrPanelViewport = new CtrlrPanelViewport (*this));
    addAndMakeVisible (ctrlrPanelProperties = new CtrlrPanelProperties (*this));
    addAndMakeVisible (spacerComponent = new StretchableLayoutResizerBar (&layoutManager, 1, true));
	addAndMakeVisible (ctrlrPanelNotifier = new CtrlrPanelNotifier(*this));
	addAndMakeVisible (&midiToolbar);

	ctrlrPanelNotifier->setAlwaysOnTop (true);
	ctrlrPanelNotifier->setVisible (false);
	componentAnimator.addChangeListener (this);

    spacerComponent->setName (L"spacerComponent");

 	getPanelEditorTree().addListener (this);

 	layoutManager.setItemLayout (0, -0.001, -1.0, -0.8);
 	layoutManager.setItemLayout (1, 8, 8, 8);
 	layoutManager.setItemLayout (2, -0.001, -1.0, -0.2);

	editorComponentsInEditMode[0]	= ctrlrPanelViewport;
	editorComponentsInEditMode[1]	= spacerComponent;
	editorComponentsInEditMode[2]	= ctrlrPanelProperties;

	editorComponents[0]				= ctrlrPanelViewport;

	setProperty(Ids::uiPanelSnapSize, 8);
	setProperty(Ids::uiPanelBackgroundColour, "0xffffffff");
	setProperty(Ids::uiPanelBackgroundColour1, "0xffffffff");
	setProperty(Ids::uiPanelBackgroundColour2, "0xffffffff");
	setProperty(Ids::uiPanelBackgroundGradientType, 1);
	setProperty(Ids::uiPanelImageResource, COMBO_ITEM_NONE);
 	setProperty(Ids::uiPanelEditMode, true);
	setProperty(Ids::uiPanelLock, false);
	setProperty(Ids::uiPanelDisabledOnEdit, false);

 	setProperty(Ids::uiPanelWidth, 400);
 	setProperty(Ids::uiPanelHeight, 400);
 	setProperty(Ids::name, panelName);
	setProperty(Ids::uiPanelImageAlpha, 255);
	setProperty(Ids::uiPanelImageLayout, 64);
	setProperty(Ids::uiPanelSnapActive, true);
	setProperty(Ids::uiPanelPropertiesOnRight, false);
	setProperty(Ids::luaPanelPaintBackground, COMBO_ITEM_NONE);
	setProperty(Ids::luaPanelResized, COMBO_ITEM_NONE);
	setProperty(Ids::luaPanelFileDragDropHandler, COMBO_ITEM_NONE);
	setProperty(Ids::luaPanelFileDragEnterHandler, COMBO_ITEM_NONE);
	setProperty(Ids::luaPanelFileDragExitHandler, COMBO_ITEM_NONE);

	setProperty(Ids::uiPanelInvisibleComponentAlpha, 0.5);
	setProperty(Ids::uiPanelMidiToolbarVisible, false);
	setProperty(Ids::uiPanelTooltipBackgroundColour, "0xffeeeebb");
	setProperty(Ids::uiPanelTooltipOutlineColour, "0xff000000");
	setProperty(Ids::uiPanelTooltipColour, "0xff000000");
	setProperty(Ids::uiPanelTooltipCornerRound, 1.0);
	setProperty(Ids::uiPanelTooltipPlacement, BubbleComponent::below);
	setProperty(Ids::uiPanelTooltipFont, Font(15.0f, Font::bold).toString());
	setProperty(Ids::uiPanelZoom, 1.0);
 	ctrlrComponentSelection->addChangeListener (ctrlrPanelProperties);

    setSize (600, 400);

	ctrlrComponentSelection->sendChangeMessage();
}

CtrlrPanelEditor::~CtrlrPanelEditor()
{
	componentAnimator.removeChangeListener (this);
	getPanelEditorTree().removeListener (this);
	owner.getPanelTree().removeListener (this);
	owner.getPanelTree().removeChild (getPanelEditorTree(), 0);
	ctrlrComponentSelection->removeChangeListener (ctrlrPanelProperties);
	masterReference.clear();
    deleteAndZero (ctrlrPanelProperties);
    deleteAndZero (spacerComponent);
    deleteAndZero (ctrlrPanelViewport);
}

void CtrlrPanelEditor::visibilityChanged()
{
}

void CtrlrPanelEditor::paint (Graphics& g)
{
	drawDefaultWindowBackground (g,getWidth(),getHeight());
}

void CtrlrPanelEditor::resized()
{
	midiToolbar.setBounds (0, 0, getWidth(), CTRLR_TOOLBAR_HEIGHT);

	if (!midiToolbar.isVisible())
	{
		ctrlrPanelViewport->setBounds 	(0, 				0, 	getWidth() - 308, 	getHeight());
		ctrlrPanelProperties->setBounds (getWidth() - 300, 	0, 	300, 				getHeight());
		spacerComponent->setBounds 		(getWidth(), 		0, 	8, 					getHeight());
	}
	else
	{
		ctrlrPanelViewport->setBounds 	(0, 				CTRLR_TOOLBAR_HEIGHT, getWidth() - 308, getHeight() - CTRLR_TOOLBAR_HEIGHT);
		ctrlrPanelProperties->setBounds (getWidth() - 300, 	CTRLR_TOOLBAR_HEIGHT, 300, 				getHeight() - CTRLR_TOOLBAR_HEIGHT);
		spacerComponent->setBounds 		(getWidth(), 		CTRLR_TOOLBAR_HEIGHT, 8, 				getHeight() - CTRLR_TOOLBAR_HEIGHT);
	}

	if (ctrlrPanelNotifier)
	{
		ctrlrPanelNotifier->setBounds (16, getHeight() - 28, getWidth() - 32, 20);
	}

	layoutItems();

	if (!getRestoreState())
	{
		saveLayout();
	}
}

CtrlrComponentSelection *CtrlrPanelEditor::getSelection()
{
    return (ctrlrComponentSelection);
}

void CtrlrPanelEditor::layoutItems()
{
	if (getProperty(Ids::uiPanelEditMode))
	{
		if (getProperty(Ids::uiPanelPropertiesOnRight))
		{
			Component* comps[] = { ctrlrPanelProperties, spacerComponent, ctrlrPanelViewport  };
			layoutManager.layOutComponents (comps, 3, 0, midiToolbar.isVisible() ? CTRLR_TOOLBAR_HEIGHT : 0, getWidth(), getHeight() - (midiToolbar.isVisible() ? CTRLR_TOOLBAR_HEIGHT : 0), false, true);
		}
		else
		{
			Component* comps[] = { ctrlrPanelViewport, spacerComponent, ctrlrPanelProperties  };
			layoutManager.layOutComponents (comps, 3, 0, midiToolbar.isVisible() ? CTRLR_TOOLBAR_HEIGHT : 0, getWidth(), getHeight() - (midiToolbar.isVisible() ? CTRLR_TOOLBAR_HEIGHT : 0), false, true);
		}
	}
	else
	{
		layoutManager.layOutComponents (editorComponents, 1, 0, midiToolbar.isVisible() ? CTRLR_TOOLBAR_HEIGHT : 0, getWidth(), getHeight() - (midiToolbar.isVisible() ? CTRLR_TOOLBAR_HEIGHT : 0), false, true);
	}
}

void CtrlrPanelEditor::saveLayout()
{
	setProperty (Ids::uiPanelViewPortSize, layoutManager.getItemCurrentAbsoluteSize(0));
	setProperty (Ids::uiPanelPropertiesSize, layoutManager.getItemCurrentAbsoluteSize(2));
}

CtrlrPanelCanvas *CtrlrPanelEditor::getCanvas()
{
	if (ctrlrPanelViewport != 0)
	{
		return (ctrlrPanelViewport->getCanvas());
	}

	return (0);
}

void CtrlrPanelEditor::editModeChanged()
{
	const bool editMode = getProperty(Ids::uiPanelEditMode);
	owner.editModeChanged(editMode);

	if (editMode)
	{
		layoutManager.setItemLayout (0, -0.001, -1.0, getProperty(Ids::uiPanelViewPortSize, -0.8));
		layoutManager.setItemLayout (2, -0.001, -1.0, getProperty(Ids::uiPanelPropertiesSize, -0.2));
		spacerComponent->setVisible (true);
		ctrlrPanelProperties->setVisible (true);
		getCanvas()->getResizableBorder()->setVisible(true);

		if ((bool)getProperty (Ids::uiPanelDisableCombosOnEdit))
			setAllCombosDisabled();
	}
	else
	{
        if (getSelection())

            getSelection()->deselectAll();
		spacerComponent->setVisible (false);
		ctrlrPanelProperties->setVisible (false);
		getCanvas()->getResizableBorder()->setVisible(false);

		if ((bool)getProperty (Ids::uiPanelDisableCombosOnEdit))
			setAllCombosEnabled();
	}

	resized();
}

void CtrlrPanelEditor::setAllCombosDisabled()
{
	OwnedArray <CtrlrModulator, CriticalSection> &mods = owner.getModulators();
	for (int i=0; i<mods.size(); i++)
	{
		CtrlrCombo *cc = dynamic_cast<CtrlrCombo*>(mods[i]->getComponent());
		if (cc != nullptr)
		{
			cc->setEnabled (false);
		}
	}
}

void CtrlrPanelEditor::setAllCombosEnabled()
{
	OwnedArray <CtrlrModulator, CriticalSection> &mods = owner.getModulators();
	for (int i=0; i<mods.size(); i++)
	{
		CtrlrCombo *cc = dynamic_cast<CtrlrCombo*>(mods[i]->getComponent());
		if (cc != nullptr)
		{
			cc->setEnabled (true);
		}
	}
}

void CtrlrPanelEditor::restoreState(const ValueTree &savedState)
{
	setRestoreState(true);

	restoreProperties (savedState.getChildWithName(Ids::uiPanelEditor), panelEditorTree, 0);
	getCanvas()->restoreState (savedState);

    if (getSelection())
        getSelection()->sendChangeMessage();

	if (owner.getOwner().getInstanceMode() == InstanceSingle || owner.getOwner().getInstanceMode() == InstanceSingleRestriced)
	{
		initSingleInstance();
	}

	editModeChanged();

	setRestoreState(false);
}

CtrlrComponent *CtrlrPanelEditor::getSelected(const Identifier &type)
{
    if (getSelection() == nullptr)
        return (nullptr);

	if (getSelection()->getNumSelected() == 1)
	{
		if (CtrlrComponentTypeManager::findType(getSelection()->getSelectedItem(0)) == type)
		{
			return (getSelection()->getSelectedItem(0));
		}
	}

	return (0);
}

void CtrlrPanelEditor::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (treeWhosePropertyHasChanged.hasType(Ids::uiPanelEditor))
	{
		if (property == Ids::uiPanelEditMode)
		{
			editModeChanged();
		}
		else if (property == Ids::uiPanelSnapSize)
		{
			repaint();
		}
		else if (property == Ids::name)
		{
			Component::setName (getProperty(Ids::name));
		}
		else if (property == Ids::uiPanelPropertiesOnRight)
		{
			ctrlrPanelProperties->layoutChanged();

			if (!owner.getOwner().isRestoring())
			{
				resized();
			}
		}
		else if (property == Ids::uiPanelMidiToolbarVisible)
		{
			midiToolbar.setVisible ((bool)getProperty(property));
			resized();
		}
		else if (property == Ids::uiPanelDisableCombosOnEdit)
		{
			if ((bool)getProperty(property) && getMode())
			{
				setAllCombosDisabled();
			}
			else
			{
				setAllCombosEnabled();
			}
		}
		else if (property == Ids::uiPanelZoom)
		{
			getPanelViewport()->setZoom (getProperty(property), getCanvas()->getBounds().getCentre().getX(), getCanvas()->getBounds().getCentre().getY());
		}
		else if (property == Ids::uiPanelBackgroundGradientType
					|| property == Ids::uiPanelBackgroundColour1
					|| property == Ids::uiPanelBackgroundColour2
					|| property == Ids::uiPanelBackgroundColour
					)
		{
			repaint();
		}
	}
}

const var &CtrlrPanelEditor::getProperty (const Identifier& name) const
{
	return (panelEditorTree.getProperty (name));
}

const var CtrlrPanelEditor::getProperty (const Identifier& name, const var &defaultReturnValue) const
{
	return (panelEditorTree.getProperty (name, defaultReturnValue));
}

void CtrlrPanelEditor::setProperty (const Identifier& name, const var &newValue, const bool isUndoable)
{
	panelEditorTree.setProperty (name, newValue, 0);
}

const bool CtrlrPanelEditor::getMode()
{
	return (getProperty (Ids::uiPanelEditMode));
}

AffineTransform CtrlrPanelEditor::moveSelectionToPosition(const int newX, const int newY)
{
    if (getSelection() == nullptr)
        return (AffineTransform::identity);

	RectangleList <int>rectangleList;

	for (int i=0; i<getSelection()->getNumSelected(); i++)
	{
		CtrlrComponent *c = getSelection()->getSelectedItem(i);
		rectangleList.add (c->getBounds());
	}

	RectanglePlacement rp(RectanglePlacement::xLeft);
	return (rp.getTransformToFit (rectangleList.getBounds().toFloat(), rectangleList.getBounds().withPosition(newX, newY).toFloat()));
}

void CtrlrPanelEditor::initSingleInstance()
{
	owner.setProperty (Ids::uiPanelEditMode, false);
}

void CtrlrPanelEditor::notify(const String &notification, CtrlrNotificationCallback *callback, const CtrlrNotificationType ctrlrNotificationType)
{
	if (ctrlrPanelNotifier)
	{
		if ((int)owner.getProperty(Ids::panelMessageTime) <= 0)
			return;

		notificationCallback = callback;

		componentAnimator.cancelAllAnimations (true);
		ctrlrPanelNotifier->setVisible (true);
		if (notificationCallback != nullptr)
		{
			ctrlrPanelNotifier->setMouseCursor (MouseCursor::PointingHandCursor);
		}
		else
		{
			ctrlrPanelNotifier->setMouseCursor (MouseCursor::NormalCursor);
		}
		ctrlrPanelNotifier->setBounds (16, getHeight() - 28, getWidth() - 32, 20);
		ctrlrPanelNotifier->setAlpha (1.0f);

		ctrlrPanelNotifier->setNotification (notification, ctrlrNotificationType);

		componentAnimator.animateComponent (ctrlrPanelNotifier, ctrlrPanelNotifier->getBounds(), 0.0f, owner.getProperty(Ids::panelMessageTime), false, 1.0, 1.0);
	}
}

void CtrlrPanelEditor::notificationClicked(const MouseEvent e)
{
	componentAnimator.cancelAllAnimations (true);

	if (!notificationCallback.wasObjectDeleted() && notificationCallback)
	{
		notificationCallback->notificationClicked(e);
	}
}

void CtrlrPanelEditor::changeListenerCallback (ChangeBroadcaster *source)
{
	if (source == &componentAnimator)
	{
		if (!componentAnimator.isAnimating())
		{
			ctrlrPanelNotifier->setVisible (false);
		}
	}
}

void CtrlrPanelEditor::toggleMIDIToolbar()
{
	setProperty (Ids::uiPanelMidiToolbarVisible, !getProperty(Ids::uiPanelMidiToolbarVisible));
}

void CtrlrPanelEditor::reloadResources (Array <CtrlrPanelResource*> resourcesThatChanged)
{
	if (resourcesThatChanged.size() > 1)
	{
		notify("Reloaded ["+STR(resourcesThatChanged.size())+"] resources", nullptr);
	}
	else if (resourcesThatChanged.size() == 1)
	{
		notify("Reloaded resource: "+resourcesThatChanged[0]->getName()+" from file: "+resourcesThatChanged[0]->getSourceFile().getFullPathName(), nullptr);
	}

	for (int i=0; i<owner.getNumModulators(); i++)
	{
		if (owner.getModulatorByIndex (i)->getComponent())
		{
			owner.getModulatorByIndex (i)->getComponent()->reloadResources(resourcesThatChanged);
		}
	}

	resized();
}
