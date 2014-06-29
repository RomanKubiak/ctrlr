#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrEditor.h"
#include "CtrlrMacros.h"
#include "CtrlrProcessor.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrDocumentPanel.h"
#include "CtrlrInlineUtilitiesGUI.h"

CtrlrDocumentPanel::CtrlrDocumentPanel (CtrlrManager &_owner)
    : ctrlrEditor(0), owner(_owner)
{
	useFullscreenWhenOneDocument (true);
    setSize (600, 400);
}

CtrlrDocumentPanel::~CtrlrDocumentPanel()
{
}

void CtrlrDocumentPanel::paint (Graphics& g)
{
	MultiDocumentPanel::paint(g);
	drawDefaultWindowBackground(g,getWidth(),getHeight());
}

void CtrlrDocumentPanel::resized()
{
	MultiDocumentPanel::resized();
}

bool CtrlrDocumentPanel::tryToCloseDocument (Component* component)
{
	return (true);
}

void CtrlrDocumentPanel::activeDocumentChanged()
{
	CtrlrEditor *ed = dynamic_cast <CtrlrEditor*> (getParentComponent());
	if (ed)
		ed->activeCtrlrChanged();
}

void CtrlrDocumentPanel::setEditor (CtrlrEditor *_editorToSet)
{
	ctrlrEditor = _editorToSet;
}
