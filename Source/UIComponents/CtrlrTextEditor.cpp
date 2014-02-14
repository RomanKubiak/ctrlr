#include "stdafx.h"
#include "CtrlrTextEditor.h"
#include "CtrlrLog.h"

CtrlrTextEditor::CtrlrTextEditor(const String &componentName, juce_wchar passwordCharacter)
	: TextEditor (componentName, passwordCharacter)
{
}

CtrlrTextEditor::~CtrlrTextEditor()
{
}

void CtrlrTextEditor::setAttributedText (const AttributedString &text)
{
	clear();

	for (int i=0; i<text.getNumAttributes(); i++)
	{
		const AttributedString::Attribute *a = text.getAttribute(i);

		if (a->getFont())
			setFont (*a->getFont());

		if (a->getColour())
			setColour (TextEditor::textColourId, *a->getColour());

		insertTextAtCaret (text.getText().substring (a->range.getStart(), a->range.getEnd()));
	}
}

void CtrlrTextEditor::insertText (const String &text, const Font &font, const Colour &colour)
{
	Colour previousColour	= findColour(TextEditor::textColourId);
	Font previousFont		= getFont();
	
	setFont (font);
	setColour (TextEditor::textColourId, colour);
	insertTextAtCaret (text);
	setFont(previousFont);
	setColour(TextEditor::textColourId, previousColour);
}

void CtrlrTextEditor::insertAttributedText (const AttributedString &text)
{
	if (!getText().endsWithChar('\n'))
	{
		setCaretPosition (getText().length());
		insertTextAtCaret ("\n");
	}

	Range<int> lastRange, currentRange;

	currentRange = text.getAttribute(0)->range;

	for (int i=0; i<text.getNumAttributes(); i++)
	{
		const AttributedString::Attribute *a = text.getAttribute(i);
		
		if (currentRange != a->range)
		{			
			insertTextAtCaret (text.getText().substring (currentRange.getStart(), currentRange.getEnd()));
		}

		currentRange = a->range;

		if (a->getFont())
			setFont (*a->getFont());

		if (a->getColour())
			setColour (TextEditor::textColourId, *a->getColour());
	}

	insertTextAtCaret (text.getText().substring (currentRange.getStart(), currentRange.getEnd()));
}

const String CtrlrTextEditor::getLineAtPosition(const int index)
{
	const String allText	= getText();
	
	int indexOfStartingEol;

	for (indexOfStartingEol=index; indexOfStartingEol>=0; indexOfStartingEol--)
	{
		if (allText[indexOfStartingEol] == '\n')
			break;
	}
	
	const int indexOfEndingEol = (allText.indexOf (index,"\n") > 0) ? allText.indexOf (index,"\n") : allText.length();

	return (allText.substring(indexOfStartingEol, indexOfEndingEol));
}

CtrlrTextEditor *CtrlrTextEditor::readOnlyMultiline(const String &xmlSource, const Colour backgroundColour, const Colour outlineColour, const Colour shadowColour)
{
	CtrlrTextEditor *t = new CtrlrTextEditor();
	t->setColour (TextEditor::backgroundColourId, backgroundColour);
	t->setColour (TextEditor::shadowColourId, shadowColour);
	t->setColour (TextEditor::outlineColourId, outlineColour);
	t->setReadOnly (true);
	t->setMultiLine (true, true);
	t->setXmlSource (xmlSource);

	return (t);
}

void CtrlrTextEditor::setXmlSource (const String &xmlSource)
{
	ScopedPointer <XmlElement> xml (XmlDocument::parse(xmlSource));
	if (xml)
	{
		forEachXmlChildElement (*xml, el)
		{
			if (el->hasTagName ("font"))
			{
				Font font;
				font					= el->hasAttribute("bold") ? font.withStyle (Font::bold) : font;
				font					= el->hasAttribute("italic") ? font.withStyle (Font::italic) : font;
				font					= el->hasAttribute("underline") ? font.withStyle (Font::underlined) : font;
				
				font					= el->hasAttribute("height") ? font.withHeight (el->getDoubleAttribute("height")) : font;

				if (el->hasAttribute("name"))
				{
					if (el->getStringAttribute("name").startsWith(":"))
					{
						if (el->getStringAttribute("name") == ":Monospaced")						
							font.setTypefaceName (Font::getDefaultMonospacedFontName());
						if (el->getStringAttribute("name") == ":Sans")
							font.setTypefaceName (Font::getDefaultSansSerifFontName());
						if (el->getStringAttribute("name") == ":Serif")
							font.setTypefaceName (Font::getDefaultSerifFontName());
					}
					else
					{
						font.setTypefaceName (el->getStringAttribute("name"));
					}
				}

				const Colour fgColour	= Colour::fromString (el->hasAttribute("colour") ? el->getStringAttribute("colour") : "0xff000000");
				const Colour bgColour	= Colour::fromString (el->hasAttribute("background") ? el->getStringAttribute("background") : findColour (TextEditor::backgroundColourId).toString());

				setFont (font);
				setColour (TextEditor::textColourId, fgColour);
				setColour (TextEditor::backgroundColourId, bgColour);
				
				TextEditor::insertTextAtCaret (el->getAllSubText());
			}
			
			if (el->hasTagName("br"))
			{
				TextEditor::insertTextAtCaret ("\n");
			}
		}
	}
}