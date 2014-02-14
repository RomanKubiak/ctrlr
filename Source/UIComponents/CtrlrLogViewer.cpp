#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrLogViewer.h"

template<class Iterator> static int parseMessageType (Iterator& source)
{
	source.skip();

	String level;
	CtrlrLog::LogLevel ret = CtrlrLog::Info;

	for (int i=0; i<8; i++)
	{
		level << source.nextChar();
	}

	if (source.peekNextChar() == ']')
	{
		ret = CtrlrLog::stringToLevel(level);
	}

	source.skipToEndOfLine();
	return (ret);
}


CtrlrLogViewerTokeniser::CtrlrLogViewerTokeniser() {}
CtrlrLogViewerTokeniser::~CtrlrLogViewerTokeniser() {}

int CtrlrLogViewerTokeniser::readNextToken (CodeDocument::Iterator& source)
{
	int result = CtrlrLog::Info;
	source.skipWhitespace();

	const juce_wchar firstChar = source.peekNextChar();

	switch (firstChar)
	{
		case '[':
			result = parseMessageType(source);
			break;

		default:
			source.skip();
			break;
	}

	return (result);
}

CodeEditorComponent::ColourScheme CtrlrLogViewerTokeniser::getDefaultColourScheme()
{
    CodeEditorComponent::ColourScheme cs;

    for (int i=0; i<CtrlrLog::kLogLevels; i++)
	{
        cs.set (CtrlrLog::levelToString((CtrlrLog::LogLevel)i), CtrlrLog::getColourForLevel((CtrlrLog::LogLevel)i));
	}

    return cs;
}

CtrlrLogViewer::CtrlrLogViewer (CtrlrManager &_owner)
    : owner(_owner),
      logEditor (0)
{
    addAndMakeVisible (logEditor = new CodeEditorComponent (logDocument, &logViewerTokeniser));
    logEditor->setName (L"logEditor");
	logEditor->setFont (Font (owner.getFontManager().getDefaultMonoFontName(), 14, Font::plain));
	logEditor->setWantsKeyboardFocus(false);
	logEditor->setColour (CodeEditorComponent::backgroundColourId, Colour(0xffffffff));
	owner.getCtrlrLog().addListener (this);
    setSize (600, 400);
}

CtrlrLogViewer::~CtrlrLogViewer()
{
	owner.getCtrlrLog().removeListener (this);
    deleteAndZero (logEditor);
}

void CtrlrLogViewer::paint (Graphics& g)
{
}

void CtrlrLogViewer::resized()
{
    logEditor->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
}

void CtrlrLogViewer::messageLogged (CtrlrLog::CtrlrLogMessage message)
{
	if (container->getParentComponent()->isVisible())
	{
		if  (message.level == CtrlrLog::MidiIn || message.level == CtrlrLog::MidiOut || message.level == CtrlrLog::Lua)
			return;

		logEditor->insertTextAtCaret (CtrlrLog::formatMessage(message) + "\n");
	}
}

StringArray CtrlrLogViewer::getMenuBarNames()
{
	const char* const names[] = { "File", "View", nullptr };
	return StringArray (names);
}

PopupMenu CtrlrLogViewer::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
	PopupMenu menu;
	if (topLevelMenuIndex == 0)
	{
		menu.addItem (1, "Close");
	}
	else if (topLevelMenuIndex == 1)
	{
		menu.addItem (2, "Clear window");
	}
	return (menu);
}

void CtrlrLogViewer::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	if (menuItemID == 2)
	{
		logDocument.replaceAllContent(String::empty);
	}
}
