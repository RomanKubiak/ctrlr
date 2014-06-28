#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  1 Jul 2011 6:04:12pm

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
#pragma warning(disable:4244)
#include "CtrlrLuaObjectWrapper.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "Lua/CtrlrLuaManager.h"
#include "CtrlrApplicationWindow/CtrlrLookAndFeel.h"
//[/Headers]

#include "CtrlrTabsComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrUtilities.h"

CtrlrTabsLF::CtrlrTabsLF(CtrlrTabsComponent &_owner) : owner(_owner)
{
}

int CtrlrTabsLF::getTabButtonBestWidth (int tabIndex,
                                        const String& text,
                                        int tabDepth,
                                        Button &button)
{
	Font f = owner.getOwner().getOwner().getOwner().getFontManager().getFontFromString (owner.getProperty(Ids::uiTabsTabFont));
    return f.getStringWidth (text.trim()) + getTabButtonOverlap (tabDepth) * 2;
}



void CtrlrTabsLF::drawTabButtonText (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown)
{
	const Rectangle<float> area (button.getTextArea().toFloat());

    float length = area.getWidth();
    float depth  = area.getHeight();

    if (button.getTabbedButtonBar().isVertical())
        std::swap (length, depth);

	Font otherTabFont  = owner.getOwner().getOwner().getOwner().getFontManager().getFontFromString (owner.getProperty(Ids::uiTabsTabFont));
	Font activeTabFont = owner.getOwner().getOwner().getOwner().getFontManager().getFontFromString (owner.getProperty(Ids::uiTabsFrontTabFont));

    otherTabFont.setUnderline (button.hasKeyboardFocus (false));
	activeTabFont.setUnderline (button.hasKeyboardFocus (false));

    GlyphArrangement textLayout;
	textLayout.addFittedText (button.isFrontTab() ? activeTabFont : otherTabFont, button.getButtonText().trim(),
				                0.0f, 0.0f, (float) length, (float) depth,
								Justification::centred,
								jmax<int> (1, depth / 12));
    AffineTransform t;

    switch (button.getTabbedButtonBar().getOrientation())
    {
        case TabbedButtonBar::TabsAtLeft:   t = t.rotated (float_Pi * -0.5f).translated (area.getX(), area.getBottom()); break;
        case TabbedButtonBar::TabsAtRight:  t = t.rotated (float_Pi *  0.5f).translated (area.getRight(), area.getY()); break;
        case TabbedButtonBar::TabsAtTop:
        case TabbedButtonBar::TabsAtBottom: t = t.translated (area.getX(), area.getY()); break;
        default:                            jassertfalse; break;
    }

    Colour col;

    if (button.isFrontTab() && (button.isColourSpecified (TabbedButtonBar::frontTextColourId)
                                    || isColourSpecified (TabbedButtonBar::frontTextColourId)))
        col = findColour (TabbedButtonBar::frontTextColourId);
    else if (button.isColourSpecified (TabbedButtonBar::tabTextColourId)
                 || isColourSpecified (TabbedButtonBar::tabTextColourId))
        col = findColour (TabbedButtonBar::tabTextColourId);
    else
        col = button.getTabBackgroundColour().contrasting();

    const float alpha = button.isEnabled() ? ((isMouseOver || isMouseDown) ? 1.0f : 0.8f) : 0.3f;

    g.setColour (col.withMultipliedAlpha (alpha));
    textLayout.draw (g, t);
}

void CtrlrTabsLF::fillTabButtonShape (TabBarButton& button, Graphics& g, const Path& path,  bool /*isMouseOver*/, bool /*isMouseDown*/)
{
	const Colour tabBackground (button.getTabBackgroundColour());
    const bool isFrontTab = button.isFrontTab();

    g.setColour (isFrontTab ? tabBackground
                            : tabBackground.withMultipliedAlpha (0.9f));

    g.fillPath (path);

    g.setColour (button.findColour (isFrontTab ? TabbedButtonBar::frontOutlineColourId
                                               : TabbedButtonBar::tabOutlineColourId, false)
                    .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));

    g.strokePath (path, PathStrokeType (isFrontTab ? owner.getProperty(Ids::uiTabsFrontTabOutline) : owner.getProperty(Ids::uiTabsTabOutline)));
}




