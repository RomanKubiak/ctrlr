#ifndef __CTRLR_PROCESSOR__
#define __CTRLR_PROCESSOR__

#include "CtrlrProperties.h"
#include "CtrlrPanel/CtrlrPanelProcessor.h"
#include "juce_PluginHostType.h"
#include "boost/bind.hpp"
#include "boost/function.hpp"

class CtrlrLog;
class CtrlrManager;

typedef WeakReference<CtrlrPanelProcessor>	PanelProcessorReference;
typedef WeakReference<CtrlrModulator> ModulatorReference;

struct CtrlrParameterFromHost
{
	CtrlrParameterFromHost(const int _index, const float _value)
		: index(_index), value(_value) {}
	CtrlrParameterFromHost()
		: index(-1), value(0.0f) {}
	int index;
	float value;
};

class CtrlrProcessor  : public AudioProcessor
{
	public:
	    CtrlrProcessor();
		~CtrlrProcessor();
		void prepareToPlay (double sampleRate, int samplesPerBlock);
		void releaseResources();
		void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
		AudioProcessorEditor* createEditor();
		const bool useWrapper();
		bool hasEditor() const;
		const String getName() const;
		int getNumParameters();
		float getParameter (int index);
		void setParameter (int index, float newValue);
		const String getParameterName (int index);
		const String getParameterText (int index);
		const String getInputChannelName (int channelIndex) const;
		const String getOutputChannelName (int channelIndex) const;
		bool isInputChannelStereoPair (int index) const;
		bool isOutputChannelStereoPair (int index) const;
		int getNumInputChannels()										{ return (2); }
		int getNumOutputChannels()										{ return (2); }
		bool acceptsMidi() const;
		bool producesMidi() const;
		int getNumPrograms();
		int getCurrentProgram();
		void setCurrentProgram (int index);
		const String getProgramName (int index);
		void changeProgramName (int index, const String& newName);
		bool silenceInProducesSilenceOut() const						{ return (true); }
		static XmlElement* getXmlFromBinary (const void* data, const int sizeInBytes);
		static void copyXmlToBinary (const XmlElement& xml, juce::MemoryBlock& destData);
		double getTailLengthSeconds() const { return (0); }
		void getStateInformation (MemoryBlock& destData);
		void setStateInformation (const void* data, int sizeInBytes);
		void setStateInformation (const XmlElement *xmlState);
		CtrlrLog &getCtrlrLog()										{ return (*ctrlrLog); }
		CtrlrManager &getManager()									{ return (*ctrlrManager); }
		ValueTree getOverrides()									{ return (overridesTree); }
		void addMidiToOutputQueue (CtrlrMidiMessage &m);
		void addMidiToOutputQueue (const CtrlrMidiMessage &m);
		void addMidiToOutputQueue (const MidiMessage &m);
		void addMidiToOutputQueue (const MidiBuffer &buffer);
		void setMidiOptions(const bool _thruHostToHost, const bool _thruHostToDevice, const bool _outputToHost, const bool _inputFromHost, const bool _thruFromHostChannelize);
		void processPanels(MidiBuffer &midiMessages);
		void addPanelProcessor (CtrlrPanelProcessor *processorToAdd);
		void removePanelProcessor (CtrlrPanelProcessor *processorToRemove);
		void setParameterHandler (int index, float value);
		void openFileFromCli(const File &file);
		AudioPlayHead::CurrentPositionInfo lastPosInfo;
		const var &getProperty (const Identifier& name) const;
		const bool hasProperty(const Identifier &name) const;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrProcessor);

	private:
        ::PluginHostType host;
		MidiBuffer leftoverBuffer;
		CtrlrLog *ctrlrLog;
		ScopedPointer <CtrlrManager> ctrlrManager;
		File currentExec;
		File overridesFile;
		ValueTree overridesTree;
		MidiMessageCollector midiCollector;
		Array <PanelProcessorReference,CriticalSection> panelProcessors;
		Array <CtrlrParameterFromHost,CriticalSection> parameterUpdates;
		bool	thruHostToHost,
				thruHostToDevice,
				thruFromHostChannelize,
				outputToHost,
				inputFromHost;
};

#endif
