#include "stdafx.h"
#include "CtrlrWindowManagers/CtrlrManagerWindowManager.h"
#include "CtrlrExpressionProperty.h"

CtrlrExpressionProperty::CtrlrExpressionProperty (const Value &_valeToControl) : valeToControl(_valeToControl), externalEditorWindow(nullptr)
{
    addAndMakeVisible (text = new TextEditor (String::empty));
    text->setMultiLine (true, true);
    text->setReturnKeyStartsNewLine (false);
    text->setReadOnly (false);
    text->setScrollbarsShown (true);
    text->setCaretVisible (true);
    text->setPopupMenuEnabled (true);
    text->setText (String::empty);
	text->setColour (TextEditor::outlineColourId, findColour (ComboBox::outlineColourId));

    addAndMakeVisible (apply = new ImageButton ("Compile"));
    apply->addListener (this);
	apply->setTooltip ("Compile expression, if it's valid set the property");
	apply->setMouseCursor (MouseCursor::PointingHandCursor);
	apply->setImages (false, true, true,
						IMAGE(ico_bug_png), 0.6500f, Colour (0x0),
						IMAGE(ico_bug_png), 0.8000f, Colour (0x0),
						IMAGE(ico_bug_png), 1.0000f, Colour (0x0));

	text->setFont (Font (Font::getDefaultMonospacedFontName(), 10.0f, Font::plain));
	text->setText (valeToControl.toString(), false);
	text->addListener (this);

    setSize (256, 48);
}

CtrlrExpressionProperty::~CtrlrExpressionProperty()
{
    deleteAndZero (text);
    deleteAndZero (apply);
}

void CtrlrExpressionProperty::resized()
{
	text->setBounds (0, 0, getWidth() - 24, getHeight() - 0);
    apply->setBounds (getWidth() - 24, 0, 24, getHeight()/2);
}

void CtrlrExpressionProperty::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == apply)
    {
		if (compile(true))
		{
			AlertWindow::showMessageBox (AlertWindow::InfoIcon, "Expression validation", "Expression is valid");
		}
    }
}

void CtrlrExpressionProperty::refresh()
{
	text->setText (valeToControl.toString(), false);
}

void CtrlrExpressionProperty::textEditorTextChanged (TextEditor &editor)
{
}

void CtrlrExpressionProperty::textEditorReturnKeyPressed (TextEditor &editor)
{
	compile (true);
}

void CtrlrExpressionProperty::textEditorFocusLost (TextEditor &editor)
{	
	compile (true);
}

const bool CtrlrExpressionProperty::compile(const bool setPropertyIfValid)
{
	try
	{
		Expression e = Expression(text->getText());
	}
	catch (Expression::ParseError err)
	{
		text->setColour (TextEditor::backgroundColourId, Colours::lightpink);
		AlertWindow::showMessageBox (AlertWindow::WarningIcon, "Expression validation", "Validation failed: "+err.description, "OK", this);
		return (false);
	}
	
	text->setColour (TextEditor::backgroundColourId, Colours::white);

	if (setPropertyIfValid)
	{
		valeToControl = text->getText();
	}

	return (true);
}
