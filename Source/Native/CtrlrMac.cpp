#include "stdafx.h"
static const int zero=0;
#ifdef __APPLE__
#include <luabind/luabind.hpp>
#include "lua.hpp"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrMac.h"
#include "CtrlrMacros.h"
#include "CtrlrLog.h"


CtrlrMac::CtrlrMac()
{
}

CtrlrMac::~CtrlrMac()
{
}

const Result CtrlrMac::exportWithDefaultPanel(CtrlrPanel *panelToWrite, const bool isRestricted)
{
	if (panelToWrite == nullptr)
	{
		return (Result::fail("MAC native, panel pointer is invalid"));
	}

	File	me = File::getSpecialLocation(File::currentApplicationFile);
	File	newMe;
	MemoryBlock panelExportData,panelResourcesData;
	String error;
	FileChooser fc(CTRLR_NEW_INSTANCE_DIALOG_TITLE, me.getParentDirectory().getChildFile(File::createLegalFileName(panelToWrite->getProperty(Ids::name))).withFileExtension(me.getFileExtension()), me.getFileExtension());

	if (fc.browseForDirectory())
	{
		newMe = fc.getResult().getChildFile (File::createLegalFileName (panelToWrite->getProperty(Ids::name).toString()+me.getFileExtension()));
		if (!me.copyDirectoryTo (newMe))
		{
			return (Result::fail("MAC native, copyDirectoryTo from \""+me.getFullPathName()+"\" to \""+newMe.getFullPathName()+"\" failed"));
		}
	}
	else
	{
		return (Result::fail("MAC native, browse for directory dialog failed"));
	}

	if (!setBundleInfo(panelToWrite, newMe))
	{
		_WRN("CtrlrMac::exportMeWithNewResource failed to write new bundle information");
	}

	if ( (error = CtrlrPanel::exportPanel (panelToWrite, File::nonexistent, newMe, &panelExportData, &panelResourcesData, isRestricted)) == String::empty)
	{
		File panelFile		= newMe.getChildFile("Contents/Resources/"+String(CTRLR_MAC_PANEL_FILE));
		File resourcesFile	= newMe.getChildFile("Contents/Resources/"+String(CTRLR_MAC_RESOURCES_FILE));

		if (panelFile.create() && panelFile.hasWriteAccess())
		{
			if (!panelFile.replaceWithData(panelExportData.getData(), panelExportData.getSize()))
			{
				return (Result::fail("MAC native, failed to write panel file at: " + panelFile.getFullPathName()));
			}
		}

		if (resourcesFile.create() && resourcesFile.hasWriteAccess())
		{
			if (!resourcesFile.replaceWithData(panelResourcesData.getData(), panelResourcesData.getSize()))
			{
				return (Result::fail("MAC native, failed to write resources file at: " + resourcesFile.getFullPathName()));
			}
		}
	}

	return (Result::ok());
}

const Result CtrlrMac::getDefaultPanel(MemoryBlock &dataToWrite)
{
#ifdef DEBUG_INSTANCE
	File me("/Users/atom/devel/debug.bpanelz");
#else
	File me = File::getSpecialLocation(File::currentApplicationFile).getChildFile("Contents/Resources/"+String(CTRLR_MAC_PANEL_FILE));
#endif

	_DBG("MAC native, loading panel from file: \""+me.getFullPathName()+"\"");

	if (me.existsAsFile())
	{
		me.loadFileAsData (dataToWrite);
		return (Result::ok());
	}

	return (Result::fail("MAC native, \""+me.getFullPathName()+"\" does not exist"));
}

const Result CtrlrMac::getDefaultResources(MemoryBlock& dataToWrite)
{
#ifdef DEBUG_INSTANCE
	File meRes = File("/Users/atom/devel/debug.z");
#else
	File meRes = File::getSpecialLocation(File::currentApplicationFile).getChildFile("Contents/Resources/"+String(CTRLR_MAC_RESOURCES_FILE));
#endif
	_DBG("MAC native, loading resuources from: \""+meRes.getFullPathName()+"\"");

	if (meRes.existsAsFile())
	{
		meRes.loadFileAsData (dataToWrite);
		return (Result::ok());
	}

	return (Result::fail("MAC native, \""+meRes.getFullPathName()+"\" does not exist"));
}

