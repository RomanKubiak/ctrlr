#ifndef __CTRLR_UPDATE_MANAGER__
#define __CTRLR_UPDATE_MANAGER__

#include "CtrlrModulator/CtrlrModulator.h"

class CtrlrManager;

class CtrlrFileDownloader : public ThreadWithProgressWindow
{
	public:
		CtrlrFileDownloader();
		~CtrlrFileDownloader();
		void setUrl(const URL &_fileToDownload);
		void run();
		static bool progressCallback(void *context, int bytesSent, int totalBytes);
		void setResponseData(const int _bytesSent, const int _totalBytes);
		void setFile (const File &_outputFile);
		
		JUCE_LEAK_DETECTOR(CtrlrFileDownloader)

	private:
		URL fileToDownload;
		int totalBytes;
		int bytesSent;
		File outputFile;
};

class CtrlrUpdateManager :	public Thread, 
							public ChangeBroadcaster, 
							public Timer, 
							public AsyncUpdater,
							public CtrlrNotificationCallback
{
	public:
		CtrlrUpdateManager(CtrlrManager &_owner, const bool _startTimer=true, ChangeListener *initialListener=0);
		~CtrlrUpdateManager();

		void run();		
		void checkForUpdates();
		void timerCallback();
		XmlElement *getUpdateData(const String &updateUrl=String::empty);
		static const String getOsIdea();
		static const String getOsBitIdea();
		static const String getMyPackage();
		void addChangeListener(ChangeListener *newListener);
		void handleAsyncUpdate();
		void notificationClicked (const MouseEvent e);
		JUCE_LEAK_DETECTOR(CtrlrUpdateManager)

	private:
		CtrlrManager &owner;
		CtrlrFileDownloader downloader;
};

#endif