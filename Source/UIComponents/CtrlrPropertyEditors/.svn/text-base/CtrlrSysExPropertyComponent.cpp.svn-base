#include "stdafx.h"
#include "CtrlrSysExEditor.h"
#include "CtrlrSysExPropertyComponent.h"
#include "CtrlrPanel/CtrlrPanel.h"

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
	sysexPreview->setColour (Label::backgroundColourId, Colours::white);
	sysexPreview->setColour (Label::outlineColourId, findColour (ComboBox::outlineColourId));

    addAndMakeVisible (editButton = new TextButton (L"editButton"));
    editButton->setButtonText (L"Edit");
    editButton->addListener (this);

    addAndMakeVisible (copy = new ImageButton (String::empty));
    copy->setTooltip (L"Copy to clipboard");
    copy->setButtonText (L"new button");
    copy->addListener (this);

    copy->setImages (false, true, true,
                     IMAGE(ico_copy_png), 0.6500f, Colour (0x0),
                     IMAGE(ico_copy_png), 0.8500f, Colour (0x0),
                     IMAGE(ico_copy_png), 1.0000f, Colour (0x0));

    addAndMakeVisible (paste = new ImageButton (String::empty));
    paste->setTooltip (L"Paste from clipboard");
    paste->setButtonText (L"new button");
    paste->addListener (this);

    paste->setImages (false, true, true,
                      IMAGE(ico_paste_png), 0.6500f, Colour (0x0),
                      IMAGE(ico_paste_png), 0.8500f, Colour (0x0),
                      IMAGE(ico_paste_png), 1.0000f, Colour (0x0));

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
		o.dialogBackgroundColour 		= Colours::whitesmoke;
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
