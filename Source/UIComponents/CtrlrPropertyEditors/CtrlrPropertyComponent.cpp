#include "stdafx.h"
#include "CtrlrMultiMidiPropertyComponent.h"
#include "CtrlrPropertyComponent.h"
#include "CtrlrUnknownPropertyComponent.h"
#include "CtrlrTextPropertyComponent.h"
#include "CtrlrExpressionProperty.h"
#include "CtrlrColourPropertyComponent.h"
#include "CtrlrFontPropertyComponent.h"
#include "CtrlrBooleanPropertyComponent.h"
#include "CtrlrSysExPropertyComponent.h"
#include "CtrlrLuaMethodProperty.h"
#include "CtrlrButtonPropertyComponent.h"
#include "CtrlrSliderPropertyComponent.h"
#include "CtrlrChoicePropertyComponent.h"
#include "CtrlrFilePropertyComponent.h"
#include "CtrlrTimestampProperty.h"
#include "CtrlrModulatorListProperty.h"
#include "CtrlrPanel/CtrlrPanel.h"

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

void CtrlrPropertyComponent::paint (Graphics &g)
{
	getLookAndFeel().drawPropertyComponentBackground (g, getLookAndFeel().getPropertyComponentContentPosition (*this).getX(), getHeight(), *this);

	g.setColour (Colours::black);

	if (isMouseOver(false) && !currentFont.isUnderlined())
	{
		currentFont.setUnderline(true);
	}
	else if (currentFont.isUnderlined())
	{
		currentFont.setUnderline(false);
	}

	g.setFont (currentFont);
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

void CtrlrPropertyComponent::mouseEnter (const MouseEvent &e)
{
	if (e.x < getLookAndFeel().getPropertyComponentContentPosition (*this).getX())
	{
		setMouseCursor (MouseCursor::PointingHandCursor);
		repaint();
	}
}

void CtrlrPropertyComponent::mouseExit (const MouseEvent &e)
{
	setMouseCursor (MouseCursor::NormalCursor);
	repaint();
}

void CtrlrPropertyComponent::mouseDown (const MouseEvent &e)
{
	if (e.x < getLookAndFeel().getPropertyComponentContentPosition (*this).getX())
	{
		/*if (panel)
		{
			if ((bool)panel->getOwner().getProperty (Ids::ctrlrPropertiesAreURLs) == true)
			{
				url = URL (urlString.replace ("%ELEMENT_TYPE%", getElementType().isEmpty() ? "" : (":"+getElementType()))
								.replace ("%ELEMENT_SUBTYPE%", getElementSubType().isEmpty() ? "" : (":"+getElementSubType()))
								.replace ("%ELEMENT_PROPERTY%", propertyName.toString()));
				url.launchInDefaultBrowser();
			}
		}*/
	}
}

void CtrlrPropertyComponent::mouseMove (const MouseEvent &e)
{
	if (e.x < getLookAndFeel().getPropertyComponentContentPosition (*this).getX())
	{
		if (getMouseCursor() != MouseCursor::PointingHandCursor)
		{
			setMouseCursor (MouseCursor::PointingHandCursor);
			repaint();
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
		return (String::empty);
	}
	else if (propertyElement.getType() == Ids::component)
	{
		return (propertyElement.getProperty("uiType"));
	}
	else if (propertyElement.getType() == Ids::modulator)
	{
		return (String::empty);
	}
	else if (propertyElement.getType() == Ids::midi)
	{
		return ("midi");
	}
	else if (propertyElement.getType() == Ids::uiPanelEditor)
	{
		return (String::empty);
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
		return (String::empty);
	}
	else
	{
		return (propertyElement.getType().toString());
	}
}
