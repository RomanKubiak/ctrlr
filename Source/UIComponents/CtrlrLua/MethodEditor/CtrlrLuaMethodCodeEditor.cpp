#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrLuaMethodCodeEditor.h"
#include "CtrlrLuaMethodEditor.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "Methods/CtrlrLuaMethodManager.h"
#include "CtrlrLuaDebugger.h"
#include "CtrlrLuaManager.h"

CtrlrLuaMethodCodeEditor::CtrlrLuaMethodCodeEditor(CtrlrLuaMethodEditor &_owner, CtrlrLuaMethod *_method)
	:	editorComponent(nullptr),
		owner(_owner),
		method(_method),
		lastFoundPosition(-1)
{
	addAndMakeVisible (editorComponent	= new GenericCodeEditorComponent (*this,
															document, codeTokeniser = new CtrlrLuaCodeTokeniser()));

	editorComponent->grabKeyboardFocus();
	document.replaceAllContent(method->getCode());
	document.setSavePoint();

	document.addListener (this);
	editorComponent->addMouseListener (this, true);
	editorComponent->addKeyListener (this);

	if (method != nullptr)
		method->setCodeEditor (this);

	if (owner.getComponentTree().hasProperty (Ids::luaMethodEditorFont))
	{
		setFontAndColour (owner.getOwner().getCtrlrManagerOwner().getFontManager().getFontFromString (owner.getComponentTree().getProperty (Ids::luaMethodEditorFont))
					,VAR2COLOUR(owner.getComponentTree().getProperty (Ids::luaMethodEditorBgColour, Colours::white.toString())));
	}
	else
	{
		setFontAndColour (Font (Font::getDefaultMonospacedFontName(), 14.0f, Font::plain), Colours::white);
	}
}

CtrlrLuaMethodCodeEditor::~CtrlrLuaMethodCodeEditor()
{
	masterReference.clear();

	if (method)
		method->setCodeEditor (nullptr);

	document.removeListener (this);
	deleteAndZero(editorComponent);
	deleteAndZero (codeTokeniser);
}

void CtrlrLuaMethodCodeEditor::resized()
{
	editorComponent->setBounds (0,0,getWidth(),getHeight());
}

void CtrlrLuaMethodCodeEditor::mouseDown (const MouseEvent &e)
{
	CodeDocument::Position pos = editorComponent->getCaretPos();
	String url;
	if (isMouseOverUrl (pos, &url))
	{
		URL(url).launchInDefaultBrowser();
	}
	owner.setPositionLabelText ("Line:  " + String(pos.getLineNumber()+1) + " Column: " + String(pos.getIndexInLine()));
}

void CtrlrLuaMethodCodeEditor::mouseMove (const MouseEvent &e)
{
	if (e.eventComponent == editorComponent)
	{
		CodeDocument::Position pos = editorComponent->getPositionAt (e.x, e.y);
		if (isMouseOverUrl (pos))
		{
			editorComponent->setMouseCursor (MouseCursor::PointingHandCursor);
			return;
		}
		else if (editorComponent->getMouseCursor() == MouseCursor::PointingHandCursor)
		{
			editorComponent->setMouseCursor (MouseCursor::IBeamCursor);
		}
	}
}

bool CtrlrLuaMethodCodeEditor::keyStateChanged (bool isKeyDown, Component *originatingComponent)
{
	CodeDocument::Position pos = editorComponent->getCaretPos();
	owner.setPositionLabelText ("Line:  " + String(pos.getLineNumber()+1) + " Column: " + String(pos.getIndexInLine()));
	return (false);
}

