#include "stdafx.h"
#include "CtrlrPropertyComponent.h"
#include "CtrlrLua/MethodEditor/CtrlrLuaMethodEditor.h"
#include "CtrlrLuaManager.h"
#include "CtrlrInlineUtilitiesGUI.h"

CtrlrPropertyComponent::CtrlrPropertyComponent (const Identifier &_propertyName,
								const ValueTree &_propertyElement,
								const ValueTree &_identifierDefinition,
								CtrlrPanel *_panel,
								StringArray *_possibleChoices,
								Array<var>  *_possibleValues)
	:	PropertyComponent (_propertyName.toString()),
		identifierDefinition(_identifierDefinition),
		propertyName(_propertyName),
		propertyElement(_propertyElement),
		panel(_panel),
		possibleChoices(_possibleChoices),
		possibleValues(_possibleValues)
{
	if (!identifierDefinition.isValid())
	{
		addAndMakeVisible (new CtrlrUnknownPropertyComponent (propertyName, propertyElement, identifierDefinition));
		visibleText	 = propertyName.toString();
		propertyType = CtrlrIDManager::UnknownProperty;
	}
	else
	{
		addAndMakeVisible (getPropertyComponent());
	}
}

CtrlrPropertyComponent::~CtrlrPropertyComponent()
{
	deleteAllChildren();
}

const String CtrlrPropertyComponent::getPropertyName()
{
	return propertyName.toString();
}

const String CtrlrPropertyComponent::getVisibleText()
{
	return visibleText;
}
void CtrlrPropertyComponent::paint (Graphics &g)
{
	getLookAndFeel().drawPropertyComponentBackground (g, getLookAndFeel().getPropertyComponentContentPosition (*this).getX(), getHeight(), *this);
	if (isMouseOver(false) && !currentFont.isUnderlined())
	{
		currentFont.setUnderline(true);
	}
	else if (currentFont.isUnderlined())
	{
		currentFont.setUnderline(false);
	}

	g.setFont (currentFont);
	g.setColour(findColour(PropertyComponent::labelTextColourId));
	g.drawFittedText (visibleText, 3, 0, getLookAndFeel().getPropertyComponentContentPosition (*this).getX()-5, getHeight(), Justification::centredLeft, 2);
}

void CtrlrPropertyComponent::resized()
{
	currentFont.setHeight (jmin (getHeight(), 24) * 0.55f);

	if (getNumChildComponents() > 0)
	{
        getChildComponent (0)->setBounds (getLookAndFeel().getPropertyComponentContentPosition (*this));
	}
}

void CtrlrPropertyComponent::refresh()
{
	if (getNumChildComponents() > 0)
	{
		CtrlrPropertyChild *child = dynamic_cast<CtrlrPropertyChild*>(getChildComponent (0));
		if (child != nullptr)
		{
			child->refresh();
		}
	}
}

Component *CtrlrPropertyComponent::getPropertyComponent()
{
	Value valueToControl	= propertyElement.getPropertyAsValue (propertyName, panel ? panel->getUndoManager() : nullptr);

	if (panel)
	{
		if ((bool)panel->getProperty(Ids::panelPropertyDisplayIDs) == false)
		{
			visibleText				= identifierDefinition.getProperty ("text").toString();
		}
		else
		{
			visibleText				= propertyName.toString();
		}
	}
	else
	{
		visibleText				= identifierDefinition.getProperty ("text").toString();
	}

	propertyType			= CtrlrIDManager::stringToType(identifierDefinition.getProperty("type"));

	switch (propertyType)
	{
		case CtrlrIDManager::ReadOnly:
			return (new CtrlrTextPropertyComponent (valueToControl, 1024, false, true));

		case CtrlrIDManager::Text:
			return (new CtrlrTextPropertyComponent (valueToControl, 1024, false));

		case CtrlrIDManager::MultiLine:
			preferredHeight = 96;
			return (new CtrlrTextPropertyComponent (valueToControl, 8192*4, true));

		case CtrlrIDManager::MultiLineSmall:
			preferredHeight = 64;
			return (new CtrlrTextPropertyComponent (valueToControl, 8192, true));

		case CtrlrIDManager::Expression:
			preferredHeight = 64;
			return (new CtrlrExpressionProperty (valueToControl));

		case CtrlrIDManager::Colour:
			return (new CtrlrColourPropertyComponent (valueToControl));

		case CtrlrIDManager::Font:
			return (new CtrlrFontPropertyComponent (valueToControl, panel));

		case CtrlrIDManager::Bool:
			return (new CtrlrBooleanPropertyComponent(valueToControl, identifierDefinition.getProperty ("defaults")));

		case CtrlrIDManager::MultiMidi:
			preferredHeight = 128;
			return (new CtrlrMultiMidiPropertyComponent(valueToControl));

		case CtrlrIDManager::SysEx:
			preferredHeight = 28;
			return (new CtrlrSysExPropertyComponent(valueToControl, propertyElement, propertyName, panel));

		case CtrlrIDManager::LuaMethod:
			return (new CtrlrLuaMethodProperty(valueToControl, propertyName, panel));

		case CtrlrIDManager::ActionButton:
			return (new CtrlrButtonPropertyComponent(valueToControl, visibleText));

		case CtrlrIDManager::Numeric:
			return (new CtrlrSliderPropertyComponent(valueToControl, (double)identifierDefinition.getProperty ("min", 0), (double)identifierDefinition.getProperty ("max", 127), (double)identifierDefinition.getProperty ("int", 1)));

		case CtrlrIDManager::VarNumeric:
			return (new CtrlrChoicePropertyComponent(valueToControl, possibleChoices, possibleValues, true));

		case CtrlrIDManager::VarText:
			return (new CtrlrChoicePropertyComponent(valueToControl, possibleChoices, possibleValues, false));

		case CtrlrIDManager::FileProperty:
			return (new CtrlrFileProperty (valueToControl));

		case CtrlrIDManager::Timestamp:
			return (new CtrlrTimestampProperty (valueToControl));

		case CtrlrIDManager::ModulatorList:
			return (new CtrlrModulatorListProperty (valueToControl, panel));

		default:
			break;
	}

	return (new CtrlrUnknownPropertyComponent (propertyName, propertyElement, identifierDefinition));
}

const String CtrlrPropertyComponent::getElementSubType()
{
	if (propertyElement.getType() == Ids::panel)
	{
		return ("");
	}
	else if (propertyElement.getType() == Ids::component)
	{
		return (propertyElement.getProperty("uiType"));
	}
	else if (propertyElement.getType() == Ids::modulator)
	{
		return ("");
	}
	else if (propertyElement.getType() == Ids::midi)
	{
		return ("midi");
	}
	else if (propertyElement.getType() == Ids::uiPanelEditor)
	{
		return ("");
	}
	else if (propertyElement.getType() == Ids::uiPanelCanvasLayer)
	{
		return ("uiPanelCanvasLayer");
	}
	else
	{
		return ("unknownSubType");
	}
}

const String CtrlrPropertyComponent::getElementType()
{
	if (propertyElement.getType() == Ids::midi)
	{
		return ("modulator");
	}
	else if (propertyElement.getType() == Ids::panel)
	{
		return ("");
	}
	else
	{
		return (propertyElement.getType().toString());
	}
}

CtrlrBooleanPropertyComponent::CtrlrBooleanPropertyComponent (const Value& _valueToControl, const String& _stateText)
    : valueToControl(_valueToControl), stateText(_stateText)
{
	if (stateText.contains ("/"))
	{
		onText	= stateText.upToFirstOccurrenceOf ("/", false, false);
		offText	= stateText.fromFirstOccurrenceOf ("/", false, false);
	}
	else
	{
		onText = offText = stateText;
	}

    addAndMakeVisible (&button);
	button.addListener (this);
    button.setClickingTogglesState (false);
    button.setButtonText (offText);
    button.setClickingTogglesState (true);
	button.setToggleState (valueToControl.getValue(), dontSendNotification);
}

