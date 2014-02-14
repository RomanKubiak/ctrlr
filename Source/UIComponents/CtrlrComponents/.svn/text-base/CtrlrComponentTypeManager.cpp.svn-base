#include "stdafx.h"
#include "CtrlrComponents/CtrlrCustomComponent.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrComponentTypeManager.h"
#include "CtrlrComponents/Sliders/CtrlrSlider.h"
#include "CtrlrComponents/Sliders/CtrlrFixedSlider.h"
#include "CtrlrComponents/CtrlrCombo.h"
#include "CtrlrComponents/Buttons/CtrlrButton.h"
#include "CtrlrComponents/Buttons/CtrlrToggleButton.h"
#include "CtrlrComponents/Buttons/CtrlrImageButton.h"
#include "CtrlrComponents/Labels/CtrlrLabel.h"
#include "CtrlrComponents/Labels/CtrlrLCDLabel.h"
#include "CtrlrComponents/Groups/CtrlrGroup.h"
#include "CtrlrComponents/Labels/CtrlrImage.h"
#include "CtrlrComponents/Specials/CtrlrMidiKeyboard.h"
#include "CtrlrComponents/Sliders/CtrlrImageSlider.h"
#include "CtrlrComponents/Specials/CtrlrWaveform.h"
#include "CtrlrComponents/Buttons/CtrlrHyperlink.h"
#include "CtrlrComponents/Sliders/CtrlrFixedImageSlider.h"
#include "CtrlrComponents/Groups/CtrlrTabsComponent.h"
#include "CtrlrComponents/Specials/CtrlrXYSurface.h"
#include "CtrlrComponents/Statics/CtrlrArrow.h"
#include "CtrlrComponents/Specials/CtrlrListBox.h"
#include "CtrlrComponents/Specials/CtrlrFileListBox.h"
#include "CtrlrProcessor.h"

CtrlrComponent *CtrlrComponentTypeManager::createComponent (const Identifier& uiType, CtrlrModulator &owner)
{
	if (uiType == Ids::uiImageSlider)
		return (new CtrlrImageSlider(owner));
	if (uiType == Ids::uiSlider)
		return (new CtrlrSlider(owner));
	if (uiType == Ids::uiFixedSlider)
		return (new CtrlrFixedSlider(owner));
	if (uiType == Ids::uiFixedImageSlider)
		return (new CtrlrFixedImageSlider(owner));
	if (uiType == Ids::uiCombo)
		return (new CtrlrCombo(owner));
	if (uiType == Ids::uiToggleButton)
		return (new CtrlrToggleButton(owner));
	if (uiType == Ids::uiButton)
		return (new CtrlrButton(owner));
	if (uiType == Ids::uiImageButton)
		return (new CtrlrImageButton(owner));
	if (uiType == Ids::uiLabel)
		return (new CtrlrLabel(owner));
	if (uiType == Ids::uiLCDLabel)
		return (new CtrlrLCDLabel(owner));
	if (uiType == Ids::uiGroup)
		return (new CtrlrGroup(owner));
	if (uiType == Ids::uiImage)
		return (new CtrlrImage(owner));
	if (uiType == Ids::uiMidiKeyboard)
		return (new CtrlrMidiKeyboard(owner));
	if (uiType == Ids::uiCustomComponent)
		return (new CtrlrCustomComponent(owner));
	if (uiType == Ids::uiTabs)
		return (new CtrlrTabsComponent(owner));
	if (uiType == Ids::uiArrow)
		return (new CtrlrArrow(owner));
	if (uiType == Ids::uiWaveform)
		return (new CtrlrWaveform(owner));
	if (uiType == Ids::uiHyperlink)
		return (new CtrlrHyperlink(owner));
	if (uiType == Ids::uiXYSurface)
		return (new CtrlrXYSurface(owner));
	if (uiType == Ids::uiListBox)
		return (new CtrlrListBox(owner));
	if (uiType == Ids::uiFileListBox)
		return (new CtrlrFileListBox(owner));

	jassertfalse; // unknown type was specified, and i don't know how to create it
	return (new CtrlrCustomComponent(owner));
}

CtrlrComponent *CtrlrComponentTypeManager::createComponent (const ValueTree &savedState, CtrlrModulator &owner)
{
	if (savedState.hasProperty (Ids::uiType))
	{
		CtrlrComponent *c = createComponent(savedState.getProperty(Ids::uiType).toString(), owner);
		c->restoreState (savedState);
		return (c);
	}

	jassertfalse; // trying to restore a component with no type, can't do that
	return (0);
}