bool CtrlrLuaMethodCodeEditor::keyPressed (const KeyPress &key, Component *originatingComponent)
{
    if (key.getModifiers().isCommandDown() )
	{
		if(key.getKeyCode() == 9)
		{
			owner.keyPressed (key, originatingComponent);
			return (true);
		}
		if (key.getKeyCode() == 83) // CTRL + S
		{
			saveDocument();
			return (true);
		}
		if (CharacterFunctions::toUpperCase ((juce_wchar) (key.getKeyCode())) == 70) // CTRL + F
		{
			// Show search Dialog
			editorComponent->showFindPanel();
			return (true);
		}
		if (CharacterFunctions::toUpperCase ((juce_wchar) (key.getKeyCode())) == 71) // CTRL + G
		{
			// Show Go To Dialog
			editorComponent->showGoTOPanel();
			return (true);
		}
		if (CharacterFunctions::toUpperCase ((juce_wchar) (key.getKeyCode())) == 72) // CTRL + H
		{
			// Show search Dialog
			editorComponent->showFindPanel(true);
			return (true);
		}

		if (key.getKeyCode() == KeyPress::deleteKey) // CTRL + Delete
		{
			owner.keyPressed(key, originatingComponent);
			return (true);
		}

		// search selected previous in current
		if (key.getModifiers().isShiftDown()
			&& key.getKeyCode() == KeyPress::F3Key) // CTRL + SHIFT + F3
		{
			editorComponent->findSelection(false);
			return (true);
		}
	}

	// search selected next in current
	if (key.getModifiers().isShiftDown() && key.getKeyCode() == KeyPress::F3Key) // SHIFT + F3
	{
		editorComponent->findSelection(true);
		return (true);
	}

	if (key.getKeyCode() == KeyPress::F7Key)
	{
		saveAndCompileDocument();
		return (true);
	}

	if (key.getKeyCode() == KeyPress::F8Key)
	{
		owner.saveAndCompilAllMethods();
		return (true);
	}

	CodeDocument::Position pos = editorComponent->getCaretPos();
	owner.setPositionLabelText ("Line:  " + String(pos.getLineNumber()+1) + " Column: " + String(pos.getIndexInLine()));
	return (false);
}

void CtrlrLuaMethodCodeEditor::codeDocumentTextInserted (const String& newText, int insertIndex)
{
	document.newTransaction();
	documentChanged(false);
}

void CtrlrLuaMethodCodeEditor::codeDocumentTextDeleted (int startIndex, int endIndex)
{
	document.newTransaction();
	documentChanged(false);
}

void CtrlrLuaMethodCodeEditor::documentChanged(const bool save, const bool recompile)
{
	owner.tabChanged (this, save, recompile);
}

void CtrlrLuaMethodCodeEditor::saveDocument()
{
	document.setSavePoint();

	if (method)
	{
		method->triggerSourceChangeFromEditor(false);
		if (owner.getMethodEditArea())
		{
			owner.getMethodEditArea()->setActiveOutputTab();
		}
	}

	documentChanged(true, false);
}

void CtrlrLuaMethodCodeEditor::saveAndCompileDocument()
{
	document.setSavePoint();

	if (method)
	{
		method->triggerSourceChangeFromEditor(true);
		if (owner.getMethodEditArea())
		{
			owner.getMethodEditArea()->setActiveOutputTab();
		}
	}

	documentChanged(true, true);
}

const bool CtrlrLuaMethodCodeEditor::isMouseOverUrl(CodeDocument::Position &position, String *url)
{
	if (position.getPosition() >= document.getNumCharacters())
	{
		return (false);
	}

	int moveLeft=0;

	while (!CharacterFunctions::isWhitespace(position.getCharacter()))
	{
		if (position.getPosition() <= 0)
			break;

		position.moveBy(-1);
		moveLeft++;
	}

	int start = position.getPosition();
	position.setPosition (position.getPosition()+moveLeft);

	while (!CharacterFunctions::isWhitespace(position.getCharacter()))
	{
		if (position.getPosition() >= document.getNumCharacters())
			break;

		position.moveBy(1);
	}

	int end = position.getPosition();

	const String word = document.getTextBetween (CodeDocument::Position(document, start), CodeDocument::Position(document, end)).trim();

	if (word.startsWith ("http://"))
	{
		if (url)
		{
			*url = word;
		}
		return (URL::isProbablyAWebsiteURL (word));
	}

	return (false);
}

void CtrlrLuaMethodCodeEditor::handleAsyncUpdate()
{
	owner.tabChanged (this, false, false);
}

void CtrlrLuaMethodCodeEditor::setErrorLine (const int lineNumber)
{
	editorComponent->scrollToLine (lineNumber-1);
	CodeDocument::Position start(document, lineNumber-1,0);
	CodeDocument::Position end(document,lineNumber-1,document.getLine (lineNumber-1).length());
	editorComponent->setHighlightedRegion(Range<int>(start.getPosition(), end.getPosition()));
}