CtrlrTabsContentComponent::CtrlrTabsContentComponent(const ValueTree &_tabTree, CtrlrTabsComponent &_owner)
	: tabTree(_tabTree), owner(_owner)
{
	tabTree.addListener(this);
	tabBackgroundImage = owner.getOwner().getOwner().getResourceManager().getResourceAsImage(getProperty(Ids::uiTabsTabBackgroundImage));
}

CtrlrTabsContentComponent::~CtrlrTabsContentComponent()
{
	tabTree.removeListener(this);
}

const var &CtrlrTabsContentComponent::getProperty (const Identifier& name) const
{
	return (tabTree.getProperty(name));
}

void CtrlrTabsContentComponent::resized()
{
}

void CtrlrTabsContentComponent::paint (Graphics &g)
{
	g.fillAll(VAR2COLOUR(getProperty(Ids::uiTabsTabContentBackgroundColour)));

	if (tabBackgroundImage.isValid())
	{
		if ((int)getProperty (Ids::uiTabsTabBackgroundImageLayout) == 8192)
		{
			g.setTiledImageFill (tabBackgroundImage, 0, 0, (float)getProperty (Ids::uiTabsTabBackgroundImageAlpha)/255.0f);
			g.fillAll();
		}
		else
		{
			g.setColour (Colours::black.withAlpha ((float)getProperty (Ids::uiTabsTabBackgroundImageAlpha)/255.0f));
			g.drawImageWithin (tabBackgroundImage,
								0,
								0,
								getWidth(),
								getHeight(),
								RectanglePlacement(getProperty (Ids::uiTabsTabBackgroundImageLayout)));
		}
	}
}

void CtrlrTabsContentComponent::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiTabsTabBackgroundImage)
	{
		tabBackgroundImage = owner.getOwner().getOwner().getResourceManager().getResourceAsImage(getProperty(Ids::uiTabsTabBackgroundImage));
	}

	repaint();
}

void CtrlrTabsContentComponent::parentNameChanged(const String &newName)
{
	for (int i=0; i<getNumChildComponents(); i++)
	{
		CtrlrComponent *c = dynamic_cast<CtrlrComponent*>(getChildComponent(i));
		if (c!=0)
		{
			c->setProperty (Ids::componentTabName, newName);
		}
	}
}

CtrlrTabsInternal::CtrlrTabsInternal(CtrlrTabsComponent &_owner) : owner(_owner), TabbedComponent(TabbedButtonBar::TabsAtTop)
{
}

CtrlrTabsInternal::~CtrlrTabsInternal()
{
}

void CtrlrTabsInternal::currentTabChanged (int newCurrentTabIndex, const String &newCurrentTabName)
{
	owner.setProperty (Ids::uiTabsCurrentTab, newCurrentTabIndex);
}
//[/MiscUserDefs]