const Identifier CtrlrComponentTypeManager::findType (CtrlrComponent *componentToIdentify)
{
	if (dynamic_cast <CtrlrSlider*>(componentToIdentify) != 0)
		return (Ids::uiSlider);

	if (dynamic_cast <CtrlrFixedSlider*>(componentToIdentify) != 0)
		return (Ids::uiFixedSlider);

	if (dynamic_cast <CtrlrCombo*>(componentToIdentify) != 0)
		return (Ids::uiCombo);

	if (dynamic_cast <CtrlrToggleButton*>(componentToIdentify) != 0)
		return (Ids::uiToggleButton);

	if (dynamic_cast <CtrlrImageButton*>(componentToIdentify) != 0)
		return (Ids::uiImageButton);

	if (dynamic_cast <CtrlrButton*>(componentToIdentify) != 0)
		return (Ids::uiButton);

	if (dynamic_cast <CtrlrLabel*>(componentToIdentify) != 0)
		return (Ids::uiLabel);

	if (dynamic_cast <CtrlrLCDLabel*>(componentToIdentify) != 0)
		return (Ids::uiLCDLabel);

	if (dynamic_cast <CtrlrGroup*>(componentToIdentify) != 0)
		return (Ids::uiGroup);

	if (dynamic_cast <CtrlrImage*>(componentToIdentify) != 0)
		return (Ids::uiImage);

	if (dynamic_cast <CtrlrMidiKeyboard*>(componentToIdentify) != 0)
		return (Ids::uiMidiKeyboard);

	if (dynamic_cast <CtrlrImageSlider*>(componentToIdentify) != 0)
		return (Ids::uiImageSlider);

	if (dynamic_cast <CtrlrFixedImageSlider*>(componentToIdentify) != 0)
		return (Ids::uiFixedImageSlider);

	if (dynamic_cast <CtrlrTabsComponent*>(componentToIdentify) != 0)
		return (Ids::uiTabs);

	if (dynamic_cast <CtrlrArrow*>(componentToIdentify) != 0)
		return (Ids::uiArrow);

	if (dynamic_cast <CtrlrWaveform*>(componentToIdentify) != 0)
		return (Ids::uiWaveform);

	if (dynamic_cast <CtrlrHyperlink*>(componentToIdentify) != 0)
		return (Ids::uiHyperlink);

	if (dynamic_cast <CtrlrXYSurface*>(componentToIdentify) != 0)
		return (Ids::uiXYSurface);

	if (dynamic_cast <CtrlrListBox*>(componentToIdentify) != 0)
		return (Ids::uiListBox);

	if (dynamic_cast <CtrlrFileListBox*>(componentToIdentify) != 0)
		return (Ids::uiFileListBox);

	if (dynamic_cast <CtrlrCustomComponent*>(componentToIdentify) != 0)
		return (Ids::uiCustomComponent);

	return (Ids::uiNone);
}

