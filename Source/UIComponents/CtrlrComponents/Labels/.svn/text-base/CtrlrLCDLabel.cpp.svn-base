#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  20 May 2011 11:32:48pm

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

#include "CtrlrLCDLabel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "../CtrlrComponentTypeManager.h"
#include "CtrlrUtilities.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrLuaManager.h"
//[/MiscUserDefs]

//==============================================================================
CtrlrLCDLabel::CtrlrLCDLabel (CtrlrModulator &owner)
    : CtrlrComponent(owner),
      ctrlrLabel (0)
{
    addAndMakeVisible (ctrlrLabel = new Label ("ctrlrLabel",
                                               "LCD TEST"));
    ctrlrLabel->setFont (Font (16.0000f, Font::plain));
    ctrlrLabel->setJustificationType (Justification::centred);
    ctrlrLabel->setEditable (false, false, false);
    ctrlrLabel->setColour (Label::backgroundColourId, Colour (0x0));
    ctrlrLabel->setColour (Label::textColourId, Colours::black);
    ctrlrLabel->setColour (TextEditor::textColourId, Colours::black);
    ctrlrLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));


    //[UserPreSize]
	owner.setProperty (Ids::modulatorIsStatic, true);
	owner.setProperty (Ids::modulatorVstExported, false);

	setProperty (Ids::uiLabelBgColour, "0xff000000");
	setProperty (Ids::uiLabelTextColour, "0xff56c312");
	setProperty (Ids::uiLabelOutline, 0);
	setProperty (Ids::uiLabelOutlineColour, "0x00000000");
	setProperty (Ids::uiLabelJustification, "centred");
	setProperty (Ids::uiLabelFitFont, false);
	setProperty (Ids::uiLCDLabelFont, 5);
	setProperty (Ids::uiLCDLabelFontHeight, 18);
	setProperty (Ids::uiLabelText, "Label text");
	setProperty (Ids::uiLabelDisplaysAllValues, false);
	setProperty (Ids::uiLabelDisplayFormat, "%n(%N) = %v(%h)");
	setProperty (Ids::uiLabelInputHighlightTextColour, "0xffffffff");
	setProperty (Ids::uiLabelInputHighlightColour, "0xff0000ff");
	setProperty (Ids::uiLabelEditOnSingleClick, false);
	setProperty (Ids::uiLabelEditOnDoubleClick, false);
	setProperty (Ids::uiLabelEditFocusDiscardsChanges, true);
	setProperty (Ids::uiLabelInputAllowedChars, "");
	setProperty (Ids::uiLabelInputAllowedChars, "");
	setProperty (Ids::uiLabelInputMaxLength, 1024);
	setProperty (Ids::uiLabelChangedCbk, COMBO_NONE_ITEM);
	componentTree.addListener (this);
    //[/UserPreSize]

    setSize (96, 32);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrLCDLabel::~CtrlrLCDLabel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (ctrlrLabel);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrLCDLabel::paint (Graphics& g)
{
	//[UserPrePaint] Add your own custom painting code here..
	//[/UserPrePaint]



	//[UserPaint] Add your own custom painting code here..
	int i = getProperty(Ids::uiLabelOutline);
	g.setColour (VAR2COLOUR (getProperty(Ids::uiLabelBgColour)));
	g.fillRoundedRectangle (i, i, getWidth() - 2*i, getHeight() - 2*i, 7);
//	g.fillRect( i, i, (getWidth() - 2*i), (getHeight() - 2*i));
//	g.fillRoundedRectangle (2.0f, 2.0f, (float) (getWidth() - 4), (float) (getHeight() - 4), 7.0000f);

	g.setColour (VAR2COLOUR (getProperty(Ids::uiLabelOutlineColour)));
	g.drawRoundedRectangle (0, 0, getWidth(), getHeight(), 7, i);
//	g.drawRect (0, 0, getWidth(), getHeight(), i);
//	g.setColour (STR2COLOUR (getProperty(Ids::uiLabelBgColour)).darker(0.2f));
//	g.drawRoundedRectangle (2.0f, 2.0f, (float) (getWidth() - 4), (float) (getHeight() - 4), 7.0000f, 2.0000f);
	//[/UserPaint]
}