//==============================================================================
CtrlrTabsComponent::CtrlrTabsComponent (CtrlrModulator &owner)
    : CtrlrComponent(owner), lf(*this),
      ctrlrTabs (0)
{
    addAndMakeVisible (ctrlrTabs = new CtrlrTabsInternal (*this));
    ctrlrTabs->setName (L"ctrlrTabs");


    //[UserPreSize]
	ctrlrTabs->setLookAndFeel (&lf);
	owner.setProperty (Ids::modulatorVstExported, false);

	setProperty (Ids::uiTabsCurrentTabChanged, "");
	setProperty (Ids::uiTabsDepth, 24);
	setProperty (Ids::uiTabsOutlineThickness, 2);
	setProperty (Ids::uiTabsFrontTabOutline, 1.0f);
	setProperty (Ids::uiTabsTabOutline, 0.5f);
	setProperty (Ids::uiTabsIndentThickness, 0);
	setProperty (Ids::uiTabsOrientation, 0);

	setProperty (Ids::uiTabsFrontTabFont, FONT2STR(Font(16)));
	setProperty (Ids::uiTabsTabFont, FONT2STR(Font(16)));

	setProperty (Ids::uiTabsOutlineGlobalColour, "0x00000000");
	setProperty (Ids::uiTabsOutlineGlobalBackgroundColour, "0x67000000");

	setProperty (Ids::uiTabsOutlineTabColour, "0xff303030");
	setProperty (Ids::uiTabsTextTabColour, "0xff909090");
	setProperty (Ids::uiTabsFrontTabOutlineColour, "0xff000000");
	setProperty (Ids::uiTabsFrontTabTextColour, "0xff000000");

	setProperty (Ids::uiTabsAddTab, 0);
	setProperty (Ids::uiTabsRemoveTab, 0);
    //[/UserPreSize]

    setSize (256, 256);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrTabsComponent::~CtrlrTabsComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	owner.getModulatorTree().removeListener (this);
    //[/Destructor_pre]

    deleteAndZero (ctrlrTabs);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrTabsComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrTabsComponent::resized()
{
    ctrlrTabs->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
	ctrlrTabs->setBounds (getUsableRect());
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrTabsComponent::setComponentValue (const double newValue, const bool sendChangeMessage)
{
	if (newValue >= ctrlrTabs->getNumTabs())
		ctrlrTabs->setCurrentTabIndex(0);
	else
		ctrlrTabs->setCurrentTabIndex(newValue);

	if (sendChangeMessage)
	{
		owner.getProcessor().setValueFromGUI (newValue);
	}
}

const double CtrlrTabsComponent::getComponentValue()
{
	return (ctrlrTabs->getCurrentTabIndex());
}

const int CtrlrTabsComponent::getComponentMidiValue()
{
	return (getComponentValue());
}

const double CtrlrTabsComponent::getComponentMaxValue()
{
	return (ctrlrTabs->getNumTabs()-1);
}

void CtrlrTabsComponent::modulatorChanged (CtrlrModulator *modulatorThatChanged)
{
}

void CtrlrTabsComponent::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiTabsOutlineThickness
		|| property == Ids::uiTabsIndentThickness)
	{
		ctrlrTabs->setOutline(getProperty(Ids::uiTabsOutlineThickness));
		ctrlrTabs->setIndent(getProperty(Ids::uiTabsIndentThickness));

		repaint();
	}

	else if (property == Ids::uiTabsCurrentTabChanged)
	{
		if (getProperty(property) == String::empty)
			return;

		tabChangedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}

	else if (property == Ids::uiTabsCurrentTab)
	{
		if (ctrlrTabs->getCurrentTabIndex() != (int)getProperty (property))
		{
			ctrlrTabs->setCurrentTabIndex (getProperty(property), false);
		}

		if (tabChangedCbk && !tabChangedCbk.wasObjectDeleted())
		{
			if (tabChangedCbk->isValid())
			{
				owner.getOwner().getCtrlrLuaManager().getMethodManager().call (tabChangedCbk, &owner, (int)getProperty(property));
			}
		}
	}

	else if (property == Ids::uiTabsOutlineGlobalColour
		|| property == Ids::uiTabsOutlineGlobalBackgroundColour
		|| property == Ids::uiTabsOutlineTabColour
		|| property == Ids::uiTabsTextTabColour
		|| property == Ids::uiTabsFrontTabOutlineColour
		|| property == Ids::uiTabsFrontTabTextColour)
	{
		ctrlrTabs->setColour ( TabbedComponent::backgroundColourId, VAR2COLOUR(getProperty(Ids::uiTabsOutlineGlobalColour)) );
		ctrlrTabs->setColour ( TabbedComponent::outlineColourId, VAR2COLOUR(getProperty(Ids::uiTabsOutlineGlobalBackgroundColour)) );

		ctrlrTabs->setColour ( TabbedButtonBar::tabOutlineColourId, VAR2COLOUR(getProperty(Ids::uiTabsOutlineTabColour)) );
		ctrlrTabs->setColour ( TabbedButtonBar::tabTextColourId, VAR2COLOUR(getProperty(Ids::uiTabsTextTabColour)) );
		ctrlrTabs->setColour ( TabbedButtonBar::frontOutlineColourId, VAR2COLOUR(getProperty(Ids::uiTabsFrontTabOutlineColour)) );
		ctrlrTabs->setColour ( TabbedButtonBar::frontTextColourId, VAR2COLOUR(getProperty(Ids::uiTabsFrontTabTextColour)) );

		repaint();
	}

	else if (property == Ids::uiTabsFrontTabFont
		|| property == Ids::uiTabsTabFont
		|| property == Ids::uiTabsFrontTabOutline
		|| property == Ids::uiTabsTabOutline)
	{
		ctrlrTabs->setLookAndFeel(0);
		ctrlrTabs->setLookAndFeel(&lf);
	}

	else if (property == Ids::uiTabsDepth)
	{
		ctrlrTabs->setTabBarDepth(getProperty(property));
	}

	else if (property == Ids::uiTabsOrientation)
	{
		ctrlrTabs->setOrientation ((TabbedButtonBar::Orientation)(int)getProperty(property));
	}

	else if (property == Ids::uiTabsTabName)
	{
		const int tabIndex = treeWhosePropertyHasChanged.getProperty(Ids::uiTabsTabIndex);
		ctrlrTabs->setTabName (tabIndex, treeWhosePropertyHasChanged.getProperty(property));
	}

	else if (property == Ids::uiTabsTabBackgroundColour)
	{
		const int tabIndex = treeWhosePropertyHasChanged.getProperty(Ids::uiTabsTabIndex);
		ctrlrTabs->setTabBackgroundColour (tabIndex, VAR2COLOUR(treeWhosePropertyHasChanged.getProperty(property)));
	}

	else if (property == Ids::uiTabsAddTab)
	{
		if (CtrlrComponent::restoreStateInProgress)
			return;

		if ((bool)getProperty(property) == true)
		{
			ValueTree v(Ids::uiTabsTab);
			getComponentTree().addChild (v, -1, 0);
		}

		setProperty(property, false);
	}

	else if (property == Ids::uiTabsRemoveTab)
	{
		if (CtrlrComponent::restoreStateInProgress)
			return;

		if ((bool)getProperty(property) == true)
		{
			PopupMenu m;
			for (int i=0; i<ctrlrTabs->getNumTabs(); i++)
			{
				m.addItem (i+1, ctrlrTabs->getTabNames() [i]);
			}
			const int ret = m.show();
			if (ret > 0)
			{
				if (AlertWindow::showOkCancelBox(AlertWindow::QuestionIcon, "Removing tab", "Are you sure you want to remove this tab? All child components in it will also be removed"))
				{
					getComponentTree().removeChild (ret-1, 0);
				}
			}
		}

		setProperty(property, false);
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

void CtrlrTabsComponent::valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded)
{
	addTab(childWhichHasBeenAdded);
}

void CtrlrTabsComponent::valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved)
{
	removeTab(childWhichHasBeenRemoved);
}

