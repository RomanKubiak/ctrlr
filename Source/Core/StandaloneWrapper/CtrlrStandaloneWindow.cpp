#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrProcessor.h"
#include "CtrlrStandaloneWindow.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"

extern AudioProcessor* JUCE_CALLTYPE createPluginFilter();

CtrlrStandaloneWindow::CtrlrStandaloneWindow (const String& title, const Colour& backgroundColour)
	:	DocumentWindow (title, backgroundColour, DocumentWindow::allButtons, true), 
		ctrlrProcessor(nullptr), 
		filter(nullptr),
		appProperties(nullptr),
		restoreState(true)
{
	setTitleBarButtonsRequired (DocumentWindow::allButtons, false);
	setUsingNativeTitleBar (true);

    JUCE_TRY
    {
        filter = createPluginFilter();

        if (filter != 0)
        {
			ctrlrProcessor = dynamic_cast<CtrlrProcessor*>(filter);

			if (ctrlrProcessor == nullptr)
			{
				AlertWindow::showMessageBox (AlertWindow::WarningIcon, "CTRLR", "The filter object is not a valid Ctrlr Processor");
				return;
			}

			/* set some default audio stuff so the filter works without the audio card */
            ctrlrProcessor->setPlayConfigDetails (2, 2, SAMPLERATE, 512);

			addKeyListener (ctrlrProcessor->getManager().getCommandManager().getKeyMappings());

			/* get the properties pointer from the manager */
			appProperties = ctrlrProcessor->getManager().getApplicationProperties();

			setResizable (true, false);

			if (appProperties != nullptr)
			{
				ScopedPointer <XmlElement> xml(appProperties->getUserSettings()->getXmlValue(CTRLR_PROPERTIES_FILTER_STATE));

				if (xml != nullptr)
				{
					ctrlrProcessor->setStateInformation (xml);
				}
				

				AudioProcessorEditor *editor = ctrlrProcessor->createEditorIfNeeded();
				setName (ctrlrProcessor->getManager().getInstanceName());

				if (appProperties->getUserSettings()->getValue(CTRLR_PROPERTIES_WINDOW_STATE,String::empty) != String::empty)
				{
					restoreWindowStateFromString (appProperties->getUserSettings()->getValue(CTRLR_PROPERTIES_WINDOW_STATE));
				}
				else
				{
					Rectangle<int> r = VAR2RECT(ctrlrProcessor->getManager().getInstanceTree().getChildWithName(Ids::uiPanelEditor).getProperty(Ids::uiPanelCanvasRectangle, "0 0 800 600"));
					centreWithSize (r.getWidth(), r.getHeight()+CTRLR_MENUBAR_HEIGHT/*Menubar*/);
				}

				setContentOwned (editor, false);
			}
			else
			{
				AlertWindow::showMessageBox (AlertWindow::WarningIcon, "CTRLR", "Can't find any application properties");
			}
        }

		restoreState = false;
		setVisible (true);
    }
    JUCE_CATCH_ALL
}

CtrlrStandaloneWindow::~CtrlrStandaloneWindow()
{
    if (ctrlrProcessor != nullptr && appProperties != nullptr)
    {
		appProperties->getUserSettings()->setValue (CTRLR_PROPERTIES_WINDOW_STATE, getWindowStateAsString());

		MemoryBlock data;
		ctrlrProcessor->getStateInformation(data);

		if (data.getSize() > 0)
		{
			ScopedPointer <XmlElement> xml(CtrlrProcessor::getXmlFromBinary(data.getData(), data.getSize()));

			if (xml)
			{
				appProperties->getUserSettings()->setValue (CTRLR_PROPERTIES_FILTER_STATE, xml);
			}
		}
	}

    deleteFilter();
}

void CtrlrStandaloneWindow::deleteFilter()
{
    if (filter != 0 && getContentComponent() != 0)
    {
        filter->editorBeingDeleted (dynamic_cast <AudioProcessorEditor*> (getContentComponent()));
		clearContentComponent ();
    }

    deleteAndZero (filter);
}

PropertySet* CtrlrStandaloneWindow::getGlobalSettings()
{
    return ctrlrProcessor->getManager().getCtrlrProperties().getProperties().getUserSettings();
}

void CtrlrStandaloneWindow::closeButtonPressed()
{
	JUCEApplication::quit();
}

void CtrlrStandaloneWindow::resized()
{
	DocumentWindow::resized();

	if (appProperties != nullptr && !restoreState)
	{
		appProperties->getUserSettings()->setValue (CTRLR_PROPERTIES_WINDOW_STATE, getWindowStateAsString());
	}
}

void CtrlrStandaloneWindow::moveed()
{
	DocumentWindow::moved();

	if (appProperties != nullptr)
	{
		appProperties->getUserSettings()->setValue (CTRLR_PROPERTIES_WINDOW_STATE, getWindowStateAsString());
	}
}

AudioProcessor *CtrlrStandaloneWindow::getFilter()
{
	return (filter);
}

void CtrlrStandaloneWindow::openFileFromCli(const File &file)
{
	if (ctrlrProcessor)
	{
		ctrlrProcessor->openFileFromCli (file);
	}
}