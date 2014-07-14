#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  13 Oct 2011 10:49:23pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "CtrlrCombo.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "CtrlrProcessor.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrComponentTypeManager.h"
#include "CtrlrLog.h"
//[/MiscUserDefs]

//==============================================================================
CtrlrCombo::CtrlrCombo (CtrlrModulator &owner)
    : CtrlrComponent(owner), lf(*this),
      ctrlrCombo (0)
{
    addAndMakeVisible (ctrlrCombo = new ComboBox (L"ctrlrCombo"));
    ctrlrCombo->setEditableText (false);
    ctrlrCombo->setJustificationType (Justification::centred);
    ctrlrCombo->setTextWhenNothingSelected (L"(no selection)");
    ctrlrCombo->setTextWhenNoChoicesAvailable (L"(no choices)");
    ctrlrCombo->addListener (this);


    //[UserPreSize]
	ctrlrCombo->setLookAndFeel (&lf);
	componentTree.addListener (this);

	setProperty (Ids::uiComboArrowColour, "0xff0000ff");
	setProperty (Ids::uiComboOutlineColour, "0xff0000ff");
	setProperty (Ids::uiComboTextColour, "0xff000000");
	setProperty (Ids::uiComboTextJustification, "centred");
	setProperty (Ids::uiComboFont, FONT2STR (Font(14)));
	setProperty (Ids::uiComboMenuFont, FONT2STR (Font(16)));
	setProperty (Ids::uiComboButtonColour, "0xff0000ff");
	setProperty (Ids::uiComboBgColour, "0xffffffff");
	setProperty (Ids::uiComboMenuBackgroundColour, "0xfff0f0f0");
	setProperty (Ids::uiComboMenuFontColour, "0xff000000");
	setProperty (Ids::uiComboMenuHighlightColour, Colours::lightblue.toString());
	setProperty (Ids::uiComboMenuFontHighlightedColour, "0xff232323");
	setProperty (Ids::uiComboContent, "");
	setProperty (Ids::uiComboMenuBackgroundRibbed, true);
	setProperty (Ids::uiComboButtonGradient, false);
	setProperty (Ids::uiComboButtonGradientColour1, Colours::blue.toString());
	setProperty (Ids::uiComboButtonGradientColour2, Colours::darkblue.toString());
	setProperty (Ids::uiComboButtonWidthOverride, false);
	setProperty (Ids::uiComboButtonWidth, 16);
	setProperty (Ids::uiComboDynamicContent, 0);
    //[/UserPreSize]

    setSize (88, 32);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrCombo::~CtrlrCombo()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (ctrlrCombo);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrCombo::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrCombo::resized()
{
    ctrlrCombo->setBounds (2, 2, getWidth() - 4, getHeight() - 4);
    //[UserResized] Add your own custom resize handling here..
	ctrlrCombo->setBounds (getUsableRect());
    //[/UserResized]
}

void CtrlrCombo::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == ctrlrCombo)
    {
        //[UserComboBoxCode_ctrlrCombo] -- add your combo box handling code here..
		setComponentValue (ctrlrCombo->getSelectedItemIndex(), true);
        //[/UserComboBoxCode_ctrlrCombo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void CtrlrCombo::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    //[/UserCode_mouseDown]
}

bool CtrlrCombo::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyPressed]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
const double CtrlrCombo::getComponentMaxValue()
{
	return (valueMap.getNonMappedMax());
}

const double CtrlrCombo::getComponentValue()
{
	return (ctrlrCombo->getSelectedId()-1);
}

const int CtrlrCombo::getComponentMidiValue()
{
	return (valueMap.getMappedValue(ctrlrCombo->getSelectedId() - 1));
}

const String CtrlrCombo::getComponentText()
{
	return (ctrlrCombo->getText());
}

void CtrlrCombo::setComponentValue (const double newValue, const bool sendChangeMessage)
{
	ctrlrCombo->setSelectedId (newValue+1, sendNotification);

	if (sendChangeMessage)
	{
		owner.getProcessor().setValueFromGUI (newValue, sendChangeMessage);
	}
}

void CtrlrCombo::comboContentChanged()
{
	if ((int)getProperty(Ids::uiComboDynamicContent) > 0)
		return;

	valueMap.copyFrom (owner.getProcessor().setValueMap (getProperty(Ids::uiComboContent)));
	valueMap.fillCombo (*ctrlrCombo, true);
}

