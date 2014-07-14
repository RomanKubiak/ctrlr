#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  8 Jun 2011 12:42:46am

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
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrLog.h"
#include "CtrlrPanel/CtrlrPanelResource.h"
//[/Headers]

#include "CtrlrImageSlider.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrImageSlider::CtrlrImageSlider (CtrlrModulator &owner)
    : CtrlrComponent(owner), lf(*this),
      ctrlrSlider (0)
{
    addAndMakeVisible (ctrlrSlider = new CtrlrSliderInternal (*this));
    ctrlrSlider->setRange (0, 10, 0);
    ctrlrSlider->setSliderStyle (Slider::LinearHorizontal);
    ctrlrSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    ctrlrSlider->addListener (this);


    //[UserPreSize]
	ctrlrSlider->setBufferedToImage (true);
	setBufferedToImage (true);
	ctrlrSlider->setSliderStyle (Slider::RotaryVerticalDrag);
	ctrlrSlider->setLookAndFeel (&lf);
	setProperty (Ids::uiSliderStyle, "RotaryVerticalDrag");
	setProperty (Ids::uiImageSliderResource, "");
	setProperty (Ids::resourceImageWidth, 32);
	setProperty (Ids::resourceImageHeight, 32);
	setProperty (Ids::resourceImagePaintMode, 36);
	setProperty (Ids::resourceImageOrientation, 1);
	setProperty (Ids::uiSliderMin, 0);
	setProperty (Ids::uiSliderMax, 127);
	setProperty (Ids::uiSliderInterval, 1);
	setProperty (Ids::uiSliderDoubleClickEnabled, true);
	setProperty (Ids::uiSliderDoubleClickValue, 0);
	setProperty (Ids::uiSliderValuePosition, (int)Slider::TextBoxBelow);
	setProperty (Ids::uiSliderValueHeight, 12);
	setProperty (Ids::uiSliderValueWidth, 64);
	setProperty (Ids::uiSliderValueTextColour, "0xff000000");
	setProperty (Ids::uiSliderValueBgColour, "0xffffffff");
	setProperty (Ids::uiSliderValueFont, FONT2STR (Font(12)));
	setProperty (Ids::uiSliderValueTextJustification, "centred");
	setProperty (Ids::uiSliderValueHighlightColour, "0xff0000ff");
	setProperty (Ids::uiSliderValueOutlineColour, "0xffffffff");
	setProperty (Ids::uiSliderVelocitySensitivity, 1.0);
	setProperty (Ids::uiSliderVelocityThreshold, 1);
	setProperty (Ids::uiSliderVelocityOffset, 0.0);
	setProperty (Ids::uiSliderVelocityMode, false);
	setProperty (Ids::uiSliderVelocityModeKeyTrigger, true);
	setProperty (Ids::uiSliderSpringMode, false);
	setProperty (Ids::uiSliderSpringValue, 0);
	setProperty (Ids::uiSliderMouseWheelInterval, 1);
	setProperty (Ids::uiSliderPopupBubble, false);
    //[/UserPreSize]

    setSize (64, 64);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrImageSlider::~CtrlrImageSlider()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (ctrlrSlider);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrImageSlider::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrImageSlider::resized()
{
    //ctrlrSlider->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
	if (restoreStateInProgress)
		return;
	ctrlrSlider->setBounds (getUsableRect());
    //[/UserResized]
}

void CtrlrImageSlider::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == ctrlrSlider)
    {
        //[UserSliderCode_ctrlrSlider] -- add your slider handling code here..
		setComponentValue ((int)ctrlrSlider->getValue(), true);
        //[/UserSliderCode_ctrlrSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void CtrlrImageSlider::mouseUp (const MouseEvent& e)
{
    //[UserCode_mouseUp] -- Add your code here...
	if ((bool)getProperty(Ids::uiSliderSpringMode) == true)
	{
		ctrlrSlider->setValue ((double)getProperty(Ids::uiSliderSpringValue), sendNotificationSync);
	}
    //[/UserCode_mouseUp]
}

void CtrlrImageSlider::mouseDoubleClick (const MouseEvent& e)
{
    //[UserCode_mouseDoubleClick] -- Add your code here...
	if (e.mods.isCommandDown())
		bubble.show();
    //[/UserCode_mouseDoubleClick]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
const double CtrlrImageSlider::getComponentMaxValue()
{
	return ((int)ctrlrSlider->getMaximum());
}

const double CtrlrImageSlider::getComponentValue()
{
	return ((int)ctrlrSlider->getValue());
}

const int CtrlrImageSlider::getComponentMidiValue()
{
	return ((int)ctrlrSlider->getValue());
}

void CtrlrImageSlider::setComponentValue (const double newValue, const bool sendChangeMessage)
{
	ctrlrSlider->setValue (newValue, dontSendNotification);
	if (sendChangeMessage)
	{
		owner.getProcessor().setValueFromGUI (newValue);
	}
}

void CtrlrImageSlider::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiImageSliderResource)
	{
		setResource();
	}
	else if (property == Ids::resourceImageWidth)
	{
		lf.setImage (filmStripImage, (int)getProperty(Ids::resourceImageWidth), (int)getProperty(Ids::resourceImageHeight));
	}
	else if (property == Ids::resourceImageHeight)
	{
		lf.setImage (filmStripImage, (int)getProperty(Ids::resourceImageWidth), (int)getProperty(Ids::resourceImageHeight));
	}
	else if (property == Ids::resourceImagePaintMode)
	{
		lf.setPaintMode ((RectanglePlacement)(int)getProperty(Ids::resourceImagePaintMode));
	}
	else if (property == Ids::resourceImageOrientation)
	{
		lf.setOrientation((bool)getProperty(Ids::resourceImageOrientation));
	}
	else if (property == Ids::uiSliderInterval || property == Ids::uiSliderMax || property == Ids::uiSliderMin)
	{
		ctrlrSlider->setRange ( getProperty (Ids::uiSliderMin), getProperty (Ids::uiSliderMax), getProperty (Ids::uiSliderInterval) );
		owner.setProperty (Ids::modulatorMax, ctrlrSlider->getMaximum());
		owner.setProperty (Ids::modulatorMin, ctrlrSlider->getMinimum());
	}
	else if (property == Ids::uiSliderValueTextColour)
	{
		ctrlrSlider->setColour (Slider::textBoxTextColourId, VAR2COLOUR(getProperty (Ids::uiSliderValueTextColour)) );
	}
	else if (property == Ids::uiSliderValueBgColour)
	{
		ctrlrSlider->setColour (Slider::textBoxBackgroundColourId, VAR2COLOUR(getProperty (Ids::uiSliderValueBgColour)) );
	}
	else if (property == Ids::uiSliderValueHighlightColour)
	{
		ctrlrSlider->setColour (Slider::textBoxHighlightColourId, VAR2COLOUR(getProperty (Ids::uiSliderValueOutlineColour)) );
	}
	else if (property == Ids::uiSliderValueOutlineColour)
	{
		ctrlrSlider->setColour (Slider::textBoxOutlineColourId, VAR2COLOUR(getProperty (Ids::uiSliderValueOutlineColour)) );
	}
	else if (property == Ids::uiSliderValuePosition || property == Ids::uiSliderValueHeight || property == Ids::uiSliderValueWidth)
	{
		ctrlrSlider->setTextBoxStyle (
			(Slider::TextEntryBoxPosition)(int)getProperty (Ids::uiSliderValuePosition),
			false,
			getProperty (Ids::uiSliderValueWidth, 64),
			getProperty (Ids::uiSliderValueHeight, 12));
	}

	else if (property == Ids::uiSliderIncDecButtonColour
		|| property == Ids::uiSliderIncDecTextColour
		|| property == Ids::uiSliderValueFont
		|| property == Ids::uiSliderValueTextJustification
		)
	{
		lf.setOrientation((bool)getProperty(Ids::resourceImageOrientation));
		lf.setImage (filmStripImage, (int)getProperty(Ids::resourceImageWidth), (int)getProperty(Ids::resourceImageHeight));
		lookAndFeelChanged();
	}

	else if (property == Ids::uiSliderStyle)
	{
		ctrlrSlider->setSliderStyle ((Slider::SliderStyle)CtrlrComponentTypeManager::sliderStringToStyle (getProperty (Ids::uiSliderStyle)));
	}
	else if (property == Ids::uiSliderVelocityMode
		|| property == Ids::uiSliderVelocityModeKeyTrigger
		|| property == Ids::uiSliderVelocitySensitivity
		|| property == Ids::uiSliderVelocityThreshold
		|| property == Ids::uiSliderVelocityOffset
		)
	{
		ctrlrSlider->setVelocityBasedMode((bool)getProperty(Ids::uiSliderVelocityMode));
		ctrlrSlider->setVelocityModeParameters ((double)getProperty(Ids::uiSliderVelocitySensitivity),
												(int)getProperty(Ids::uiSliderVelocityThreshold),
												(double)getProperty(Ids::uiSliderVelocityOffset),
												(bool)getProperty(Ids::uiSliderVelocityModeKeyTrigger));
	}
	else if (property == Ids::uiSliderSpringValue)
	{
		ctrlrSlider->setValue (getProperty(property), dontSendNotification);
	}
	else if (property == Ids::uiSliderDoubleClickValue
			|| property == Ids::uiSliderDoubleClickEnabled)
	{
		ctrlrSlider->setDoubleClickReturnValue ((bool)getProperty(Ids::uiSliderDoubleClickEnabled), getProperty(Ids::uiSliderDoubleClickValue));
	}
	else if (property == Ids::uiSliderSpringMode)
	{
		if ((bool)getProperty(property) == true)
		{
			ctrlrSlider->setValue (getProperty(Ids::uiSliderSpringValue), dontSendNotification);
		}
	}
	else if (property == Ids::uiSliderPopupBubble)
	{
		ctrlrSlider->setPopupDisplayEnabled ((bool)getProperty(property), owner.getOwner().getEditor());
	}
	else
	{
		CtrlrComponent::valueTreePropertyChanged(treeWhosePropertyHasChanged, property);
	}

	if (restoreStateInProgress == false)
	{
		resized();
	}
}