void CtrlrLuaMethodCodeEditor::setFontAndColour (const Font newFont, const Colour newColour)
{
	editorComponent->setColour (CodeEditorComponent::backgroundColourId, newColour);
	editorComponent->setFont (newFont);
}

void CtrlrLuaMethodCodeEditor::findNextMatch(const String & search, bool bMatchCase)
{
	if (owner.getCurrentEditor() == nullptr)
	{
		return;
	}

	CodeDocument &doc = owner.getCurrentEditor()->getCodeDocument();
	int position = -1;

	if (bMatchCase)
	{
		position = document.getAllContent().indexOfIgnoreCase(lastFoundPosition + 1, search);
	}
	else
	{
		position = document.getAllContent().indexOf(lastFoundPosition + 1, search);
	}

	if (position >= 0)
	{
		lastFoundPosition = position;
		if (editorComponent)
		{
			editorComponent->selectRegion(CodeDocument::Position(document, lastFoundPosition), CodeDocument::Position(doc, lastFoundPosition + search.length()));
		}
	}
	else
	{
		lastFoundPosition = -1;
	}
}

void CtrlrLuaMethodCodeEditor::replaceNextMatch(const String &search, const String &replace, bool bMatchCase)
{
	if (owner.getCurrentEditor() == nullptr)
	{
		return;
	}

	CodeDocument &doc		= owner.getCurrentEditor()->getCodeDocument();
	findNextMatch(search, bMatchCase);
	if (lastFoundPosition >= 0)
	{
		doc.newTransaction();
		doc.deleteSection (lastFoundPosition, lastFoundPosition+search.length());
		doc.insertText (lastFoundPosition, replace);
	}
}

void CtrlrLuaMethodCodeEditor::replaceAllMatches(const String &search, const String &replace,bool bMatchCase)
{
	lastFoundPosition = -1;
	do
	{
		replaceNextMatch(search, replace, bMatchCase);
	}
	while (lastFoundPosition >= 0);
}

void CtrlrLuaMethodCodeEditor::findInOpened(const String &search)
{
	if (owner.getTabs() == nullptr)
		return;

	StringArray names = owner.getTabs()->getTabNames();

	owner.getMethodEditArea()->insertOutput("\n\nSearching for: \""+search+"\" in all opened methods (double click line to jump)\n", Colours::darkblue);

	for (int i=0; i<owner.getTabs()->getNumTabs(); i++)
	{
		CtrlrLuaMethodCodeEditor *codeEditor = dynamic_cast<CtrlrLuaMethodCodeEditor*>(owner.getTabs()->getTabContentComponent(i));

		if (codeEditor != nullptr )
		{
			CodeDocument &doc	= codeEditor->getCodeDocument() ;

			Array<Range<int> > results = searchForMatchesInDocument (doc, search);

			for (int j=0; j<results.size(); j++)
			{
				reportFoundMatch (doc, names[i], results[j]);
			}
		}
	}

	owner.getMethodEditArea()->getLowerTabs()->setCurrentTabIndex(0,true);
}

void CtrlrLuaMethodCodeEditor::findInAll(const String &search)
{
	owner.getMethodEditArea()->insertOutput("\n\nSearching for: \""+search+"\" in all methods (double click line to jump)\n", Colours::darkblue);
	StringArray names;

	for (int i=0; i<owner.getMethodManager().getNumMethods(); i++)
	{
		CtrlrLuaMethod *m = owner.getMethodManager().getMethodByIndex (i);

		if (m)
		{
			names.add (m->getName());

			if (m->getCodeEditor())
			{
				/* it has an editor so it's open */
				CodeDocument &doc		= m->getCodeEditor()->getCodeDocument();

				Array<Range<int> > results = searchForMatchesInDocument (doc, search);

				for (int j=0; j<results.size(); j++)
				{
					reportFoundMatch (doc, names[i], results[j]);
				}
			}
		}
	}

	owner.getMethodEditArea()->getLowerTabs()->setCurrentTabIndex(0,true);
}

