#include "stdafx.h"
#include "CtrlrLuaObjectWrapper.h"
#include "CtrlrManager/CtrlrManager.h"
#include "../../CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrWaveform.h"
#include "CtrlrLuaAudioConverter.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrLuaManager.h"

CtrlrWaveform::CtrlrWaveform (CtrlrModulator &owner)
    : CtrlrComponent(owner),
	  audioThumbnail(nullptr),
	  audioBufferCopy(1,0),
	  qualityForAudioFiles(0)
{
	audioThumbnail			= new AudioThumbnail (1, owner.getOwner().getOwner().getAudioFormatManager(), owner.getOwner().getOwner().getAudioThumbnailCache());
	audioThumbnail->addChangeListener (this);

	setProperty (Ids::uiWaveformColour, "0xff000000");
	setProperty (Ids::uiWaveformBackgroundColour1, "0x79ffffff");
	setProperty (Ids::uiWaveformBackgroundColour2, "0x79a0a0a0");
	setProperty (Ids::uiWaveformOutlineColour, "0xff000000");
	setProperty (Ids::uiWaveformOutlineThickness, 1);
	setProperty (Ids::uiWaveformSourceSamplesPerThumbnailSample, 1);
	setProperty (Ids::uiWaveFormVeritcalZoomFactor, 1.0);
	setProperty (Ids::uiWaveFormDrawSecondsStart, 0.0);
	setProperty (Ids::uiWaveFormDrawSecondsEnd, 1.0);
	setProperty (Ids::uiWaveFormThumbnailChangedCallback, COMBO_NONE_ITEM);
	setProperty (Ids::uiWaveFormSourceChangedCallback, COMBO_NONE_ITEM);
	setProperty (Ids::uiWaveFormFilesDroppedCallback, COMBO_NONE_ITEM);
    setSize (256, 128);
}

CtrlrWaveform::~CtrlrWaveform()
{
}

void CtrlrWaveform::mouseDown (const MouseEvent &e)
{
}

void CtrlrWaveform::paint (Graphics& g)
{
	Rectangle<int> r = getUsableRect();

	g.setGradientFill (ColourGradient (VAR2COLOUR(getProperty (Ids::uiWaveformBackgroundColour1)),
                                       (float) (r.getWidth()/2), 0.0f,
                                       VAR2COLOUR(getProperty (Ids::uiWaveformBackgroundColour2)),
                                       (float) (r.getWidth()/2), (float) r.getHeight(),
                                       false));
	g.fillRect (r.withSize(r.getWidth(), r.getHeight()));

	g.setColour (VAR2COLOUR(getProperty (Ids::uiWaveformOutlineColour)));

	const int t = getProperty (Ids::uiWaveformOutlineThickness);
	g.drawRect (r.withSize(r.getWidth(), r.getHeight()), t);

	g.setColour (VAR2COLOUR(getProperty (Ids::uiWaveformColour)));

	if (drawSecondsEnd < 0)
	{
		audioThumbnail->drawChannels (g, r, drawSecondsStart, audioThumbnail->getTotalLength(), drawVerticalZoom);
	}
	else
	{
		audioThumbnail->drawChannels (g, r, drawSecondsStart, drawSecondsEnd, drawVerticalZoom);
	}
}

void CtrlrWaveform::resized()
{
	CtrlrComponent::resized();
}

void CtrlrWaveform::setComponentValue (const double newValue, const bool sendChangeMessage)
{
}

const double CtrlrWaveform::getComponentValue()
{
	return (1);
}

const int CtrlrWaveform::getComponentMidiValue()
{
	return (1);
}

const double CtrlrWaveform::getComponentMaxValue()
{
	return (roundFloatToInt(getApproximatePeak()));
}

const String CtrlrWaveform::getComponentText()
{
	return (currentFile.getFullPathName());
}

