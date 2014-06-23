#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  25 Jul 2011 7:59:52pm

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

#include "CtrlrLabel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "CtrlrProcessor.h"
#include "../CtrlrComponentTypeManager.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrLuaManager.h"

CtrlrLabelInternal::CtrlrLabelInternal(CtrlrLabel &_owner, const String &componentName, const String &labelText)
	: Label (componentName, labelText), owner(_owner)
{
}

TextEditor *CtrlrLabelInternal::createEditorComponent()
{
	TextEditor* const ed = new TextEditor (getName());
	ed->setFont (getFont());
	ed->setInputRestrictions (owner.getProperty(::Ids::uiLabelInputMaxLength), owner.getProperty(::Ids::uiLabelInputAllowedChars));

	const int cols[] = { TextEditor::backgroundColourId,
                       TextEditor::textColourId,
                       TextEditor::highlightColourId,
                       TextEditor::highlightedTextColourId,
                       TextEditor::outlineColourId,
                       TextEditor::focusedOutlineColourId,
                       TextEditor::shadowColourId,
                       CaretComponent::caretColourId };

	for (int i = 0; i < numElementsInArray (cols); ++i)
		ed->setColour (cols[i], findColour (cols[i]));

	return ed;
}

bool CtrlrLabelInternal::keyPressed (const KeyPress &key)
{
	_DBG("CtrlrLabelInternal::keyPressed");
	return (false);
}
//[/MiscUserDefs]

//==============================================================================
CtrlrLabel::CtrlrLabel (CtrlrModulator &owner)
    : CtrlrComponent(owner),
      ctrlrLabel (0)
{
    addAndMakeVisible (ctrlrLabel = new CtrlrLabelInternal (*this, "ctrlrLabel",
                                               "label text"));
    ctrlrLabel->setFont (Font (15.0000f, Font::plain));
    ctrlrLabel->setJustificationType (Justification::centredLeft);
    ctrlrLabel->setEditable (false, false, false);
    ctrlrLabel->setColour (TextEditor::textColourId, Colours::black);
    ctrlrLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));


    //[UserPreSize]
	owner.setProperty (Ids::modulatorIsStatic, true);
	owner.setProperty (Ids::modulatorVstExported, false);

	setProperty (Ids::uiLabelBgColour, "0x00000000");
	setProperty (Ids::uiLabelTextColour, "0xff000000");
	setProperty (Ids::uiLabelOutline, 0);
	setProperty (Ids::uiLabelOutlineColour, "0x00000000");
	setProperty (Ids::uiLabelJustification, "centred");
	setProperty (Ids::uiLabelFitFont, false);
	setProperty (Ids::uiLabelFont, FONT2STR (Font(14)));
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

	ctrlrLabel->addListener (this);
	componentTree.addListener (this);
    //[/UserPreSize]

    setSize (88, 24);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrLabel::~CtrlrLabel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	owner.getOwner().removePanelListener(this);
    //[/Destructor_pre]

    deleteAndZero (ctrlrLabel);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrLabel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
	int i = getProperty(Ids::uiLabelOutline);
	g.setColour (VAR2COLOUR(getProperty(Ids::uiLabelBgColour)));
	g.fillRect( i, i, (getWidth() - 2*i), (getHeight() - 2*i));
    g.setColour (VAR2COLOUR(getProperty(Ids::uiLabelOutlineColour)));
	g.drawRect (0, 0, getWidth(), getHeight(),  i);
    //[/UserPaint]
}

