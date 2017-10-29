#include "stdafx.h"
#include "CtrlrUtilities.h"
#include "CtrlrLog.h"
#include "CtrlrPanel.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrPanel/CtrlrPanelResourceManager.h"
#include "CtrlrPanel/CtrlrPanelResource.h"
#include "CtrlrProcessor.h"
#include "CtrlrMacros.h"
#include "CtrlrManager/CtrlrManager.h"

ValueTree CtrlrPanel::getCleanPanelTree()
{
	ValueTree exportTree = panelTree.createCopy();

	for (int i=0; i<exportTree.getNumProperties(); i++)
	{
		exportTree.removeProperty (Ids::panelMidiOutputDevice, 0);
		exportTree.removeProperty (Ids::panelMidiInputDevice, 0);
		exportTree.removeProperty (Ids::panelMidiControllerDevice, 0);
	}
	ValueTree ed = exportTree.getChildWithName(Ids::uiPanelEditor);

	if (ed.isValid())
	{
		bool hideMenuBar = (bool)ed.getProperty(Ids::uiPanelMenuBarHideOnExport);
		ed.setProperty(Ids::uiPanelMenuBarVisible, !hideMenuBar, nullptr);
	}

	// Embed external lua code in properties
	convertLuaMethodsToPropeties(getPanelLuaDir(),exportTree);

	return (exportTree);
}

String CtrlrPanel::getPanelContentDirPath()
{
	const String filePath = getProperty(Ids::panelFilePath);
	return filePath.upToLastOccurrenceOf(".", false, false);
}

File CtrlrPanel::getPanelContentDir()
{
	return File(getPanelContentDirPath());
}

File CtrlrPanel::getPanelLuaDir()
{
	return getPanelContentDir().getChildFile("lua");
}

String CtrlrPanel::getPanelLuaDirPath()
{
	return getPanelLuaDir().getFullPathName();
}

File CtrlrPanel::getPanelResourcesDir()
{
	return getPanelContentDir().getChildFile("resources");
}

String CtrlrPanel::getPanelResourcesDirPath()
{
	return getPanelResourcesDir().getFullPathName();
}

File CtrlrPanel::getLuaMethodGroupDir(const ValueTree &methodGroup)
{
	ValueTree currentItem = methodGroup;
	StringArray temp;
	while (currentItem.isValid() && currentItem.hasType(Ids::luaMethodGroup))
	{
		String currentPath = currentItem.getProperty(Ids::name);
		if (!currentPath.isEmpty())
		{
			temp.add(currentPath);
		}
		currentItem = currentItem.getParent();
	}
	File result(getPanelLuaDirPath());
	for (int i = temp.size(); i >= 0; i--)
	{
		result = result.getChildFile(temp[i]);
	}
	return result;
}

Result CtrlrPanel::convertLuaMethodsToFiles(const String dirPath)
{
	Result res = Result::ok();
	// Try and get access to panel directory
	File panelLuaDirectory(dirPath);
	if (panelLuaDirectory.existsAsFile())
	{	// A directory with that name already exists
		res = Result::fail("Convert to files can't create directory (a file with that name already exists): " + dirPath);
	}
	else if (!panelLuaDirectory.exists())
	{
		res = panelLuaDirectory.createDirectory();
	}
	if (res.ok())
	{
		if (panelLuaDirectory.hasWriteAccess())
		{	// Save lua code
			res = saveLuaCode(panelLuaDirectory, this);
		}
		else
		{
			res = Result::fail("Convert to XML can't write in panel directory: " + dirPath);
		}
	}
	return res;
}

void CtrlrPanel::convertLuaMethodsToPropeties(const File &panelLuaDir, ValueTree &panelTree)
{
	ValueTree luaManager = panelTree.getChildWithName(Ids::luaManager);
	if (luaManager.isValid())
	{
		ValueTree luaMethods = luaManager.getChildWithName(Ids::luaManagerMethods);
		CtrlrPanel::convertLuaChildrenToProperties(panelLuaDir, &luaMethods);
	}
}