const Array<Range<int> > CtrlrLuaMethodCodeEditor::searchForMatchesInDocument(CodeDocument &doc, const String &search)
{
	Array<Range<int> > results;
	int position			= -1;
	lastFoundPosition		= -1;
	do
	{
		String documentContent = doc.getAllContent();
		if (documentContent.isNotEmpty())
		{
			if (editorComponent->isCaseSensitiveSearch())
			{
				position = documentContent.indexOfIgnoreCase (lastFoundPosition+1, search);
			}
			else
			{
				position = documentContent.indexOf (lastFoundPosition+1, search);
			}
		}


		if (position >= 0)
		{
			lastFoundPosition		= position;
			results.add (Range<int> (lastFoundPosition, lastFoundPosition+search.length()));
		}
		else
		{
			lastFoundPosition = -1;
		}
	}
	while (lastFoundPosition >= 0);

	return (results);
}

void CtrlrLuaMethodCodeEditor::reportFoundMatch (CodeDocument &doc, const String &methodName, const Range<int> range)
{
	CodeDocument::Position pos (doc, range.getStart());
	AttributedString as;
	as.append ("Method: ", Colours::black);
	as.append (methodName, Colours::blue);

	as.append ("\tline: ", Colours::black);
	as.append (String(pos.getLineNumber()+1), Colours::darkgreen);

	as.append ("\tstart: ", Colours::black);
	as.append (String(range.getStart()), Colours::darkgreen);

	as.append ("\tend: ", Colours::black);
	as.append (String(range.getEnd()), Colours::darkgreen);

	owner.getMethodEditArea()->insertOutput (as);
}

void CtrlrLuaMethodCodeEditor::gotoLine(int position, const bool selectLine)
{
	editorComponent->scrollToLine(position-3);
	editorComponent->moveCaretTo(CodeDocument::Position(document, position - 1, 0), false);
	if (selectLine)
    {
        editorComponent->selectRegion (CodeDocument::Position (document, position - 1, 0), CodeDocument::Position (document, position - 1, 1024));
    }
	//editorComponent->selectRegion(CodeDocument::Position(document, position - 1, 0), CodeDocument::Position(document, position - 1, 1));
	editorComponent->grabKeyboardFocus();
	editorComponent->hideGoTOPanel();
}

CtrlrLuaMethodEditor &CtrlrLuaMethodCodeEditor::getOwner()
{
    return  (owner);
}

//==============================================================================
class GenericCodeEditorComponent::GoToPanel  : public Component,
	private TextEditor::Listener,
	private ButtonListener
{
public:
	GoToPanel() : goToButton("", 0.0, Colours::white)
	{
		editor.setColour (CaretComponent::caretColourId, Colours::black);
		editor.setInputRestrictions(5, ("1234567890"));
		editor.addListener (this);
		addAndMakeVisible (editor);
		goToButton.addListener(this);
		addAndMakeVisible (goToButton);

		label.setText ("Go To:", dontSendNotification);
		label.setColour (Label::textColourId, Colours::white);
		label.attachToComponent (&editor, true);

		setWantsKeyboardFocus (false);
		setFocusContainer (true);
	}

	void paint (Graphics& g) override
	{
		Path outline;
		outline.addRoundedRectangle (1.0f, 1.0f, getWidth() - 2.0f, getHeight() - 2.0f, 8.0f);

		g.setColour (Colours::black.withAlpha (0.6f));
		g.fillPath (outline);
		g.setColour (Colours::white.withAlpha (0.8f));
		g.strokePath (outline, PathStrokeType (1.0f));
	}

	void resized() override
	{
		int y = 5;
		editor.setBounds (45, y, getWidth() - 90, 24);
		goToButton.setBounds(editor.getRight() + 5, y+1, 30, 24);
	}
	void buttonClicked (Button* button) override
	{
		GenericCodeEditorComponent* ed = getOwner();
		if (ed)
		{
			if (button == &goToButton)
			{
				ed->gotoLine(editor.getText().getIntValue());
			}
		}
	}

	void textEditorTextChanged (TextEditor&) override	{}

	void textEditorFocusLost (TextEditor&) override {}

	void textEditorReturnKeyPressed (TextEditor& textEditor) override
	{
		GenericCodeEditorComponent* ed = getOwner();
		if (ed)
		{
			ed->gotoLine(editor.getText().getIntValue());
		}
	}

	void textEditorEscapeKeyPressed (TextEditor&) override
	{
		if (GenericCodeEditorComponent* ed = getOwner())
			ed->hideGoTOPanel();
	}

	GenericCodeEditorComponent* getOwner() const
	{
		return findParentComponentOfClass <GenericCodeEditorComponent>();
	}

	TextEditor editor;
	Label label;
	ArrowButton goToButton;
};

