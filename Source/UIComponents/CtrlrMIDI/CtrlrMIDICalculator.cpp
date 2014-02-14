#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrMIDICalculator.h"

CtrlrMIDICalculator::CtrlrMIDICalculator (CtrlrManager &_owner)
    : owner(_owner)
{
    addAndMakeVisible (hexDisplay = new TextEditor (String::empty));
    hexDisplay->setMultiLine (false);
    hexDisplay->setReturnKeyStartsNewLine (false);
    hexDisplay->setReadOnly (false);
    hexDisplay->setScrollbarsShown (true);
    hexDisplay->setCaretVisible (true);
    hexDisplay->setPopupMenuEnabled (true);
    hexDisplay->setText ("F0 00 01 40 A3 F7");

    addAndMakeVisible (label = new Label ("new label",
                                          "Hexadecimal"));
    label->setFont (Font (24.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           "Binary"));
    label2->setFont (Font (24.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (binDisplay = new TextEditor (String::empty));
    binDisplay->setMultiLine (true);
    binDisplay->setReturnKeyStartsNewLine (false);
    binDisplay->setReadOnly (false);
    binDisplay->setScrollbarsShown (true);
    binDisplay->setCaretVisible (true);
    binDisplay->setPopupMenuEnabled (true);
    binDisplay->setText ("01100000 01100000");

    addAndMakeVisible (label3 = new Label ("new label",
                                           "Decimal"));
    label3->setFont (Font (24.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (decDisplay = new TextEditor (String::empty));
    decDisplay->setMultiLine (false);
    decDisplay->setReturnKeyStartsNewLine (false);
    decDisplay->setReadOnly (false);
    decDisplay->setScrollbarsShown (true);
    decDisplay->setCaretVisible (true);
    decDisplay->setPopupMenuEnabled (true);
    decDisplay->setText (String::empty);

    addAndMakeVisible (hexFormat = new ComboBox (String::empty));
    hexFormat->setEditableText (false);
    hexFormat->setJustificationType (Justification::centredLeft);
    hexFormat->setTextWhenNothingSelected ("Plain text");
    hexFormat->setTextWhenNoChoicesAvailable ("(no choices)");
    hexFormat->addItem ("Plain text", 1);
    hexFormat->addItem ("LUA table format", 2);
    hexFormat->addItem ("HEX string format", 3);
    hexFormat->addListener (this);

    addAndMakeVisible (bit16Switch = new ToggleButton (String::empty));
    bit16Switch->setButtonText ("16bit");
    bit16Switch->addListener (this);


    //[UserPreSize]
	hexDisplay->clear();
	hexDisplay->setFont (Font(owner.getFontManager().getDefaultMonoFontName(), 24, Font::plain));
	hexDisplay->setText (L"F0");
	hexDisplay->addListener (this);

	binDisplay->clear();
	binDisplay->setFont (Font(owner.getFontManager().getDefaultMonoFontName(), 16, Font::plain));
	binDisplay->setText (L"11110000");
	binDisplay->addListener (this);

	decDisplay->clear();
	decDisplay->setFont (Font(owner.getFontManager().getDefaultMonoFontName(), 24, Font::plain));
	decDisplay->setText (L"240");
	decDisplay->addListener (this);
    setSize (400, 256);
}

CtrlrMIDICalculator::~CtrlrMIDICalculator()
{
    hexDisplay = nullptr;
    label = nullptr;
    label2 = nullptr;
    binDisplay = nullptr;
    label3 = nullptr;
    decDisplay = nullptr;
    hexFormat = nullptr;
    bit16Switch = nullptr;
}

void CtrlrMIDICalculator::paint (Graphics& g)
{
}

void CtrlrMIDICalculator::resized()
{
    hexDisplay->setBounds (8, 40, getWidth() - 16, 32);
    label->setBounds (8, 8, 150, 24);
    label2->setBounds (8, 80, 150, 24);
    binDisplay->setBounds (8, 112, getWidth() - 16, 64);
    label3->setBounds (8, 184, 150, 24);
    decDisplay->setBounds (8, 216, getWidth() - 16, 32);
    hexFormat->setBounds (168, 8, 150, 24);
    bit16Switch->setBounds ((168) + (150), 8, 64, 24);
}

void CtrlrMIDICalculator::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == hexFormat)
    {
		formatData (binDisplay->getText(), false, false, true);
    }
}

void CtrlrMIDICalculator::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == bit16Switch)
    {
		formatData (hexDisplay->getText(), true, false, false);
    }
}

void CtrlrMIDICalculator::textEditorTextChanged (TextEditor &editor)
{
	if (&editor == decDisplay)
	{
		formatData (editor.getText(), false, true, false);
	}

	if (&editor == binDisplay)
	{
		formatData (editor.getText(), false, false, true);
	}

	if (&editor == hexDisplay)
	{
		formatData (editor.getText(), true, false, false);
	}
}

void CtrlrMIDICalculator::formatData (const String &data, const bool isHex, const bool isDec, const bool isBin)
{
	const bool bitsLen = bit16Switch->getToggleState();
	StringArray ar;
	ar.addTokens (data, " ;:\t", "\"\'");
	String bin,dec,hex;
	BigInteger bits(0);
	int d=0;
	for (int i=0; i<ar.size(); i++)
	{
		if (isHex)
		{
			d = ar[i].getHexValue32();
		}
		if (isDec)
		{
			d = ar[i].getIntValue();
		}
		if (isBin)
		{
			bits.parseString (ar[i], 2);
			d = bits.getBitRangeAsInt (0, bitsLen ? 16 : 8);
		}

		BigInteger bi(d);
		bin << bi.toString (2, bitsLen ? 16 : 8) + " ";
		dec << String::formatted ("%.3d ", d);
		hex << formatHex (d);
	}
	if (!isBin)
		binDisplay->setText (bin.trim(), false);
	if (!isDec)
		decDisplay->setText (dec.trim(), false);
	if (!isHex)
		hexDisplay->setText (makeHexPretty(hex.trim()), false);
}

String CtrlrMIDICalculator::formatHex(const int d)
{
	if (hexFormat->getSelectedId() == 1)
	{
		return (String::formatted ("%.3x ", d));
	}

	if (hexFormat->getSelectedId() == 2)
	{
		return (String::formatted ("0x%.2x, ", d));
	}

	if (hexFormat->getSelectedId() == 3)
	{
		return (String::formatted ("%.2x ", d));
	}

	return (String::formatted ("%.3x ", d));
}

String CtrlrMIDICalculator::makeHexPretty(const String &hex)
{
	if (hexFormat->getSelectedId() == 2)
	{
		return ("{" + hex.substring(0, hex.length()-1) + "}");
	}

	return (hex);
}