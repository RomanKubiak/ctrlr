#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrUtilities.h"
#include "CtrlrProcessor.h"
#include "CtrlrMIDIMon.h"

CtrlrMIDIMon::CtrlrMIDIMon (CtrlrManager &_owner)
    : owner(_owner), logIn(false), logOut(false),
      resizer (0),
      outMon (0),
      inMon (0)
{
    addAndMakeVisible (resizer = new StretchableLayoutResizerBar (&layoutManager, 1, false));

    addAndMakeVisible (outMon = new CodeEditorComponent (outputDocument, 0));
    outMon->setName (L"outMon");

    addAndMakeVisible (inMon = new CodeEditorComponent (inputDocument, 0));
    inMon->setName (L"inMon");

	layoutManager.setItemLayout (0, -0.001, -1.0, -0.49);
 	layoutManager.setItemLayout (1, -0.001, -0.01, -0.01);
 	layoutManager.setItemLayout (2, -0.001, -1.0, -0.49);
	
	owner.getCtrlrLog().addListener (this);

	inMon->setFont ( Font(owner.getFontManager().getDefaultMonoFontName(), 12, Font::plain) );
	inMon->setColour (CodeEditorComponent::backgroundColourId, Colour(0xffb3ffac));
	outMon->setFont ( Font(owner.getFontManager().getDefaultMonoFontName(), 12, Font::plain) );
	outMon->setColour (CodeEditorComponent::backgroundColourId, Colour(0xffffacac));

    setSize (500, 400);
}

CtrlrMIDIMon::~CtrlrMIDIMon()
{
	owner.getCtrlrLog().removeListener (this);
    deleteAndZero (resizer);
    deleteAndZero (outMon);
    deleteAndZero (inMon);
}

void CtrlrMIDIMon::paint (Graphics& g)
{
}

void CtrlrMIDIMon::resized()
{
    resizer->setBounds (0, proportionOfHeight (0.4900f), getWidth() - 0, proportionOfHeight (0.0100f));
    outMon->setBounds (0, 0, getWidth() - 0, proportionOfHeight (0.4900f));
    inMon->setBounds (0, proportionOfHeight (0.5000f), getWidth() - 0, proportionOfHeight (0.4900f));
	Component* comps[] = { outMon, resizer, inMon  };
 	layoutManager.layOutComponents (comps, 3, 0, 0, getWidth(), getHeight(), true, true);
}

void CtrlrMIDIMon::messageLogged (CtrlrLog::CtrlrLogMessage _message)
{
	if (!isVisible())
		return;

	CtrlrLog::CtrlrLogMessage message = _message;

	if (message.level == CtrlrLog::MidiIn)
	{
		if (inputDocument.getAllContent().length() > (int)owner.getProperty(Ids::ctrlrMidiMonInputBufferSize))
			inputDocument.replaceAllContent(String::empty);

		inMon->insertTextAtCaret (CtrlrLog::formatMessage(message, false, true) + "\n");
	}

	if (message.level == CtrlrLog::MidiOut)
	{
		if (outputDocument.getAllContent().length() > (int)owner.getProperty(Ids::ctrlrMidiMonOutputBufferSize))
			outputDocument.replaceAllContent(String::empty);

		outMon->insertTextAtCaret (CtrlrLog::formatMessage(message, false, true) + "\n");
	}
}

StringArray CtrlrMIDIMon::getMenuBarNames()
{
	const char* const names[] = { "File", "View", "Filter", nullptr };
	return StringArray (names);
}

PopupMenu CtrlrMIDIMon::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
	PopupMenu menu;

	int opts = (int)owner.getProperty (Ids::ctrlrLogOptions);

	if (topLevelMenuIndex == 0)
	{
		menu.addItem (1, "Close");
	}
	else if (topLevelMenuIndex == 1)
	{
		menu.addItem (12, "Show name", true, getBitOption(opts,midiLogName));
		menu.addItem (14, "Show channel", true, getBitOption(opts,midiLogChannel));
		menu.addItem (18, "Show number", true, getBitOption(opts,midiLogNumber));
		menu.addItem (26, "Show value", true, getBitOption(opts,midiLogValue));
		menu.addItem (42, "Show RAW data", true, getBitOption(opts,midiLogRawData));
		menu.addItem (74, "Show timestamp", true, getBitOption(opts,midiLogTimestamp));
		menu.addItem (138, "RAW data in decimal", true, getBitOption(opts,midiLogRawDecimal));
		menu.addItem (1034, "Show device name", true, getBitOption(opts,midiLogDevice));
		menu.addItem  (4096+10, "Show RAW data size", true, getBitOption(opts,midiLogDataSize));
		menu.addSeparator();
		menu.addColouredItem (266, "Monitor input", Colour(0xff21c630), true, getBitOption(opts,midiLogInput));
		menu.addColouredItem (522, "Monitor output", Colour(0xffc62121), true, getBitOption(opts,midiLogOutput));
	}
	else if (topLevelMenuIndex == 2)
	{
		menu.addItem (8192, "Create new");
		menu.addSectionHeader ("Active filters");
	}

	return (menu);
}

void CtrlrMIDIMon::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	if (topLevelMenuIndex == 1)
	{
		int opts = (int)owner.getProperty (Ids::ctrlrLogOptions);

		setBitOption (opts, menuItemID-10, !getBitOption(opts, menuItemID-10));
		owner.setProperty (Ids::ctrlrLogOptions, opts);
	}
}