CtrlrBooleanPropertyComponent::~CtrlrBooleanPropertyComponent()
{
}

void CtrlrBooleanPropertyComponent::paint (Graphics& g)
{
    g.setColour (findColour(ComboBox::backgroundColourId));
    g.fillRect (button.getBounds());

    g.setColour (findColour (ComboBox::outlineColourId));
    g.drawRect (button.getBounds());
}

void CtrlrBooleanPropertyComponent::refresh()
{
	button.setToggleState (button.getToggleState(), dontSendNotification);
	button.setButtonText (button.getToggleState() ? onText : offText);
}

void CtrlrBooleanPropertyComponent::resized()
{
	button.setBounds (0, 0, getWidth(), getHeight());
}

void CtrlrBooleanPropertyComponent::buttonClicked (Button*)
{
	button.setButtonText (button.getToggleState() ? onText : offText);
	valueToControl = button.getToggleState();
}

CtrlrButtonPropertyComponent::CtrlrButtonPropertyComponent(const Value &_valueToControl, const String &_propertyName)
	: valueToControl(_valueToControl), propertyName(_propertyName)
{
	button.setButtonText (propertyName);
	button.addListener (this);
	addAndMakeVisible (&button);
}

CtrlrButtonPropertyComponent::~CtrlrButtonPropertyComponent()
{
}

void CtrlrButtonPropertyComponent::resized()
{
	button.setBounds (0, 0, getWidth(), getHeight());
}

void CtrlrButtonPropertyComponent::refresh()
{
}

void CtrlrButtonPropertyComponent::buttonClicked (Button *_button)
{
	valueToControl = true;
}

CtrlrChoicePropertyComponent::CtrlrChoicePropertyComponent (const Value &_valueToControl,
                                                            const StringArray *_choices,
                                                            const Array<var> *_values,
                                                            const bool _numeric)
    : valueToControl(_valueToControl),
      combo (nullptr),
	  numeric(_numeric)
{
    addAndMakeVisible (combo = new ComboBox (""));
    combo->setEditableText (false);
    combo->setJustificationType (Justification::centredLeft);
    combo->setTextWhenNothingSelected ("");
    combo->setTextWhenNoChoicesAvailable (L"(no choices)");
    combo->addListener (this);

	if (_choices != nullptr)
	{
		choices = *_choices;

		for (int i=0; i<choices.size(); i++)
		{
			combo->addItem (choices[i], i+1);
		}

        if (choices.size() > 0)
            combo->setTextWhenNothingSelected (choices[0]);
	}

	if (_values != nullptr)
	{
		values = *_values;

		if (values.size() == 0)
		{
			for (int i=0; i<choices.size(); i++)
			{
				values.add (i);
			}
		}
	}
    setSize (256, 25);
	refresh();
}

CtrlrChoicePropertyComponent::~CtrlrChoicePropertyComponent()
{
}

void CtrlrChoicePropertyComponent::resized()
{
	combo->setBounds (0, 0, getWidth(), getHeight());
}

void CtrlrChoicePropertyComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
	changed();
}

void CtrlrChoicePropertyComponent::refresh()
{
	if (numeric)
	{
		const int i = values.indexOf (valueToControl.toString());
		combo->setSelectedItemIndex (i, sendNotification);
	}
	else
	{
		combo->setText (valueToControl.toString(), sendNotification);
	}
}

void CtrlrChoicePropertyComponent::changed()
{
	if (numeric)
	{
		valueToControl = values[combo->getSelectedItemIndex()];
	}
	else
	{
		valueToControl = combo->getText();
	}

	if (owner)
    {
        sendChangeMessage ();
    }
}

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
	colourTextInput.setColour (Label::textColourId, getColour().contrasting().darker(0.25f));
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
		/*
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
		*/
		auto colourSelector = std::make_unique<CtrlrColourSelectorComp> (this, canResetToDefault);

		 CallOutBox::launchAsynchronously (std::move(colourSelector), getScreenBounds(), nullptr);
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

CtrlrExpressionProperty::CtrlrExpressionProperty (const Value &_valeToControl) : valeToControl(_valeToControl), externalEditorWindow(nullptr)
{
    addAndMakeVisible (text = new TextEditor (""));
    text->setMultiLine (true, true);
    text->setReturnKeyStartsNewLine (false);
    text->setReadOnly (false);
    text->setScrollbarsShown (true);
    text->setCaretVisible (true);
    text->setPopupMenuEnabled (true);
    text->setText ("");
	text->setColour (TextEditor::outlineColourId, findColour (TextEditor::outlineColourId));
	text->setColour(TextEditor::highlightedTextColourId, findColour(TextEditor::highlightedTextColourId));
	text->setColour(TextEditor::highlightColourId, findColour(TextEditor::focusedOutlineColourId));

    addAndMakeVisible (apply = gui::createDrawableButton("Apply", BIN2STR(bug_svg)));
    apply->addListener (this);
	apply->setTooltip ("Compile expression, if it's valid set the property");
	apply->setMouseCursor (MouseCursor::PointingHandCursor);

	text->setFont (Font (Font::getDefaultMonospacedFontName(), 10.0f, Font::plain));
	text->setText (valeToControl.toString(), false);
	text->addListener (this);

    setSize (256, 48);
}

CtrlrExpressionProperty::~CtrlrExpressionProperty()
{
    deleteAndZero (text);
    deleteAndZero (apply);
}

void CtrlrExpressionProperty::resized()
{
	text->setBounds (0, 0, getWidth() - 24, getHeight() - 0);
    apply->setBounds (getWidth() - 24, 0, 24, getHeight()/2);
}

void CtrlrExpressionProperty::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == apply)
    {
		if (compile(true))
		{
			AlertWindow::showMessageBox (AlertWindow::InfoIcon, "Expression validation", "Expression is valid");
		}
    }
}

void CtrlrExpressionProperty::refresh()
{
	text->setText (valeToControl.toString(), false);
}

void CtrlrExpressionProperty::textEditorTextChanged (TextEditor &editor)
{
}

void CtrlrExpressionProperty::textEditorReturnKeyPressed (TextEditor &editor)
{
	compile (true);
}

void CtrlrExpressionProperty::textEditorFocusLost (TextEditor &editor)
{
	compile (true);
}

const bool CtrlrExpressionProperty::compile(const bool setPropertyIfValid)
{
	String parseError;
	Expression e = Expression(text->getText(), parseError);

	if (!parseError.isEmpty())
	{
		text->setColour (TextEditor::backgroundColourId, Colours::deeppink);
		AlertWindow::showMessageBox (AlertWindow::WarningIcon, "Expression validation", "Validation failed: "+parseError, "OK", this);
		return (false);
	}

	text->setColour (TextEditor::backgroundColourId, findColour(TextEditor::backgroundColourId));

	if (setPropertyIfValid)
	{
		valeToControl = text->getText();
	}

	return (true);
}

CtrlrFileProperty::CtrlrFileProperty (const Value &_valeToControl) : valueToControl(_valeToControl)
{
    addAndMakeVisible (path = new Label (""));
	path->setText (valueToControl.toString(), dontSendNotification);
	path->addListener (this);
	path->setColour (Label::backgroundColourId, findColour(ComboBox::backgroundColourId));
	path->setColour (Label::outlineColourId, findColour (ComboBox::outlineColourId));

    addAndMakeVisible (browse = new TextButton ("Browse", "Browse"));
    browse->addListener (this);
	browse->setConnectedEdges (TextButton::ConnectedOnRight);
    setSize (256, 48);
}

CtrlrFileProperty::~CtrlrFileProperty()
{
    deleteAndZero (path);
    deleteAndZero (browse);
}

void CtrlrFileProperty::resized()
{
	browse->setBounds (0, 0, 48, getHeight());
    path->setBounds (48, 0, getWidth() - 48, getHeight());
}

