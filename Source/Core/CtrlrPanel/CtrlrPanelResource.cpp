#include "stdafx.h"
#include "CtrlrPanelResource.h"
#include "CtrlrPanelResourceManager.h"
#include "CtrlrMacros.h"
#include "CtrlrProcessor.h"
#include "CtrlrPanel.h"
#include "CtrlrUtilities.h"
#include "CtrlrLog.h"

/** Single resource representation

*/

CtrlrPanelResource::CtrlrPanelResource (CtrlrPanelResourceManager &_owner, const File &_resourceDataFile, const File &_resourceSourceFile, const String _resourceName)
	: 	resourceDataFile(_resourceDataFile),
		resourceHashCode(0),
		resourceLoaded(false),
		owner(_owner),
		resourceName(_resourceName),
		audioFormatReader(nullptr),
		resourceTree(Ids::resource)
{
	if (resourceName == String::empty)
	{
		resourceName = _resourceSourceFile.getFileNameWithoutExtension();
	}

	resourceHashCode	= _resourceSourceFile.hashCode();
	resourceType		= owner.guessType (_resourceSourceFile);

	load();

	setProperty (Ids::resourceFile, resourceDataFile.getFileName(), nullptr);
	setProperty (Ids::resourceSourceFile, _resourceSourceFile.getFullPathName(), nullptr);
	setProperty (Ids::resourceName, getName(), nullptr);
	setProperty (Ids::resourceSize, getSize(), nullptr);
	setProperty (Ids::resourceType, CtrlrPanelResourceManager::getTypeDescription(getType()), nullptr);

	resourceTree.addListener(this);
}

CtrlrPanelResource::~CtrlrPanelResource()
{
	resourceTree.removeListener (this);

	if (audioFormatReader)
		deleteAndZero (audioFormatReader);

	masterReference.clear();
}

void CtrlrPanelResource::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	// _DBG("CtrlrPanelResource::valueTreePropertyChanged");
	// _DBG("\t"+property.toString()+"="+getProperty(property).toString());
}

File &CtrlrPanelResource::getFile()
{
	return (resourceDataFile);
}

const int64 CtrlrPanelResource::getSize()
{
	return (resourceDataFile.getSize());
}

const double CtrlrPanelResource::getSizeDouble()
{
	return ((double)getSize());
}

const int64 CtrlrPanelResource::getHashCode()
{
	return (getProperty(Ids::resourceHash));
}

const String CtrlrPanelResource::getName()
{
	return (resourceName);
}

const Image CtrlrPanelResource::asImage()
{
	Image image;

	image = ImageCache::getFromHashCode(getHashCode());

	if (!image.isValid())
	{
		image = ImageFileFormat::loadFrom (resourceDataFile);
		ImageCache::addImageToCache (image, getHashCode());
	}

	return (image);
}

const String CtrlrPanelResource::asText()
{
	return (resourceDataFile.loadFileAsString());
}

const Font CtrlrPanelResource::asFont()
{
    MemoryBlock tempData;
    resourceDataFile.loadFileAsData (tempData);
    return (Font (Typeface::createSystemTypefaceFor (tempData.getData(), tempData.getSize())));
}

const XmlElement *CtrlrPanelResource::asXml()
{
	return (XmlDocument::parse(resourceDataFile));
}

AudioFormatReader *CtrlrPanelResource::asAudioFormat()
{
	if (audioFormatReader)
	{
		deleteAndZero (audioFormatReader);
	}

	audioFormatReader = owner.getOwner().getOwner().getAudioFormatManager().createReaderFor(resourceDataFile);
	return (audioFormatReader);
}

const MemoryBlock &CtrlrPanelResource::asData()
{
	loadIfNeeded();
	return (data);
}

const bool CtrlrPanelResource::isLoaded()
{
	return (resourceLoaded);
}

void CtrlrPanelResource::loadIfNeeded()
{
	if (!resourceLoaded)
		load();
}

void CtrlrPanelResource::calculateHash()
{
	setProperty (Ids::resourceHash, resourceDataFile.hashCode64() + resourceDataFile.getLastModificationTime().toMilliseconds());
}

void CtrlrPanelResource::load()
{
	calculateHash();

	if (resourceLoaded || resourceType == CtrlrPanelResourceManager::ImageRes)
	{
		// ImageCache deals with that
	}
	else if (resourceType == CtrlrPanelResourceManager::AudioRes
			|| resourceType == CtrlrPanelResourceManager::XmlRes
			|| resourceType == CtrlrPanelResourceManager::TextRes
			|| resourceType ==CtrlrPanelResourceManager::FontRes)
	{
		// We don't load theese types, they will be rad when accessed
	}
	else if (resourceType == CtrlrPanelResourceManager::DataRes)
	{
		// Theese types go into memory

		resourceDataFile.loadFileAsData (data);
	}

	setProperty (Ids::resourceLoadedTime, Time::getCurrentTime().toMilliseconds());
	setProperty (Ids::resourceSize, resourceDataFile.getSize());

	resourceLoaded = true;
}

Time CtrlrPanelResource::getLoadedTime()
{
	return (Time((int64)getProperty(Ids::resourceLoadedTime)));
}

ValueTree CtrlrPanelResource::createTree()
{
	ValueTree resourceTreeCopy;

	if (resourceDataFile.existsAsFile())
	{
		resourceTreeCopy = resourceTree.createCopy();

		if (data.getSize() != resourceDataFile.getSize())
			resourceDataFile.loadFileAsData (data);

		resourceTreeCopy.setProperty (Ids::resourceData, data.toBase64Encoding(), 0);
	}

	return (resourceTreeCopy);
}

const CtrlrPanelResourceManager::CtrlrPanelResourceType CtrlrPanelResource::getType()
{
	return (resourceType);
}

File CtrlrPanelResource::getSourceFile()
{
	return (File(getProperty(Ids::resourceSourceFile)));
}

const String CtrlrPanelResource::getTypeDescription()
{
	return (CtrlrPanelResourceManager::getTypeDescription(getType()));
}

ValueTree &CtrlrPanelResource::getResourceTree()
{
	return (resourceTree);
}

void CtrlrPanelResource::setProperty (const Identifier& name, const var &newValue, const bool isUndoable)
{
	resourceTree.setProperty (name, newValue, nullptr);
}

bool CtrlrPanelResource::reloadFromSourceFile()
{
	if (getSourceFile().existsAsFile())
	{
		if (getSourceFile().copyFileTo (resourceDataFile))
		{
			resourceLoaded = false;
			load();
		}
	}

	return (true);
}
