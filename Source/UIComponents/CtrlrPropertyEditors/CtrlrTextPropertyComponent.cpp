#include "stdafx.h"
#include "CtrlrTextPropertyComponent.h"

class CtrlrTextPropLabel  : public Label
{
	public:
		CtrlrTextPropLabel (CtrlrTextPropertyComponent& owner_, const int maxChars_, const bool isMultiline_)
			: Label (String::empty, String::empty),
				owner (owner_), maxChars (maxChars_), isMultiline (isMultiline_)
		{
	        setEditable (true, true, false);
			setColour (backgroundColourId, Colours::white);
			setColour (outlineColourId, findColour (ComboBox::outlineColourId));
		}

		TextEditor* createEditorComponent()
		{
			TextEditor* const textEditor = Label::createEditorComponent();
			textEditor->setInputRestrictions (maxChars);

			if (isMultiline)
			{
				textEditor->setMultiLine (true, true);
				textEditor->setReturnKeyStartsNewLine (true);
	        }

		    return textEditor;
		}

		void textWasEdited()
		{
	        owner.textWasEdited();
	    }

	private:
	    CtrlrTextPropertyComponent& owner;
	    int maxChars;
	    bool isMultiline;
};

//==============================================================================
CtrlrTextPropertyComponent::CtrlrTextPropertyComponent (const Value& _valueToControl,
														const int maxNumChars,
														const bool isMultiLine, const bool isReadOnly) : valueToControl(_valueToControl)
{
    createEditor (maxNumChars, isMultiLine);
    textEditor->getTextValue().referTo (valueToControl);

	if (isReadOnly)
	{
		textEditor->setColour (Label::backgroundColourId, textEditor->findColour(Label::backgroundColourId,false).withAlpha(0.5f));
		textEditor->setColour (Label::textColourId, textEditor->findColour(Label::textColourId,false).brighter(0.5f));
		textEditor->setEditable (false, false, false);
	}
}

CtrlrTextPropertyComponent::~CtrlrTextPropertyComponent()
{
}

void CtrlrTextPropertyComponent::setText (const String& newText)
{
    textEditor->setText (newText, sendNotification);
}

String CtrlrTextPropertyComponent::getText() const
{
    return textEditor->getText();
}

void CtrlrTextPropertyComponent::createEditor (const int maxNumChars, const bool isMultiLine)
{
    addAndMakeVisible (textEditor = new CtrlrTextPropLabel (*this, maxNumChars, isMultiLine));

    if (isMultiLine)
    {
        textEditor->setJustificationType (Justification::topLeft);
    }
}

void CtrlrTextPropertyComponent::resized()
{
	if (textEditor)
		textEditor->setBounds (0,0,getWidth(),getHeight());
}

void CtrlrTextPropertyComponent::textWasEdited()
{
    const String newText (textEditor->getText());

    if (getText() != newText)
        setText (newText);
}

void CtrlrTextPropertyComponent::refresh()
{
	if (textEditor)
		textEditor->setText (valueToControl.toString(), dontSendNotification);
}
