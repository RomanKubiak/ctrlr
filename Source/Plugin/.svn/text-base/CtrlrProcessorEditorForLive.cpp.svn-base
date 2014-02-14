#include "stdafx.h"
#ifdef _WIN32
#include <Windows.h>
#endif

#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrProcessorEditorForLive.h"

CtrlrEditorWrapper::CtrlrEditorWrapper(CtrlrProcessorEditorForLive &_liveEditorOwner, CtrlrProcessor *ownerFilter, CtrlrManager &ctrlrManager) 
	: DocumentWindow("Ctrlr", Colours::lightgrey, 0, true), liveEditorOwner(_liveEditorOwner)
{
	setTitleBarHeight(1);

	editor = new CtrlrEditor(ownerFilter, ctrlrManager);
	setContentOwned (editor, true);
	setAlwaysOnTop(true);
	centreWithSize (getWidth(),getHeight());
}

CtrlrEditorWrapper::~CtrlrEditorWrapper()
{
}

void CtrlrEditorWrapper::resized()
{
	DocumentWindow::resized();
	liveEditorOwner.wrapperResized();
}

CtrlrProcessorEditorForLive::CtrlrProcessorEditorForLive(CtrlrProcessor *_filterOwner, CtrlrManager &_owner)
	: owner(_owner), filterOwner(_filterOwner), AudioProcessorEditor((AudioProcessor *)_filterOwner),
		wrapper(*this, filterOwner, owner)
{
	wrapper.setVisible (true);
	setSize (wrapper.getWidth(), 16);
	startTimer (50);
}

CtrlrProcessorEditorForLive::~CtrlrProcessorEditorForLive()
{
}

void CtrlrProcessorEditorForLive::paint(Graphics &g)
{
	ColourGradient cg(Colours::grey, 0.0f, 0.0f, Colours::darkgrey,0.0f, getHeight(),  false);
	g.setFillType (cg);
	g.fillAll();
}

void CtrlrProcessorEditorForLive::timerCallback()
{
	if (getPeer())
	{
#ifdef _WIN32
		HWND hwndMsg = (HWND)getPeer()->getNativeHandle();

		if (hwndMsg)
		{
			wrapper.setVisible (IsWindowVisible(hwndMsg) ? true : false);
		}
#endif
	}

	if (getScreenPosition() != lastScreenPosition)
	{
		wrapper.setTopLeftPosition(getScreenPosition().getX(), getScreenPosition().getY()+24);
	}
}

void CtrlrProcessorEditorForLive::wrapperResized()
{
	setSize(wrapper.getWidth(), 16);
}