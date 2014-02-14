#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrLuaMethodCodeEditor.h"
#include "CtrlrLuaMethodEditor.h"
#include "CtrlrPanel/CtrlrPanel.h"

CtrlrLuaMethodCodeEditor::CtrlrLuaMethodCodeEditor(CtrlrLuaMethodEditor &_owner, CtrlrLuaMethod *_method)
	:	editorComponent(nullptr), 
		owner(_owner), 
		method(_method)
{
	addAndMakeVisible (editorComponent	= new CodeEditorComponent (document, codeTokeniser = new CtrlrLuaCodeTokeniser()));

	editorComponent->grabKeyboardFocus();
	document.replaceAllContent(method->getCode());
	document.setSavePoint();

	document.addListener (this);
	editorComponent->addMouseListener (this, true);
	editorComponent->addKeyListener (this);

	if (method != nullptr)
		method->setCodeEditor (this);

	setFontAndColour (owner.getOwner().getOwner().getFontManager().getFontFromString (
																						owner.getComponentTree().getProperty (	Ids::luaMethodEditorFont, 
																						owner.getOwner().getOwner().getFontManager().getStringFromFont (Font(owner.getOwner().getOwner().getFontManager().getDefaultMonoFontName(), 14.0f, Font::plain))
																																)
																					)
																					,VAR2COLOUR(owner.getComponentTree().getProperty (Ids::luaMethodEditorBgColour, Colours::white.toString())));
}

CtrlrLuaMethodCodeEditor::~CtrlrLuaMethodCodeEditor()
{
	masterReference.clear();

	if (method)
		method->setCodeEditor (nullptr);

	document.removeListener (this);
	deleteAndZero (editorComponent);
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
	if (originatingComponent == editorComponent)
	{
		if (key.getModifiers().isCommandDown() && key.getKeyCode() == 83) // CTRL + S
		{
			saveDocument();
		}
		
		if (key.getKeyCode() == KeyPress::F7Key)
		{
			saveAndCompileDocument();
		}
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
	}

	documentChanged(true, false);
}

void CtrlrLuaMethodCodeEditor::saveAndCompileDocument()
{
	document.setSavePoint();

	if (method)
	{
		method->triggerSourceChangeFromEditor(true);
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
	editorComponent->setHighlightedRegion (Range<int>(start.getPosition(), end.getPosition()));
}

void CtrlrLuaMethodCodeEditor::setFontAndColour (const Font newFont, const Colour newColour)
{
	editorComponent->setColour (CodeEditorComponent::backgroundColourId, newColour);
	editorComponent->setFont (newFont);
}