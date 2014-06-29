#include "stdafx.h"
#include "CtrlrManager.h"
#include "CtrlrProperties.h"
#include "CtrlrPanel/CtrlrPanel.h"

void CtrlrManager::setEmbeddedDefaults()
{
	_DBG("CtrlrManager::setEmbeddedDefaults");

	/* first init the ApplicationProperties stuff */
	if (ctrlrPlayerInstanceTree.hasProperty(Ids::restricted))
	{
		ctrlrPlayerInstanceMode	= (CtrlrInstance)(int)ctrlrPlayerInstanceTree.getProperty(Ids::restricted);
	}
	else
	{
		ctrlrPlayerInstanceMode = InstanceSingle;
	}

	ctrlrProperties			= new CtrlrProperties (*this);

	setProperty (Ids::ctrlrLogToFile, false);
	setProperty (Ids::ctrlrLuaDebug, false);
	setProperty (Ids::ctrlrVersionSeparator, "_");
	setProperty (Ids::ctrlrVersionCompressed, false);
	setProperty (Ids::ctrlrMidiMonInputBufferSize, 8192);
	setProperty (Ids::ctrlrMidiMonOutputBufferSize, 8192);
	setProperty (Ids::ctrlrLuaDisabled, false);
	setProperty (Ids::ctrlrOverwriteResources, true);
	setProperty (Ids::ctrlrAutoSave, true);
	setProperty (Ids::ctrlrAutoSaveInterval, 300);
	setProperty (Ids::ctrlrLogOptions, 32);
	setProperty (Ids::ctrlrUseEditorWrapper, (bool)ctrlrPlayerInstanceTree.hasProperty(Ids::ctrlrUseEditorWrapper) ? (bool)ctrlrPlayerInstanceTree.getProperty(Ids::ctrlrUseEditorWrapper) : true);
	setProperty (Ids::uiLuaConsoleInputRemoveAfterRun, true);
}

Result CtrlrManager::initEmbeddedInstance()
{
	ctrlrNativeObject	= CtrlrNative::getNativeObject();

	if (ctrlrNativeObject)
	{
		MemoryBlock defaultPanelData;

		if (ctrlrNativeObject->getDefaultPanel (defaultPanelData))
		{
			ctrlrPlayerInstanceTree = ValueTree::readFromGZIPData (defaultPanelData.getData(), defaultPanelData.getSize());

			if (ctrlrPlayerInstanceTree.isValid())
			{
				/* Set any defaults we need **/
				setEmbeddedDefaults();

				/* Look at the resources, see if
					we need to import them **/
				Result result = importInstanceResources(ctrlrNativeObject);

				if (result.wasOk())
				{
					/** We need to load the panel here
						but make sure the VST manager is
						done and that the restore state
						will give us only the program for
						the panel **/

					return (addInstancePanel());
				}
				else
				{
					return (result);
				}
			}
			else
			{
				return (Result::fail("InitEmbeddedInstance instance data is invalid"));
			}
		}
	}

	return (Result::fail("InitEmbeddedInstance failed to initialize the OS Native object"));
}

const String CtrlrManager::getInstanceNameForHost() const
{
	if (getInstanceMode() == InstanceSingle
        || getInstanceMode() == InstanceSingleRestriced)
	{
		return (ctrlrPlayerInstanceTree.getProperty(Ids::name).toString() + "|" + ctrlrPlayerInstanceTree.getProperty(Ids::panelAuthorName).toString());
	}
	else
	{
		return ("Ctrlr|Instigator");
	}
}

const String CtrlrManager::getInstanceName() const
{
	if (getInstanceMode() == InstanceSingle
        || getInstanceMode() == InstanceSingleRestriced)
	{
		return (ctrlrPlayerInstanceTree.getProperty(Ids::name));
	}
	else
	{
		return ("Ctrlr");
	}
}

Result CtrlrManager::addInstancePanel()
{
	if (ctrlrPlayerInstanceTree.isValid())
	{
		CtrlrPanel *panel = new CtrlrPanel(*this, getInstanceName(), ctrlrPanels.size());
		ctrlrPanels.add (panel);

		Result restoreResult = panel->restoreState (ctrlrPlayerInstanceTree);

		if (!restoreResult.wasOk())
		{
			WARN("AddInstancePanel failed to restore the state of the panel");
			ctrlrPanels.clear (true);
			return (restoreResult);
		}

		managerTree.addChild (panel->getPanelTree(), -1, 0);
		addPanel (panel->getEditor(true));

		organizePanels();

		return (Result::ok());
	}
	else
	{
		return (Result::fail("AddInstancePanel failed, the decoded instance tree is invalid"));
	}
}

Result CtrlrManager::importInstanceResources(CtrlrNative *native)
{
	if (getCtrlrProperties().getProperties().getUserSettings())
	{
		if (getCtrlrProperties().getProperties().getUserSettings()->getFile().getParentDirectory().getChildFile(".delete_me_to_reload_resources").existsAsFile())
		{
			return (Result::ok());
		}
		else
		{
			getCtrlrProperties().getProperties().getUserSettings()->getFile().getParentDirectory().getChildFile(".delete_me_to_reload_resources").create();
		}
	}

	MemoryBlock resourcesData;
	Result resourceFetch = native->getDefaultResources (resourcesData);

	if (resourceFetch.failed())
	{
		return (Result::fail("ImportInstanceResources getDefaultResources() failed"));
	}

	ctrlrPlayerInstanceResources = ValueTree::readFromGZIPData(resourcesData.getData(), resourcesData.getSize());

	if (ctrlrPlayerInstanceResources.isValid())
	{
		return (Result::ok());
	}
	else
	{
		return (Result::fail("ImportInstanceResources got some data but couldn't understand it"));
	}
}

void CtrlrManager::restoreInstanceState(const ValueTree &instanceState)
{
	if (ctrlrEditor)
	{
		restoreEditorState();
	}

	getActivePanel()->setInstanceProperties (instanceState);
	getActivePanel()->setProgram (instanceState);

	ctrlrManagerRestoring = false;
}

const CtrlrInstance CtrlrManager::getInstanceMode() const
{
	return (ctrlrPlayerInstanceMode);
}

XmlElement *CtrlrManager::saveState()
{
	if (getInstanceMode() == InstanceMulti)
	{
		return (managerTree.createXml());
	}
	else
	{
		if (getActivePanel())
		{
			ValueTree program = getActivePanel()->getProgram();
			restoreProperties (managerTree, program);
			restoreProperties (getActivePanel()->getPanelTree(), program, 0, "panelMidi");
			return (program.createXml());
		}
		return (nullptr);
	}
}

ValueTree &CtrlrManager::getInstanceTree()
{
	return (ctrlrPlayerInstanceTree);
}

ValueTree &CtrlrManager::getInstanceResourcesTree()
{
	return (ctrlrPlayerInstanceResources);
}