Result CtrlrPanel::savePanel()
{
	_DBG("CtrlrPanel::savePanel");

	bool panelWasDirty = isPanelDirty();
	setPanelDirty(false);
	Result res = Result::ok();
	const String filePath = getProperty(Ids::panelFilePath);
	File panelFile(filePath);

	if (panelFile.existsAsFile() && panelFile.hasWriteAccess())
	{
		if (panelFile.hasFileExtension("panel"))
		{	
			res = savePanelXml(panelFile, this, false);
		}
		if (panelFile.hasFileExtension("panelz"))
			res = savePanelXml (panelFile, this, true);
		if (panelFile.hasFileExtension("bpanel"))
			res = savePanelBin (panelFile, this, false);
		if (panelFile.hasFileExtension("bpanelz"))
			res = savePanelBin(panelFile, this, true);

		if (getEditor())
		{
			if (res.failed())
			{
				notify ("Panel save: ["+res.getErrorMessage()+"]", nullptr, NotifyFailure);
			}
			else
			{
				notify ("Panel saved: ["+panelFile.getFullPathName()+"]", nullptr, NotifySuccess);
			}
		}
	}
	else
	{
		File ret = askForPanelFileToSave (this, File(owner.getProperty(Ids::lastBrowsedPanelDir)).getChildFile(getVersionString()));
		if (ret != File::nonexistent)
		{
			res = savePanelXml(ret, this);
			setProperty (Ids::panelFilePath, ret.getFullPathName());
		}
		else
		{
			res = Result::fail ("Selected file is invalid");
		}

		if (getEditor())
		{
			if (res.failed())
			{
				notify ("Panel save: ["+res.getErrorMessage()+"]", nullptr, NotifyFailure);
			}
			else
			{
				notify ("Panel saved: ["+panelFile.getFullPathName()+"]", nullptr, NotifySuccess);
			}
		}
	}
	if (res.wasOk())
	{
		getUndoManager()->clearUndoHistory();
		updatePanelWindowTitle();
	}
	else if (panelWasDirty)
	{
		setPanelDirty(panelWasDirty);
	}
	return res;
}

const File CtrlrPanel::savePanelAs(const CommandID saveOption)
{
	File fileToSave;
	File f(getProperty(Ids::lastBrowsedPanelDir));

	if (saveOption == CtrlrEditor::doExportFileText)
	{
		fileToSave = CtrlrPanel::askForPanelFileToSave (this, f, true, false);

		if (fileToSave == File::nonexistent)
			return (fileToSave);

		savePanelXml (fileToSave, this);
		setProperty (Ids::panelFilePath, fileToSave.getFullPathName());
	}
	if (saveOption == CtrlrEditor::doExportFileZText)
	{
		fileToSave = CtrlrPanel::askForPanelFileToSave (this, f, true, true);

		if (fileToSave == File::nonexistent)
			return (fileToSave);

		savePanelXml (fileToSave, this, true);
		setProperty (Ids::panelFilePath, fileToSave.getFullPathName());
	}
	if (saveOption == CtrlrEditor::doExportFileBin)
	{
		fileToSave = CtrlrPanel::askForPanelFileToSave (this, f, false, false);

		if (fileToSave == File::nonexistent)
			return (fileToSave);

		savePanelBin (fileToSave, this, false);
	}
	if (saveOption == CtrlrEditor::doExportFileZBin)
	{
		fileToSave = CtrlrPanel::askForPanelFileToSave (this, f, false, true);

		if (fileToSave == File::nonexistent)
			return (fileToSave);

		savePanelBin (fileToSave, this, true);
	}
	if (saveOption == CtrlrEditor::doExportFileZBinRes)
	{
		const String err = exportPanel(this, f);
		if (err != String::empty)
		{
			AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Panel Export", err);
		}
	}
	if (saveOption == CtrlrEditor::doExportFileInstance)
	{
		Result res = owner.getNativeObject().exportWithDefaultPanel(this, false, false, RSAKey());
		if (res.failed())
		{
			AlertWindow::showMessageBox (AlertWindow::WarningIcon, "Panel export", "Failed to export panel as standalone instance.\n"+res.getErrorMessage());
		}
		else
		{
			AlertWindow::showMessageBox (AlertWindow::InfoIcon, "Panel export", "Wrote new panel instance");
		}
	}
	if (saveOption == CtrlrEditor::doExportFileInstanceRestricted)
	{
	    RSAKey privateKey;
	    File privateKeyFile (owner.getProperty(Ids::ctrlrPrivateKey));
	    if (privateKeyFile.existsAsFile())
        {
            privateKey = RSAKey (privateKeyFile.loadFileAsString());
        }

		Result res = owner.getNativeObject().exportWithDefaultPanel(this, true, true, privateKey);

		if (res.failed())
		{
			AlertWindow::showMessageBox (AlertWindow::WarningIcon, "Panel export", "Failed to export panel as standalone instance.\n"+res.getErrorMessage());
		}
		else
		{
			AlertWindow::showMessageBox (AlertWindow::InfoIcon, "Panel export", "Wrote new panel instance");
		}
	}
	if (saveOption == CtrlrEditor::doExportGenerateUID)
	{
		setProperty (Ids::panelUID, generateRandomUnique(STR (Time::currentTimeMillis())));
	}

	return (fileToSave);
}