//==============================================================================
class GenericCodeEditorComponent::FindPanel  : public Component,
	private TextEditor::Listener,
	private ButtonListener,
	private ComboBoxListener
{
public:
	FindPanel()
		: caseButton ("Match Case"),
		findPrev ("<", "Search Previous"),
		findNext (">", "Search Next"),
		searchButton("", 0.0, Colours::white)
	{
		editor.setColour (CaretComponent::caretColourId, Colours::black);
		editor.addListener (this);
		addAndMakeVisible (editor);
		searchButton.addListener(this);
		addAndMakeVisible (searchButton);

		label.setText ("Find:", dontSendNotification);
		label.setColour (Label::textColourId, Colours::white);
		label.attachToComponent (&editor, true);

		searchInComboBox.setEditableText (false);
		searchInComboBox.setJustificationType (Justification::centredLeft);
		searchInComboBox.addItem (TRANS("Editor"), 1);
		searchInComboBox.addItem (TRANS("Output"), 2);
		searchInComboBox.addItem (TRANS("Methods"), 3);
		searchInComboBox.setSelectedItemIndex(0, dontSendNotification);
		searchInComboBox.addListener(this);
		searchInComboBox.setEnabled(false);
		addAndMakeVisible(searchInComboBox);

		addAndMakeVisible (caseButton);
		caseButton.setColour (ToggleButton::textColourId, Colours::white);
		caseButton.setToggleState (false, dontSendNotification);
		caseButton.addListener (this);

		lookInComboBox.setEditableText (false);
		lookInComboBox.setJustificationType (Justification::centredLeft);
		lookInComboBox.addItem (TRANS("Current"), 1);
		lookInComboBox.addItem (TRANS("All Open"), 2);
		lookInComboBox.addItem (TRANS("All"), 3);
		lookInComboBox.setSelectedItemIndex(0, dontSendNotification);
		lookInComboBox.addListener(this);
		addAndMakeVisible(lookInComboBox);

		findPrev.setConnectedEdges (Button::ConnectedOnRight);
		findPrev.addListener(this);
		findNext.setConnectedEdges (Button::ConnectedOnLeft);
		findNext.addListener(this);
		addAndMakeVisible (findPrev);
		addAndMakeVisible (findNext);

		setWantsKeyboardFocus (false);
		setFocusContainer (true);
		findPrev.setWantsKeyboardFocus (true);
		findNext.setWantsKeyboardFocus (true);
	}

	~FindPanel()
	{
		replaceEditor = nullptr;
		replaceLabel = nullptr;
		replaceButton = nullptr;
		replaceAllButton = nullptr;
	}

	void applyCurrentSetting()
	{
		if(GenericCodeEditorComponent* ed = getOwner())
		{
			caseButton.setToggleState(ed->getCtrlrLuaMethodCodeEditor().getCtrlrLuaMethodEditor().caseCansitive, dontSendNotification);
			lookInComboBox.setText(ed->getCtrlrLuaMethodCodeEditor().getCtrlrLuaMethodEditor().lookInString, dontSendNotification);
			searchInComboBox.setText(ed->getCtrlrLuaMethodCodeEditor().getCtrlrLuaMethodEditor().searchInString, dontSendNotification);
			editor.setText(ed->getCtrlrLuaMethodCodeEditor().getCtrlrLuaMethodEditor().currentSearchString, true);
		}
	}

	void setSearchText(const String& s)
	{
		editor.setText(s);
	}

	void addReplaceComponents()
	{
		replaceEditor = new TextEditor();
		replaceEditor->setColour (CaretComponent::caretColourId, Colours::black);
		addAndMakeVisible (*replaceEditor);

		replaceLabel = new Label();
		replaceLabel->setText ("Replace:", dontSendNotification);
		replaceLabel->setFont(Font (13.00f, Font::plain));
		replaceLabel->setColour (Label::textColourId, Colours::white);
		replaceLabel->attachToComponent (replaceEditor, true);

		replaceButton = new TextButton(">", "Replace Next");
		replaceButton->addListener(this);
		addAndMakeVisible (*replaceButton);

		replaceAllButton = new TextButton("A", "Replace all in current");
		replaceAllButton->addListener(this);
		addAndMakeVisible (*replaceAllButton);

		replaceButton->setConnectedEdges (Button::ConnectedOnRight);
		replaceAllButton->setConnectedEdges (Button::ConnectedOnLeft);

		replaceEditor->addListener (this);
		resized();
	}

	void paint (Graphics& g) override
	{
		Path outline;
		outline.addRoundedRectangle (1.0f, 1.0f, getWidth() - 2.0f, getHeight() - 2.0f, 8.0f);

		g.setColour (Colours::black.withAlpha (0.6f));
		g.fillPath (outline);
		g.setColour (Colours::white.withAlpha (0.8f));
		g.strokePath (outline, PathStrokeType (1.0f));
	}

	void resized() override
	{
		int y = 5;
		editor.setBounds (45, y, getWidth() - 90, 24);
		searchButton.setBounds(editor.getRight() + 5, y+1, 30, 24);
		y += 30;
		if (replaceEditor != nullptr)
		{
			replaceEditor->setBounds (45, y, getWidth() - 90, 24);
			replaceButton->setBounds(replaceEditor->getRight(), y, 20, 24);
			replaceAllButton->setBounds(replaceButton->getRight(), y, 20, 24);
			y += 30;
		}
		caseButton.setBounds (0, y, 75, 22);
		searchInComboBox.setBounds(caseButton.getRight(), y, 70, 24);
		lookInComboBox.setBounds(searchInComboBox.getRight() + 5, y, 70, 24);
		findPrev.setBounds (lookInComboBox.getRight(), y, 15, 24);
		findNext.setBounds (findPrev.getRight(), y, 15, 24);
	}

	void comboBoxChanged(ComboBox* combo) override
	{
		if (combo == &searchInComboBox)
		{
			switch (searchInComboBox.getSelectedItemIndex())
			{
			case 0:
				lookInComboBox.setEnabled(true);
				if (replaceEditor != nullptr)
				{
					replaceEditor->setEnabled(true);
					replaceLabel->setEnabled(true);
					replaceButton->setEnabled(true);
					replaceAllButton->setEnabled(true);
				}
				break;
			default:
				lookInComboBox.setEnabled(false);
				if (replaceEditor != nullptr)
				{
					replaceEditor->setEnabled(false);
					replaceLabel->setEnabled(false);
					replaceButton->setEnabled(false);
					replaceAllButton->setEnabled(false);
				}
				break;
			}
			if(GenericCodeEditorComponent* ed = getOwner())
				ed->getCtrlrLuaMethodCodeEditor().getCtrlrLuaMethodEditor().searchInString=
				searchInComboBox.getText();
		}
		else if (combo == &lookInComboBox)
		{
			if(GenericCodeEditorComponent* ed = getOwner())
				ed->getCtrlrLuaMethodCodeEditor().getCtrlrLuaMethodEditor().lookInString =
				lookInComboBox.getText();
		}
	}

	void buttonClicked (Button* button) override
	{
		GenericCodeEditorComponent* ed = getOwner();
		if (ed)
		{
			if (button == &findNext )
			{
				ed->findNext (true, true);
			}
			else if (button == &findPrev )
			{
				ed->findNext (false, false);
			}
			else if (button == replaceButton)
			{
				ed->replaceNextMatch (editor.getText(), replaceEditor->getText(), caseButton.getToggleState());
			}
			else if (button == replaceAllButton)
			{
				ed->replaceAllMatches(editor.getText(), replaceEditor->getText(), caseButton.getToggleState());
			}
			else if (button == &searchButton)
			{
				lookInSearch();
			}
			else if (button == &caseButton)
			{
				ed->getCtrlrLuaMethodCodeEditor().getCtrlrLuaMethodEditor().caseCansitive =
					caseButton.getToggleState();
			}
		}
	}

	void textEditorTextChanged (TextEditor& te) override
	{
		switch(searchInComboBox.getSelectedItemIndex())
		{
		case 0:
			if (GenericCodeEditorComponent* ed = getOwner())
			{
				ed->findNext (true, false);
				ed->getCtrlrLuaMethodCodeEditor().getCtrlrLuaMethodEditor().currentSearchString = editor.getText();
			}
			break;
		default:
			break;
		}
	}

	void textEditorFocusLost (TextEditor&) override {}

	void textEditorReturnKeyPressed (TextEditor& textEditor) override
	{
		if (&textEditor == &editor)
		{
			lookInSearch();
		}
		else if (&textEditor == replaceEditor)
		{
			if (GenericCodeEditorComponent* ed = getOwner())
			{
				ed->replaceNextMatch(editor.getText(), replaceEditor->getText(), caseButton.getToggleState());
			}
		}
	}

	void lookInSearch()
	{
		if (GenericCodeEditorComponent* ed = getOwner())
		{
			switch(lookInComboBox.getSelectedItemIndex())
			{
			case 0: // code editor current
				switch(searchInComboBox.getSelectedItemIndex())
				{
				case 0: // code editor
					ed->findNext (true, true);
					break;
				case 1: // output window
					break;
				case 2: // Lua method tree
					break;
				default:
					jassertfalse;
				}
				break;
			case 1: // code editor all open
				ed->findInOpened(editor.getText());
				break;
			case 2: // All methods
				ed->findInAll(editor.getText());
				break;
			default:
				jassertfalse;
			}
		}
	}

	void textEditorEscapeKeyPressed (TextEditor&) override
	{
		if (GenericCodeEditorComponent* ed = getOwner())
			ed->hideFindPanel();
	}

	GenericCodeEditorComponent* getOwner() const
	{
		return findParentComponentOfClass <GenericCodeEditorComponent>();
	}

	TextEditor editor;
	Label label;
	ToggleButton caseButton;
	TextButton findPrev, findNext;
	ArrowButton searchButton;
	ComboBox    lookInComboBox, searchInComboBox;
	// For replace
	ScopedPointer<TextEditor> replaceEditor;
	ScopedPointer<Label> replaceLabel;
	ScopedPointer<TextButton> replaceButton, replaceAllButton;
};