bool CtrlrComponentTypeManager::isGroupingComponent(CtrlrComponent *componentToCheck)
{
	if (findType(componentToCheck) == Ids::uiTabs
		|| findType(componentToCheck) == Ids::uiGroup)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

CtrlrComponent *CtrlrComponentTypeManager::getParentIfGroupped(CtrlrComponent *childComponent)
{
	if (childComponent->getOwner().getOwner().getModulator (childComponent->getComponentGroup()))
	{
		return (childComponent->getOwner().getOwner().getModulator (childComponent->getComponentGroup())->getComponent());
	}

	if (childComponent->getProperty(Ids::componentTabName).toString() != String::empty)
	{
		return (childComponent->getOwner().getOwner().getModulator(childComponent->getProperty(Ids::componentTabName))->getComponent());
	}

	return (0);
}

const String CtrlrComponentTypeManager::sliderStyleToString (CtrlrComponentTypeManager::CtrlrSliderStyle style)
{
	switch (style)
	{
		case Slider::LinearHorizontal:
			return "LinearHorizontal";
		case Slider::LinearVertical:
			return "LinearVertical";
		case Slider::LinearBar:
			return "LinearBar";
		case Slider::Rotary:
			return "Rotary";
		case Slider::RotaryHorizontalDrag:
			return "RotaryHorizontalDrag";
		case Slider::RotaryVerticalDrag:
			return "RotaryVerticalDrag";
		case Slider::IncDecButtons:
			return "IncDecButtons";
		default:
			return "Unknown";
	}
}

const CtrlrComponentTypeManager::CtrlrSliderStyle CtrlrComponentTypeManager::sliderStringToStyle (const String& s)
{
	if (s == "LinearHorizontal")
		return LinearHorizontal;
	else if (s == "LinearVertical")
		return LinearVertical;
	else if (s == "LinearBar")
		return LinearBar;
	else if (s == "Rotary")
		return Rotary;
	else if (s == "RotaryHorizontalDrag")
		return RotaryHorizontalDrag;
	else if (s == "RotaryVerticalDrag")
		return RotaryVerticalDrag;
	else if (s == "IncDecButtons")
		return IncDecButtons;

	return RotaryVerticalDrag;
}

const PopupMenu CtrlrComponentTypeManager::getComponentMenu(const bool areItemsEnabled)
{
	PopupMenu m;
	m.addSectionHeader ("Add component");

	PopupMenu sliders;
	sliders.addItem (11, Ids::uiSlider.toString(), areItemsEnabled);
	sliders.addItem (12, Ids::uiImageSlider.toString(), areItemsEnabled);
	sliders.addItem (13, Ids::uiFixedSlider.toString(), areItemsEnabled);
	sliders.addItem (24, Ids::uiFixedImageSlider.toString(), areItemsEnabled);

	PopupMenu buttons;
	buttons.addItem (15, Ids::uiToggleButton.toString(), areItemsEnabled);
	buttons.addItem (16, Ids::uiButton.toString(), areItemsEnabled);
	buttons.addItem (17, Ids::uiImageButton.toString(), areItemsEnabled);
	buttons.addItem (14, Ids::uiCombo.toString(), areItemsEnabled);
	buttons.addItem (31, Ids::uiHyperlink.toString(), areItemsEnabled);

	PopupMenu statics;
	statics.addItem (18, Ids::uiLabel.toString(), areItemsEnabled);
	statics.addItem (26, Ids::uiLCDLabel.toString(), areItemsEnabled);
	statics.addItem (20, Ids::uiImage.toString(), areItemsEnabled);
	statics.addItem (28, Ids::uiArrow.toString(), areItemsEnabled);

	PopupMenu grouping;
	grouping.addItem (19, Ids::uiGroup.toString(), areItemsEnabled);
	grouping.addItem (27, Ids::uiTabs.toString(), areItemsEnabled);

	PopupMenu complex;
	complex.addItem (21, Ids::uiMidiKeyboard.toString(), areItemsEnabled);
	complex.addItem (29, Ids::uiCustomComponent.toString(), areItemsEnabled);
	complex.addItem (30, Ids::uiWaveform.toString(), areItemsEnabled);
	complex.addItem (32, Ids::uiXYSurface.toString(), areItemsEnabled);
	complex.addItem (33, Ids::uiListBox.toString(), areItemsEnabled);
	complex.addItem (34, Ids::uiFileListBox.toString(), areItemsEnabled);

	m.addSubMenu ("Sliders", sliders);
	m.addSubMenu ("Buttons", buttons);
	m.addSubMenu ("Statics", statics);
	m.addSubMenu ("Groups and views", grouping);
	m.addSubMenu ("Misc", complex);

	return (m);
}

const MidiKeyboardComponent::Orientation CtrlrComponentTypeManager::orientationFromString (const String &str)
{
	if (str == "horizontalKeyboard")
	{
		return (MidiKeyboardComponent::horizontalKeyboard);
	}
	if (str == "verticalKeyboardFacingLeft")
	{
		return (MidiKeyboardComponent::verticalKeyboardFacingLeft);
	}
	if (str == "verticalKeyboardFacingRight")
	{
		return (MidiKeyboardComponent::verticalKeyboardFacingRight);
	}

	return (MidiKeyboardComponent::horizontalKeyboard);
}

const bool CtrlrComponentTypeManager::isStatic(CtrlrComponent *componentToIdentify)
{
	if (	findType(componentToIdentify) == Ids::uiArrow
			|| findType(componentToIdentify) == Ids::uiGroup
			|| findType(componentToIdentify) == Ids::uiTabs
			|| findType(componentToIdentify) == Ids::uiImage
			|| findType(componentToIdentify) == Ids::uiLCDLabel
			|| findType(componentToIdentify) == Ids::uiLabel
			|| findType(componentToIdentify) == Ids::uiNone
			)
	{
		return (true);
	}

	return (false);
}

const bool CtrlrComponentTypeManager::isStatic(const Identifier &guiType)
{
	if (	guiType == Ids::uiArrow
			|| guiType == Ids::uiGroup
			|| guiType == Ids::uiTabs
			|| guiType == Ids::uiImage
			|| guiType == Ids::uiLCDLabel
			|| guiType == Ids::uiLabel
			|| guiType == Ids::uiNone
			)
	{
		return (true);
	}

	return (false);
}
