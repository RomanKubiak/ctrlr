#ifndef __JUCER_HEADER_CTRLRPANELLAYERLISTITEM_CTRLRPANELLAYERLISTITEM_618D5794__
#define __JUCER_HEADER_CTRLRPANELLAYERLISTITEM_CTRLRPANELLAYERLISTITEM_618D5794__

#include "CtrlrMacros.h"
class CtrlrPanelCanvas;
class CtrlrPanelLayerList;
class CtrlrPanelCanvasLayer;
class CtrlrColourEditorComponent;

class CtrlrPanelLayerListItem  : public Component,
                                 public ChangeListener,
								 public Label::Listener,
								 public Button::Listener
{
public:
    //==============================================================================
    CtrlrPanelLayerListItem (CtrlrPanelLayerList &_owner);
    ~CtrlrPanelLayerListItem();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setLayer(CtrlrPanelCanvasLayer *_layer);
	void changeListenerCallback (ChangeBroadcaster* source);
	CtrlrPanelCanvasLayer *getLayer() { return (layer); }
	void setRow(const int _rowIndex);
	const int getRow() { return (rowIndex); }
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void labelTextChanged (Label* labelThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);
    void mouseDown (const MouseEvent& e);



    //==============================================================================
    JUCE_LEAK_DETECTOR(CtrlrPanelLayerListItem)

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	CtrlrPanelCanvasLayer *layer;
	CtrlrPanelLayerList &owner;
	int rowIndex;
    //[/UserVariables]

    //==============================================================================
    Label* layerName;
    ImageButton* layerVisibility;
    CtrlrColourEditorComponent* layerColour;
    Label* layerIndex;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrPanelLayerListItem (const CtrlrPanelLayerListItem&);
    const CtrlrPanelLayerListItem& operator= (const CtrlrPanelLayerListItem&);
};


#endif   // __JUCER_HEADER_CTRLRPANELLAYERLISTITEM_CTRLRPANELLAYERLISTITEM_618D5794__
