#include "stdafx.h"
#include "CtrlrUtilities.h"
#include "CtrlrProcessor.h"
#include "CtrlrApplicationWindow/CtrlrEditor.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrProcessorEditorForLive.h"
#include "CtrlrLog.h"
#include "CtrlrPanel/CtrlrPanelMIDIInputThread.h"
#include "CtrlrPanel/CtrlrPanel.h"

const uint32 magicXmlNumber = 0x00001040;

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CtrlrProcessor();
}

CtrlrProcessor::CtrlrProcessor() : overridesTree(Ids::ctrlrOverrides), ctrlrManager(nullptr)
{
	midiCollector.reset (SAMPLERATE);

	currentExec		= File::getSpecialLocation(File::currentApplicationFile);
	overridesFile	= currentExec.withFileExtension("overrides");

	overridesTree.setProperty (Ids::ctrlrMaxExportedVstParameters, 64, 0);
	overridesTree.setProperty (Ids::ctrlrShutdownDelay, 512, 0);

	if (overridesFile.existsAsFile())
	{
		ScopedPointer <XmlElement> xml (XmlDocument(overridesFile).getDocumentElement());
		if (xml)
		{
			overridesTree = ValueTree::fromXml (*xml);
		}
	}

	ctrlrLog				= new CtrlrLog(overridesTree.getProperty (Ids::ctrlrLogToFile));
	ctrlrManager			= new CtrlrManager(this, *ctrlrLog);

	if (ctrlrManager->getInstanceMode() == InstanceSingle || ctrlrManager->getInstanceMode() == InstanceSingleRestriced)
	{
		if (ctrlrManager->getActivePanel())
		{
			ctrlrManager->getActivePanel()->initEmbeddedInstance();
		}
	}
}

CtrlrProcessor::~CtrlrProcessor()
{
	deleteAndZero (ctrlrLog);
	MessageManager::getInstance()->runDispatchLoopUntil((int)overridesTree.getProperty(Ids::ctrlrShutdownDelay));
}

const String CtrlrProcessor::getName() const
{
	if (ctrlrManager)
    {
		return (ctrlrManager->getInstanceNameForHost());
    }
	else
    {
		return ("Ctrlr");
    }
}

int CtrlrProcessor::getNumParameters()
{
	if (ctrlrManager)
		return (jmax(ctrlrManager->getNumModulators(true), (int)overridesTree.getProperty (Ids::ctrlrMaxExportedVstParameters)));
	else
		return (CTRLR_DEFAULT_PARAMETER_COUNT);
}

float CtrlrProcessor::getParameter (int index)
{
	CtrlrModulator *m = ctrlrManager->getModulatorByVstIndex (index);
	if (m)
	{
		return (m->getProcessor().getValueForHost());
	}
	else
	{
		return 0.0f;
	}
}

void CtrlrProcessor::setParameter (int index, float newValue)
{
	CtrlrModulator *m = ctrlrManager->getModulatorByVstIndex (index);
	if (m == nullptr)
	{
		return;
	}
	else if (newValue > 1.0f || newValue < 0.000000f)
	{
		return;
	}
	else
	{
		return (m->getProcessor().setValueFromHost(newValue));
	}
}

const String CtrlrProcessor::getParameterName (int index)
{
    if (ctrlrManager->getModulatorByVstIndex (index))
	{
		return (ctrlrManager->getModulatorByVstIndex (index)->getNameForHost());
	}
	else
	{
		return ("undefined_"+String(index));
	}
}

const String CtrlrProcessor::getParameterText (int index)
{
    if (ctrlrManager->getModulatorByVstIndex (index))
	{
		const String text = ctrlrManager->getModulatorByVstIndex (index)->getTextForHost();
		return (text);
	}
	else
	{
		return ("value_"+String(index));
	}
}