void CtrlrLabel::resized()
{
    ctrlrLabel->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
	if ((bool)ctrlrLabel->getProperties() ["fh"] == true)
	{
		Font f = ctrlrLabel->getFont();
		f.setHeight (getHeight()*0.95f);
		ctrlrLabel->setFont (f);
	}
	ctrlrLabel->setBounds (getUsableRect());
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
const double CtrlrLabel::getComponentMaxValue()
{
	return (1);
}

void CtrlrLabel::setComponentValue (const double newValue, const bool sendChangeMessage)
{
	if (sendChangeMessage)
	{
		owner.getProcessor().setValueFromGUI (newValue, true);
	}
}

const double CtrlrLabel::getComponentValue()
{
	return (1);
}

const int CtrlrLabel::getComponentMidiValue()
{
	return (1);
}

const Array<Font> CtrlrLabel::getFontList()
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

void CtrlrLabel::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
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
		ctrlrLabel->setColour (Label::backgroundColourId, VAR2COLOUR(getProperty(Ids::uiLabelBgColour)));
	}
	else if (property == Ids::uiLabelTextColour)
	{
		ctrlrLabel->setColour (Label::textColourId, VAR2COLOUR(getProperty(Ids::uiLabelTextColour)));
		ctrlrLabel->setColour (TextEditor::textColourId, VAR2COLOUR(getProperty(Ids::uiLabelTextColour)));
	}
	else if (property == Ids::uiLabelOutline)
	{
		ctrlrLabel->setBorderSize (BorderSize <int> (getProperty (property)));
		repaint();
	}
	else if (property == Ids::uiLabelOutlineColour)
	{
		ctrlrLabel->setColour (Label::outlineColourId, VAR2COLOUR(getProperty(Ids::uiLabelOutlineColour)));
		repaint();
	}
	else if (property == Ids::uiLabelFitFont || property == Ids::uiLabelFont)
	{
		ctrlrLabel->getProperties().set ("fh", getProperty(Ids::uiLabelFitFont));
		const String t = ctrlrLabel->getText();
		ctrlrLabel->setFont (STR2FONT(getProperty(Ids::uiLabelFont)));
		ctrlrLabel->setText (t, dontSendNotification);
	}
	else if (property == Ids::uiLabelJustification)
	{
		ctrlrLabel->setJustificationType (justificationFromProperty (getProperty(property)));
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

void CtrlrLabel::setComponentText(const String &componentText)
{
	setProperty (Ids::uiLabelText, componentText);
}

const String CtrlrLabel::getComponentText()
{
	return (ctrlrLabel->getText());
}

void CtrlrLabel::modulatorChanged (CtrlrModulator *modulatorThatChanged)
{
	if (modulatorThatChanged == 0 || modulatorThatChanged->getComponent() == 0)
		return;

	if ((bool)modulatorThatChanged->getComponent()->getProperty(Ids::componentExcludedFromLabelDisplay) == true)
		return;

	ctrlrLabel->setText (labelFromProperty (modulatorThatChanged, getProperty (Ids::uiLabelDisplayFormat)), dontSendNotification);
}

void CtrlrLabel::labelTextChanged (Label* labelThatHasChanged)
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

void CtrlrLabel::lookAndFeelChanged ()
{
}

CtrlrLabel &CtrlrLabel::setLabelText(const String &text)
{
	setProperty (Ids::uiLabelText, text);

	return (*this);
}

CtrlrLabel &CtrlrLabel::appendText(const String &text)
{
	setProperty (Ids::uiLabelText, ctrlrLabel->getText() + text);

	return (*this);
}

const String CtrlrLabel::getText()
{
	return (ctrlrLabel->getText());
}

void CtrlrLabel::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrLabel,bases<CtrlrComponent,CtrlrLuaObject> >("CtrlrLabel")
			.def("setText", &CtrlrLabel::setLabelText)
			.def("appendText", &CtrlrLabel::appendText)
			.def("append", &CtrlrLabel::appendText)
			.def("getText", &CtrlrLabel::getText)
	];
}

bool CtrlrLabel::keyPressed (const KeyPress &key)
{
	_DBG("CtrlrLabel::keyPressed");
	return (false);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrLabel" componentName=""
                 parentClasses="public CtrlrComponent, public CtrlrPanel::PanelListener, public Label::Listener"
                 constructorParams="CtrlrModulator &amp;owner" variableInitialisers="CtrlrComponent(owner)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="88" initialHeight="24">
  <BACKGROUND backgroundColour="0"/>
  <LABEL name="ctrlrLabel" id="409d64ae540e634d" memberName="ctrlrLabel"
         virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" edTextCol="ff000000"
         edBkgCol="0" labelText="label text" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
