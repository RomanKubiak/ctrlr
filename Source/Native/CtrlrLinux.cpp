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

CtrlrLinux::CtrlrLinux(CtrlrManager &_owner) : owner(_owner)
{
}

CtrlrLinux::~CtrlrLinux()
{
}

const Result CtrlrLinux::exportWithDefaultPanel(CtrlrPanel *panelToWrite, const bool isRestricted, const bool signPanel, RSAKey privateKey)
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
	    _DBG("CtrlrLinux::exportWithDefaultPanel chosen file: "+fc.getResult().getFullPathName());

		newMe = fc.getResult();
		if (!me.copyFileTo (newMe))
		{
			return (Result::fail("Linux native, copyFileTo from \""+me.getFullPathName()+"\" to \""+newMe.getFullPathName()+"\" failed"));
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
	else
    {
        _DBG("CtrlrLinux::exportWithDefaultPanel libr_open success on: "+newMe.getFullPathName());
    }

	if ( (error = CtrlrPanel::exportPanel (panelToWrite, File::nonexistent, newMe, &panelExportData, &panelResourcesData, isRestricted)) == String::empty)
	{
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
			    libr_close (outputHandle);
				return (Result::fail ("Linux native, failed to write panel resource data to binary ["+newMe.getFullPathName()+"], size ["+STR((int32)panelResourcesData.getSize())+"]"));
			}
			else
            {
                _DBG("CtrlrLinux::exportWithDefaultPanel wrote resources, size: "+_STR((int)panelResourcesData.getSize()));
            }
		}

		/* If it's a restricted instance and the signing key is valid, sign the instance */
		if (isRestricted && privateKey != RSAKey())
        {
            /* Sign the panel */
            MemoryBlock signature = signData (panelResourcesData, privateKey);

            if (!libr_write (outputHandle, CTRLR_INTERNAL_SIGNATURE_SECTION, signature.getData(), signature.getSize(), LIBR_UNCOMPRESSED, LIBR_OVERWRITE))
			{
			    libr_close (outputHandle);
				return (Result::fail ("Linux native, failed to write panel signature data to binary ["+newMe.getFullPathName()+"], size ["+STR((int32)signature.getSize())+"]"));
			}
			else
            {
                _DBG("CtrlrLinux::exportWithDefaultPanel wrote signature, size: "+_STR((int)signature.getSize()));
            }
        }
	}

    /* We need to move the temporary file to the new destination, libr won't do that for us */
	libr_close (outputHandle);

    if (File (outputHandle->tempfile).moveFileTo (newMe))
    {
        _DBG("CtrlrLinux::exportWithDefaultPanel file: "+_STR(outputHandle->tempfile)+" move to: "+newMe.getFullPathName());
        if (chmod (newMe.getFullPathName().toUTF8().getAddress(), S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH))
        {
			return (Result::fail ("Linux native, chmod failed on destination binary ["+newMe.getFullPathName()+"]"));
		}
		else
		{
		    _DBG("CtrlrLinux::exportWithDefaultPanel file: "+_STR(newMe.getFullPathName())+" made executable");
		}
    }
    else
    {
        return (Result::fail("Can't move file: "+_STR(outputHandle->tempfile)+" move to: "+newMe.getFullPathName()));
    }

	return (Result::ok());
}

const Result CtrlrLinux::getDefaultPanel(MemoryBlock& dataToWrite)
{
#ifdef DEBUG_INSTANCE
    File temp("/home/r.kubiak/devel/debug.bpanelz");
	temp.loadFileAsData (dataToWrite);
	return (Result::ok());
#endif
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
#ifdef DEBUG_INSTANCE
	File temp("/home/r.kubiak/devel/debug.bpanelz");
	MemoryBlock data;
	{
		ScopedPointer <FileInputStream> fis (temp.createInputStream());
		fis->readIntoMemoryBlock (data);
	}

	ValueTree t = ValueTree::readFromGZIPData(data.getData(), data.getSize());

	if (t.isValid())
	{
		ValueTree r = t.getChildWithName (Ids::resourceExportList);
		if (r.isValid())
		{
			MemoryOutputStream mos (dataToWrite, false);
			{
				GZIPCompressorOutputStream gzipOutputStream (&mos);
				r.writeToStream(gzipOutputStream);
				gzipOutputStream.flush();
			}
			return (Result::ok());
		}
	}
	else
	{
		return (Result::fail("Linux Native: getDefaultResources got data but couldn't parse it as a compressed ValueTree"));
	}
#endif

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

const Result CtrlrLinux::getSignature(MemoryBlock &dataToWrite)
{
    libr_file *handle = libr_open (nullptr, LIBR_READ);

	if (handle == nullptr)
	{
		return (Result::fail ("Linux native, libr_open failed to open binary [self]"));
	}
	else
	{
		_DBG("CtrlrLinux::getSignature, libr_open succeeded for binary [self]");
	}

	size_t signatureDataSize;
	char *signatureData = libr_malloc (handle, CTRLR_INTERNAL_RESOURCES_SECTION, &signatureDataSize);

	if (signatureData == nullptr)
	{
		libr_close (handle);
		return (Result::fail ("Linux native, libr_malloc didn't find embedded signature in binary"));
	}
	else
	{
		_DBG("CtrlrLinux::getSignature, libr_malloc returned data for signature size ["+STR((int32)signatureDataSize)+"]");
	}

	dataToWrite.append (signatureData, signatureDataSize);

	libr_close (handle);

    return (Result::ok());
}

#endif
