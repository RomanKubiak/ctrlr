#include "stdafx.h"
#include "CtrlrUtilities.h"
#include "../CtrlrComponentTypeManager.h"
#include "CtrlrMidiKeyboard.h"

CtrlrMidiKeyboard::CtrlrMidiKeyboard (CtrlrModulator &owner)
    : CtrlrComponent(owner),
      midiKeyboard (0)
{
    addAndMakeVisible (midiKeyboard = new MidiKeyboardComponent (keyboardState, MidiKeyboardComponent::horizontalKeyboard ));
    midiKeyboard->setName ("midiKeyboard");
	keyboardState.addListener (this);
	setProperty (Ids::uiMidiKeyboardOrientation, "horizontalKeyboard");
	setProperty (Ids::uiMidiKeyboardWhiteButtonColour, "0xffffffff");
	setProperty (Ids::uiMidiKeyboardBlackButtonColour, "0xff000000");
	setProperty (Ids::uiMidiKeyboardSeparatorLineColour, "0xff000000");
	setProperty (Ids::uiMidiKeyboardMouseOverColour, "0xffff0000");
	setProperty (Ids::uiMidiKeyboardMouseDownColour, "0xff0000ff");
	setProperty (Ids::uiMidiKeyboardTextLabelColour, "0xff000000");
	setProperty (Ids::uiMidiKeyboardButtonBackgroundColour, "0xff0f0f0f");
	setProperty (Ids::uiMidiKeyboardButtonArrowColour, "0xff000000");
	setProperty (Ids::uiMidiKeyboardLowestVisibleKey, 48);
	setProperty (Ids::uiMidiKeyboardBaseOctaveKeyPress, 0);
	setProperty (Ids::uiMidiKeyboardOctaveFroMiddleC, 3);

    setSize (256, 64);
	owner.getOwner().addPanelListener (this);
	midiKeyboard->setKeyPressBaseOctave( 5 );
	midiKeyboard->setOctaveForMiddleC( 4 );
}

CtrlrMidiKeyboard::~CtrlrMidiKeyboard()
{
	owner.getOwner().removePanelListener (this);
    deleteAndZero (midiKeyboard);
}

void CtrlrMidiKeyboard::paint (Graphics& g)
{
}

void CtrlrMidiKeyboard::resized()
{
	midiKeyboard->setBounds (getUsableRect());
}


const double CtrlrMidiKeyboard::getComponentValue()
{
	return (owner.getMidiMessage().getValue());
}

const int CtrlrMidiKeyboard::getComponentMidiValue()
{
	return (owner.getMidiMessage().getValue());
}

const double CtrlrMidiKeyboard::getComponentMaxValue()
{
	return (127);
}

void CtrlrMidiKeyboard::setComponentValue (const double newValue, const bool sendChangeMessage)
{
	// keyboardState.noteOn (owner.getMidiMessage().getChannel(), owner.getMidiMessage().getNumber(), (float)(127/newValue));
}

void CtrlrMidiKeyboard::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiMidiKeyboardOrientation)
	{
		midiKeyboard->setOrientation (CtrlrComponentTypeManager::orientationFromString(getProperty(property)));
	}
	else if (property == Ids::uiMidiKeyboardWhiteButtonColour)
	{
		midiKeyboard->setColour (MidiKeyboardComponent::whiteNoteColourId, VAR2COLOUR(getProperty(property)));
	}
	else if (property == Ids::uiMidiKeyboardBlackButtonColour)
	{
		midiKeyboard->setColour (MidiKeyboardComponent::blackNoteColourId, VAR2COLOUR(getProperty(property)));
	}
	else if (property == Ids::uiMidiKeyboardSeparatorLineColour)
	{
		midiKeyboard->setColour (MidiKeyboardComponent::keySeparatorLineColourId, VAR2COLOUR(getProperty(property)));
	}
	else if (property == Ids::uiMidiKeyboardMouseOverColour)
	{
		midiKeyboard->setColour (MidiKeyboardComponent::mouseOverKeyOverlayColourId, VAR2COLOUR(getProperty(property)));
	}
	else if (property == Ids::uiMidiKeyboardMouseDownColour)
	{
		midiKeyboard->setColour (MidiKeyboardComponent::keyDownOverlayColourId, VAR2COLOUR(getProperty(property)));
	}
	else if (property == Ids::uiMidiKeyboardTextLabelColour)
	{
		midiKeyboard->setColour (MidiKeyboardComponent::textLabelColourId, VAR2COLOUR(getProperty(property)));
	}
	else if (property == Ids::uiMidiKeyboardButtonBackgroundColour)
	{
		midiKeyboard->setColour (MidiKeyboardComponent::upDownButtonBackgroundColourId, VAR2COLOUR(getProperty(property)));
	}
	else if (property == Ids::uiMidiKeyboardButtonArrowColour)
	{
		midiKeyboard->setColour (MidiKeyboardComponent::upDownButtonArrowColourId, VAR2COLOUR(getProperty(property)));
	}
	else if (property == Ids::uiMidiKeyboardLowestVisibleKey)
	{
		midiKeyboard->setLowestVisibleKey((int)getProperty(property));
		//midiKeyboard->setKeyPressBaseOctave( (int)getProperty(property)/12 + 1 );
	}
	else if (property == Ids::uiMidiKeyboardBaseOctaveKeyPress)
	{
		midiKeyboard->setKeyPressBaseOctave (getProperty(property));
	}
	else if (property == Ids::uiMidiKeyboardOctaveFroMiddleC)
	{
		midiKeyboard->setOctaveForMiddleC (getProperty(property));
	}
	else
	{
		CtrlrComponent::valueTreePropertyChanged(treeWhosePropertyHasChanged, property);
	}

	if (restoreStateInProgress == false)
	{
		resized();
	}
}

void CtrlrMidiKeyboard::handleNoteOn (MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{
	owner.getMidiMessage().setMidiMessageType(NoteOn);
	owner.getMidiMessage().setNumber (midiNoteNumber);
	owner.getProcessor().setValueFromGUI ((int)(velocity*127));
}

void CtrlrMidiKeyboard::handleNoteOff (MidiKeyboardState* source, int midiChannel, int midiNoteNumber)
{
	owner.getMidiMessage().setMidiMessageType(NoteOff);
	owner.getMidiMessage().setNumber (midiNoteNumber);
	owner.getProcessor().setValueFromGUI (0);
}

void CtrlrMidiKeyboard::midiReceived(MidiMessage &message)
{
	keyboardState.processNextMidiEvent (message);
}