void CtrlrPanel::savePanelVersioned()
{
	File panelFile(getProperty (Ids::panelFilePath));

	if (panelFile.existsAsFile() && panelFile.hasWriteAccess())
	{
		setProperty (Ids::panelVersionMinor, (int)getProperty(Ids::panelVersionMinor)+1);

		if (panelFile != File::nonexistent)
		{
			savePanelXml (File(panelFile.getParentDirectory().getChildFile(getProperty(Ids::name).toString() + owner.getProperty(Ids::ctrlrVersionSeparator).toString() + getVersionString()).withFileExtension((bool)owner.getProperty(Ids::ctrlrVersionCompressed) ? "panelz" : "panel")), this, owner.getProperty(Ids::ctrlrVersionCompressed));
		}
	}
	else
	{
		savePanel();
	}
}

const String CtrlrPanel::exportPanel(CtrlrPanel *panel, const File &lastBrowsedDir, const File &destinationFile, MemoryBlock *outputPanelData, MemoryBlock *outputResourcesData, const bool isRestricted)
{
	Image panelSnapshot (Image::ARGB, 400, 400, true);
	CtrlrPanelCanvas *canvas = panel->getEditor()->getCanvas();
	// CtrlrPanelEditor *editor = panel->getEditor();

	if (panel == 0 || panel == nullptr)
		return ("Undefined panel passeed to exporter");

	File exportedFile = File::nonexistent;

	if (destinationFile == File::nonexistent)
		exportedFile = askForPanelFileToSave (panel, lastBrowsedDir, false, true);
	else
		exportedFile = destinationFile;

	if (exportedFile == File::nonexistent)
		return ("Destination file does not exist or is invalid");

	panel->luaSavePanel (PanelFileExport, exportedFile);

	if (canvas)
	{
		Image snap	= canvas->createComponentSnapshot (canvas->getBounds(), true);
		Graphics g(panelSnapshot);
		g.drawImageWithin (snap, 0, 0, 400, 400, RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, false);
	}

	ValueTree resources(Ids::resourceExportList);

	for (int i=0; i<panel->getResourceManager().getNumResources(); i++)
	{
		CtrlrPanelResource *res = panel->getResourceManager().getResource(i);
		if (res)
		{
			resources.addChild (res->createTree(), -1, 0);
		}
	}

	if (panel->getResourceManager().getNumResources() > 0)
	{
		const int ret = AlertWindow::showOkCancelBox (AlertWindow::QuestionIcon, "License question", "Would you like to attach a license to this panel?", "Yes", "No");
		if (ret == 1)
		{
			AlertWindow licenseWindow("License content", "Paste your license below", AlertWindow::InfoIcon, 0);
			TextEditor lic;
			lic.setMultiLine (true, false);
			lic.setSize (400,300);
			licenseWindow.addCustomComponent (&lic);
			licenseWindow.addButton ("OK", 1);

			if (licenseWindow.runModalLoop())
			{
				ValueTree licTree(Ids::resourceLicense);
				licTree.setProperty(Ids::resourceData, lic.getText(), 0);
				resources.addChild (licTree, -1, 0);
			}
		}
	}

	ValueTree exportTree	= panel->getCleanPanelTree();

	if (isRestricted)
	{
		exportTree.setProperty (Ids::restricted, (int)InstanceSingleRestriced, nullptr);
		if (exportTree.getChildWithName (Ids::uiPanelEditor).isValid())
		{
			exportTree.getChildWithName (Ids::uiPanelEditor).setProperty (Ids::uiPanelEditMode, false, nullptr);
		}
	}

	if (panelSnapshot != Image::null)
	{
		MemoryBlock imageData;
		MemoryOutputStream imageDataStream(imageData, true);
		PNGImageFormat png;
		png.writeImageToStream (panelSnapshot, imageDataStream);

		if (imageData.getSize() != 0)
		{
			ValueTree snap(Ids::resourcePanelSnapshot);
			snap.setProperty (Ids::resourceSize, (int)imageData.getSize(), 0);
			snap.setProperty (Ids::resourceData, imageData.toBase64Encoding(), 0);
			resources.addChild (snap, -1, 0);
		}
	}

	if (exportedFile.hasWriteAccess() && outputPanelData == nullptr)
	{
		exportTree.addChild (resources, -1, 0);
		MemoryOutputStream compressedData;

		{
			GZIPCompressorOutputStream gzipOutputStream (&compressedData);
			exportTree.writeToStream(gzipOutputStream);
			gzipOutputStream.flush();
		}

		exportedFile.replaceWithData(compressedData.getData(), compressedData.getDataSize());

		return (String::empty);
	}
	else if (outputPanelData != nullptr && outputResourcesData != nullptr)
	{
		MemoryOutputStream compressedPanelData(*outputPanelData, false);
		MemoryOutputStream compressedResourcesData(*outputResourcesData, false);

		{
			GZIPCompressorOutputStream gzipOutputStream (&compressedPanelData);
			exportTree.writeToStream(gzipOutputStream);
			gzipOutputStream.flush();
		}

		{
			GZIPCompressorOutputStream gzipOutputStream (&compressedResourcesData);
			resources.writeToStream(gzipOutputStream);
			gzipOutputStream.flush();
		}

		return (String::empty);
	}
	else
	{
		return ("Can't export panel, I can't write to the specified file");
	}

}