const PopupMenu CtrlrWaveform::getComponentMenu(const MouseEvent &e)
{
	PopupMenu m;
	m.addSectionHeader ("Waveform");

	m.addItem (4096, audioThumbnail->isFullyLoaded() ? "Load from file" : "Stop loading");
	m.addItem (4097, "Edit shape", audioThumbnail->isFullyLoaded());
	m.addItem (4098, "Save to file", audioThumbnail->isFullyLoaded());

	return (m);
}

void CtrlrWaveform::handlePopupMenu (const int popupMenuItem)
{
	if (popupMenuItem == 4096)
	{
		if (audioThumbnail->isFullyLoaded())
		{
			FileChooser fc("Load a file", currentFile.getParentDirectory(), owner.getOwner().getOwner().getAudioFormatManager().getWildcardForAllFormats(), true);
			if (fc.browseForFileToOpen())
			{
				loadFromFile (fc.getResult());
			}
		}
		else
		{
			audioThumbnail->clear();
		}
	}
	else if (popupMenuItem == 4097)
	{
		WARN("Not implemented yet :(");
	}
	else if (popupMenuItem == 4098)
	{
		FileChooser fc("Save to an audio file", currentFile.getParentDirectory(), owner.getOwner().getOwner().getAudioFormatManager().getWildcardForAllFormats(), true);

		if (fc.browseForFileToSave(true))
		{
			File outputFile = fc.getResult();

			AudioFormat *format = owner.getOwner().getOwner().getAudioFormatManager().findFormatForFileExtension (outputFile.getFileExtension());

			if (format != nullptr)
			{
				{
					ScopedPointer <AudioFormatWriter> writer (format->createWriterFor (outputFile.createOutputStream(),
																						currentSampleRate,
																						audioThumbnail->getNumChannels(),
																						32,
																						metadataForAudioFiles,
																						qualityForAudioFiles));

					if (writer != nullptr)
					{
						writer->writeFromAudioSampleBuffer (audioBufferCopy, 0, audioBufferCopy.getNumSamples());
					}
					else
					{
						if (owner.getOwner().getDialogStatus())
							WARN ("Can't create AudioFormatWriter sampleRate="+String(currentSampleRate)+", channels="+String(audioThumbnail->getNumChannels())+", bitsPerSample=32, qualityIndex="+String(qualityForAudioFiles));
					}
				}
			}
			else
			{
				if (owner.getOwner().getDialogStatus())
					WARN("Can't find AudioFormat for the file: "+outputFile.getFileName());
				return;
			}
		}
	}
}

void CtrlrWaveform::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiWaveformBackgroundColour1
		|| property == Ids::uiWaveformBackgroundColour2
		|| property == Ids::uiWaveformOutlineColour
		|| property == Ids::uiWaveformColour
		|| property == Ids::uiWaveformOutlineThickness)
	{
		repaint();
	}
	else if (property == Ids::uiWaveformSourceSamplesPerThumbnailSample)
	{
		if (audioThumbnail)
			delete audioThumbnail.release();

		audioThumbnail	= new AudioThumbnail (getProperty(property), owner.getOwner().getOwner().getAudioFormatManager(), owner.getOwner().getOwner().getAudioThumbnailCache());
		audioThumbnail->addChangeListener (this);
		audioThumbnail->clear();
		audioBufferCopy.clear();

		repaint();
	}
	else if (property == Ids::uiWaveFormDrawSecondsStart)
	{
		drawSecondsStart = getProperty(property);
		repaint();
	}
	else if (property == Ids::uiWaveFormDrawSecondsEnd)
	{
		drawSecondsEnd = getProperty(property);
		repaint();
	}
	else if (property == Ids::uiWaveFormVeritcalZoomFactor)
	{
		drawVerticalZoom = getProperty(property);
		repaint();
	}
	else if (property == Ids::uiWaveFormThumbnailChangedCallback)
	{
		if (isInvalidMethodName(getProperty (property)))
			return;

		thumbnailChangedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiWaveFormSourceChangedCallback)
	{
		if (isInvalidMethodName(getProperty (property)))
			return;

		sourceChangedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiWaveFormFilesDroppedCallback)
	{
		if (isInvalidMethodName(getProperty (property)))
			return;

		fileDroppedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}

	if (restoreStateInProgress == false)
	{
		resized();
	}

	CtrlrComponent::valueTreePropertyChanged(treeWhosePropertyHasChanged, property);
}

