#ifndef __CTRLR_PROCESSOR_EDITOR_FOR_LIVE__
#define __CTRLR_PROCESSOR_EDITOR_FOR_LIVE__

#include "CtrlrApplicationWindow/CtrlrEditor.h"

class CtrlrManager;
class CtrlrProcessorEditorForLive;

class CtrlrEditorWrapper : public DocumentWindow
{
	public:
		CtrlrEditorWrapper(CtrlrProcessorEditorForLive &_liveEditorOwner, CtrlrProcessor *_filterOwner, CtrlrManager &_owner);
		~CtrlrEditorWrapper();
		void resized();

	private:
		CtrlrEditor *editor;
		CtrlrProcessorEditorForLive &liveEditorOwner;
};

class CtrlrProcessorEditorForLive : public AudioProcessorEditor, public Timer
{
	public:
		CtrlrProcessorEditorForLive(CtrlrProcessor *_filterOwner, CtrlrManager &_owner);
		~CtrlrProcessorEditorForLive();
		void paint(Graphics &g);
		void timerCallback();
		void wrapperResized();
		
	private:
		CtrlrProcessor *filterOwner;
		CtrlrManager &owner;
		CtrlrEditorWrapper wrapper;
		Point<int> lastScreenPosition;
};

#endif