const String CtrlrProcessor::getInputChannelName (const int channelIndex) const
{
    if (channelIndex >= 1024)
    {
        /* used internally */
        switch (channelIndex)
        {
            case 1024:
                if (ctrlrManager)
                {
                    if (ctrlrManager->getActivePanel())
                    {
                        return (ctrlrManager->getActivePanel()->getProperty(Ids::panelInstanceUID));
                    }
                }
                return ("CTRL");

            case 1025:
                if (ctrlrManager)
                {
                    if (ctrlrManager->getActivePanel())
                    {
                        return (ctrlrManager->getActivePanel()->getProperty(Ids::panelAuthorName));
                    }
                }
                return ("Instigator");

            case 1026:
                if (ctrlrManager)
                {
                    if (ctrlrManager->getActivePanel())
                    {
                        return (ctrlrManager->getActivePanel()->getProperty(Ids::name));
                    }
                }
                return ("Ctrlr");

            case 1027:
                if (ctrlrManager)
                {
                    if (ctrlrManager->getActivePanel())
                    {
                        return (ctrlrManager->getActivePanel()->getProperty(Ids::panelVersionMajor));
                    }
                }
                return (ProjectInfo::versionString);

            default:
                break;
        }
    }
    return ("Audio Input: "+_STR(channelIndex));
}

const String CtrlrProcessor::getOutputChannelName (const int channelIndex) const
{
    return ("Audio Output: "+_STR(channelIndex));
}

bool CtrlrProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool CtrlrProcessor::isOutputChannelStereoPair (int index) const
{
    return (true);
}

bool CtrlrProcessor::acceptsMidi() const
{
	return (true);
}

bool CtrlrProcessor::producesMidi() const
{
    return (true);
}

int CtrlrProcessor::getNumPrograms()
{
    return (1);
}

int CtrlrProcessor::getCurrentProgram()
{
    return (1);
}

void CtrlrProcessor::setCurrentProgram (int index)
{
}

const String CtrlrProcessor::getProgramName (int index)
{
    return ("Default CTRLR program");
}

void CtrlrProcessor::changeProgramName (int index, const String& newName)
{
}

void CtrlrProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	midiCollector.reset (sampleRate);
	leftoverBuffer.ensureSize (8192);
}

void CtrlrProcessor::releaseResources()
{
}

void CtrlrProcessor::addMidiToOutputQueue (CtrlrMidiMessage &m)
{
	for (int i=0; i<m.getNumMessages(); i++)
	{
		midiCollector.addMessageToQueue (m.getReference(i).m);
	}
}

void CtrlrProcessor::addMidiToOutputQueue (const CtrlrMidiMessage &m)
{
	for (int i=0; i<m.getNumMessages(); i++)
	{
		m.getReference(i).m.setTimeStamp(i+1);
		midiCollector.addMessageToQueue (m.getReference(i).m);
	}
}

void CtrlrProcessor::addMidiToOutputQueue (const MidiMessage &m)
{
	midiCollector.addMessageToQueue (m);
}

void CtrlrProcessor::addMidiToOutputQueue (const MidiBuffer &buffer)
{
	MidiBuffer::Iterator i(buffer);
	MidiMessage m;
	int time;

	while (i.getNextEvent (m, time))
	{
		midiCollector.addMessageToQueue (m);
	}
}

void CtrlrProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	if (midiMessages.getNumEvents() > 0)
	{
		processPanels(midiMessages);
	}

	midiCollector.removeNextBlockOfMessages (midiMessages, buffer.getNumSamples());
}

bool CtrlrProcessor::hasEditor() const
{
    return true;
}

const var &CtrlrProcessor::getProperty (const Identifier& name) const
{
	if (ctrlrManager)
	{
		if (ctrlrManager->getManagerTree().hasProperty(name))
			return (ctrlrManager->getProperty(name));
		else
			return (overridesTree.getProperty(name));
	}
	else
	{
		return (overridesTree.getProperty(name));
	}
}

const bool CtrlrProcessor::hasProperty(const Identifier &name) const
{
	if (ctrlrManager->getManagerTree().hasProperty(name) || overridesTree.hasProperty(name))
		return (true);
	else
		return (false);
}

