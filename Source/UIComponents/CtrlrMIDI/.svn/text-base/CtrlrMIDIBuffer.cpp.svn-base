/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "stdafx.h"
#include "CtrlrPanel/CtrlrPanel.h"

//[/Headers]

#include "CtrlrMIDIBuffer.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
CtrlrMIDIBufferTokeniser::CtrlrMIDIBufferTokeniser(CtrlrMIDIBuffer &_owner) : owner(_owner)
{
}

void CtrlrMIDIBufferTokeniser::setTokenSet (CtrlrMIDIBufferTokenSet tokenSetToUse)
{
	tokenSet = tokenSetToUse;
}

int CtrlrMIDIBufferTokeniser::readNextToken (CodeDocument::Iterator &source)
{
	const juce_wchar c 	= source.peekNextChar();
	int result  		= CtrlrMIDIBufferTokeniser::tokenType_rawData;
	int pos 			= source.getPosition();
	int prefixHigh		= (tokenSet.prefixLen*3)-1;
	int suffixLow		= ((tokenSet.len) - (tokenSet.suffixLen*3));
	int suffixHigh		= tokenSet.len;
	int dataLow			= (tokenSet.dataOffset*3)-1;
	int dataHigh		= dataLow + ((tokenSet.dataLen*3));
	int nameLow			= (tokenSet.nameOffset*3)-1;
	int nameHigh		= nameLow + (tokenSet.nameLen*3);

	source.skipWhitespace();

	switch (c)
	{
		case 0:
			source.skip();
            return (result);
	}

	if (owner.getUnequalPosition().contains(pos))
	{
		source.skip();
		return (tokenType_mismatch);
	}

	if (pos >= 0 && pos < prefixHigh && prefixHigh>0)
	{
		source.skip();
		return (tokenType_prefix);
	}

	if (pos >= suffixLow && pos <= suffixHigh)
	{
		source.skip();
		return (tokenType_suffix);
	}

	if (pos >= dataLow && pos < dataHigh)
	{
		source.skip();
		return (tokenType_data);
	}

	if (pos >= nameLow && pos < nameHigh)
	{
		source.skip();
		return (tokenType_name);
	}
	source.skip();
	return result;
}

CodeEditorComponent::ColourScheme CtrlrMIDIBufferTokeniser::getDefaultColourScheme ()
{
	struct Type
    {
        const char* name;
        uint32 colour;
    };

    const Type types[] =
    {
        { "RawData",    0xff0e0e0e },
        { "Name",       0xFF237D23 },
        { "Data",       0xFF949494 },
        { "Suffix",     0xFF0028A4 },
        { "SysexToken", 0xff0000ff },
        { "Prefix",     0xFFA4A400 },
		{ "Mismatch",   0xFFFF0000 }
    };

    CodeEditorComponent::ColourScheme cs;

    for (unsigned int i = 0; i < sizeof (types) / sizeof (types[0]); ++i)  // (NB: numElementsInArray doesn't work here in GCC4.2)
        cs.set (types[i].name, Colour (types[i].colour));

    return cs;
}

CtrlrMidiBufferStatus::CtrlrMidiBufferStatus (CtrlrMIDIBuffer &_owner)
	: owner(_owner)
{
	statusFont = Font(12.0f);
	status.setJustification (Justification::centredLeft);
	size.setFont (statusFont.boldened());
	size.setJustification (Justification::centred);
	owner.getCodeEditor().addMouseListener (this, true);
}

void CtrlrMidiBufferStatus::update(const int x, const int y)
{
	size.setText(STR(owner.getDataSize()/3));

	status.setFont (statusFont);
	status.setText ("Byte: ");
	CodeDocument::Position pos = owner.getCodeEditor().getPositionAt (x,y);

	status.append (STR(pos.getPosition()/3), statusFont.boldened());
	status.append ("/"+STR(pos.getPosition()), statusFont);
	status.append (" "+currentByte(pos), statusFont);

	Range<int> sel = owner.getCodeEditor().getHighlightedRegion();
	if (!sel.isEmpty())
	{
		const int end   = sel.getEnd() / 3;
		const int start = sel.getStart() / 3;
		String selection = owner.getCodeEditor().getTextInRange (Range<int> (sel.getStart(),sel.getEnd())).trim();

		status.append (" Selected("+STR((end - start)+1)+"): ", statusFont);
		status.append (STR(start), statusFont.boldened());
		status.append (" - ", statusFont);
		status.append (STR(end), statusFont.boldened());
		status.append (" "+hexString(selection), statusFont);
	}

	repaint();
}

