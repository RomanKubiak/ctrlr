#include "stdafx.h"
#ifdef JUCE_WINDOWS
#include "CtrlrLog.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrWindows.h"
#include <psapi.h>

CtrlrWindows::CtrlrWindows(CtrlrManager &_owner) : owner(_owner)
{
}

CtrlrWindows::~CtrlrWindows()
{
}

const Result CtrlrWindows::writeResource (void *handle, const LPSTR resourceId, const LPSTR resourceType, const MemoryBlock &resourceData)
{
	HANDLE	hResource = (HANDLE)handle;

	if (hResource)
	{
		return (UpdateResource (hResource, resourceType, resourceId, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPVOID) resourceData.getData(), (DWORD)resourceData.getSize()) ? Result::ok() : Result::fail("WIN32 UpdateResource failed"));
	}
	else
	{
		return (Result::fail("Windows Native: UpdateResource, resource HANDLE cast failed"));
	}
}

const Result CtrlrWindows::readResource (void *handle, const LPSTR resourceId, const LPSTR resourceType, MemoryBlock &resourceData)
{
	HRSRC	panelResource;
	HGLOBAL panelLoadedResource;
	String  data;
	char	*dataPointer;
	DWORD	dataSize;
	HMODULE myModuleHandle;

	if (handle != nullptr)
	{
		myModuleHandle = (HMODULE)handle;
	}
	else
	{
		myModuleHandle = GetModuleHandle(File::getSpecialLocation(File::currentExecutableFile).getFullPathName().toUTF8());
	}

	if (myModuleHandle)
	{
		panelResource = FindResource(myModuleHandle, resourceId, resourceType);

		if (panelResource)
		{
			panelLoadedResource = LoadResource(myModuleHandle, panelResource);

			if (panelLoadedResource)
			{
				dataSize	= SizeofResource (myModuleHandle, panelResource);
				dataPointer = (char *) LockResource (panelLoadedResource);

				resourceData = MemoryBlock(dataPointer,dataSize);

				return (Result::ok());
			}
			else
			{
				return (Result::fail("Windows Native: LoadResource() failed"));
			}
		}
		else
		{
			return (Result::fail("Windows Native: FindResource() failed"));
		}
	}
	else
	{
		return (Result::fail("Windows Native: GetModuleHandle() for: \""+File::getSpecialLocation(File::currentExecutableFile).getFullPathName()+"\" failed"));
	}
}

const Result CtrlrWindows::exportWithDefaultPanel(CtrlrPanel*  panelToWrite, const bool isRestricted, const bool signPanel, RSAKey privateKey)
{
	if (panelToWrite == nullptr)
	{
		return (Result::fail("Windows Native: exportWithDefaultPanel got nullptr for panel"));
	}

	File	me = File::getSpecialLocation(File::currentExecutableFile);
	File	newMe;
	HANDLE	hResource;
	MemoryBlock panelExportData,panelResourcesData;
	MemoryBlock iconData(BinaryData::ico_midi_png, BinaryData::ico_midi_pngSize);

	FileChooser fc(CTRLR_NEW_INSTANCE_DIALOG_TITLE,
					me.getParentDirectory().getChildFile(File::createLegalFileName(panelToWrite->getProperty(Ids::name))).withFileExtension(me.getFileExtension()),
					"*"+me.getFileExtension(),
					panelToWrite->getOwner().getProperty(Ids::ctrlrNativeFileDialogs));

	if (fc.browseForFileToSave(true))
	{
		newMe = fc.getResult();

		if (!newMe.hasFileExtension(me.getFileExtension()))
		{
			newMe = newMe.withFileExtension(me.getFileExtension());
		}

		if (!me.copyFileTo (newMe))
		{
			return (Result::fail("Windows Native: exportMeWithNewResource can't copy \""+me.getFullPathName()+"\" to \""+newMe.getFullPathName()+"\""));
		}
	}
	else
	{
		return (Result::fail("Windows Native: exportMeWithNewResource \"Save file\" dialog failed"));
	}

	hResource = BeginUpdateResource(newMe.getFullPathName().toUTF8(), FALSE);

	if (hResource)
	{
		String error;

		if ( (error = CtrlrPanel::exportPanel (panelToWrite, File::nonexistent, newMe, &panelExportData, &panelResourcesData, isRestricted)) == String::empty)
		{
			if (	writeResource (hResource, MAKEINTRESOURCE(CTRLR_INTERNAL_PANEL_RESID), RT_RCDATA, panelExportData)
				&&	writeResource (hResource, MAKEINTRESOURCE(CTRLR_INTERNAL_RESOURCES_RESID), RT_RCDATA, panelResourcesData)
				)
			{
				EndUpdateResource(hResource, FALSE);
			}
			else
			{
				return (Result::fail("Windows Native: exportMeWithNewResource writeResource[panel] failed"));
			}

			if (isRestricted && privateKey != RSAKey())
			{
				/* Sign the panel */
				MemoryBlock signature = signData (panelResourcesData, privateKey);
			}
		}
		else
		{
			return (Result::fail("Windows Native: exportMeWithNewResource exportPanel error: \""+error+"\""));
		}

		return (Result::ok());
	}

	return (Result::fail("Windows Native: exportMeWithNewResource BeginUpdateResource failed"));
}

