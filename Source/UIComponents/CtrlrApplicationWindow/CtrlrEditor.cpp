#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrMIDILibrary/CtrlrMIDILibrary.h"
#include "CtrlrLog.h"
#include "CtrlrEditor.h"
#include "CtrlrProcessor.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrLookAndFeel.h"

CtrlrEditor::CtrlrEditor (CtrlrProcessor *_ownerFilter, CtrlrManager &_owner)
	: AudioProcessorEditor (_ownerFilter), ownerFilter(_ownerFilter), owner(_owner), resizer(this, 0), tempResult(Result::ok()), menuHandlerCalled(false)
{
    // http://www.juce.com/forum/topic/applicationcommandmanager-menus-not-active-annoyance#new
    owner.getCommandManager().setFirstCommandTarget (this);

	addAndMakeVisible (menuBar = new MenuBarComponent (this));
	menuBarLookAndFeel = new CtrlrMenuBarLookAndFeel (*this);

	setApplicationCommandManagerToWatch (&owner.getCommandManager());

	owner.getCommandManager().registerAllCommandsForTarget (this);
	owner.getCommandManager().registerAllCommandsForTarget (JUCEApplication::getInstance());
	ScopedPointer <XmlElement> xml(XmlDocument::parse(owner.getProperty(Ids::ctrlrKeyboardMapping)));

	if (xml)
	{
		owner.getCommandManager().getKeyMappings()->restoreFromXml (*xml);
	}

	owner.setEditor (this);

	addAndMakeVisible (&owner.getCtrlrDocumentPanel());

	if (!JUCEApplication::isStandaloneApp())
	{
		addAndMakeVisible (&resizer);
		resizer.setAlwaysOnTop (false);
		resizer.grabKeyboardFocus();
		resizer.toFront (true);
	}

	if (owner.getProperty (Ids::ctrlrEditorBounds).toString() != String::empty)
	{
		setBounds (VAR2RECT(owner.getProperty (Ids::ctrlrEditorBounds)));
	}
	else
	{
		setSize (640, 480);
	}

	initTest();

	lookAndFeelChanged();
	activeCtrlrChanged();
}

CtrlrEditor::~CtrlrEditor()
{
	deleteAndZero (menuBar);
	masterReference.clear();
}

void CtrlrEditor::paint (Graphics& g)
{
}

void CtrlrEditor::resized()
{
	menuBar->setBounds (0, 0, getWidth(), CTRLR_MENUBAR_HEIGHT);
	owner.getCtrlrDocumentPanel().setBounds (0, CTRLR_MENUBAR_HEIGHT, getWidth(), getHeight() - (CTRLR_MENUBAR_HEIGHT));
	owner.setProperty (Ids::ctrlrEditorBounds, getBounds().toString());
	resizer.setBounds (getWidth()-24, getHeight()-24, 24, 24);
}

void CtrlrEditor::activeCtrlrChanged()
{
	menuBarLookAndFeel->setPanel (owner.getActivePanel());
	if (owner.getActivePanel() && owner.getCtrlrLookAndFeel())
	{
		owner.getCtrlrLookAndFeel()->setActivePanelEditor (owner.getActivePanel()->getEditor());
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

const bool CtrlrEditor::isRestricted()
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

const bool CtrlrEditor::isPanelActive(const bool checkRestrictedInstance)
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

void CtrlrEditor::initTest()
{
	MemoryBlock r (BinaryData::CtrlrInstance_rsrc, BinaryData::CtrlrInstance_rsrcSize);
	const int dataStart = ByteOrder::bigEndianInt (r.getData());
	const int mapStart  = ByteOrder::bigEndianInt ((char *)r.getData() + 4);
	const int dataLen   = ByteOrder::bigEndianInt ((char *)r.getData() + 8);
	const int mapLen    = ByteOrder::bigEndianInt ((char *)r.getData() + 12);

	const int nameLen   = ByteOrder::bigEndianInt ((void *)&r[dataStart]);

	const String name ( ((char *)r.getData() + dataStart + sizeof(int) + 1), dataLen);
	_DBG (String::formatted ("dataStart: %d mapStart %d dataLen: %d mapLen: %d nameLen: %d", dataStart, mapStart, dataLen, mapLen, nameLen));
	_DBG("name: \""+name+"\"");
}
