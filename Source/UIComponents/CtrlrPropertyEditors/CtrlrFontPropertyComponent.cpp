#include "stdafx.h"
#include "CtrlrUtilities.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrFontPropertyComponent.h"
#include "CtrlrProcessor.h"

CtrlrFontPropertyComponent::CtrlrFontPropertyComponent (const Value &_valueToControl, CtrlrPanel *_owner)
    : valueToControl(_valueToControl), owner(_owner),
      typeface (0),
      fontBold (0),
      fontItalic (0),
      fontUnderline (0),
      fontSize (0),
	  kerning(0),
	  horizontalScale(0)
{
    addAndMakeVisible (typeface = new ComboBox (String::empty));
    typeface->setEditableText (false);
    typeface->setJustificationType (Justification::centredLeft);
    typeface->setTextWhenNothingSelected (L"<Sans-Serif>");
    typeface->setTextWhenNoChoicesAvailable (L"<Sans-Serif>");
    typeface->addListener (this);

    addAndMakeVisible (fontBold = new ImageButton (String::empty));
    fontBold->setTooltip (L"Bold");
    fontBold->setButtonText (L"new button");
    fontBold->addListener (this);

    fontBold->setImages (false, true, true,
                         IMAGE (ico_font_bold_png), 0.5000f, Colour (0x0),
                         IMAGE (ico_font_bold_png), 0.7500f, Colour (0xa0ffffff),
                         IMAGE (ico_font_bold_png), 1.0000f, Colour (0x0));
    addAndMakeVisible (fontItalic = new ImageButton (String::empty));
    fontItalic->setTooltip (L"Italic");
    fontItalic->setButtonText (L"new button");
    fontItalic->addListener (this);

    fontItalic->setImages (false, true, true,
                           IMAGE (ico_font_italic_png), 0.5000f, Colour (0x0),
                           IMAGE (ico_font_italic_png), 0.7500f, Colour (0xa0ffffff),
                           IMAGE (ico_font_italic_png), 1.0000f, Colour (0x0));
    addAndMakeVisible (fontUnderline = new ImageButton (String::empty));
    fontUnderline->setTooltip (L"Underline");
    fontUnderline->setButtonText (L"new button");
    fontUnderline->addListener (this);

    fontUnderline->setImages (false, true, true,
                              IMAGE (ico_font_underline_png), 0.5000f, Colour (0x0),
                              IMAGE (ico_font_underline_png), 0.7500f, Colour (0xa0ffffff),
                              IMAGE (ico_font_underline_png), 1.0000f, Colour (0x0));

    addAndMakeVisible (fontSize = new Slider (String::empty));
	fontSize->setLookAndFeel (this);
    fontSize->setTooltip (L"Size");
    fontSize->setRange (1, 999, 1);
    fontSize->setSliderStyle (Slider::RotaryVerticalDrag);
    fontSize->setTextBoxStyle (Slider::TextBoxRight, false, 34, 16);
    fontSize->addListener (this);

	addAndMakeVisible (horizontalScale = new Slider (String::empty));
	horizontalScale->setLookAndFeel (this);
    horizontalScale->setTooltip (L"Horizontal Scale");
    horizontalScale->setRange (0.0, 10.0, 0.01);
    horizontalScale->setSliderStyle (Slider::RotaryVerticalDrag);
    horizontalScale->setTextBoxStyle (Slider::TextBoxRight, false, 34, 16);
    horizontalScale->addListener (this);

	addAndMakeVisible (kerning = new Slider (String::empty));
    kerning->setLookAndFeel (this);
	kerning->setTooltip (L"Extra Kerning");
    kerning->setRange (0.0, 10.0, 0.01);
    kerning->setSliderStyle (Slider::RotaryVerticalDrag);
    kerning->setTextBoxStyle (Slider::TextBoxRight, false, 34, 16);
    kerning->addListener (this);

	fontBold->setClickingTogglesState (true);
	fontBold->setMouseCursor (MouseCursor::PointingHandCursor);
	fontItalic->setClickingTogglesState (true);
	fontItalic->setMouseCursor (MouseCursor::PointingHandCursor);
	fontUnderline->setClickingTogglesState (true);
	fontUnderline->setMouseCursor (MouseCursor::PointingHandCursor);

    owner->getOwner().getFontManager().fillCombo (*typeface, true, true, true, true);

    setSize (300, 32);
}

