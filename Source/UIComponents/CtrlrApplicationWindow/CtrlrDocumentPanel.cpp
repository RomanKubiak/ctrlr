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

    if (getCurrentTabbedComponent())
    {
        TabbedButtonBar &bar = getCurrentTabbedComponent()->getTabbedButtonBar();

        for (int i=0; i<bar.getNumTabs(); i++)
        {
            TabBarButton *button = bar.getTabButton (i);

            if (button)
            {
                ImageButton *imageButton = new ImageButton ("Close"+_STR(i));
                imageButton->addListener (this);
                imageButton->setSize (16,16);
                imageButton->getProperties().set ("index", button->getIndex());
                imageButton->setMouseCursor (MouseCursor::PointingHandCursor);
                imageButton->setImages (false, true, true,
                            IMAGE (ico_delete_png), 1.000f, Colour (0x00858585),
                            IMAGE (ico_delete_png), 1.000f, Colour (0x38bababa),
                            IMAGE (ico_delete_png), 1.000f, Colour (0xb8777777));

                button->setExtraComponent (imageButton, TabBarButton::beforeText);
            }
        }
    }
}

void CtrlrDocumentPanel::setEditor (CtrlrEditor *_editorToSet)
{
	ctrlrEditor = _editorToSet;
}

void CtrlrDocumentPanel::buttonClicked (Button *button)
{
    int documentIndex       = (int)button->getProperties().getWithDefault("index", -1);
    CtrlrPanelEditor *ed    = dynamic_cast<CtrlrPanelEditor*> (getDocument(documentIndex));

    if (documentIndex >= 0 && ed != nullptr)
    {
        if (AlertWindow::showYesNoCancelBox (AlertWindow::QuestionIcon, "Close panel", "Are you sure you want to close this panel [" + ed->getName() + "]", "Yes", "No", "Cancel", this) == 1)
        {
            owner.removePanel(ed);
        }
    }
}
