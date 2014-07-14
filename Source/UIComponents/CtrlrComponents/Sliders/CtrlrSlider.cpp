#include "stdafx.h"
#include "CtrlrSlider.h"
#include "CtrlrProcessor.h"
#include "../CtrlrComponentTypeManager.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrModulator/CtrlrModulator.h"

CtrlrSlider::CtrlrSlider (CtrlrModulator &owner)
    :	CtrlrComponent(owner),
		lf(*this, componentTree),
		ctrlrSlider (*this)
{
	setColour (TooltipWindow::textColourId, Colours::red);
	addAndMakeVisible (&ctrlrSlider);

	ctrlrSlider.setBufferedToImage (true);
    ctrlrSlider.setRange (1, 127, 1);
    ctrlrSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    ctrlrSlider.setTextBoxStyle (Slider::TextBoxBelow, false, 64, 12);
    ctrlrSlider.addListener (this);
	ctrlrSlider.setLookAndFeel (&lf);

	componentTree.addListener (this);

	setProperty (Ids::uiSliderStyle, "RotaryVerticalDrag");
	setProperty (Ids::uiSliderMin, 0);
	setProperty (Ids::uiSliderMax, 127);
	setProperty (Ids::uiSliderInterval, 1);
	setProperty (Ids::uiSliderDoubleClickEnabled, true);
	setProperty (Ids::uiSliderDoubleClickValue, 0);
	setProperty (Ids::uiSliderValuePosition, (int)Slider::TextBoxBelow);
	setProperty (Ids::uiSliderValueHeight, 12);
	setProperty (Ids::uiSliderValueWidth, 64);
	setProperty (Ids::uiSliderTrackCornerSize, 5);
	setProperty (Ids::uiSliderThumbCornerSize, 3);
	setProperty (Ids::uiSliderThumbWidth, 0);
	setProperty (Ids::uiSliderThumbHeight, 0);
	setProperty (Ids::uiSliderThumbFlatOnLeft, false);
	setProperty (Ids::uiSliderThumbFlatOnRight, false);
	setProperty (Ids::uiSliderThumbFlatOnTop, false);
	setProperty (Ids::uiSliderThumbFlatOnBottom, false);
	setProperty (Ids::uiSliderValueTextColour, "0xff000000");
	setProperty (Ids::uiSliderValueBgColour, "0xffffffff");
	setProperty (Ids::uiSliderRotaryOutlineColour, "0xff0000ff");
	setProperty (Ids::uiSliderRotaryFillColour, "0xff0000ff");
	setProperty (Ids::uiSliderThumbColour, "0xffff0000");
	setProperty (Ids::uiSliderValueHighlightColour, "0xff0000ff");
	setProperty (Ids::uiSliderValueOutlineColour, "0xffffffff");
	setProperty (Ids::uiSliderTrackColour, "0xff0f0f0f");
	setProperty (Ids::uiSliderIncDecButtonColour, "0xff0000ff");
	setProperty (Ids::uiSliderIncDecTextColour, "0xffffffff");
	setProperty (Ids::uiSliderValueFont, FONT2STR (Font(12)));
	setProperty (Ids::uiSliderValueTextJustification, "centred");
	setProperty (Ids::uiSliderVelocitySensitivity, 1.0);
	setProperty (Ids::uiSliderVelocityThreshold, 1);
	setProperty (Ids::uiSliderVelocityOffset, 0.0);
	setProperty (Ids::uiSliderVelocityMode, false);
	setProperty (Ids::uiSliderVelocityModeKeyTrigger, true);
	setProperty (Ids::uiSliderSpringMode, false);
	setProperty (Ids::uiSliderSpringValue, 0);
	setProperty (Ids::uiSliderMouseWheelInterval, 1);
	setProperty (Ids::uiSliderPopupBubble, false);


    setSize (64, 64);
}

CtrlrSlider::~CtrlrSlider()
{
	componentTree.removeListener (this);
}

void CtrlrSlider::resized()
{
	if (restoreStateInProgress)
		return;
	ctrlrSlider.setBounds (getUsableRect());
}

void CtrlrSlider::sliderValueChanged (Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == &ctrlrSlider)
    {
		if ((bool)owner.getOwner().getEditor()->getProperty(Ids::uiPanelEditMode) == true)
			return;

		setComponentValue (ctrlrSlider.getValue(), true);
    }
}

void CtrlrSlider::mouseUp (const MouseEvent& e)
{
	if ((bool)getProperty(Ids::uiSliderSpringMode) == true)
	{
		ctrlrSlider.setValue ((double)getProperty(Ids::uiSliderSpringValue), sendNotificationSync);
	}
}

void CtrlrSlider::mouseDoubleClick (const MouseEvent& e)
{
	if (e.mods.isCommandDown())
		bubble.show();
}

const double CtrlrSlider::getComponentValue()
{
	return (ctrlrSlider.getValue());
}

const int CtrlrSlider::getComponentMidiValue()
{
	return ((int)ctrlrSlider.getValue());
}

const double CtrlrSlider::getComponentMaxValue()
{
	return (ctrlrSlider.getMaximum());
}

void CtrlrSlider::setComponentValue (const double newValue, const bool sendChangeMessage)
{
	ctrlrSlider.setValue (newValue, dontSendNotification);
	if (sendChangeMessage)
	{
		owner.getProcessor().setValueFromGUI (newValue);
	}
}

const Array<Font> CtrlrSlider::getFontList()
{
	Array <Font> ret;
	Font f = STR2FONT(getProperty(Ids::uiSliderValueFont));
	if (f.getTypefaceName() != Font::getDefaultSerifFontName()
		&& f.getTypefaceName() != Font::getDefaultSansSerifFontName()
		&& f.getTypefaceName() != Font::getDefaultMonospacedFontName()
		&& f.getTypefaceName() != "<Sans-Serif>")
	{
		ret.add (f);
	}
	return (ret);
}