const bool CtrlrMac::setBundleInfo (CtrlrPanel *sourceInfo, const File &bundle)
{
	File plist = bundle.getChildFile("Contents/Info.plist");

	if (plist.existsAsFile() && plist.hasWriteAccess())
	{
		ScopedPointer <XmlElement> plistXml (XmlDocument::parse(plist));
		if (plistXml == nullptr)
		{
			return (Result::fail("MAC native, can't parse Info.plist as a XML document"));
		}

		XmlElement *dict = plistXml->getChildByName("dict");
		if (dict != nullptr)
		{
			forEachXmlChildElement (*dict, e1)
			{
				if (e1->hasTagName("key") && e1->getAllSubText() == "CFBundleName")
				{
					XmlElement *cfBundleElement = e1->getNextElementWithTagName("string");
					if (cfBundleElement != nullptr)
					{
						cfBundleElement->deleteAllTextElements();
						cfBundleElement->addTextElement(sourceInfo->getProperty(Ids::name).toString());
					}
				}
				if (e1->hasTagName("key") && (e1->getAllSubText() == "CFBundleShortVersionString" || e1->getAllSubText() == "CFBundleVersion"))
				{
					XmlElement *cfVersionElement = e1->getNextElementWithTagName("string");
					if (cfVersionElement != nullptr)
					{
						cfVersionElement->deleteAllTextElements();
						cfVersionElement->addTextElement(sourceInfo->getVersionString(false,false,"."));
					}
				}
                if (e1->hasTagName("key") && (e1->getAllSubText() == "NSHumanReadableCopyright"))
				{
					XmlElement *nsCopyright = e1->getNextElementWithTagName("string");
					if (nsCopyright != nullptr)
					{
						nsCopyright->deleteAllTextElements();
						nsCopyright->addTextElement(sourceInfo->getProperty(Ids::panelAuthorName).toString());
					}
                }
                
                if (e1->hasTagName ("key") && (e1->getAllSubText() == "AudioComponents"))
                {
                    _DBG("INSTANCE: AudioComponents found");
                    
                    /* resource section */
                    XmlElement *dict = nullptr;
                    XmlElement *array = e1->getNextElement();
                    if (array)
                    {
                        _DBG("INSTANCE: array is valid");
                        dict = array->getChildByName("dict");
                    }
                    
                    if (dict != nullptr)
                    {
                        _DBG("INSTANCE: dict is valid");
                        
                        forEachXmlChildElement (*dict, e2)
                        {
                            _DBG("INSTANCE: enum element: "+e2->getTagName());
                            _DBG("INSTANCE: enum subtext: "+e2->getAllSubText());
                            if (e2->hasTagName("key") && (e2->getAllSubText() == "description"))
                            {
                                XmlElement *description = e2->getNextElementWithTagName("string");
                                if (description != nullptr)
                                {
                                    description->deleteAllTextElements();
                                    description->addTextElement (sourceInfo->getProperty(Ids::name).toString());
                                }
                            }
                        
                            if (e2->hasTagName("key") && (e2->getAllSubText() == "manufacturer"))
                            {
                                XmlElement *manufacturer = e2->getNextElementWithTagName("string");
                                if (manufacturer != nullptr)
                                {
                                    manufacturer->deleteAllTextElements();
                                    manufacturer->addTextElement(sourceInfo->getProperty(Ids::panelInstanceManufacturerID).toString().isEmpty() ? generateRandomUniquePluginId() : sourceInfo->getProperty(Ids::panelInstanceManufacturerID).toString());
                                }
                            }
                        
                            if (e2->hasTagName("key") && (e2->getAllSubText() == "name"))
                            {
                                XmlElement *name = e2->getNextElementWithTagName("string");
                                if (name != nullptr)
                                {
                                    name->deleteAllTextElements();
                                    name->addTextElement(sourceInfo->getProperty(Ids::panelAuthorName).toString() + ": " + sourceInfo->getProperty(Ids::name).toString());
                                }
                            }
                        
                            if (e2->hasTagName("key") && (e2->getAllSubText() == "subtype"))
                            {
                                XmlElement *subtype = e2->getNextElementWithTagName("string");
                                if (subtype != nullptr)
                                {
                                    subtype->deleteAllTextElements();
                                    subtype->addTextElement(sourceInfo->getProperty(Ids::panelInstanceUID).toString().isEmpty() ? generateRandomUniquePluginId() : sourceInfo->getProperty(Ids::panelInstanceUID).toString());
                                }
                            }
                        
                            if (e2->hasTagName("key") && (e2->getAllSubText() == "version"))
                            {
                                XmlElement *version = e2->getNextElementWithTagName("integer");
                                if (version != nullptr)
                                {
                                    version->deleteAllTextElements();
                                    version->addTextElement (_STR(getVersionAsHexInteger (sourceInfo->getVersionString(false,false,"."))));
                                }
                            }
                        }
                    }
                }
			}
		}
		else
		{
			return (Result::fail("MAC native, Infp.plist does not contain <dict /> element"));
		}

		plist.replaceWithText(plistXml->createDocument("<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd\">"));
		return (true);
	}
	else
	{
		 return (Result::fail("MAC native, Infp.plist does not exist or is not writable: \""+plist.getFullPathName()+"\""));
	 }
}

int CtrlrMac::getVersionAsHexInteger(const String version) const
{
    const StringArray segments = StringArray::fromTokens (version, ".", "\"'");
    
    int value = (segments[0].getIntValue() << 16)
    + (segments[1].getIntValue() << 8)
    + segments[2].getIntValue();
    
    if (segments.size() >= 4)
        value = (value << 8) + segments[3].getIntValue();
    
    return value;
}
#endif