void CtrlrFileProperty::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == browse)
    {
		FileChooser myChooser ("Select a file",
								File::getSpecialLocation (File::userHomeDirectory),
								"*.*",
								false);

        if (myChooser.browseForFileToOpen())
        {
			valueToControl = myChooser.getResult().getFullPathName();
			path->setText (valueToControl.toString(), dontSendNotification);
        }
    }
}

void CtrlrFileProperty::refresh()
{
	path->setText (valueToControl.toString(), dontSendNotification);
}

void CtrlrFileProperty::labelTextChanged (Label* labelThatHasChanged)
{
	valueToControl = labelThatHasChanged->getText();
}

CtrlrFontPropertyComponent::CtrlrFontPropertyComponent (const Value &_valueToControl, CtrlrPanel *_owner)
    : valueToControl(_valueToControl), owner(_owner),
      typeface (0),
      fontBold (0),
      fontItalic (0),
      fontUnderline (0),
      fontSize (0),
	  kerning(0),
	  horizontalScale(0)
{
    addAndMakeVisible (typeface = new ComboBox (""));
    typeface->setEditableText (false);
    typeface->setJustificationType (Justification::centredLeft);
    typeface->setTextWhenNothingSelected (L"<Sans-Serif>");
    typeface->setTextWhenNoChoicesAvailable (L"<Sans-Serif>");
    typeface->addListener (this);

    addAndMakeVisible (fontBold = gui::createDrawableButton("Bold", BIN2STR(bold_svg)));
    fontBold->setTooltip (L"Bold");
    fontBold->addListener (this);

    addAndMakeVisible (fontItalic = gui::createDrawableButton("Italic", BIN2STR(italic_svg)));
    fontItalic->setTooltip (L"Italic");
    fontItalic->addListener (this);

    addAndMakeVisible (fontUnderline = gui::createDrawableButton("Underline", BIN2STR(underline_svg)));
    fontUnderline->setTooltip (L"Underline");
    fontUnderline->addListener (this);

    addAndMakeVisible (fontSize = new Slider (""));
	fontSize->setLookAndFeel (this);
	fontSize->setColour(Slider::rotarySliderFillColourId, Component::findColour(TextEditor::textColourId));
	fontSize->setTooltip (L"Size");
    fontSize->setRange (1, 999, 1);
    fontSize->setSliderStyle (Slider::RotaryVerticalDrag);
    fontSize->setTextBoxStyle (Slider::TextBoxRight, false, 34, 16);
    fontSize->addListener (this);

	addAndMakeVisible (horizontalScale = new Slider (""));
	horizontalScale->setLookAndFeel (this);
	horizontalScale->setColour(Slider::rotarySliderFillColourId, Component::findColour(TextEditor::textColourId));
	horizontalScale->setTooltip (L"Horizontal Scale");
    horizontalScale->setRange (0.0, 10.0, 0.01);
    horizontalScale->setSliderStyle (Slider::RotaryVerticalDrag);
    horizontalScale->setTextBoxStyle (Slider::TextBoxRight, false, 34, 16);
    horizontalScale->addListener (this);

	addAndMakeVisible (kerning = new Slider (""));
    kerning->setLookAndFeel (this);
	kerning->setColour(Slider::rotarySliderFillColourId, Component::findColour(TextEditor::textColourId));
	kerning->setTooltip (L"Extra Kerning");
    kerning->setRange (0.0, 10.0, 0.01);
    kerning->setSliderStyle (Slider::RotaryVerticalDrag);
    kerning->setTextBoxStyle (Slider::TextBoxRight, false, 34, 16);
    kerning->addListener (this);

	fontBold->setClickingTogglesState (true);
	fontBold->setMouseCursor (MouseCursor::PointingHandCursor);
	fontItalic->setClickingTogglesState (true);
	fontItalic->setMouseCursor (MouseCursor::PointingHandCursor);
	fontUnderline->setClickingTogglesState (true);
	fontUnderline->setMouseCursor (MouseCursor::PointingHandCursor);

    owner->getCtrlrManagerOwner().getFontManager().fillCombo (*typeface, true, true, true, true);

    setSize (300, 32);
}

CtrlrFontPropertyComponent::~CtrlrFontPropertyComponent()
{
    deleteAndZero (typeface);
    deleteAndZero (fontBold);
    deleteAndZero (fontItalic);
    deleteAndZero (fontUnderline);
    deleteAndZero (fontSize);
	deleteAndZero (kerning);
	deleteAndZero (horizontalScale);
}

void CtrlrFontPropertyComponent::resized()
{
    typeface->setBounds (0, 0, getWidth() * 0.4f, getHeight());

	fontBold->setBounds (getWidth() * 0.4f,									0, getWidth() * 0.05f,	getHeight());
    fontItalic->setBounds ((getWidth() * 0.4f) + (getWidth() * 0.05f),		0, getWidth() * 0.05f,	getHeight());
	fontUnderline->setBounds ((getWidth() * 0.4f) + 2*(getWidth() * 0.05f), 0, getWidth() * 0.05f,	getHeight());

    fontSize->setBounds			((getWidth() * 0.4f) + 3*(getWidth() * 0.05f),							0, getWidth() * 0.14f,	getHeight());
	horizontalScale->setBounds	((getWidth() * 0.4f) + 3*(getWidth() * 0.05f) + (getWidth() * 0.14f),	0, getWidth() * 0.14f,	getHeight());
	kerning->setBounds			((getWidth() * 0.4f) + 3*(getWidth() * 0.05f) + 2*(getWidth() * 0.14f),	0, getWidth() * 0.14f,	getHeight());
}

void CtrlrFontPropertyComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
	valueToControl = owner->getCtrlrManagerOwner().getFontManager().getStringFromFont(getFont());
}

void CtrlrFontPropertyComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == fontBold || buttonThatWasClicked == fontItalic || buttonThatWasClicked == fontUnderline)
    {
		valueToControl = owner->getCtrlrManagerOwner().getFontManager().getStringFromFont(getFont());
	}
}

void CtrlrFontPropertyComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
	valueToControl = owner->getCtrlrManagerOwner().getFontManager().getStringFromFont(getFont());
}

void CtrlrFontPropertyComponent::refresh()
{
	Font font = owner->getCtrlrManagerOwner().getFontManager().getFontFromString(valueToControl.toString());
	typeface->setText (font.getTypefaceName(), sendNotification);
	fontSize->setValue (font.getHeight(), dontSendNotification);
	kerning->setValue(font.getExtraKerningFactor(), dontSendNotification);
	horizontalScale->setValue(font.getHorizontalScale(), dontSendNotification);
	fontBold->setToggleState (font.isBold(), sendNotification);
	fontItalic->setToggleState (font.isItalic(), sendNotification);
	fontUnderline->setToggleState (font.isUnderlined(), sendNotification);
}

Font CtrlrFontPropertyComponent::getFont()
{
	Font font;

	if (typeface)
		font.setTypefaceName (typeface->getText());
	else
		return (font);

	font.setHeight (fontSize->getValue());
	font.setBold (fontBold->getToggleState());
	font.setItalic (fontItalic->getToggleState());
	font.setUnderline (fontUnderline->getToggleState());
	font.setExtraKerningFactor (kerning->getValue());
	font.setHorizontalScale (horizontalScale->getValue());
	return (font);
}

