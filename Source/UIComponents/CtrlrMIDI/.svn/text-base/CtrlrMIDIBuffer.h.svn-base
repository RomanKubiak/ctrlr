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

#ifndef __JUCE_HEADER_16DA51FEAFD7A9F8__
#define __JUCE_HEADER_16DA51FEAFD7A9F8__

//[Headers]     -- You can add your own extra header files here --
#include "CtrlrMIDILibrary/CtrlrMIDILibrary.h"
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
                         public ComboBoxListener,
                         public LabelListener,
                         public ButtonListener
{
public:
    //==============================================================================
    CtrlrMIDIBuffer (CtrlrPanel &_owner);
    ~CtrlrMIDIBuffer();

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
	CtrlrMIDILibrary &getLibrary();
	LMemoryBlock processFormula(const String &formula);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void labelTextChanged (Label* labelThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



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
    ScopedPointer<CodeEditorComponent> documentEditor;
    ScopedPointer<ComboBox> bufferSource;
    ScopedPointer<Label> label;
    ScopedPointer<Label> prefixLengthLabel;
    ScopedPointer<Label> nameLengthLabel;
    ScopedPointer<Label> dataOffsetLabel;
    ScopedPointer<Label> suffixLengthLabel;
    ScopedPointer<Label> label7;
    ScopedPointer<Label> label8;
    ScopedPointer<Label> label9;
    ScopedPointer<Label> nameOffsetLabel;
    ScopedPointer<Label> dataLengthLabel;
    ScopedPointer<TextButton> reloadButton;
    ScopedPointer<CtrlrMidiBufferStatus> status;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrMIDIBuffer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_16DA51FEAFD7A9F8__
