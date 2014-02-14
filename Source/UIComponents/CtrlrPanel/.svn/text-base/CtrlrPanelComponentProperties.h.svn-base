/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_E144F840B8BF67B2__
#define __JUCE_HEADER_E144F840B8BF67B2__

//[Headers]     -- You can add your own extra header files here --
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrIDs.h"
#include "CtrlrComponents/CtrlrComponentTypeManager.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrPanelComponentProperties  : public Component,
                                       public ChangeListener,
                                       public ValueTree::Listener,
                                       public CtrlrManager::Listener,
                                       public LookAndFeel_V3
{
public:
    //==============================================================================
    CtrlrPanelComponentProperties (CtrlrPanelEditor &_owner);
    ~CtrlrPanelComponentProperties();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	enum ToolbarItems
	{
		_none,
		refresh
	};
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
	void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
	void setTree (const ValueTree &_treeToEdit, const bool force=false);
	void changeListenerCallback (ChangeBroadcaster* source);
	PropertyComponent *getPropertyEditor (const Value &valueToEdit, const Identifier &valueIdentifier);
	void refreshDynamicData();
	void refreshAll();
	void copyProperties(ValueTree &sourceTree, ValueTree &destinationTree);
	void managerStateChanged (const CtrlrManager::CtrlrManagerState newState);
	void refreshTargetModulationPropertyList(const ValueTree &sourceModulationTree);

	void buttonClicked (Button *button);
	void getAllToolbarItemIds (Array< int > &ids);
	void getDefaultItemSet (Array< int > &ids);
	ToolbarItemComponent *createItem (int itemId);
	void visibilityChanged();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	bool mark;
	CtrlrPanelEditor &owner;
	ValueTree treeToEdit;
	Array <Font> fonts;
	StringArray possibleMidiReferences;
	StringArray resourceList;
	StringPairArray midiTemplates;
	StringArray midiTemplateNames;
	StringArray midiTemplateValues;
	StringArray midiInputDevices;
	StringArray midiOutputDevices;
	StringArray modulatorList;
	StringArray modulatorPropertyList;
	StringArray panelPropertyList;
	StringArray componentGroupList;
	StringArray luaMethodList;
	ValueTree msTree;
	XmlElement panelPropertyOpennessState;
	XmlElement modulatorPropertyOpennessState;
	StringArray emptyValueSet;
	int selectedItems;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<PropertyPanel> propertyPanel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrPanelComponentProperties)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_E144F840B8BF67B2__
