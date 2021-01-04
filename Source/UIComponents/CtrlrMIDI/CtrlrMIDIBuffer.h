/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "JuceClasses/LMemoryBlock.h"
class CtrlrMIDIBuffer;

class CtrlrMidiBufferStatus : public Component
{
	public:
		CtrlrMidiBufferStatus (CtrlrMIDIBuffer &_owner);
		void mouseMove (const MouseEvent &e);
		void mouseDrag (const MouseEvent &e);
		void paint(Graphics &g);
		void update(const int x, const int y);
		const String hexString(const String &hex);
		const String currentByte(const CodeDocument::Position &pos);
	private:
		CtrlrMIDIBuffer &owner;
		AttributedString status,size;
		Font statusFont;
};

struct CtrlrMIDIBufferTokenSet
{
	CtrlrMIDIBufferTokenSet()
	: prefixLen(0), nameLen(0), nameOffset(0),
	  dataLen(0), dataOffset(0), suffixLen(0),
	  len(0)
	{}

	CtrlrMIDIBufferTokenSet(const CtrlrMIDIBufferTokenSet &other)
	: prefixLen(other.prefixLen), nameLen(other.nameLen), nameOffset(other.nameOffset),
	  dataLen(other.dataLen), dataOffset(other.dataOffset), suffixLen(other.suffixLen),
	  len(other.len)
	{}

	CtrlrMIDIBufferTokenSet(uint32 _prefixLen, uint32 _nameLen, uint32 _nameOffset, uint32 _dataLen, uint32 _dataOffset, uint32 _suffixLen, uint32 _len)
	: prefixLen(_prefixLen), nameLen(_nameLen), nameOffset(_nameOffset),
	  dataLen(_dataLen), dataOffset(_dataOffset), suffixLen(_suffixLen), len(_len)
	{}

    uint32 prefixLen;
    uint32 nameLen;
    uint32 nameOffset;
    uint32 dataLen;
    uint32 dataOffset;
    uint32 suffixLen;
    uint32 len;
};

class CtrlrMIDIBufferTokeniser : public CodeTokeniser
{
   	public:
		enum TokenType
		{
	        tokenType_rawData = 0,
			tokenType_name,
			tokenType_data,
			tokenType_suffix,
			tokenType_sysexToken,
			tokenType_prefix,
			tokenType_mismatch
		};
   		CtrlrMIDIBufferTokeniser(CtrlrMIDIBuffer &_owner);
   		void setTokenSet (CtrlrMIDIBufferTokenSet tokenSetToUse);
		int readNextToken (CodeDocument::Iterator &source);
		CodeEditorComponent::ColourScheme getDefaultColourScheme();

	private:
		CodeEditorComponent::ColourScheme colourScheme;
		CtrlrMIDIBuffer &owner;
		CtrlrMIDIBufferTokenSet tokenSet;
};
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrMIDIBuffer  : public Component,
                         public CodeDocument::Listener,
                         public juce::ComboBox::Listener,
                         public juce::Label::Listener,
                         public juce::Button::Listener
{
public:
    //==============================================================================
    CtrlrMIDIBuffer (CtrlrPanel &_owner);
    ~CtrlrMIDIBuffer() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void loadBinFile(const File fileToOpen);
	void loadTextFile(const File fileToOpen);
	void reloadEditor(const String &_dataToDisplay, const bool resetPositions=false);
	void wordBreak(const int columns);
	CtrlrMIDIBufferTokenSet getTokenSetFromMenu();
	void colorize();
	uint32 getDataSize();
	CodeEditorComponent &getCodeEditor();
	CodeDocument &getDocument();
	MemoryBlock getData();
	void clearUnequalPositions();
	void addUnequalPosition(const int position);
	Array<int> &getUnequalPosition();
	void setSizeMatch(const bool _matchingSize);
	const bool getSizeMatch() { return (matchingSize); }
	void setCompareMode(const bool _compareMode);
	const bool getCompareMode() { return (compareMode); }
	void codeDocumentTextInserted (const String &newText, int insertIndex);
	void codeDocumentTextDeleted (int startIndex, int endIndex);
	ValueTree getState(const Identifier &stateId);
	const File browseForFile(const String &mask);
	void restoreState(const ValueTree &savedState);
	void loadFromProgram(const String &direction, const String &type);
	LMemoryBlock processFormula(const String &formula);
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void labelTextChanged (juce::Label* labelThatHasChanged) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    CodeDocument document;
    CtrlrMIDIBufferTokeniser tokeniser;
	File lastBrowsedDirectory;
	File lastFile;
	String dataToDisplay;
	uint32 dataToDisplaySize;
	int lastNumberOfColumns;
	CtrlrMIDIBufferTokenSet currentTokenSet;
	MemoryBlock data;
	Array<int> unequalPositions;
	bool matchingSize, compareMode;
	CtrlrPanel &owner;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<CodeEditorComponent> documentEditor;
    std::unique_ptr<juce::ComboBox> bufferSource;
    std::unique_ptr<juce::Label> label;
    std::unique_ptr<juce::Label> prefixLengthLabel;
    std::unique_ptr<juce::Label> nameLengthLabel;
    std::unique_ptr<juce::Label> dataOffsetLabel;
    std::unique_ptr<juce::Label> suffixLengthLabel;
    std::unique_ptr<juce::Label> label7;
    std::unique_ptr<juce::Label> label8;
    std::unique_ptr<juce::Label> label9;
    std::unique_ptr<juce::Label> nameOffsetLabel;
    std::unique_ptr<juce::Label> dataLengthLabel;
    std::unique_ptr<juce::TextButton> reloadButton;
    std::unique_ptr<CtrlrMidiBufferStatus> status;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrMIDIBuffer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