const bool CtrlrProcessor::useWrapper()
{
	if (JUCEApplication::isStandaloneApp())
	{
		return (false);
	}

	if (((SystemStats::getOperatingSystemType() & SystemStats::Windows) != 0) && host.isAbletonLive())
	{
		if (hasProperty(Ids::ctrlrUseEditorWrapper))
		{
			return ((bool)getProperty(Ids::ctrlrUseEditorWrapper));
		}
		else
		{
			return (true);
		}
	}
	return (false);
}

AudioProcessorEditor* CtrlrProcessor::createEditor()
{
	if (useWrapper())
	{
		return new CtrlrProcessorEditorForLive (this, *ctrlrManager);
	}
	else
	{
		return new CtrlrEditor (this, *ctrlrManager);
	}
}

void CtrlrProcessor::getStateInformation (MemoryBlock& destData)
{
	ScopedPointer <XmlElement> xml(ctrlrManager->saveState());
	if (xml)
	{
		CtrlrProcessor::copyXmlToBinary (*xml, destData);
	}
}

void CtrlrProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

	if (xmlState)
	{
		setStateInformation (xmlState);
	}
}

void CtrlrProcessor::setStateInformation (const XmlElement *xmlState)
{
	if (KeyPress::isKeyCurrentlyDown(KeyPress::createFromDescription("ctrl + R").getKeyCode()))
	{
		AlertWindow::showMessageBox (AlertWindow::WarningIcon, "Ctrlr v5", "Ctrl+R key is pressed, resetting to defaults");
		return;
	}

	if (xmlState)
	{
		ctrlrManager->restoreState (*xmlState);
	}
}

void CtrlrProcessor::setMidiOptions(const bool _thruHostToHost, const bool _thruHostToDevice, const bool _outputToHost, const bool _inputFromHost, const bool _thruFromHostChannelize)
{
	const ScopedLock sl(getCallbackLock());

	thruHostToHost				= _thruHostToHost;
	thruHostToDevice			= _thruHostToDevice;
	thruFromHostChannelize		= _thruFromHostChannelize;
	outputToHost				= _outputToHost;
	inputFromHost				= _inputFromHost;
}

void CtrlrProcessor::processPanels(MidiBuffer &midiMessages)
{
	for (int i=0; i<panelProcessors.size(); i++)
	{
		if (!panelProcessors[i].wasObjectDeleted())
		{
			panelProcessors[i]->processBlock (midiMessages, leftoverBuffer);
		}
	}
}

void CtrlrProcessor::addPanelProcessor (CtrlrPanelProcessor *processorToAdd)
{
	panelProcessors.addIfNotAlreadyThere (processorToAdd);
}

void CtrlrProcessor::removePanelProcessor (CtrlrPanelProcessor *processorToRemove)
{
	panelProcessors.removeAllInstancesOf (processorToRemove);
}

void CtrlrProcessor::copyXmlToBinary (const XmlElement& xml, juce::MemoryBlock& destData)
{
    const String xmlString (xml.createDocument (String::empty, true, false));
    const int stringLength = xmlString.getNumBytesAsUTF8();

    destData.setSize ((size_t) stringLength + 10);

    char* const d = static_cast<char*> (destData.getData());
    *(uint32*) d = ByteOrder::swapIfBigEndian ((const uint32) magicXmlNumber);
    *(uint32*) (d + 4) = ByteOrder::swapIfBigEndian ((const uint32) stringLength);

    xmlString.copyToUTF8 (d + 8, stringLength + 1);
}

XmlElement* CtrlrProcessor::getXmlFromBinary (const void* data, const int sizeInBytes)
{
    if (sizeInBytes > 8
         && ByteOrder::littleEndianInt (data) == magicXmlNumber)
    {
        const int stringLength = (int) ByteOrder::littleEndianInt (addBytesToPointer (data, 4));

        if (stringLength > 0)
            return XmlDocument::parse (String::fromUTF8 (static_cast<const char*> (data) + 8,
                                                         jmin ((sizeInBytes - 8), stringLength)));
    }

    return nullptr;
}

void CtrlrProcessor::openFileFromCli(const File &file)
{
	if (ctrlrManager)
	{
		ctrlrManager->openPanelInternal (file);
	}
}