void CtrlrCombo::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiComboContent)
	{
		comboContentChanged();
	}
	else if (property == Ids::uiComboBgColour)
	{
		ctrlrCombo->setColour (ComboBox::backgroundColourId, VAR2COLOUR(getProperty(Ids::uiComboBgColour)));
	}
	else if (property == Ids::uiComboButtonColour)
	{
		ctrlrCombo->setColour (ComboBox::buttonColourId, VAR2COLOUR(getProperty(Ids::uiComboButtonColour)));
	}
	else if (property == Ids::uiComboTextColour)
	{
		ctrlrCombo->setColour (ComboBox::textColourId, VAR2COLOUR(getProperty(Ids::uiComboTextColour)));
	}
	else if (property == Ids::uiComboOutlineColour)
	{
		ctrlrCombo->setColour (ComboBox::outlineColourId, VAR2COLOUR(getProperty(Ids::uiComboOutlineColour)));
	}
	else if (property == Ids::uiComboArrowColour)
	{
		ctrlrCombo->setColour (ComboBox::arrowColourId, VAR2COLOUR(getProperty(Ids::uiComboArrowColour)));
	}
	else if (property == Ids::uiComboTextJustification)
	{
		ctrlrCombo->setJustificationType (justificationFromProperty(getProperty(property)));
	}
	else if (property == Ids::uiComboFont
		|| property == Ids::uiComboMenuBackgroundColour
		|| property == Ids::uiComboMenuFont
		|| property == Ids::uiComboMenuFontHighlightedColour
		|| property == Ids::uiComboMenuFontColour
		|| property == Ids::uiComboMenuHighlightColour
		|| property == Ids::uiComboButtonWidthOverride
		|| property == Ids::uiComboButtonWidth)
	{
		ctrlrCombo->setLookAndFeel(0);
		ctrlrCombo->setLookAndFeel(&lf);
	}
	else if (property == Ids::uiComboDynamicContent)
	{
		fillContent(getProperty(property));
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

bool CtrlrCombo::keyPressed (const KeyPress& key, Component* originatingComponent)
{
	if (getParentComponent())
	{
		CtrlrPanelCanvas *canvas = dynamic_cast<CtrlrPanelCanvas*>(getParentComponent());
		if (canvas)
		{
			canvas->keyPressed (key, this);
		}
	}
	return (false);
}

void CtrlrCombo::setComponentText (const String &componentText)
{
	ctrlrCombo->setText (componentText);
}

void CtrlrCombo::fillContent(const int contentType)
{
	Array<File> files;
	const String prewviousContent = ctrlrCombo->getText();

	switch (contentType)
	{
		case 1:
			for (int i=0; i<owner.getOwner().getModulators().size(); i++)
			{
				valueMap.setPair (i, i, owner.getOwner().getModulatorByIndex(i)->getName());
			}
			owner.getProcessor().setValueMap (valueMap);
			valueMap.fillCombo (*ctrlrCombo, true);
			ctrlrCombo->setText (prewviousContent, dontSendNotification);
			break;

		case 2:
			File::findFileSystemRoots(files);
			for (int i=0; i<files.size(); i++)
			{
				valueMap.setPair (i, i, files[i].getFullPathName());
			}
			owner.getProcessor().setValueMap (valueMap);
			valueMap.fillCombo (*ctrlrCombo, true);
			ctrlrCombo->setText (prewviousContent, dontSendNotification);
			break;
		default:
			comboContentChanged();
			break;
	}
}

void CtrlrCombo::panelEditModeChanged(const bool isInEditMode)
{
	if (isInEditMode)
	{
		if ((bool)owner.getOwner().getEditor()->getProperty (Ids::uiPanelDisabledOnEdit) == true)
		{
			ctrlrCombo->setEnabled (false);
		}
	}
	else
	{
		if ((bool)owner.getOwner().getEditor()->getProperty (Ids::uiPanelDisabledOnEdit) == true)
		{
			ctrlrCombo->setEnabled (true);
		}

		if ((int)getProperty (Ids::uiComboDynamicContent) > 0)
		{
			fillContent(getProperty(Ids::uiComboDynamicContent));
		}
	}
}

Font CtrlrCombo::CtrlrComboLF::getComboBoxFont (ComboBox &box)
{
	return (owner.getOwner().getOwner().getOwner().getFontManager().getFontFromString (owner.getProperty(Ids::uiComboFont)));
}

Font CtrlrCombo::CtrlrComboLF::getPopupMenuFont ()
{
	return (owner.getOwner().getOwner().getOwner().getFontManager().getFontFromString (owner.getProperty(Ids::uiComboMenuFont)));
}

void CtrlrCombo::CtrlrComboLF::drawPopupMenuBackground (Graphics &g, int width, int height)
{
	const Colour background = VAR2COLOUR(owner.getProperty(Ids::uiComboMenuBackgroundColour));

    g.fillAll (background);

	if (owner.getProperty (Ids::uiComboMenuBackgroundRibbed))
	{
    g.setColour (background.overlaidWith (Colour (0x2badd8e6)));

    for (int i = 0; i < height; i += 3)
        g.fillRect (0, i, width, 1);

#if ! JUCE_MAC
    g.setColour (findColour (PopupMenu::textColourId).withAlpha (0.6f));
    g.drawRect (0, 0, width, height);
#endif
	}
}

//void CtrlrCombo::CtrlrComboLF::drawPopupMenuItem (Graphics &g, int width, int height, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const String &text, const String &shortcutKeyText, Image *image, const Colour *const textColourToUse)
void CtrlrCombo::CtrlrComboLF::drawPopupMenuItem (Graphics &g, const Rectangle<int>& area,
                            bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu,
                            const String& text, const String& shortcutKeyText,
                            const Drawable* icon, const Colour* textColourToUse)
{
	const int width = area.getWidth();
	const int height = area.getHeight();

	const float halfH = height * 0.5f;

    if (isSeparator)
    {
        const float separatorIndent = 5.5f;

        g.setColour (Colour (0x33000000));
        g.drawLine (separatorIndent, halfH, width - separatorIndent, halfH);

        g.setColour (Colour (0x66ffffff));
        g.drawLine (separatorIndent, halfH + 1.0f, width - separatorIndent, halfH + 1.0f);
    }
    else
    {
		Colour textColour = VAR2COLOUR(owner.getProperty(Ids::uiComboMenuFontColour));

        if (textColourToUse != nullptr)
		{
			_DBG("Using passed in colour: "+textColourToUse->toString());
            textColour = *textColourToUse;
		}

        if (isHighlighted)
        {
			g.setColour (VAR2COLOUR(owner.getProperty(Ids::uiComboMenuHighlightColour)));
            g.fillRect (1, 1, width - 2, height - 2);

            g.setColour (VAR2COLOUR(owner.getProperty(Ids::uiComboMenuFontHighlightedColour)));
        }
        else
        {
            g.setColour (textColour);
        }

        if (! isActive)
            g.setOpacity (0.3f);

		Font font = owner.getOwner().getOwner().getOwner().getFontManager().getFontFromString (owner.getProperty(Ids::uiComboMenuFont));

        if (font.getHeight() > height / 1.3f)
            font.setHeight (height / 1.3f);

        g.setFont (font);

        const int leftBorder = (height * 5) / 4;
        const int rightBorder = 4;

        if (icon != nullptr)
        {
			icon->drawWithin (g, Rectangle<float>(2, 1, leftBorder - 4, height - 2), RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
        }
        else if (isTicked)
        {
            const Path tick (getTickShape (1.0f));
            const float th = font.getAscent();
            const float ty = halfH - th * 0.5f;

            g.fillPath (tick, tick.getTransformToScaleToFit (2.0f, ty, (float) (leftBorder - 4),
                                                             th, true));
        }

        g.drawFittedText (text,
                          leftBorder, 0,
                          width - (leftBorder + rightBorder), height,
                          Justification::centredLeft, 1);

        if (shortcutKeyText.isNotEmpty())
        {
            Font f2 (font);
            f2.setHeight (f2.getHeight() * 0.75f);
            f2.setHorizontalScale (0.95f);
            g.setFont (f2);

            g.drawText (shortcutKeyText,
                        leftBorder,
                        0,
                        width - (leftBorder + rightBorder + 4),
                        height,
                        Justification::centredRight,
                        true);
        }

        if (hasSubMenu)
        {
            const float arrowH = 0.6f * getPopupMenuFont().getAscent();
            const float x = width - height * 0.6f;

            Path p;
            p.addTriangle (x, halfH - arrowH * 0.5f,
                           x, halfH + arrowH * 0.5f,
                           x + arrowH * 0.6f, halfH);

            g.fillPath (p);
        }
    }
}

void CtrlrCombo::CtrlrComboLF::drawComboBox (Graphics& g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox& box)
{
	int bw=buttonW;
	int bx=buttonX;
	const float outlineThickness = isButtonDown ? 1.2f : 0.5f;

	g.fillAll (box.findColour (ComboBox::backgroundColourId));
    g.setColour (box.findColour (ComboBox::outlineColourId));
    g.drawRect (0, 0, width, height);

	if ((bool)owner.getProperty (Ids::uiComboButtonWidthOverride) == true)
	{
		bw = owner.getProperty (Ids::uiComboButtonWidth);
		bx = width - bw;
	}

    const Colour baseColour (createBaseColour (box.findColour (ComboBox::buttonColourId),
                                                                   box.hasKeyboardFocus (true),
                                                                   false, isButtonDown)
                                .withMultipliedAlpha (1.0f));

	if ((bool)owner.getProperty (Ids::uiComboButtonGradient) == true)
	{
		g.setGradientFill (
							ColourGradient (
												VAR2COLOUR(owner.getProperty(Ids::uiComboButtonGradientColour1)),
												buttonX + outlineThickness,
												buttonY + outlineThickness,
												VAR2COLOUR(owner.getProperty(Ids::uiComboButtonGradientColour2)),
												buttonX + outlineThickness,
												(buttonY + outlineThickness) + (buttonH - outlineThickness * 2.0f),
												false
											)
						);

		g.fillRect (buttonX + outlineThickness, buttonY + outlineThickness, buttonW - outlineThickness * 2.0f, buttonH - outlineThickness * 2.0f);
	}
	else
	{
		drawGlassLozenge (g,
							bx + outlineThickness,
							buttonY + outlineThickness,
							bw - outlineThickness * 2.0f,
							buttonH - outlineThickness * 2.0f,
							baseColour,
							outlineThickness, -1.0f,
							true,
							true,
							true,
							true);
	}

	const float arrowX = 0.3f;
    const float arrowH = 0.2f;

    Path p;
    p.addTriangle (	bx + bw * 0.5f,
					buttonY + buttonH * (0.45f - arrowH),
					bx + bw * (1.0f - arrowX), buttonY + buttonH * 0.45f,
                    bx + bw * arrowX,          buttonY + buttonH * 0.45f);

    p.addTriangle (	bx + bw * 0.5f,
					buttonY + buttonH * (0.55f + arrowH),
                    bx + bw * (1.0f - arrowX), buttonY + buttonH * 0.55f,
                    bx + bw * arrowX,          buttonY + buttonH * 0.55f);

    g.setColour (box.findColour (ComboBox::arrowColourId));
    g.fillPath (p);
}

const Colour CtrlrCombo::CtrlrComboLF::createBaseColour (const Colour& buttonColour, const bool hasKeyboardFocus, const bool isMouseOverButton, const bool isButtonDown)
{
	const float sat = hasKeyboardFocus ? 1.3f : 0.9f;
	const Colour baseColour (buttonColour.withMultipliedSaturation (sat));

	if (isButtonDown)
		return baseColour.contrasting (0.2f);
	else if (isMouseOverButton)
		return baseColour.contrasting (0.1f);

	return baseColour;
}

void CtrlrCombo::CtrlrComboLF::positionComboBoxText (ComboBox& box, Label& label)
{
	int bw			= owner.getProperty (Ids::uiComboButtonWidth);

	if ((bool)owner.getProperty (Ids::uiComboButtonWidthOverride) == true)
	{
		label.setBounds (1, 1, box.getWidth() - bw, box.getHeight() - 2);
	}
	else
	{
		label.setBounds (1, 1, box.getWidth() + 3 - box.getHeight(), box.getHeight() - 2);
	}

    label.setFont (getComboBoxFont (box));
}

int CtrlrCombo::getSelectedId()
{
	return (ctrlrCombo->getSelectedId());
}

int CtrlrCombo::getSelectedItemIndex()
{
	return (ctrlrCombo->getSelectedItemIndex());
}

void CtrlrCombo::setSelectedId(const int id, const bool dontNotify)
{
	ctrlrCombo->setSelectedId (id, dontNotify ? dontSendNotification : sendNotification);
}

void CtrlrCombo::setSelectedItemIndex(const int index, const bool dontNotify)
{
	ctrlrCombo->setSelectedItemIndex (index, dontNotify ? dontSendNotification : sendNotification);
}

const String CtrlrCombo::getText()
{
	return (ctrlrCombo->getText());
}

void CtrlrCombo::setText(const String &text, const bool dontNotify)
{
	return (ctrlrCombo->setText(text, dontNotify ? dontSendNotification : sendNotification));
}

void CtrlrCombo::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrCombo, bases<CtrlrComponent,CtrlrLuaObject> >("CtrlrCombo")
			.def("getOwnedComboBox", &CtrlrCombo::getOwnedComboBox)
			.def("getSelectedId", &CtrlrCombo::getSelectedId)
			.def("getSelectedItemIndex", &CtrlrCombo::getSelectedItemIndex)
			.def("setSelectedId", &CtrlrCombo::setSelectedId)
			.def("setSelectedItemIndex", &CtrlrCombo::setSelectedItemIndex)
			.def("getText", &CtrlrCombo::getText)
			.def("setText", &CtrlrCombo::setText)
	];
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrCombo" componentName=""
                 parentClasses="public CtrlrComponent, public KeyListener" constructorParams="CtrlrModulator &amp;owner"
                 variableInitialisers="CtrlrComponent(owner), lf(*this)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330000013" fixedSize="1"
                 initialWidth="88" initialHeight="32">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffff"/>
  <COMBOBOX name="ctrlrCombo" id="8c7a382fb899f6c2" memberName="ctrlrCombo"
            virtualName="" explicitFocusOrder="0" pos="2 2 4M 4M" editable="0"
            layout="36" items="" textWhenNonSelected="(no selection)" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
