#include "stdafx.h"
#include "CtrlrDialogWindow.h"
#include "CtrlrInlineUtilitiesGUI.h"

class CtrlrTempDialogWindow : public DialogWindow
{
public:
    CtrlrTempDialogWindow (const String& title,
                      Component* contentComponent_,
                      Component* componentToCentreAround,
                      const Colour& colour,
                      const bool escapeKeyTriggersCloseButton_,
                      const bool shouldBeResizable,
                      const bool useBottomRightCornerResizer)
        : DialogWindow (title, colour, escapeKeyTriggersCloseButton_, true)
    {
        if (! JUCEApplication::isStandaloneApp())
            setAlwaysOnTop (true); // for a plugin, make it always-on-top because the host windows are often top-level

		setUsingNativeTitleBar (true);
        setContentNonOwned (contentComponent_, true);
        centreAroundComponent (componentToCentreAround, getWidth(), getHeight());
        setResizable (shouldBeResizable, useBottomRightCornerResizer);
    }

    void closeButtonPressed()
    {
        setVisible (false);
    }

	void paint(Graphics &g)
	{
		drawDefaultWindowBackground(g,getWidth(),getHeight());
	}

private:
    JUCE_DECLARE_NON_COPYABLE (CtrlrTempDialogWindow);
};

const int CtrlrDialogWindow::showModalDialog(const String &title, Component *content, const bool resizable, Component *parent)
{
	CtrlrTempDialogWindow dw (title, content, parent, Colours::lightgrey, true, resizable, false);
	return dw.runModalLoop();
}