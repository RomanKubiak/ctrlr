#ifndef __CTRLR_WAVEFORM__
#define __CTRLR_WAVEFORM__

#include "../CtrlrComponent.h"
class CtrlrLuaAudioSampleBuffer;

class CtrlrWaveform  : public CtrlrComponent, public FileDragAndDropTarget
{
	public:
		CtrlrWaveform (CtrlrModulator &owner);
		~CtrlrWaveform();
		void setComponentValue (const double newValue, const bool sendChangeMessage=false);
		const double getComponentValue();
		const int getComponentMidiValue();
		const double getComponentMaxValue();
		const String getComponentText();
		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
		void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
		void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
		void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
		void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
		void changeListenerCallback (ChangeBroadcaster* source);
		static void wrapForLua(lua_State *L);
		void paint (Graphics& g);
		void resized();
		const PopupMenu getComponentMenu(const MouseEvent &e);
		void handlePopupMenu (const int popupMenuItem);
		void mouseDown (const MouseEvent &e);
		void setStart (const double seconds);
		void setEnd (const double seconds);
		void setVerticalZoomFactor (const float verticalZoomFactor);
		void setSourceSamplesPerThumbnailSample (int sourceSamplesPerThumbnailSample);

		void setReader (AudioFormatReader *newReader, double hashCode);
		void addBlock (double sampleNumberInsource, const AudioSampleBuffer &newData, int startOffsetInBuffer, int numSamples);
		void reset (int numChannels, double sampleRate, double totalSamplesInSource);
		const bool loadFromFile (const File &fileToLoadFrom);
		const bool loadFromFile (const std::string &filePath);
		const bool loadFromFile (const String &filePath);

		bool isInterestedInFileDrag (const StringArray &files);
		void filesDropped (const StringArray &files, int x, int y);
		void fileDragExit (const StringArray &files);
		void fileDragEnter (const StringArray &files, int x, int y);

		AudioSampleBuffer &getCurrentAudioBuffer();
		File getCurrentFile();

		double getTotalLength();
		bool isFullyLoaded();
		double getNumSamplesFinished();
		float getApproximatePeak();
		void getApproximateMinMax (double startTime, double endTime, int channelIndex, float &minValue, float &maxValue);
		double getHashCode();
		int getNumChannels();
		void clear();
		
		JUCE_LEAK_DETECTOR(CtrlrWaveform)

	private:
		WeakReference <CtrlrLuaMethod> thumbnailChangedCbk, sourceChangedCbk, fileDroppedCbk;
		File currentFile;
		double currentSampleRate;
		ScopedPointer <AudioThumbnail> audioThumbnail;
		AudioSampleBuffer audioBufferCopy;
		double drawSecondsStart, drawSecondsEnd; double drawVerticalZoom;
		StringPairArray metadataForAudioFiles;
		int qualityForAudioFiles;
};


#endif
