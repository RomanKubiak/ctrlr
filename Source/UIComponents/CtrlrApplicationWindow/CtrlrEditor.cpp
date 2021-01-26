#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrLog.h"
#include "CtrlrEditor.h"
#include "CtrlrProcessor.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrInlineUtilitiesGUI.h"

CtrlrEditor::CtrlrEditor (CtrlrProcessor *_ownerFilter, CtrlrManager &_owner)
	:	AudioProcessorEditor (_ownerFilter), ownerFilter(_ownerFilter),
		owner(_owner), resizer(this, 0),
		tempResult(Result::ok()),
		menuHandlerCalled(false),
		lastCommandInvocationMillis(0)
{
    setColourScheme(gui::colourSchemeFromProperty(owner.getProperty(Ids::ctrlrColourScheme)));
	LookAndFeel::setDefaultLookAndFeel(this);
	Rectangle<int> editorRect;
    // http://www.juce.com/forum/topic/applicationcommandmanager-menus-not-active-annoyance#new
    owner.getCommandManager().setFirstCommandTarget (this);

	addAndMakeVisible (menuBar = new MenuBarComponent (this));
	// menuBarLookAndFeel = new CtrlrMenuBarLookAndFeel (*this);

	setApplicationCommandManagerToWatch (&owner.getCommandManager());

	owner.getCommandManager().registerAllCommandsForTarget (this);
	owner.getCommandManager().registerAllCommandsForTarget (JUCEApplication::getInstance());
	ScopedPointer <XmlElement> xml(XmlDocument::parse(owner.getProperty(Ids::ctrlrKeyboardMapping)).release());

	if (xml)
	{
		owner.getCommandManager().getKeyMappings()->restoreFromXml (*xml);
	}

	owner.setEditor (this);

	addAndMakeVisible (&owner.getCtrlrDocumentPanel());

	if (!JUCEApplication::isStandaloneApp())
	{
	    if (owner.getInstanceMode() != InstanceSingleRestriced)
        {
            /* Restricted instances don't get to be resizable */
            addAndMakeVisible (&resizer);
            resizer.setAlwaysOnTop (false);
            resizer.grabKeyboardFocus();
            resizer.toFront (true);
        }
	}

	if (owner.getProperty (Ids::ctrlrEditorBounds).toString() != "")
	{
		if (owner.getInstanceMode() != InstanceSingle
			&& owner.getInstanceMode() != InstanceSingleRestriced)
		{
			editorRect = VAR2RECT(owner.getProperty (Ids::ctrlrEditorBounds));
		}
		else if (owner.getActivePanel())
		{
			editorRect = VAR2RECT(owner.getActivePanel()->getEditor()->getProperty(Ids::uiPanelCanvasRectangle));

			if ((bool)owner.getActivePanel()->getEditor()->getProperty(Ids::uiPanelMenuBarVisible))
				editorRect.setHeight (editorRect.getHeight() + (int)owner.getProperty(Ids::ctrlrMenuBarHeight));
			else
				editorRect.setHeight (editorRect.getHeight());
		}

		setBounds (editorRect);
	}
	else
	{
		if (JUCEApplication::isStandaloneApp())
			centreWithSize(800, 600);
		else
			setSize(800, 600);
	}

    getLookAndFeel().setUsingNativeAlertWindows((bool)owner.getProperty(Ids::ctrlrNativeAlerts));
	lookAndFeelChanged();
	activeCtrlrChanged();

	if (isRestricted() && owner.getActivePanel())
	{
		hideProgramsMenu = owner.getActivePanel()->getEditor()->getProperty(Ids::uiPanelProgramsMenuHideOnExport);
		hideMidiControllerMenu = owner.getActivePanel()->getEditor()->getProperty(Ids::uiPanelMidiControllerMenuHideOnExport);
		hideMidiThruMenu = owner.getActivePanel()->getEditor()->getProperty(Ids::uiPanelMidiThruMenuHideOnExport);
		hideMidiChannelMenu = owner.getActivePanel()->getEditor()->getProperty(Ids::uiPanelMidiChannelMenuHideOnExport);
	}
}

CtrlrEditor::~CtrlrEditor()
{
	deleteAndZero (menuBar);
	masterReference.clear();
}

void CtrlrEditor::paint (Graphics& g)
{
    g.fillAll(Colours::lightgrey);
}

void CtrlrEditor::resized()
{
	if (menuBar->isVisible())
	{
		menuBar->setBounds (0, 0, getWidth(), (int)owner.getProperty(Ids::ctrlrMenuBarHeight));
		owner.getCtrlrDocumentPanel().setBounds (0, (int)owner.getProperty(Ids::ctrlrMenuBarHeight), getWidth(), getHeight() - ((int)owner.getProperty(Ids::ctrlrMenuBarHeight)));
	}
	else
	{
		owner.getCtrlrDocumentPanel().setBounds (0, 0, getWidth(), getHeight());
	}

	resizer.setBounds (getWidth()-24, getHeight()-24, 24, 24);
	owner.setProperty (Ids::ctrlrEditorBounds, getBounds().toString());
}

void CtrlrEditor::activeCtrlrChanged()
{
	ownerFilter->activePanelChanged();
	bool menuBarVisible = true;

	if (owner.getActivePanel() && owner.getActivePanel()->getEditor())
	{
		menuBarVisible = owner.getActivePanel()->getEditor()->getProperty(Ids::uiPanelMenuBarVisible);

		if (menuBarVisible != menuBar->isVisible())
		{
			setMenuBarVisible(menuBarVisible);
		}
	}
}

MenuBarComponent *CtrlrEditor::getMenuBar()
{
	return (menuBar);
}

CtrlrPanel *CtrlrEditor::getActivePanel()
{
	return (owner.getActivePanel());
}

bool CtrlrEditor::isRestricted()
{
	return (owner.getInstanceMode() == InstanceSingleRestriced);
}

CtrlrPanelEditor *CtrlrEditor::getActivePanelEditor()
{
	if (owner.getActivePanel())
	{
		return (owner.getActivePanel()->getEditor());
	}

	return (nullptr);
}

bool CtrlrEditor::isPanelActive(const bool checkRestrictedInstance)
{
	if (getActivePanel())
	{
		if (checkRestrictedInstance)
		{
			if (owner.getInstanceMode() == InstanceSingleRestriced)
			{
				return (false);
			}

			return (true);
		}
		else
		{
			return (true);
		}
	}

	return (false);
}

void CtrlrEditor::setMenuBarVisible(const bool shouldBeVisible)
{
	menuBar->setVisible (shouldBeVisible);
	resized();
}
