#include "stdafx.h"
#include "CtrlrUtilities.h"
#include "CtrlrWindowManagers/CtrlrManagerWindowManager.h"
#include "CtrlrMultiMidiPropertyComponent.h"

CtrlrMultiMidiPropertyComponent::CtrlrMultiMidiPropertyComponent (const Value &_valueToControl)
    : valueToControl(_valueToControl),
      add (0),
      remove (0),
      list (0),
      copy (0),
      paste (0),
      insert (0)
{
    addAndMakeVisible (add = new ImageButton (String::empty));
    add->setTooltip (L"Add message");
    add->setButtonText (L"new button");
    add->addListener (this);

    add->setImages (false, true, true,
                    Image(), 0.6500f, Colour (0x0),
                    Image(), 0.8500f, Colour (0x0),
                    Image(), 1.0000f, Colour (0x0));
    addAndMakeVisible (remove = new ImageButton (String::empty));
    remove->setTooltip (L"Remove selected message");
    remove->setButtonText (L"new button");
    remove->addListener (this);

    remove->setImages (false, true, true,
                       Image(), 0.6500f, Colour (0x0),
                       Image(), 0.8500f, Colour (0x0),
                       Image(), 1.0000f, Colour (0x0));
    addAndMakeVisible (list = new ListBox ("list", this));

    addAndMakeVisible (copy = new ImageButton (String::empty));
    copy->setTooltip (L"Copy to clipboard");
    copy->setButtonText (L"new button");
    copy->addListener (this);

    copy->setImages (false, true, true,
                     Image(), 0.6500f, Colour (0x0),
                     Image(), 0.8500f, Colour (0x0),
                     Image(), 1.0000f, Colour (0x0));
    addAndMakeVisible (paste = new ImageButton (String::empty));
    paste->setTooltip (L"Paste from clipboard");
    paste->setButtonText (L"new button");
    paste->addListener (this);

    paste->setImages (false, true, true,
                      Image(), 0.6500f, Colour (0x0),
                      Image(), 0.8500f, Colour (0x0),
                      Image(), 1.0000f, Colour (0x0));
    addAndMakeVisible (insert = new ImageButton (String::empty));
    insert->setTooltip (L"Insert pre-defined");
    insert->setButtonText (L"new button");
    insert->addListener (this);

		insert->setImages (false, true, true,
                       Image(), 1.0000f, Colour (0x0),
                       Image(), 1.0000f, Colour (0x0),
                       Image(), 1.0000f, Colour (0x0));

		add->setImages (false, true, true,
						IMAGE(ico_new_document_png), 0.6500f, Colour (0x0),
						IMAGE(ico_new_document_png), 0.8500f, Colour (0x0),
						IMAGE(ico_new_document_png), 1.0000f, Colour (0x0));
		copy->setImages (false, true, true,
						IMAGE(ico_copy_png), 0.6500f, Colour (0x0),
						IMAGE(ico_copy_png), 0.8500f, Colour (0x0),
						IMAGE(ico_copy_png), 1.0000f, Colour (0x0));
		paste->setImages (false, true, true,
						IMAGE(ico_paste_png), 0.6500f, Colour (0x0),
						IMAGE(ico_paste_png), 0.8500f, Colour (0x0),
						IMAGE(ico_paste_png), 1.0000f, Colour (0x0));
		remove->setImages (false, true, true,
						IMAGE(ico_delete_png), 0.6500f, Colour (0x0),
						IMAGE(ico_delete_png), 0.8500f, Colour (0x0),
						IMAGE(ico_delete_png), 1.0000f, Colour (0x0));
		insert->setImages (false, true, true,
						IMAGE(ico_import_document_png), 0.6500f, Colour (0x0),
						IMAGE(ico_import_document_png), 0.8500f, Colour (0x0),
						IMAGE(ico_import_document_png), 1.0000f, Colour (0x0));

	list->setRowHeight (14);
	add->setMouseCursor (MouseCursor::PointingHandCursor);
	remove->setMouseCursor (MouseCursor::PointingHandCursor);
	copy->setMouseCursor (MouseCursor::PointingHandCursor);
	paste->setMouseCursor (MouseCursor::PointingHandCursor);
	insert->setMouseCursor (MouseCursor::PointingHandCursor);
	remove->setTooltip ("Remove selected");
	loadAdditionalTemplates(File::nonexistent);
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
			const String data = templates.getValue (templates.getAllKeys() [ret-1], String::empty);
			if (data != String::empty)
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
		l = new Label (String::empty, values[rowNumber]);
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

	ScopedPointer <XmlElement> dynamicXml(dynamicTemplates.getDocumentElement());
	ScopedPointer <XmlElement> staticXml(staticTemplates.getDocumentElement());

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
