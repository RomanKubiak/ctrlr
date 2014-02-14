#ifndef __CTRLR_PANEL_PROCESSOR__
#define __CTRLR_PANEL_PROCESSOR__

#include "CtrlrMacros.h"
class CtrlrPanel;

class CtrlrPanelProcessor : public AsyncUpdater, public CtrlrPanelMidiProcessor
{
	public:
		CtrlrPanelProcessor(CtrlrPanel &_owner);
		virtual ~CtrlrPanelProcessor();
		void handleAsyncUpdate();
		void processBlock(MidiBuffer &midiMessages, MidiBuffer &leftoverBuffer);
		void midiOptionChanged(const CtrlrPanelMidiOption optionThatChanged);
		void midiChannelChaned(const CtrlrPanelMidiChannel channelThatChanged){}
		CtrlrPanel &getOwner();

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrPanelProcessor)

	private:
		WeakReference<CtrlrPanelProcessor>::Master masterReference;
		friend class WeakReference<CtrlrPanelProcessor>;
		ReadWriteLock processorLock;
		CtrlrPanel &owner;
		MidiBuffer junkBuffer;
};

#endif