void CtrlrSlider::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiSliderStyle)
	{
		ctrlrSlider.setSliderStyle ((Slider::SliderStyle)CtrlrComponentTypeManager::sliderStringToStyle (getProperty (Ids::uiSliderStyle)));
	}
	else if (property == Ids::uiSliderRotaryFillColour)
	{
		ctrlrSlider.setColour (Slider::rotarySliderFillColourId, VAR2COLOUR(getProperty (Ids::uiSliderRotaryFillColour)) );
	}
	else if (property == Ids::uiSliderRotaryOutlineColour)
	{
		ctrlrSlider.setColour (Slider::rotarySliderOutlineColourId, VAR2COLOUR(getProperty (Ids::uiSliderRotaryOutlineColour)) );
	}
	else if (property == Ids::uiSliderValueTextColour)
	{
		ctrlrSlider.setColour (Slider::textBoxTextColourId, VAR2COLOUR(getProperty (Ids::uiSliderValueTextColour)) );
	}

	else if (property == Ids::uiSliderValueBgColour)
	{
		ctrlrSlider.setColour (Slider::textBoxBackgroundColourId, VAR2COLOUR(getProperty (Ids::uiSliderValueBgColour)) );
	}
	else if (property == Ids::uiSliderThumbColour)
	{
		ctrlrSlider.setColour (Slider::thumbColourId, VAR2COLOUR(getProperty (Ids::uiSliderThumbColour)) );
	}
	else if (property == Ids::uiSliderValueHighlightColour)
	{
		ctrlrSlider.setColour (Slider::textBoxHighlightColourId, VAR2COLOUR(getProperty (Ids::uiSliderValueOutlineColour)) );
	}
	else if (property == Ids::uiSliderValueOutlineColour)
	{
		ctrlrSlider.setColour (Slider::textBoxOutlineColourId, VAR2COLOUR(getProperty (Ids::uiSliderValueOutlineColour)) );
	}
	else if (property == Ids::uiSliderTrackColour)
	{
		ctrlrSlider.setColour (Slider::trackColourId, VAR2COLOUR(getProperty (Ids::uiSliderTrackColour)) );
	}
	else if (property == Ids::uiSliderInterval || property == Ids::uiSliderMax || property == Ids::uiSliderMin)
	{
		ctrlrSlider.setRange ( (double) getProperty (Ids::uiSliderMin), (double) getProperty (Ids::uiSliderMax), (double) getProperty (Ids::uiSliderInterval) );
		owner.setProperty (Ids::modulatorMax, ctrlrSlider.getMaximum());
		owner.setProperty (Ids::modulatorMin, ctrlrSlider.getMinimum());
	}
	else if (property == Ids::uiSliderValuePosition || property == Ids::uiSliderValueHeight || property == Ids::uiSliderValueWidth)
	{
		ctrlrSlider.setTextBoxStyle (
			(Slider::TextEntryBoxPosition)(int)getProperty (Ids::uiSliderValuePosition),
			false,
			getProperty (Ids::uiSliderValueWidth, 64),
			getProperty (Ids::uiSliderValueHeight, 12));
	}
	else if (property == Ids::uiSliderIncDecButtonColour
			|| property == Ids::uiSliderIncDecTextColour
			|| property == Ids::uiSliderValueFont
			|| property == Ids::uiSliderValueTextJustification)
	{
		ctrlrSlider.setLookAndFeel (nullptr);
		ctrlrSlider.setLookAndFeel (&lf);
	}
	else if (property == Ids::uiSliderVelocityMode
		|| property == Ids::uiSliderVelocityModeKeyTrigger
		|| property == Ids::uiSliderVelocitySensitivity
		|| property == Ids::uiSliderVelocityThreshold
		|| property == Ids::uiSliderVelocityOffset
		)
	{
		ctrlrSlider.setVelocityBasedMode((bool)getProperty(Ids::uiSliderVelocityMode));
		ctrlrSlider.setVelocityModeParameters ((double)getProperty(Ids::uiSliderVelocitySensitivity),
												(int)getProperty(Ids::uiSliderVelocityThreshold),
												(double)getProperty(Ids::uiSliderVelocityOffset),
												(bool)getProperty(Ids::uiSliderVelocityModeKeyTrigger));
	}
	else if (property == Ids::uiSliderSpringValue)
	{
		ctrlrSlider.setValue (getProperty(property), dontSendNotification);
	}

	else if (property == Ids::uiSliderDoubleClickValue
			|| property == Ids::uiSliderDoubleClickEnabled)
	{
		ctrlrSlider.setDoubleClickReturnValue ((bool)getProperty(Ids::uiSliderDoubleClickEnabled), getProperty(Ids::uiSliderDoubleClickValue));
	}
	else if (property == Ids::uiSliderSpringMode)
	{
		if ((bool)getProperty(property) == true)
		{
			ctrlrSlider.setValue (getProperty(Ids::uiSliderSpringValue), dontSendNotification);
		}
	}
	else if (property == Ids::uiSliderPopupBubble)
	{
		ctrlrSlider.setPopupDisplayEnabled ((bool)getProperty(property), owner.getOwner().getEditor());
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

const String CtrlrSlider::getComponentText()
{
	return (String(getComponentValue()));
}

void CtrlrSlider::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrSlider, bases<CtrlrComponent,CtrlrLuaObject> >("CtrlrSlider")
			.def("getOwnedSlider", &CtrlrSlider::getOwnedSlider)
	];
}
