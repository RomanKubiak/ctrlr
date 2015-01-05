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
    lastCommandInvocationMillis = Time::getCurrentTime().toMilliseconds();
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

void CtrlrEditor::initTest()
{
}

static const char* openGLRendererName = "OpenGL Renderer";

StringArray CtrlrEditor::getRenderingEngines() const
{
    StringArray renderingEngines;

    if (ComponentPeer* peer = getPeer())
        renderingEngines = peer->getAvailableRenderingEngines();

   #if JUCE_OPENGL
    renderingEngines.add (openGLRendererName);
   #endif

    return renderingEngines;
}

void CtrlrEditor::setRenderingEngine (int index)
{
   #if JUCE_OPENGL
    if (getRenderingEngines()[index] == openGLRendererName)
    {
        openGLContext.attachTo (*getTopLevelComponent());
        return;
    }

    openGLContext.detach();
   #endif

    if (ComponentPeer* peer = getPeer())
        peer->setCurrentRenderingEngine (index);
}

void CtrlrEditor::setOpenGLRenderingEngine()
{
    setRenderingEngine (getRenderingEngines().indexOf (openGLRendererName));
}

int CtrlrEditor::getActiveRenderingEngine() const
{
   #if JUCE_OPENGL
    if (openGLContext.isAttached())
        return getRenderingEngines().indexOf (openGLRendererName);
   #endif

    if (ComponentPeer* peer = getPeer())
        return peer->getCurrentRenderingEngine();

    return 0;
}

void CtrlrEditor::setUsingOpenGL(const bool isUsingOpenGL)
{
    if (isUsingOpenGL)
    {
        if (getRenderingEngines().contains(openGLRendererName))
        {
            setOpenGLRenderingEngine();
        }
    }
    else
    {
        setRenderingEngine (0);
    }
}