void CtrlrLCDLabel::resized()
{
    ctrlrLabel->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
const double CtrlrLCDLabel::getComponentMaxValue()
{
	return (1);
}

void CtrlrLCDLabel::setComponentValue (const double newValue, const bool sendChangeMessage)
{
}

const double CtrlrLCDLabel::getComponentValue()
{
	return (1);
}

const int CtrlrLCDLabel::getComponentMidiValue()
{
	return (1);
}

const Array<Font> CtrlrLCDLabel::getFontList()
{
	Array <Font> ret;
	Font f = STR2FONT(getProperty(Ids::uiLabelFont));
	if (f.getTypefaceName() != Font::getDefaultSerifFontName()
		&& f.getTypefaceName() != Font::getDefaultSansSerifFontName()
		&& f.getTypefaceName() != Font::getDefaultMonospacedFontName()
		&& f.getTypefaceName() != "<Sans-Serif>")
	{
		ret.add (f);
	}
	return (ret);
}

void CtrlrLCDLabel::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiLabelDisplaysAllValues)
	{
		if ((bool)getProperty(property) == true)
		{
			owner.getOwner().addPanelListener(this);
		}
		else
		{
			owner.getOwner().removePanelListener(this);
		}
	}
	else if (property == Ids::uiLabelText)
	{
		ctrlrLabel->setText (getProperty(Ids::uiLabelText), dontSendNotification);
	}
	else if (property == Ids::uiLabelBgColour)
	{
		repaint();
	}
	else if (property == Ids::uiLabelTextColour)
	{
		ctrlrLabel->setColour (Label::textColourId, VAR2COLOUR(getProperty(Ids::uiLabelTextColour)));
		ctrlrLabel->setColour (TextEditor::textColourId, VAR2COLOUR(getProperty(Ids::uiLabelTextColour)));
	}
	else if (property == Ids::uiLabelFitFont || property == Ids::uiLabelFont)
	{
		ctrlrLabel->getProperties().set ("fh", getProperty(Ids::uiLabelFitFont));
		const String t = ctrlrLabel->getText();
		ctrlrLabel->setText (t, dontSendNotification);
	}
	else if (property == Ids::uiLabelJustification)
	{
		ctrlrLabel->setJustificationType (justificationFromProperty(getProperty(property)));
	}

	else if (property == Ids::uiLCDLabelFontHeight)
	{
		Font f = ctrlrLabel->getFont();
		f.setHeight ((float)getProperty(property));
		ctrlrLabel->setFont(f);
	}

	else if (property == Ids::uiLCDLabelFont)
	{
		Font f;

		if ((int)getProperty(property) == 0)
		{
			f = INTERNAL_FONT (FONT_LCD_bin);
		}
		if ((int)getProperty(property) == 1)
		{
			f = INTERNAL_FONT (FONT_Digital7_bin);
		}
		if ((int)getProperty(property) == 2)
		{
			f = INTERNAL_FONT (FONT_DottyShadow_bin);
		}
		if ((int)getProperty(property) == 3)
		{
			f = INTERNAL_FONT (FONT_ZX81_bin);
		}
		if ((int)getProperty(property) == 4)
		{
			f = INTERNAL_FONT (FONT_Invasion2000_bin);
		}
		if ((int)getProperty(property) == 5)
		{
			f = INTERNAL_FONT (FONT_Digit_bin);
		}
		if ((int)getProperty(property) == 6)
		{
			f = INTERNAL_FONT (FONT_Computerfont_bin);
		}
		if ((int)getProperty(property) == 7)
		{
			f = INTERNAL_FONT (FONT_Electronic_Highway_Sign_bin);
		}
		if ((int)getProperty(property) == 8)
		{
			f = INTERNAL_FONT (FONT_Karmatic_Arcade_bin);
		}
		if ((int)getProperty(property) == 9)
		{
			f = INTERNAL_FONT (FONT_60sekuntia_bin);
		}

		f.setHeight ((float)getProperty(Ids::uiLCDLabelFontHeight));
		ctrlrLabel->setFont (f);
	}
	else if (property == Ids::uiLabelEditOnSingleClick
		|| property == Ids::uiLabelEditOnDoubleClick
		|| property == Ids::uiLabelEditFocusDiscardsChanges)
	{
		ctrlrLabel->setEditable ((bool)getProperty(Ids::uiLabelEditOnSingleClick),(bool)getProperty(Ids::uiLabelEditOnDoubleClick),(bool)getProperty(Ids::uiLabelEditFocusDiscardsChanges));
	}
	else if (property == Ids::uiLabelChangedCbk)
	{
		if (getProperty(property) == String::empty)
			return;

		labelChangedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiLabelInputHighlightTextColour || property == Ids::uiLabelInputHighlightColour)
	{
		ctrlrLabel->setColour (TextEditor::highlightColourId, VAR2COLOUR(getProperty(Ids::uiLabelInputHighlightColour)));
		ctrlrLabel->setColour (TextEditor::highlightedTextColourId, VAR2COLOUR(getProperty(Ids::uiLabelInputHighlightTextColour)));
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

void CtrlrLCDLabel::setComponentText(const String &newText)
{
	setProperty (Ids::uiLabelText, newText);
}

const String CtrlrLCDLabel::getComponentText()
{
	return (ctrlrLabel->getText());
}

void CtrlrLCDLabel::modulatorChanged (CtrlrModulator *modulatorThatChanged)
{
	if (modulatorThatChanged == 0 || modulatorThatChanged->getComponent() == 0)
		return;

	if ((bool)modulatorThatChanged->getComponent()->getProperty(Ids::componentExcludedFromLabelDisplay) == true)
		return;

	ctrlrLabel->setText (labelFromProperty (modulatorThatChanged, getProperty (Ids::uiLabelDisplayFormat)), dontSendNotification);
}

void CtrlrLCDLabel::labelTextChanged (Label* labelThatHasChanged)
{
	setProperty (Ids::uiLabelText, labelThatHasChanged->getText(), false);
	setComponentValue(0, true);

	if (labelChangedCbk && !labelChangedCbk.wasObjectDeleted())
	{
		if (labelChangedCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (labelChangedCbk, dynamic_cast<CtrlrComponent*>(this), labelThatHasChanged->getText());
		}
	}
}

CtrlrLCDLabel &CtrlrLCDLabel::setLabelText(const String &text)
{
	setProperty (Ids::uiLabelText, text);

	return (*this);
}

CtrlrLCDLabel &CtrlrLCDLabel::appendText(const String &text)
{
	setProperty (Ids::uiLabelText, ctrlrLabel->getText() + text);

	return (*this);
}

const String CtrlrLCDLabel::getText()
{
	return (ctrlrLabel->getText());
}

void CtrlrLCDLabel::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrLCDLabel,bases<CtrlrComponent,CtrlrLuaObject> >("CtrlrLCDLabel")
			.def("setText", &CtrlrLCDLabel::setLabelText)
			.def("appendText", &CtrlrLCDLabel::appendText)
			.def("append", &CtrlrLCDLabel::appendText)
			.def("getText", &CtrlrLCDLabel::getText)
	];
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrLCDLabel" componentName=""
                 parentClasses="public CtrlrComponent, public CtrlrPanel::PanelListener"
                 constructorParams="CtrlrModulator &amp;owner" variableInitialisers="CtrlrComponent(owner)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="96" initialHeight="32">
  <BACKGROUND backgroundColour="ffffff">
    <ROUNDRECT pos="2 2 4M 4M" cornerSize="7" fill="solid: ff00c109" hasStroke="1"
               stroke="2, mitered, butt" strokeColour="solid: ff008c0f"/>
  </BACKGROUND>
  <LABEL name="ctrlrLabel" id="409d64ae540e634d" memberName="ctrlrLabel"
         virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" bkgCol="0"
         textCol="ff000000" edTextCol="ff000000" edBkgCol="0" labelText="LCD TEST"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="16" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
