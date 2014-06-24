#include "stdafx.h"
#include "CtrlrPanelResourceManager.h"
#include "CtrlrPanelResource.h"
#include "CtrlrMacros.h"
#include "CtrlrProcessor.h"
#include "CtrlrPanel.h"
#include "CtrlrUtilities.h"
#include "CtrlrLog.h"

/** Resource Manager class implementation

*/

CtrlrPanelResourceManager::CtrlrPanelResourceManager(CtrlrPanel &_owner)
	: owner(_owner), lastLoadedResource(nullptr), managerTree(Ids::panelResources)
{
}

CtrlrPanelResourceManager::~CtrlrPanelResourceManager()
{
}

void CtrlrPanelResourceManager::panelUIDChanged()
{
	initManager();
}

void CtrlrPanelResourceManager::restoreSavedState (const ValueTree &savedState)
{
	// _DBG("CtrlrPanelResourceManager::restoreSavedState");
	// _DBG(dumpTree(savedState));

	for (int i=0; i<savedState.getNumChildren(); i++)
	{
		if (savedState.getChild(i).hasType(Ids::resource))
		{
			CtrlrPanelResource *res = getResource(savedState.getChild(i).getProperty(Ids::resourceName).toString());
			if (res)
			{
				res->setProperty (Ids::resourceSourceFile, savedState.getChild(i).getProperty(Ids::resourceSourceFile));
			}
		}
	}
}

void CtrlrPanelResourceManager::initManager()
{
	{
		resources.clear();
		resourceHashCodes.clear();
		lastLoadedResource = nullptr;
	}

	const File newResourcesDirectory = owner.getPanelDirectory();

	if (newResourcesDirectory != resourcesDirectory && resourcesDirectory != File::nonexistent)
	{
		if (resourcesDirectory.getNumberOfChildFiles (File::findFiles) == 0)
		{
			resourcesDirectory.deleteRecursively();
		}
		else
		{
			if (SURE("The resource directory has changed, do you want to delete the old one?",nullptr))
			{
				resourcesDirectory.deleteRecursively ();
			}
		}
	}

	resourcesDirectory = newResourcesDirectory;

	if (!resourcesDirectory.isDirectory())
	{
		if (!resourcesDirectory.createDirectory())
		{
			_ERR("CtrlrResourceManager::ctor failed to create resources directory");
			resourcesDirectory = File::nonexistent;
		}
	}
	else
	{
		Array <File> resourceFiles;
		resourcesDirectory.findChildFiles (resourceFiles, File::findFiles, false);
		for (int i=0; i<resourceFiles.size(); i++)
		{
			addResource (resourceFiles[i]);
		}
	}
}

int CtrlrPanelResourceManager::getNumResources()
{
	return (resources.size());
}

CtrlrPanelResource *CtrlrPanelResourceManager::getResource (const int resourceIndex)
{
	return (resources[resourceIndex]);
}

CtrlrPanelResource *CtrlrPanelResourceManager::getResource (const String &resourceName)
{
	if (lastLoadedResource.get() && !lastLoadedResource.wasObjectDeleted())
		if (lastLoadedResource->getName() == resourceName)
			return (lastLoadedResource);

	for (int i=0; i<resources.size(); i++)
	{
		if (resources[i]->getName() == resourceName)
		{
			lastLoadedResource = resources[i];
			return (resources[i]);
		}
	}
	return (0);
}

const Image CtrlrPanelResourceManager::getResourceAsImage (const String &resourceName)
{
	CtrlrPanelResource *res = getResource (resourceName);
	if (res != 0)
	{
		return (res->asImage());
	}

	return (Image::null);
}

void CtrlrPanelResourceManager::reloadComboContents (ComboBox &comboToUpdate)
{
	const String lastSelected	= comboToUpdate.getText();
	int newSelectedId			= -1;
	int i=0;

	comboToUpdate.clear();

	for (i=0; i<resources.size(); i++)
	{
		comboToUpdate.addItem (resources[i]->getName(), i+1);
		if (lastSelected == resources[i]->getName())
		{
			newSelectedId = i+1;
		}
	}

	comboToUpdate.addItem (COMBO_NONE_ITEM, i+1);

	comboToUpdate.setSelectedId (newSelectedId, dontSendNotification);
}

CtrlrPanel &CtrlrPanelResourceManager::getOwner()
{
	return (owner);
}

const int CtrlrPanelResourceManager::getHashCode (const String &resourceName, const bool preloadResource)
{
	CtrlrPanelResource *r = getResource(resourceName);

	if (r)
	{
		if (preloadResource)
			r->load();

		return (r->getHashCode());
	}

	return (-1);
}

const int CtrlrPanelResourceManager::getResourceIndex (const String &resourceName)
{
	for (int i=0; i<resources.size(); i++)
	{
		if (resources[i]->getName() == resourceName)
			return (i);
	}
	return (-1);
}