Label* CtrlrFontPropertyComponent::createSliderTextBox (Slider& slider)
{
    Label* const l = new CtrlrFontPropertyComponent::SliderLabelComp();

	l->setFont (Font(10.0f,Font::bold));
    l->setJustificationType (Justification::centred);

    l->setColour (Label::textColourId, slider.findColour (Slider::textBoxTextColourId));

    l->setColour (Label::backgroundColourId,
                  (slider.getSliderStyle() == Slider::LinearBar || slider.getSliderStyle() == Slider::LinearBarVertical)
                            ? Colours::transparentBlack
                            : slider.findColour (Slider::textBoxBackgroundColourId));
    l->setColour (Label::outlineColourId, slider.findColour (Slider::textBoxOutlineColourId));

    l->setColour (TextEditor::textColourId, slider.findColour (Slider::textBoxTextColourId));

    l->setColour (TextEditor::backgroundColourId,
                  slider.findColour (Slider::textBoxBackgroundColourId)
                        .withAlpha ((slider.getSliderStyle() == Slider::LinearBar || slider.getSliderStyle() == Slider::LinearBarVertical)
                                        ? 0.7f : 1.0f));

    l->setColour (TextEditor::outlineColourId, slider.findColour (Slider::textBoxOutlineColourId));

    return l;
}

CtrlrLuaMethodProperty::CtrlrLuaMethodProperty (const Value &_valeToControl, const Identifier &_id, CtrlrPanel *_owner)
    : valeToControl(_valeToControl), owner(_owner), id(_id),
      methodSelectorCombo (0),
      editMethodButton (0),
      newMethodButton (0),
      deleteMethodButton (0)
{
    addAndMakeVisible (methodSelectorCombo = new ComboBox (L"methodSelectorCombo"));
    methodSelectorCombo->setEditableText (false);
    methodSelectorCombo->setJustificationType (Justification::centredLeft);
    methodSelectorCombo->setTextWhenNothingSelected ("");
    methodSelectorCombo->setTextWhenNoChoicesAvailable (L"(no choices)");
    methodSelectorCombo->addListener (this);

    addAndMakeVisible (editMethodButton = gui::createDrawableButton("Edit Metod", BIN2STR(edit_svg)));
    editMethodButton->setTooltip (L"Edit selected method");
    editMethodButton->setButtonText (L"new button");
    editMethodButton->addListener (this);

    addAndMakeVisible (newMethodButton = gui::createDrawableButton("New Method", BIN2STR(file_svg)));
    newMethodButton->setTooltip (L"Add new method");
    newMethodButton->setButtonText (L"new button");
    newMethodButton->addListener (this);

    addAndMakeVisible (deleteMethodButton = gui::createDrawableButton("Delete Method", BIN2STR(clear_svg)));
    deleteMethodButton->setTooltip (L"Remove selected method");
    deleteMethodButton->setButtonText (L"new button");
    deleteMethodButton->addListener (this);

	editMethodButton->setMouseCursor(MouseCursor::PointingHandCursor);
	newMethodButton->setMouseCursor(MouseCursor::PointingHandCursor);
	deleteMethodButton->setMouseCursor(MouseCursor::PointingHandCursor);

    setSize (200, 25);
}

CtrlrLuaMethodProperty::~CtrlrLuaMethodProperty()
{
    deleteAndZero (methodSelectorCombo);
    deleteAndZero (editMethodButton);
    deleteAndZero (newMethodButton);
    deleteAndZero (deleteMethodButton);
}


void CtrlrLuaMethodProperty::resized()
{
    methodSelectorCombo->setBounds ((48) + (24), 0, getWidth() - 72, getHeight() - 0);
    editMethodButton->setBounds (0, 0, 24, getHeight() - 0);
    newMethodButton->setBounds (24, 0, 24, getHeight() - 0);
    deleteMethodButton->setBounds (48, 0, 24, getHeight() - 0);
}

void CtrlrLuaMethodProperty::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == methodSelectorCombo)
    {
		valeToControl = methodSelectorCombo->getText();
    }
}

void CtrlrLuaMethodProperty::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == editMethodButton)
    {
		if (methodSelectorCombo->getText() == "" || methodSelectorCombo->getText() == COMBO_NONE_ITEM)
		{
			return;
		}
		if (owner)
		{
			owner->getPanelWindowManager().show (CtrlrPanelWindowManager::LuaMethodEditor);
			CtrlrLuaMethodEditor *ed = dynamic_cast<CtrlrLuaMethodEditor*>(owner->getPanelWindowManager().getContent(CtrlrPanelWindowManager::LuaMethodEditor));
			if (ed != nullptr)
			{
				ed->setEditedMethod (methodSelectorCombo->getText());
			}
		}
    }
    else if (buttonThatWasClicked == newMethodButton)
    {
		AlertWindow w("Method name", "New method name", AlertWindow::QuestionIcon, this);
		w.addTextEditor ("methodName", "myMethod", "Method", false);
		w.addButton ("OK", 1, KeyPress(KeyPress::returnKey));
		w.addButton ("Cancel", 0, KeyPress(KeyPress::escapeKey));
		if (w.runModalLoop())
		{
			if (owner)
			{
				owner->getCtrlrLuaManager().getMethodManager().addMethod (ValueTree(), w.getTextEditorContents("methodName"), "", id.toString());
			}
		}

		refresh();
    }
    else if (buttonThatWasClicked == deleteMethodButton)
    {
		if (owner)
		{
			owner->getCtrlrLuaManager().getMethodManager().deleteMethod(methodSelectorCombo->getText());
		}

		refresh();
    }
}

void CtrlrLuaMethodProperty::refresh()
{
	if (owner == 0)
		return;
	methodSelectorCombo->clear();
	methodSelectorCombo->addItem (COMBO_NONE_ITEM, 1);
	methodSelectorCombo->addItemList (owner->getCtrlrLuaManager().getMethodManager().getMethodList(), 2);
	methodSelectorCombo->setText (valeToControl.toString(), sendNotification);
}

CtrlrModulatorListProperty::CtrlrModulatorListProperty(const Value &_valueToControl, CtrlrPanel *_owner)
	: owner(_owner), valueToControl(_valueToControl)
{
	addAndMakeVisible (combo = new ComboBox (""));
    combo->setEditableText (false);
    combo->setJustificationType (Justification::centredLeft);
    combo->setTextWhenNothingSelected (COMBO_ITEM_NONE);
    combo->setTextWhenNoChoicesAvailable ("No modulators");
    combo->addListener (this);

	listChanged();
}

CtrlrModulatorListProperty::~CtrlrModulatorListProperty()
{
}

void CtrlrModulatorListProperty::resized()
{
	combo->setBounds (0, 0, getWidth(), getHeight());
}

void CtrlrModulatorListProperty::refresh()
{
	if (choices.contains (valueToControl.toString()))
	{
		combo->setColour (ComboBox::textColourId, Colours::black);
	}
	else
	{
		combo->setColour (ComboBox::textColourId, Colours::red);
	}

	combo->setText (valueToControl.toString(), sendNotification);
}

void CtrlrModulatorListProperty::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
	valueToControl = combo->getText();
}

void CtrlrModulatorListProperty::listChanged()
{
	choices.clear();
	choices.add (COMBO_ITEM_NONE);
	combo->addItem (COMBO_ITEM_NONE, 1);

	for (int i=0; i<owner->getModulators().size(); i++)
	{
		choices.add (owner->getModulatorByIndex(i)->getName());
		combo->addItem (owner->getModulatorByIndex(i)->getName(), i+2);
	}

	const String storedModulatorName = valueToControl.toString();

	if (choices.contains (storedModulatorName))
	{
		combo->setColour (ComboBox::textColourId, Colours::black);
		combo->setText (storedModulatorName, sendNotification);
	}
	else
	{
		combo->setColour (ComboBox::textColourId, Colours::red);
		combo->setText (storedModulatorName, dontSendNotification);
	}
}

void CtrlrModulatorListProperty::modulatorChanged (CtrlrModulator *modulatorThatChanged)
{
}

void CtrlrModulatorListProperty::modulatorAdded (CtrlrModulator *modulatorThatWasAdded)
{
	listChanged();
}

void CtrlrModulatorListProperty::modulatorRemoved (CtrlrModulator *modulatorRemoved)
{
	listChanged();
}