void CtrlrWaveform::changeListenerCallback (ChangeBroadcaster* source)
{
	if (source == audioThumbnail)
	{
		if (thumbnailChangedCbk && !thumbnailChangedCbk.wasObjectDeleted())
		{
			if (thumbnailChangedCbk->isValid())
			{
				owner.getOwner().getCtrlrLuaManager().getMethodManager().call (thumbnailChangedCbk, this);
			}
		}
		repaint();
	}
	CtrlrComponent::changeListenerCallback (source);
}

void CtrlrWaveform::setReader (AudioFormatReader *newReader, double hashCode)
{
	audioThumbnail->setReader (newReader, hashCode);
	repaint();
}

void CtrlrWaveform::addBlock (double sampleNumberInsource, const AudioSampleBuffer &newData, int startOffsetInBuffer, int numSamples)
{
	int sampleToAddAt = 0;

	if (audioBufferCopy.getNumSamples() == 0)
	{
		/* Initialize the buffer */
		audioBufferCopy.setSize (newData.getNumChannels(), newData.getNumSamples());
	}
	else
	{
		/* it's already filled, just extend it */
		sampleToAddAt = audioBufferCopy.getNumSamples();

		if (newData.getNumChannels() > audioBufferCopy.getNumChannels())
		{
			audioBufferCopy.setSize (newData.getNumChannels(), audioBufferCopy.getNumSamples() + newData.getNumSamples(), true);
		}
		else
		{
			audioBufferCopy.setSize (audioBufferCopy.getNumChannels(), audioBufferCopy.getNumSamples() + newData.getNumSamples(), true);
		}
	}

	for (int i=0; i<newData.getNumChannels(); i++)
	{
		audioBufferCopy.copyFrom (i, sampleToAddAt, newData, i, startOffsetInBuffer, numSamples);
	}

	audioThumbnail->addBlock (sampleNumberInsource, newData, startOffsetInBuffer, numSamples);
	repaint();
}

void CtrlrWaveform::reset (int numChannels, double sampleRate, double totalSamplesInSource)
{
	currentFile			= File::nonexistent;
	currentSampleRate	= sampleRate;

	audioBufferCopy		= AudioSampleBuffer (numChannels, totalSamplesInSource);

	audioThumbnail->reset (numChannels, sampleRate, totalSamplesInSource);

	if (sourceChangedCbk && !sourceChangedCbk.wasObjectDeleted())
	{
		if (sourceChangedCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (sourceChangedCbk, this);
		}
	}
}

const bool CtrlrWaveform::loadFromFile (const File &fileToLoadFrom)
{
	currentFile = fileToLoadFrom;

	AudioFormatReader *reader = owner.getOwner().getOwner().getAudioFormatManager().createReaderFor (currentFile);

	if (sourceChangedCbk && !sourceChangedCbk.wasObjectDeleted())
	{
		if (sourceChangedCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (sourceChangedCbk, this);
		}
	}

	if (reader)
	{
		setReader (reader, Random::getSystemRandom().nextInt64());
		return (true);
	}
	else
	{
		return (false);
	}
}

const bool CtrlrWaveform::loadFromFile (const String &filePath)
{
	File file(filePath);

	if (file.existsAsFile())
	{
		return (loadFromFile (file));
	}

	return (false);
}

void CtrlrWaveform::setStart (const double seconds)
{
	setProperty (Ids::uiWaveFormDrawSecondsStart, seconds);
}

void CtrlrWaveform::setEnd (const double seconds)
{
	setProperty (Ids::uiWaveFormDrawSecondsEnd, seconds);
}

void CtrlrWaveform::setVerticalZoomFactor (const float verticalZoomFactor)
{
	setProperty (Ids::uiWaveFormVeritcalZoomFactor, verticalZoomFactor);
}