//==============================================================================
GenericCodeEditorComponent::GenericCodeEditorComponent (CtrlrLuaMethodCodeEditor &_owner, CodeDocument &codeDocument,
	CodeTokeniser* tokeniser)	: CodeEditorComponent (codeDocument, tokeniser), owner(_owner), bSensitive(false),
	lookUpString("")
{
    setColour (CodeEditorComponent::lineNumberTextId, Colours::black);
}

GenericCodeEditorComponent::~GenericCodeEditorComponent()
{
}

void GenericCodeEditorComponent::resized()
{
	CodeEditorComponent::resized();

	if (findPanel != nullptr)
	{
		findPanel->setSize (jmin (260, getWidth() - 32), 100);
		findPanel->setTopRightPosition (getWidth() - 6, 4);
	}
	if (goToPanel != nullptr)
	{
		goToPanel->setSize (jmin (160, getWidth() - 32), 40);
		goToPanel->setTopRightPosition (getWidth() - 6, getHeight() -40);
	}
}

bool GenericCodeEditorComponent::isFindActive()
{
	return (findPanel == nullptr);
}

void GenericCodeEditorComponent::showFindPanel(bool bForReplace)
{
	if (findPanel == nullptr)
	{
		findPanel = new FindPanel();
		addAndMakeVisible (findPanel);
		resized();
	}

	if (findPanel != nullptr)
	{
		findPanel->setSearchText(getTextInRange (getHighlightedRegion()));
		findPanel->applyCurrentSetting();
		if (bForReplace)
			findPanel->addReplaceComponents();
		findPanel->editor.grabKeyboardFocus();
		findPanel->editor.selectAll();
	}
	owner.getCtrlrLuaMethodEditor().findDialogActive = true;
}