const ValueTree CtrlrPanel::openBinPanel(const File &panelFile)
{
	ValueTree tree;

	if (panelFile.hasFileExtension(".bpanelz"))
	{
		ScopedPointer <FileInputStream> fileInputStream (panelFile.createInputStream());

		if (fileInputStream)
		{
            GZIPDecompressorInputStream gzFileInputStream (*fileInputStream);
			return (ValueTree::readFromStream (gzFileInputStream));
		}
	}
	else if (panelFile.hasFileExtension(".bpanel"))
	{
		ScopedPointer <FileInputStream> fileInputStream(panelFile.createInputStream());
		if (fileInputStream)
		{
			return (ValueTree::readFromStream (*fileInputStream));
		}
	}

	return (ValueTree());
}

const ValueTree CtrlrPanel::openBinPanel(const MemoryBlock &panelData, const bool isCompressed)
{
	ValueTree tree;

	if (isCompressed)
	{
		MemoryInputStream mi(panelData, false);

		{
			GZIPDecompressorInputStream gzFileInputStream (mi);
			tree = ValueTree::readFromStream (gzFileInputStream);

			return (tree);
		}
	}
	else
	{
		{
			MemoryInputStream mi(panelData, false);
			return (ValueTree::readFromStream (mi));
		}
	}
}

