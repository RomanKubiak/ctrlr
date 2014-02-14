#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  7 Mar 2011 10:02:48pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "CtrlrImage.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "CtrlrProcessor.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrPanel/CtrlrPanelResource.h"
//[/MiscUserDefs]

//==============================================================================
CtrlrImage::CtrlrImage (CtrlrModulator &owner)
    : CtrlrComponent(owner)
{

    //[UserPreSize]
	owner.setProperty (Ids::modulatorIsStatic, true);
	owner.setProperty (Ids::modulatorVstExported, false);

	setProperty (Ids::uiImageResource, "");
	componentTree.addListener (this);
    //[/UserPreSize]

    setSize (128, 128);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrImage::~CtrlrImage()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrImage::paint (Graphics& g)
{
	if (!currentImage.isValid())
	{
		g.setColour (Colours::red);
		g.setFont (Font (15.0000f, Font::bold));
		g.drawFittedText ("Invalid Resource", 0, 0, getWidth(), getHeight(), Justification::left, 2);
	}
	else
	{
		const Rectangle<int> r = getUsableRect();
		g.drawImage(currentImage, r.getX(), r.getY(), r.getWidth(), r.getHeight(), 0, 0, currentImage.getWidth(), currentImage.getHeight(), false);
	}

	CtrlrComponent::resized();
	CtrlrComponent::paint (g);
}

void CtrlrImage::resized()
{
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
const double CtrlrImage::getComponentMaxValue()
{
	return (1);
}

const double CtrlrImage::getComponentValue()
{
	return (1);
}

const int CtrlrImage::getComponentMidiValue()
{
	return (1);
}

void CtrlrImage::setComponentValue (const double newValue, const bool sendChangeMessage)
{
}

void CtrlrImage::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiImageResource)
	{
		_DBG("CtrlrImage::valueTreePropertyChanged res="+getProperty(property).toString());
		setResource();
	}

	CtrlrComponent::valueTreePropertyChanged(treeWhosePropertyHasChanged, property);
	if (restoreStateInProgress == false)
	{
		resized();
	}
}

void CtrlrImage::resetSize()
{
	setSize (currentImage.getWidth(), currentImage.getHeight());
}

void CtrlrImage::restoreState (const ValueTree &savedState)
{
	CtrlrComponent::restoreState(savedState);
}

void CtrlrImage::setResource()
{
	_DBG("CtrlrImage::setResource");
	currentImage = owner.getOwner().getResourceManager().getResourceAsImage (getProperty(Ids::uiImageResource));
	repaint();
	resized();
}

void CtrlrImage::reloadResources(Array <CtrlrPanelResource*> resourcesThatChanged)
{
	for (int i=0; i<resourcesThatChanged.size(); i++)
	{
		if (resourcesThatChanged[i]->getName() == getProperty(Ids::uiImageResource).toString())
		{
			setResource();
		}
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrImage" componentName=""
                 parentClasses="public CtrlrComponent" constructorParams="CtrlrModulator &amp;owner"
                 variableInitialisers="CtrlrComponent(owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="128"
                 initialHeight="128">
  <BACKGROUND backgroundColour="ffffff"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