CtrlrMultiMidiPropertyComponent::CtrlrMultiMidiPropertyComponent (const Value &_valueToControl)
    : valueToControl(_valueToControl),
      add (0),
      remove (0),
      list (0),
      copy (0),
      paste (0),
      insert (0)
{
    addAndMakeVisible (add = gui::createDrawableButton("Add", BIN2STR(file_svg)));
    add->setTooltip (L"Add message");
    add->addListener (this);

    addAndMakeVisible (remove = gui::createDrawableButton("Remove", BIN2STR(clear_svg)));
    remove->setTooltip (L"Remove selected message");
    remove->addListener (this);


    addAndMakeVisible (list = new ListBox ("list", this));

    addAndMakeVisible (copy = gui::createDrawableButton("Copy", BIN2STR(copy_svg)));
    copy->setTooltip (L"Copy to clipboard");
    copy->addListener (this);

    addAndMakeVisible (paste = gui::createDrawableButton("Paste", BIN2STR(paste_svg)));
    paste->setTooltip (L"Paste from clipboard");
    paste->addListener (this);

    addAndMakeVisible (insert = gui::createDrawableButton("Insert", BIN2STR(receive_svg)));
    insert->setTooltip (L"Insert pre-defined");
    insert->addListener (this);

	list->setRowHeight (14);
	add->setMouseCursor (MouseCursor::PointingHandCursor);
	remove->setMouseCursor (MouseCursor::PointingHandCursor);
	copy->setMouseCursor (MouseCursor::PointingHandCursor);
	paste->setMouseCursor (MouseCursor::PointingHandCursor);
	insert->setMouseCursor (MouseCursor::PointingHandCursor);
	remove->setTooltip ("Remove selected");
	loadAdditionalTemplates(File());
    setSize (256, 96);
}

CtrlrMultiMidiPropertyComponent::~CtrlrMultiMidiPropertyComponent()
{
    deleteAndZero (add);
    deleteAndZero (remove);
    deleteAndZero (list);
    deleteAndZero (copy);
    deleteAndZero (paste);
    deleteAndZero (insert);
}

void CtrlrMultiMidiPropertyComponent::paint (Graphics& g)
{
    g.setGradientFill (ColourGradient (Colours::white,
                                       (float) ((getWidth() / 2)), 0.0f,
                                       Colour (0xffe2e2e2),
                                       (float) ((getWidth() / 2)), 32.0f,
                                       false));
    g.fillRect (0, 0, getWidth() - 0, 32);

    g.setGradientFill (ColourGradient (Colour (0xffd6d6d6),
                                       (float) ((getWidth() / 2)), 29.0f,
                                       Colour (0xff767676),
                                       (float) ((getWidth() / 2)), 32.0f,
                                       false));
    g.fillRect (0, 29, getWidth() - 0, 3);
}

void CtrlrMultiMidiPropertyComponent::resized()
{
    add->setBounds (8, 4, 24, 24);
    remove->setBounds (72, 4, 24, 24);
    list->setBounds (0, 32, getWidth() - 0, getHeight() - 32);
    copy->setBounds ((getWidth() - 32) + -32, 4, 24, 24);
    paste->setBounds (getWidth() - 32, 4, 24, 24);
    insert->setBounds (40, 4, 24, 24);
}

void CtrlrMultiMidiPropertyComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == add)
    {
		CtrlrManagerWindowManager::showModalDialog("Add MIDI message", &questionWindow, false, this);
		values.add (questionWindow.getValue().trim());
		valueToControl = values.joinIntoString (":");
    }
    else if (buttonThatWasClicked == remove)
    {
		values.remove (list->getSelectedRow());
		valueToControl = values.joinIntoString (":");
    }
    else if (buttonThatWasClicked == copy)
    {
		SystemClipboard::copyTextToClipboard (values.joinIntoString(":"));
    }
    else if (buttonThatWasClicked == paste)
    {
		valueToControl = SystemClipboard::getTextFromClipboard();
		refresh();
    }
    else if (buttonThatWasClicked == insert)
    {
		PopupMenu m;
		for (int i=0; i<templates.getAllKeys().size(); i++)
		{
			m.addItem (i+1, templates.getAllKeys() [i]);
		}
		const int ret = m.show();
		if (ret > 0)
		{
			const String data = templates.getValue (templates.getAllKeys() [ret-1], "");
			if (data != "")
			{
				valueToControl = data;
				refresh();
			}
		}
		else
		{
			return;
		}
    }

	if (list)
		list->updateContent();
}

void CtrlrMultiMidiPropertyComponent::mouseDown (const MouseEvent& e)
{
	Label *l = dynamic_cast<Label*>(e.eventComponent);

	if (l)
	{
		const int id = l->getProperties().getWithDefault("dOb", -1);
		list->selectRow (id, true, true);
	}
}

void CtrlrMultiMidiPropertyComponent::mouseDoubleClick (const MouseEvent& e)
{
	Label *l = dynamic_cast<Label*>(e.eventComponent);

	if (l)
	{
		const int id = l->getProperties().getWithDefault("dOb", -1);
		list->selectRow (id, true, true);
	}
}

void CtrlrMultiMidiPropertyComponent::paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected)
{
	if (rowIsSelected)
	{
		g.setColour (Colours::lightblue);
		g.fillAll();
	}
	else
	{
		g.setColour (Colours::white);
		g.fillAll();
	}
}

Component *CtrlrMultiMidiPropertyComponent::refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate)
{
	Label *l = (Label*) existingComponentToUpdate;

	if (l == 0)
	{
		l = new Label ("", values[rowNumber]);
		l->setEditable (false, true, false);
		l->setColour (Label::backgroundColourId, Colours::transparentBlack);
		l->getProperties().set ("dOb", rowNumber);
		l->addListener (this);
		l->addMouseListener (this, false);
	}
	else
	{
		l->getProperties().set ("dOb", rowNumber);
		l->setText (values[rowNumber], dontSendNotification);
		l->addMouseListener (this, false);
	}

	return l;
}

int CtrlrMultiMidiPropertyComponent::getNumRows()
{
	return (values.size());
}

void CtrlrMultiMidiPropertyComponent::refresh()
{
	values.clear();
	values.addTokens (valueToControl.toString().trim(), ":", "\"\'");
	list->updateContent();
	list->repaint();
}

void CtrlrMultiMidiPropertyComponent::loadAdditionalTemplates(const File &templateFile)
{
	XmlDocument staticTemplates(MemoryBlock (BinaryData::CtrlrMidiMultiTemplate_xml, BinaryData::CtrlrMidiMultiTemplate_xmlSize).toString());
	XmlDocument dynamicTemplates(templateFile);

	ScopedPointer <XmlElement> dynamicXml(dynamicTemplates.getDocumentElement().release());
	ScopedPointer <XmlElement> staticXml(staticTemplates.getDocumentElement().release());

	if (dynamicXml)
	{
		forEachXmlChildElement (*dynamicXml, t)
		{
			if (t->hasTagName("template"))
			{
				templates.set (t->getStringAttribute ("name"), t->getAllSubText().trim());
			}
		}
	}

	if (staticXml)
	{
		forEachXmlChildElement (*staticXml, t)
		{
			if (t->hasTagName("template"))
			{
				templates.set (t->getStringAttribute ("name"), t->getAllSubText().trim());
			}
		}
	}
}

void CtrlrMultiMidiPropertyComponent::labelTextChanged (Label* l)
{
	const int id = l->getProperties().getWithDefault("dOb", -1);

	if (id >= 0)
	{
		values.set (id, l->getText());
		valueToControl = values.joinIntoString (":");
	}
}

CtrlrSliderPropertyComponent::CtrlrSliderPropertyComponent (const Value &_valueToControl, double rangeMin, double rangeMax, double interval)
	: valueToControl(_valueToControl)
{
    addAndMakeVisible (&slider);
    slider.setRange (rangeMin, rangeMax, interval);
    slider.setSliderStyle (Slider::LinearBar);
    slider.getValueObject().referTo (valueToControl);
}