const String CtrlrMidiBufferStatus::currentByte(const CodeDocument::Position &pos)
{
	const String current 	= owner.getCodeEditor().getTextInRange(Range<int>(pos.getPosition(), pos.getPosition()+1));
	const String next 		= owner.getCodeEditor().getTextInRange(Range<int>(pos.getPosition()+1, pos.getPosition()+2));
	const String previous 	= owner.getCodeEditor().getTextInRange(Range<int>(pos.getPosition()-1, pos.getPosition()));
	String byte;
	String ret;

	if (next.trim().isEmpty())
	{
        byte << previous << current;
	}

	if (previous.trim().isEmpty())
	{
		byte << current << next;
	}

	if (!byte.isEmpty())
	{
		return (hexString(byte));
	}

	return (String::empty);
}

const String CtrlrMidiBufferStatus::hexString(const String &hex)
{
	String ret;
	MemoryBlock mb;
	mb.loadFromHexString (hex);
	uint8 *ptr = (uint8*)mb.getData();
	for (size_t i=0; i<mb.getSize(); i++)
	{
		const String bis = BigInteger (*(ptr+i)).toString(2, 8);
		ret << String::formatted ("[0x%.2x/%.3d/", *(ptr+i), *(ptr+i)) << bis.substring(0,4) << ":" << bis.substring(4,8) << "] ";
	}

	return (ret.trim());
}

void CtrlrMidiBufferStatus::paint(Graphics &g)
{
	g.fillAll (Colours::whitesmoke);
	g.setColour (Colours::black);
	g.drawRect (getWidth() - 32.0f, 0.0f, 1.0f, (float)getHeight());
	status.draw (g, Rectangle<float>(2.0f, 0.0f, getWidth()-32.0f, getHeight()));
	size.draw (g, Rectangle<float> (getWidth() - 32.0f, 0.0f, 32.0f, getHeight()));
}

void CtrlrMidiBufferStatus::mouseMove (const MouseEvent &e)
{
	if (e.eventComponent == &owner.getCodeEditor())
	{
		update(e.x,e.y);
	}
}

void CtrlrMidiBufferStatus::mouseDrag (const MouseEvent &e)
{
	if (e.eventComponent == &owner.getCodeEditor())
	{
		update(e.x,e.y);
	}
}
//[/MiscUserDefs]