CtrlrFontPropertyComponent::~CtrlrFontPropertyComponent()
{
    deleteAndZero (typeface);
    deleteAndZero (fontBold);
    deleteAndZero (fontItalic);
    deleteAndZero (fontUnderline);
    deleteAndZero (fontSize);
	deleteAndZero (kerning);
	deleteAndZero (horizontalScale);
}

void CtrlrFontPropertyComponent::resized()
{
    typeface->setBounds (0, 0, getWidth() * 0.4f, getHeight());

	fontBold->setBounds (getWidth() * 0.4f,									0, getWidth() * 0.05f,	getHeight());
    fontItalic->setBounds ((getWidth() * 0.4f) + (getWidth() * 0.05f),		0, getWidth() * 0.05f,	getHeight());
	fontUnderline->setBounds ((getWidth() * 0.4f) + 2*(getWidth() * 0.05f), 0, getWidth() * 0.05f,	getHeight());

    fontSize->setBounds			((getWidth() * 0.4f) + 3*(getWidth() * 0.05f),							0, getWidth() * 0.14f,	getHeight());
	horizontalScale->setBounds	((getWidth() * 0.4f) + 3*(getWidth() * 0.05f) + (getWidth() * 0.14f),	0, getWidth() * 0.14f,	getHeight());
	kerning->setBounds			((getWidth() * 0.4f) + 3*(getWidth() * 0.05f) + 2*(getWidth() * 0.14f),	0, getWidth() * 0.14f,	getHeight());
}

void CtrlrFontPropertyComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
	valueToControl = owner->getOwner().getFontManager().getStringFromFont(getFont());
}

void CtrlrFontPropertyComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == fontBold || buttonThatWasClicked == fontItalic || buttonThatWasClicked == fontUnderline)
    {
		valueToControl = owner->getOwner().getFontManager().getStringFromFont(getFont());
    }
}

void CtrlrFontPropertyComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
	valueToControl = owner->getOwner().getFontManager().getStringFromFont(getFont());
}

void CtrlrFontPropertyComponent::refresh()
{
	font = owner->getOwner().getFontManager().getFontFromString(valueToControl.toString());
	typeface->setText (font.getTypefaceName(), sendNotification);
	fontSize->setValue (font.getHeight(), dontSendNotification);
	fontBold->setToggleState (font.isBold(), sendNotification);
	fontItalic->setToggleState (font.isItalic(), sendNotification);
	fontUnderline->setToggleState (font.isUnderlined(), sendNotification);
	kerning->setValue (font.getExtraKerningFactor(), dontSendNotification);
	horizontalScale->setValue (font.getHorizontalScale(), dontSendNotification);
}

Font CtrlrFontPropertyComponent::getFont()
{
	Font font;

	if (typeface)
		font.setTypefaceName (typeface->getText());
	else
		return (font);

	font.setHeight (fontSize->getValue());
	font.setBold (fontBold->getToggleState());
	font.setItalic (fontItalic->getToggleState());
	font.setUnderline (fontUnderline->getToggleState());
	font.setExtraKerningFactor (kerning->getValue());
	font.setHorizontalScale (horizontalScale->getValue());
	return (font);
}

Label* CtrlrFontPropertyComponent::createSliderTextBox (Slider& slider)
{
    Label* const l = new CtrlrFontPropertyComponent::SliderLabelComp();

	l->setFont (Font(10.0f,Font::bold));
    l->setJustificationType (Justification::centred);

    l->setColour (Label::textColourId, slider.findColour (Slider::textBoxTextColourId));

    l->setColour (Label::backgroundColourId,
                  (slider.getSliderStyle() == Slider::LinearBar || slider.getSliderStyle() == Slider::LinearBarVertical)
                            ? Colours::transparentBlack
                            : slider.findColour (Slider::textBoxBackgroundColourId));
    l->setColour (Label::outlineColourId, slider.findColour (Slider::textBoxOutlineColourId));

    l->setColour (TextEditor::textColourId, slider.findColour (Slider::textBoxTextColourId));

    l->setColour (TextEditor::backgroundColourId,
                  slider.findColour (Slider::textBoxBackgroundColourId)
                        .withAlpha ((slider.getSliderStyle() == Slider::LinearBar || slider.getSliderStyle() == Slider::LinearBarVertical)
                                        ? 0.7f : 1.0f));

    l->setColour (TextEditor::outlineColourId, slider.findColour (Slider::textBoxOutlineColourId));

    return l;
}