const ValueTree CtrlrPanel::openXmlPanel(const File &panelFile)
{
	String xmlData;

	if (panelFile.hasFileExtension("panelz"))
	{
		ScopedPointer <FileInputStream> fz(panelFile.createInputStream());
		if (fz)
		{
			GZIPDecompressorInputStream gzInput (fz, false);
			xmlData = gzInput.readEntireStreamAsString();
		}
		else
		{
			_ERR("CtrlrPanel::openXmlPanel can't create input stream for file: " + panelFile.getFullPathName());
		}

		ScopedPointer <XmlElement> xml(XmlDocument::parse (xmlData));

		if (xml)
		{
			return (ValueTree::fromXml (*xml));
		}
		else
		{
			_ERR("CtrlrPanel::openXmlPanel can't parse file contents as XML");
		}
	}
	else if (panelFile.hasFileExtension("panel"))
	{
		ScopedPointer <XmlElement> xml(XmlDocument::parse (panelFile));
		if (xml)
		{
			return (ValueTree::fromXml (*xml));
		}
		else
		{
			_ERR("CtrlrPanel::openXmlPanel can't parse file contents as XML");
		}
	}
	else
	{
		_ERR("CtrlrPanel::openXmlPanel unknown file type");
	}

	_ERR("CtrlrPanel::openXmlPanel can't open panel");
	return (ValueTree());
}

const ValueTree CtrlrPanel::openPanel(const File &panelFile)
{
	ValueTree result;
	if (panelFile.hasFileExtension("panelz;panel"))
	{
		result = openXmlPanel(panelFile);
	}
	else if (panelFile.hasFileExtension("bpanelz;bpanel"))
	{
		result = openBinPanel(panelFile);
	}
	else 
	{
		result = ValueTree();
	}
	// Patch panelFilePath property to match the actual file
	result.setProperty(Ids::panelFilePath,panelFile.getFullPathName(),nullptr);
	return result;
}

Result CtrlrPanel::savePanelBin(const File &fileToSave, CtrlrPanel *panel, const bool compressPanel)
{
	MemoryOutputStream panelBinData;

	if (panel == nullptr)
		return (Result::fail ("Invalid panel pointer"));

	panel->sync();

	if (compressPanel)
	{
		panel->luaSavePanel (PanelFileBinaryCompressed, fileToSave);

		GZIPCompressorOutputStream gzOutputStream (&panelBinData);
		panel->getPanelTree().writeToStream(gzOutputStream);
		gzOutputStream.flush();
	}
	else
	{
		panel->luaSavePanel (PanelFileBinary, fileToSave);

		panel->getPanelTree().writeToStream(panelBinData);
	}

	if (fileToSave.hasWriteAccess())
	{
		if (fileToSave.replaceWithData(panelBinData.getData(), panelBinData.getDataSize()))
		{
			return (Result::ok());
		}
		else
		{
			return (Result::fail ("savePanelBin replaceWithData() failed on destination file "+fileToSave.getFullPathName()));
		}
	}
	else
	{
		AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Can't save panel", "I can't write to the specified file", "OK");
		return (Result::fail ("savePanelBin now write access to file: "+fileToSave.getFullPathName()));
	}
}

void CtrlrPanel::writePanelXml(OutputStream &outputStream, CtrlrPanel *panel, const bool compressPanel)
{
	if (panel == nullptr)
		return;

	panel->sync();

	ScopedPointer <XmlElement> panelXml (panel->getPanelTree().createXml());

	if (compressPanel && panelXml)
	{
		String xml = panelXml->createDocument("");
		{
			GZIPCompressorOutputStream gzipOutputStream(&outputStream, 9, false);
			gzipOutputStream.writeString (xml);
		}
	}
	if (!compressPanel && panelXml)
	{
		panelXml->writeToStream (outputStream,"");
	}
}

File CtrlrPanel::getLuaMethodSourceFile(const ValueTree *method)
{
	String path = method->getProperty(Ids::luaMethodSourcePath);
	if (File::isAbsolutePath(path))
	{
		return File(path);
	}
	else
	{
		return getPanelLuaDir().getChildFile(path);
	}
}