CtrlrSliderPropertyComponent::~CtrlrSliderPropertyComponent()
{
}

void CtrlrSliderPropertyComponent::setValue (const double newValue)
{
}

double CtrlrSliderPropertyComponent::getValue() const
{
    return slider.getValue();
}

void CtrlrSliderPropertyComponent::refresh()
{
	slider.setValue (getValue(), dontSendNotification);
}

void CtrlrSliderPropertyComponent::sliderValueChanged (Slider *sliderThatChanged)
{
    if (getValue() != slider.getValue())
        setValue (slider.getValue());
}

void CtrlrSliderPropertyComponent::resized()
{
	slider.setBounds (0, 0, getWidth(), getHeight());
}

//==============================================================================
CtrlrSysExEditor::CtrlrSysExEditor (Value &_val, CtrlrPanel *_owner)
    : val(_val),
      messageLength (0),
      label (0),
      owner(_owner)
{
    addAndMakeVisible (messageLength = new Slider (L"messageLength"));
    messageLength->setRange (0, 512, 1);
    messageLength->setSliderStyle (Slider::IncDecButtons);
    messageLength->setTextBoxStyle (Slider::TextBoxLeft, false, 32, 20);
    messageLength->addListener (this);

    addAndMakeVisible (label = new Label ("Length", "Length"));
    label->setFont (Font (14.0000f, Font::bold));
    label->setJustificationType (Justification::centred);
    label->setEditable (true, true, true);
    label->addListener (this);

	splitMessage.addTokens (val.toString(), " :;", "\'\"");
	setLength (splitMessage.size());
    setSize (612, 256);
}

CtrlrSysExEditor::~CtrlrSysExEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (messageLength);
    deleteAndZero (label);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrSysExEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

	Colour backGroundColor = findColour(TextEditor::backgroundColourId);
	Colour lightBackGroundColor = findColour(TextEditor::outlineColourId);
    g.fillAll (backGroundColor);

    g.setGradientFill (ColourGradient (backGroundColor,
                                       (float) ((getWidth() / 2)), 0.0f,
									   lightBackGroundColor,
                                       (float) ((getWidth() / 2)), 32.0f,
                                       false));
    g.fillRect (0, 0, getWidth() - 0, 32);

    g.setGradientFill (ColourGradient (Colour (0xffd6d6d6),
                                       (float) ((getWidth() / 2)), 29.0f,
                                       Colour (0xff767676),
                                       (float) ((getWidth() / 2)), 32.0f,
                                       false));
    g.fillRect (0, 29, getWidth() - 0, 3);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrSysExEditor::resized()
{
    messageLength->setBounds (72, 4, 88, 22);
    label->setBounds (8, 8, 55, 16);
	int y;
	int x=0;
	for (int i=0; i<byteValueLabels.size(); i++)
	{
		y = 48 + ((i/16)*48);
		byteValueLabels[i]->setBounds (16+(x*36), y, 32, 32);
		x++;
		if (x==16)
			x=0;
	}

	for (int i=0; i<rows.size(); i++)
	{
		rows[i]->setBounds (16, 40+(i*48), getWidth()-32, 8);
	}
}

void CtrlrSysExEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == messageLength)
    {
		setLength ((int)messageLength->getValue());
    }
}

void CtrlrSysExEditor::labelTextChanged (Label* labelThatHasChanged)
{
    sendChangeMessage();
}

void CtrlrSysExEditor::mouseDown (const MouseEvent& e)
{
	if (e.mods.isPopupMenu())
	{
		Label *l = dynamic_cast<Label*>(e.eventComponent);
		if (l!=0)
		{
			PopupMenu m;
			m.addSectionHeader ("Insert variable");
			m.addItem (1, "MIDI Channel (7bits)");
			m.addItem (2, "MIDI Channel (4bits)");
			m.addItem (3, "LSB part of value (7bits)");
			m.addItem (4, "MSB part of value (7bits)");
			m.addItem (5, "LSB part of value (4bits)");
			m.addItem (6, "MSB part of value (4bits)");
			m.addItem (7, "Roland JV1010 upper byte");
			m.addItem (8, "Roland JV1010 upper middle byte");
			m.addItem (9, "Roland JV1010 lower middle byte");
			m.addItem (10, "Roland JV1010 lower byte");

			m.addSectionHeader ("Insert static");

			m.addItem (11, "SysEx Start");
			m.addItem (12, "SysEx EOM");
			m.addSubMenu ("Vendor ID", getVendorIdMenu());

			m.addSectionHeader ("Program variables");
			m.addItem (8192, "Current program number");
			m.addItem (8193, "Current bank number");

			m.addSectionHeader ("Checksums (tN) t=type N=num bytes to count");
			m.addItem (13, "Roland JP8080 Checksum");
			m.addItem (14, "Waldorf RackAttack Checksum");
			m.addItem (15, "Ignore this byte on input");
			PopupMenu km,lm,mm,nm;

			for (int i=0; i<16; i++)
			{
				km.addItem (20+i, "Global variable [k"+String::toHexString(i)+"]");
			}
			m.addSubMenu ("Global variable[0]",km);

			for (int i=0; i<16; i++)
			{
				lm.addItem (37+i, "Global variable [o"+String::toHexString(i)+"]");
			}
			m.addSubMenu ("Global variable[1]",lm);

			for (int i=0; i<16; i++)
			{
				mm.addItem (53+i, "Global variable [p"+String::toHexString(i)+"]");
			}
			m.addSubMenu ("Global variable[2]",mm);

			for (int i=0; i<16; i++)
			{
				nm.addItem (69+i, "Global variable [n"+String::toHexString(i)+"]");
			}
			m.addSubMenu ("Global variable[3]",nm);

			const int ret = m.show();
			switch (ret)
			{
			case 1:
				l->setText("yy", sendNotification);
				break;
			case 2:
				l->setText ("0y", sendNotification);
				break;
			case 3:
				l->setText ("LS", sendNotification);
				break;
			case 4:
				l->setText ("MS", sendNotification);
				break;
			case 5:
				l->setText ("ls", sendNotification);
				break;
			case 6:
				l->setText ("ms", sendNotification);
				break;
			case 7:
				l->setText ("r1", sendNotification);
				break;
			case 8:
				l->setText ("r2", sendNotification);
				break;
			case 9:
				l->setText ("r3", sendNotification);
				break;
			case 10:
				l->setText ("r4", sendNotification);
				break;
			case 11:
				l->setText ("f0", sendNotification);
				break;
			case 12:
				l->setText ("f7", sendNotification);
				break;
			case 13:
				l->setText ("z5", sendNotification);
				break;
			case 14:
				l->setText ("w5", sendNotification);
				break;
			case 15:
				l->setText ("ii", sendNotification);
				break;
			}

			if (ret >= 20 && ret < 37)
			{
				l->setText ("k"+String::toHexString(ret-20), sendNotification);
			}

			if (ret >= 37 && ret < 53)
			{
				l->setText ("o"+String::toHexString(ret-37), sendNotification);
			}

			if (ret >= 53 && ret < 69)
			{
				l->setText ("p"+String::toHexString(ret-53), sendNotification);
			}

			if (ret >= 69 && ret < 86)
			{
				l->setText ("n"+String::toHexString(ret-69), sendNotification);
			}

			if (ret > 1024 && ret < 4096)
			{
				ValueTree vendor = owner->getCtrlrManagerOwner().getIDManager().getVendorTree().getChild (ret - 1024);
				const String vendorId = vendor.getProperty(Ids::id).toString();
				if (vendorId.length() == 2)
				{
					/* vendor is oldSkool */
					l->setText (vendorId, sendNotification);
				}

				if (vendorId.length() == 6)
				{
					/* moder vendor id, 3 bytes
					   check if the next bytes are available so we can fill them with data
					   */

					const int indexOfLabel = byteValueLabels.indexOf (l);
					if (byteValueLabels[indexOfLabel+1] && byteValueLabels[indexOfLabel+2])
					{
						byteValueLabels[indexOfLabel]->setText (vendorId.substring   (0,2), dontSendNotification);
						byteValueLabels[indexOfLabel+1]->setText (vendorId.substring (2,4), dontSendNotification);
						byteValueLabels[indexOfLabel+2]->setText (vendorId.substring (4,6), dontSendNotification);
					}
					else
					{
						WARN("Not enough space to fit a 3 byte vendor ID, add some space.");
					}
				}
			}

			if (ret == 8192)
			{
				l->setText ("tp", sendNotification);
			}
			if (ret == 8193)
			{
				l->setText ("tb", sendNotification);
			}
		}
	}
}

