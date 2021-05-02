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
	/* Full screen mode is not completely implemented in JUCE 6
	   we get some assertions when adding the first Tab to an invisble
	   panel, as it wants to grep the focus, which is not possible at this stage.
	*/
	useFullscreenWhenOneDocument (true);
    setSize (600, 400);
}

CtrlrDocumentPanel::~CtrlrDocumentPanel()
{
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
    if (getCurrentTabbedComponent()) {
        getCurrentTabbedComponent()->setTabBarDepth(owner.getProperty(Ids::ctrlrTabBarDepth));
    }
}

void CtrlrDocumentPanel::setEditor (CtrlrEditor *_editorToSet)
{
	ctrlrEditor = _editorToSet;
}