Result CtrlrPanel::writeLuaMethod(const File &parentDir, ValueTree *method)
{
	if (method == nullptr)
		return Result::fail("Method name is missing");

	const String methodName = method->getProperty(Ids::luaMethodName);
	const String methodCode = method->getProperty(Ids::luaMethodCode);
	if (methodName.isEmpty())
		return Result::fail("Method name is empty");

	// Create file
	const File methodFile = parentDir.getNonexistentChildFile(methodName,".lua",false);
	if (methodFile.replaceWithText(methodCode))
	{
		method->setProperty(Ids::luaMethodName, methodFile.getFileNameWithoutExtension(), nullptr);
		method->setProperty(Ids::luaMethodSourcePath, methodFile.getRelativePathFrom(getPanelLuaDir()), nullptr);
		method->setProperty(Ids::luaMethodSource, (int)CtrlrLuaMethod::codeInFile, nullptr);
		method->removeProperty(Ids::luaMethodCode,nullptr);
		return Result::ok();
	}
	else
	{
		AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Could not save lua method", "Could not save lua method", "OK");
		return (Result::fail("saveLuaMethod: could not save lua method."));
	}
}

Result CtrlrPanel::writeLuaMethodGroup(const File &parentDir, ValueTree *methodGroup)
{
	if (methodGroup == nullptr)
		return Result::fail("Method group is missing");

	const String methodGroupName = methodGroup->getProperty(Ids::name);
	if (methodGroupName.isEmpty())
		return Result::fail("Method group is empty");

	// Create file
	const File methodGroupFile = parentDir.getChildFile(methodGroupName);
	Result res = methodGroupFile.createDirectory();
	if (res.wasOk())
	{	// Save contained methods and groups
		return CtrlrPanel::writeLuaChildren(methodGroupFile, methodGroup);
	}
	else
	{
		AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Could not save lua method group", "Could not save lua method group", "OK");
	}
	return res;
}

Result CtrlrPanel::writeLuaChildren(const File &parentDir, ValueTree *parentElement)
{
	if (parentElement == nullptr)
		return Result::fail("Parent element is missing");

	Result res = Result::ok();
	for (int i = 0; i<parentElement->getNumChildren(); i++)
	{
		ValueTree child = parentElement->getChild(i);
		if (child.hasType(Ids::luaMethod))
		{
			if ((int)child.getProperty(Ids::luaMethodSource) != CtrlrLuaMethod::codeInFile)
			{	// Only process methods that are not already saved in files
				res = CtrlrPanel::writeLuaMethod(parentDir, &child);
				if (res.failed())
				{	// Break on first error
					return res;
				}
			}
		}
		else if (child.hasType(Ids::luaMethodGroup))
		{
			res = CtrlrPanel::writeLuaMethodGroup(parentDir, &child);
			if (res.failed())
			{	// Break on first error
				return res;
			}
		}
	}
	return res;
}

Result CtrlrPanel::saveLuaCode(const File &panelLuaDir, CtrlrPanel *panel)
{
	ValueTree luaManager = panel->getPanelTree().getChildWithName(Ids::luaManager);
	if (luaManager.isValid())
	{
		ValueTree luaMethods = luaManager.getChildWithName(Ids::luaManagerMethods);
		return CtrlrPanel::writeLuaChildren(panelLuaDir,&luaMethods);
	}
	else
	{
		return (Result::fail("saveLuaCode failed due to missing luaManager"));
	}
	return Result::ok();
}

void CtrlrPanel::convertLuaMethodToProperty(const File &panelLuaDir, ValueTree *method)
{
	if (method == nullptr)
		return;

	const String methodName = method->getProperty(Ids::luaMethodName);
	const String methodFilePath = method->getProperty(Ids::luaMethodCode);
	if (methodName.isEmpty() || methodFilePath.isEmpty())
		return;
	// Get file path
	File methodFile;
	if (File::isAbsolutePath(methodFilePath))
	{
		methodFile = File(methodFilePath);
	}
	else
	{
		methodFile = panelLuaDir.getChildFile(methodFilePath);
	}

	// Read file
	method->removeProperty(Ids::luaMethodSourcePath,nullptr);
	method->setProperty(Ids::luaMethodSource, (int)CtrlrLuaMethod::codeInProperty, nullptr);
	method->setProperty(Ids::luaMethodCode,methodFile.loadFileAsString(), nullptr);
}

