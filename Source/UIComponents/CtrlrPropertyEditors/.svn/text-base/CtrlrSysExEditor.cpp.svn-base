#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  30 Sep 2011 1:50:29am

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

#include "CtrlrSysExEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "CtrlrProcessor.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrIDManager.h"
//[/MiscUserDefs]

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

    g.fillAll (Colours::white);

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
				ValueTree vendor = owner->getOwner().getCtrlrIDManager().getVendorTree().getChild (ret - 1024);
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
    ValueTree vendorTree = owner->getOwner().getCtrlrIDManager().getVendorTree();

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
    byteLabel->setColour (Label::outlineColourId, Colour (0x9e000000));
    byteLabel->setColour (TextEditor::textColourId, Colours::black);
    byteLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
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
	g.setColour (Colours::black);
	for (int i=0; i<16; i++)
	{
		g.drawFittedText (String ((16*n)+(i+1)), i*(w+gap), 0, w, 8, Justification::centred, 1);
	}

	g.fillRect (0,getHeight()-1,getWidth(),1);
}

void SysExRow::resized()
{
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrSysExEditor" componentName=""
                 parentClasses="public Component" constructorParams="Value &amp;_val"
                 variableInitialisers="val(_val)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="612"
                 initialHeight="256">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 0 0M 32" fill="linear: 0C 0, 0C 32, 0=ffffffff, 1=ffe2e2e2"
          hasStroke="0"/>
    <RECT pos="0 29 0M 3" fill="linear: 0C 29, 0C 32, 0=ffd6d6d6, 1=ff767676"
          hasStroke="0"/>
  </BACKGROUND>
  <SLIDER name="messageLength" id="6818d21a3ac3cc2c" memberName="messageLength"
          virtualName="" explicitFocusOrder="0" pos="72 4 88 22" min="2"
          max="64" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="32" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="3e46e6dc309f352d" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="8 8 55 16" edTextCol="ff000000" edBkgCol="0"
         labelText="Length" editableSingleClick="1" editableDoubleClick="1"
         focusDiscardsChanges="1" fontname="Default font" fontsize="14"
         bold="1" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
