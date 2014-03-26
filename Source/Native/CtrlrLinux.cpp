#include "stdafx.h"
#ifdef LINUX
#include "CtrlrMacros.h"
#include "CtrlrLinux.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrManager/CtrlrManager.h"
#include <sys/types.h>
#include <sys/stat.h>

extern "C"
{
    #include "Linux/libr.h"
}

CtrlrLinux::CtrlrLinux()
{
}

CtrlrLinux::~CtrlrLinux()
{
}

const Result CtrlrLinux::exportWithDefaultPanel(CtrlrPanel*  panelToWrite, const bool isRestricted=false)
{
	_DBG("CtrlrLinux::exportWithDefaultPanel");

    if (panelToWrite == nullptr)
	{
		return (Result::fail("Linux native, panel pointer is invalid"));
	}

	File	me = File::getSpecialLocation(File::currentApplicationFile);
	File	newMe;
	libr_file *outputHandle;

	MemoryBlock panelExportData;
	MemoryBlock panelResourcesData;
	String error;

	FileChooser fc(CTRLR_NEW_INSTANCE_DIALOG_TITLE,
					me.getParentDirectory().getChildFile(File::createLegalFileName(panelToWrite->getProperty(Ids::name))).withFileExtension(me.getFileExtension()),
					me.getFileExtension());

	if (fc.browseForFileToSave (true))
	{
		newMe = fc.getResult();
		if (!me.copyFileTo (newMe))
		{
			return (Result::fail("Linux native, copyFileTo from \""+me.getFullPathName()+"\" to \""+newMe.getFullPathName()+"\" failed"));
		}
		else
		{
			if (chmod (newMe.getFullPathName().toUTF8().getAddress(), S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH))
			{
				return (Result::fail ("Linux native, chmod failed on destination binary ["+newMe.getFullPathName()+"]"));
			}
		}
	}
	else
	{
		return (Result::fail("Linux native, browse for save file dialog failed"));
	}

	outputHandle = libr_open (newMe.getFullPathName().toUTF8().getAddress(), LIBR_READ_WRITE);

	if (outputHandle == nullptr)
	{
		return (Result::fail ("Linux native, can't open output binary ["+newMe.getFullPathName()+"] using libr_open()"));
	}

	if ( (error = CtrlrPanel::exportPanel (panelToWrite, File::nonexistent, newMe, &panelExportData, &panelResourcesData, isRestricted)) == String::empty)
	{
		//CTRLR_INTERNAL_RESOURCES_RESID;

		if (!libr_write (outputHandle, CTRLR_INTERNAL_PANEL_SECTION, panelExportData.getData(), panelExportData.getSize(), LIBR_UNCOMPRESSED, LIBR_OVERWRITE))
		{
			return (Result::fail ("Linux native, failed to write panel data to binary ["+newMe.getFullPathName()+"], size ["+STR((int32)panelExportData.getSize())+"]"));
			libr_close (outputHandle);
		}

		_DBG ("CtrlrLinux::exportWithDefaultPanel wrote panel data to binary size ["+STR((int32)panelExportData.getSize())+"]");

		if (panelResourcesData.getSize() > 0)
		{
			if (!libr_write (outputHandle, CTRLR_INTERNAL_RESOURCES_SECTION, panelResourcesData.getData(), panelResourcesData.getSize(), LIBR_UNCOMPRESSED, LIBR_OVERWRITE))
			{
				return (Result::fail ("Linux native, failed to write panel resource data to binary ["+newMe.getFullPathName()+"], size ["+STR((int32)panelResourcesData.getSize())+"]"));
				libr_close (outputHandle);
			}
		}
	}

	libr_close (outputHandle);

	return (Result::ok());
}

const Result CtrlrLinux::getDefaultPanel(MemoryBlock& dataToWrite)
{
	libr_file *handle = libr_open (nullptr, LIBR_READ);

	if (handle == nullptr)
	{
		return (Result::fail ("Linux native, libr_open failed to open binary [self]"));
	}
	else
	{
		_DBG("CtrlrLinux::getDefaultPanel, libr_open succeeded for binary [self]");
	}

	size_t panelDataSize;
	char *panelData = libr_malloc (handle, CTRLR_INTERNAL_PANEL_SECTION, &panelDataSize);

	if (panelData == nullptr)
	{
		libr_close (handle);
		return (Result::fail ("Linux native, libr_malloc didn't fint embedded panel in binary"));
	}
	else
	{
		_DBG("CtrlrLinux::getDefaultPanel, libr_malloc returned data for panel size ["+STR((int32)panelDataSize)+"]");
	}

	dataToWrite.append (panelData, panelDataSize);

	libr_close (handle);

    return (Result::ok());
}

const Result CtrlrLinux::getDefaultResources(MemoryBlock& dataToWrite)
{
    libr_file *handle = libr_open (nullptr, LIBR_READ);

	if (handle == nullptr)
	{
		return (Result::fail ("Linux native, libr_open failed to open binary [self]"));
	}
	else
	{
		_DBG("CtrlrLinux::getDefaultResources, libr_open succeeded for binary [self]");
	}

	size_t panelResourcesDataSize;
	char *panelResourcesData = libr_malloc (handle, CTRLR_INTERNAL_RESOURCES_SECTION, &panelResourcesDataSize);

	if (panelResourcesData == nullptr)
	{
		libr_close (handle);
		return (Result::fail ("Linux native, libr_malloc didn't find embedded panel resources in binary"));
	}
	else
	{
		_DBG("CtrlrLinux::getDefaultResources, libr_malloc returned data for panel size ["+STR((int32)panelResourcesDataSize)+"]");
	}

	dataToWrite.append (panelResourcesData, panelResourcesDataSize);

	libr_close (handle);

    return (Result::ok());
}

#endif