void CtrlrPanel::convertLuaChildrenToProperties(const File &panelLuaDir, ValueTree *parentElement)
{
	if (parentElement == nullptr)
		return;

	for (int i = 0; i<parentElement->getNumChildren(); i++)
	{
		ValueTree child = parentElement->getChild(i);
		if (child.hasType(Ids::luaMethod))
		{	// This is a method, check if it's on file
			if ((int)child.getProperty(Ids::luaMethodSource) == CtrlrLuaMethod::codeInFile)
			{	// Only process methods that are saved in files
				CtrlrPanel::convertLuaMethodToProperty(panelLuaDir, &child);
			}
		}
		else if (child.hasType(Ids::luaMethodGroup))
		{	// This is a group => recursive call
			CtrlrPanel::convertLuaChildrenToProperties(panelLuaDir, &child);
		}
	}
}

Result CtrlrPanel::savePanelXml(const File &fileToSave, CtrlrPanel *panel, const bool compressPanel)
{
	MemoryOutputStream dataToSave;

	if (compressPanel)
	{
		panel->luaSavePanel (PanelFileXMLCompressed, fileToSave);
	}
	else
	{
		panel->luaSavePanel (PanelFileXML, fileToSave);
	}

	writePanelXml (dataToSave, panel, compressPanel);

	if (fileToSave.hasWriteAccess())
	{
		if (fileToSave.replaceWithData(dataToSave.getData(), dataToSave.getDataSize()))
		{
			return (Result::ok());
		}
		else
		{
			return (Result::fail ("savePanelXml replaceWithData() failed on destination file "+fileToSave.getFullPathName()));
		}
	}
	else
	{
		AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Can't save panel", "I can't write to the specified file", "OK");
		return (Result::fail ("savePanelXml now write access to file: "+fileToSave.getFullPathName()));
	}
}

const File CtrlrPanel::askForPanelFileToSave (CtrlrPanel *panel,
												const File &lastBrowsedDir,
												const bool isXml,
												const bool isCompressed)
{
	String panelFileName = "Ctrlr Panel";
	File panelFile;
	bool useOSDialog = panel ? (bool)panel->getCtrlrManagerOwner().getProperty(Ids::ctrlrNativeFileDialogs) : true;
	if (panel)
	{
		panelFileName = panel->getProperty(Ids::name);
		panelFileName << "_" + panel->getVersionString();
	}

	if (isXml)
	{
		if (isCompressed)
			panelFileName << ".panelz";
		else
			panelFileName << ".panel";
	}
	else
	{
		if (isCompressed)
			panelFileName << ".bpanelz";
		else
			panelFileName << ".bpanel";
	}

	if (File::isAbsolutePath(lastBrowsedDir.getFullPathName()))
	{
		panelFile = lastBrowsedDir.getChildFile(panelFileName);
	}
	else
	{
		panelFile = File::getSpecialLocation(File::userDocumentsDirectory).getChildFile(panelFileName);
	}

	if (isXml)
	{
		if (isCompressed)
		{
			FileChooser fileChooser ("Panel file XML compressed", panelFile, "*.panelz", useOSDialog);
			if (fileChooser.browseForFileToSave (true))
			{
				return (fileChooser.getResult().withFileExtension("panelz"));
			}
			else
			{
				if (panel)
					panel->notify ("Save file dialog failed", nullptr, NotifyFailure);
			}
		}
		else
		{
			FileChooser fileChooser ("Panel file XML", panelFile, "*.panel", useOSDialog);
			if (fileChooser.browseForFileToSave (true))
			{
				return (fileChooser.getResult().withFileExtension("panel"));
			}
			else
			{
				if (panel)
					panel->notify ("Save file dialog failed", nullptr, NotifyFailure);
			}
		}
	}
	else
	{
		if (isCompressed)
		{
			FileChooser fileChooser ("Panel file binary compressed", panelFile, "*.bpanelz", useOSDialog);
			if (fileChooser.browseForFileToSave (true))
			{
				return (fileChooser.getResult().withFileExtension("bpanelz"));
			}
			else
			{
				if (panel)
					panel->notify ("Save file dialog failed", nullptr, NotifyFailure);
			}
		}
		else
		{
			FileChooser fileChooser ("Panel file binary", panelFile, "*.bpanel", useOSDialog);
			if (fileChooser.browseForFileToSave (true))
			{
				return (fileChooser.getResult().withFileExtension("bpanel"));
			}
			else
			{
				if (panel)
					panel->notify ("Save file dialog failed", nullptr, NotifyFailure);
			}
		}
	}

	return (File::nonexistent);
}