const bool CtrlrPanelResourceManager::resourceExists(const File &resourceFile)
{
	if (getResource (resourceFile.getFileNameWithoutExtension()))
	{
		return (true);
	}

	return (false);
}

Result CtrlrPanelResourceManager::importResource (const ValueTree &resourceTree)
{
	if (getResource(resourceTree.getProperty(Ids::resourceName).toString()))
	{
		if ((bool)owner.getOwner().getProperty(Ids::ctrlrOverwriteResources) == false)
		{
			return (Result::fail("ImportResource resource: " + resourceTree.getProperty(Ids::resourceName).toString() + "failed, a resource with this name already exists"));
		}
		else
		{
			return (Result::ok());
		}
	}
	else
	{
		File resourceTempFile = File::getCurrentWorkingDirectory().getChildFile(resourceTree.getProperty(Ids::resourceFile).toString());
		File resourceDest = resourcesDirectory.getChildFile(resourceTempFile.getFileName());

		if (resourcesDirectory.isDirectory())
		{
			MemoryBlock resourceData;
			if (resourceData.fromBase64Encoding (resourceTree.getProperty(Ids::resourceData).toString()))
			{
				if (!resourceDest.exists())
				{
					resourceDest.create();
				}

				if (!resourceDest.replaceWithData(resourceData.getData(), (int)resourceData.getSize()))
				{
					return (Result::fail("ImportResource can't replace file contents with new data, resource: "+resourceDest.getFullPathName()));
				}

				// resources.add (new CtrlrPanelResource (*this, resourceDest, File (resourceTree.getProperty(Ids::resourceSourceFile)), resourceTree.getProperty(Ids::resourceName)));
				// resourceHashCodes.add (resources.getLast()->getHashCode());

				addResource (resourceDest, resourceTree.getProperty(Ids::resourceName));
				return (Result::ok());
			}
			else
			{
				resourceDest.deleteFile();
				return (Result::fail("ImportResource resource: " + resourceTree.getProperty(Ids::resourceName).toString() + " failed to decode base64 encoded data"));
			}
		}
		else
		{
			return (Result::fail("Import resource failed, the path specified as the resource directory is not one:"+resourcesDirectory.getFullPathName()));
		}
	}
}

Result CtrlrPanelResourceManager::addResource (const File &source, const String &name)
{
	// _DBG("CtrlrPanelResourceManager::addResource");

	if ((bool)owner.getOwner().getProperty(Ids::ctrlrOverwriteResources) == false)
	{
		if (getResource (source.getFileNameWithoutExtension()))
		{
			return (Result::fail("This resource already exists"));
		}
	}

	File resourceDest = resourcesDirectory.getChildFile(source.getFileName());

	if (resourcesDirectory.isDirectory())
	{
		source.copyFileTo (resourceDest);
	}
	else
	{
		return (Result::fail("Can't copy resource to resources directory:"+resourcesDirectory.getFullPathName()));
	}

	{
		CtrlrPanelResource *newResource = new CtrlrPanelResource (*this, resourceDest, source, name);

		resources.add (newResource);
		resourceHashCodes.add (newResource->getHashCode());
		managerTree.addChild (newResource->getResourceTree(), -1, nullptr);
	}

	return (Result::ok());
}

Result CtrlrPanelResourceManager::removeResource(CtrlrPanelResource *resourceToRemove)
{
	return (removeResource (resources.indexOf(resourceToRemove)));
}

Result CtrlrPanelResourceManager::removeResource (const int resourceIndex)
{
	CtrlrPanelResource *res = resources[resourceIndex];

	if (res)
	{
		resourceHashCodes.removeAllInstancesOf (resources[resourceIndex]->getHashCode());
		if (!resources[resourceIndex]->getFile().deleteFile())
		{
			return (Result::fail("Removing resource partialy failed, can't delete resource file:"+resources[resourceIndex]->getFile().getFullPathName()));
		}

		managerTree.removeChild (resources[resourceIndex]->getResourceTree(),nullptr);
		resources.remove (resourceIndex, true);

		return (Result::ok());
	}
	else
	{
		return (Result::fail("Unable to remove result with index:"+STR(resourceIndex)));
	}
}

Result CtrlrPanelResourceManager::removeResourceRange (const int resourceIndexStart, const int numberOfResourcesToRemove)
{
	for (int i=resourceIndexStart; i<resourceIndexStart+numberOfResourcesToRemove; i++)
	{
		if (resources[i])
		{
			Result ret = removeResource (i);

			if (!ret.wasOk())
			{
				return (ret);
			}
		}
	}

	return (Result::ok());
}