const PopupMenu CtrlrSysExEditor::getVendorIdMenu()
{
    PopupMenu m;
    ValueTree vendorTree = owner->getCtrlrManagerOwner().getIDManager().getVendorTree();

    for (int i=0; i<vendorTree.getNumChildren(); i++)
	{
		m.addItem (1024+i, vendorTree.getChild(i).getProperty(Ids::name));
	}
    return (m);
}

void CtrlrSysExEditor::setLength (const int newLength)
{

	currentMessageLength = newLength;

	messageLength->setValue (currentMessageLength, dontSendNotification);

	if (byteValueLabels.size() < currentMessageLength)
	{
		for (int i=byteValueLabels.size(); i<currentMessageLength; i++)
		{
			byteValueLabels.add (addByte (splitMessage[i]));
		}
	}
	else if (byteValueLabels.size() > currentMessageLength)
	{
		byteValueLabels.removeLast (byteValueLabels.size() - currentMessageLength);
	}

	rows.clear();
	for (int i=0; i<=byteValueLabels.size()/16; i++)
	{
		SysExRow *r = new SysExRow(i);
		addAndMakeVisible(r);
		rows.add (r);
	}

	resized();

	sendChangeMessage();
}

Label *CtrlrSysExEditor::addByte(const String &byteAsString)
{
	Label *byteLabel = new Label ("byteLabel", byteAsString);
	addAndMakeVisible (byteLabel);
    byteLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 15.0000f, Font::plain));
    byteLabel->setJustificationType (Justification::centredLeft);
    byteLabel->setEditable (true, true, false);
    byteLabel->setColour (Label::outlineColourId, Colours::white);
    byteLabel->setColour (TextEditor::textColourId, findColour(TextEditor::textColourId));
    byteLabel->setColour (TextEditor::backgroundColourId, findColour(TextEditor::backgroundColourId));
	byteLabel->setColour (TextEditor::highlightColourId, findColour(TextEditor::focusedOutlineColourId));
    byteLabel->addListener (this);
	byteLabel->addMouseListener (this, false);

	return (byteLabel);
}

const String CtrlrSysExEditor::getValue()
{
	String ret;
	for (int i=0; i<byteValueLabels.size(); i++)
	{
		ret<< byteValueLabels[i]->getText()+" ";
	}

	return (ret.trim());
}

SysExRow::SysExRow(const int _n, const int _w, const int _gap) : n(_n), w(_w), gap(_gap)
{
}

void SysExRow::paint (Graphics &g)
{
	g.setFont (Font (Font::getDefaultMonospacedFontName(), 8.0f, Font::plain));
	g.setColour (findColour(TextEditor::textColourId));
	for (int i=0; i<16; i++)
	{
		g.drawFittedText (String ((16*n)+(i+1)), i*(w+gap), 0, w, 8, Justification::centred, 1);
	}

	g.fillRect (0,getHeight()-1,getWidth(),1);
}

void SysExRow::resized()
{
}