bool CtrlrPanel::isPanelFile(const File &fileToCheck, const bool beThorough)
{
	if (beThorough)
	{
		return (false);
	}
	else
	{
		if (fileToCheck.hasFileExtension("bpanel;bpanelz;panel;panelz"))
		{
			return (true);
		}
		else
		{
			return (false);
		}
	}
}

void CtrlrPanel::setSavePoint()
{
	indexOfSavedState = currentActionIndex;
}

bool CtrlrPanel::hasChangedSinceSavePoint()
{
	return currentActionIndex != indexOfSavedState;
}

bool CtrlrPanel::isPanelDirty()
{
	return getProperty(Ids::panelIsDirty,false);
}

void CtrlrPanel::setPanelDirty(const bool dirty)
{
	setProperty(Ids::panelIsDirty, dirty);
}

void CtrlrPanel::actionPerformed()
{
	currentActionIndex++;
	updatePanelWindowTitle();
}

void CtrlrPanel::actionUndone()
{
	currentActionIndex--;
	updatePanelWindowTitle();
}

const String CtrlrPanel::getPanelWindowTitle()
{
	String name = getProperty(Ids::name);
	if (isPanelDirty() || hasChangedSinceSavePoint())
	{
		name = name + "*";
	}
	return name;
}

void CtrlrPanel::updatePanelWindowTitle()
{
	CtrlrPanelEditor *editor = getEditor(false);
	if (editor) 
	{
		String newName = getPanelWindowTitle();
		if (newName != editor->getName())
		{
			editor->setName(newName);
			// Trigger editor window title update
			owner.getEditor()->activeCtrlrChanged();
		}
	}
}

void CtrlrPanel::luaManagerChanged()
{
	if (!getRestoreState())
	{
		setPanelDirty(true);
		updatePanelWindowTitle();
	}
}

void CtrlrPanel::panelResourcesChanged()
{
	if (!getRestoreState())
	{
		setPanelDirty(true);
		updatePanelWindowTitle();
	}
}


bool CtrlrPanel::canClose(const bool closePanel)
{
	bool result = true;
	// Check for modified Lua Code
	CtrlrPanelWindowManager &manager = getWindowManager();
	if (manager.isCreated(CtrlrPanelWindowManager::LuaMethodEditor))
	{
		CtrlrChildWindowContent *content = manager.getContent(CtrlrPanelWindowManager::LuaMethodEditor);
		if (content != nullptr)
		{	// Move the editor to front
			content->toFront(true);
			if (!content->canCloseWindow())
			{
				result = false;
			}
		}
	}
	// Check for panel modifications
	if(closePanel && (hasChangedSinceSavePoint() || isPanelDirty()))
	{
		int ret = AlertWindow::showYesNoCancelBox(AlertWindow::QuestionIcon, "Save panel (" + getName() + ")", "There are unsaved changes in this panel. Do you want to save them berfore closing ?", "Save", "Discard", "Cancel");
		if (ret == 0)
		{	// Cancel
			result = false;
		}
		else if (ret == 1)
		{	// Save
			savePanel();
			result = true;
		}
		else
		{	// Discard
			result = true;
		}
	}
	return result;
}