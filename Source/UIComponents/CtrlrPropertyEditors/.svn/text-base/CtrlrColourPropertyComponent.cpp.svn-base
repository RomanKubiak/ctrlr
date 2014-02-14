#include "stdafx.h"
#include "CtrlrColourPropertyComponent.h"

CtrlrColourEditorComponent::CtrlrColourEditorComponent(ChangeListener *defaultListener) : canResetToDefault (true)
{
	addAndMakeVisible (&colourTextInput);
	colourTextInput.setJustificationType (Justification::centred);
	colourTextInput.setFont (colourTextInput.getFont().withStyle(Font::bold));
	colourTextInput.setEditable (true, false, false);
	colourTextInput.setAlwaysOnTop (true);
	colourTextInput.addListener (this);
	colourTextInput.addMouseListener (this, true);

	if (defaultListener)
		addChangeListener (defaultListener);
}

void CtrlrColourEditorComponent::updateLabel()
{
	colourTextInput.setColour (Label::backgroundColourId, getColour());
	colourTextInput.setColour (Label::textColourId, getColour().contrasting());
	colourTextInput.setText (getColour().toDisplayString (true), dontSendNotification);
}

void CtrlrColourEditorComponent::labelTextChanged (Label *labelThatHasChanged)
{
	colour = Colour::fromString(labelThatHasChanged->getText());
	sendChangeMessage();
}

void CtrlrColourEditorComponent::resized()
{
	colourTextInput.setBounds (0, 0, getWidth(), getHeight());
}

void CtrlrColourEditorComponent::setColour (const Colour& newColour, const bool sendChangeMessageNow)
{
	colour = newColour;

	updateLabel();

	if (sendChangeMessageNow)
		sendChangeMessage();
}

void CtrlrColourEditorComponent::mouseDown (const MouseEvent &e)
{
	if (e.mods.isPopupMenu())
	{
		DialogWindow::LaunchOptions o;

    	CtrlrColourSelectorComp *editor 		= new CtrlrColourSelectorComp (this, canResetToDefault);
		o.dialogTitle					= "Colour editor";
		o.content.set (editor, true);
		o.resizable						= true;
		o.useNativeTitleBar				= true;
		o.dialogBackgroundColour 		= Colours::whitesmoke;
		o.escapeKeyTriggersCloseButton	= true;
		o.componentToCentreAround		= this;
		o.launchAsync();
	}
}

void CtrlrColourEditorComponent::changeListenerCallback (ChangeBroadcaster* source)
{
	const ColourSelector* const cs = (const ColourSelector*) source;

	if (cs != 0)
	{
		if (cs->getCurrentColour() != getColour())
            setColour (cs->getCurrentColour(), true);
	}
}

/**
 *
 */
CtrlrColourPropertyComponent::CtrlrColourPropertyComponent (const Value &_valueToControl) : valueToControl(_valueToControl)
{
	addAndMakeVisible (&cs);
	cs.addChangeListener (this);
}

CtrlrColourPropertyComponent::~CtrlrColourPropertyComponent()
{
}

void CtrlrColourPropertyComponent::refresh()
{
	cs.setColour (Colour::fromString (valueToControl.toString()));
}

void CtrlrColourPropertyComponent::changeListenerCallback (ChangeBroadcaster* source)
{
	valueToControl = cs.getColour().toString();
}

void CtrlrColourPropertyComponent::resized()
{
	cs.setBounds (0, 0, getWidth(), getHeight());
}

/** A read-only component **/

CtrlrReadOnlyProperty::CtrlrReadOnlyProperty(const Identifier &_propertyName,
															const ValueTree &_propertyElement,
															const ValueTree &identifier,
															CtrlrPanel *panel,
															StringArray *possibleChoices,
															StringArray *possibleValues) : propertyName(_propertyName), propertyElement(_propertyElement)
{
	addAndMakeVisible (&value);
	value.setColour(Label::backgroundColourId, Colours::white.withAlpha(0.5f));
	value.setColour(Label::outlineColourId, Colours::black.withAlpha(0.5f));
}

CtrlrReadOnlyProperty::~CtrlrReadOnlyProperty()
{
}

void CtrlrReadOnlyProperty::refresh()
{
	value.setText (propertyElement.getPropertyAsValue(propertyName, 0).toString(), dontSendNotification);
}

void CtrlrReadOnlyProperty::resized()
{
	value.setBounds (0, 2, getWidth(), getHeight()-4);
}
