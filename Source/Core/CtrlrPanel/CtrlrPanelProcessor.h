#ifndef CTRLR_PANEL_PROCESSOR
#define CTRLR_PANEL_PROCESSOR

#include "CtrlrMacros.h"
#include "Methods/CtrlrLuaMethod.h"

class CtrlrPanel;

class CtrlrPanelProcessor : public AsyncUpdater, public CtrlrPanelMidiProcessor
{
	public:
		CtrlrPanelProcessor(CtrlrPanel &_owner);
		virtual ~CtrlrPanelProcessor();
		void handleAsyncUpdate();
		void processBlock(MidiBuffer &midiMessages, MidiBuffer &leftoverBuffer, const AudioPlayHead::CurrentPositionInfo &positionInfo);
		void midiOptionChanged(const CtrlrPanelMidiOption optionThatChanged);
		void midiChannelChaned(const CtrlrPanelMidiChannel /*channelThatChanged*/){}
		void processLua(MidiBuffer &midiMessages, const AudioPlayHead::CurrentPositionInfo &info);
		CtrlrPanel &getOwner();

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrPanelProcessor)

	private:
		WeakReference<CtrlrPanelProcessor>::Master masterReference;
		friend class WeakReference<CtrlrPanelProcessor>;
		ReadWriteLock processorLock;
		CtrlrPanel &owner;
		MidiBuffer junkBuffer;
		WeakReference <CtrlrLuaMethod> luaAudioProcessBlockCbk;
};

#endif