void CtrlrPanelResourceManager::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrPanelResource>("CtrlrPanelResource")
			.def("asImage", &CtrlrPanelResource::asImage)
			.def("asText", &CtrlrPanelResource::asText)
			.def("asFont", &CtrlrPanelResource::asFont)
			.def("asXml", &CtrlrPanelResource::asXml)
			.def("asAudioFormat", &CtrlrPanelResource::asAudioFormat)
			.def("asData", &CtrlrPanelResource::asData)
			.def("getName", &CtrlrPanelResource::getName)
			.def("getSize", (double (CtrlrPanelResource::*)() )&CtrlrPanelResource::getSize)
			.def("getHashCode", &CtrlrPanelResource::getHashCode)
			.def("load", &CtrlrPanelResource::load)
			.def("loadIfNeeded", &CtrlrPanelResource::loadIfNeeded)
			.def("getType", &CtrlrPanelResource::getType)
			.def("getTypeDescription", &CtrlrPanelResource::getTypeDescription)
			.def("getFile", &CtrlrPanelResource::getFile)
		,
		class_<CtrlrPanelResourceManager>("CtrlrPanelResourceManager")
			.def("getResource", (CtrlrPanelResource *(CtrlrPanelResourceManager::*)(const int))&CtrlrPanelResourceManager::getResource)
			.def("getResource", (CtrlrPanelResource *(CtrlrPanelResourceManager::*)(const String &))&CtrlrPanelResourceManager::getResource)
			.def("getNumResources", &CtrlrPanelResourceManager::getNumResources)
			.def("getResourceIndex", &CtrlrPanelResourceManager::getResourceIndex)
			.def("getResourceAsImage", &CtrlrPanelResourceManager::getResourceAsImage)
	];
}

const String CtrlrPanelResourceManager::getTypeDescription(const CtrlrPanelResourceType type)
{
	switch (type)
	{
		case ImageRes:
			return ("Image");
		case AudioRes:
			return ("Audio");
		case FontRes:
			return ("Font");
		case TextRes:
			return ("Text");
		case XmlRes:
			return ("Xml");
		case DataRes:
		default:
			return ("Data");
	}
}

const CtrlrPanelResourceManager::CtrlrPanelResourceType CtrlrPanelResourceManager::guessType(const File &resourceFile)
{
	// Image ?
	Image image = ImageCache::getFromFile (resourceFile);

	if (!image.isNull())
	{
		return (ImageRes);
	}

	// Audio ?
	ScopedPointer <AudioFormatReader> audio(owner.getOwner().getAudioFormatManager().createReaderFor(resourceFile));

	if (audio != nullptr)
	{
		return (AudioRes);
	}

	// Font ?
	if (resourceFile.hasFileExtension("ttf") || resourceFile.hasFileExtension("otf"))
	{
		return (FontRes);
	}

	// XML ?
	ScopedPointer <XmlElement> xml (XmlDocument::parse (resourceFile));

	if (xml != nullptr)
	{
		return (XmlRes);
	}

	// Text ?

	if (resourceFile.hasFileExtension ("txt"))
	{
		return (TextRes);
	}

	return (DataRes);
}

const int CtrlrPanelResourceManager::getResourceHashCode(const int resourceIndex)
{
	if (resources[resourceIndex])
	{
		return (resources[resourceIndex]->getHashCode());
	}

	return (-1);
}

const int CtrlrPanelResourceManager::getResourceIndexByHashCode(const int hashCode)
{
	for (int i=0; i<resources.size(); i++)
	{
		if (resources[i])
		{
			if (resources[i]->getHashCode() == hashCode)
				return (i);
		}
	}

	return (-1);
}

Result CtrlrPanelResourceManager::restoreState (const ValueTree &savedState)
{
	for (int i=0; i<savedState.getNumChildren(); i++)
	{
		if (savedState.getChild(i).hasType(Ids::resourceLicense))
		{
			AlertWindow licenseWindow("License agreement", "You must agree to the below license", AlertWindow::QuestionIcon);
			TextEditor licenseText;
			licenseText.setMultiLine(true);
			licenseText.setReadOnly(true);
			licenseText.setText (savedState.getChild(i).getProperty(Ids::resourceData));
			licenseText.setSize (500,400);
			licenseWindow.addCustomComponent (&licenseText);
			licenseWindow.addButton ("Yes", 1);
			licenseWindow.addButton ("No", 0);
			if (!licenseWindow.runModalLoop())
			{
				return (Result::fail("User did not agree to embedded license"));
			}
		}

		if (savedState.getChild(i).hasType(Ids::resourceBlob) || savedState.getChild(i).hasType(Ids::resourceImage) || savedState.getChild(i).hasType(Ids::resource))
		{
			Result importResult = importResource (savedState.getChild(i));
			if (!importResult.wasOk())
			{
				if (owner.getDialogStatus())
					WARN(importResult.getErrorMessage());
				else
					_WRN(importResult.getErrorMessage());
			}
		}
	}

	return (Result::ok());
}

Array <CtrlrPanelResource*> CtrlrPanelResourceManager::getResourcesCopy()
{
	Array <CtrlrPanelResource*> ret;
	for (int i=0; i<resources.size(); i++)
	{
		ret.add (resources[i]);
	}
	return (ret);
}
