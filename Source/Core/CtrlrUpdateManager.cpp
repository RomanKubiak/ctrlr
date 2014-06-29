#include "stdafx.h"
#include "CtrlrUpdateManager.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrProcessor.h"
#include "CtrlrRevision.h"
#include "CtrlrUtilities.h"
#include "CtrlrLog.h"
#include "CtrlrPanel/CtrlrPanel.h"

CtrlrUpdateManager::CtrlrUpdateManager(CtrlrManager &_owner, const bool _startTimer, ChangeListener *initialListener)
	:	Thread("Update Manager"),
		owner(_owner)
{
	if (initialListener)
	{
		addChangeListener (initialListener);
	}

	startTimer (3000);
}

CtrlrUpdateManager::~CtrlrUpdateManager()
{
	removeAllChangeListeners();
	stopThread (5000);
}

void CtrlrUpdateManager::addChangeListener(ChangeListener *newListener)
{
	ChangeBroadcaster::addChangeListener (newListener);
#ifndef LINUX
	if ((bool)owner.getProperty(Ids::ctrlrCheckForUpdates) == true)
	{
		startTimer (5000);
	}
#endif
}

void CtrlrUpdateManager::handleAsyncUpdate()
{
	if (owner.getActivePanel())
	{
		owner.getActivePanel()->notify ("New version of Ctrlr is available for download", this, NotifySuccess);
	}
}

void CtrlrUpdateManager::notificationClicked (const MouseEvent e)
{
	URL ("http://ctrlr.org/downloads").launchInDefaultBrowser();
}

void CtrlrUpdateManager::run()
{
#ifdef LINUX
	return;
#endif

	_INF("Running update check");

	sendChangeMessage();

	ScopedPointer <XmlElement> xml(getUpdateData());
	if (xml)
	{
		_DBG("--------------------------------------------------------------");
		_DBG(xml->createDocument(String::empty));
		_DBG("--------------------------------------------------------------");

		if (xml->getBoolAttribute("update"))
		{
			/* new version */

			triggerAsyncUpdate();

			return;
		}
	}

	sendChangeMessage();
}

void CtrlrUpdateManager::checkForUpdates()
{
	sendChangeMessage();
}

void CtrlrUpdateManager::timerCallback()
{
	stopTimer();

	if ((bool)owner.getProperty(Ids::ctrlrCheckForUpdates) == false)
	{
		return;
	}

	startThread();
}

XmlElement *CtrlrUpdateManager::getUpdateData(const String &updateUrl)
{
	URL url;
	if (updateUrl != String::empty)
	{
		url = URL(updateUrl);
	}
	else
	{
		url = URL(owner.getProperty (Ids::ctrlrUpdateUrl));
	}

	url = url.withParameter("build",String(CTRLR_NIGHTLY));
	url = url.withParameter("revision",String(ctrlrRevision));
	url = url.withParameter("osname",getOsIdea());
	url = url.withParameter("osbits",getOsBitIdea());

	_DBG(url.toString(true));

	XmlElement *e = url.readEntireXmlStream(false);

	return (e);
}

const String CtrlrUpdateManager::getOsIdea()
{
	if ((SystemStats::getOperatingSystemType() & SystemStats::Windows) != 0)
	{
		return ("Windows");
	}
	else if (SystemStats::getOperatingSystemType() == SystemStats::Linux)
	{
		return ("Linux");
	}
	else
	{
		return ("MacOSX");
	}
}

const String CtrlrUpdateManager::getOsBitIdea()
{
#ifdef _M_IX86
	return ("32");
#elif defined _M_X64
	return ("64");
#elif defined __APPLE__
	return ("32");
#else
	return ("32");
#endif
}

const String CtrlrUpdateManager::getMyPackage()
{
#if CTRLR_NIGHTLY
	String ar = "Ctrlr_Nightly_" + getOsIdea() + "_x" + getOsBitIdea() + ".zip";
#else
	String ar = "Ctrlr_" + getOsIdea() + "_x" + getOsBitIdea() + ".zip";
#endif
	return (ar);
}

CtrlrFileDownloader::CtrlrFileDownloader() : ThreadWithProgressWindow("Downloading file", true, true)
{
}

CtrlrFileDownloader::~CtrlrFileDownloader()
{
}

void CtrlrFileDownloader::setUrl(const URL &_fileToDownload)
{
	fileToDownload = _fileToDownload;
}

void CtrlrFileDownloader::setFile (const File &_outputFile)
{
	outputFile = _outputFile;
}

void CtrlrFileDownloader::setResponseData(const int _bytesSent, const int _totalBytes)
{
	totalBytes = _totalBytes;
	bytesSent  = _bytesSent;
}

void CtrlrFileDownloader::run()
{
	ScopedPointer <InputStream> is (fileToDownload.createInputStream (false));
	const int totalLength = is->getTotalLength();
	int bytesSoFar = 0;
	const String packageFile = CtrlrUpdateManager::getMyPackage();

	if (outputFile.exists())
	{
		outputFile.deleteFile();
		outputFile.create();
	}

	while (! (is->isExhausted()))
	{
		if (threadShouldExit())
		{
			return;
		}

		MemoryBlock buffer(8192);
		const int num = is->read (buffer.getData(), 8192);

		if (num == 0)
			break;

		bytesSoFar += num;
		outputFile.appendData(buffer.getData(), buffer.getSize());

		setStatusMessage ("File: " + packageFile + "\nTotal size: " + File::descriptionOfSizeInBytes (totalLength) + " Got size: " + File::descriptionOfSizeInBytes (bytesSoFar));
		setProgress (bytesSoFar / (double)totalLength);
	}
}