void GenericCodeEditorComponent::hideFindPanel()
{
	owner.getCtrlrLuaMethodEditor().findDialogActive = false;
	findPanel = nullptr;
}

void GenericCodeEditorComponent::showGoTOPanel()
{
	if (goToPanel == nullptr)
	{
		goToPanel = new GoToPanel();
		addAndMakeVisible (goToPanel);
		resized();
	}
	if (goToPanel != nullptr)
	{
		goToPanel->editor.grabKeyboardFocus();
		goToPanel->editor.selectAll();
	}
}

void GenericCodeEditorComponent::hideGoTOPanel()
{
	goToPanel = nullptr;
}

void GenericCodeEditorComponent::findSelection(bool forward)
{
	const String selected = getSearchString();

	if (selected.isNotEmpty())
	{
		if (forward)
		{
			findNext (true, true);
		}
		else
		{
			findNext (false, false);
		}
	}
}

void GenericCodeEditorComponent::findNext (bool forwards, bool skipCurrentSelection)
{
	const Range<int> highlight (getHighlightedRegion());
	const CodeDocument::Position startPos (getDocument(), skipCurrentSelection ? highlight.getEnd()
		: highlight.getStart());
	int lineNum = startPos.getLineNumber();
	int linePos = startPos.getIndexInLine();

	const int totalLines = getDocument().getNumLines();
	const String searchText (getSearchString());
	const bool caseSensitive = isCaseSensitiveSearch();

	for (int linesToSearch = totalLines; --linesToSearch >= 0;)
	{
		String line (getDocument().getLine (lineNum));
		int index;

		if (forwards)
		{
			index = caseSensitive ? line.indexOf (linePos, searchText)
				: line.indexOfIgnoreCase (linePos, searchText);
		}
		else
		{
			if (linePos >= 0)
				line = line.substring (0, linePos);

			index = caseSensitive ? line.lastIndexOf (searchText)
				: line.lastIndexOfIgnoreCase (searchText);
		}

		if (index >= 0)
		{
			const CodeDocument::Position p (getDocument(), lineNum, index);
			selectRegion (p, p.movedBy (searchText.length()));
			break;
		}

		if (forwards)
		{
			linePos = 0;
			lineNum = (lineNum + 1) % totalLines;
		}
		else
		{
			if (--lineNum < 0)
				lineNum = totalLines - 1;

			linePos = -1;
		}
	}
}