const Result CtrlrWindows::getDefaultPanel(MemoryBlock &dataToWrite)
{
#ifdef DEBUG_INSTANCE
	File temp("c:\\devel\\debug_small.bpanelz");
	temp.loadFileAsData (dataToWrite);
	return (Result::ok());
#endif

	return (readResource (nullptr, MAKEINTRESOURCE(CTRLR_INTERNAL_PANEL_RESID), RT_RCDATA, dataToWrite));
}

const Result CtrlrWindows::getDefaultResources(MemoryBlock& dataToWrite)
{
#ifdef DEBUG_INSTANCE
	File temp("c:\\devel\\debug_small.bpanelz");

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
		return (Result::fail("Windows Native: getDefaultResources got data but couldn't parse it as a compressed ValueTree"));
	}
#endif

	return (readResource (nullptr, MAKEINTRESOURCE(CTRLR_INTERNAL_RESOURCES_RESID), RT_RCDATA, dataToWrite));
}

const Result CtrlrWindows::getSignature(MemoryBlock &dataToWrite)
{
	return (readResource (nullptr, MAKEINTRESOURCE(CTRLR_INTERNAL_SIGNATURE_RESID), RT_RCDATA, dataToWrite));
}

const Result CtrlrWindows::registerFileHandler()
{
	if (!JUCEApplication::isStandaloneApp())
		return (Result::ok());

	const char* const exts[] = { ".panel", ".panelz", ".bpanel", ".bpanelz", nullptr };
	StringArray extensions(exts);

	for (int i=0; i<extensions.size(); i++)
	{
		if (!WindowsRegistry::registerFileAssociation (extensions[i], "ctrlr"+extensions[i], "Ctrlr panel file ("+extensions[i]+")", File::getSpecialLocation(File::currentApplicationFile), -1, true))
			return (Result::fail("Can't register ["+extensions[i]+"] file extension"));
	}

	return (Result::ok());
}

static void sendKey(const KeyPress &event)
{
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wScan = 0;
	input.ki.dwFlags = 0;

	// Modifier Down
	if (event.getModifiers().isCommandDown())
	{
		input.ki.wVk = VK_CONTROL;
		SendInput(1, &input, sizeof(INPUT));
	}
	if (event.getModifiers().isAltDown())
	{
		input.ki.wVk = VK_MENU;
		SendInput(1, &input, sizeof(INPUT));
	}
	if (event.getModifiers().isShiftDown())
	{
		input.ki.wVk = VK_SHIFT;
		SendInput(1, &input, sizeof(INPUT));
	}

	// KEY Down
	input.ki.wVk = event.getKeyCode();
	SendInput(1, &input, sizeof(INPUT));

	// KEY Up
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));

	// MODIFIER Up
	if (event.getModifiers().isCommandDown())
	{
		input.ki.wVk = VK_CONTROL;
		SendInput(1, &input, sizeof(INPUT));
	}
	if (event.getModifiers().isAltDown())
	{
		input.ki.wVk = VK_MENU;
		SendInput(1, &input, sizeof(INPUT));
	}
	if (event.getModifiers().isShiftDown())
	{
		input.ki.wVk = VK_SHIFT;
		SendInput(1, &input, sizeof(INPUT));
	}
}

const Result CtrlrWindows::sendKeyPressEvent (const KeyPress &event)
{
	return (sendKeyPressEvent(event, String::empty));
}

const Result CtrlrWindows::sendKeyPressEvent (const KeyPress &event, const String &targetWindowName)
{
	HWND firstwindow = FindWindowEx(NULL, NULL, NULL, NULL);
    HWND window = firstwindow;
    TCHAR windowtext[MAX_PATH];
	// INPUT input;

	if (targetWindowName != String::empty)
	{
		while(1)
		{

			GetWindowText(window, windowtext, MAX_PATH);
			if (strstr(windowtext, targetWindowName.getCharPointer()) != NULL)
				break;

			window = FindWindowEx(NULL, window, NULL, NULL);
			if (window == NULL || window == firstwindow)
				return (Result::fail("Can't find target window: " + targetWindowName));
		}
	}

	SetForegroundWindow(window);
	sendKey(event);
	return (Result::ok());
}
#endif
