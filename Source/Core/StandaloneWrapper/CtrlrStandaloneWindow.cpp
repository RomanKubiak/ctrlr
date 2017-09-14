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
	filter = createPluginFilter();
	centreWithSize(800, 600);
	setTitleBarButtonsRequired (DocumentWindow::allButtons, false);
	setUsingNativeTitleBar (true);
	setResizable(true, false);

    if (filter != 0)
	{
			ctrlrProcessor = dynamic_cast<CtrlrProcessor*>(filter);

			if (ctrlrProcessor == nullptr)
			{
				AlertWindow::showMessageBox (AlertWindow::WarningIcon, "CTRLR", "The filter object is not a valid Ctrlr Processor");
				return;
			}

			/* set some default audio stuff so the filter works without the audio card */
            //ctrlrProcessor->setPlayConfigDetails (0, 0, SAMPLERATE, 512);
			ctrlrProcessor->setRateAndBufferSizeDetails(SAMPLERATE, 512);
			addKeyListener (ctrlrProcessor->getManager().getCommandManager().getKeyMappings());

            /* we want to listen too manager actions */
            ctrlrProcessor->getManager().addActionListener (this);

			/* get the properties pointer from the manager */
			appProperties = ctrlrProcessor->getManager().getApplicationProperties();

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
					if (ctrlrProcessor->getManager().getInstanceTree().getChildWithName(Ids::uiPanelEditor).isValid())
					{
						ValueTree ed = ctrlrProcessor->getManager().getInstanceTree().getChildWithName(Ids::uiPanelEditor);
						Rectangle<int> r = VAR2RECT(ed.getProperty(Ids::uiPanelCanvasRectangle, "0 0 800 600"));
						centreWithSize (r.getWidth(), r.getHeight() + ((bool)ed.getProperty(Ids::uiPanelMenuBarVisible) ? CTRLR_MENUBAR_HEIGHT : 0));
					}
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

CtrlrStandaloneWindow::~CtrlrStandaloneWindow()
{
    ctrlrProcessor->getManager().removeActionListener (this);
    saveStateNow();
    deleteFilter();
}

void CtrlrStandaloneWindow::actionListenerCallback(const String &message)
{
    if (message == "save")
    {
        saveStateNow();
    }
}

void CtrlrStandaloneWindow::saveStateNow()
{
    _DBG("CtrlrStandaloneWindow::saveStateNow");

    if (ctrlrProcessor != nullptr && appProperties != nullptr)
    {
		appProperties->getUserSettings()->setValue (CTRLR_PROPERTIES_WINDOW_STATE, getWindowStateAsString());

		MemoryBlock data;
		ctrlrProcessor->getStateInformation(data);

		if (data.getSize() > 0)
		{
			ScopedPointer <XmlElement> xml(CtrlrProcessor::getXmlFromBinary(data.getData(), (int)data.getSize()));

			if (xml)
			{
				appProperties->getUserSettings()->setValue (CTRLR_PROPERTIES_FILTER_STATE, xml);
			}
		}
	}
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

void CtrlrStandaloneWindow::moved()
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
