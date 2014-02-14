/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  11 Oct 2011 9:41:30pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRPANELLAYERLISTITEM_CTRLRPANELLAYERLISTITEM_618D5794__
#define __JUCER_HEADER_CTRLRPANELLAYERLISTITEM_CTRLRPANELLAYERLISTITEM_618D5794__

//[Headers]     -- You can add your own extra header files here --
#include "CtrlrPropertyEditors/CtrlrColourPropertyComponent.h"

class CtrlrPanelCanvas;
class CtrlrPanelLayerList;

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrPanelLayerListItem  : public Component,
                                 public ChangeListener,
                                 public LabelListener,
                                 public ButtonListener
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