void GenericCodeEditorComponent::handleEscapeKey()
{
	CodeEditorComponent::handleEscapeKey();
	hideFindPanel();
}

String GenericCodeEditorComponent::getSearchString()
{
	String searchString = "";
	if (findPanel != nullptr)
		searchString = findPanel->editor.getText();
	else
		searchString = getTextInRange (getHighlightedRegion());
	return searchString;
}

bool GenericCodeEditorComponent::isCaseSensitiveSearch()
{
	if (findPanel != nullptr)
		bSensitive = findPanel->caseButton.getToggleState();
	return bSensitive;
}

void GenericCodeEditorComponent::gotoLine(int position)
{
	owner.gotoLine(position);
}

void GenericCodeEditorComponent::replaceAllMatches(const String &search, const String &replace, bool bMatchCase)
{
	owner.replaceAllMatches(search,replace,bMatchCase);
}
void GenericCodeEditorComponent::replaceNextMatch(const String &search, const String &replace, bool bMatchCase)
{
	owner.replaceNextMatch(search, replace,bMatchCase);
}
void GenericCodeEditorComponent::findInAll(const String &search)
{
	owner.findInAll(search);
}
void GenericCodeEditorComponent::findInOpened(const String &search)
{
	owner.findInOpened(search);
}

CtrlrLuaDebugger &GenericCodeEditorComponent::getDebugger()
{
    return (owner.getOwner().getOwner().getCtrlrLuaManager().getDebugger());
}

void GenericCodeEditorComponent::markedLinesChanged(int lineNumber, bool isNowSelected)
{
    getDebugger().setBreakpoint (lineNumber, owner.getMethod() ? owner.getMethod()->getName() : "ctrlr", isNowSelected);
}
