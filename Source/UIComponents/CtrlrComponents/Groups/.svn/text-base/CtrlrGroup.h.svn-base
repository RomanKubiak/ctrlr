/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  2 Jun 2011 1:01:21am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRGROUP_CTRLRGROUP_F9C865FE__
#define __JUCER_HEADER_CTRLRGROUP_CTRLRGROUP_F9C865FE__

//[Headers]     -- You can add your own extra header files here --
#include "../CtrlrComponent.h"

class CtrlrGroup;

class CtrlrGroupContentComponent : public Component
{
	public:
		CtrlrGroupContentComponent(CtrlrGroup &_owner);
		~CtrlrGroupContentComponent();

	private:
		CtrlrGroup &owner;
};
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrGroup  : public CtrlrComponent, public DragAndDropTarget, public CtrlrGrouppingComponent
{
public:
    //==============================================================================
    CtrlrGroup (CtrlrModulator &owner);
    ~CtrlrGroup();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	enum GradientType
	{
		None,
		Vertical,
		Horizontal,
		Radial
	};

	const Array<Font> getFontList();
	static const GradientType gradientFromString(const String &str);
	static const Justification justificationFromString(const String &str);
	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	const double getComponentValue();
	const int getComponentMidiValue();
	const double getComponentMaxValue();
	const String getComponentText();
	void setComponentText (const String &componentText);
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
	void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
	void setOwned (CtrlrComponent *componentToOwn, const int subIndexInGroup = 0, const bool shouldOwnThisComponent = true);
	void canvasStateRestored();
	const Array<int> getResourceList();
	void modulatorNameChanged (const String &newName);
	bool isInterestedInDragSource (const SourceDetails &dragSourceDetails);
	void itemDropped (const SourceDetails &dragSourceDetails);
	void itemDragExit (const SourceDetails &dragSourceDetails);
	void itemDragEnter (const SourceDetails &dragSourceDetails);
	bool isOwned(CtrlrComponent *componentToCheck);
	Array <CtrlrComponent*> getOwnedChildren();
	void reloadResources(Array <CtrlrPanelResource*> resourcesThatChanged);
	void setResource();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	Array <int> values;
	GradientType outlineGradient, backgroundGradient;
	Colour outlineColour1, outlineColour2, backgroundColour1, backgroundColour2;
	float outlineThickness;
	float outlineAngle;
	int textMargin;
	Image groupBackgroundImage;
	CtrlrGroupContentComponent content;
    //[/UserVariables]

    //==============================================================================
    Label* label;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrGroup (const CtrlrGroup&);
    const CtrlrGroup& operator= (const CtrlrGroup&);
};


#endif   // __JUCER_HEADER_CTRLRGROUP_CTRLRGROUP_F9C865FE__