CtrlrSysExFormulaEditor::CtrlrSysExFormulaEditor ()
    : forwardFormula (0),
      reverseFormula (0),
      forwardLabel (0),
      reverseLabel (0),
      label (0)
{
    addAndMakeVisible (forwardFormula = new CodeEditorComponent (forwardFormulaDocument, 0));

    addAndMakeVisible (reverseFormula = new CodeEditorComponent (reverseFormulaDocument, 0));

    addAndMakeVisible (forwardLabel = new Label (L"forwardLabel",
                                                 L"Forward"));
    forwardLabel->setFont (Font (16.0000f, Font::plain));
    forwardLabel->setJustificationType (Justification::centredLeft);
    forwardLabel->setEditable (false, false, false);
    forwardLabel->setColour (TextEditor::textColourId, findColour(TextEditor::textColourId));
    forwardLabel->setColour (TextEditor::backgroundColourId, findColour(TextEditor::backgroundColourId));

    addAndMakeVisible (reverseLabel = new Label (L"reverseLabel",
                                                 L"Reverse"));
    reverseLabel->setFont (Font (16.0000f, Font::plain));
    reverseLabel->setJustificationType (Justification::centredLeft);
    reverseLabel->setEditable (false, false, false);
    reverseLabel->setColour (TextEditor::textColourId, findColour(TextEditor::textColourId));
    reverseLabel->setColour (TextEditor::backgroundColourId, findColour(TextEditor::backgroundColourId));

    addAndMakeVisible (label = new Label (L"new label",
                                          L"SysEx Formula ()"));
    label->setFont (Font (24.0000f, Font::plain));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
	label->setColour(TextEditor::textColourId, findColour(TextEditor::textColourId));
	label->setColour(TextEditor::backgroundColourId, findColour(TextEditor::backgroundColourId));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrSysExFormulaEditor::~CtrlrSysExFormulaEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (forwardFormula);
    deleteAndZero (reverseFormula);
    deleteAndZero (forwardLabel);
    deleteAndZero (reverseLabel);
    deleteAndZero (label);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrSysExFormulaEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrSysExFormulaEditor::resized()
{
    forwardFormula->setBounds (0, (32) + (16), getWidth() - 0, proportionOfHeight (0.4200f));
    reverseFormula->setBounds (0, (((32) + (16)) + (proportionOfHeight (0.4200f))) + (16), getWidth() - 0, proportionOfHeight (0.4200f));
    forwardLabel->setBounds (0, 32, getWidth() - 0, 16);
    reverseLabel->setBounds (0, ((32) + (16)) + (proportionOfHeight (0.4200f)), getWidth() - 0, 16);
    label->setBounds (0, 0, getWidth() - 0, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

CtrlrSysExPropertyComponent::CtrlrSysExPropertyComponent (const Value &_valueToControl, const ValueTree &_propertyTree, const Identifier &_propertyName, CtrlrPanel *_owner)
    : valueToControl(_valueToControl),
      propertyTree(_propertyTree),
      propertyName(_propertyName),
      sysexPreview (0),
      editButton (0),
      copy (0),
      paste (0),
      owner(_owner)
{
    addAndMakeVisible (sysexPreview = new Label (L"sysexPreview",
                                                 L"F0 00 F7"));
    sysexPreview->setFont (Font (Font::getDefaultMonospacedFontName(), 12.0000f, Font::plain));
    sysexPreview->setJustificationType (Justification::centredLeft);
    sysexPreview->setEditable (true, false, false);
    sysexPreview->addListener (this);
	sysexPreview->setColour (Label::backgroundColourId, findColour(ComboBox::backgroundColourId));
	sysexPreview->setColour (Label::outlineColourId, findColour (ComboBox::outlineColourId));
	sysexPreview->setColour (TextEditor::highlightColourId, findColour(TextEditor::focusedOutlineColourId));

    addAndMakeVisible (editButton = new TextButton (L"editButton"));
    editButton->setButtonText (L"Edit");
    editButton->addListener (this);

    addAndMakeVisible (copy = gui::createDrawableButton("Copy", BIN2STR(copy_svg)));
    copy->setTooltip (L"Copy to clipboard");
    copy->addListener (this);

    addAndMakeVisible (paste = gui::createDrawableButton("Paste", BIN2STR(paste_svg)));
    paste->setTooltip (L"Paste from clipboard");
    paste->addListener (this);

	copy->setMouseCursor(MouseCursor::PointingHandCursor);
	paste->setMouseCursor(MouseCursor::PointingHandCursor);
    setSize (200, 25);
	refresh();
}

CtrlrSysExPropertyComponent::~CtrlrSysExPropertyComponent()
{
    deleteAndZero (sysexPreview);
    deleteAndZero (editButton);
    deleteAndZero (copy);
    deleteAndZero (paste);
}

void CtrlrSysExPropertyComponent::resized()
{
    editButton->setBounds (0, 0, 48, 24);
    copy->setBounds (52, 0, 24, 24);
    paste->setBounds (80, 0, 24, 24);
	sysexPreview->setBounds (108, 0, getWidth()-108, getHeight());
}

void CtrlrSysExPropertyComponent::labelTextChanged (Label* labelThatHasChanged)
{
    if (labelThatHasChanged == sysexPreview)
    {
		valueToControl = sysexPreview->getText();
    }
}

void CtrlrSysExPropertyComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == editButton)
    {
    	DialogWindow::LaunchOptions o;

    	CtrlrSysExEditor *editor 		= new CtrlrSysExEditor (valueToControl, owner);
    	editor->addChangeListener (this);

    	if (propertyTree.hasType (Ids::midi) && propertyTree.getParent().hasType (Ids::modulator))
			o.dialogTitle 					= STR (owner->getName() + "/" + propertyTree.getParent().getProperty(Ids::name).toString() + "/" + propertyName.toString());
		else
			o.dialogTitle					= STR (owner->getName() + "/" + "SysEx editor");

		o.content.set (editor, true);
		o.resizable						= true;
		o.useNativeTitleBar				= true;
		o.dialogBackgroundColour 		= findColour(TextEditor::backgroundColourId);
		o.escapeKeyTriggersCloseButton	= true;
		o.componentToCentreAround		= this;
		o.launchAsync();

		valueToControl = editor->getValue();
		sysexPreview->setText (valueToControl.toString(), dontSendNotification);
    }
    else if (buttonThatWasClicked == copy)
    {
		SystemClipboard::copyTextToClipboard (valueToControl.toString());
    }
    else if (buttonThatWasClicked == paste)
    {
		const String v = SystemClipboard::getTextFromClipboard();
		if (v.containsOnly("0123456789abcdefABCDEFxyXYlsLSMmkKrzi :;"))
		{
			valueToControl = v;
			refresh();
		}
    }
}

void CtrlrSysExPropertyComponent::changeListenerCallback (ChangeBroadcaster *cb)
{
	CtrlrSysExEditor *ed = dynamic_cast<CtrlrSysExEditor*>(cb);

	if (ed != nullptr)
	{
		valueToControl = ed->getValue();
		refresh();
	}
}

void CtrlrSysExPropertyComponent::refresh()
{
	sysexPreview->setText (valueToControl.toString(), dontSendNotification);
}

class CtrlrTextPropLabel  : public Label
{
	public:
		CtrlrTextPropLabel (CtrlrTextPropertyComponent& owner_, const int maxChars_, const bool isMultiline_)
			: Label ("", ""),
				owner (owner_), maxChars (maxChars_), isMultiline (isMultiline_)
		{
	        setEditable (true, true, false);
			setColour (backgroundColourId, findColour(ComboBox::backgroundColourId));
			setColour (outlineColourId, findColour (ComboBox::outlineColourId));
			setColour (TextEditor::highlightColourId, findColour(TextEditor::focusedOutlineColourId));
		}

		TextEditor* createEditorComponent()
		{
			TextEditor* const textEditor = Label::createEditorComponent();
			textEditor->setInputRestrictions (maxChars);

			if (isMultiline)
			{
				textEditor->setMultiLine (true, true);
				textEditor->setReturnKeyStartsNewLine (true);
	        }

		    return textEditor;
		}

		void textWasEdited()
		{
	        owner.textWasEdited();
	    }

	private:
	    CtrlrTextPropertyComponent& owner;
	    int maxChars;
	    bool isMultiline;
};

//==============================================================================
CtrlrTextPropertyComponent::CtrlrTextPropertyComponent (const Value& _valueToControl,
														const int maxNumChars,
														const bool isMultiLine, const bool isReadOnly) : valueToControl(_valueToControl)
{
    createEditor (maxNumChars, isMultiLine);
    textEditor->getTextValue().referTo (valueToControl);

	if (isReadOnly)
	{
		textEditor->setColour (Label::backgroundColourId, textEditor->findColour(Label::backgroundColourId,false).withAlpha(0.5f));
		textEditor->setColour (Label::textColourId, textEditor->findColour(Label::textColourId,false).brighter(0.5f));
		textEditor->setEditable (false, false, false);
	}
}

CtrlrTextPropertyComponent::~CtrlrTextPropertyComponent()
{
}

void CtrlrTextPropertyComponent::setText (const String& newText)
{
    textEditor->setText (newText, sendNotification);
}

String CtrlrTextPropertyComponent::getText() const
{
    return textEditor->getText();
}

void CtrlrTextPropertyComponent::createEditor (const int maxNumChars, const bool isMultiLine)
{
    addAndMakeVisible (textEditor = new CtrlrTextPropLabel (*this, maxNumChars, isMultiLine));

    if (isMultiLine)
    {
        textEditor->setJustificationType (Justification::topLeft);
    }
}

void CtrlrTextPropertyComponent::resized()
{
	if (textEditor)
		textEditor->setBounds (0,0,getWidth(),getHeight());
}

void CtrlrTextPropertyComponent::textWasEdited()
{
    const String newText (textEditor->getText());

    if (getText() != newText)
        setText (newText);
}

void CtrlrTextPropertyComponent::refresh()
{
	if (textEditor)
		textEditor->setText (valueToControl.toString(), dontSendNotification);
}

CtrlrTimestampProperty::CtrlrTimestampProperty (const Value& _valueToControl) : valueToControl(_valueToControl)
{
	addAndMakeVisible (textEditor = new Label ());
	textEditor->setColour (Label::backgroundColourId, Colours::white.withAlpha(0.2f));
}

CtrlrTimestampProperty::~CtrlrTimestampProperty()
{
}

void CtrlrTimestampProperty::refresh()
{
	if (textEditor)
	{
		textEditor->setText (Time ((int64)valueToControl.getValue()).formatted("%Y-%m-%d %H:%M:%S"), dontSendNotification);
	}
}

void CtrlrTimestampProperty::resized()
{
	if (textEditor)
		textEditor->setBounds (0,0,getWidth(),getHeight());
}


CtrlrUnknownPropertyComponent::CtrlrUnknownPropertyComponent(const Identifier &_propertyName,
															const ValueTree &_propertyElement,
															const ValueTree &identifier,
															CtrlrPanel *panel,
															StringArray *possibleChoices,
															StringArray *possibleValues) : propertyName(_propertyName), propertyElement(_propertyElement)
{
	l.setColour (Label::backgroundColourId, Colours::white);
	l.setColour (Label::textColourId, Colours::red.brighter());
	l.setText (propertyElement.getProperty(propertyName), dontSendNotification);
	addAndMakeVisible (&l);
}

CtrlrUnknownPropertyComponent::~CtrlrUnknownPropertyComponent()
{
}

void CtrlrUnknownPropertyComponent::resized()
{
	l.setBounds (0, 0, getWidth(), getHeight());
}

void CtrlrUnknownPropertyComponent::refresh()
{
	l.setText (propertyElement.getPropertyAsValue(propertyName, 0).toString(), dontSendNotification);
}
