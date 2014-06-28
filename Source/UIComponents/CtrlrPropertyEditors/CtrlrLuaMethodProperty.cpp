#include "stdafx.h"
#include "CtrlrLuaManager.h"
#include "CtrlrMacros.h"
#include "CtrlrLua/MethodEditor/CtrlrLuaMethodEditor.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrLuaMethodProperty.h"

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
    methodSelectorCombo->setTextWhenNothingSelected (String::empty);
    methodSelectorCombo->setTextWhenNoChoicesAvailable (L"(no choices)");
    methodSelectorCombo->addListener (this);

    addAndMakeVisible (editMethodButton = new ImageButton (L"editMethodButton"));
    editMethodButton->setTooltip (L"Edit selected method");
    editMethodButton->setButtonText (L"new button");
    editMethodButton->addListener (this);

    editMethodButton->setImages (false, true, true,
                                 Image(), 1.0000f, Colour (0x0),
                                 Image(), 1.0000f, Colour (0x0),
                                 Image(), 1.0000f, Colour (0x0));
    addAndMakeVisible (newMethodButton = new ImageButton (L"newMethodButton"));
    newMethodButton->setTooltip (L"Add new method");
    newMethodButton->setButtonText (L"new button");
    newMethodButton->addListener (this);

    newMethodButton->setImages (false, true, true,
                                Image(), 1.0000f, Colour (0x0),
                                Image(), 1.0000f, Colour (0x0),
                                Image(), 1.0000f, Colour (0x0));
    addAndMakeVisible (deleteMethodButton = new ImageButton (L"deleteMethodButton"));
    deleteMethodButton->setTooltip (L"Remove selected method");
    deleteMethodButton->setButtonText (L"new button");
    deleteMethodButton->addListener (this);

    deleteMethodButton->setImages (false, true, true,
                                   Image(), 1.0000f, Colour (0x0),
                                   Image(), 1.0000f, Colour (0x0),
                                   Image(), 1.0000f, Colour (0x0));

	editMethodButton->setMouseCursor(MouseCursor::PointingHandCursor);
	newMethodButton->setMouseCursor(MouseCursor::PointingHandCursor);
	deleteMethodButton->setMouseCursor(MouseCursor::PointingHandCursor);

	
	editMethodButton->setImages (false, true, true,
									IMAGE(ico_edit_document_png), 0.6500f, Colour (0x0),
									IMAGE(ico_edit_document_png), 0.8500f, Colour (0x0),
									IMAGE(ico_edit_document_png), 1.0000f, Colour (0x0));

	newMethodButton->setImages (false, true, true,
									IMAGE(ico_new_document_png), 0.6500f, Colour (0x0),
									IMAGE(ico_new_document_png), 0.8500f, Colour (0x0),
									IMAGE(ico_new_document_png), 1.0000f, Colour (0x0));

	deleteMethodButton->setImages (false, true, true,
									IMAGE(ico_delete_png), 0.6500f, Colour (0x0),
									IMAGE(ico_delete_png), 0.8500f, Colour (0x0),
									IMAGE(ico_delete_png), 1.0000f, Colour (0x0));
									
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
				owner->getCtrlrLuaManager().getMethodManager().addMethod (ValueTree(), w.getTextEditorContents("methodName"), String::empty, id.toString());
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