void CtrlrWaveform::setSourceSamplesPerThumbnailSample (int sourceSamplesPerThumbnailSample)
{
	setProperty (Ids::uiWaveformSourceSamplesPerThumbnailSample, sourceSamplesPerThumbnailSample);
}

AudioSampleBuffer &CtrlrWaveform::getCurrentAudioBuffer()
{
	return (audioBufferCopy);
}

File CtrlrWaveform::getCurrentFile()
{
	return (currentFile);
}

double CtrlrWaveform::getTotalLength()
{
	return (audioThumbnail->getTotalLength());
}

bool CtrlrWaveform::isFullyLoaded()
{
	return (audioThumbnail->isFullyLoaded());
}

double CtrlrWaveform::getNumSamplesFinished()
{
	return (audioThumbnail->getNumSamplesFinished());
}

float CtrlrWaveform::getApproximatePeak()
{
	return (audioThumbnail->getApproximatePeak());
}

void CtrlrWaveform::getApproximateMinMax (double startTime, double endTime, int channelIndex, float &minValue, float &maxValue)
{
	audioThumbnail->getApproximateMinMax(startTime, endTime, channelIndex, minValue, maxValue);
}

double CtrlrWaveform::getHashCode()
{
	return (audioThumbnail->getHashCode());
}

int CtrlrWaveform::getNumChannels()
{
	return (audioThumbnail->getNumChannels());
}

void CtrlrWaveform::clear()
{
	audioBufferCopy.clear();
	audioThumbnail->clear();
}

bool CtrlrWaveform::isInterestedInFileDrag (const StringArray &files)
{
	return (true);
}

void CtrlrWaveform::filesDropped (const StringArray &files, int x, int y)
{
	if (fileDroppedCbk && !fileDroppedCbk.wasObjectDeleted())
	{
		if (fileDroppedCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (fileDroppedCbk, files, x, y);
		}
	}
	else if (files.size() == 1)
	{
		loadFromFile (files[0]);
	}
}

void CtrlrWaveform::fileDragExit (const StringArray &files)
{
}

void CtrlrWaveform::fileDragEnter (const StringArray &files, int x, int y)
{
}

void CtrlrWaveform::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrWaveform,bases<CtrlrComponent,CtrlrLuaObject> >("CtrlrWaveform")
			.def("setReader", &CtrlrWaveform::setReader)
			.def("reset", &CtrlrWaveform::reset)
			.def("addBlock", &CtrlrWaveform::addBlock)
			.def("loadFromFile", (const bool (CtrlrWaveform::*)(const File &))&CtrlrWaveform::loadFromFile)
			.def("loadFromFile", (const bool (CtrlrWaveform::*)(const String &))&CtrlrWaveform::loadFromFile)
			.def("getCurrentFile", &CtrlrWaveform::getCurrentFile)
			.def("getCurrentAudioBuffer", &CtrlrWaveform::getCurrentAudioBuffer)
			.def("setVerticalZoomFactor", &CtrlrWaveform::setVerticalZoomFactor)
			.def("setSourceSamplesPerThumbnailSample", &CtrlrWaveform::setSourceSamplesPerThumbnailSample)
			.def("setStart", &CtrlrWaveform::setStart)
			.def("setEnd", &CtrlrWaveform::setEnd)
			.def("clear", &CtrlrWaveform::clear)
			.def("getNumChannels", &CtrlrWaveform::getNumChannels)
			.def("getHashCode", &CtrlrWaveform::getHashCode)
			.def("getApproximateMinMax", &CtrlrWaveform::getApproximateMinMax)
			.def("getApproximatePeak", &CtrlrWaveform::getApproximatePeak)
			.def("getNumSamplesFinished", &CtrlrWaveform::getNumSamplesFinished)
			.def("isFullyLoaded", &CtrlrWaveform::isFullyLoaded)
			.def("getTotalLength", &CtrlrWaveform::getTotalLength)
	];
}