//==============================================================================
CtrlrMIDIBuffer::CtrlrMIDIBuffer (CtrlrPanel &_owner)
    : owner(_owner), tokeniser(*this)
{
    addAndMakeVisible (documentEditor = new CodeEditorComponent (document, &tokeniser));

    addAndMakeVisible (bufferSource = new ComboBox (String::empty));
    bufferSource->setEditableText (false);
    bufferSource->setJustificationType (Justification::centredLeft);
    bufferSource->setTextWhenNothingSelected ("Select buffer source");
    bufferSource->setTextWhenNoChoicesAvailable ("(no choices)");
    bufferSource->addItem ("Custom data", 1);
    bufferSource->addItem ("File - SYX", 2);
    bufferSource->addItem ("File - Text", 3);
    bufferSource->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          "Prefix"));
    label->setFont (Font (11.00f, Font::bold | Font::italic));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (prefixLengthLabel = new Label ("new label",
                                                      "4"));
    prefixLengthLabel->setFont (Font (12.00f, Font::plain));
    prefixLengthLabel->setJustificationType (Justification::centred);
    prefixLengthLabel->setEditable (true, true, false);
    prefixLengthLabel->setColour (Label::backgroundColourId, Colour (0xffefff8f));
    prefixLengthLabel->setColour (Label::outlineColourId, Colour (0x8c000000));
    prefixLengthLabel->setColour (TextEditor::textColourId, Colours::black);
    prefixLengthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    prefixLengthLabel->addListener (this);

    addAndMakeVisible (nameLengthLabel = new Label ("new label",
                                                    "16"));
    nameLengthLabel->setTooltip ("Name section length");
    nameLengthLabel->setFont (Font (12.00f, Font::plain));
    nameLengthLabel->setJustificationType (Justification::centred);
    nameLengthLabel->setEditable (true, true, false);
    nameLengthLabel->setColour (Label::backgroundColourId, Colour (0xffbeff87));
    nameLengthLabel->setColour (Label::outlineColourId, Colour (0x8c000000));
    nameLengthLabel->setColour (TextEditor::textColourId, Colours::black);
    nameLengthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    nameLengthLabel->addListener (this);

    addAndMakeVisible (dataOffsetLabel = new Label ("new label",
                                                    "4"));
    dataOffsetLabel->setTooltip ("Data section offset");
    dataOffsetLabel->setFont (Font (12.00f, Font::plain));
    dataOffsetLabel->setJustificationType (Justification::centred);
    dataOffsetLabel->setEditable (true, true, false);
    dataOffsetLabel->setColour (Label::backgroundColourId, Colour (0xffa6a6a6));
    dataOffsetLabel->setColour (Label::outlineColourId, Colour (0x8c000000));
    dataOffsetLabel->setColour (TextEditor::textColourId, Colours::black);
    dataOffsetLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    dataOffsetLabel->addListener (this);

    addAndMakeVisible (suffixLengthLabel = new Label ("new label",
                                                      "4"));
    suffixLengthLabel->setFont (Font (12.00f, Font::plain));
    suffixLengthLabel->setJustificationType (Justification::centred);
    suffixLengthLabel->setEditable (true, true, false);
    suffixLengthLabel->setColour (Label::backgroundColourId, Colour (0xff79a0ff));
    suffixLengthLabel->setColour (Label::outlineColourId, Colour (0x8c000000));
    suffixLengthLabel->setColour (TextEditor::textColourId, Colours::black);
    suffixLengthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    suffixLengthLabel->addListener (this);

    addAndMakeVisible (label7 = new Label ("new label",
                                           "Name"));
    label7->setFont (Font (11.00f, Font::bold | Font::italic));
    label7->setJustificationType (Justification::centred);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label8 = new Label ("new label",
                                           "Data"));
    label8->setFont (Font (11.00f, Font::bold | Font::italic));
    label8->setJustificationType (Justification::centred);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label9 = new Label ("new label",
                                           "Suffix"));
    label9->setFont (Font (11.00f, Font::bold | Font::italic));
    label9->setJustificationType (Justification::centred);
    label9->setEditable (false, false, false);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nameOffsetLabel = new Label ("new label",
                                                    "16"));
    nameOffsetLabel->setTooltip ("Name section offset");
    nameOffsetLabel->setFont (Font (12.00f, Font::plain));
    nameOffsetLabel->setJustificationType (Justification::centred);
    nameOffsetLabel->setEditable (true, true, false);
    nameOffsetLabel->setColour (Label::backgroundColourId, Colour (0xffe6ffd0));
    nameOffsetLabel->setColour (Label::outlineColourId, Colour (0x8c000000));
    nameOffsetLabel->setColour (TextEditor::textColourId, Colours::black);
    nameOffsetLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    nameOffsetLabel->addListener (this);

    addAndMakeVisible (dataLengthLabel = new Label ("new label",
                                                    "4"));
    dataLengthLabel->setFont (Font (12.00f, Font::plain));
    dataLengthLabel->setJustificationType (Justification::centred);
    dataLengthLabel->setEditable (true, true, false);
    dataLengthLabel->setColour (Label::backgroundColourId, Colour (0xff7c7c7c));
    dataLengthLabel->setColour (Label::outlineColourId, Colour (0x8c000000));
    dataLengthLabel->setColour (TextEditor::textColourId, Colours::black);
    dataLengthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    dataLengthLabel->addListener (this);

    addAndMakeVisible (reloadButton = new TextButton (String::empty));
    reloadButton->setButtonText ("Reload");
    reloadButton->addListener (this);
    reloadButton->setColour (TextButton::buttonColourId, Colour (0xff8cff7f));

    addAndMakeVisible (status = new CtrlrMidiBufferStatus (*this));


    //[UserPreSize]
    document.addListener (this);
    matchingSize		= true;
    compareMode			= false;
	dataToDisplaySize	=  0;
	lastNumberOfColumns = -1;
	bufferSource->setSelectedId (1, dontSendNotification);
    //[/UserPreSize]

    setSize (400, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrMIDIBuffer::~CtrlrMIDIBuffer()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    document.removeListener (this);
    //[/Destructor_pre]

    documentEditor = nullptr;
    bufferSource = nullptr;
    label = nullptr;
    prefixLengthLabel = nullptr;
    nameLengthLabel = nullptr;
    dataOffsetLabel = nullptr;
    suffixLengthLabel = nullptr;
    label7 = nullptr;
    label8 = nullptr;
    label9 = nullptr;
    nameOffsetLabel = nullptr;
    dataLengthLabel = nullptr;
    reloadButton = nullptr;
    status = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrMIDIBuffer::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrMIDIBuffer::resized()
{
    documentEditor->setBounds (0, 88, getWidth() - 0, getHeight() - 104);
    bufferSource->setBounds (8, 8, proportionOfWidth (0.4000f), 24);
    label->setBounds (8, 40, 32, 16);
    prefixLengthLabel->setBounds (8, 56, 32, 24);
    nameLengthLabel->setBounds (80, 56, 32, 24);
    dataOffsetLabel->setBounds (120, 56, 32, 24);
    suffixLengthLabel->setBounds (192, 56, 32, 24);
    label7->setBounds (48, 40, 64, 16);
    label8->setBounds (120, 40, 64, 16);
    label9->setBounds (192, 40, 32, 16);
    nameOffsetLabel->setBounds (48, 56, 32, 24);
    dataLengthLabel->setBounds (152, 56, 32, 24);
    reloadButton->setBounds ((8) + (proportionOfWidth (0.4000f)), 8, proportionOfWidth (0.1525f), 24);
    status->setBounds (0, getHeight() - 16, getWidth() - 0, 16);
    //[UserResized] Add your own custom resize handling here..
	const int columnsVisible	= documentEditor->getNumColumnsOnScreen();

	if (lastNumberOfColumns != columnsVisible)
	{
		lastNumberOfColumns = columnsVisible;
		colorize();
	}
    //[/UserResized]
}

void CtrlrMIDIBuffer::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == bufferSource)
    {
        //[UserComboBoxCode_bufferSource] -- add your combo box handling code here..
		switch (bufferSource->getSelectedId())
		{
			case 1:
				break;
			case 2:
				loadBinFile(File::nonexistent);
				break;
			case 3:
				loadTextFile(File::nonexistent);
				break;
			default:
				break;
		}
        //[/UserComboBoxCode_bufferSource]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void CtrlrMIDIBuffer::labelTextChanged (Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == prefixLengthLabel)
    {
        //[UserLabelCode_prefixLengthLabel] -- add your label text handling code here..
        //[/UserLabelCode_prefixLengthLabel]
    }
    else if (labelThatHasChanged == nameLengthLabel)
    {
        //[UserLabelCode_nameLengthLabel] -- add your label text handling code here..
        //[/UserLabelCode_nameLengthLabel]
    }
    else if (labelThatHasChanged == dataOffsetLabel)
    {
        //[UserLabelCode_dataOffsetLabel] -- add your label text handling code here..
        //[/UserLabelCode_dataOffsetLabel]
    }
    else if (labelThatHasChanged == suffixLengthLabel)
    {
        //[UserLabelCode_suffixLengthLabel] -- add your label text handling code here..
        //[/UserLabelCode_suffixLengthLabel]
    }
    else if (labelThatHasChanged == nameOffsetLabel)
    {
        //[UserLabelCode_nameOffsetLabel] -- add your label text handling code here..
        //[/UserLabelCode_nameOffsetLabel]
    }
    else if (labelThatHasChanged == dataLengthLabel)
    {
        //[UserLabelCode_dataLengthLabel] -- add your label text handling code here..
        //[/UserLabelCode_dataLengthLabel]
    }

    //[UserlabelTextChanged_Post]
    colorize();
    //[/UserlabelTextChanged_Post]
}