const String CtrlrImageSlider::getComponentText()
{
	return (String(getComponentValue()));
}

void CtrlrImageSlider::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrImageSlider, bases<CtrlrComponent,CtrlrLuaObject> >("CtrlrSlider")
			.def("getOwnedSlider", &CtrlrImageSlider::getOwnedSlider)
	];
}

void CtrlrImageSlider::setResource()
{
	filmStripImage = owner.getOwner().getResourceManager().getResourceAsImage (getProperty(Ids::uiImageSliderResource));
	lf.setImage (filmStripImage, (int)getProperty(Ids::resourceImageWidth), (int)getProperty(Ids::resourceImageHeight));
	lookAndFeelChanged();
	repaint();
	resized();
}

void CtrlrImageSlider::reloadResources(Array <CtrlrPanelResource*> resourcesThatChanged)
{
	for (int i=0; i<resourcesThatChanged.size(); i++)
	{
		if (resourcesThatChanged[i]->getName() == getProperty(Ids::uiImageSliderResource).toString())
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

<JUCER_COMPONENT documentType="Component" className="CtrlrImageSlider" componentName=""
                 parentClasses="public CtrlrComponent, public SettableTooltipClient"
                 constructorParams="CtrlrModulator &amp;owner" variableInitialisers="CtrlrComponent(owner), lf(*this)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="64" initialHeight="64">
  <METHODS>
    <METHOD name="mouseUp (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDoubleClick (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="0"/>
  <SLIDER name="ctrlrSlider" id="9d33c05c00f3fd09" memberName="ctrlrSlider"
          virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" min="0"
          max="10" int="0" style="LinearHorizontal" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
