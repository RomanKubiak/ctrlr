#pragma once

#include "CtrlrPanelFindProperty.h"
class CtrlrPanelEditor;
class CtrlrLookAndFeel;

class CtrlrPanelProperties  : public Component,
                              public ChangeListener,
                              public ChangeBroadcaster
{
public:
    CtrlrPanelProperties (CtrlrPanelEditor &_owner);
    ~CtrlrPanelProperties();
	void changeListenerCallback (ChangeBroadcaster* source);
	void refreshAll();
	void layoutChanged();
    void paint (Graphics& g);
    void resized();
    JUCE_LEAK_DETECTOR(CtrlrPanelProperties)

private:
	CtrlrPanelEditor &owner;
    TabbedComponent* tabbedComponent;
    CtrlrPanelProperties (const CtrlrPanelProperties&);
	std::unique_ptr<CtrlrPanelFindProperty> ctrlrPanelFindProperty;
	const CtrlrPanelProperties& operator= (const CtrlrPanelProperties&);
};