bool CtrlrTabsComponent::isOwned(CtrlrComponent *componentToCheck)
{
	for (int i=0; i<ctrlrTabs->getNumTabs(); i++)
	{
		for (int j=0; j<ctrlrTabs->getTabContentComponent(i)->getNumChildComponents(); j++)
		{
			CtrlrComponent *child = dynamic_cast<CtrlrComponent*>(ctrlrTabs->getTabContentComponent(i)->getChildComponent(j));
			if (child == componentToCheck)
			{
				return (true);
			}
		}
	}

	return (false);
}

void CtrlrTabsComponent::setOwned (CtrlrComponent *componentToOwn, const int subIndexInGroup, const bool shouldOwnThisComponent)
{
	if (componentToOwn == nullptr)
		return;

	if (shouldOwnThisComponent)
	{
		componentToOwn->setProperty (Ids::componentTabName, owner.getName(), true);
		componentToOwn->setProperty (Ids::componentTabId, subIndexInGroup, true);
		componentToOwn->setProperty (Ids::componentGroupped, true, true);
		componentToOwn->setLookAndFeel (owner.getOwner().getOwner().getCtrlrLookAndFeel());

		if (ctrlrTabs->getTabContentComponent(subIndexInGroup))
			ctrlrTabs->getTabContentComponent(subIndexInGroup)->addAndMakeVisible (componentToOwn);
	}
	else
	{
		owner.getOwner().getEditor()->getCanvas()->addAndMakeVisibleNg (componentToOwn);
		componentToOwn->setProperty (Ids::componentGroupped, false, true);

        if (!getOwner().getOwner().isSchemeAtLeast(1))
		{
            componentToOwn->setProperty (Ids::componentTabName, String::empty, false);
		}
	}
}

