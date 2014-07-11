#include "stdafx.h"
#include "CtrlrUtilities.h"
#include "CtrlrLog.h"
#include "CtrlrPanel.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrPanel/CtrlrPanelResourceManager.h"
#include "CtrlrPanel/CtrlrPanelResource.h"
#include "CtrlrProcessor.h"
#include "CtrlrMIDILibrary/CtrlrMIDILibrary.h"
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

	return (exportTree);
}

Result CtrlrPanel::savePanel()
{
	_DBG("CtrlrPanel::savePanel");

	Result res = Result::ok();
	File panelFile(getProperty (Ids::panelFilePath));

	if (panelFile.existsAsFile() && panelFile.hasWriteAccess())
	{
		if (panelFile.hasFileExtension("panel"))
			res = savePanelXml (panelFile, this, false);
		if (panelFile.hasFileExtension("panelz"))
			res = savePanelXml (panelFile, this, true);
		if (panelFile.hasFileExtension("bpanel"))
			res = savePanelBin (panelFile, this, false);
		if (panelFile.hasFileExtension("bpanelz"))
			res = savePanelXml (panelFile, this, true);

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

		return (res);
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

		return (res);
	}
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
		Result res = owner.getNativeObject().exportWithDefaultPanel(this, false);
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
        else
        {
            privateKey = owner.getCtrlrPrivateKey();
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

	if (panel->getEditor()->getCanvas())
	{
		Image snap	= panel->getEditor()->getCanvas()->createComponentSnapshot (panel->getEditor()->getCanvas()->getBounds(), true);
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
			tree = ValueTree::readFromStream (gzFileInputStream);
			return (tree);
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
	ScopedPointer <XmlElement> xml;
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
	if (panelFile.hasFileExtension("panelz;panel"))
	{
		return (openXmlPanel(panelFile));
	}

	if (panelFile.hasFileExtension("bpanelz;bpanel"))
	{
		return (openBinPanel(panelFile));
	}

	return  (ValueTree());
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

const File CtrlrPanel::askForPanelFileToSave (CtrlrPanel *possiblePanel, const File &lastBrowsedDir, const bool isXml, const bool isCompressed)
{
	String panelFileName = "Ctrlr Panel";
	File panelFile;

	if (possiblePanel)
	{
		panelFileName = possiblePanel->getProperty(Ids::name);
		panelFileName << "_" + possiblePanel->getVersionString();
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
			FileChooser fileChooser ("Panel file XML compressed", panelFile, "*.panelz");
			if (fileChooser.browseForFileToSave (true))
			{
				return (fileChooser.getResult().withFileExtension("panelz"));
			}
			else
			{
				if (possiblePanel)
					possiblePanel->notify ("Save file dialog failed", nullptr, NotifyFailure);
			}
		}
		else
		{
			FileChooser fileChooser ("Panel file XML", panelFile, "*.panel");
			if (fileChooser.browseForFileToSave (true))
			{
				return (fileChooser.getResult().withFileExtension("panel"));
			}
			else
			{
				if (possiblePanel)
					possiblePanel->notify ("Save file dialog failed", nullptr, NotifyFailure);
			}
		}
	}
	else
	{
		if (isCompressed)
		{
			FileChooser fileChooser ("Panel file binary compressed", panelFile, "*.bpanelz");
			if (fileChooser.browseForFileToSave (true))
			{
				return (fileChooser.getResult().withFileExtension("bpanelz"));
			}
			else
			{
				if (possiblePanel)
					possiblePanel->notify ("Save file dialog failed", nullptr, NotifyFailure);
			}
		}
		else
		{
			FileChooser fileChooser ("Panel file binary", panelFile, "*.bpanel");
			if (fileChooser.browseForFileToSave (true))
			{
				return (fileChooser.getResult().withFileExtension("bpanel"));
			}
			else
			{
				if (possiblePanel)
					possiblePanel->notify ("Save file dialog failed", nullptr, NotifyFailure);
			}
		}
	}

	return (File::nonexistent);
}

const bool CtrlrPanel::isPanelFile(const File &fileToCheck, const bool beThorough)
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