void CtrlrMIDIBuffer::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == reloadButton)
    {
        //[UserButtonCode_reloadButton] -- add your button handler code here..
        switch (bufferSource->getSelectedId())
		{
			case 1:
                reloadEditor(document.getAllContent(), false);
				break;
			case 7:
			case 8:
			default:
				break;
		}
        //[/UserButtonCode_reloadButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
const File CtrlrMIDIBuffer::browseForFile(const String &mask)
{
	FileChooser fc("Open file", lastBrowsedDirectory, mask, true);
	if (fc.browseForFileToOpen())
	{
		if (fc.getResult().existsAsFile())
		{
			lastBrowsedDirectory	= fc.getResult().getParentDirectory();
			return (fc.getResult());
		}
	}

	return (File::nonexistent);
}

void CtrlrMIDIBuffer::loadBinFile(const File fileToOpen)
{
	_DBG("CtrlrMIDIBuffer::loadBinFile");
	if (fileToOpen == File::nonexistent)
	{
		lastFile = browseForFile("*.syx;*.bin;*.dat;*.*");
	}
	else
	{
		lastFile = fileToOpen;
	}

	lastFile.loadFileAsData (data);
	reloadEditor (String::toHexString (data.getData(), data.getSize()), true);
}

void CtrlrMIDIBuffer::loadTextFile(const File fileToOpen)
{
	if (fileToOpen == File::nonexistent)
	{
		lastFile = browseForFile("*.syx;*.bin;*.dat;*.*");
	}
	else
	{
		lastFile = fileToOpen;
	}

    MemoryBlock data;
	data.loadFromHexString (lastFile.loadFileAsString());
	reloadEditor (lastFile.loadFileAsString(), true);
}

CtrlrMIDIBufferTokenSet CtrlrMIDIBuffer::getTokenSetFromMenu()
{
	return (CtrlrMIDIBufferTokenSet (	prefixLengthLabel->getText().getIntValue(),
										nameLengthLabel->getText().getIntValue(),
										nameOffsetLabel->getText().getIntValue(),
										dataLengthLabel->getText().getIntValue(),
										dataOffsetLabel->getText().getIntValue(),
										suffixLengthLabel->getText().getIntValue(),
										document.getNumCharacters()
									));
}

void CtrlrMIDIBuffer::reloadEditor(const String &_dataToDisplay, const bool resetPositions)
{
	dataToDisplay		= _dataToDisplay;
	dataToDisplaySize	= dataToDisplay.length();

	if (resetPositions)
	{
		prefixLengthLabel->setText ("4", sendNotification);
		nameLengthLabel->setText ("16", sendNotification);
		nameOffsetLabel->setText ("4", sendNotification);
		dataLengthLabel->setText ("16", sendNotification);
		dataOffsetLabel->setText ("20", sendNotification);
		suffixLengthLabel->setText ("4", sendNotification);
	}

	colorize();
}

void CtrlrMIDIBuffer::colorize()
{
	if (!dataToDisplay.contains("\n"))
		wordBreak(documentEditor->getNumColumnsOnScreen());

	currentTokenSet = getTokenSetFromMenu();
    tokeniser.setTokenSet (currentTokenSet);
    status->repaint();
}

void CtrlrMIDIBuffer::wordBreak(const int columns)
{
	const size_t eol = (dataToDisplaySize / 3) / columns;
	if (eol < dataToDisplaySize)
	{
		uint32 nextPosition = 0;
		uint32 prevPosition = 0;

		String total;
		while (nextPosition < dataToDisplaySize)
		{
			nextPosition += columns;

			if (nextPosition >= dataToDisplaySize)
			{
				nextPosition = dataToDisplaySize;
			}

			total << (prevPosition ? "\n" : String::empty) + dataToDisplay.substring (prevPosition, nextPosition).trim();

			prevPosition = nextPosition;
		}

		document.replaceAllContent (total);
	}
}

uint32 CtrlrMIDIBuffer::getDataSize()
{
	return (document.getNumCharacters());
}

CodeEditorComponent &CtrlrMIDIBuffer::getCodeEditor()
{
	return (*documentEditor);
}

CodeDocument &CtrlrMIDIBuffer::getDocument()
{
	return (document);
}

MemoryBlock CtrlrMIDIBuffer::getData()
{
	MemoryBlock bl;
	bl.loadFromHexString (document.getAllContent());
	return (bl);
}

void CtrlrMIDIBuffer::clearUnequalPositions()
{
	unequalPositions.clear();
}

void CtrlrMIDIBuffer::setSizeMatch(const bool _matchingSize)
{
	matchingSize = _matchingSize;
}

void CtrlrMIDIBuffer::setCompareMode(const bool _compareMode)
{
	compareMode = _compareMode;
}

void CtrlrMIDIBuffer::addUnequalPosition(const int position)
{
	unequalPositions.addIfNotAlreadyThere (position);
}

Array<int> &CtrlrMIDIBuffer::getUnequalPosition()
{
	return (unequalPositions);
}

void CtrlrMIDIBuffer::codeDocumentTextInserted (const String &newText, int insertIndex)
{
}

void CtrlrMIDIBuffer::codeDocumentTextDeleted (int startIndex, int endIndex)
{
}

ValueTree CtrlrMIDIBuffer::getState(const Identifier &stateId)
{
	ValueTree state(stateId);
	state.setProperty (Ids::midiBufferEditorSource,bufferSource->getSelectedId(), nullptr);
    state.setProperty (Ids::midiBufferEditorFilePath, lastFile.getFullPathName(), nullptr);

    if (bufferSource->getSelectedId() == 1)
	{
		state.setProperty (Ids::midiBufferEditorContent, document.getAllContent(), nullptr);
	}

    state.setProperty (Ids::midiBufferEditorCodeEditor, CodeEditorComponent::State(*documentEditor).toString(), nullptr);
	return (state);
}

void CtrlrMIDIBuffer::restoreState(const ValueTree &savedState)
{
	bufferSource->setSelectedId (savedState.getProperty (Ids::midiBufferEditorSource),dontSendNotification);

	if (bufferSource->getSelectedId() == 1)
	{
		document.replaceAllContent (savedState.getProperty(Ids::midiBufferEditorContent));
	}
	else if (bufferSource->getSelectedId() == 3)
	{
		loadTextFile(savedState.getProperty(Ids::midiBufferEditorFilePath).toString());
	}
	else if (bufferSource->getSelectedId() == 2)
	{
		loadBinFile(savedState.getProperty(Ids::midiBufferEditorFilePath).toString());
	}
}

void CtrlrMIDIBuffer::loadFromProgram(const String &direction, const String &type)
{
}

LMemoryBlock CtrlrMIDIBuffer::processFormula(const String &formula)
{
	CtrlrOwnedMidiMessage m(owner);
	m.setProperty (Ids::midiMessageType, SysEx);
	m.setProperty (Ids::midiMessageSysExFormula, formula);
	return (m.getData());
}

CtrlrMIDILibrary &CtrlrMIDIBuffer::getLibrary()
{
	return (owner.getCtrlrMIDILibrary());
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrMIDIBuffer" componentName=""
                 parentClasses="public Component, public CodeDocument::Listener"
                 constructorParams="CtrlrPanel &amp;_owner" variableInitialisers="owner(_owner), tokeniser(*this)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="400" initialHeight="400">
  <BACKGROUND backgroundColour="ffffff"/>
  <GENERICCOMPONENT name="" id="11490a54f4d9ce20" memberName="documentEditor" virtualName=""
                    explicitFocusOrder="0" pos="0 88 0M 104M" class="CodeEditorComponent"
                    params="document, &amp;tokeniser"/>
  <COMBOBOX name="" id="89bbcb18489c2790" memberName="bufferSource" virtualName=""
            explicitFocusOrder="0" pos="8 8 40% 24" editable="0" layout="33"
            items="Custom data&#10;File - SYX&#10;File - Text" textWhenNonSelected="Select buffer source"
            textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="812d76f10e6a2f58" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="8 40 32 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Prefix" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="11"
         bold="1" italic="1" justification="33"/>
  <LABEL name="new label" id="a8af45fb34466561" memberName="prefixLengthLabel"
         virtualName="" explicitFocusOrder="0" pos="8 56 32 24" bkgCol="ffefff8f"
         outlineCol="8c000000" edTextCol="ff000000" edBkgCol="0" labelText="4"
         editableSingleClick="1" editableDoubleClick="1" focusDiscardsChanges="0"
         fontname="Default font" fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="c4b3824503e9b2ce" memberName="nameLengthLabel"
         virtualName="" explicitFocusOrder="0" pos="80 56 32 24" tooltip="Name section length"
         bkgCol="ffbeff87" outlineCol="8c000000" edTextCol="ff000000"
         edBkgCol="0" labelText="16" editableSingleClick="1" editableDoubleClick="1"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="ea5df1a95ce050da" memberName="dataOffsetLabel"
         virtualName="" explicitFocusOrder="0" pos="120 56 32 24" tooltip="Data section offset"
         bkgCol="ffa6a6a6" outlineCol="8c000000" edTextCol="ff000000"
         edBkgCol="0" labelText="4" editableSingleClick="1" editableDoubleClick="1"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="7bcc861e345cae32" memberName="suffixLengthLabel"
         virtualName="" explicitFocusOrder="0" pos="192 56 32 24" bkgCol="ff79a0ff"
         outlineCol="8c000000" edTextCol="ff000000" edBkgCol="0" labelText="4"
         editableSingleClick="1" editableDoubleClick="1" focusDiscardsChanges="0"
         fontname="Default font" fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="61138b8535d5fcc9" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="48 40 64 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Name" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="11"
         bold="1" italic="1" justification="36"/>
  <LABEL name="new label" id="399521cf99c21fdb" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="120 40 64 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Data" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="11"
         bold="1" italic="1" justification="36"/>
  <LABEL name="new label" id="617443e4e1f072fd" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="192 40 32 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Suffix" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="11"
         bold="1" italic="1" justification="36"/>
  <LABEL name="new label" id="28f6d8c68ee16e6f" memberName="nameOffsetLabel"
         virtualName="" explicitFocusOrder="0" pos="48 56 32 24" tooltip="Name section offset"
         bkgCol="ffe6ffd0" outlineCol="8c000000" edTextCol="ff000000"
         edBkgCol="0" labelText="16" editableSingleClick="1" editableDoubleClick="1"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="949532f6fb03bcb4" memberName="dataLengthLabel"
         virtualName="" explicitFocusOrder="0" pos="152 56 32 24" bkgCol="ff7c7c7c"
         outlineCol="8c000000" edTextCol="ff000000" edBkgCol="0" labelText="4"
         editableSingleClick="1" editableDoubleClick="1" focusDiscardsChanges="0"
         fontname="Default font" fontsize="12" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="" id="4308facfa36a7140" memberName="reloadButton" virtualName=""
              explicitFocusOrder="0" pos="0R 8 15.25% 24" posRelativeX="89bbcb18489c2790"
              bgColOff="ff8cff7f" buttonText="Reload" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <GENERICCOMPONENT name="" id="d3e76702cdb231b8" memberName="status" virtualName=""
                    explicitFocusOrder="0" pos="0 16R 0M 16" class="CtrlrMidiBufferStatus"
                    params="*this"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