void CtrlrTabsComponent::canvasStateRestored()
{
	Array <CtrlrModulator*> children = owner.getOwner().getModulatorsWithProperty(Ids::componentTabName, owner.getName());

	for (int i=0; i<children.size(); i++)
	{
		if (children[i]->getComponent())
		{
			if (getOwner().getOwner().isSchemeAtLeast(1))
			{
				if ((bool)children[i]->getComponent()->getProperty(Ids::componentGroupped))
				{
					setOwned (children[i]->getComponent(), children[i]->getComponent()->getProperty(Ids::componentTabId));
				}
			}
			else
			{
				setOwned (children[i]->getComponent(), children[i]->getComponent()->getProperty(Ids::componentTabId));
			}
		}
	}
}

void CtrlrTabsComponent::addTab(const ValueTree tabToAdd)
{
	ValueTree tabTree = tabToAdd;

	const int tabId = ctrlrTabs->getNumTabs();

	if (!tabTree.hasProperty(Ids::uiTabsTabIndex))
		tabTree.setProperty (Ids::uiTabsTabIndex, tabId, 0);

	if (!tabTree.hasProperty(Ids::uiTabsTabName))
		tabTree.setProperty (Ids::uiTabsTabName, "Tab "+String(tabId), 0);

	if (!tabTree.hasProperty(Ids::uiTabsTabContentBackgroundColour))
		tabTree.setProperty (Ids::uiTabsTabContentBackgroundColour, Colours::yellow.toString(), 0);

	if (!tabTree.hasProperty(Ids::uiTabsTabBackgroundColour))
		tabTree.setProperty (Ids::uiTabsTabBackgroundColour, Colours::lightgrey.toString(), 0);

	if (!tabTree.hasProperty(Ids::uiTabsTabBackgroundImage))
		tabTree.setProperty (Ids::uiTabsTabBackgroundImage, COMBO_NONE_ITEM, 0);

	if (!tabTree.hasProperty(Ids::uiTabsTabBackgroundImageLayout))
		tabTree.setProperty (Ids::uiTabsTabBackgroundImageLayout, 36, 0);

	if (!tabTree.hasProperty(Ids::uiTabsTabBackgroundImageAlpha))
		tabTree.setProperty (Ids::uiTabsTabBackgroundImageAlpha, 255, 0);

	ctrlrTabs->addTab (	tabTree.getProperty(Ids::uiTabsTabName).toString(),
						VAR2COLOUR(tabTree.getProperty(Ids::uiTabsTabBackgroundColour)),
						new CtrlrTabsContentComponent(tabTree, *this),
						true,
						tabTree.getProperty(Ids::uiTabsTabIndex));
}

void CtrlrTabsComponent::removeTab(const ValueTree tabToRemove)
{
	const int tabId = tabToRemove.getProperty(Ids::uiTabsTabIndex);

	if (tabId >= 0)
	{
		if (ctrlrTabs->getTabContentComponent(tabId))
		{
			for (int i=0; i<ctrlrTabs->getTabContentComponent(tabId)->getNumChildComponents(); i++)
			{
				CtrlrComponent *child = dynamic_cast<CtrlrComponent*>(ctrlrTabs->getTabContentComponent(tabId)->getChildComponent(i));
				if (child != 0)
				{
					owner.getOwner().getEditor()->getCanvas()->removeComponent(child);
				}
			}
		}

		ctrlrTabs->removeTab(tabId);
	}
}

void CtrlrTabsComponent::modulatorNameChanged (const String &newName)
{
	for (int i=0; i<ctrlrTabs->getNumTabs(); i++)
	{
		CtrlrTabsContentComponent *c = dynamic_cast<CtrlrTabsContentComponent*>(ctrlrTabs->getTabContentComponent(i));
		if (c!=0)
		{
			c->parentNameChanged(newName);
		}
	}
}

void CtrlrTabsComponent::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrTabsComponent>("CtrlrTabsComponent")
	];
}

bool CtrlrTabsComponent::isInterestedInDragSource (const SourceDetails &dragSourceDetails)
{
	if (dragSourceDetails.description == "__ctrlr_component_selection")
	{
		return (true);
	}

	return (false);
}

void CtrlrTabsComponent::itemDropped (const SourceDetails &dragSourceDetails)
{
	if (dragSourceDetails.description == "__ctrlr_component_selection")
	{
		if (owner.getOwner().getEditor() && owner.getOwner().getEditor()->getSelection())
		{
			AffineTransform trans = owner.getOwner().getEditor()->moveSelectionToPosition(dragSourceDetails.localPosition.getX(), dragSourceDetails.localPosition.getY()-ctrlrTabs->getTabBarDepth());

			for (int i=0; i<owner.getOwner().getEditor()->getSelection()->getNumSelected(); i++)
			{
				CtrlrComponent *c = owner.getOwner().getEditor()->getSelection()->getSelectedItem(i);

				if (c != nullptr)
				{
					if (c == this || isOwned(c) || (bool)c->getProperty(Ids::componentIsLocked) == true)
						continue;

					setOwned (c, ctrlrTabs->getCurrentTabIndex(), true);

					c->setBounds (c->getBounds().transformedBy(trans));
				}
			}
		}
	}
}

void CtrlrTabsComponent::itemDragExit (const SourceDetails &dragSourceDetails)
{
}

void CtrlrTabsComponent::itemDragEnter (const SourceDetails &dragSourceDetails)
{
}

Array <CtrlrComponent*> CtrlrTabsComponent::getOwnedChildren()
{
	Array <CtrlrComponent*> ar;

	for (int i=0; i<ctrlrTabs->getNumTabs(); i++)
	{
		for (int j=0; j<ctrlrTabs->getTabContentComponent(i)->getNumChildComponents(); j++)
		{
			CtrlrComponent *child = dynamic_cast<CtrlrComponent*>(ctrlrTabs->getTabContentComponent(i)->getChildComponent(j));
			if (child != nullptr)
			{
				ar.add(child);
			}
		}
	}

	return (ar);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrTabsComponent" componentName=""
                 parentClasses="public CtrlrComponent, public CtrlrPanel::PanelListener"
                 constructorParams="CtrlrModulator &amp;owner" variableInitialisers="CtrlrComponent(owner), lf(*this)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="256" initialHeight="256">
  <BACKGROUND backgroundColour="ffffff"/>
  <GENERICCOMPONENT name="ctrlrTabs" id="e0c7af1494f7ba1c" memberName="ctrlrTabs"
                    virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" class="CtrlrTabsInternal"
                    params="*this"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
